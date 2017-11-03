[![Travis-CI](https://travis-ci.org/CppTrim/CppTrimProposal.svg?branch=master)](https://travis-ci.org/CppTrim/CppTrimProposal)
[![Licence](https://img.shields.io/badge/licence-gfdl_1.3-green.svg)](https://www.gnu.org/licenses/fdl-1.3.en.html)

# C++ Trim

This repository is for work by various people to create a proposal for a (set of) trim function(s) for the C++
standard library. This repository has the working document and a reference implementation.

## Getting Involved

The usual GitHub approach is (fairly obviously?) the way to go. Clone this repository within GitHub and then
from there clone to your local machine. However a little more is needed. You may want to install Python 3
and [SCons](http://scons.org/) 3 for builds, though there is a Make set up. However a little more is needed…

The tests for the code rely on [RapidCheck](https://github.com/emil-e/rapidcheck). This repository has a
submodule that pulls RapidCheck to a known place within the working tree of this repository. However the
library is not header only so there is a build phase needed after checking out this repository. The approach
used for the Travis-CI test is to:
```
git submodule init
git submodule update
mkdir RapidCheckBuild
pushd RapidCheckBuild
cmake ../RapidCheck
make
popd
```
This creates the RapidCheck library file needed for linking. With all this done, you can then go on to run
the tests:
```
cd src
scons test property-test
```
should run the two tests which should pass. SCons 3 running on Python 3 is strongly recommended, in fact
this is the only combination known to work, no other has been tried. For those not interested in using
SCons:
```
cd src
make
```

There is also the document that is the formal proposal – still in very early stages. This is a LaTeX document
built using XeLaTeX. The Debian (and hence Ubuntu) packages requires are:

* texlive-xetex
* texlive-latex-recommended
* texlive-latex-extra
* texlive-fonts-recommended
* texlive-bibtex-extra

Other distributions and OSes will have different package structures, or may not use TeX Live. In dire straights installing the full
TeX Live system has to work. With these TeX Live bits installed then from the project root:
```
cd doc
scons
```
or for those not interested in using SCons:
```
cd doc
make
```
You should now have proposal.pdf.

## LICENCE

The material here is licenced under the [GFDL 1.3](https://www.gnu.org/licenses/fdl-1.3.en.html)
[![Licence](https://img.shields.io/badge/licence-gfdl_1.3-green.svg)](https://www.gnu.org/licenses/fdl-1.3.en.html)
