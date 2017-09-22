.PHONY: test doc clean

CXX=g++-7
EXTRACXXFLAGS=
CXXFLAGS=-std=c++1z -g $(EXTRACXXFLAGS)
LATEXCOMMAND=xelatex
LATEXFLAGS=-file-line-error -halt-on-error 

TESTROOT=string_trim_tests
DOCROOT=proposal
HEADER=string_trim.hpp

all: test doc

test: $(TESTROOT)
	./$(TESTROOT)

$(TESTROOT): $(TESTROOT).cpp $(HEADER) makefile
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

doc: $(DOCROOT).pdf makefile

$(DOCROOT).pdf: $(DOCROOT).ltx
	$(LATEXCOMMAND) $(LATEXFLAGS) $<
	biber $(DOCROOT)
	$(LATEXCOMMAND) $(LATEXFLAGS) $<
	$(LATEXCOMMAND) $(LATEXFLAGS) $<

clean:
	rm -f $(TESTROOT)
	rm -f $(DOCROOT).aux
	rm -f $(DOCROOT).bbl
	rm -f $(DOCROOT).bcf
	rm -f $(DOCROOT).blg
	rm -f $(DOCROOT).log
	rm -f $(DOCROOT).out
	rm -f $(DOCROOT).pdf
	rm -f $(DOCROOT).run.xml
	rm -f $(DOCROOT).toc
