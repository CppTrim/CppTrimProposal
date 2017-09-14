.PHONY: test doc clean

CXXFLAGS=-std=c++1z

TESTROOT=string_trim_tests
DOCROOT=proposal

all: test doc

test: $(TESTROOT)
	./$(TESTROOT)

string_trim_tests: $(TEST_ROOT).cpp $(TESTROOT).hpp makefile
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

doc: $(DOCROOT).pdf makefile

$(DOCROOT).pdf: $(DOCROOT).tex
	xelatex $<
	biber $(DOCROOT)
	xelatex $<
	xelatex $<

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
