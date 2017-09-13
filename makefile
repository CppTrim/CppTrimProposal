.PHONY: test

CXX=g++ -std=c++1z

test: string_trim_tests
	./string_trim_tests

proposal.pdf: proposal.tex
	xelatex proposal.tex
	xelatex proposal.tex
	xelatex proposal.tex
