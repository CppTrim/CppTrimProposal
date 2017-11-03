.PHONY: doc clean

LATEXCOMMAND=xelatex
LATEXFLAGS=-file-line-error -halt-on-error

DOCROOT=proposal

doc: $(DOCROOT).pdf makefile

$(DOCROOT).pdf: $(DOCROOT).ltx
	$(LATEXCOMMAND) $(LATEXFLAGS) $<
	biber $(DOCROOT)
	$(LATEXCOMMAND) $(LATEXFLAGS) $<
	$(LATEXCOMMAND) $(LATEXFLAGS) $<

clean:
	@rm -f $(DOCROOT).aux
	@rm -f $(DOCROOT).bbl
	@rm -f $(DOCROOT).bcf
	@rm -f $(DOCROOT).blg
	@rm -f $(DOCROOT).log
	@rm -f $(DOCROOT).out
	@rm -f $(DOCROOT).pdf
	@rm -f $(DOCROOT).run.xml
	@rm -f $(DOCROOT).toc
	@rm -f $(DOCROOT).fls
