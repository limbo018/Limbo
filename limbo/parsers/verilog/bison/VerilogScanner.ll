/* $Id: scanner.ll 44 2008-10-23 09:03:19Z tb $ -*- mode: c++ -*- */
/** \file scanner.ll Define the example Flex lexical scanner */

%{ /*** C/C++ Declarations ***/

#include <string>

#include "VerilogScanner.h"

/* import the parser's token type into a local typedef */
typedef VerilogParser::Parser::token token;
typedef VerilogParser::Parser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "ExampleFlexLexer" */
%option prefix="DefParser"

/* the manual says "somewhat more optimized" */
%option batch

/* enable scanner to generate debug output. disable this for release
 * versions. */
%option debug

/* no support for include files is planned */
%option yywrap nounput 

/* enables the use of start condition stacks */
%option stack

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

%% /*** Regular Expressions Part ***/

 /* code to place at the beginning of yylex() */
%{
    // reset location
    yylloc->step();
%}

 /*** BEGIN EXAMPLE - Change the example lexer rules below ***/

[/][/].*\n      ; // comment
[ \t\r\n]       ; // whitespace
[`].+\n         ;

if              return IF;
else            return ELSE;
always          return ALWAYS;
initial         return INIT;
begin           return BEG;
end             return END;
posedge         return POSEDGE;
negedge         return NEGEDGE;
@               return AT;
module          return MODULE;
input           return INPUT;
output          return OUTPUT;
reg             return REG;
wire            return WIRE;
integer         return INTEGER;
[0-1]+[']b[0-9]+    return BIT_MASK;
[0-7]+[']o[0-9]+    return OCT_MASK;
[0-9]+[']d[0-9]+    return DEC_MASK;
[0-9a-fA-F]+[']h[0-9]+  return HEX_MASK;

[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = yytext;
                        return ID;}
\#[0-9]+        {
                    char* end;
                    char* temp;
                    yylval.mask.value = strtol(yytext+sizeof(char),&end,16); 
                    yylval.mask.bits  = strtol(end+2*sizeof(char),&temp,10);
                    if (*(end+sizeof(char))!='h')
                    {
                        if (*(end+sizeof(char))=='b')
                        {
                            yylval.mask.value = strtol(yytext+sizeof(char),&end,2); 
                            yylval.mask.bits  = strtol(end+2*sizeof(char),&temp,10);
                        }else if (*(end+sizeof(char))=='o')
                        {
                            yylval.mask.value = strtol(yytext+sizeof(char),&end,8);
                            yylval.mask.bits  = strtol(end+2*sizeof(char),&temp,10);
                        }else if (*(end+sizeof(char))=='d')
                        {
                            yylval.mask.value = strtol(yytext+sizeof(char),&end,10);
                            yylval.mask.bits  = strtol(end+2*sizeof(char),&temp,10);
                        }
                    }
                    return TIME;
                }
[0-9]+          { 
                    yylval.mask.value = atoi(yytext);
                    return NUM;
                }
\<=             return EQUAL;
[:\[\]-{};()=<>+*/!,\~]    { return *yytext; }
                yyerror("Invalid character");

 /* pass all other characters up to bison */
. {
    return static_cast<token_type>(*yytext);
}

 /*** END EXAMPLE - Change the example lexer rules above ***/

%% /*** Additional Code ***/

namespace VerilogParser {

Scanner::Scanner(std::istream* in,
		 std::ostream* out)
    : VerilogParserFlexLexer(in, out)
{
}

Scanner::~Scanner()
{
}

void Scanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

}

/* This implementation of ExampleFlexLexer::yylex() is required to fill the
 * vtable of the class ExampleFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int VerilogParserFlexLexer::yylex()
{
    std::cerr << "in VerilogParserFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int VerilogParserFlexLexer::yywrap()
{
    return 1;
}
