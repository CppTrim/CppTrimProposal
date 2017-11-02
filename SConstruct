from __future__ import print_function

import os

# It is assumed that the C++ compiler is g++ >= 7.0 or clang >= 3.9. Clang 5
# and later and g++ 7.2.1 and later support -std=c++17, so no need for
# -std=c++1z
cxx_flags = ['-std=c++17', '-g']

if 'CXX' in os.environ:
    if os.environ['CXX'].startswith('clang++'):
        cpp_environment = Environment(
            tools=['clangxx', 'link'],
            CXX=os.environ['CXX'],
            CXXFLAGS=cxx_flags,
        )
    else:
        cpp_environment = Environment(
            tools=['g++', 'gnulink'],
            CXX=os.environ['CXX'],
            CXXFLAGS=cxx_flags,
        )
else:
    cpp_environment = Environment(
        tools=['c++', 'link'],
        CXXFLAGS=cxx_flags,
    )

# With g++ can add -fconcepts to get concepts. Clang does not support concepts.
if 'EXTRACXXFLAGS' in os.environ:
    cpp_environment.Append(CXXFLAGS=os.environ['EXTRACXXFLAGS'])

test = cpp_environment.Program('string_trim_tests.cpp')

# For experimentation hardwire the location of rapidcheck. Need to check if
# the library is in Conan.

includes_directories = [os.environ['HOME'] + '/include']
libs_directories = [os.environ['HOME'] + '/Built/' + location for location in ('lib', 'lib64')]

property_test = cpp_environment.Program('string_trim_property_tests.cpp',
                                        CPPPATH=includes_directories,
                                        LINKFLAGS=['-L' + location for location in libs_directories],
                                        LIBS='rapidcheck',
)

latex_environment = Environment(
    tools=['xetex'],
)

document = latex_environment.XELATEX('proposal')

Command('test', test, './$SOURCE')
Command('property_test', property_test, './$SOURCE')
Alias('doc', document)
