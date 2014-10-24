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
%name-prefix="DefParser"

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
    int  			integerVal;
    double 			doubleVal;
    std::string*		stringVal;
	std::string*		quoteVal;
/*    class CalcNode*		calcnode; */
}

%token			END	     0	"end of file"
/* %token			EOL		"end of line" */
%token <integerVal> 	INTEGER		"integer"
%token <doubleVal> 	DOUBLE		"double"
%token <stringVal> 	STRING		"string"
%token <quoteVal> 	QUOTE		"quoted chars"
%token			KWD_VERSION		"VERSION"
%token			KWD_DIVIDERCHAR	"DIVIDERCHAR"
%token			KWD_BUSBITCHARS	"BUSBITCHARS"
%token			KWD_DESIGN		"DESIGN"
%token			KWD_UNITS		"UNITS"
%token			KWD_DISTANCE	"DISTANCE"
%token			KWD_MICRONS		"MICRONS"
%token			KWD_DIEAREA		"DIEAREA"
%token			KWD_ROW			"ROW"
%token			KWD_DO			"DO"
%token			KWD_BY			"BY"
%token			KWD_COMPONENTS	"COMPONENTS"
%token			KWD_PINS		"PINS"
%token			KWD_NETS		"NETS"
%token			KWD_NET			"NET"
%token			KWD_STEP		"STEP"
%token			KWD_END			"END"
%token			KWD_DIRECTION	"DIRECTION"
%token			KWD_LAYER		"LAYER"

/*
%type <integerVal>	block_other block_row block_comp block_pin block_net 
%type <integerVal>	expression 
*/

%destructor { delete $$; } STRING QUOTE
/*
%destructor { delete $$; } constant variable
%destructor { delete $$; } atomexpr powexpr unaryexpr mulexpr addexpr expr
*/

 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include "DefDriver.h"
#include "DefScanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN EXAMPLE - Change the example grammar rules below ***/

block_other : KWD_VERSION DOUBLE ';' {
				driver.version_cbk($2);
			}
			| KWD_DIVIDERCHAR QUOTE ';' {
				driver.dividerchar_cbk(*$2);
			}
			| KWD_BUSBITCHARS QUOTE ';' {
				driver.busbitchars_cbk(*$2);
			}
			
 /*** grammar for rows ***/
single_row : KWD_ROW STRING STRING INTEGER INTEGER STRING KWD_DO INTEGER KWD_BY INTEGER KWD_STEP INTEGER INTEGER ';' {
				driver.row_cbk(*$2, *$3, $4, $5, *$6, $8, $10, $12, $13);
			 }

block_rows : single_row 
		  | block_rows single_row 
		  ;

 /*** grammar for components ***/
begin_components : KWD_COMPONENTS INTEGER ';' {
					driver.component_cbk_size($2);
				 }

end_components : KWD_END KWD_COMPONENTS 
			   ;

single_component : '-' STRING STRING '+' STRING '(' INTEGER INTEGER ')' STRING ';' {
				driver.component_cbk(*$2, *$3, *$5, $7, $8, *$10);
			}
			| '-' STRING STRING '+' STRING ';' {
				driver.component_cbk(*$2, *$3, *$5);
			}

multiple_components : single_component 
				  | multiple_components single_component
			  ;

block_components : begin_components 
				 multiple_components 
				 end_components
				 | begin_components
				 end_components
				 ;
				 
 /*** grammar for pins ***/
begin_pins : KWD_PINS INTEGER ';' {
					driver.pin_cbk_size($2);
				}

end_pins : KWD_END KWD_PINS
		 ;

single_pin : '-' STRING '+' KWD_NET STRING 
		   '+' KWD_DIRECTION STRING 
		   '+' STRING '(' INTEGER INTEGER ')' STRING 
		   '+' KWD_LAYER STRING '(' INTEGER INTEGER ')' '(' INTEGER INTEGER ')' ';' {
				driver.pin_cbk(*$2, *$5, *$8, *$10, $12, $13, *$15, *$18, $20, $21, $24, $25);
		   }

multiple_pins : single_pin 
			  | multiple_pins single_pin 
			  ;

block_pins : begin_pins 
		   multiple_pins 
		   end_pins
		   | begin_pins 
		   end_pins 
		   ;

 /*** grammar for nets ***/
begin_nets : KWD_NETS INTEGER ';' {
					driver.net_cbk_size($2);
				}

end_nets : KWD_END KWD_NETS
		 ;

node_pin_pair : '(' STRING STRING ')' {
		   /** be careful, this callback will be invoked before net_cbk_name **/
				driver.net_cbk_pin(*$2, *$3); 
			  }

node_pin_pairs : node_pin_pair 
			   | node_pin_pairs node_pin_pair
			   ;

single_net : '-' STRING node_pin_pairs ';' {
				driver.net_cbk_name(*$2);
		   }

multiple_nets : single_net 
			  | multiple_nets single_net
			  ;

block_nets : begin_nets
		   multiple_nets 
		   end_nets
		   | begin_nets 
		   end_nets 
		   ;

 /*** grammar for top design ***/

begin_design : KWD_DESIGN STRING ';' {
				driver.design_cbk(*$2);
			 }

end_design : KWD_END KWD_DESIGN
		   ;

block_unit : KWD_UNITS KWD_DISTANCE KWD_MICRONS INTEGER ';' {
				driver.unit_cbk($4);
		   }

block_diearea : KWD_DIEAREA '(' INTEGER INTEGER ')' '(' INTEGER INTEGER ')' ';' {
				driver.diearea_cbk($3, $4, $7, $8);
			  }

block_design : begin_design 
			 block_unit
			 block_diearea
			 block_rows 
			 block_components
			 block_pins
			 block_nets 
			 end_design 
			 ;

 /*** grammar for top file ***/
start : 
	  | start block_other
	  | start block_design
	  ;

 /*** END EXAMPLE - Change the example grammar rules above ***/

%% /*** Additional Code ***/

void DefParser::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
