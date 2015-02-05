
#**Limbo Library**
---------

Limbo Library for VLSI CAD Design 

---------

All components are written with C/C++ and API is designed for easy usage and simple embedding. 

---------

## Components 
| Components              | Languages & Libraries           |
| ----------------------- | ------------------------------- |
| Lef Parser              | flex/bison                      |
|                         | boost.spirit                    |
| Def Parser              | flex/bison                      |
|                         | boost.spirit                    |
| Gds Parser              | stream parser: c/c++            |
|                         | ascii parser: boost.spirit      |
| Tf Parser               | boost.spirit                    |
| Lp Parser               | flex/bison                      |
| LP Min-Cost Flow Solver | boost, lemon                    |
| Geometry Algorithms     | c++                             |
| String Algorithms       | c++                             |
| Math Utilities          | c++                             |
| Partition Algorithms    | c++                             |

## Authors

|  Name              | Affiliation                |  email                            |
| ------------------ | -------------------------- | --------------------------------- |
| Yibo Lin           | ECE Dept, UT Austin        | yibolin@utexas.edu			      |

## Maintainers

|  Name              | Affiliation                |  email                            |
| ------------------ | -------------------------- | --------------------------------- |
| UTDA Folks         | ECE Dept, UT Austin        | http://www.cerc.utexas.edu/utda/  |

## Introduction

### 1. Flex

* A fast scanner generator or lexical analyzer generator. Another famous related software is Lex.

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

## Copyright 
Copyright (c) 2014-2014 

