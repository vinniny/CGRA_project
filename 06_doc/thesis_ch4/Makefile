# Makefile for the Chapter 4 LaTeX build.
# Usage:
#   make          — build main.pdf (standalone Chapter 4 PDF)
#   make watch    — continuous build (latexmk -pvc); needs a PDF viewer
#   make clean    — drop intermediate files
#   make distclean — also drop main.pdf

LATEX     := pdflatex
LATEXMK   := latexmk
DOC       := main
SOURCES   := main.tex preamble.tex chapter4.tex

.PHONY: all watch clean distclean

all: $(DOC).pdf

$(DOC).pdf: $(SOURCES)
	$(LATEXMK) -pdf -interaction=nonstopmode -halt-on-error $(DOC).tex

watch: $(SOURCES)
	$(LATEXMK) -pdf -pvc -interaction=nonstopmode $(DOC).tex

clean:
	$(LATEXMK) -c
	rm -f *.aux *.log *.toc *.out *.fls *.fdb_latexmk *.synctex.gz

distclean: clean
	rm -f $(DOC).pdf
