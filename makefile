.PHONY: test

CXXFLAGS=-std=c++1z

all: test proposal.pdf

test: string_trim_tests
	./string_trim_tests

string_trim_tests: string_trim_tests.cpp string_trim.hpp makefile
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

proposal.pdf: proposal.tex
	xelatex $<
	xelatex $<
	xelatex $<
