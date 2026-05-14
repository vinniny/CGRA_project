# Chapter 4 — Software Design and Implementation (LaTeX)

Standalone LaTeX project that builds the Software Design chapter of the
graduation thesis as a self-contained PDF. Content is verified against
the locked demo at `baremetal-mnist-fc-demo-locked` and the head of
`main` (commit `2ad1e7f` at time of writing).

## Files

| File | Role |
|---|---|
| `main.tex` | Standalone wrapper. `\maketitle`, ToC, then `\input{chapter4}`. |
| `preamble.tex` | All package loads, TikZ styles, listings style, colour palette. |
| `chapter4.tex` | The chapter itself: sections 4.1, 4.2, 4.3 with subsections, TikZ swim-lane flowchart (Fig. 4.1), FC-group detail (Fig. 4.2), register map (Tab. 4.2), six embedded code listings, and the silicon-measured performance summary (Tab. 4.3). |
| `Makefile` | `latexmk` wrapper. `make`, `make watch`, `make clean`, `make distclean`. |
| `figures/` | Reserved for any rendered raster figures (currently empty — all diagrams are TikZ in-line). |
| `listings/` | Reserved for any external code listings included via `\lstinputlisting` (currently empty — all snippets are inline). |

## Build

```bash
cd 06_doc/thesis_ch4
make            # produces main.pdf
make watch      # auto-rebuild on edit (latexmk -pvc)
make clean      # drop intermediates
```

Requires a TeX Live distribution with:
- `pdflatex` (engine)
- `latexmk` (build driver)
- packages: `geometry`, `parskip`, `microtype`, `booktabs`, `tabularx`,
  `longtable`, `multirow`, `enumitem`, `cleveref`, `xcolor`, `listings`,
  `tikz` with libraries `arrows.meta`, `calc`, `chains`,
  `decorations.pathmorphing`, `fit`, `positioning`, `shapes.geometric`,
  `shapes.symbols`, `backgrounds`, `shadows.blur`,
  `caption`, `subcaption`, `hyperref`.

All of the above are in `texlive-latex-extra` and
`texlive-pictures` on Debian/Ubuntu, or
`texlive-collection-latex` + `texlive-collection-pictures` on
TeX Live's `tlmgr`.

## Integrating into a larger thesis

If the larger thesis uses `\documentclass{book}` or
`\documentclass{report}`, the chapter file can be reused with two edits:

1. In the master thesis, do **not** `\input` `preamble.tex` (the master
   should already define its own). Instead, ensure these packages are
   loaded in the master preamble: `listings`, `xcolor`, `tikz` (with
   the libraries listed in `preamble.tex`), `booktabs`, `tabularx`,
   `cleveref`, `enumitem`.
2. In `chapter4.tex`, remove the `\setcounter{section}{0}` and the four
   subsequent `\setcounter{...}{0}` calls — those exist only so the
   standalone build numbers the sections as 4.1, 4.2, … rather than
   1, 2, … When `\input` from inside a `book`/`report` chapter, the
   standard `\chapter{Software Design and Implementation}` command
   provides the numbering automatically.

## Verification

Every register address, register offset, function signature, and code
snippet in this chapter was cross-checked against the source files in
`07_sw/baremetal/` (head commit `2ad1e7f`). The cross-check report is
in the session transcript; the six discrepancies it identified
(C1–C6) have all been folded into the version committed here.
