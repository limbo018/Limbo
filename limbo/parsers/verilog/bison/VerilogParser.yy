/* $Id: parser.yy 48 2009-09-05 08:07:10Z tb $ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

/*#include "expression.h"*/

%}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.3"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug

/* start symbol is named "start" */
%start start

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%name-prefix="VerilogParser"

/* set the parser's class identifier */
%define "parser_class_name" "Parser"

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

 /*** BEGIN EXAMPLE - Change the example grammar's tokens below ***/

%union {
    char* str;
    struct {
        long value;
        long bits;
    } mask;
}

%token ALWAYS 
%token EQUAL
%token POSEDGE
%token NEGEDGE
%token OR
%token BEG
%token END
%token AND
%token IF
%token ELSE
%token INIT
%token AT
%token ID
%token NUM
%token MODULE
%token INPUT
%token OUTPUT
%token REG
%token WIRE
%token INTEGER
%token TIME
%token BIT_MASK;
%token OCT_MASK;
%token DEC_MASK;
%token HEX_MASK;

%left OR
%left AND

%type<str> ID 
%type<mask> BIT_MASK OCT_MASK DEC_MASK HEX_MASK
%type<int> VAL NUM VAL_DEC EXPR_CALC

 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include "VerilogDriver.h"
#include "VerilogScanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN EXAMPLE - Change the example grammar rules below ***/

PROGRAM: OPS ;

OPS: INIT_BLOCK | VAL_DEC | MODULE_INIT | OP_BLOCK
| OPS OPS

OP_CALC: ID EQUAL EXPR_CALC
|   TIME OP_CALC

OP_BLOCK: OP_CALC ';'
| '{' OP_BLOCK '}'
|   IF '(' EXPR ')' OP_BLOCK   {; }
|   IF '(' EXPR ')' OP_BLOCK ELSE OP_BLOCK {;}
|   OP_TREE

OP_TREE: ALWAYS AT '(' POSNEG_EXPR ')' OP_BLOCK {;}
|   ALWAYS INIT_VAL {;}

POSNEG_EXPR: POSEDGE ID
| POSNEG_EXPR OR POSNEG_EXPR
| POSNEG_EXPR AND POSNEG_EXPR ; 

EXPR: EXPR_CALC {$$ = $1;}
|   '!' EXPR_CALC {$$ = !$1;}
|   EXPR '>' EXPR_CALC {$$ = ($1>$2);}
|   EXPR '<' EXPR_CALC {$$ = ($1<$2);}
|   EXPR '=' EXPR_CALC {$$ = ($1==$2);}

EXPR_CALC: VAL
|   TERM '+' VAL { $$ = $1 + $2;}
|   TERM '-' VAL { $$ = $1 - $2;}

TERM: VAL
|   TERM '*' VAL {$$ = $1 * $2;}
|   TERM '/' VAL {$$ = $1 / $2;}

VAL: MASK {$$=$1.mask.value;}
|   '~' VAL {$$=0; OPS* ops = new OPS(OPERAND_ASSIGN, MAX32, "="); totop.push_back(ops);}
|   '(' EXPR_CALC ')'
|   ID {$$=0;}

VAL_DEC: REG ID ';' {OPS* ops = new OPS(OPERAND_REG, 0, $2); totop.push_back(ops);printf("%s\n",$2);}
| WIRE '[' NUM ':' NUM ']' ID ';' {OPS* ops = new OPS(OPERAND_REG, 0, $4); totop.push_back(ops);}

INIT_BLOCK: INIT BEG INIT_VAL END ;

INIT_VAL: ID '=' VAL ';' {OPS* ops = new OPS(OPERAND_ASSIGN, MAX32, "="); totop.push_back(ops);}
| TIME_DEF
| INIT_VAL INIT_VAL

TIME_DEF: TIME ID '=' VAL ';' {OPS* ops = new OPS(OPERAND_ASSIGN, MAX32, "="); totop.push_back(ops) }

MODULE_INIT: MODULE ID '(' PARAMS ')' ';';

PARAMS: INPUT ID 
| OUTPUT ID
| INPUT REG '[' NUM ':' NUM ']' ID
| OUTPUT REG '[' NUM ':' NUM ']' ID
| PARAMS ',' PARAMS ;

MASK: BIT_MASK
| OCT_MASK
| DEC_MASK
| HEX_MASK ;

 /*** END EXAMPLE - Change the example grammar rules above ***/

%% /*** Additional Code ***/

void VerilogParser::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
