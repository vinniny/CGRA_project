#!/usr/bin/env bash
# strip_coauthor_trailer.sh
#
# One-shot history rewrite to remove the "Co-Authored-By: Claude ..."
# trailer (and the trailing blank line that line leaves behind) from
# every commit on the current branch. Does NOT push.
#
# Safety:
#   - Aborts if the working tree has uncommitted changes
#   - Aborts if HEAD is not on `main`
#   - Aborts if the backup tag `pre-coauthor-sweep-backup` already exists
#   - Aborts if the OLDEST_SHA can't be resolved
#   - Requires the user to type YES at the confirmation prompt
#   - After rewrite, verifies (a) commit count unchanged, (b) zero
#     remaining `Co-Authored-By: Claude` lines on the new branch
#   - Cleans up `refs/original/` left over by filter-branch
#   - Force-pushing is a SEPARATE manual step printed at the end —
#     this script never touches `origin`.
#
# Rollback (if anything looks wrong before you push):
#   git reset --hard pre-coauthor-sweep-backup
#   git for-each-ref --format='%(refname)' refs/original/ | xargs -n1 git update-ref -d
#
# Usage:
#   bash scripts/strip_coauthor_trailer.sh           # full run, prompts for YES
#   DRY_RUN=1 bash scripts/strip_coauthor_trailer.sh # show what would change, do nothing
#
set -euo pipefail

OLDEST_SHA="8b30a54"   # earliest commit known to carry the trailer
BACKUP_TAG="pre-coauthor-sweep-backup"
BRANCH_EXPECTED="main"
TRAILER_PATTERN='^Co-Authored-By: Claude'

bold() { printf "\033[1m%s\033[0m\n" "$*"; }
red()  { printf "\033[31m%s\033[0m\n" "$*"; }
green(){ printf "\033[32m%s\033[0m\n" "$*"; }
yellow(){ printf "\033[33m%s\033[0m\n" "$*"; }
die()  { red "ABORT: $*"; exit 1; }

# ─── Preflight checks ─────────────────────────────────────────────────
bold "[1/7] Preflight checks"

current_branch=$(git rev-parse --abbrev-ref HEAD)
[ "$current_branch" = "$BRANCH_EXPECTED" ] || \
    die "expected branch $BRANCH_EXPECTED, got '$current_branch'"

git diff --quiet HEAD -- || die "working tree has uncommitted changes; commit or stash first"
[ -z "$(git status --porcelain | grep -v '^??')" ] || \
    die "working tree has staged/modified files; commit or stash first"

if git rev-parse "$BACKUP_TAG" >/dev/null 2>&1; then
    die "backup tag $BACKUP_TAG already exists; delete it first if you intend to re-run"
fi

if ! git rev-parse "$OLDEST_SHA^{commit}" >/dev/null 2>&1; then
    die "oldest violator SHA $OLDEST_SHA not in repo"
fi

if [ -d .git/refs/original ] || git for-each-ref refs/original/ | grep -q .; then
    die "stale refs/original/ from a previous filter-branch present; clean them first"
fi

green "  preflight OK"

# ─── Count violators ──────────────────────────────────────────────────
bold "[2/7] Scope"
violator_count=$(git log --grep="$TRAILER_PATTERN" --pretty=format:"%H" | wc -l)
total_count=$(git rev-list --count HEAD)
echo "  total commits on $BRANCH_EXPECTED:   $total_count"
echo "  commits carrying the trailer:        $violator_count"
echo "  rewrite range:                       ${OLDEST_SHA}^..HEAD"
echo "  oldest violator $(git log -1 --pretty=format:'%h %ad %s' --date=short $OLDEST_SHA)"
echo "  newest violator $(git log -1 --pretty=format:'%h %ad %s' --date=short HEAD)"
[ "$violator_count" -gt 0 ] || die "no commits matched the trailer; nothing to do"

# ─── Confirm ──────────────────────────────────────────────────────────
if [ "${DRY_RUN:-0}" = "1" ]; then
    yellow "[3/7] DRY_RUN=1 — exiting before any change. Re-run without DRY_RUN=1 to apply."
    exit 0
fi

bold "[3/7] Confirm"
echo "  This will REWRITE HISTORY on '$BRANCH_EXPECTED' (new SHAs for $violator_count commits)."
echo "  A backup tag '$BACKUP_TAG' will mark the current HEAD for rollback."
echo "  Origin is NOT touched. Force-push is a manual step printed at the end."
echo
read -p "  Type YES to proceed: " confirm
[ "$confirm" = "YES" ] || die "did not receive YES; aborting"

# ─── Backup ───────────────────────────────────────────────────────────
bold "[4/7] Tag current HEAD as $BACKUP_TAG"
git tag "$BACKUP_TAG" HEAD
green "  $BACKUP_TAG -> $(git rev-parse HEAD)"

