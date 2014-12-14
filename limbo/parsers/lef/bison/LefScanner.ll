/* $Id: scanner.ll 44 2008-10-23 09:03:19Z tb $ -*- mode: c++ -*- */
/** \file scanner.ll Define the example Flex lexical scanner */

%{ /*** C/C++ Declarations ***/

#include <string>

#include "LefScanner.h"

/* import the parser's token type into a local typedef */
typedef LefParser::Parser::token token;
typedef LefParser::Parser::token_type token_type;

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
%option prefix="LefParser"

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

"DEFINE" {return token::K_DEFINE;}
"DEFINEB" {return token::K_DEFINEB;}
"DEFINES" {return token::K_DEFINES;}
"MESSAGE" {return token::K_MESSAGE;}
"CREATEFILE" {return token::K_CREATEFILE;}
"OPENFILE" {return token::K_OPENFILE;}
"CLOSEFILE" {return token::K_CLOSEFILE;}
"WARNING" {return token::K_WARNING;}
"ERROR" {return token::K_ERROR;}
"FATALERROR" {return token::K_FATALERROR;}
"namescasesensitive" {return token::K_namescasesensitive;}
"off" {return token::K_off;}
"on" {return token::K_on;}
"ABOVE" {return token::K_ABOVE;}
"ABUT" {return token::K_ABUT;}
"ABUTMENT" {return token::K_ABUTMENT;}
"ACCURRENTDENSITY" {return token::K_ACCURRENTDENSITY;}
"ACTIVE" {return token::K_ACTIVE;}
"ADJACENTCUTS" {return token::K_ADJACENTCUTS;}
"ANALOG" {return token::K_ANALOG;}
"AND" {return token::K_AND;}
"ANTENNAAREAFACTOR" {return token::K_ANTENNAAREAFACTOR;}
"ANTENNAAREADIFFREDUCEPWL" {return token::K_ANTENNAAREADIFFREDUCEPWL;}
"ANTENNAAREAMINUSDIFF" {return token::K_ANTENNAAREAMINUSDIFF;}
"ANTENNAAREARATIO" {return token::K_ANTENNAAREARATIO;}
"ANTENNACELL" {return token::K_ANTENNACELL;}
"ANTENNACUMAREARATIO" {return token::K_ANTENNACUMAREARATIO;}
"ANTENNACUMDIFFAREARATIO" {return token::K_ANTENNACUMDIFFAREARATIO;}
"ANTENNACUMDIFFSIDEAREARATIO" {return token::K_ANTENNACUMDIFFSIDEAREARATIO;}
"ANTENNACUMROUTINGPLUSCUT" {return token::K_ANTENNACUMROUTINGPLUSCUT;}
"ANTENNACUMSIDEAREARATIO" {return token::K_ANTENNACUMSIDEAREARATIO;}
"ANTENNADIFFAREA" {return token::K_ANTENNADIFFAREA;}
"ANTENNADIFFAREARATIO" {return token::K_ANTENNADIFFAREARATIO;}
"ANTENNADIFFSIDEAREARATIO" {return token::K_ANTENNADIFFSIDEAREARATIO;}
"ANTENNAGATEAREA" {return token::K_ANTENNAGATEAREA;}
"ANTENNAGATEPLUSDIFF" {return token::K_ANTENNAGATEPLUSDIFF;}
"ANTENNAINOUTDIFFAREA" {return token::K_ANTENNAINOUTDIFFAREA;}
"ANTENNAINPUTGATEAREA" {return token::K_ANTENNAINPUTGATEAREA;}
"ANTENNALENGTHFACTOR" {return token::K_ANTENNALENGTHFACTOR;}
"ANTENNAMAXAREACAR" {return token::K_ANTENNAMAXAREACAR;}
"ANTENNAMAXCUTCAR" {return token::K_ANTENNAMAXCUTCAR;}
"ANTENNAMAXSIDEAREACAR" {return token::K_ANTENNAMAXSIDEAREACAR;}
"ANTENNAMETALAREA" {return token::K_ANTENNAMETALAREA;}
"ANTENNAMETALLENGTH" {return token::K_ANTENNAMETALLENGTH;}
"ANTENNAMODEL" {return token::K_ANTENNAMODEL;}
"ANTENNAOUTPUTDIFFAREA" {return token::K_ANTENNAOUTPUTDIFFAREA;}
"ANTENNAPARTIALCUTAREA" {return token::K_ANTENNAPARTIALCUTAREA;}
"ANTENNAPARTIALMETALAREA" {return token::K_ANTENNAPARTIALMETALAREA;}
"ANTENNAPARTIALMETALSIDEAREA" {return token::K_ANTENNAPARTIALMETALSIDEAREA;}
"ANTENNASIDEAREARATIO" {return token::K_ANTENNASIDEAREARATIO;}
"ANTENNASIZE" {return token::K_ANTENNASIZE;}
"ANTENNASIDEAREAFACTOR" {return token::K_ANTENNASIDEAREAFACTOR;}
"ANYEDGE" {return token::K_ANYEDGE;}
"AREA" {return token::K_AREA;}
"AREAIO" {return token::K_AREAIO;}
"ARRAY" {return token::K_ARRAY;}
"ARRAYCUTS" {return token::K_ARRAYCUTS;}
"ARRAYSPACING" {return token::K_ARRAYSPACING;}
"AVERAGE" {return token::K_AVERAGE;}
"BELOW" {return token::K_BELOW;}
"BEGINEXT" {return token::K_BEGINEXT;}
"BLACKBOX" {return token::K_BLACKBOX;}
"BLOCK" {return token::K_BLOCK;}
"BOTTOMLEFT" {return token::K_BOTTOMLEFT;}
"BOTTOMRIGHT" {return token::K_BOTTOMRIGHT;}
"BUMP" {return token::K_BUMP;}
"BUSBITCHARS" {return token::K_BUSBITCHARS;}
"BUFFER" {return token::K_BUFFER;}
"BY" {return token::K_BY;}
"CANNOTOCCUPY" {return token::K_CANNOTOCCUPY;}
"CANPLACE" {return token::K_CANPLACE;}
"CAPACITANCE" {return token::K_CAPACITANCE;}
"CAPMULTIPLIER" {return token::K_CAPMULTIPLIER;}
"CENTERTOCENTER" {return token::K_CENTERTOCENTER;}
"CLASS" {return token::K_CLASS;}
"CLEARANCEMEASURE" {return token::K_CLEARANCEMEASURE;}
"CLOCK" {return token::K_CLOCK;}
"CLOCKTYPE" {return token::K_CLOCKTYPE;}
"COLUMNMAJOR" {return token::K_COLUMNMAJOR;}
"CURRENTDEN" {return token::K_CURRENTDEN;}
"COMPONENTPIN" {return token::K_COMPONENTPIN;}
"CORE" {return token::K_CORE;}
"CORNER" {return token::K_CORNER;}
"CORRECTIONFACTOR" {return token::K_CORRECTIONFACTOR;}
"CORRECTIONTABLE" {return token::K_CORRECTIONTABLE;}
"COVER" {return token::K_COVER;}
"CPERSQDIST" {return token::K_CPERSQDIST;}
"CURRENT" {return token::K_CURRENT;}
"CURRENTSOURCE" {return token::K_CURRENTSOURCE;}
"CUT" {return token::K_CUT;}
"CUTAREA" {return token::K_CUTAREA;}
"CUTSIZE" {return token::K_CUTSIZE;}
"CUTSPACING" {return token::K_CUTSPACING;}
"DATA" {return token::K_DATA;}
"DATABASE" {return token::K_DATABASE;}
"DCCURRENTDENSITY" {return token::K_DCCURRENTDENSITY;}
"DEFAULT" {return token::K_DEFAULT;}
"DEFAULTCAP" {return token::K_DEFAULTCAP;}
"DELAY" {return token::K_DELAY;}
"DENSITY" {return token::K_DENSITY;}
"DENSITYCHECKSTEP" {return token::K_DENSITYCHECKSTEP;}
"DENSITYCHECKWINDOW" {return token::K_DENSITYCHECKWINDOW;}
"DESIGNRULEWIDTH" {return token::K_DESIGNRULEWIDTH;}
"DIAG45" {return token::K_DIAG45;}
"DIAG135" {return token::K_DIAG135;}
"DIAGMINEDGELENGTH" {return token::K_DIAGMINEDGELENGTH;}
"DIAGSPACING" {return token::K_DIAGSPACING;}
"DIAGPITCH" {return token::K_DIAGPITCH;}
"DIAGWIDTH" {return token::K_DIAGWIDTH;}
"DIELECTRIC" {return token::K_DIELECTRIC;}
"DIFFUSEONLY" {return token::K_DIFFUSEONLY;}
"DIRECTION" {return token::K_DIRECTION;}
"DIVIDERCHAR" {return token::K_DIVIDERCHAR;}
"DO" {return token::K_DO;}
"E" {return token::K_E;}
"EDGECAPACITANCE" {return token::K_EDGECAPACITANCE;}
"EDGERATE" {return token::K_EDGERATE;}
"EDGERATESCALEFACTOR" {return token::K_EDGERATESCALEFACTOR;}
"EDGERATETHRESHOLD1" {return token::K_EDGERATETHRESHOLD1;}
"EDGERATETHRESHOLD2" {return token::K_EDGERATETHRESHOLD2;}
"EEQ" {return token::K_EEQ;}
"ELSE" {return token::K_ELSE;}
"ENCLOSURE" {return token::K_ENCLOSURE;}
"END" {return token::K_END;}
"ENDEXT" {return token::K_ENDEXT;}
"ENDCAP" {return token::K_ENDCAP;}
"ENDOFLINE" {return token::K_ENDOFLINE;}
"ENDOFNOTCHWIDTH" {return token::K_ENDOFNOTCHWIDTH;}
"EUCLIDEAN" {return token::K_EUCLIDEAN;}
"EXCEPTEXTRACUT" {return token::K_EXCEPTEXTRACUT;}
"EXCEPTSAMEPGNET" {return token::K_EXCEPTSAMEPGNET;}
"EXCEPTPGNET" {return token::K_EXCEPTPGNET;}
"EXTENSION" {return token::K_EXTENSION;}
"FALL" {return token::K_FALL;}
"FALLCS" {return token::K_FALLCS;}
"FALLRS" {return token::K_FALLRS;}
"FALLSATCUR" {return token::K_FALLSATCUR;}
"FALLSATT1" {return token::K_FALLSATT1;}
"FALLSLEWLIMIT" {return token::K_FALLSLEWLIMIT;}
"FALLT0" {return token::K_FALLT0;}
"FALLTHRESH" {return token::K_FALLTHRESH;}
"FALLVOLTAGETHRESHOLD" {return token::K_FALLVOLTAGETHRESHOLD;}
"FALSE" {return token::K_FALSE;}
"FE" {return token::K_FE;}
"FEEDTHRU" {return token::K_FEEDTHRU;}
"FILLACTIVESPACING" {return token::K_FILLACTIVESPACING;}
"FIXED" {return token::K_FIXED;}
"FLIP" {return token::K_FLIP;}
"FLOORPLAN" {return token::K_FLOORPLAN;}
"FN" {return token::K_FN;}
"FOREIGN" {return token::K_FOREIGN;}
"FREQUENCY" {return token::K_FREQUENCY;}
"FROMABOVE" {return token::K_FROMABOVE;}
"FROMBELOW" {return token::K_FROMBELOW;}
"FROMPIN" {return token::K_FROMPIN;}
"FUNCTION" {return token::K_FUNCTION;}
"FS" {return token::K_FS;}
"FW" {return token::K_FW;}
"GCELLGRID" {return token::K_GCELLGRID;}
"GENERATE" {return token::K_GENERATE;}
"GENERATED" {return token::K_GENERATED;}
"GENERATOR" {return token::K_GENERATOR;}
"GROUND" {return token::K_GROUND;}
"GROUNDSENSITIVITY" {return token::K_GROUNDSENSITIVITY;}
"HARDSPACING" {return token::K_HARDSPACING;}
"HEIGHT" {return token::K_HEIGHT;}
"HISTORY" {return token::K_HISTORY;}
"HOLD" {return token::K_HOLD;}
"HORIZONTAL" {return token::K_HORIZONTAL;}
"IF" {return token::K_IF;}
"IMPLANT" {return token::K_IMPLANT;}
"INFLUENCE" {return token::K_INFLUENCE;}
"INOUT" {return token::K_INOUT;}
"INOUTPINANTENNASIZE" {return token::K_INOUTPINANTENNASIZE;}
"INPUT" {return token::K_INPUT;}
"INPUTPINANTENNASIZE" {return token::K_INPUTPINANTENNASIZE;}
"INPUTNOISEMARGIN" {return token::K_INPUTNOISEMARGIN;}
"INSIDECORNER" {return token::K_INSIDECORNER;}
"INTEGER" {return token::K_INTEGER;}
"INTRINSIC" {return token::K_INTRINSIC;}
"INVERT" {return token::K_INVERT;}
"INVERTER" {return token::K_INVERTER;}
"IRDROP" {return token::K_IRDROP;}
"ITERATE" {return token::K_ITERATE;}
"IV_TABLES" {return token::K_IV_TABLES;}
"LAYER" {return token::K_LAYER;}
"LAYERS" {return token::K_LAYERS;}
"LEAKAGE" {return token::K_LEAKAGE;}
"LENGTH" {return token::K_LENGTH;}
"LENGTHSUM" {return token::K_LENGTHSUM;}
"LENGTHTHRESHOLD" {return token::K_LENGTHTHRESHOLD;}
"LEQ" {return token::K_LEQ;}
"LIBRARY" {return token::K_LIBRARY;}
"LONGARRAY" {return token::K_LONGARRAY;}
"MACRO" {return token::K_MACRO;}
"MANUFACTURINGGRID" {return token::K_MANUFACTURINGGRID;}
"MASTERSLICE" {return token::K_MASTERSLICE;}
"MATCH" {return token::K_MATCH;}
"MAXADJACENTSLOTSPACING" {return token::K_MAXADJACENTSLOTSPACING;}
"MAXCOAXIALSLOTSPACING" {return token::K_MAXCOAXIALSLOTSPACING;}
"MAXDELAY" {return token::K_MAXDELAY;}
"MAXEDGES" {return token::K_MAXEDGES;}
"MAXEDGESLOTSPACING" {return token::K_MAXEDGESLOTSPACING;}
"MAXLOAD" {return token::K_MAXLOAD;}
"MAXIMUMDENSITY" {return token::K_MAXIMUMDENSITY;}
"MAXVIASTACK" {return token::K_MAXVIASTACK;}
"MAXWIDTH" {return token::K_MAXWIDTH;}
"MAXXY" {return token::K_MAXXY;}
"MEGAHERTZ" {return token::K_MEGAHERTZ;}
"METALOVERHANG" {return token::K_METALOVERHANG;}
"MICRONS" {return token::K_MICRONS;}
"MILLIAMPS" {return token::K_MILLIAMPS;}
"MILLIWATTS" {return token::K_MILLIWATTS;}
"MINCUTS" {return token::K_MINCUTS;}
"MINENCLOSEDAREA" {return token::K_MINENCLOSEDAREA;}
"MINFEATURE" {return token::K_MINFEATURE;}
"MINIMUMCUT" {return token::K_MINIMUMCUT;}
"MINIMUMDENSITY" {return token::K_MINIMUMDENSITY;}
"MINPINS" {return token::K_MINPINS;}
"MINSIZE" {return token::K_MINSIZE;}
"MINSTEP" {return token::K_MINSTEP;}
"MINWIDTH" {return token::K_MINWIDTH;}
"MPWH" {return token::K_MPWH;}
"MPWL" {return token::K_MPWL;}
"MUSTJOIN" {return token::K_MUSTJOIN;}
"MX" {return token::K_MX;}
"MY" {return token::K_MY;}
"MXR90" {return token::K_MXR90;}
"MYR90" {return token::K_MYR90;}
"N" {return token::K_N;}
"NAMEMAPSTRING" {return token::K_NAMEMAPSTRING;}
"NAMESCASESENSITIVE" {return token::K_NAMESCASESENSITIVE;}
"NANOSECONDS" {return token::K_NANOSECONDS;}
"NEGEDGE" {return token::K_NEGEDGE;}
"NETEXPR" {return token::K_NETEXPR;}
"NETS" {return token::K_NETS;}
"NEW" {return token::K_NEW;}
"NONDEFAULTRULE" {return token::K_NONDEFAULTRULE;}
"NONE" {return token::K_NONE;}
"NONINVERT" {return token::K_NONINVERT;}
"NONUNATE" {return token::K_NONUNATE;}
"NOISETABLE" {return token::K_NOISETABLE;}
"NOTCHLENGTH" {return token::K_NOTCHLENGTH;}
"NOTCHSPACING" {return token::K_NOTCHSPACING;}
"NOWIREEXTENSIONATPIN" {return token::K_NOWIREEXTENSIONATPIN;}
"OBS" {return token::K_OBS;}
"OFF" {return token::K_OFF;}
"OFFSET" {return token::K_OFFSET;}
"OHMS" {return token::K_OHMS;}
"ON" {return token::K_ON;}
"OR" {return token::K_OR;}
"ORIENT" {return token::K_ORIENT;}
"ORIENTATION" {return token::K_ORIENTATION;}
"ORIGIN" {return token::K_ORIGIN;}
"ORTHOGONAL" {return token::K_ORTHOGONAL;}
"OUTPUT" {return token::K_OUTPUT;}
"OUTPUTPINANTENNASIZE" {return token::K_OUTPUTPINANTENNASIZE;}
"OUTPUTNOISEMARGIN" {return token::K_OUTPUTNOISEMARGIN;}
"OUTPUTRESISTANCE" {return token::K_OUTPUTRESISTANCE;}
"OUTSIDECORNER" {return token::K_OUTSIDECORNER;}
"OVERHANG" {return token::K_OVERHANG;}
"OVERLAP" {return token::K_OVERLAP;}
"OVERLAPS" {return token::K_OVERLAPS;}
"OXIDE1" {return token::K_OXIDE1;}
"OXIDE2" {return token::K_OXIDE2;}
"OXIDE3" {return token::K_OXIDE3;}
"OXIDE4" {return token::K_OXIDE4;}
"PAD" {return token::K_PAD;}
"PARALLELEDGE" {return token::K_PARALLELEDGE;}
"PARALLELOVERLAP" {return token::K_PARALLELOVERLAP;}
"PARALLELRUNLENGTH" {return token::K_PARALLELRUNLENGTH;}
"PATH" {return token::K_PATH;}
"PATTERN" {return token::K_PATTERN;}
"PEAK" {return token::K_PEAK;}
"PERIOD" {return token::K_PERIOD;}
"PGONLY" {return token::K_PGONLY;}
"PICOFARADS" {return token::K_PICOFARADS;}
"PIN" {return token::K_PIN;}
"PITCH" {return token::K_PITCH;}
"PLACED" {return token::K_PLACED;}
"POLYGON" {return token::K_POLYGON;}
"PORT" {return token::K_PORT;}
"POSEDGE" {return token::K_POSEDGE;}
"POST" {return token::K_POST;}
"POWER" {return token::K_POWER;}
"PRE" {return token::K_PRE;}
"PREFERENCLOSURE" {return token::K_PREFERENCLOSURE;}
"PRL" {return token::K_PRL;}
"PROPERTY" {return token::K_PROPERTY;}
"PROPERTYDEFINITIONS" {return token::K_PROPERTYDEFINITIONS;}
"PROTRUSIONWIDTH" {return token::K_PROTRUSIONWIDTH;}
"PULLDOWNRES" {return token::K_PULLDOWNRES;}
"PWL" {return token::K_PWL;}
"R0" {return token::K_R0;}
"R90" {return token::K_R90;}
"R180" {return token::K_R180;}
"R270" {return token::K_R270;}
"RANGE" {return token::K_RANGE;}
"REAL" {return token::K_REAL;}
"RECOVERY" {return token::K_RECOVERY;}
"RECT" {return token::K_RECT;}
"RESISTANCE" {return token::K_RESISTANCE;}
"RESISTIVE" {return token::K_RESISTIVE;}
"RING" {return token::K_RING;}
"RISE" {return token::K_RISE;}
"RISECS" {return token::K_RISECS;}
"RISERS" {return token::K_RISERS;}
"RISESATCUR" {return token::K_RISESATCUR;}
"RISESATT1" {return token::K_RISESATT1;}
"RISESLEWLIMIT" {return token::K_RISESLEWLIMIT;}
"RISET0" {return token::K_RISET0;}
"RISETHRESH" {return token::K_RISETHRESH;}
"RISEVOLTAGETHRESHOLD" {return token::K_RISEVOLTAGETHRESHOLD;}
"RMS" {return token::K_RMS;}
"ROUTING" {return token::K_ROUTING;}
"ROWABUTSPACING" {return token::K_ROWABUTSPACING;}
"ROWCOL" {return token::K_ROWCOL;}
"ROWMAJOR" {return token::K_ROWMAJOR;}
"ROWMINSPACING" {return token::K_ROWMINSPACING;}
"ROWPATTERN" {return token::K_ROWPATTERN;}
"RPERSQ" {return token::K_RPERSQ;}
"S" {return token::K_S;}
"SAMENET" {return token::K_SAMENET;}
"SCANUSE" {return token::K_SCANUSE;}
"SDFCOND" {return token::K_SDFCOND;}
"SDFCONDEND" {return token::K_SDFCONDEND;}
"SDFCONDSTART" {return token::K_SDFCONDSTART;}
"SETUP" {return token::K_SETUP;}
"SHAPE" {return token::K_SHAPE;}
"SHRINKAGE" {return token::K_SHRINKAGE;}
"SIGNAL" {return token::K_SIGNAL;}
"SITE" {return token::K_SITE;}
"SIZE" {return token::K_SIZE;}
"SKEW" {return token::K_SKEW;}
"SLOTLENGTH" {return token::K_SLOTLENGTH;}
"SLOTWIDTH" {return token::K_SLOTWIDTH;}
"SLOTWIRELENGTH" {return token::K_SLOTWIRELENGTH;}
"SLOTWIREWIDTH" {return token::K_SLOTWIREWIDTH;}
"SPLITWIREWIDTH" {return token::K_SPLITWIREWIDTH;}
"SOFT" {return token::K_SOFT;}
"SOURCE" {return token::K_SOURCE;}
"SPACER" {return token::K_SPACER;}
"SPACING" {return token::K_SPACING;}
"SPACINGTABLE" {return token::K_SPACINGTABLE;}
"SPECIALNETS" {return token::K_SPECIALNETS;}
"STABLE" {return token::K_STABLE;}
"STACK" {return token::K_STACK;}
"START" {return token::K_START;}
"STEP" {return token::K_STEP;}
"STOP" {return token::K_STOP;}
"STRING" {return token::K_STRING;}
"STRUCTURE" {return token::K_STRUCTURE;}
"SUPPLYSENSITIVITY" {return token::K_SUPPLYSENSITIVITY;}
"SYMMETRY" {return token::K_SYMMETRY;}
"TABLE" {return token::K_TABLE;}
"TABLEAXIS" {return token::K_TABLEAXIS;}
"TABLEDIMENSION" {return token::K_TABLEDIMENSION;}
"TABLEENTRIES" {return token::K_TABLEENTRIES;}
"TAPERRULE" {return token::K_TAPERRULE;}
"THEN" {return token::K_THEN;}
"THICKNESS" {return token::K_THICKNESS;}
"TIEHIGH" {return token::K_TIEHIGH;}
"TIELOW" {return token::K_TIELOW;}
"TIEOFFR" {return token::K_TIEOFFR;}
"TIME" {return token::K_TIME;}
"TIMING" {return token::K_TIMING;}
"TO" {return token::K_TO;}
"TOPIN" {return token::K_TOPIN;}
"TOPLEFT" {return token::K_TOPLEFT;}
"TOPOFSTACKONLY" {return token::K_TOPOFSTACKONLY;}
"TOPRIGHT" {return token::K_TOPRIGHT;}
"TRACKS" {return token::K_TRACKS;}
"TRANSITIONTIME" {return token::K_TRANSITIONTIME;}
"TRISTATE" {return token::K_TRISTATE;}
"TRUE" {return token::K_TRUE;}
"TWOEDGES" {return token::K_TWOEDGES;}
"TWOWIDTHS" {return token::K_TWOWIDTHS;}
"TYPE" {return token::K_TYPE;}
"UNATENESS" {return token::K_UNATENESS;}
"UNITS" {return token::K_UNITS;}
"UNIVERSALNOISEMARGIN" {return token::K_UNIVERSALNOISEMARGIN;}
"USE" {return token::K_USE;}
"USELENGTHTHRESHOLD" {return token::K_USELENGTHTHRESHOLD;}
"USEMINSPACING" {return token::K_USEMINSPACING;}
"USER" {return token::K_USER;}
"USEVIA" {return token::K_USEVIA;}
"USEVIARULE" {return token::K_USEVIARULE;}
"VARIABLE" {return token::K_VARIABLE;}
"VERSION" {return token::K_VERSION;}
"VERTICAL" {return token::K_VERTICAL;}
"VHI" {return token::K_VHI;}
"VIA" {return token::K_VIA;}
"VIARULE" {return token::K_VIARULE;}
"VICTIMLENGTH" {return token::K_VICTIMLENGTH;}
"VICTIMNOISE" {return token::K_VICTIMNOISE;}
"VIRTUAL" {return token::K_VIRTUAL;}
"VLO" {return token::K_VLO;}
"VOLTAGE" {return token::K_VOLTAGE;}
"VOLTS" {return token::K_VOLTS;}
"W" {return token::K_W;}
"WELLTAP" {return token::K_WELLTAP;}
"WIDTH" {return token::K_WIDTH;}
"WITHIN" {return token::K_WITHIN;}
"WIRECAP" {return token::K_WIRECAP;}
"WIREEXTENSION" {return token::K_WIREEXTENSION;}
"X" {return token::K_X;}
"Y" {return token::K_Y;}

[\+\-]?[0-9]+ {
    yylval->integerVal = atoi(yytext);
    return token::INTEGER;
}

[\+\-]?[0-9]+"."[0-9]* {
    yylval->doubleVal = atof(yytext);
    return token::DOUBLE;
}

[0-9]*\'[A-Za-z][0-9]+ {
    yylval->stringVal = new std::string(yytext, yyleng);
    return token::BINARY;
}

[A-Za-z][A-Za-z0-9_,.\-\[\]]* {
    yylval->stringVal = new std::string(yytext, yyleng);
    return token::STRING;
}

\"([^"])*\" {
    yylval->qstringVal = new std::string(yytext+1, yyleng-2);
    return token::QSTRING;
}

 /* gobble up comments */
"#"([^\n])*\n {
    yylloc->step();
}

 /* gobble up white-spaces */
[ \t\r]+ {
    yylloc->step();
}

 /* gobble up end-of-lines */
\n {
    yylloc->lines(yyleng); yylloc->step();
    /* return token::EOL; */
}

 /* pass all other characters up to bison */
. {
    return static_cast<token_type>(*yytext);
}

 /*** END EXAMPLE - Change the example lexer rules above ***/

%% /*** Additional Code ***/

namespace LefParser {

Scanner::Scanner(std::istream* in,
		 std::ostream* out)
    : LefParserFlexLexer(in, out)
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

int LefParserFlexLexer::yylex()
{
    std::cerr << "in LefParserFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int LefParserFlexLexer::yywrap()
{
    return 1;
}
