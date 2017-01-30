Limbo.ProgramOptions {#ProgramOptions}
---------

[TOC]

## Introduction {#Introduction}

The package allows programs obtain command line options, such as (name, value) pairs, from user input without writing wordy parsing blocks in the source code. 
It supports various data types, including integer, floating point number, char, boolean, string, vector, etc. 
It provides easy API for developers to define command line options to their programs with a highly extendable manner, i.e., only single line of code for each option. No need to write any code for parsing. 
It also offers detailed error reporting scheme that print incorrect and missing arguments. 

## Examples {#Examples}

### Example 1 {#Example1}

[test/programoptions/test_ProgramOptions_simple.cpp](@ref test_ProgramOptions_simple.cpp)
\include test/programoptions/test_ProgramOptions_simple.cpp

Compiling and running commands (assuming LIMBO_DIR is valid and limbo library has been properly installed)
~~~~~~~~~~~~~~~~
# linkage is necessary for Limbo.ProgramOptions
g++ test_ProgramOptions_simple.cpp -I $LIMBO_DIR/include -L $LIMBO_DIR/lib -lprogramoptions
# test 1: help message 
./a.out -help
# test 2: integer and floating point number 
./a.out -i 20 -f 1.5 
# test 3: vector of integers; the numbers are appending to the container 
./a.out -i 20 -f 1.5 -vi 10 -vi 30 -vi 50
~~~~~~~~~~~~~~~~
Output 1
~~~~~~~~~~~~~~~~
parsing succeeded
help = true
i = 100
fp = 0
vInteger =
~~~~~~~~~~~~~~~~
Output 2
~~~~~~~~~~~~~~~~
parsing succeeded
help = false
i = 20
fp = 1.5
vInteger =
~~~~~~~~~~~~~~~~
Output 3
~~~~~~~~~~~~~~~~
parsing succeeded
help = false
i = 20
fp = 1.5
vInteger = 10 30 50
~~~~~~~~~~~~~~~~

### Example 2 {#Example2}

[test/programoptions/test_ProgramOptions.cpp](@ref test_ProgramOptions.cpp)
\include test/programoptions/test_ProgramOptions.cpp