# ─── Rewrite ──────────────────────────────────────────────────────────
bold "[5/7] git filter-branch (this rewrites $violator_count commit messages)"
# Write the Python filter to a tempfile so we never have to shell-escape
# the script body through filter-branch's --msg-filter argument. That
# avoids quoting bugs that previously truncated the script mid-line.
FILTER_PY=$(mktemp /tmp/strip_coauthor_filter.XXXXXX.py)
trap 'rm -f "$FILTER_PY"; rm -rf .git-rewrite 2>/dev/null || true' EXIT
cat > "$FILTER_PY" <<'PYEOF'
import sys, re
msg = sys.stdin.read()
lines = [l for l in msg.splitlines(keepends=True)
         if not re.match(r"^Co-Authored-By: Claude", l)]
while lines and lines[-1].strip() == "":
    lines.pop()
sys.stdout.write("".join(lines))
if lines and not lines[-1].endswith("\n"):
    sys.stdout.write("\n")
PYEOF

# Quick self-test of the filter on a synthetic message so we never run
# filter-branch with a broken script.
expected="foo
bar"
got=$(printf 'foo\nbar\n\nCo-Authored-By: Claude X <y@z>\n' | python3 "$FILTER_PY")
[ "$got" = "$expected" ] || die "filter self-test failed; aborting before history rewrite"
green "  filter self-test passed"

git filter-branch -f --msg-filter "python3 $FILTER_PY" \
    "${OLDEST_SHA}^..HEAD" 2>&1 | tail -10

# ─── Post-conditions ──────────────────────────────────────────────────
bold "[6/7] Verify"

new_total=$(git rev-list --count HEAD)
if [ "$new_total" != "$total_count" ]; then
    red "FAIL: commit count changed ($total_count -> $new_total). Rolling back."
    git reset --hard "$BACKUP_TAG"
    die "rolled back to $BACKUP_TAG"
fi
green "  commit count unchanged ($new_total)"

remaining=$(git log --grep="$TRAILER_PATTERN" --pretty=format:"%H" | wc -l)
if [ "$remaining" != "0" ]; then
    red "FAIL: $remaining commits still carry the trailer. Rolling back."
    git reset --hard "$BACKUP_TAG"
    die "rolled back to $BACKUP_TAG"
fi
green "  zero remaining trailers"

# Show before/after of one commit (the newest) for visual confirmation
echo
echo "  Newest commit, before:"
git show --no-patch --format="    %H%n    %s%n----%n%b" "$BACKUP_TAG" | head -20
echo
echo "  Newest commit, after:"
git show --no-patch --format="    %H%n    %s%n----%n%b" HEAD | head -20

# ─── Re-anchor the locked-demo tag (if it existed) ────────────────────
bold "[7/7] Cleanup + re-anchor tags"

# filter-branch leaves refs/original/refs/heads/main pointing at the old
# history. Drop it so subsequent runs aren't confused.
if git for-each-ref refs/original/ | grep -q .; then
    git for-each-ref --format='%(refname)' refs/original/ \
        | xargs -n1 git update-ref -d
    green "  removed stale refs/original/ refs"
fi

LOCKED_TAG="baremetal-mnist-fc-demo-locked"
if git rev-parse "$LOCKED_TAG" >/dev/null 2>&1; then
    # The old tag points at the pre-rewrite SHA. Re-anchor at the new
    # SHA whose first line matches the old commit subject.
    old_sha=$(git rev-parse "$LOCKED_TAG")
    old_subject=$(git show --no-patch --format='%s' "$old_sha")
    new_sha=$(git log --pretty=format:"%H %s" | \
              awk -v s="$old_subject" '$0 ~ s {print $1; exit}')
    if [ -n "$new_sha" ]; then
        git tag -d "$LOCKED_TAG"
        git tag "$LOCKED_TAG" "$new_sha"
        green "  re-anchored $LOCKED_TAG: $old_sha -> $new_sha"
    else
        yellow "  WARN: could not re-anchor $LOCKED_TAG (subject not found in new history)"
    fi
fi

echo
green "DONE. History rewritten locally. Origin still has the OLD history."
echo
bold "Next step (when YOU are ready — this is destructive on origin):"
echo "  git push --force-with-lease origin main"
echo "  git push --force origin $LOCKED_TAG     # if you re-anchored a tag"
echo
bold "Rollback (if you change your mind BEFORE pushing):"
echo "  git reset --hard $BACKUP_TAG"
echo "  git tag -d $LOCKED_TAG && git tag $LOCKED_TAG <original-SHA>"
echo
echo "Backup tag remains in place. Delete it once you're satisfied:"
echo "  git tag -d $BACKUP_TAG"
