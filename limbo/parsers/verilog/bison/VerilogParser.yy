/* $Id: parser.yy 48 2009-09-05 08:07:10Z tb $ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

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
    std::string* stringVal;
    struct {
        long value;
        long bits;
    } mask;
    struct Range* rangeVal;
/*    struct Range {
        int low;
        int high;
    } rangeVal;
    */
}

%token ALWAYS 
%token EQUAL
%token POSEDGE
%token NEGEDGE
%token OR
%token BEG
%token END 0 "end of file"
%token AND
%token IF
%token ELSE
%token INIT
%token AT
%token NAME
%token NUM
%token MODULE
%token ENDMODULE
%token INPUT
%token OUTPUT
%token INOUT
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

%type<stringVal> NAME
%type<mask> BIT_MASK OCT_MASK DEC_MASK HEX_MASK
%type<int> NUM 
%type<rangeVal> range

%destructor {delete $$;} NAME
%destructor {delete $$;} range

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

range: '[' NUM ':' NUM ']' {$$ = new Range (1, 2);}

param1: NAME {delete $1;}
      | NAME range {delete $1; delete $2;} 
      ;

/* wire_pin_cbk will be called before module_instance_cbk */
param2: '.' NAME '(' NAME ')' {driver.wire_pin_cbk(*$4, *$2); delete $2; delete $4;}
      | '.' NAME '(' NAME range ')' {driver.wire_pin_cbk(*$4, *$2, *$5); delete $2; delete $4; delete $5;}
      ;

param3: INPUT NAME {driver.pin_declare_cbk(*$2, kINPUT); delete $2;}
      | INPUT REG NAME {driver.pin_declare_cbk(*$3, kINPUT|kREG); delete $3;}
      | INPUT range NAME {driver.pin_declare_cbk(*$3, kINPUT, *$2); delete $2; delete $3;} 
      | INPUT REG range NAME {driver.pin_declare_cbk(*$4, kINPUT|kREG, *$3); delete $3; delete $4;}
      | OUTPUT NAME {driver.pin_declare_cbk(*$2, kOUTPUT); delete $2;}
      | OUTPUT REG NAME {driver.pin_declare_cbk(*$3, kOUTPUT|kREG); delete $3;}
      | OUTPUT range NAME {driver.pin_declare_cbk(*$3, kOUTPUT, *$2); delete $2; delete $3;}
      | OUTPUT REG range NAME {driver.pin_declare_cbk(*$4, kOUTPUT|kREG, *$3); delete $3; delete $4;}
      | INOUT NAME {driver.pin_declare_cbk(*$2, kINPUT|kOUTPUT); delete $2;}
      | INOUT REG NAME {driver.pin_declare_cbk(*$3, kINPUT|kOUTPUT|kREG); delete $3;}
      | INOUT range NAME {driver.pin_declare_cbk(*$3, kINPUT|kOUTPUT, *$2); delete $2; delete $3;}
      | INOUT REG range NAME {driver.pin_declare_cbk(*$4, kINPUT|kOUTPUT|kREG, *$3); delete $3; delete $4;}
      ;

param4: REG NAME {delete $2;}
      | REG range NAME {delete $2; delete $3;}
      ;

param5: WIRE NAME {driver.wire_declare_cbk(*$2); delete $2;}
      | WIRE range NAME {driver.wire_declare_cbk(*$3, *$2); delete $2; delete $3;}
      ;


module_param: param1 
            | param3
      ;

module_params: /* empty */
             | module_param 
             | module_params ',' module_param 
             ;

module_declare: MODULE NAME '(' module_params ')' ';' {delete $2;}
              ;

variable_declare: param3 ';'
                | param4 ';'
                | param5 ';'
                ;

/* do not support param1 yet */
instance_params: /* empty */
               | param2 
               | instance_params ',' param2 
               ;

module_instance: NAME NAME '(' instance_params ')' ';' {driver.module_instance_cbk(*$1, *$2); delete $1; delete $2;}
               ;

module_content: /* empty */
              | module_content variable_declare
              | module_content module_instance 
              ;


single_module: module_declare module_content ENDMODULE 
             ;

start : /* empty */
     | start single_module
     ;

 /*** END EXAMPLE - Change the example grammar rules above ***/

%% /*** Additional Code ***/

void VerilogParser::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
