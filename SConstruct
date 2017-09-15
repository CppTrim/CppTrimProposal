import os

if 'CXX' in os.environ:
    if os.environ['CXX'].startswith('clang++'):
        cpp_environment = Environment(
            tools=['clangxx', 'link'],
            CXX=os.environ['CXX'],
            CXXFLAGS=['-std=c++1z'],
        )
    else:
        cpp_environment = Environment(
            tools=['g++', 'gnulink'],
            CXX=os.environ['CXX'],
            CXXFLAGS=['-std=c++1z'],
        )
else:
    cpp_environment = Environment(
        tools=['c++', 'link'],
        CXXFLAGS=['-std=c++1z'],
    )

test = cpp_environment.Program('string_trim_tests.cpp')

latex_environment = Environment(
    tools=['xetex'],
)

document = latex_environment.XELATEX('proposal')

Command('test', test, './$SOURCE')
Alias('doc', document)
