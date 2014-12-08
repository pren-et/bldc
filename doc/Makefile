DOCUMENT = doc

.PHONY: all doc single bib clean

all:	single bib doc clean

doc:
	for i in {1..3}; do \
		pdflatex $(DOCUMENT).tex; \
	done

single:
	pdflatex $(DOCUMENT).tex

bib:
	bibtex $(DOCUMENT).aux

clean:
	rm *.aux
	rm *.bbl
	rm *.blg
	rm *.log
	rm *.out
	rm *.toc
	rm *.lot
	rm *.lof
