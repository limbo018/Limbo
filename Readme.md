#**Limbo Library**
---------

Limbo Library for VLSI CAD Design 

---------

All components are written with C/C++ and API is designed for easy usage and simple embedding. 

---------

## Components 
| Components              | Languages & Libraries           | Description                                              |
| ----------------------- | ------------------------------- | -------------------------------------------------------- |
| Lef Parser              | flex/bison                      |                                                          |
|                         | boost.spirit                    |                                                          |
| Def Parser              | flex/bison                      |                                                          |
|                         | boost.spirit                    |                                                          |
| Gds Parser              | stream parser: c/c++            |                                                          |
|                         | ascii parser: boost.spirit      |                                                          |
| Tf Parser               | boost.spirit                    |                                                          |
| Verilog netlist parser  | flex/bison                      | read verilog netlist to initialize nets during placement |
| Lp Parser               | flex/bison                      |                                                          |
| GDF Parser              | flex/bison                      | routing file format from Jason Cong's group at UCLA      |
| Bookshelf Parser        | flex/bison                      | placement file format from UCSD                          |
| LP Min-Cost Flow Solver | boost, lemon                    |                                                          |
| Geometry Algorithms     | c++                             |                                                          |
| String Algorithms       | c++                             |                                                          |
| Math Utilities          | c++                             |                                                          |
| Partition Algorithms    | c++                             |                                                          |
| Placement Algorithms    | c++                             | some common and useful placement algorithms              |
| Graph Algorithms        | c++                             | basic graph algorithms based on Boost.Graph structure    |
| Program Options         | c++                             | package for easy command line options for a program      |
| Makefile Utilities      | makefile                        | makefile help functions                                  |
| Third Party Libraries   | c/c++/fortran                   | OpenBlas, Csdp                                           |

## Authors & Maintainers

|  Name              | Affiliation                |  email                            |
| ------------------ | -------------------------- | --------------------------------- |
| Yibo Lin           | ECE Dept, UT Austin        | yibolin@utexas.edu			      |

## Users

|  Name              | Affiliation                |  email                            |
| ------------------ | -------------------------- | --------------------------------- |
| UTDA Folks         | ECE Dept, UT Austin        | http://www.cerc.utexas.edu/utda/  |

## Introduction

### 1. Flex

* A fast scanner generator or lexical analyzer generator. Another famous related software is Lex.
Current parsers support flex 2.5.37. 

### 2. Bison 

* A Yacc-compatible parser generator that is part of the GNU Project. 
	For details, please refer to [here](http://en.wikipedia.org/wiki/GNU_bison).
	Another famous related software is Yacc.

### 3. Boost.Spirit

* An object-oriented, recursive-descent parser and output generation library for C++. 
	For details, please refer to [here](http://www.boost.org/doc/libs/1_55_0/libs/spirit/doc/html/index.html).

### 4. LL Parser 

* In computer science, a LL parser is a top-down parser for a subset of context-free languages. 
	It parses the input from Left to right, performing Leftmost derivation of the sentence. 

### 5. LR Parser 

* In computer science, LR parsers are a type of bottom-up parsers that efficiently handle 
	deterministic context-free languages in guaranteed linear time. 

### 6. LL v.s. LR

* Bison is based on LR parser and Boost.Spirit is based on LL parser.
Please refer to [here](http://cs.stackexchange.com/questions/43/language-theoretic-comparison-of-ll-and-lr-grammars).

### 7. LP and Min-Cost Flow 

* Min-cost flow (MCF) is a special case of linear programs (LP). 
It is usually faster than general LP solver and is also able to achieve integer solution.
Some LP can be directly transformed to MCF problem, and for some other LP, its duality is a MCF problem. 
In this library, an API for lemon (MFC solver) is implemented to solve LP and dual LP problems. 
The API supports reading files with both LGF (lemon graph format) and LP (linear program format) and then dump out solutions. 
Thus, it will be easier to verify results with general LP solvers such as Gurobi or CBC.

## Bug Report 

Please report bugs to Yibo Lin (yibolin at utexas dot edu). 

## Intallation

In the directory of limbo library, run

make install

## Examples

In the subdirectories of source code, there are test folders including test/example programs.

## FAQ

###1. *(Deprecated)* Compiling errors like
```
LefScanner.cc:5582:21: error: out-of-line definition of 'LexerInput' does not match any declaration in 'LefParserFlexLexer'
                        size_t yyFlexLexer::LexerInput( char* buf, size_t max_size )
```
come from old versions of flex, such as 2.5.35. 

**A:** It can be solved by installing correct flex version 2.5.37 and add the directory to correct flex to PATH environmental variable. 

###2. *(Deprecated)* Compiling errors like 
```
LefScanner.cc:3195:8: error: member reference type 'std::istream *' (aka 'basic_istream<char> *') is a pointer; did you mean to use '->'?
                        yyin.rdbuf(std::cin.rdbuf());
```
come from new versions of flex, such as 2.6.0. 

**A:** It can be solved by installing correct flex version 2.5.37 and add the directory to correct flex to PATH environmental variable. 

###3. Compiling errors related to LefScanner.cc usually come from the configurations of flex version and environmental variables FLEX_DIR and LEX_INCLUDE_DIR. 

**A:** LefScanner.cc needs to include the correct FlexLexer.h from the flex package for compilation; i.e., the version of FlexLexer.h must match the version of the flex executable. 
Most errors for LefScanner.cc are caused by the failure of finding the correct FlexLexer.h (be careful when you have multiple versions of flex installed). 
To solve the problem, users can set the environmental variable FLEX_DIR such that $FLEX_DIR/include points to the directory containing FlexLexer.h, or alternatively set LEX_INCLUDE_DIR to the directory containing FlexLexer.h. 
The decision can be made according to how the flex package is installed.  

## Copyright 
The software is released under MIT license except third party packages. Please see the LICENSE file for details. 

Third party package **c-thread-pool** is released under MIT license. 

Third party package **csdp** is released under CPL v1.0 license. 

Third party package **OpenBlas** has its copyright reserved; please check its license. 

Third party package **liblinear** has its copy right reserved; please check its license. 
