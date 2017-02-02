Limbo.Parsers.DefParser {#Parsers_DefParser}
---------

[TOC]

# Introduction {#Parsers_DefParser_Introduction}

[DEF](https://en.wikipedia.org/wiki/Design_Exchange_Format) together with [LEF](https://en.wikipedia.org/wiki/Library_Exchange_Format) is a common file format in VLSI physical design. 
Generally LEF/DEF formats are quit complicated due to the complex cases in chip design. 
The parser is not a full implementation of the LEF/DEF manual, but it is tested under various academic benchmarks. 
It is also easy to support additional features with low effort. 

# Examples {#Parsers_DefParser_Examples}

## Flex/Bison Parser {#Parsers_DefParser_Flex_Bison}

See documented version: [test/parsers/def/test_bison.cpp](@ref def/test_bison.cpp)
\include test/parsers/def/test_bison.cpp

Compiling and running commands (assuming LIMBO_DIR is exported as the environment variable to the path where limbo library is installed)
~~~~~~~~~~~~~~~~
g++ -o test_bison test_bison.cpp -I $LIMBO_DIR/include -L $LIMBO_DIR/lib -ldefparser
./test_bison benchmarks/simple.def
~~~~~~~~~~~~~~~~

## All Examples {#Parsers_DefParser_Examples_All}

- [test/parsers/def/test_bison.cpp](@ref def/test_bison.cpp)

# References {#Parsers_DefParser_References}

- [limbo/parsers/def/bison/DefDataBase.h](@ref DefDataBase.h)
- [limbo/parsers/def/bison/DefDriver.h](@ref DefDriver.h)
