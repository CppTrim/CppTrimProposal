import os

# It is assumed that the C++ compiler is g++ >= 7.0 or clang >= 3.9

# Clang 5 and later supports -std=c++17
cxx_flags = ['-std=c++1z', '-g']

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

latex_environment = Environment(
    tools=['xetex'],
)

document = latex_environment.XELATEX('proposal')

Command('test', test, './$SOURCE')
Alias('doc', document)
