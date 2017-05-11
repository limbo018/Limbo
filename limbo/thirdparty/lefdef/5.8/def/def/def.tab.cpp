/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         defyyparse
#define yylex           defyylex
#define yyerror         defyyerror
#define yylval          defyylval
#define yychar          defyychar
#define yydebug         defyydebug
#define yynerrs         defyynerrs


/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 58 "def.y"

#include <stdlib.h>
#include <string.h>
#include "defrReader.hpp"
#include "defiUser.hpp"
#include "defrCallBacks.hpp"
#include "lex.h"

#define DEF_MAX_INT 2147483647
#define YYDEBUG 1     // this is temp fix for pcr 755132 
// TX_DIR:TRANSLATION ON


#include "defrData.hpp"
#include "defrSettings.hpp"
#include "defrCallBacks.hpp"

BEGIN_LEFDEF_PARSER_NAMESPACE

// Macro to describe how we handle a callback.
// If the function was set then call it.
// If the function returns non zero then there was an error
// so call the error routine and exit.
//
#define CALLBACK(func, typ, data) \
    if (!defData->errors) {\
      if (func) { \
        if ((defData->defRetVal = (*func)(typ, data, defData->session->UserData)) == PARSE_OK) { \
        } else if (defData->defRetVal == STOP_PARSE) { \
          return defData->defRetVal; \
        } else { \
          defData->defError(6010, "An error has been reported in callback."); \
          return defData->defRetVal; \
        } \
      } \
    }

#define CHKERR() \
    if (defData->checkErrors()) { \
      return 1; \
    }

#define CHKPROPTYPE(propType, propName, name) \
    if (propType == 'N') { \
       defData->warningMsg = (char*)malloc(strlen(propName)+strlen(name)+40); \
       sprintf(defData->warningMsg, "The PropName %s is not defined for %s.", \
               propName, name); \
       defData->defWarning(7010, defData->warningMsg); \
       free(defData->warningMsg); \
    }

int yylex(YYSTYPE *pYylval, defrData *defData)
{
    return defData->defyylex(pYylval);
}


void yyerror(defrData *defData, const char *s)
{
    return defData->defyyerror(s);
}




#define FIXED 1
#define COVER 2
#define PLACED 3
#define UNPLACED 4


/* Line 268 of yacc.c  */
#line 151 "def.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     QSTRING = 258,
     T_STRING = 259,
     SITE_PATTERN = 260,
     NUMBER = 261,
     K_HISTORY = 262,
     K_NAMESCASESENSITIVE = 263,
     K_DESIGN = 264,
     K_VIAS = 265,
     K_TECH = 266,
     K_UNITS = 267,
     K_ARRAY = 268,
     K_FLOORPLAN = 269,
     K_SITE = 270,
     K_CANPLACE = 271,
     K_CANNOTOCCUPY = 272,
     K_DIEAREA = 273,
     K_PINS = 274,
     K_DEFAULTCAP = 275,
     K_MINPINS = 276,
     K_WIRECAP = 277,
     K_TRACKS = 278,
     K_GCELLGRID = 279,
     K_DO = 280,
     K_BY = 281,
     K_STEP = 282,
     K_LAYER = 283,
     K_ROW = 284,
     K_RECT = 285,
     K_COMPS = 286,
     K_COMP_GEN = 287,
     K_SOURCE = 288,
     K_WEIGHT = 289,
     K_EEQMASTER = 290,
     K_FIXED = 291,
     K_COVER = 292,
     K_UNPLACED = 293,
     K_PLACED = 294,
     K_FOREIGN = 295,
     K_REGION = 296,
     K_REGIONS = 297,
     K_NETS = 298,
     K_START_NET = 299,
     K_MUSTJOIN = 300,
     K_ORIGINAL = 301,
     K_USE = 302,
     K_STYLE = 303,
     K_PATTERN = 304,
     K_PATTERNNAME = 305,
     K_ESTCAP = 306,
     K_ROUTED = 307,
     K_NEW = 308,
     K_SNETS = 309,
     K_SHAPE = 310,
     K_WIDTH = 311,
     K_VOLTAGE = 312,
     K_SPACING = 313,
     K_NONDEFAULTRULE = 314,
     K_NONDEFAULTRULES = 315,
     K_N = 316,
     K_S = 317,
     K_E = 318,
     K_W = 319,
     K_FN = 320,
     K_FE = 321,
     K_FS = 322,
     K_FW = 323,
     K_GROUPS = 324,
     K_GROUP = 325,
     K_SOFT = 326,
     K_MAXX = 327,
     K_MAXY = 328,
     K_MAXHALFPERIMETER = 329,
     K_CONSTRAINTS = 330,
     K_NET = 331,
     K_PATH = 332,
     K_SUM = 333,
     K_DIFF = 334,
     K_SCANCHAINS = 335,
     K_START = 336,
     K_FLOATING = 337,
     K_ORDERED = 338,
     K_STOP = 339,
     K_IN = 340,
     K_OUT = 341,
     K_RISEMIN = 342,
     K_RISEMAX = 343,
     K_FALLMIN = 344,
     K_FALLMAX = 345,
     K_WIREDLOGIC = 346,
     K_MAXDIST = 347,
     K_ASSERTIONS = 348,
     K_DISTANCE = 349,
     K_MICRONS = 350,
     K_END = 351,
     K_IOTIMINGS = 352,
     K_RISE = 353,
     K_FALL = 354,
     K_VARIABLE = 355,
     K_SLEWRATE = 356,
     K_CAPACITANCE = 357,
     K_DRIVECELL = 358,
     K_FROMPIN = 359,
     K_TOPIN = 360,
     K_PARALLEL = 361,
     K_TIMINGDISABLES = 362,
     K_THRUPIN = 363,
     K_MACRO = 364,
     K_PARTITIONS = 365,
     K_TURNOFF = 366,
     K_FROMCLOCKPIN = 367,
     K_FROMCOMPPIN = 368,
     K_FROMIOPIN = 369,
     K_TOCLOCKPIN = 370,
     K_TOCOMPPIN = 371,
     K_TOIOPIN = 372,
     K_SETUPRISE = 373,
     K_SETUPFALL = 374,
     K_HOLDRISE = 375,
     K_HOLDFALL = 376,
     K_VPIN = 377,
     K_SUBNET = 378,
     K_XTALK = 379,
     K_PIN = 380,
     K_SYNTHESIZED = 381,
     K_DEFINE = 382,
     K_DEFINES = 383,
     K_DEFINEB = 384,
     K_IF = 385,
     K_THEN = 386,
     K_ELSE = 387,
     K_FALSE = 388,
     K_TRUE = 389,
     K_EQ = 390,
     K_NE = 391,
     K_LE = 392,
     K_LT = 393,
     K_GE = 394,
     K_GT = 395,
     K_OR = 396,
     K_AND = 397,
     K_NOT = 398,
     K_SPECIAL = 399,
     K_DIRECTION = 400,
     K_RANGE = 401,
     K_FPC = 402,
     K_HORIZONTAL = 403,
     K_VERTICAL = 404,
     K_ALIGN = 405,
     K_MIN = 406,
     K_MAX = 407,
     K_EQUAL = 408,
     K_BOTTOMLEFT = 409,
     K_TOPRIGHT = 410,
     K_ROWS = 411,
     K_TAPER = 412,
     K_TAPERRULE = 413,
     K_VERSION = 414,
     K_DIVIDERCHAR = 415,
     K_BUSBITCHARS = 416,
     K_PROPERTYDEFINITIONS = 417,
     K_STRING = 418,
     K_REAL = 419,
     K_INTEGER = 420,
     K_PROPERTY = 421,
     K_BEGINEXT = 422,
     K_ENDEXT = 423,
     K_NAMEMAPSTRING = 424,
     K_ON = 425,
     K_OFF = 426,
     K_X = 427,
     K_Y = 428,
     K_COMPONENT = 429,
     K_MASK = 430,
     K_MASKSHIFT = 431,
     K_COMPSMASKSHIFT = 432,
     K_SAMEMASK = 433,
     K_PINPROPERTIES = 434,
     K_TEST = 435,
     K_COMMONSCANPINS = 436,
     K_SNET = 437,
     K_COMPONENTPIN = 438,
     K_REENTRANTPATHS = 439,
     K_SHIELD = 440,
     K_SHIELDNET = 441,
     K_NOSHIELD = 442,
     K_VIRTUAL = 443,
     K_ANTENNAPINPARTIALMETALAREA = 444,
     K_ANTENNAPINPARTIALMETALSIDEAREA = 445,
     K_ANTENNAPINGATEAREA = 446,
     K_ANTENNAPINDIFFAREA = 447,
     K_ANTENNAPINMAXAREACAR = 448,
     K_ANTENNAPINMAXSIDEAREACAR = 449,
     K_ANTENNAPINPARTIALCUTAREA = 450,
     K_ANTENNAPINMAXCUTCAR = 451,
     K_SIGNAL = 452,
     K_POWER = 453,
     K_GROUND = 454,
     K_CLOCK = 455,
     K_TIEOFF = 456,
     K_ANALOG = 457,
     K_SCAN = 458,
     K_RESET = 459,
     K_RING = 460,
     K_STRIPE = 461,
     K_FOLLOWPIN = 462,
     K_IOWIRE = 463,
     K_COREWIRE = 464,
     K_BLOCKWIRE = 465,
     K_FILLWIRE = 466,
     K_BLOCKAGEWIRE = 467,
     K_PADRING = 468,
     K_BLOCKRING = 469,
     K_BLOCKAGES = 470,
     K_PLACEMENT = 471,
     K_SLOTS = 472,
     K_FILLS = 473,
     K_PUSHDOWN = 474,
     K_NETLIST = 475,
     K_DIST = 476,
     K_USER = 477,
     K_TIMING = 478,
     K_BALANCED = 479,
     K_STEINER = 480,
     K_TRUNK = 481,
     K_FIXEDBUMP = 482,
     K_FENCE = 483,
     K_FREQUENCY = 484,
     K_GUIDE = 485,
     K_MAXBITS = 486,
     K_PARTITION = 487,
     K_TYPE = 488,
     K_ANTENNAMODEL = 489,
     K_DRCFILL = 490,
     K_OXIDE1 = 491,
     K_OXIDE2 = 492,
     K_OXIDE3 = 493,
     K_OXIDE4 = 494,
     K_CUTSIZE = 495,
     K_CUTSPACING = 496,
     K_DESIGNRULEWIDTH = 497,
     K_DIAGWIDTH = 498,
     K_ENCLOSURE = 499,
     K_HALO = 500,
     K_GROUNDSENSITIVITY = 501,
     K_HARDSPACING = 502,
     K_LAYERS = 503,
     K_MINCUTS = 504,
     K_NETEXPR = 505,
     K_OFFSET = 506,
     K_ORIGIN = 507,
     K_ROWCOL = 508,
     K_STYLES = 509,
     K_POLYGON = 510,
     K_PORT = 511,
     K_SUPPLYSENSITIVITY = 512,
     K_VIA = 513,
     K_VIARULE = 514,
     K_WIREEXT = 515,
     K_EXCEPTPGNET = 516,
     K_FILLWIREOPC = 517,
     K_OPC = 518,
     K_PARTIAL = 519,
     K_ROUTEHALO = 520
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 457 "def.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1486

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  273
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  522
/* YYNRULES -- Number of rules.  */
#define YYNRULES  957
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1668

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   520

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     269,   270,   271,   268,   272,   267,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   266,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,     9,    10,    15,    16,    20,    24,
      25,    28,    30,    32,    34,    36,    38,    40,    42,    44,
      46,    48,    50,    52,    54,    56,    58,    60,    62,    64,
      66,    68,    70,    72,    74,    76,    78,    80,    82,    84,
      86,    88,    90,    92,    94,    96,    98,   100,   102,   104,
     106,   108,   109,   114,   117,   118,   123,   124,   129,   130,
     135,   137,   138,   144,   145,   148,   149,   155,   156,   162,
     163,   169,   170,   176,   177,   183,   184,   190,   191,   197,
     198,   204,   205,   211,   214,   215,   220,   221,   226,   228,
     231,   234,   235,   237,   243,   247,   251,   252,   267,   268,
     283,   285,   287,   289,   291,   293,   295,   297,   299,   300,
     307,   311,   314,   315,   318,   324,   327,   331,   335,   336,
     339,   340,   341,   342,   353,   354,   357,   360,   362,   366,
     370,   371,   376,   377,   382,   386,   389,   390,   391,   401,
     402,   403,   415,   416,   426,   430,   435,   440,   445,   450,
     451,   458,   459,   466,   471,   472,   479,   483,   484,   487,
     488,   491,   492,   495,   496,   499,   502,   503,   506,   509,
     511,   513,   515,   517,   519,   521,   523,   525,   527,   529,
     531,   533,   534,   535,   539,   542,   543,   544,   556,   557,
     563,   564,   568,   569,   572,   573,   578,   579,   582,   585,
     588,   591,   592,   602,   605,   607,   609,   612,   613,   617,
     618,   620,   621,   622,   627,   628,   631,   633,   642,   644,
     647,   651,   655,   656,   659,   660,   661,   668,   669,   672,
     673,   681,   682,   683,   694,   695,   700,   701,   702,   727,
     729,   731,   736,   741,   748,   749,   754,   756,   758,   759,
     762,   767,   772,   777,   782,   783,   787,   790,   795,   799,
     800,   803,   804,   805,   813,   816,   820,   821,   824,   825,
     830,   834,   835,   838,   841,   844,   847,   849,   851,   855,
     859,   863,   864,   867,   869,   870,   873,   877,   880,   881,
     886,   887,   890,   893,   894,   897,   899,   901,   903,   905,
     907,   909,   911,   913,   915,   917,   919,   921,   923,   924,
     929,   930,   936,   937,   939,   943,   945,   947,   949,   951,
     954,   957,   960,   964,   965,   974,   975,   977,   978,   985,
     986,   991,   993,   996,   999,  1002,  1005,  1008,  1009,  1016,
    1018,  1021,  1025,  1028,  1033,  1034,  1039,  1042,  1045,  1048,
    1052,  1055,  1059,  1063,  1064,  1067,  1071,  1073,  1074,  1078,
    1079,  1083,  1084,  1091,  1092,  1095,  1096,  1103,  1104,  1111,
    1112,  1119,  1120,  1122,  1125,  1126,  1129,  1130,  1135,  1139,
    1142,  1143,  1148,  1149,  1154,  1158,  1162,  1166,  1170,  1174,
    1178,  1179,  1184,  1186,  1187,  1192,  1193,  1194,  1200,  1201,
    1202,  1203,  1212,  1213,  1218,  1220,  1222,  1225,  1228,  1231,
    1234,  1236,  1238,  1240,  1242,  1244,  1245,  1252,  1253,  1258,
    1259,  1260,  1264,  1265,  1269,  1271,  1273,  1275,  1277,  1279,
    1281,  1283,  1286,  1287,  1291,  1292,  1293,  1300,  1303,  1306,
    1307,  1310,  1312,  1316,  1319,  1324,  1335,  1344,  1354,  1366,
    1368,  1370,  1371,  1382,  1383,  1388,  1390,  1395,  1400,  1405,
    1410,  1416,  1422,  1428,  1434,  1439,  1444,  1449,  1454,  1461,
    1462,  1465,  1467,  1469,  1471,  1472,  1476,  1479,  1480,  1483,
    1487,  1491,  1494,  1496,  1498,  1500,  1502,  1504,  1506,  1508,
    1510,  1512,  1514,  1516,  1518,  1522,  1523,  1526,  1530,  1531,
    1534,  1536,  1538,  1540,  1542,  1545,  1546,  1551,  1552,  1553,
    1560,  1564,  1568,  1569,  1570,  1580,  1581,  1588,  1589,  1590,
    1599,  1603,  1606,  1610,  1611,  1616,  1620,  1624,  1628,  1632,
    1636,  1637,  1642,  1644,  1645,  1647,  1649,  1651,  1653,  1655,
    1657,  1659,  1661,  1662,  1663,  1666,  1667,  1673,  1674,  1679,
    1680,  1681,  1689,  1691,  1694,  1697,  1700,  1703,  1704,  1708,
    1709,  1713,  1715,  1717,  1719,  1721,  1723,  1726,  1727,  1731,
    1732,  1733,  1741,  1743,  1747,  1750,  1754,  1758,  1759,  1762,
    1767,  1768,  1772,  1773,  1776,  1778,  1779,  1782,  1786,  1787,
    1792,  1793,  1798,  1800,  1803,  1805,  1806,  1809,  1812,  1815,
    1818,  1819,  1822,  1825,  1828,  1831,  1834,  1838,  1842,  1846,
    1850,  1851,  1854,  1856,  1858,  1863,  1864,  1868,  1869,  1876,
    1881,  1886,  1888,  1891,  1895,  1896,  1905,  1906,  1908,  1909,
    1912,  1916,  1920,  1924,  1928,  1931,  1934,  1938,  1942,  1943,
    1946,  1950,  1951,  1955,  1956,  1959,  1960,  1962,  1963,  1969,
    1970,  1975,  1976,  1981,  1982,  1988,  1989,  1994,  1995,  2001,
    2003,  2004,  2009,  2018,  2019,  2022,  2023,  2027,  2028,  2033,
    2042,  2055,  2056,  2059,  2060,  2064,  2065,  2070,  2079,  2092,
    2093,  2096,  2099,  2103,  2107,  2108,  2111,  2115,  2116,  2123,
    2124,  2127,  2133,  2139,  2143,  2144,  2145,  2152,  2154,  2155,
    2156,  2163,  2164,  2165,  2169,  2170,  2173,  2175,  2177,  2180,
    2185,  2189,  2190,  2193,  2194,  2195,  2204,  2206,  2208,  2210,
    2213,  2216,  2219,  2220,  2223,  2224,  2229,  2230,  2235,  2236,
    2239,  2240,  2246,  2247,  2253,  2257,  2261,  2262,  2265,  2266,
    2267,  2278,  2279,  2286,  2287,  2294,  2298,  2299,  2300,  2307,
    2308,  2312,  2315,  2319,  2323,  2324,  2327,  2331,  2332,  2337,
    2338,  2342,  2343,  2345,  2347,  2348,  2350,  2352,  2353,  2356,
    2357,  2365,  2366,  2373,  2374,  2380,  2381,  2389,  2390,  2397,
    2398,  2404,  2406,  2407,  2412,  2413,  2416,  2420,  2424,  2425,
    2428,  2429,  2432,  2435,  2438,  2441,  2444,  2446,  2449,  2453,
    2457,  2461,  2465,  2468,  2469,  2472,  2473,  2480,  2481,  2484,
    2485,  2488,  2489,  2493,  2494,  2498,  2500,  2502,  2504,  2506,
    2510,  2514,  2515,  2517,  2520,  2521,  2524,  2525,  2526,  2534,
    2535,  2538,  2539,  2544,  2545,  2548,  2551,  2554,  2557,  2561,
    2565,  2568,  2569,  2572,  2577,  2578,  2579,  2586,  2587,  2592,
    2593,  2596,  2600,  2604,  2606,  2608,  2612,  2613,  2618,  2621,
    2624,  2627,  2630,  2631,  2634,  2635,  2640,  2643,  2646,  2650,
    2651,  2654,  2658,  2659,  2666,  2670,  2674,  2677,  2678,  2681,
    2685,  2686,  2687,  2694,  2695,  2698,  2702,  2703,  2710,  2714,
    2718,  2721,  2722,  2725,  2729,  2730,  2731,  2740,  2741,  2742,
    2750,  2751,  2754,  2758,  2759,  2766,  2767,  2770,  2772,  2774,
    2777,  2780,  2781,  2784,  2786,  2788,  2791,  2795,  2799,  2804,
    2808,  2811,  2812,  2815,  2816,  2817,  2824,  2825,  2828,  2831,
    2832,  2833,  2842,  2843,  2848,  2849,  2854,  2855,  2861,  2863,
    2864,  2867,  2870,  2873,  2876,  2877,  2882,  2883,  2886,  2889,
    2892,  2895,  2899,  2903,  2906,  2907,  2910,  2911
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     274,     0,    -1,   275,   277,   278,   283,    -1,    -1,    -1,
     159,   276,     4,   266,    -1,    -1,     8,   170,   266,    -1,
       8,   171,   266,    -1,    -1,   278,   279,    -1,     1,    -1,
     280,    -1,   576,    -1,   716,    -1,   412,    -1,   577,    -1,
     374,    -1,   747,    -1,   411,    -1,   638,    -1,   558,    -1,
     620,    -1,   453,    -1,   769,    -1,   667,    -1,   703,    -1,
     398,    -1,   594,    -1,   736,    -1,   518,    -1,   789,    -1,
     654,    -1,   376,    -1,   286,    -1,   310,    -1,   311,    -1,
     313,    -1,   281,    -1,   316,    -1,   309,    -1,   288,    -1,
     373,    -1,   290,    -1,   318,    -1,   323,    -1,   291,    -1,
     352,    -1,   284,    -1,   362,    -1,   308,    -1,    -1,     9,
     282,     4,   266,    -1,    96,     9,    -1,    -1,    11,   285,
       4,   266,    -1,    -1,    13,   287,     4,   266,    -1,    -1,
      14,   289,     4,   266,    -1,     7,    -1,    -1,   162,   292,
     293,    96,   162,    -1,    -1,   293,   294,    -1,    -1,     9,
     295,     4,   304,   266,    -1,    -1,    76,   296,     4,   304,
     266,    -1,    -1,   182,   297,     4,   304,   266,    -1,    -1,
      41,   298,     4,   304,   266,    -1,    -1,    70,   299,     4,
     304,   266,    -1,    -1,   174,   300,     4,   304,   266,    -1,
      -1,    29,   301,     4,   304,   266,    -1,    -1,   183,   302,
       4,   304,   266,    -1,    -1,    59,   303,     4,   304,   266,
      -1,     1,   266,    -1,    -1,   165,   305,   547,   307,    -1,
      -1,   164,   306,   547,   307,    -1,   163,    -1,   163,     3,
      -1,   169,     4,    -1,    -1,     6,    -1,    12,    94,    95,
       6,   266,    -1,   160,     3,   266,    -1,   161,     3,   266,
      -1,    -1,    16,   312,     4,     6,     6,   315,    25,     6,
      26,     6,    27,     6,     6,   266,    -1,    -1,    17,   314,
       4,     6,     6,   315,    25,     6,    26,     6,    27,     6,
       6,   266,    -1,    61,    -1,    64,    -1,    62,    -1,    63,
      -1,    65,    -1,    68,    -1,    67,    -1,    66,    -1,    -1,
      18,   317,   392,   393,   394,   266,    -1,   319,   320,   322,
      -1,    20,     6,    -1,    -1,   320,   321,    -1,    21,     6,
      22,     6,   266,    -1,    96,    20,    -1,   324,   325,   351,
      -1,    19,     6,   266,    -1,    -1,   325,   326,    -1,    -1,
      -1,    -1,   267,   327,     4,   268,    76,   328,     4,   329,
     330,   266,    -1,    -1,   330,   331,    -1,   268,   144,    -1,
     375,    -1,   268,   145,     4,    -1,   268,   250,     3,    -1,
      -1,   268,   257,   332,     4,    -1,    -1,   268,   246,   333,
       4,    -1,   268,    47,   348,    -1,   268,   256,    -1,    -1,
      -1,   268,    28,   334,     4,   335,   342,   345,   395,   395,
      -1,    -1,    -1,   268,   255,   336,     4,   337,   344,   346,
     392,   393,   393,   394,    -1,    -1,   268,   258,   338,     4,
     343,   269,     6,     6,   270,    -1,   450,   395,   315,    -1,
     268,   189,     6,   349,    -1,   268,   190,     6,   349,    -1,
     268,   191,     6,   349,    -1,   268,   192,     6,   349,    -1,
      -1,   268,   193,     6,    28,   339,     4,    -1,    -1,   268,
     194,     6,    28,   340,     4,    -1,   268,   195,     6,   349,
      -1,    -1,   268,   196,     6,    28,   341,     4,    -1,   268,
     234,   347,    -1,    -1,   175,     6,    -1,    -1,   175,     6,
      -1,    -1,   175,     6,    -1,    -1,    58,     6,    -1,   242,
       6,    -1,    -1,    58,     6,    -1,   242,     6,    -1,   236,
      -1,   237,    -1,   238,    -1,   239,    -1,   197,    -1,   198,
      -1,   199,    -1,   200,    -1,   201,    -1,   202,    -1,   203,
      -1,   204,    -1,    -1,    -1,    28,   350,     4,    -1,    96,
      19,    -1,    -1,    -1,    29,   353,     4,     4,     6,     6,
     315,   354,   355,   357,   266,    -1,    -1,    25,     6,    26,
       6,   356,    -1,    -1,    27,     6,     6,    -1,    -1,   357,
     358,    -1,    -1,   268,   166,   359,   360,    -1,    -1,   360,
     361,    -1,     4,     6,    -1,     4,     3,    -1,     4,     4,
      -1,    -1,   364,     6,   363,    25,     6,    27,     6,   366,
     266,    -1,    23,   365,    -1,   172,    -1,   173,    -1,   367,
     369,    -1,    -1,   175,     6,   368,    -1,    -1,   178,    -1,
      -1,    -1,    28,   370,   372,   371,    -1,    -1,   372,   371,
      -1,     4,    -1,    24,   365,     6,    25,     6,    27,     6,
     266,    -1,   167,    -1,   268,   167,    -1,   377,   378,   397,
      -1,    10,     6,   266,    -1,    -1,   378,   379,    -1,    -1,
      -1,   267,   380,     4,   381,   382,   266,    -1,    -1,   382,
     383,    -1,    -1,   268,    30,   384,     4,   396,   395,   395,
      -1,    -1,    -1,   268,   255,   385,     4,   396,   386,   392,
     393,   393,   394,    -1,    -1,   268,    50,   387,     4,    -1,
      -1,    -1,   268,   259,   388,     4,   268,   240,     6,     6,
     268,   248,   389,     4,     4,     4,   268,   241,     6,     6,
     268,   244,     6,     6,     6,     6,    -1,   390,    -1,   375,
      -1,   268,   253,     6,     6,    -1,   268,   252,     6,     6,
      -1,   268,   251,     6,     6,     6,     6,    -1,    -1,   268,
      49,   391,     4,    -1,   395,    -1,   395,    -1,    -1,   394,
     393,    -1,   269,     6,     6,   270,    -1,   269,   271,     6,
     270,    -1,   269,     6,   271,   270,    -1,   269,   271,   271,
     270,    -1,    -1,   268,   175,     6,    -1,    96,    10,    -1,
     399,   400,    96,    42,    -1,    42,     6,   266,    -1,    -1,
     400,   401,    -1,    -1,    -1,   267,   402,     4,   403,   404,
     405,   266,    -1,   395,   395,    -1,   404,   395,   395,    -1,
      -1,   405,   406,    -1,    -1,   268,   166,   407,   408,    -1,
     268,   233,   410,    -1,    -1,   408,   409,    -1,     4,     6,
      -1,     4,     3,    -1,     4,     4,    -1,   228,    -1,   230,
      -1,   177,   414,   266,    -1,   413,   416,   452,    -1,    31,
       6,   266,    -1,    -1,   414,   415,    -1,     4,    -1,    -1,
     416,   417,    -1,   418,   422,   266,    -1,   419,   421,    -1,
      -1,   267,   420,     4,     4,    -1,    -1,   421,   271,    -1,
     421,     4,    -1,    -1,   422,   423,    -1,   427,    -1,   430,
      -1,   447,    -1,   451,    -1,   448,    -1,   444,    -1,   432,
      -1,   425,    -1,   434,    -1,   437,    -1,   439,    -1,   424,
      -1,   375,    -1,    -1,   268,    35,   426,     4,    -1,    -1,
     268,    32,   428,     4,   429,    -1,    -1,     4,    -1,   268,
      33,   431,    -1,   220,    -1,   221,    -1,   222,    -1,   223,
      -1,   443,   433,    -1,   443,     4,    -1,   395,   395,    -1,
     433,   395,   395,    -1,    -1,   268,   245,   435,   436,     6,
       6,     6,     6,    -1,    -1,    71,    -1,    -1,   268,   265,
       6,   438,     4,     4,    -1,    -1,   268,   166,   440,   441,
      -1,   442,    -1,   441,   442,    -1,     4,     6,    -1,     4,
       3,    -1,     4,     4,    -1,   268,    41,    -1,    -1,   268,
      40,   445,     4,   446,   315,    -1,   395,    -1,     6,     6,
      -1,   450,   395,   315,    -1,   268,    38,    -1,   268,    38,
     395,   315,    -1,    -1,   268,   176,   449,     4,    -1,   268,
      36,    -1,   268,    37,    -1,   268,    39,    -1,   268,    34,
       6,    -1,    96,    31,    -1,   454,   455,   516,    -1,    43,
       6,   266,    -1,    -1,   455,   456,    -1,   457,   469,   266,
      -1,   458,    -1,    -1,   267,   459,   460,    -1,    -1,     4,
     461,   463,    -1,    -1,    45,   269,     4,   462,     4,   270,
      -1,    -1,   463,   464,    -1,    -1,   269,     4,   465,     4,
     468,   270,    -1,    -1,   269,   271,   466,     4,   468,   270,
      -1,    -1,   269,   125,   467,     4,   468,   270,    -1,    -1,
     375,    -1,   268,   126,    -1,    -1,   469,   470,    -1,    -1,
     268,   493,   471,   494,    -1,   268,    33,   484,    -1,   268,
     227,    -1,    -1,   268,   229,   472,     6,    -1,    -1,   268,
      46,   473,     4,    -1,   268,    49,   548,    -1,   268,    34,
       6,    -1,   268,   124,     6,    -1,   268,    51,     6,    -1,
     268,    47,   348,    -1,   268,    48,     6,    -1,    -1,   268,
      59,   474,     4,    -1,   485,    -1,    -1,   268,   186,   475,
       4,    -1,    -1,    -1,   268,   187,   476,   477,   494,    -1,
      -1,    -1,    -1,   268,   123,   478,     4,   479,   694,   480,
     698,    -1,    -1,   268,   166,   481,   482,    -1,   375,    -1,
     483,    -1,   482,   483,    -1,     4,     6,    -1,     4,     3,
      -1,     4,     4,    -1,   220,    -1,   221,    -1,   222,    -1,
     223,    -1,   180,    -1,    -1,   487,   489,   395,   395,   486,
     491,    -1,    -1,   268,   122,   488,     4,    -1,    -1,    -1,
      28,   490,     4,    -1,    -1,   492,   395,   315,    -1,    39,
      -1,    36,    -1,    37,    -1,    36,    -1,    37,    -1,    52,
      -1,   497,    -1,   494,   495,    -1,    -1,    53,   496,   497,
      -1,    -1,    -1,     4,   498,   509,   506,   499,   502,    -1,
     188,   507,    -1,    30,   508,    -1,    -1,   502,   503,    -1,
       4,    -1,   175,     6,     4,    -1,     4,   315,    -1,   175,
       6,     4,   315,    -1,   175,     6,     4,    25,     6,    26,
       6,    27,     6,     6,    -1,     4,    25,     6,    26,     6,
      27,     6,     6,    -1,     4,   315,    25,     6,    26,     6,
      27,     6,     6,    -1,   175,     6,     4,   315,    25,     6,
      26,     6,    27,     6,     6,    -1,   500,    -1,   501,    -1,
      -1,   175,     6,    30,   504,   269,     6,     6,     6,     6,
     270,    -1,    -1,   175,     6,   505,   506,    -1,   506,    -1,
     269,     6,     6,   270,    -1,   269,   271,     6,   270,    -1,
     269,     6,   271,   270,    -1,   269,   271,   271,   270,    -1,
     269,     6,     6,     6,   270,    -1,   269,   271,     6,     6,
     270,    -1,   269,     6,   271,     6,   270,    -1,   269,   271,
     271,     6,   270,    -1,   269,     6,     6,   270,    -1,   269,
     271,     6,   270,    -1,   269,     6,   271,   270,    -1,   269,
     271,   271,   270,    -1,   269,     6,     6,     6,     6,   270,
      -1,    -1,   509,   510,    -1,   513,    -1,   511,    -1,   157,
      -1,    -1,   158,   512,     4,    -1,    48,     6,    -1,    -1,
     514,   515,    -1,   268,    55,   517,    -1,   268,    48,     6,
      -1,    96,    43,    -1,   205,    -1,   206,    -1,   207,    -1,
     208,    -1,   209,    -1,   210,    -1,   211,    -1,   262,    -1,
     235,    -1,   212,    -1,   213,    -1,   214,    -1,   556,   519,
     557,    -1,    -1,   519,   520,    -1,   457,   521,   266,    -1,
      -1,   521,   522,    -1,   537,    -1,   539,    -1,   541,    -1,
     523,    -1,   268,   493,    -1,    -1,   268,   493,   524,   549,
      -1,    -1,    -1,   268,   185,   525,     4,   526,   535,    -1,
     268,    55,   517,    -1,   268,   175,     6,    -1,    -1,    -1,
     268,   255,   527,     4,   528,   392,   393,   393,   394,    -1,
      -1,   268,    30,   529,     4,   395,   395,    -1,    -1,    -1,
     268,   258,   530,     4,   534,   531,   392,   394,    -1,   268,
      33,   431,    -1,   268,   227,    -1,   268,   229,     6,    -1,
      -1,   268,    46,   532,     4,    -1,   268,    49,   548,    -1,
     268,    34,     6,    -1,   268,    51,     6,    -1,   268,    47,
     348,    -1,   268,    48,     6,    -1,    -1,   268,   166,   533,
     544,    -1,   375,    -1,    -1,    61,    -1,    64,    -1,    62,
      -1,    63,    -1,    65,    -1,    68,    -1,    67,    -1,    66,
      -1,    -1,    -1,   536,   549,    -1,    -1,   268,    56,   538,
       4,     6,    -1,    -1,   268,    57,   540,     4,    -1,    -1,
      -1,   268,    58,   542,     4,     6,   543,   546,    -1,   545,
      -1,   544,   545,    -1,     4,     6,    -1,     4,     3,    -1,
       4,     4,    -1,    -1,   146,     6,     6,    -1,    -1,   146,
       6,     6,    -1,   224,    -1,   225,    -1,   226,    -1,    91,
      -1,   552,    -1,   549,   550,    -1,    -1,    53,   551,   552,
      -1,    -1,    -1,     4,   553,   555,   514,   506,   554,   502,
      -1,     6,    -1,    54,     6,   266,    -1,    96,    54,    -1,
     559,   560,   575,    -1,    69,     6,   266,    -1,    -1,   560,
     561,    -1,   562,   564,   566,   266,    -1,    -1,   267,   563,
       4,    -1,    -1,   564,   565,    -1,     4,    -1,    -1,   566,
     567,    -1,   268,    71,   573,    -1,    -1,   268,   166,   568,
     571,    -1,    -1,   268,    41,   569,   570,    -1,   375,    -1,
     395,   395,    -1,     4,    -1,    -1,   571,   572,    -1,     4,
       6,    -1,     4,     3,    -1,     4,     4,    -1,    -1,   573,
     574,    -1,    72,     6,    -1,    73,     6,    -1,    74,     6,
      -1,    96,    69,    -1,   578,   580,   593,    -1,   579,   580,
     592,    -1,    93,     6,   266,    -1,    75,     6,   266,    -1,
      -1,   580,   581,    -1,   582,    -1,   587,    -1,   267,   583,
     590,   266,    -1,    -1,    76,   584,     4,    -1,    -1,    77,
     585,     4,     4,     4,     4,    -1,    78,   269,   586,   270,
      -1,    79,   269,   586,   270,    -1,   583,    -1,   586,   583,
      -1,   586,   272,   583,    -1,    -1,   267,    91,   588,     4,
     589,    92,     6,   266,    -1,    -1,   268,    -1,    -1,   590,
     591,    -1,   268,    87,     6,    -1,   268,    88,     6,    -1,
     268,    89,     6,    -1,   268,    90,     6,    -1,    96,    75,
      -1,    96,    93,    -1,   595,   596,   619,    -1,    80,     6,
     266,    -1,    -1,   596,   597,    -1,   598,   600,   266,    -1,
      -1,   267,   599,     4,    -1,    -1,   600,   602,    -1,    -1,
       4,    -1,    -1,   268,    81,   603,     4,   601,    -1,    -1,
     268,    82,   604,   610,    -1,    -1,   268,    83,   605,   614,
      -1,    -1,   268,    84,   606,     4,   601,    -1,    -1,   268,
     181,   607,   609,    -1,    -1,   268,   232,   608,     4,   618,
      -1,   375,    -1,    -1,   269,     4,     4,   270,    -1,   269,
       4,     4,   270,   269,     4,     4,   270,    -1,    -1,   610,
     611,    -1,    -1,     4,   612,   613,    -1,    -1,   269,     4,
       4,   270,    -1,   269,     4,     4,   270,   269,     4,     4,
     270,    -1,   269,     4,     4,   270,   269,     4,     4,   270,
     269,     4,     4,   270,    -1,    -1,   614,   615,    -1,    -1,
       4,   616,   617,    -1,    -1,   269,     4,     4,   270,    -1,
     269,     4,     4,   270,   269,     4,     4,   270,    -1,   269,
       4,     4,   270,   269,     4,     4,   270,   269,     4,     4,
     270,    -1,    -1,   231,     6,    -1,    96,    80,    -1,   621,
     622,   637,    -1,    97,     6,   266,    -1,    -1,   622,   623,
      -1,   624,   626,   266,    -1,    -1,   267,   269,   625,     4,
       4,   270,    -1,    -1,   626,   627,    -1,   268,   636,   100,
       6,     6,    -1,   268,   636,   101,     6,     6,    -1,   268,
     102,     6,    -1,    -1,    -1,   268,   103,   628,     4,   629,
     630,    -1,   375,    -1,    -1,    -1,   633,   105,   631,     4,
     632,   635,    -1,    -1,    -1,   104,   634,     4,    -1,    -1,
     106,     6,    -1,    98,    -1,    99,    -1,    96,    97,    -1,
     639,   640,    96,   147,    -1,   147,     6,   266,    -1,    -1,
     640,   641,    -1,    -1,    -1,   267,   642,     4,   644,   643,
     645,   646,   266,    -1,   148,    -1,   149,    -1,   150,    -1,
     152,     6,    -1,   151,     6,    -1,   153,     6,    -1,    -1,
     646,   647,    -1,    -1,   268,   154,   648,   650,    -1,    -1,
     268,   155,   649,   650,    -1,    -1,   650,   651,    -1,    -1,
     269,   156,   652,     4,   270,    -1,    -1,   269,    31,   653,
       4,   270,    -1,   655,   656,   666,    -1,   107,     6,   266,
      -1,    -1,   656,   657,    -1,    -1,    -1,   267,   104,   658,
       4,     4,   105,   659,     4,     4,   266,    -1,    -1,   267,
     108,   660,     4,     4,   266,    -1,    -1,   267,   109,   661,
       4,   662,   266,    -1,   267,   184,   266,    -1,    -1,    -1,
     104,   663,     4,   105,   664,     4,    -1,    -1,   108,   665,
       4,    -1,    96,   107,    -1,   668,   669,   693,    -1,   110,
       6,   266,    -1,    -1,   669,   670,    -1,   671,   676,   266,
      -1,    -1,   267,   672,     4,   673,    -1,    -1,   111,   674,
     675,    -1,    -1,   118,    -1,   119,    -1,    -1,   120,    -1,
     121,    -1,    -1,   676,   677,    -1,    -1,   268,   112,   678,
       4,     4,   636,   684,    -1,    -1,   268,   113,   679,     4,
       4,   691,    -1,    -1,   268,   114,   680,     4,   689,    -1,
      -1,   268,   115,   681,     4,     4,   636,   684,    -1,    -1,
     268,   116,   682,     4,     4,   691,    -1,    -1,   268,   117,
     683,     4,   689,    -1,   375,    -1,    -1,   686,    19,   685,
     688,    -1,    -1,   686,   687,    -1,   151,     6,     6,    -1,
     152,     6,     6,    -1,    -1,   688,     4,    -1,    -1,   689,
     690,    -1,    87,     6,    -1,    89,     6,    -1,    88,     6,
      -1,    90,     6,    -1,   692,    -1,   691,   692,    -1,    87,
       6,     6,    -1,    89,     6,     6,    -1,    88,     6,     6,
      -1,    90,     6,     6,    -1,    96,   110,    -1,    -1,   694,
     695,    -1,    -1,   269,   696,     4,     4,   697,   270,    -1,
      -1,   268,   126,    -1,    -1,   698,   699,    -1,    -1,   702,
     700,   494,    -1,    -1,    59,   701,     4,    -1,    36,    -1,
      37,    -1,    52,    -1,   187,    -1,   704,   707,   706,    -1,
     179,     6,   705,    -1,    -1,   266,    -1,    96,   179,    -1,
      -1,   707,   708,    -1,    -1,    -1,   267,   709,     4,     4,
     710,   711,   266,    -1,    -1,   711,   712,    -1,    -1,   268,
     166,   713,   714,    -1,    -1,   714,   715,    -1,     4,     6,
      -1,     4,     3,    -1,     4,     4,    -1,   717,   719,   718,
      -1,   215,     6,   266,    -1,    96,   215,    -1,    -1,   719,
     720,    -1,   721,   734,   733,   266,    -1,    -1,    -1,   267,
      28,   722,     4,   723,   725,    -1,    -1,   267,   216,   724,
     730,    -1,    -1,   725,   726,    -1,   268,    58,     6,    -1,
     268,   242,     6,    -1,   727,    -1,   728,    -1,   268,   175,
       6,    -1,    -1,   268,   174,   729,     4,    -1,   268,   217,
      -1,   268,   218,    -1,   268,   219,    -1,   268,   261,    -1,
      -1,   730,   731,    -1,    -1,   268,   174,   732,     4,    -1,
     268,   219,    -1,   268,    71,    -1,   268,   264,     6,    -1,
      -1,   733,   734,    -1,    30,   395,   395,    -1,    -1,   255,
     735,   392,   393,   393,   394,    -1,   737,   739,   738,    -1,
     217,     6,   266,    -1,    96,   217,    -1,    -1,   739,   740,
      -1,   741,   744,   266,    -1,    -1,    -1,   267,    28,   742,
       4,   743,   745,    -1,    -1,   744,   745,    -1,    30,   395,
     395,    -1,    -1,   255,   746,   392,   393,   393,   394,    -1,
     748,   750,   749,    -1,   218,     6,   266,    -1,    96,   218,
      -1,    -1,   750,   751,    -1,   754,   757,   266,    -1,    -1,
      -1,   267,   258,   752,     4,   753,   764,   763,   266,    -1,
      -1,    -1,   267,    28,   755,     4,   756,   760,   758,    -1,
      -1,   757,   758,    -1,    30,   395,   395,    -1,    -1,   255,
     759,   392,   393,   393,   394,    -1,    -1,   760,   761,    -1,
     762,    -1,   767,    -1,   268,   263,    -1,   392,   394,    -1,
      -1,   764,   765,    -1,   766,    -1,   768,    -1,   268,   263,
      -1,   268,   175,     6,    -1,   268,   175,     6,    -1,   770,
     773,   772,   771,    -1,    60,     6,   266,    -1,    96,    60,
      -1,    -1,   772,   773,    -1,    -1,    -1,   267,   774,     4,
     775,   776,   266,    -1,    -1,   776,   777,    -1,   268,   247,
      -1,    -1,    -1,   268,    28,   778,     4,    56,     6,   779,
     783,    -1,    -1,   268,   258,   780,     4,    -1,    -1,   268,
     259,   781,     4,    -1,    -1,   268,   249,   782,     4,     6,
      -1,   785,    -1,    -1,   783,   784,    -1,   243,     6,    -1,
      58,     6,    -1,   260,     6,    -1,    -1,   268,   166,   786,
     787,    -1,    -1,   787,   788,    -1,     4,     6,    -1,     4,
       3,    -1,     4,     4,    -1,   790,   792,   791,    -1,   254,
       6,   266,    -1,    96,   254,    -1,    -1,   792,   793,    -1,
      -1,   267,    48,     6,   794,   392,   393,   394,   266,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   216,   216,   219,   220,   220,   246,   247,   260,   278,
     279,   280,   283,   283,   283,   283,   284,   284,   284,   284,
     285,   285,   285,   286,   286,   286,   287,   287,   287,   288,
     288,   288,   288,   289,   292,   292,   292,   292,   293,   293,
     293,   294,   294,   294,   295,   295,   295,   296,   296,   296,
     296,   301,   301,   308,   333,   333,   339,   339,   345,   345,
     351,   358,   357,   369,   370,   373,   373,   382,   382,   391,
     391,   400,   400,   409,   409,   418,   418,   427,   427,   438,
     437,   448,   447,   468,   470,   470,   475,   475,   481,   486,
     491,   497,   498,   501,   509,   516,   523,   523,   535,   535,
     548,   549,   550,   551,   552,   553,   554,   555,   558,   557,
     570,   573,   585,   586,   589,   600,   603,   606,   612,   613,
     616,   617,   618,   616,   630,   631,   633,   639,   645,   651,
     672,   672,   692,   692,   712,   716,   737,   738,   737,   756,
     757,   756,   792,   792,   818,   829,   847,   865,   883,   901,
     901,   919,   919,   938,   956,   956,   974,   991,   992,  1006,
    1007,  1014,  1015,  1028,  1029,  1052,  1076,  1077,  1100,  1124,
    1129,  1134,  1139,  1145,  1147,  1149,  1151,  1153,  1155,  1157,
    1159,  1164,  1165,  1165,  1168,  1174,  1176,  1174,  1190,  1200,
    1238,  1241,  1249,  1250,  1253,  1253,  1257,  1258,  1261,  1273,
    1282,  1293,  1292,  1326,  1331,  1333,  1336,  1338,  1339,  1350,
    1351,  1354,  1355,  1355,  1358,  1359,  1362,  1368,  1397,  1403,
    1406,  1409,  1415,  1416,  1419,  1420,  1419,  1431,  1432,  1435,
    1435,  1442,  1443,  1442,  1469,  1469,  1479,  1481,  1479,  1504,
    1505,  1511,  1523,  1535,  1547,  1547,  1560,  1563,  1566,  1567,
    1570,  1577,  1583,  1589,  1596,  1597,  1600,  1606,  1612,  1618,
    1619,  1622,  1623,  1622,  1632,  1635,  1640,  1641,  1644,  1644,
    1647,  1662,  1663,  1666,  1681,  1690,  1700,  1702,  1705,  1722,
    1725,  1732,  1733,  1736,  1743,  1744,  1747,  1753,  1759,  1759,
    1767,  1768,  1773,  1779,  1780,  1783,  1783,  1783,  1783,  1783,
    1784,  1784,  1784,  1784,  1785,  1785,  1785,  1788,  1795,  1795,
    1801,  1801,  1809,  1810,  1813,  1819,  1821,  1823,  1825,  1830,
    1832,  1838,  1849,  1862,  1861,  1883,  1884,  1904,  1904,  1924,
    1924,  1928,  1929,  1932,  1943,  1952,  1962,  1965,  1965,  1980,
    1982,  1985,  1992,  1999,  2014,  2014,  2023,  2025,  2027,  2030,
    2036,  2042,  2045,  2052,  2053,  2056,  2067,  2071,  2071,  2074,
    2073,  2082,  2082,  2090,  2091,  2094,  2094,  2108,  2108,  2115,
    2115,  2124,  2125,  2132,  2137,  2138,  2142,  2141,  2160,  2163,
    2180,  2180,  2198,  2198,  2201,  2204,  2207,  2210,  2213,  2216,
    2219,  2219,  2230,  2232,  2232,  2235,  2236,  2235,  2282,  2287,
    2297,  2281,  2311,  2311,  2315,  2321,  2322,  2325,  2336,  2345,
    2355,  2357,  2359,  2361,  2363,  2367,  2366,  2377,  2377,  2380,
    2381,  2381,  2384,  2385,  2388,  2390,  2392,  2395,  2397,  2399,
    2403,  2407,  2410,  2410,  2416,  2435,  2415,  2449,  2466,  2483,
    2484,  2489,  2500,  2514,  2521,  2532,  2556,  2590,  2624,  2649,
    2650,  2651,  2651,  2662,  2661,  2671,  2682,  2690,  2697,  2704,
    2710,  2718,  2726,  2734,  2743,  2751,  2758,  2765,  2773,  2782,
    2783,  2785,  2786,  2789,  2793,  2793,  2798,  2818,  2819,  2823,
    2827,  2847,  2853,  2855,  2857,  2859,  2861,  2863,  2865,  2867,
    2883,  2885,  2887,  2889,  2892,  2895,  2896,  2899,  2902,  2903,
    2906,  2906,  2907,  2907,  2910,  2924,  2923,  2945,  2946,  2945,
    2952,  2956,  2962,  2963,  2962,  3003,  3003,  3036,  3037,  3036,
    3069,  3072,  3075,  3078,  3078,  3081,  3084,  3087,  3096,  3099,
    3102,  3102,  3106,  3110,  3111,  3112,  3113,  3114,  3115,  3116,
    3117,  3118,  3121,  3135,  3135,  3190,  3190,  3199,  3199,  3217,
    3218,  3217,  3225,  3226,  3229,  3241,  3250,  3260,  3261,  3266,
    3267,  3270,  3272,  3274,  3276,  3280,  3297,  3300,  3300,  3319,
    3327,  3318,  3335,  3340,  3347,  3354,  3357,  3363,  3364,  3367,
    3373,  3373,  3384,  3385,  3388,  3395,  3396,  3399,  3401,  3401,
    3404,  3404,  3406,  3412,  3422,  3427,  3428,  3431,  3442,  3451,
    3461,  3462,  3465,  3473,  3481,  3490,  3497,  3501,  3504,  3518,
    3532,  3533,  3536,  3537,  3547,  3560,  3560,  3565,  3565,  3570,
    3575,  3581,  3582,  3584,  3586,  3586,  3595,  3596,  3599,  3600,
    3603,  3608,  3613,  3618,  3624,  3635,  3646,  3649,  3655,  3656,
    3659,  3665,  3665,  3672,  3673,  3678,  3679,  3682,  3682,  3686,
    3686,  3689,  3688,  3697,  3697,  3701,  3701,  3703,  3703,  3721,
    3728,  3729,  3738,  3752,  3753,  3757,  3756,  3767,  3768,  3781,
    3802,  3833,  3834,  3838,  3837,  3846,  3847,  3860,  3881,  3913,
    3914,  3917,  3926,  3929,  3940,  3941,  3944,  3950,  3950,  3956,
    3957,  3961,  3966,  3971,  3976,  3977,  3976,  3985,  3992,  3993,
    3991,  3999,  4000,  4000,  4006,  4007,  4013,  4013,  4015,  4021,
    4027,  4033,  4034,  4037,  4038,  4037,  4042,  4044,  4047,  4049,
    4051,  4053,  4056,  4057,  4061,  4060,  4064,  4063,  4068,  4069,
    4071,  4071,  4073,  4073,  4076,  4080,  4087,  4088,  4091,  4092,
    4091,  4100,  4100,  4108,  4108,  4116,  4122,  4123,  4122,  4128,
    4128,  4134,  4141,  4144,  4151,  4152,  4155,  4161,  4161,  4167,
    4168,  4175,  4176,  4178,  4182,  4183,  4185,  4188,  4189,  4192,
    4192,  4198,  4198,  4204,  4204,  4210,  4210,  4216,  4216,  4222,
    4222,  4227,  4235,  4234,  4238,  4239,  4242,  4247,  4253,  4254,
    4257,  4258,  4260,  4262,  4264,  4266,  4270,  4271,  4274,  4277,
    4280,  4283,  4287,  4291,  4292,  4295,  4295,  4304,  4305,  4308,
    4309,  4312,  4311,  4324,  4324,  4327,  4329,  4331,  4333,  4336,
    4338,  4344,  4345,  4348,  4352,  4353,  4356,  4357,  4356,  4366,
    4367,  4369,  4369,  4373,  4374,  4377,  4388,  4397,  4407,  4409,
    4413,  4417,  4418,  4421,  4430,  4431,  4430,  4450,  4449,  4466,
    4467,  4470,  4496,  4518,  4519,  4522,  4531,  4531,  4550,  4571,
    4592,  4610,  4642,  4643,  4648,  4648,  4666,  4684,  4718,  4754,
    4755,  4758,  4764,  4763,  4789,  4791,  4795,  4799,  4800,  4803,
    4811,  4812,  4811,  4819,  4820,  4823,  4829,  4828,  4841,  4843,
    4847,  4851,  4852,  4855,  4862,  4863,  4862,  4872,  4873,  4872,
    4881,  4882,  4885,  4891,  4890,  4909,  4910,  4912,  4913,  4918,
    4937,  4947,  4948,  4950,  4951,  4956,  4976,  4986,  4996,  4999,
    5017,  5021,  5022,  5025,  5026,  5025,  5036,  5037,  5040,  5045,
    5047,  5045,  5054,  5054,  5060,  5060,  5066,  5066,  5072,  5075,
    5076,  5079,  5085,  5091,  5099,  5099,  5103,  5104,  5107,  5118,
    5127,  5138,  5140,  5157,  5161,  5162,  5166,  5165
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "QSTRING", "T_STRING", "SITE_PATTERN",
  "NUMBER", "K_HISTORY", "K_NAMESCASESENSITIVE", "K_DESIGN", "K_VIAS",
  "K_TECH", "K_UNITS", "K_ARRAY", "K_FLOORPLAN", "K_SITE", "K_CANPLACE",
  "K_CANNOTOCCUPY", "K_DIEAREA", "K_PINS", "K_DEFAULTCAP", "K_MINPINS",
  "K_WIRECAP", "K_TRACKS", "K_GCELLGRID", "K_DO", "K_BY", "K_STEP",
  "K_LAYER", "K_ROW", "K_RECT", "K_COMPS", "K_COMP_GEN", "K_SOURCE",
  "K_WEIGHT", "K_EEQMASTER", "K_FIXED", "K_COVER", "K_UNPLACED",
  "K_PLACED", "K_FOREIGN", "K_REGION", "K_REGIONS", "K_NETS",
  "K_START_NET", "K_MUSTJOIN", "K_ORIGINAL", "K_USE", "K_STYLE",
  "K_PATTERN", "K_PATTERNNAME", "K_ESTCAP", "K_ROUTED", "K_NEW", "K_SNETS",
  "K_SHAPE", "K_WIDTH", "K_VOLTAGE", "K_SPACING", "K_NONDEFAULTRULE",
  "K_NONDEFAULTRULES", "K_N", "K_S", "K_E", "K_W", "K_FN", "K_FE", "K_FS",
  "K_FW", "K_GROUPS", "K_GROUP", "K_SOFT", "K_MAXX", "K_MAXY",
  "K_MAXHALFPERIMETER", "K_CONSTRAINTS", "K_NET", "K_PATH", "K_SUM",
  "K_DIFF", "K_SCANCHAINS", "K_START", "K_FLOATING", "K_ORDERED", "K_STOP",
  "K_IN", "K_OUT", "K_RISEMIN", "K_RISEMAX", "K_FALLMIN", "K_FALLMAX",
  "K_WIREDLOGIC", "K_MAXDIST", "K_ASSERTIONS", "K_DISTANCE", "K_MICRONS",
  "K_END", "K_IOTIMINGS", "K_RISE", "K_FALL", "K_VARIABLE", "K_SLEWRATE",
  "K_CAPACITANCE", "K_DRIVECELL", "K_FROMPIN", "K_TOPIN", "K_PARALLEL",
  "K_TIMINGDISABLES", "K_THRUPIN", "K_MACRO", "K_PARTITIONS", "K_TURNOFF",
  "K_FROMCLOCKPIN", "K_FROMCOMPPIN", "K_FROMIOPIN", "K_TOCLOCKPIN",
  "K_TOCOMPPIN", "K_TOIOPIN", "K_SETUPRISE", "K_SETUPFALL", "K_HOLDRISE",
  "K_HOLDFALL", "K_VPIN", "K_SUBNET", "K_XTALK", "K_PIN", "K_SYNTHESIZED",
  "K_DEFINE", "K_DEFINES", "K_DEFINEB", "K_IF", "K_THEN", "K_ELSE",
  "K_FALSE", "K_TRUE", "K_EQ", "K_NE", "K_LE", "K_LT", "K_GE", "K_GT",
  "K_OR", "K_AND", "K_NOT", "K_SPECIAL", "K_DIRECTION", "K_RANGE", "K_FPC",
  "K_HORIZONTAL", "K_VERTICAL", "K_ALIGN", "K_MIN", "K_MAX", "K_EQUAL",
  "K_BOTTOMLEFT", "K_TOPRIGHT", "K_ROWS", "K_TAPER", "K_TAPERRULE",
  "K_VERSION", "K_DIVIDERCHAR", "K_BUSBITCHARS", "K_PROPERTYDEFINITIONS",
  "K_STRING", "K_REAL", "K_INTEGER", "K_PROPERTY", "K_BEGINEXT",
  "K_ENDEXT", "K_NAMEMAPSTRING", "K_ON", "K_OFF", "K_X", "K_Y",
  "K_COMPONENT", "K_MASK", "K_MASKSHIFT", "K_COMPSMASKSHIFT", "K_SAMEMASK",
  "K_PINPROPERTIES", "K_TEST", "K_COMMONSCANPINS", "K_SNET",
  "K_COMPONENTPIN", "K_REENTRANTPATHS", "K_SHIELD", "K_SHIELDNET",
  "K_NOSHIELD", "K_VIRTUAL", "K_ANTENNAPINPARTIALMETALAREA",
  "K_ANTENNAPINPARTIALMETALSIDEAREA", "K_ANTENNAPINGATEAREA",
  "K_ANTENNAPINDIFFAREA", "K_ANTENNAPINMAXAREACAR",
  "K_ANTENNAPINMAXSIDEAREACAR", "K_ANTENNAPINPARTIALCUTAREA",
  "K_ANTENNAPINMAXCUTCAR", "K_SIGNAL", "K_POWER", "K_GROUND", "K_CLOCK",
  "K_TIEOFF", "K_ANALOG", "K_SCAN", "K_RESET", "K_RING", "K_STRIPE",
  "K_FOLLOWPIN", "K_IOWIRE", "K_COREWIRE", "K_BLOCKWIRE", "K_FILLWIRE",
  "K_BLOCKAGEWIRE", "K_PADRING", "K_BLOCKRING", "K_BLOCKAGES",
  "K_PLACEMENT", "K_SLOTS", "K_FILLS", "K_PUSHDOWN", "K_NETLIST", "K_DIST",
  "K_USER", "K_TIMING", "K_BALANCED", "K_STEINER", "K_TRUNK",
  "K_FIXEDBUMP", "K_FENCE", "K_FREQUENCY", "K_GUIDE", "K_MAXBITS",
  "K_PARTITION", "K_TYPE", "K_ANTENNAMODEL", "K_DRCFILL", "K_OXIDE1",
  "K_OXIDE2", "K_OXIDE3", "K_OXIDE4", "K_CUTSIZE", "K_CUTSPACING",
  "K_DESIGNRULEWIDTH", "K_DIAGWIDTH", "K_ENCLOSURE", "K_HALO",
  "K_GROUNDSENSITIVITY", "K_HARDSPACING", "K_LAYERS", "K_MINCUTS",
  "K_NETEXPR", "K_OFFSET", "K_ORIGIN", "K_ROWCOL", "K_STYLES", "K_POLYGON",
  "K_PORT", "K_SUPPLYSENSITIVITY", "K_VIA", "K_VIARULE", "K_WIREEXT",
  "K_EXCEPTPGNET", "K_FILLWIREOPC", "K_OPC", "K_PARTIAL", "K_ROUTEHALO",
  "';'", "'-'", "'+'", "'('", "')'", "'*'", "','", "$accept", "def_file",
  "version_stmt", "$@1", "case_sens_stmt", "rules", "rule",
  "design_section", "design_name", "$@2", "end_design", "tech_name", "$@3",
  "array_name", "$@4", "floorplan_name", "$@5", "history",
  "prop_def_section", "$@6", "property_defs", "property_def", "$@7", "$@8",
  "$@9", "$@10", "$@11", "$@12", "$@13", "$@14", "$@15",
  "property_type_and_val", "$@16", "$@17", "opt_num_val", "units",
  "divider_char", "bus_bit_chars", "canplace", "$@18", "cannotoccupy",
  "$@19", "orient", "die_area", "$@20", "pin_cap_rule", "start_def_cap",
  "pin_caps", "pin_cap", "end_def_cap", "pin_rule", "start_pins", "pins",
  "pin", "$@21", "$@22", "$@23", "pin_options", "pin_option", "$@24",
  "$@25", "$@26", "$@27", "$@28", "$@29", "$@30", "$@31", "$@32", "$@33",
  "pin_layer_mask_opt", "pin_via_mask_opt", "pin_poly_mask_opt",
  "pin_layer_spacing_opt", "pin_poly_spacing_opt", "pin_oxide", "use_type",
  "pin_layer_opt", "$@34", "end_pins", "row_rule", "$@35", "$@36",
  "row_do_option", "row_step_option", "row_options", "row_option", "$@37",
  "row_prop_list", "row_prop", "tracks_rule", "$@38", "track_start",
  "track_type", "track_opts", "track_mask_statement", "same_mask",
  "track_layer_statement", "$@39", "track_layers", "track_layer",
  "gcellgrid", "extension_section", "extension_stmt", "via_section", "via",
  "via_declarations", "via_declaration", "$@40", "$@41", "layer_stmts",
  "layer_stmt", "$@42", "$@43", "$@44", "$@45", "$@46", "$@47",
  "layer_viarule_opts", "$@48", "firstPt", "nextPt", "otherPts", "pt",
  "mask", "via_end", "regions_section", "regions_start", "regions_stmts",
  "regions_stmt", "$@49", "$@50", "rect_list", "region_options",
  "region_option", "$@51", "region_prop_list", "region_prop",
  "region_type", "comps_maskShift_section", "comps_section", "start_comps",
  "layer_statement", "maskLayer", "comps_rule", "comp", "comp_start",
  "comp_id_and_name", "$@52", "comp_net_list", "comp_options",
  "comp_option", "comp_extension_stmt", "comp_eeq", "$@53",
  "comp_generate", "$@54", "opt_pattern", "comp_source", "source_type",
  "comp_region", "comp_pnt_list", "comp_halo", "$@55", "halo_soft",
  "comp_routehalo", "$@56", "comp_property", "$@57", "comp_prop_list",
  "comp_prop", "comp_region_start", "comp_foreign", "$@58", "opt_paren",
  "comp_type", "maskShift", "$@59", "placement_status", "weight",
  "end_comps", "nets_section", "start_nets", "net_rules", "one_net",
  "net_and_connections", "net_start", "$@60", "net_name", "$@61", "$@62",
  "net_connections", "net_connection", "$@63", "$@64", "$@65", "conn_opt",
  "net_options", "net_option", "$@66", "$@67", "$@68", "$@69", "$@70",
  "$@71", "$@72", "$@73", "$@74", "$@75", "$@76", "net_prop_list",
  "net_prop", "netsource_type", "vpin_stmt", "$@77", "vpin_begin", "$@78",
  "vpin_layer_opt", "$@79", "vpin_options", "vpin_status", "net_type",
  "paths", "new_path", "$@80", "path", "$@81", "$@82", "virtual_statement",
  "rect_statement", "path_item_list", "path_item", "$@83", "$@84",
  "path_pt", "virtual_pt", "rect_pts", "opt_taper_style_s",
  "opt_taper_style", "opt_taper", "$@85", "opt_style", "opt_spaths",
  "opt_shape_style", "end_nets", "shape_type", "snets_section",
  "snet_rules", "snet_rule", "snet_options", "snet_option",
  "snet_other_option", "$@86", "$@87", "$@88", "$@89", "$@90", "$@91",
  "$@92", "$@93", "$@94", "$@95", "orient_pt", "shield_layer", "$@96",
  "snet_width", "$@97", "snet_voltage", "$@98", "snet_spacing", "$@99",
  "$@100", "snet_prop_list", "snet_prop", "opt_snet_range", "opt_range",
  "pattern_type", "spaths", "snew_path", "$@101", "spath", "$@102",
  "$@103", "width", "start_snets", "end_snets", "groups_section",
  "groups_start", "group_rules", "group_rule", "start_group", "$@104",
  "group_members", "group_member", "group_options", "group_option",
  "$@105", "$@106", "group_region", "group_prop_list", "group_prop",
  "group_soft_options", "group_soft_option", "groups_end",
  "assertions_section", "constraint_section", "assertions_start",
  "constraints_start", "constraint_rules", "constraint_rule",
  "operand_rule", "operand", "$@107", "$@108", "operand_list",
  "wiredlogic_rule", "$@109", "opt_plus", "delay_specs", "delay_spec",
  "constraints_end", "assertions_end", "scanchains_section",
  "scanchain_start", "scanchain_rules", "scan_rule", "start_scan", "$@110",
  "scan_members", "opt_pin", "scan_member", "$@111", "$@112", "$@113",
  "$@114", "$@115", "$@116", "opt_common_pins", "floating_inst_list",
  "one_floating_inst", "$@117", "floating_pins", "ordered_inst_list",
  "one_ordered_inst", "$@118", "ordered_pins", "partition_maxbits",
  "scanchain_end", "iotiming_section", "iotiming_start", "iotiming_rules",
  "iotiming_rule", "start_iotiming", "$@119", "iotiming_members",
  "iotiming_member", "$@120", "$@121", "iotiming_drivecell_opt", "$@122",
  "$@123", "iotiming_frompin", "$@124", "iotiming_parallel", "risefall",
  "iotiming_end", "floorplan_contraints_section", "fp_start", "fp_stmts",
  "fp_stmt", "$@125", "$@126", "h_or_v", "constraint_type",
  "constrain_what_list", "constrain_what", "$@127", "$@128",
  "row_or_comp_list", "row_or_comp", "$@129", "$@130",
  "timingdisables_section", "timingdisables_start", "timingdisables_rules",
  "timingdisables_rule", "$@131", "$@132", "$@133", "$@134",
  "td_macro_option", "$@135", "$@136", "$@137", "timingdisables_end",
  "partitions_section", "partitions_start", "partition_rules",
  "partition_rule", "start_partition", "$@138", "turnoff", "turnoff_setup",
  "turnoff_hold", "partition_members", "partition_member", "$@139",
  "$@140", "$@141", "$@142", "$@143", "$@144", "minmaxpins", "$@145",
  "min_or_max_list", "min_or_max_member", "pin_list",
  "risefallminmax1_list", "risefallminmax1", "risefallminmax2_list",
  "risefallminmax2", "partitions_end", "comp_names", "comp_name", "$@146",
  "subnet_opt_syn", "subnet_options", "subnet_option", "$@147", "$@148",
  "subnet_type", "pin_props_section", "begin_pin_props", "opt_semi",
  "end_pin_props", "pin_prop_list", "pin_prop_terminal", "$@149", "$@150",
  "pin_prop_options", "pin_prop", "$@151", "pin_prop_name_value_list",
  "pin_prop_name_value", "blockage_section", "blockage_start",
  "blockage_end", "blockage_defs", "blockage_def", "blockage_rule",
  "$@152", "$@153", "$@154", "layer_blockage_rules", "layer_blockage_rule",
  "mask_blockage_rule", "comp_blockage_rule", "$@155",
  "placement_comp_rules", "placement_comp_rule", "$@156",
  "rectPoly_blockage_rules", "rectPoly_blockage", "$@157", "slot_section",
  "slot_start", "slot_end", "slot_defs", "slot_def", "slot_rule", "$@158",
  "$@159", "geom_slot_rules", "geom_slot", "$@160", "fill_section",
  "fill_start", "fill_end", "fill_defs", "fill_def", "$@161", "$@162",
  "fill_rule", "$@163", "$@164", "geom_fill_rules", "geom_fill", "$@165",
  "fill_layer_mask_opc_opt", "opt_mask_opc_l", "fill_layer_opc",
  "fill_via_pt", "fill_via_mask_opc_opt", "opt_mask_opc", "fill_via_opc",
  "fill_mask", "fill_viaMask", "nondefaultrule_section",
  "nondefault_start", "nondefault_end", "nondefault_defs",
  "nondefault_def", "$@166", "$@167", "nondefault_options",
  "nondefault_option", "$@168", "$@169", "$@170", "$@171", "$@172",
  "nondefault_layer_options", "nondefault_layer_option",
  "nondefault_prop_opt", "$@173", "nondefault_prop_list",
  "nondefault_prop", "styles_section", "styles_start", "styles_end",
  "styles_rules", "styles_rule", "$@174", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,    59,    45,    43,    40,
      41,    42,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   273,   274,   275,   276,   275,   277,   277,   277,   278,
     278,   278,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   279,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   282,   281,   283,   285,   284,   287,   286,   289,   288,
     290,   292,   291,   293,   293,   295,   294,   296,   294,   297,
     294,   298,   294,   299,   294,   300,   294,   301,   294,   302,
     294,   303,   294,   294,   305,   304,   306,   304,   304,   304,
     304,   307,   307,   308,   309,   310,   312,   311,   314,   313,
     315,   315,   315,   315,   315,   315,   315,   315,   317,   316,
     318,   319,   320,   320,   321,   322,   323,   324,   325,   325,
     327,   328,   329,   326,   330,   330,   331,   331,   331,   331,
     332,   331,   333,   331,   331,   331,   334,   335,   331,   336,
     337,   331,   338,   331,   331,   331,   331,   331,   331,   339,
     331,   340,   331,   331,   341,   331,   331,   342,   342,   343,
     343,   344,   344,   345,   345,   345,   346,   346,   346,   347,
     347,   347,   347,   348,   348,   348,   348,   348,   348,   348,
     348,   349,   350,   349,   351,   353,   354,   352,   355,   355,
     356,   356,   357,   357,   359,   358,   360,   360,   361,   361,
     361,   363,   362,   364,   365,   365,   366,   367,   367,   368,
     368,   369,   370,   369,   371,   371,   372,   373,   374,   375,
     376,   377,   378,   378,   380,   381,   379,   382,   382,   384,
     383,   385,   386,   383,   387,   383,   388,   389,   383,   383,
     383,   390,   390,   390,   391,   390,   392,   393,   394,   394,
     395,   395,   395,   395,   396,   396,   397,   398,   399,   400,
     400,   402,   403,   401,   404,   404,   405,   405,   407,   406,
     406,   408,   408,   409,   409,   409,   410,   410,   411,   412,
     413,   414,   414,   415,   416,   416,   417,   418,   420,   419,
     421,   421,   421,   422,   422,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   424,   426,   425,
     428,   427,   429,   429,   430,   431,   431,   431,   431,   432,
     432,   433,   433,   435,   434,   436,   436,   438,   437,   440,
     439,   441,   441,   442,   442,   442,   443,   445,   444,   446,
     446,   447,   447,   447,   449,   448,   450,   450,   450,   451,
     452,   453,   454,   455,   455,   456,   457,   459,   458,   461,
     460,   462,   460,   463,   463,   465,   464,   466,   464,   467,
     464,   468,   468,   468,   469,   469,   471,   470,   470,   470,
     472,   470,   473,   470,   470,   470,   470,   470,   470,   470,
     474,   470,   470,   475,   470,   476,   477,   470,   478,   479,
     480,   470,   481,   470,   470,   482,   482,   483,   483,   483,
     484,   484,   484,   484,   484,   486,   485,   488,   487,   489,
     490,   489,   491,   491,   492,   492,   492,   493,   493,   493,
     494,   494,   496,   495,   498,   499,   497,   500,   501,   502,
     502,   503,   503,   503,   503,   503,   503,   503,   503,   503,
     503,   504,   503,   505,   503,   503,   506,   506,   506,   506,
     506,   506,   506,   506,   507,   507,   507,   507,   508,   509,
     509,   510,   510,   511,   512,   511,   513,   514,   514,   515,
     515,   516,   517,   517,   517,   517,   517,   517,   517,   517,
     517,   517,   517,   517,   518,   519,   519,   520,   521,   521,
     522,   522,   522,   522,   523,   524,   523,   525,   526,   523,
     523,   523,   527,   528,   523,   529,   523,   530,   531,   523,
     523,   523,   523,   532,   523,   523,   523,   523,   523,   523,
     533,   523,   523,   534,   534,   534,   534,   534,   534,   534,
     534,   534,   535,   536,   535,   538,   537,   540,   539,   542,
     543,   541,   544,   544,   545,   545,   545,   546,   546,   547,
     547,   548,   548,   548,   548,   549,   549,   551,   550,   553,
     554,   552,   555,   556,   557,   558,   559,   560,   560,   561,
     563,   562,   564,   564,   565,   566,   566,   567,   568,   567,
     569,   567,   567,   570,   570,   571,   571,   572,   572,   572,
     573,   573,   574,   574,   574,   575,   576,   577,   578,   579,
     580,   580,   581,   581,   582,   584,   583,   585,   583,   583,
     583,   586,   586,   586,   588,   587,   589,   589,   590,   590,
     591,   591,   591,   591,   592,   593,   594,   595,   596,   596,
     597,   599,   598,   600,   600,   601,   601,   603,   602,   604,
     602,   605,   602,   606,   602,   607,   602,   608,   602,   602,
     609,   609,   609,   610,   610,   612,   611,   613,   613,   613,
     613,   614,   614,   616,   615,   617,   617,   617,   617,   618,
     618,   619,   620,   621,   622,   622,   623,   625,   624,   626,
     626,   627,   627,   627,   628,   629,   627,   627,   631,   632,
     630,   633,   634,   633,   635,   635,   636,   636,   637,   638,
     639,   640,   640,   642,   643,   641,   644,   644,   645,   645,
     645,   645,   646,   646,   648,   647,   649,   647,   650,   650,
     652,   651,   653,   651,   654,   655,   656,   656,   658,   659,
     657,   660,   657,   661,   657,   657,   663,   664,   662,   665,
     662,   666,   667,   668,   669,   669,   670,   672,   671,   673,
     673,   674,   674,   674,   675,   675,   675,   676,   676,   678,
     677,   679,   677,   680,   677,   681,   677,   682,   677,   683,
     677,   677,   685,   684,   686,   686,   687,   687,   688,   688,
     689,   689,   690,   690,   690,   690,   691,   691,   692,   692,
     692,   692,   693,   694,   694,   696,   695,   697,   697,   698,
     698,   700,   699,   701,   699,   702,   702,   702,   702,   703,
     704,   705,   705,   706,   707,   707,   709,   710,   708,   711,
     711,   713,   712,   714,   714,   715,   715,   715,   716,   717,
     718,   719,   719,   720,   722,   723,   721,   724,   721,   725,
     725,   726,   726,   726,   726,   727,   729,   728,   728,   728,
     728,   728,   730,   730,   732,   731,   731,   731,   731,   733,
     733,   734,   735,   734,   736,   737,   738,   739,   739,   740,
     742,   743,   741,   744,   744,   745,   746,   745,   747,   748,
     749,   750,   750,   751,   752,   753,   751,   755,   756,   754,
     757,   757,   758,   759,   758,   760,   760,   761,   761,   762,
     763,   764,   764,   765,   765,   766,   767,   768,   769,   770,
     771,   772,   772,   774,   775,   773,   776,   776,   777,   778,
     779,   777,   780,   777,   781,   777,   782,   777,   777,   783,
     783,   784,   784,   784,   786,   785,   787,   787,   788,   788,
     788,   789,   790,   791,   792,   792,   794,   793
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     0,     0,     4,     0,     3,     3,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     2,     0,     4,     0,     4,     0,     4,
       1,     0,     5,     0,     2,     0,     5,     0,     5,     0,
       5,     0,     5,     0,     5,     0,     5,     0,     5,     0,
       5,     0,     5,     2,     0,     4,     0,     4,     1,     2,
       2,     0,     1,     5,     3,     3,     0,    14,     0,    14,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       3,     2,     0,     2,     5,     2,     3,     3,     0,     2,
       0,     0,     0,    10,     0,     2,     2,     1,     3,     3,
       0,     4,     0,     4,     3,     2,     0,     0,     9,     0,
       0,    11,     0,     9,     3,     4,     4,     4,     4,     0,
       6,     0,     6,     4,     0,     6,     3,     0,     2,     0,
       2,     0,     2,     0,     2,     2,     0,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     0,     3,     2,     0,     0,    11,     0,     5,
       0,     3,     0,     2,     0,     4,     0,     2,     2,     2,
       2,     0,     9,     2,     1,     1,     2,     0,     3,     0,
       1,     0,     0,     4,     0,     2,     1,     8,     1,     2,
       3,     3,     0,     2,     0,     0,     6,     0,     2,     0,
       7,     0,     0,    10,     0,     4,     0,     0,    24,     1,
       1,     4,     4,     6,     0,     4,     1,     1,     0,     2,
       4,     4,     4,     4,     0,     3,     2,     4,     3,     0,
       2,     0,     0,     7,     2,     3,     0,     2,     0,     4,
       3,     0,     2,     2,     2,     2,     1,     1,     3,     3,
       3,     0,     2,     1,     0,     2,     3,     2,     0,     4,
       0,     2,     2,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     5,     0,     1,     3,     1,     1,     1,     1,     2,
       2,     2,     3,     0,     8,     0,     1,     0,     6,     0,
       4,     1,     2,     2,     2,     2,     2,     0,     6,     1,
       2,     3,     2,     4,     0,     4,     2,     2,     2,     3,
       2,     3,     3,     0,     2,     3,     1,     0,     3,     0,
       3,     0,     6,     0,     2,     0,     6,     0,     6,     0,
       6,     0,     1,     2,     0,     2,     0,     4,     3,     2,
       0,     4,     0,     4,     3,     3,     3,     3,     3,     3,
       0,     4,     1,     0,     4,     0,     0,     5,     0,     0,
       0,     8,     0,     4,     1,     1,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     0,     6,     0,     4,     0,
       0,     3,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     0,     3,     0,     0,     6,     2,     2,     0,
       2,     1,     3,     2,     4,    10,     8,     9,    11,     1,
       1,     0,    10,     0,     4,     1,     4,     4,     4,     4,
       5,     5,     5,     5,     4,     4,     4,     4,     6,     0,
       2,     1,     1,     1,     0,     3,     2,     0,     2,     3,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     2,     3,     0,     2,
       1,     1,     1,     1,     2,     0,     4,     0,     0,     6,
       3,     3,     0,     0,     9,     0,     6,     0,     0,     8,
       3,     2,     3,     0,     4,     3,     3,     3,     3,     3,
       0,     4,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     0,     2,     0,     5,     0,     4,     0,
       0,     7,     1,     2,     2,     2,     2,     0,     3,     0,
       3,     1,     1,     1,     1,     1,     2,     0,     3,     0,
       0,     7,     1,     3,     2,     3,     3,     0,     2,     4,
       0,     3,     0,     2,     1,     0,     2,     3,     0,     4,
       0,     4,     1,     2,     1,     0,     2,     2,     2,     2,
       0,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       0,     2,     1,     1,     4,     0,     3,     0,     6,     4,
       4,     1,     2,     3,     0,     8,     0,     1,     0,     2,
       3,     3,     3,     3,     2,     2,     3,     3,     0,     2,
       3,     0,     3,     0,     2,     0,     1,     0,     5,     0,
       4,     0,     4,     0,     5,     0,     4,     0,     5,     1,
       0,     4,     8,     0,     2,     0,     3,     0,     4,     8,
      12,     0,     2,     0,     3,     0,     4,     8,    12,     0,
       2,     2,     3,     3,     0,     2,     3,     0,     6,     0,
       2,     5,     5,     3,     0,     0,     6,     1,     0,     0,
       6,     0,     0,     3,     0,     2,     1,     1,     2,     4,
       3,     0,     2,     0,     0,     8,     1,     1,     1,     2,
       2,     2,     0,     2,     0,     4,     0,     4,     0,     2,
       0,     5,     0,     5,     3,     3,     0,     2,     0,     0,
      10,     0,     6,     0,     6,     3,     0,     0,     6,     0,
       3,     2,     3,     3,     0,     2,     3,     0,     4,     0,
       3,     0,     1,     1,     0,     1,     1,     0,     2,     0,
       7,     0,     6,     0,     5,     0,     7,     0,     6,     0,
       5,     1,     0,     4,     0,     2,     3,     3,     0,     2,
       0,     2,     2,     2,     2,     2,     1,     2,     3,     3,
       3,     3,     2,     0,     2,     0,     6,     0,     2,     0,
       2,     0,     3,     0,     3,     1,     1,     1,     1,     3,
       3,     0,     1,     2,     0,     2,     0,     0,     7,     0,
       2,     0,     4,     0,     2,     2,     2,     2,     3,     3,
       2,     0,     2,     4,     0,     0,     6,     0,     4,     0,
       2,     3,     3,     1,     1,     3,     0,     4,     2,     2,
       2,     2,     0,     2,     0,     4,     2,     2,     3,     0,
       2,     3,     0,     6,     3,     3,     2,     0,     2,     3,
       0,     0,     6,     0,     2,     3,     0,     6,     3,     3,
       2,     0,     2,     3,     0,     0,     8,     0,     0,     7,
       0,     2,     3,     0,     6,     0,     2,     1,     1,     2,
       2,     0,     2,     1,     1,     2,     3,     3,     4,     3,
       2,     0,     2,     0,     0,     6,     0,     2,     2,     0,
       0,     8,     0,     4,     0,     4,     0,     5,     1,     0,
       2,     2,     2,     2,     0,     4,     0,     2,     2,     2,
       2,     3,     3,     2,     0,     2,     0,     8
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       3,     4,     0,     6,     0,     1,     0,     0,     0,     0,
       0,    11,     0,     5,     7,     8,    60,    51,     0,    54,
       0,    56,    58,    96,    98,   108,     0,     0,     0,     0,
     185,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,   218,   281,
       0,     0,     0,     0,     0,    10,    12,    38,     2,    48,
      34,    41,    43,    46,    50,    40,    35,    36,    37,    39,
      44,   112,    45,   118,    47,    49,     0,    42,    17,    33,
     222,    27,   259,    19,    15,   284,    23,   353,    30,   495,
      21,   577,    13,    16,   610,   610,    28,   638,    22,   684,
      20,   711,    32,   736,    25,   754,    26,   824,    14,   841,
      29,   877,    18,   891,    24,     0,    31,   954,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   111,   204,
     205,   203,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    53,     0,     0,     0,     0,     0,     0,
      63,     0,   821,     0,     0,     0,     0,     0,     0,   201,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   923,   921,     0,
       0,   221,     0,     0,     0,     0,     0,     0,     0,     0,
     246,   117,     0,     0,   280,   258,   352,   573,   919,   576,
     609,   637,   608,   683,   735,   753,   710,    94,    95,     0,
     283,   278,   282,   822,   820,   839,   875,   889,   952,     0,
       0,   113,   110,     0,   120,   119,   116,     0,     0,   224,
     223,   220,     0,   261,   260,     0,   288,   285,   293,   290,
     279,     0,   357,   354,   374,   356,   351,     0,   498,   496,
     494,     0,   580,   578,   582,   575,     0,     0,   611,   612,
     613,   606,     0,   607,     0,   641,   639,   643,   636,     0,
       0,   685,   689,   682,     0,   713,   712,     0,     0,   737,
     734,     0,   757,   755,   767,   752,     0,   826,   819,   825,
       0,     0,   838,   842,     0,     0,     0,   874,   878,   883,
       0,     0,   888,   892,   900,     0,     0,     0,     0,   951,
     955,    52,    55,     0,    57,    59,     0,     0,     0,     0,
     248,   247,     0,     0,     0,    65,    77,    71,    81,    73,
      67,     0,    75,    69,    79,    64,     0,   115,   184,     0,
       0,   256,     0,   257,     0,   350,     0,     0,   287,   481,
       0,     0,   574,     0,   605,     0,   585,   635,   615,   617,
       0,     0,   624,   628,   634,   681,     0,     0,   708,   687,
       0,   709,     0,   751,   738,   741,   743,     0,   802,     0,
       0,   823,     0,   840,   844,   847,     0,   872,   869,   876,
     880,     0,   890,   897,   894,     0,   924,     0,   918,   922,
     953,     0,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    83,     0,     0,     0,     0,     0,     0,    62,
       0,     0,     0,     0,     0,     0,   225,   262,     0,   286,
       0,   307,   294,   306,   302,   295,   296,   301,   303,   304,
     305,     0,   300,   297,   299,     0,   298,   292,   291,   359,
       0,   358,   355,     0,   404,   375,   392,   419,   497,     0,
     532,   499,   503,   500,   501,   502,   581,   584,   583,     0,
       0,     0,     0,     0,     0,     0,   642,   640,     0,   659,
     644,     0,   686,     0,   697,   690,     0,     0,     0,     0,
     745,   759,   756,     0,   781,   768,     0,     0,   862,     0,
       0,     0,     0,     0,   886,   879,   884,     0,     0,     0,
     903,   893,   901,   926,   920,   956,   100,   102,   103,   101,
     104,   107,   106,   105,     0,     0,   250,   252,   251,   253,
     109,   249,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   227,     0,   289,   310,
       0,     0,   308,   346,   347,   342,   348,   337,   336,   329,
     219,   344,   323,     0,   320,     0,   319,     0,   363,     0,
       0,     0,   427,   428,   382,     0,     0,     0,     0,   429,
     390,   417,   398,     0,   402,   393,   395,   379,   380,   376,
     420,     0,   515,     0,     0,   523,     0,     0,     0,     0,
       0,   545,   547,   549,   530,     0,   507,   521,     0,   512,
     517,   504,   579,     0,   592,   586,   616,     0,   621,     0,
       0,   626,   614,     0,   629,   647,   649,   651,   653,   655,
     657,     0,   706,   707,     0,   694,     0,   716,   717,   714,
       0,     0,     0,   761,   758,   769,   771,   773,   775,   777,
     779,   827,   845,   848,   871,     0,   843,   870,   881,     0,
       0,   898,   895,     0,     0,     0,     0,     0,     0,     0,
     186,    88,    86,    84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   114,   121,   207,     0,     0,   266,
       0,   315,   316,   317,   318,   314,   349,     0,     0,     0,
       0,     0,   325,   327,   321,     0,   341,   360,   361,   414,
     410,   411,   412,   413,   378,   385,     0,   173,   174,   175,
     176,   177,   178,   179,   180,   388,   389,   564,   561,   562,
     563,   384,   387,     0,     0,     0,   386,     0,     0,   396,
       0,     0,     0,     0,     0,   520,   526,     0,   528,   529,
     525,   527,   482,   483,   484,   485,   486,   487,   488,   491,
     492,   493,   490,   489,   510,     0,     0,     0,     0,   511,
       0,   522,     0,     0,     0,   590,   600,   588,     0,   619,
       0,   622,   620,   627,     0,     0,     0,     0,     0,     0,
     663,   671,     0,   660,     0,     0,   693,     0,     0,     0,
       0,     0,     0,   746,   749,     0,   762,   763,   764,     0,
       0,     0,     0,     0,     0,   829,   849,     0,   863,     0,
       0,   885,     0,   905,   911,   902,     0,   925,     0,   927,
     938,     0,     0,     0,   217,   188,    89,   559,   559,    90,
      66,    78,    72,    82,    74,    68,    76,    70,    80,     0,
       0,     0,   211,   226,     0,   240,   228,   239,   264,     0,
       0,   312,   309,   343,     0,     0,   330,   331,   345,   326,
       0,     0,   322,     0,   364,     0,   383,   391,   418,   399,
       0,   403,   405,   394,     0,   381,   434,   377,   430,   421,
     415,     0,   524,     0,   548,     0,     0,   531,   552,   508,
     513,   533,   569,   506,   565,     0,   587,   595,     0,   623,
       0,   630,   631,   632,   633,   645,   650,   652,   645,     0,
     656,   679,   688,   695,     0,     0,   718,     0,     0,     0,
     722,   739,   742,     0,     0,   744,   765,   766,   760,     0,
       0,   790,     0,     0,   790,     0,   846,   867,   864,   866,
       0,   248,   882,     0,     0,     0,     0,   929,   944,   928,
     936,   932,   934,   248,     0,     0,     0,   192,     0,    91,
      91,   122,   209,   202,   212,   206,   229,   244,   234,     0,
       0,     0,   231,   236,   265,   263,     0,   267,   313,   311,
       0,   339,     0,   334,   335,   333,   332,     0,     0,   365,
     369,   367,     0,   803,   408,   409,   407,   406,   397,   469,
     432,   431,   422,     0,   546,   550,   555,   556,   554,   553,
     542,     0,   534,   536,   537,   535,   538,   541,   540,   539,
     518,     0,   567,   566,   594,     0,   591,     0,     0,     0,
     601,   589,   618,     0,   646,   648,   665,   664,   673,   672,
     654,     0,     0,   658,   701,   691,   692,   720,   719,   721,
       0,     0,     0,   750,     0,     0,   774,     0,     0,   780,
     828,     0,   830,     0,   850,   853,   854,     0,   868,   873,
     248,     0,   899,   906,   907,   908,     0,   248,     0,   912,
     913,   914,   248,     0,   946,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    92,    87,    85,   124,   210,   208,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   268,
       0,   340,   338,     0,   328,     0,     0,     0,   362,   400,
       0,     0,   425,   426,   424,   416,     0,   516,   557,   509,
       0,     0,     0,   572,   477,     0,   593,   602,   603,   604,
       0,   596,   625,   667,   675,     0,   680,   702,   696,     0,
     715,     0,   723,     0,   747,   784,     0,     0,     0,     0,
     772,   796,     0,     0,     0,     0,   791,   784,   778,   831,
       0,   856,     0,   858,   859,   860,     0,   861,   865,   887,
       0,   909,     0,   915,   910,   896,   904,     0,   945,     0,
     933,   935,   957,     0,     0,     0,   187,     0,   193,   560,
       0,   216,   214,   254,   245,   235,     0,   242,   241,   254,
       0,   271,   276,   277,   270,     0,   371,   371,   371,   805,
     809,   804,     0,   473,   474,     0,   435,   470,   472,   471,
     433,     0,     0,   551,   544,     0,   248,     0,   568,   598,
     599,   597,     0,   666,     0,   674,   661,     0,   698,   724,
     726,     0,     0,   770,     0,     0,     0,     0,     0,   797,
     792,   794,   793,   795,   776,   833,   851,     0,   855,   852,
     916,   917,     0,     0,   947,   937,     0,     0,   190,   194,
     123,     0,   125,   127,     0,   213,   214,     0,     0,     0,
     232,     0,   269,   324,     0,   372,     0,     0,     0,     0,
     401,   476,     0,     0,     0,   439,   423,     0,   248,   519,
       0,   570,   478,     0,     0,     0,   703,     0,   728,   728,
     740,   748,   782,     0,     0,   785,   798,   800,   799,   801,
     832,   857,   930,   949,   950,   948,     0,     0,     0,   189,
     196,   136,     0,   126,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   132,     0,   139,   135,   130,   142,
       0,   215,     0,     0,   243,     0,     0,     0,   272,   373,
     366,   370,   368,     0,   815,   816,   817,   813,   818,   810,
     811,   475,     0,     0,     0,     0,   436,   558,   514,     0,
       0,   439,     0,     0,     0,   699,   725,   727,   788,     0,
       0,     0,   834,   939,    97,    99,     0,   195,     0,   134,
     128,   181,   181,   181,   181,     0,     0,   181,     0,   169,
     170,   171,   172,   156,     0,   129,     0,     0,     0,   144,
     255,   230,     0,     0,   274,   275,   273,   807,     0,     0,
       0,   456,     0,   458,     0,   457,     0,   459,   441,     0,
       0,     0,   449,   450,   440,   455,   480,   479,   571,   668,
     676,     0,   704,     0,   729,   783,   786,   787,   836,   837,
     835,   931,   191,     0,   197,   137,   182,   145,   146,   147,
     148,   149,   151,   153,   154,   133,   140,   131,   159,     0,
       0,     0,     0,   814,   812,   460,   462,   461,   463,     0,
     443,     0,   438,   453,     0,   437,     0,     0,   662,     0,
     700,   732,   730,   789,     0,     0,     0,   940,   199,   200,
     198,   157,     0,     0,     0,     0,   161,     0,     0,   248,
       0,   808,   806,     0,     0,     0,   442,   451,     0,     0,
       0,     0,     0,   705,     0,     0,   942,   941,   943,     0,
     163,   183,   150,   152,   155,     0,   166,   160,     0,   233,
     237,     0,     0,     0,     0,   444,     0,   454,     0,     0,
       0,     0,     0,     0,     0,     0,   158,     0,     0,     0,
     162,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   464,   466,   465,   467,   669,   677,   733,   731,
     164,   165,     0,   167,   168,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   138,     0,   143,     0,
       0,     0,   468,     0,     0,     0,     0,     0,   248,     0,
     446,     0,     0,     0,     0,     0,     0,   141,     0,   447,
       0,     0,     0,   670,   678,     0,   445,     0,   452,     0,
     448,     0,     0,     0,     0,     0,     0,   238
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     7,    12,    55,    56,    57,   118,
      58,    59,   120,    60,   122,    61,   123,    62,    63,   150,
     209,   335,   413,   418,   421,   415,   417,   420,   414,   422,
     416,   675,   838,   837,  1105,    64,    65,    66,    67,   124,
      68,   125,   524,    69,   126,    70,    71,   157,   221,   222,
      72,    73,   158,   225,   339,   849,  1107,  1210,  1292,  1437,
    1434,  1418,  1531,  1436,  1536,  1438,  1533,  1534,  1535,  1560,
    1538,  1566,  1589,  1593,  1433,   725,  1487,  1532,   226,    74,
     133,   835,   967,  1349,  1102,  1208,  1350,  1417,  1484,    75,
     227,    76,   131,   851,   852,  1109,   975,  1110,  1295,  1296,
      77,    78,  1305,    79,    80,   160,   230,   342,   546,   687,
     856,  1111,  1117,  1375,  1113,  1118,  1595,   857,  1112,   189,
     531,   409,   321,  1298,   231,    81,    82,   161,   234,   344,
     547,   689,   860,   987,  1221,  1302,  1378,  1224,    83,    84,
      85,   151,   212,   162,   237,   238,   239,   346,   348,   347,
     432,   433,   434,   697,   435,   690,   989,   436,   695,   437,
     566,   438,   702,   870,   439,   871,   440,   700,   866,   867,
     441,   442,   699,   992,   443,   444,   701,   445,   446,   240,
      86,    87,   163,   243,   244,   245,   350,   451,   568,   875,
     707,   874,  1125,  1127,  1126,  1306,   351,   455,   741,   740,
     716,   733,   738,   739,   884,   735,  1003,  1230,   737,   881,
     882,   714,   456,  1012,   457,   734,   591,   742,  1135,  1136,
     589,   887,  1011,  1131,   888,  1009,  1315,  1462,  1463,  1396,
    1464,  1576,  1548,  1465,  1515,  1512,  1130,  1237,  1238,  1312,
    1239,  1247,  1322,   246,   764,    88,   164,   249,   353,   461,
     462,   774,   770,  1020,   772,  1021,   744,   773,  1142,   747,
     768,  1030,  1139,  1140,   463,   765,   464,   766,   465,   767,
    1138,   897,   898,  1243,   969,   731,   903,  1033,  1145,   904,
    1031,  1401,  1144,    89,   250,    90,    91,   165,   253,   254,
     355,   356,   468,   469,   615,   907,   905,  1036,  1041,  1151,
     906,  1040,   255,    92,    93,    94,    95,   166,   258,   259,
     618,   470,   471,   619,   260,   474,   784,   475,   624,   263,
     261,    96,    97,   168,   266,   267,   366,   367,  1045,   480,
     789,   790,   791,   792,   793,   794,   920,   916,  1047,  1153,
    1253,   917,  1049,  1154,  1255,  1053,   268,    98,    99,   169,
     271,   272,   481,   370,   485,   797,  1054,  1158,  1327,  1472,
    1159,  1257,  1520,   636,   273,   100,   101,   170,   276,   372,
     800,   639,   930,  1060,  1162,  1328,  1329,  1406,  1474,  1555,
    1554,   102,   103,   171,   279,   487,  1061,   488,   489,   805,
     933,  1262,   934,   280,   104,   105,   172,   283,   284,   379,
     644,   808,   938,   380,   495,   809,   810,   811,   812,   813,
     814,  1263,  1408,  1264,  1335,  1475,  1066,  1176,  1170,  1171,
     285,  1129,  1231,  1309,  1502,  1310,  1389,  1449,  1448,  1390,
     106,   107,   214,   288,   173,   289,   382,   815,   945,  1072,
    1275,  1340,  1412,   108,   109,   292,   174,   293,   294,   497,
     816,   498,   946,  1074,  1075,  1076,  1277,   653,   818,  1077,
     501,   388,   500,   110,   111,   297,   175,   298,   299,   502,
     820,   391,   506,   660,   112,   113,   302,   176,   303,   508,
     824,   304,   507,   823,   395,   512,   664,   954,  1083,  1084,
    1088,   955,  1089,  1090,  1085,  1091,   114,   115,   398,   306,
     178,   305,   513,   665,   829,  1093,  1413,  1096,  1097,  1095,
    1481,  1527,   830,  1094,  1198,  1284,   116,   117,   309,   179,
     310,   666
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1119
static const yytype_int16 yypact[] =
{
     -94, -1119,   102,   119,   207, -1119,    77,   489,  -104,   -49,
     -37, -1119,   666, -1119, -1119, -1119, -1119, -1119,   227, -1119,
     161, -1119, -1119, -1119, -1119, -1119,   256,   310,   148,   148,
   -1119,   327,   337,   359,   379,   401,   451,   461,   498,   510,
     366,   529,   530,   545,   547,   551,   552, -1119, -1119, -1119,
     550,   554,   555,   559,   560, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119,   564, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119,   290, -1119, -1119,   568,   307,
     570,   480,   572,   573,   574,   576,   312,   317, -1119, -1119,
   -1119, -1119,   578,   583,   322,   324,   325,   326,   328,   329,
     332,   344,   345, -1119,   346,   347,   348,   349,   350,   360,
   -1119,    26,   361,   362,   363,   365,   367,    74,   -29, -1119,
     -13,    -9,    -8,    -2,     4,    41,    43,    47,    50,    51,
      55,    58,    59,    60,    61,    62,    63, -1119, -1119,    64,
     368, -1119,   371,   587,   372,   374,   635,   636,    11,   312,
   -1119, -1119,   618,   642, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,   385,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,   641,
     628, -1119, -1119,   633, -1119, -1119, -1119,   629,   643, -1119,
   -1119, -1119,   613, -1119, -1119,   638, -1119, -1119, -1119, -1119,
   -1119,   624, -1119, -1119, -1119, -1119, -1119,   616, -1119, -1119,
   -1119,   602, -1119, -1119, -1119, -1119,   579,    57, -1119, -1119,
   -1119, -1119,   599, -1119,   601, -1119, -1119, -1119, -1119,   590,
     419, -1119, -1119, -1119,   544, -1119, -1119,   585,   -18, -1119,
   -1119,   584, -1119, -1119, -1119, -1119,   514, -1119, -1119, -1119,
     485,    35, -1119, -1119,    34,   486,   677, -1119, -1119, -1119,
     492,    44, -1119, -1119, -1119,   711,    65,   464,   671, -1119,
   -1119, -1119, -1119,   455, -1119, -1119,   716,   717,    12,    13,
   -1119, -1119,   719,   721,   462, -1119, -1119, -1119, -1119, -1119,
   -1119,   567, -1119, -1119, -1119, -1119,   708, -1119, -1119,   727,
     726, -1119,   730, -1119,   732, -1119,   733,  -186,     9, -1119,
      97,   -95, -1119,   -76, -1119,   735,   736, -1119, -1119, -1119,
     473,   475, -1119, -1119, -1119, -1119,   741,   -58, -1119, -1119,
     -44, -1119,   743, -1119, -1119, -1119, -1119,   482, -1119,   745,
     -23, -1119,   746, -1119, -1119, -1119,   312, -1119, -1119, -1119,
   -1119,   -14, -1119, -1119, -1119,     2, -1119,   691, -1119, -1119,
   -1119,   747, -1119,   274,   274,   484,   487,   488,   490,  -141,
     725,   749, -1119,   752,   760,   763,   764,   766,   767, -1119,
     768,   770,   771,   772,   509,   753, -1119, -1119,   777, -1119,
      21, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119,    16, -1119, -1119, -1119,   312, -1119, -1119, -1119, -1119,
     513, -1119, -1119,   665, -1119, -1119, -1119,   755, -1119,   179,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,   116,
     780,   781,   198,   198,   782,   229, -1119, -1119,    24, -1119,
   -1119,   786, -1119,    79, -1119, -1119,   223,   787,   788,   789,
   -1119,   683, -1119,     1, -1119, -1119,   791,   792, -1119,   312,
     312,    15,   793,   312, -1119, -1119, -1119,   794,   795,   312,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119,   775,   776, -1119, -1119, -1119, -1119,
   -1119, -1119,   796,   274,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   537,   728,   799, -1119,   312, -1119, -1119,
     158,   800, -1119, -1119, -1119,   312, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119,   801, -1119,   312,   312,   274, -1119,   804,
    -101,   803, -1119, -1119, -1119,   285,   805,   -50,   806, -1119,
   -1119, -1119, -1119,   808, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119,   312, -1119,   158,   809, -1119,   285,   810,   -50,   811,
     395, -1119, -1119, -1119, -1119,   812, -1119, -1119,   813, -1119,
   -1119,   816, -1119,    52, -1119, -1119, -1119,   817, -1119,   -28,
      -3,   542, -1119,   300, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119,   818, -1119, -1119,   819, -1119,    83, -1119, -1119, -1119,
     820,   826,    85,   281, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119,   566, -1119,   312, -1119, -1119, -1119,   312,
     312, -1119, -1119,   312,   312,   253,   312,   829,   830,   571,
   -1119,   836, -1119, -1119,   837,   580,   581,   582,   588,   589,
     591,   592,   593,   594, -1119, -1119,   648,   260,   312,   312,
     838, -1119, -1119, -1119, -1119, -1119, -1119,   840,   274,   845,
     846,   849,   769, -1119, -1119,   312, -1119,   595, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119,   852, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119,   857,   858,   859, -1119,   861,   862, -1119,
     863,   864,   866,   312,   867, -1119, -1119,   868, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119,   869,   870,   871,   872, -1119,
     873, -1119,   875,   876,   878, -1119, -1119, -1119,   881, -1119,
     198, -1119, -1119, -1119,   797,   880,   882,   884,   885,   889,
   -1119, -1119,   892,   630,   893,   631, -1119,   894,   896,   897,
     245,   802,   634, -1119, -1119,   639, -1119, -1119,   272,   900,
     902,   904,   906,   907,   908, -1119, -1119,   -25, -1119,   312,
      48, -1119,   312, -1119, -1119, -1119,   312, -1119,    14, -1119,
   -1119,   312,   887,   888, -1119,   890, -1119,   773,   773, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,   912,
     911,   652,   895, -1119,    54, -1119, -1119, -1119, -1119,   312,
     261,   917, -1119, -1119,    32,    93,   846, -1119, -1119, -1119,
     916,   920, -1119,     7, -1119,   921, -1119, -1119, -1119, -1119,
     106,   861, -1119, -1119,   864, -1119, -1119,   874, -1119, -1119,
   -1119,   312, -1119,   922, -1119,   923,   412,   872, -1119, -1119,
   -1119,   557, -1119,   877, -1119,    18,   369, -1119,   927, -1119,
     926, -1119, -1119, -1119, -1119,   929,   930,   931,   929,   932,
   -1119,   695, -1119, -1119,   933,   934, -1119,   935,   936,   937,
   -1119, -1119, -1119,   940,   941, -1119, -1119, -1119, -1119,   942,
     943, -1119,   944,   945, -1119,   273,   669, -1119, -1119, -1119,
     946, -1119, -1119,   312,   -15,   143,   312, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119,   947,   949,   950, -1119,   951,   952,
     952, -1119,   783, -1119, -1119, -1119, -1119, -1119, -1119,   953,
     954,   956, -1119, -1119, -1119, -1119,  -122, -1119, -1119, -1119,
     957, -1119,   274, -1119, -1119, -1119, -1119,   958,   961, -1119,
   -1119, -1119,   668, -1119, -1119, -1119, -1119, -1119,   874, -1119,
   -1119, -1119,   399,   312, -1119, -1119, -1119, -1119, -1119, -1119,
     962,   312, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119,   963, -1119, -1119, -1119,   312, -1119,   964,   965,   966,
   -1119,   969, -1119,   684, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119,   970,   971, -1119,   847, -1119, -1119, -1119, -1119, -1119,
     276,   972,   879, -1119,   321,   315,   390,   321,   315,   390,
   -1119,   814, -1119,   149, -1119, -1119, -1119,   974, -1119,   312,
   -1119,  -123, -1119, -1119, -1119, -1119,   -98, -1119,   702, -1119,
   -1119, -1119, -1119,   975, -1119,   977,   978,   979,  -125,   948,
     959,   967,   279,   981, -1119, -1119, -1119, -1119, -1119, -1119,
     984,   985,   986,   987,   988,   989,   990,   993,   994, -1119,
     318, -1119, -1119,   995, -1119,   996,   998,   999, -1119,   723,
      -5,   864, -1119, -1119, -1119, -1119,   312, -1119,   839, -1119,
     878,   312,   312, -1119, -1119,   878, -1119, -1119, -1119, -1119,
     450, -1119, -1119,   737,   738,   729, -1119, -1119, -1119,   899,
   -1119,   277, -1119,  1001, -1119, -1119,  1002,  1003,  1005,  1006,
     315, -1119,  1007,  1008,  1009,  1011, -1119, -1119,   315, -1119,
    1012, -1119,  1013, -1119, -1119, -1119,  1014, -1119, -1119,   312,
    1015, -1119,  1016, -1119,   312, -1119,   312,   968,  1019,  1020,
   -1119, -1119, -1119,  1021,  1022,  1023, -1119,   865, -1119, -1119,
     284, -1119,   984,   757, -1119, -1119,  1024, -1119, -1119,   757,
     765, -1119, -1119, -1119, -1119,  1026,   774,   774,   774, -1119,
   -1119, -1119,  1028, -1119, -1119,    17, -1119, -1119, -1119, -1119,
   -1119,   274,  1029, -1119,   877,   312, -1119,   159, -1119, -1119,
   -1119, -1119,  1032, -1119,  1033, -1119,   778,  1034, -1119, -1119,
   -1119,   779,  1035, -1119,    49,  1037,  1038,  1040,  1042, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119,  1036, -1119, -1119,
   -1119, -1119,  1043,   456, -1119, -1119,  1044,  1045,  1025, -1119,
   -1119,   167, -1119, -1119,   312, -1119,   984,   886,   312,  1047,
   -1119,   822,  1050, -1119,     5, -1119,   790,   798,   807,  1052,
      33, -1119,  1053,    19,    20, -1119, -1119,  1057, -1119,   312,
     131, -1119, -1119,  1055,  1060,  1061, -1119,  1062, -1119, -1119,
   -1119, -1119, -1119,  1063,  1064, -1119, -1119, -1119, -1119, -1119,
    1067, -1119, -1119, -1119, -1119, -1119,   815,   821,  1066, -1119,
   -1119, -1119,   285, -1119,  1069,  1068,  1070,  1072,  1073,  1074,
    1076,  1077,  1078,   255, -1119,  1082, -1119, -1119, -1119, -1119,
     274, -1119,  1080,   312, -1119,   312,  1083,   460, -1119, -1119,
   -1119, -1119, -1119,  1071, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119,    27,    28,    29,    30,    10, -1119,   312,  1084,
     395, -1119,   823,   824,  1087, -1119,   828,   828, -1119,  1086,
    1089,   511, -1119, -1119, -1119, -1119,  1092,  1095,  1096, -1119,
   -1119,  1039,  1039,  1039,  1039,  1075,  1079,  1039,  1081, -1119,
   -1119, -1119, -1119, -1119,  1097, -1119,  1098,  1100,  1101, -1119,
   -1119, -1119,   312,  1102, -1119, -1119, -1119,   842,  1107,   864,
     843, -1119,   844, -1119,   848, -1119,   850, -1119,   384,   853,
    1106,   854, -1119, -1119, -1119, -1119, -1119, -1119,    10,   855,
     856,   851,   982,    40, -1119,  1111, -1119, -1119, -1119, -1119,
   -1119,   -11, -1119,   519, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,   955,   312,
     860,   915,   883, -1119,   874, -1119, -1119, -1119, -1119,  1110,
    1094,  1120, -1119,    94,    22, -1119,  1113,  1123, -1119,  1125,
   -1119, -1119, -1119, -1119,  1126,  1127,  1128, -1119, -1119, -1119,
   -1119,   960,  1132,  1133,  1134,  1135,   973,  1136,   891, -1119,
     898, -1119, -1119,  1103,  1138,  1139,   408, -1119,   901,    23,
      25,  1137,  1143, -1119,  1145,  1146, -1119, -1119, -1119,  1148,
     -19, -1119, -1119, -1119, -1119,  1149,     8, -1119,  1150,   312,
   -1119,  1151,  1114,  1152,  1153,  1140,   905, -1119,   903,   909,
     910,   913,   914,   918,   919,   924, -1119,  1155,  1156,   312,
   -1119,  1157,  1158,   312,  1160,  1147,  1142,  1161,  1165,  1159,
    1169,  1170, -1119, -1119, -1119, -1119,   928,   938, -1119, -1119,
   -1119, -1119,   312, -1119, -1119,   312,   925,  1173,  1172,  1154,
     939,  1176,  1164,  1180,  1183,  1187, -1119,   312, -1119,  1188,
    1190,  1192, -1119,  1166,  1193,  1194,  1197,  1198, -1119,   976,
   -1119,  1199,  1200,  1177,  1202,   980,   983,   312,   991, -1119,
    1204,  1205,   992, -1119, -1119,  1206, -1119,  1207, -1119,  1208,
   -1119,   997,  1004,  1209,  1210,  1211,  1212, -1119
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119,   123, -1119, -1119,   136, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119,  -403, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119,  -591, -1072, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119,  1174, -1119, -1119, -1119, -1119, -1119,  -144,   109,
   -1119, -1119,  -343, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,  -497,
    -187,  -942,  -126,     3, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,   627, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,   355,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119,    31, -1119, -1119,
   -1119, -1119, -1119, -1119,  1059, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119,  -717, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
     343, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
     784,  -878, -1119, -1119,    95, -1119, -1119, -1119, -1119,  -176,
   -1119, -1119, -1119, -1118, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119,  -173, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119,   331, -1119,   391,   632,    91, -1119, -1119,    88,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119,  1141, -1119, -1119,
    -250, -1119, -1119,   761, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,   319, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119,  -865, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119,   -91, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119,    68, -1119, -1119, -1119, -1119,   291, -1119,   171, -1089,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119,   739, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119,   422, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119,   292, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
    1000, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119, -1119,
   -1119, -1119
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -544
static const yytype_int16 yytable[] =
{
     190,   525,   320,   655,   431,   748,  1008,   363,   454,  1079,
     460,   999,  1236,   447,  1458,   509,   503,   318,   405,   407,
     564,  1098,  1034,  1313,   479,  1392,  1394,   484,  1549,  1578,
     210,  1580,   509,  1450,  1452,  1454,  1456,   494,   990,  1587,
    1459,   727,   957,  1232,  1119,   386,   947,  1524,   358,   359,
     360,   361,  1190,   549,   550,   551,   552,   553,   554,   555,
     556,   557,   558,   384,   386,     1,  1591,   223,  1332,  1384,
    1385,  1521,   393,   358,   359,   360,   361,  1192,   503,   709,
     429,  1269,   430,   228,   976,  1386,   374,   232,   235,  1269,
     375,   376,  1387,   775,   241,   219,   993,   994,  1546,   995,
     247,   449,     5,   977,   978,   625,   626,   627,   628,  1004,
    1005,  1120,  1006,   645,   646,   647,   648,   649,   650,   710,
     711,   712,   713,   776,  1547,   530,   614,     6,   188,  1321,
     670,  1379,  1000,   358,   359,   360,   361,   251,  1189,   256,
    1191,  1202,   450,   262,   188,  1194,   264,   269,   362,   948,
    1196,   274,  1233,  1234,   277,   281,   286,   290,   295,   300,
     307,   397,    13,   822,   706,  1193,   377,   826,   560,   831,
     220,   452,   560,   453,   728,   729,   730,   632,   633,  1399,
     958,   634,   635,   798,   799,  1460,  1400,   559,   560,   803,
     458,   560,   459,   804,   949,  1351,  1522,   561,  1461,  1165,
    1333,  1334,  1177,   553,   554,   629,   556,  1180,   477,   592,
     478,     8,   593,   594,  1352,   572,   573,    14,   777,   560,
    1388,   560,   482,  1588,   483,   595,   596,   597,   598,    15,
     599,   579,  1525,   119,   600,   601,   602,   603,   224,   950,
     510,   504,   779,   492,   780,   493,   560,     9,    10,  1526,
    1592,   385,   505,  1081,   229,   121,   630,   510,   233,   236,
     499,   959,   127,   960,  1235,   242,   562,   782,   511,   780,
     387,   242,   961,   962,   358,   359,   360,   361,  1001,  1235,
     448,   656,   319,   406,   408,   188,   563,   188,  1314,   387,
    1393,  1395,   211,  1550,  1579,   863,  1581,  1451,  1453,  1455,
    1457,   188,   394,   504,  1319,   979,   980,   981,   252,   982,
     257,  1353,  1354,   983,   257,   565,   128,   265,   270,   567,
     129,   130,   275,  1181,  1182,   278,   282,   287,   291,   296,
     301,   308,   177,   134,   560,   516,   517,   518,   519,   520,
     521,   522,   523,   135,   855,   604,   560,   671,   672,   673,
    1488,  1489,  1490,   674,   605,  1493,  1355,  1356,  1357,  1358,
    1359,  1360,  1361,  1362,   606,   136,  1183,  1184,  1185,   781,
     781,   637,   638,   654,   190,   143,  1398,   659,   691,   692,
     693,   694,   612,   663,   613,   137,   324,   785,   786,   787,
     788,  1186,   936,   937,   325,   926,   927,   928,   929,   806,
     807,  1363,  1166,  1167,  1168,  1169,   607,   138,   608,  1509,
    1187,  1086,   188,  1364,   326,  1016,  1017,  1365,  1018,   632,
     633,   688,  1366,  1367,  1368,  1369,   327,  1320,  1235,   698,
    1577,  1259,  1260,  1574,   609,  1132,  1133,   610,  1134,   704,
     705,  1037,  1038,  1039,   328,   516,   517,   518,   519,   520,
     521,   522,   523,  1249,  1250,   329,  1251,   139,  1087,  1343,
    1344,   330,  1345,  1444,  1445,   743,  1446,   140,   819,   516,
     517,   518,   519,   520,   521,   522,   523,  1172,  1173,  1174,
    1175,   331,   717,   718,   719,   720,   721,   722,   723,   724,
      11,  1429,  1430,  1431,  1432,   622,    -9,   623,    -9,    -9,
      -9,    -9,    -9,    -9,   141,    -9,    -9,    -9,    -9,    -9,
    1307,  1308,    -9,    -9,  1478,  1479,   142,  1480,    -9,   827,
      -9,   828,  1528,  1529,  1141,  1530,   853,   985,   854,   986,
     909,    -9,    -9,   821,   190,   144,   145,   825,   190,  1070,
     190,  1071,  1160,    -9,  1161,  1206,  1222,  1207,  1223,    -9,
    1290,   146,  1291,   147,   148,   149,   152,   177,    -9,   332,
     153,   154,   858,   859,    -9,   155,   156,   333,   334,    -9,
     159,  1504,   180,   181,   182,   183,   184,   185,   186,   872,
     187,   188,    -9,   191,   192,    -9,    -9,   193,   194,  1122,
     195,   196,   197,   313,   198,   199,    -9,  1569,   200,    -9,
     752,   753,   754,   755,   756,   757,   758,   759,   760,   761,
     201,   202,   203,   204,   205,   206,   207,   890,  1022,  1023,
    1024,  1025,  1026,  1027,  1028,  1029,   208,   213,   215,   216,
     762,   217,   951,   218,   311,   953,    -9,   312,   314,   956,
     315,   316,   317,   322,   963,  1246,   323,   336,   337,    -9,
      -9,    -9,   338,   341,   340,   343,    -9,   763,   676,   677,
     678,   679,   680,   681,   682,   683,    -9,   349,    -9,   345,
     352,   354,   357,    16,   364,    17,    18,    19,    20,    21,
      22,   365,    23,    24,    25,    26,    27,   368,   369,    28,
      29,   371,   373,   381,   378,    30,  1647,    31,   570,   571,
     383,   572,   573,   389,    -9,   390,    -9,    -9,    32,    33,
     392,   574,   575,   576,   577,   396,   578,   579,   400,   401,
      34,   402,   403,   404,   580,   410,    35,   411,   412,   419,
     423,   424,   425,   984,   426,    36,   427,   428,   991,   466,
     467,    37,   472,    -9,   473,   476,    38,   486,   490,   491,
     496,   514,   532,   515,   526,   533,   534,   527,   528,    39,
     529,  1419,    40,    41,   535,  1013,  1080,   536,   537,  1092,
     538,   539,   540,    42,   541,   542,    43,   544,   543,  1035,
     545,   548,   569,   590,   616,   617,   621,   581,   582,   583,
     631,   640,   641,   642,   643,   651,   652,   658,   661,   662,
     667,   668,   669,   684,   685,   686,   696,   703,   708,   715,
     783,   726,   732,    44,   736,   746,   749,   751,   769,   771,
    -505,   778,   795,   850,   801,   796,    45,    46,    47,   190,
     802,   584,   560,    48,   817,   832,   833,   834,  1316,   836,
     869,   839,   861,    49,   862,    50,   840,   841,   842,   864,
     865,   585,   586,   868,   843,   844,   876,   845,   846,   847,
     848,   877,   878,   879,   873,   880,   883,  1293,   886,   885,
     889,   891,   892,   893,   894,   895,   896,   899,  1442,   900,
     901,    51,   902,    52,    53,   908,   911,  1137,   912,   910,
     913,   914,   587,   915,   588,   190,   918,   921,   923,   919,
     932,   922,   924,   925,   939,   935,   940,   931,   941,  1146,
     942,   943,   944,   964,   965,   966,   971,   972,   973,   968,
      54,   988,   997,   974,   998,  1002,  1052,  1010,  1014,  1015,
    1032,  1042,  1043,  1044,  1046,  1048,  1051,  1073,  1128,  1055,
    1056,  1057,  1058,  1059,  1062,  1063,  1064,  1065,  1067,  1068,
    1152,  1157,  1078,  1099,  1245,  1100,  1101,  1103,  1104,  1114,
    1115,  1108,  1116,  1121,  1123,  1124,  -543,  1439,  1195,  1143,
    1147,  1148,  1149,  1150,  1155,  1203,  1163,  1156,  1188,  1197,
    1179,  1199,  1200,  1201,  1164,  1242,  1204,  1209,  1211,  1213,
    1214,  1215,  1229,  1205,  1216,  1217,  1218,  1219,  1220,  1256,
    1226,  1225,  1227,  1228,  1258,  1261,  1252,  1254,  1265,  1266,
    1241,  1267,  1268,  1270,  1271,  1272,   190,  1273,  1276,  1278,
    1279,  1280,  1281,  1283,  1282,  1297,  1285,  1286,  1287,  1288,
    1299,  1289,  1303,  1301,  1311,  1317,  1323,  1324,  1326,  1331,
    1341,  1541,  1304,  1336,  1337,  1330,  1338,  1325,  1339,  1342,
    1346,  1347,  1348,  1374,  1377,  1510,  1383,  1391,  1318,  1402,
    1380,  1372,  1376,  1397,  1403,  1404,  1405,  1486,  1381,  1409,
    1410,  1411,  1416,  1420,  1421,  1447,  1422,  1382,  1423,  1424,
    1425,  1414,  1426,  1427,  1428,  1435,  1440,  1415,  1519,  1443,
    1466,  1471,  1476,  1469,  1470,  1477,  1615,  1473,  1482,  1483,
    1485,  1495,  1496,  1491,  1497,  1498,  1106,  1492,  1500,  1494,
    1501,  1503,  1513,  1505,  1506,  1523,  1543,  1551,  1507,  1544,
    1508,  1518,  1511,  1514,  1516,  1517,  1545,  1552,  1540,  1571,
    1537,  1553,  1556,  1557,  1558,  1559,  1561,  1562,  1563,  1564,
    1597,  1582,  1567,  1575,  1572,  1573,  1570,  1583,  1565,  1584,
    1585,  1617,  1371,  1542,  1586,  1590,  1594,  1596,  1598,  1599,
    1568,  1610,  1611,  1613,  1614,  1600,  1616,  1619,  1370,  1618,
    1235,  1620,  1373,  1602,  1601,  1622,  1623,  1629,  1630,  1603,
    1604,  1631,  1633,  1605,  1606,  1621,  1635,  1636,  1607,  1608,
    1634,  1637,  1639,  1642,  1609,  1628,  1640,  1624,  1641,  1643,
    1644,  1645,  1646,   132,  1651,  1649,  1650,  1625,  1652,  1632,
    1656,  1657,  1659,  1660,  1661,  1664,  1665,  1666,  1667,  1212,
     745,   996,  1300,   248,  1007,  1468,  1240,  1467,  1019,   970,
     750,  1244,  1655,  1248,   620,  1069,   167,  1050,  1407,  1178,
     657,  1294,   952,   611,  1648,  1274,  1082,  1441,  1663,   190,
    1653,     0,     0,  1654,     0,  1499,     0,     0,     0,     0,
       0,     0,  1658,     0,     0,  1662,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   399,     0,     0,     0,
       0,     0,  1539,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1627,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1638,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1612,     0,     0,     0,   190,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1626
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-1119))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     126,   404,   189,   500,   347,   596,   884,   257,   351,   951,
     353,     4,  1130,     4,     4,    30,    30,     6,     6,     6,
       4,   963,     4,     6,   367,     6,     6,   370,     6,     6,
       4,     6,    30,     6,     6,     6,     6,   380,     6,    58,
      30,    91,    28,    48,   166,    30,    71,    58,    76,    77,
      78,    79,   175,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    28,    30,   159,    58,    96,    19,    36,
      37,    31,    28,    76,    77,    78,    79,   175,    30,   180,
     266,  1170,   268,    96,    30,    52,   104,    96,    96,  1178,
     108,   109,    59,    41,    96,    21,     3,     4,     4,     6,
      96,     4,     0,    49,    50,    81,    82,    83,    84,     3,
       4,   233,     6,   112,   113,   114,   115,   116,   117,   220,
     221,   222,   223,    71,    30,   266,   469,     8,   269,  1247,
     533,   126,   125,    76,    77,    78,    79,    96,  1080,    96,
     263,   266,    45,    96,   269,  1087,    96,    96,    91,   174,
    1092,    96,   157,   158,    96,    96,    96,    96,    96,    96,
      96,    96,   266,   660,   567,   263,   184,   664,   167,   666,
      96,   266,   167,   268,   224,   225,   226,    98,    99,    48,
     166,   102,   103,   100,   101,   175,    55,   166,   167,   104,
     266,   167,   268,   108,   219,    28,   156,   176,   188,  1064,
     151,   152,  1067,    36,    37,   181,    39,    58,   266,    30,
     268,     4,    33,    34,    47,    36,    37,   266,   166,   167,
     187,   167,   266,   242,   268,    46,    47,    48,    49,   266,
      51,    52,   243,     6,    55,    56,    57,    58,   267,   264,
     255,   255,   270,   266,   272,   268,   167,   170,   171,   260,
     242,   216,   266,   268,   267,    94,   232,   255,   267,   267,
     386,   247,     6,   249,   269,   267,   245,   270,   266,   272,
     255,   267,   258,   259,    76,    77,    78,    79,   271,   269,
     271,   266,   271,   271,   271,   269,   265,   269,   271,   255,
     271,   271,   266,   271,   271,   698,   271,   270,   270,   270,
     270,   269,   258,   255,  1246,   251,   252,   253,   267,   255,
     267,   144,   145,   259,   267,   441,     6,   267,   267,   445,
     172,   173,   267,   174,   175,   267,   267,   267,   267,   267,
     267,   267,   267,     6,   167,    61,    62,    63,    64,    65,
      66,    67,    68,     6,   687,   166,   167,   163,   164,   165,
    1422,  1423,  1424,   169,   175,  1427,   189,   190,   191,   192,
     193,   194,   195,   196,   185,     6,   217,   218,   219,   619,
     620,   148,   149,   499,   500,     9,  1318,   503,   220,   221,
     222,   223,   266,   509,   268,     6,     1,    87,    88,    89,
      90,   242,   120,   121,     9,   150,   151,   152,   153,   118,
     119,   234,    87,    88,    89,    90,   227,     6,   229,    25,
     261,   268,   269,   246,    29,     3,     4,   250,     6,    98,
      99,   547,   255,   256,   257,   258,    41,   268,   269,   555,
    1548,   154,   155,    25,   255,    36,    37,   258,    39,   565,
     566,    72,    73,    74,    59,    61,    62,    63,    64,    65,
      66,    67,    68,     3,     4,    70,     6,     6,   955,     3,
       4,    76,     6,     3,     4,   591,     6,     6,   655,    61,
      62,    63,    64,    65,    66,    67,    68,    87,    88,    89,
      90,    96,   197,   198,   199,   200,   201,   202,   203,   204,
       1,   236,   237,   238,   239,   266,     7,   268,     9,    10,
      11,    12,    13,    14,     6,    16,    17,    18,    19,    20,
    1227,  1228,    23,    24,     3,     4,     6,     6,    29,   266,
      31,   268,     3,     4,  1021,     6,   266,   266,   268,   268,
     780,    42,    43,   659,   660,     6,     6,   663,   664,   266,
     666,   268,   266,    54,   268,   266,   228,   268,   230,    60,
     266,     6,   268,     6,     3,     3,     6,   267,    69,   174,
       6,     6,   688,   689,    75,     6,     6,   182,   183,    80,
       6,  1449,     4,   266,     4,    95,     4,     4,     4,   705,
       4,   269,    93,   266,     6,    96,    97,     4,   266,   992,
     266,   266,   266,     6,   266,   266,   107,  1539,   266,   110,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     266,   266,   266,   266,   266,   266,   266,   743,    61,    62,
      63,    64,    65,    66,    67,    68,   266,   266,   266,   266,
     235,   266,   819,   266,   266,   822,   147,   266,   266,   826,
     266,     6,     6,    25,   831,  1142,     4,     6,    20,   160,
     161,   162,    19,    10,    25,    42,   167,   262,   535,   536,
     537,   538,   539,   540,   541,   542,   177,    43,   179,    31,
      54,    69,    93,     7,    75,     9,    10,    11,    12,    13,
      14,    80,    16,    17,    18,    19,    20,    97,   269,    23,
      24,   147,   107,   179,   110,    29,  1638,    31,    33,    34,
     215,    36,    37,   217,   215,    28,   217,   218,    42,    43,
     218,    46,    47,    48,    49,     4,    51,    52,   254,    48,
      54,   266,     6,     6,    59,     6,    60,     6,   266,   162,
      22,     4,     6,   859,     4,    69,     4,     4,   864,     4,
       4,    75,   269,   254,   269,     4,    80,     4,   266,     4,
       4,    60,    27,     6,   270,     6,     4,   270,   270,    93,
     270,  1352,    96,    97,     4,   891,   953,     4,     4,   956,
       4,     4,     4,   107,     4,     4,   110,   268,     6,   905,
      27,     4,   269,    28,     4,     4,     4,   122,   123,   124,
       4,     4,     4,     4,   111,     4,     4,     4,     4,     4,
      25,    25,     6,   266,    76,     6,     6,     6,     4,     6,
     268,     6,     6,   147,     6,     6,     6,     6,     6,     6,
       4,     4,     4,   175,     4,     6,   160,   161,   162,   955,
       4,   166,   167,   167,   268,     6,     6,   266,  1241,     3,
      71,     4,     4,   177,     4,   179,   266,   266,   266,     4,
       4,   186,   187,     4,   266,   266,     4,   266,   266,   266,
     266,     4,     4,     4,   269,     4,     4,  1210,     4,     6,
       4,     4,     4,     4,     4,     4,     4,     4,  1375,     4,
       4,   215,     4,   217,   218,     4,     6,  1013,     6,    92,
       6,     6,   227,     4,   229,  1021,     4,     4,     4,   269,
     266,   270,     6,     6,     4,   266,     4,   105,     4,  1035,
       4,     4,     4,    26,    26,    25,     4,     6,   266,   146,
     254,     4,     6,    28,     4,     4,   231,    53,     6,     6,
      53,     4,     6,     4,     4,     4,     4,   268,   270,     6,
       6,     6,     6,     6,     4,     4,     4,     4,     4,     4,
     266,   104,     6,     6,  1141,     6,     6,     6,     6,     6,
       6,   178,     6,     6,     6,     4,     4,  1370,   266,     6,
       6,     6,     6,     4,     4,    27,     4,     6,     4,     4,
     166,     4,     4,     4,   105,   146,    27,     6,     4,     4,
       4,     4,   269,    26,     6,     6,     6,     4,     4,   270,
       4,     6,     4,     4,   105,     4,   269,   269,     6,     6,
    1136,     6,     6,     6,     6,     6,  1142,     6,     6,     6,
       6,     6,     6,     4,    56,   268,     6,     6,     6,     6,
       6,   166,     6,   268,     6,     6,     4,     4,     4,     4,
       4,   126,   268,     6,     6,   266,     6,   269,     6,     6,
       6,     6,    27,     6,     4,  1458,     4,     4,  1245,     4,
     270,   175,   240,     6,     4,     4,     4,    28,   270,     6,
       6,     4,     6,     4,     6,     4,     6,   270,     6,     6,
       6,   266,     6,     6,     6,     3,     6,   266,   106,     6,
       6,     4,     6,   270,   270,     6,  1593,   269,     6,     4,
       4,     4,     4,    28,     4,     4,   970,    28,     6,    28,
     268,     4,     6,   270,   270,     4,     6,     4,   270,    25,
     270,   270,   269,   269,   269,   269,     6,     4,   268,    26,
     175,     6,     6,     6,     6,   175,     4,     4,     4,     4,
      26,     4,     6,  1546,     6,     6,   248,     4,   175,     4,
       4,     4,  1296,   270,     6,     6,     6,     6,     6,     6,
     269,     6,     6,     6,     6,    25,     6,     6,  1294,    27,
     269,     6,  1298,   270,   269,     6,     6,     4,     6,   270,
     270,    27,     6,   270,   270,    26,     6,     4,   270,   270,
      26,     4,     4,    27,   270,   270,     6,   269,     6,     6,
       6,     4,     4,    29,    27,     6,     6,   269,     6,   270,
       6,     6,     6,     6,     6,     6,     6,     6,     6,  1110,
     593,   866,  1219,   164,   881,  1401,  1131,  1400,   897,   838,
     598,  1140,   241,  1145,   473,   944,    95,   918,  1329,  1068,
     501,  1210,   820,   459,   268,  1177,   954,  1373,   244,  1375,
     270,    -1,    -1,   270,    -1,  1442,    -1,    -1,    -1,    -1,
      -1,    -1,   270,    -1,    -1,   268,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   306,    -1,    -1,    -1,
      -1,    -1,  1499,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1615,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1627,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1589,    -1,    -1,    -1,  1593,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1612
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   159,   274,   275,   276,     0,     8,   277,     4,   170,
     171,     1,   278,   266,   266,   266,     7,     9,    10,    11,
      12,    13,    14,    16,    17,    18,    19,    20,    23,    24,
      29,    31,    42,    43,    54,    60,    69,    75,    80,    93,
      96,    97,   107,   110,   147,   160,   161,   162,   167,   177,
     179,   215,   217,   218,   254,   279,   280,   281,   283,   284,
     286,   288,   290,   291,   308,   309,   310,   311,   313,   316,
     318,   319,   323,   324,   352,   362,   364,   373,   374,   376,
     377,   398,   399,   411,   412,   413,   453,   454,   518,   556,
     558,   559,   576,   577,   578,   579,   594,   595,   620,   621,
     638,   639,   654,   655,   667,   668,   703,   704,   716,   717,
     736,   737,   747,   748,   769,   770,   789,   790,   282,     6,
     285,    94,   287,   289,   312,   314,   317,     6,     6,   172,
     173,   365,   365,   353,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     9,     6,     6,     6,     6,     3,     3,
     292,   414,     6,     6,     6,     6,     6,   320,   325,     6,
     378,   400,   416,   455,   519,   560,   580,   580,   596,   622,
     640,   656,   669,   707,   719,   739,   750,   267,   773,   792,
       4,   266,     4,    95,     4,     4,     4,     4,   269,   392,
     395,   266,     6,     4,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   293,
       4,   266,   415,   266,   705,   266,   266,   266,   266,    21,
      96,   321,   322,    96,   267,   326,   351,   363,    96,   267,
     379,   397,    96,   267,   401,    96,   267,   417,   418,   419,
     452,    96,   267,   456,   457,   458,   516,    96,   457,   520,
     557,    96,   267,   561,   562,   575,    96,   267,   581,   582,
     587,   593,    96,   592,    96,   267,   597,   598,   619,    96,
     267,   623,   624,   637,    96,   267,   641,    96,   267,   657,
     666,    96,   267,   670,   671,   693,    96,   267,   706,   708,
      96,   267,   718,   720,   721,    96,   267,   738,   740,   741,
      96,   267,   749,   751,   754,   774,   772,    96,   267,   791,
     793,   266,   266,     6,   266,   266,     6,     6,     6,   271,
     393,   395,    25,     4,     1,     9,    29,    41,    59,    70,
      76,    96,   174,   182,   183,   294,     6,    20,    19,   327,
      25,    10,   380,    42,   402,    31,   420,   422,   421,    43,
     459,   469,    54,   521,    69,   563,   564,    93,    76,    77,
      78,    79,    91,   583,    75,    80,   599,   600,    97,   269,
     626,   147,   642,   107,   104,   108,   109,   184,   110,   672,
     676,   179,   709,   215,    28,   216,    30,   255,   734,   217,
      28,   744,   218,    28,   258,   757,     4,    96,   771,   773,
     254,    48,   266,     6,     6,     6,   271,     6,   271,   394,
       6,     6,   266,   295,   301,   298,   303,   299,   296,   162,
     300,   297,   302,    22,     4,     6,     4,     4,     4,   266,
     268,   375,   423,   424,   425,   427,   430,   432,   434,   437,
     439,   443,   444,   447,   448,   450,   451,     4,   271,     4,
      45,   460,   266,   268,   375,   470,   485,   487,   266,   268,
     375,   522,   523,   537,   539,   541,     4,     4,   565,   566,
     584,   585,   269,   269,   588,   590,     4,   266,   268,   375,
     602,   625,   266,   268,   375,   627,     4,   658,   660,   661,
     266,     4,   266,   268,   375,   677,     4,   722,   724,   395,
     735,   733,   742,    30,   255,   266,   745,   755,   752,    30,
     255,   266,   758,   775,    60,     6,    61,    62,    63,    64,
      65,    66,    67,    68,   315,   315,   270,   270,   270,   270,
     266,   393,    27,     6,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     6,   268,    27,   381,   403,     4,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,   166,
     167,   176,   245,   265,     4,   395,   433,   395,   461,   269,
      33,    34,    36,    37,    46,    47,    48,    49,    51,    52,
      59,   122,   123,   124,   166,   186,   187,   227,   229,   493,
      28,   489,    30,    33,    34,    46,    47,    48,    49,    51,
      55,    56,    57,    58,   166,   175,   185,   227,   229,   255,
     258,   493,   266,   268,   375,   567,     4,     4,   583,   586,
     586,     4,   266,   268,   591,    81,    82,    83,    84,   181,
     232,     4,    98,    99,   102,   103,   636,   148,   149,   644,
       4,     4,     4,   111,   673,   112,   113,   114,   115,   116,
     117,     4,     4,   730,   395,   392,   266,   734,     4,   395,
     746,     4,     4,   395,   759,   776,   794,    25,    25,     6,
     315,   163,   164,   165,   169,   304,   304,   304,   304,   304,
     304,   304,   304,   304,   266,    76,     6,   382,   395,   404,
     428,   220,   221,   222,   223,   431,     6,   426,   395,   445,
     440,   449,   435,     6,   395,   395,   315,   463,     4,   180,
     220,   221,   222,   223,   484,     6,   473,   197,   198,   199,
     200,   201,   202,   203,   204,   348,     6,    91,   224,   225,
     226,   548,     6,   474,   488,   478,     6,   481,   475,   476,
     472,   471,   490,   395,   529,   431,     6,   532,   348,     6,
     548,     6,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   235,   262,   517,   538,   540,   542,   533,     6,
     525,     6,   527,   530,   524,    41,    71,   166,     4,   270,
     272,   583,   270,   268,   589,    87,    88,    89,    90,   603,
     604,   605,   606,   607,   608,     4,     6,   628,   100,   101,
     643,     4,     4,   104,   108,   662,   118,   119,   674,   678,
     679,   680,   681,   682,   683,   710,   723,   268,   731,   393,
     743,   395,   392,   756,   753,   395,   392,   266,   268,   777,
     785,   392,     6,     6,   266,   354,     3,   306,   305,     4,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   328,
     175,   366,   367,   266,   268,   375,   383,   390,   395,   395,
     405,     4,     4,   315,     4,     4,   441,   442,     4,    71,
     436,   438,   395,   269,   464,   462,     4,     4,     4,     4,
       4,   482,   483,     4,   477,     6,     4,   494,   497,     4,
     395,     4,     4,     4,     4,     4,     4,   544,   545,     4,
       4,     4,     4,   549,   552,   569,   573,   568,     4,   583,
      92,     6,     6,     6,     6,     4,   610,   614,     4,   269,
     609,     4,   270,     4,     6,     6,   150,   151,   152,   153,
     645,   105,   266,   663,   665,   266,   120,   121,   675,     4,
       4,     4,     4,     4,     4,   711,   725,    71,   174,   219,
     264,   393,   745,   393,   760,   764,   393,    28,   166,   247,
     249,   258,   259,   393,    26,    26,    25,   355,   146,   547,
     547,     4,     6,   266,    28,   369,    30,    49,    50,   251,
     252,   253,   255,   259,   395,   266,   268,   406,     4,   429,
       6,   395,   446,     3,     4,     6,   442,     6,     4,     4,
     125,   271,     4,   479,     3,     4,     6,   483,   494,   498,
      53,   495,   486,   395,     6,     6,     3,     4,     6,   545,
     526,   528,    61,    62,    63,    64,    65,    66,    67,    68,
     534,   553,    53,   550,     4,   395,   570,    72,    73,    74,
     574,   571,     4,     6,     4,   601,     4,   611,     4,   615,
     601,     4,   231,   618,   629,     6,     6,     6,     6,     6,
     646,   659,     4,     4,     4,     4,   689,     4,     4,   689,
     266,   268,   712,   268,   726,   727,   728,   732,     6,   394,
     393,   268,   758,   761,   762,   767,   268,   392,   763,   765,
     766,   768,   393,   778,   786,   782,   780,   781,   394,     6,
       6,     6,   357,     6,     6,   307,   307,   329,   178,   368,
     370,   384,   391,   387,     6,     6,     6,   385,   388,   166,
     233,     6,   315,     6,     4,   465,   467,   466,   270,   694,
     509,   496,    36,    37,    39,   491,   492,   395,   543,   535,
     536,   392,   531,     6,   555,   551,   395,     6,     6,     6,
       4,   572,   266,   612,   616,     4,     6,   104,   630,   633,
     266,   268,   647,     4,   105,   636,    87,    88,    89,    90,
     691,   692,    87,    88,    89,    90,   690,   636,   691,   166,
      58,   174,   175,   217,   218,   219,   242,   261,     4,   394,
     175,   263,   175,   263,   394,   266,   394,     4,   787,     4,
       4,     4,   266,    27,    27,    26,   266,   268,   358,     6,
     330,     4,   372,     4,     4,     4,     6,     6,     6,     4,
       4,   407,   228,   230,   410,     6,     4,     4,     4,   269,
     480,   695,    48,   157,   158,   269,   506,   510,   511,   513,
     497,   395,   146,   546,   549,   393,   392,   514,   552,     3,
       4,     6,   269,   613,   269,   617,   270,   634,   105,   154,
     155,     4,   664,   684,   686,     6,     6,     6,     6,   692,
       6,     6,     6,     6,   684,   713,     6,   729,     6,     6,
       6,     6,    56,     4,   788,     6,     6,     6,     6,   166,
     266,   268,   331,   375,   450,   371,   372,   268,   396,     6,
     396,   268,   408,     6,   268,   375,   468,   468,   468,   696,
     698,     6,   512,     6,   271,   499,   315,     6,   393,   394,
     268,   506,   515,     4,     4,   269,     4,   631,   648,   649,
     266,     4,    19,   151,   152,   687,     6,     6,     6,     6,
     714,     4,     6,     3,     4,     6,     6,     6,    27,   356,
     359,    28,    47,   144,   145,   189,   190,   191,   192,   193,
     194,   195,   196,   234,   246,   250,   255,   256,   257,   258,
     395,   371,   175,   395,     6,   386,   240,     4,   409,   126,
     270,   270,   270,     4,    36,    37,    52,    59,   187,   699,
     702,     4,     6,   271,     6,   271,   502,     6,   394,    48,
      55,   554,     4,     4,     4,     4,   650,   650,   685,     6,
       6,     4,   715,   779,   266,   266,     6,   360,   334,   348,
       4,     6,     6,     6,     6,     6,     6,     6,     6,   236,
     237,   238,   239,   347,   333,     3,   336,   332,   338,   315,
       6,   395,   392,     6,     3,     4,     6,     4,   701,   700,
       6,   270,     6,   270,     6,   270,     6,   270,     4,    30,
     175,   188,   500,   501,   503,   506,     6,   517,   502,   270,
     270,     4,   632,   269,   651,   688,     6,     6,     3,     4,
       6,   783,     6,     4,   361,     4,    28,   349,   349,   349,
     349,    28,    28,   349,    28,     4,     4,     4,     4,   393,
       6,   268,   697,     4,   494,   270,   270,   270,   270,    25,
     315,   269,   508,     6,   269,   507,   269,   269,   270,   106,
     635,    31,   156,     4,    58,   243,   260,   784,     3,     4,
       6,   335,   350,   339,   340,   341,   337,   175,   343,   393,
     268,   126,   270,     6,    25,     6,     4,    30,   505,     6,
     271,     4,     4,     6,   653,   652,     6,     6,     6,   175,
     342,     4,     4,     4,     4,   175,   344,     6,   269,   394,
     248,    26,     6,     6,    25,   315,   504,   506,     6,   271,
       6,   271,     4,     4,     4,     4,     6,    58,   242,   345,
       6,    58,   242,   346,     6,   389,     6,    26,     6,     6,
      25,   269,   270,   270,   270,   270,   270,   270,   270,   270,
       6,     6,   395,     6,     6,   392,     6,     4,    27,     6,
       6,    26,     6,     6,   269,   269,   395,   393,   270,     4,
       6,    27,   270,     6,    26,     6,     4,     4,   393,     4,
       6,     6,    27,     6,     6,     4,     4,   394,   268,     6,
       6,    27,     6,   270,   270,   241,     6,     6,   270,     6,
       6,     6,   268,   244,     6,     6,     6,     6
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (defData, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, defData)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, defData); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, defrData *defData)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, defData)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    defrData *defData;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (defData);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, defrData *defData)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, defData)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    defrData *defData;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, defData);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, defrData *defData)
#else
static void
yy_reduce_print (yyvsp, yyrule, defData)
    YYSTYPE *yyvsp;
    int yyrule;
    defrData *defData;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , defData);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, defData); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, defrData *defData)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, defData)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    defrData *defData;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (defData);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (defrData *defData);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (defrData *defData)
#else
int
yyparse (defData)
    defrData *defData;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:

/* Line 1806 of yacc.c  */
#line 220 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 221 "def.y"
    {
        defData->VersionNum = defrData::convert_defname2num((yyvsp[(3) - (4)].string));
        if (defData->VersionNum > CURRENT_VERSION) {
          char temp[300];
          sprintf(temp,
          "The execution has been stopped because the DEF parser %.1f does not support DEF file with version %s.\nUpdate your DEF file to version 5.8 or earlier.",
                  CURRENT_VERSION, (yyvsp[(3) - (4)].string));
          defData->defError(6503, temp);
          return 1;
        }
        if (defData->callbacks->VersionStrCbk) {
          CALLBACK(defData->callbacks->VersionStrCbk, defrVersionStrCbkType, (yyvsp[(3) - (4)].string));
        } else if (defData->callbacks->VersionCbk) {
            CALLBACK(defData->callbacks->VersionCbk, defrVersionCbkType, defData->VersionNum);
        }
        if (defData->VersionNum > 5.3 && defData->VersionNum < 5.4)
          defData->defIgnoreVersion = 1;
        if (defData->VersionNum < 5.6)     // default to false before 5.6
          defData->names_case_sensitive = defData->session->reader_case_sensitive;
        else
          defData->names_case_sensitive = 1;
        defData->hasVer = 1;
        defData->doneDesign = 0;
    }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 248 "def.y"
    {
        if (defData->VersionNum < 5.6) {
          defData->names_case_sensitive = 1;
          if (defData->callbacks->CaseSensitiveCbk)
            CALLBACK(defData->callbacks->CaseSensitiveCbk, defrCaseSensitiveCbkType,
                     defData->names_case_sensitive); 
          defData->hasNameCase = 1;
        } else
          if (defData->callbacks->CaseSensitiveCbk) // write error only if cbk is set 
             if (defData->caseSensitiveWarnings++ < defData->settings->CaseSensitiveWarnings)
               defData->defWarning(7011, "The NAMESCASESENSITIVE statement is obsolete in version 5.6 and later.\nThe DEF parser will ignore this statement.");
      }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 261 "def.y"
    {
        if (defData->VersionNum < 5.6) {
          defData->names_case_sensitive = 0;
          if (defData->callbacks->CaseSensitiveCbk)
            CALLBACK(defData->callbacks->CaseSensitiveCbk, defrCaseSensitiveCbkType,
                     defData->names_case_sensitive);
          defData->hasNameCase = 1;
        } else {
          if (defData->callbacks->CaseSensitiveCbk) { // write error only if cbk is set 
            if (defData->caseSensitiveWarnings++ < defData->settings->CaseSensitiveWarnings) {
              defData->defError(6504, "Def parser version 5.7 and later does not support NAMESCASESENSITIVE OFF.\nEither remove this optional construct or set it to ON.");
              CHKERR();
            }
          }
        }
      }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 301 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 302 "def.y"
    {
            if (defData->callbacks->DesignCbk)
              CALLBACK(defData->callbacks->DesignCbk, defrDesignStartCbkType, (yyvsp[(3) - (4)].string));
            defData->hasDes = 1;
          }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 309 "def.y"
    {
            defData->doneDesign = 1;
            if (defData->callbacks->DesignEndCbk)
              CALLBACK(defData->callbacks->DesignEndCbk, defrDesignEndCbkType, 0);
            // 11/16/2001 - pcr 408334
            // Return 1 if there is any defData->errors during parsing
            if (defData->errors)
                return 1;

            if (!defData->hasVer) {
              char temp[300];
              sprintf(temp, "No VERSION statement found, using the default value %2g.", defData->VersionNum);
              defData->defWarning(7012, temp);            
            }
            if (!defData->hasNameCase && defData->VersionNum < 5.6)
              defData->defWarning(7013, "The DEF file is invalid if NAMESCASESENSITIVE is undefined.\nNAMESCASESENSITIVE is a mandatory statement in the DEF file with version 5.6 and earlier.\nTo define the NAMESCASESENSITIVE statement, refer to the LEF/DEF 5.5 and earlier Language Reference manual.");
            if (!defData->hasBusBit && defData->VersionNum < 5.6)
              defData->defWarning(7014, "The DEF file is invalid if BUSBITCHARS is undefined.\nBUSBITCHARS is a mandatory statement in the DEF file with version 5.6 and earlier.\nTo define the BUSBITCHARS statement, refer to the LEF/DEF 5.5 and earlier Language Reference manual.");
            if (!defData->hasDivChar && defData->VersionNum < 5.6)
              defData->defWarning(7015, "The DEF file is invalid if DIVIDERCHAR is undefined.\nDIVIDERCHAR is a mandatory statement in the DEF file with version 5.6 and earlier.\nTo define the DIVIDERCHAR statement, refer to the LEF/DEF 5.5 and earlier Language Reference manual.");
            if (!defData->hasDes)
              defData->defWarning(7016, "DESIGN is a mandatory statement in the DEF file. Ensure that it exists in the file.");
          }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 333 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 334 "def.y"
    { 
            if (defData->callbacks->TechnologyCbk)
              CALLBACK(defData->callbacks->TechnologyCbk, defrTechNameCbkType, (yyvsp[(3) - (4)].string));
          }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 339 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1;}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 340 "def.y"
    { 
            if (defData->callbacks->ArrayNameCbk)
              CALLBACK(defData->callbacks->ArrayNameCbk, defrArrayNameCbkType, (yyvsp[(3) - (4)].string));
          }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 345 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 346 "def.y"
    { 
            if (defData->callbacks->FloorPlanNameCbk)
              CALLBACK(defData->callbacks->FloorPlanNameCbk, defrFloorPlanNameCbkType, (yyvsp[(3) - (4)].string));
          }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 352 "def.y"
    { 
            if (defData->callbacks->HistoryCbk)
              CALLBACK(defData->callbacks->HistoryCbk, defrHistoryCbkType, &defData->History_text[0]);
          }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 358 "def.y"
    {
            if (defData->callbacks->PropDefStartCbk)
              CALLBACK(defData->callbacks->PropDefStartCbk, defrPropDefStartCbkType, 0);
          }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 363 "def.y"
    { 
            if (defData->callbacks->PropDefEndCbk)
              CALLBACK(defData->callbacks->PropDefEndCbk, defrPropDefEndCbkType, 0);
            defData->real_num = 0;     // just want to make sure it is reset 
          }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 371 "def.y"
    { }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 373 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1; defData->Prop.clear(); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 375 "def.y"
    {
              if (defData->callbacks->PropCbk) {
                defData->Prop.setPropType("design", (yyvsp[(3) - (5)].string));
                CALLBACK(defData->callbacks->PropCbk, defrPropCbkType, &defData->Prop);
              }
              defData->session->DesignProp.setPropType(defData->DEFCASE((yyvsp[(3) - (5)].string)), defData->defPropDefType);
            }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 382 "def.y"
    { defData->dumb_mode = 1 ; defData->no_num = 1; defData->Prop.clear(); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 384 "def.y"
    {
              if (defData->callbacks->PropCbk) {
                defData->Prop.setPropType("net", (yyvsp[(3) - (5)].string));
                CALLBACK(defData->callbacks->PropCbk, defrPropCbkType, &defData->Prop);
              }
              defData->session->NetProp.setPropType(defData->DEFCASE((yyvsp[(3) - (5)].string)), defData->defPropDefType);
            }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 391 "def.y"
    { defData->dumb_mode = 1 ; defData->no_num = 1; defData->Prop.clear(); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 393 "def.y"
    {
              if (defData->callbacks->PropCbk) {
                defData->Prop.setPropType("specialnet", (yyvsp[(3) - (5)].string));
                CALLBACK(defData->callbacks->PropCbk, defrPropCbkType, &defData->Prop);
              }
              defData->session->SNetProp.setPropType(defData->DEFCASE((yyvsp[(3) - (5)].string)), defData->defPropDefType);
            }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 400 "def.y"
    { defData->dumb_mode = 1 ; defData->no_num = 1; defData->Prop.clear(); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 402 "def.y"
    {
              if (defData->callbacks->PropCbk) {
                defData->Prop.setPropType("region", (yyvsp[(3) - (5)].string));
                CALLBACK(defData->callbacks->PropCbk, defrPropCbkType, &defData->Prop);
              }
              defData->session->RegionProp.setPropType(defData->DEFCASE((yyvsp[(3) - (5)].string)), defData->defPropDefType);
            }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 409 "def.y"
    { defData->dumb_mode = 1 ; defData->no_num = 1; defData->Prop.clear(); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 411 "def.y"
    {
              if (defData->callbacks->PropCbk) {
                defData->Prop.setPropType("group", (yyvsp[(3) - (5)].string));
                CALLBACK(defData->callbacks->PropCbk, defrPropCbkType, &defData->Prop);
              }
              defData->session->GroupProp.setPropType(defData->DEFCASE((yyvsp[(3) - (5)].string)), defData->defPropDefType);
            }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 418 "def.y"
    { defData->dumb_mode = 1 ; defData->no_num = 1; defData->Prop.clear(); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 420 "def.y"
    {
              if (defData->callbacks->PropCbk) {
                defData->Prop.setPropType("component", (yyvsp[(3) - (5)].string));
                CALLBACK(defData->callbacks->PropCbk, defrPropCbkType, &defData->Prop);
              }
              defData->session->CompProp.setPropType(defData->DEFCASE((yyvsp[(3) - (5)].string)), defData->defPropDefType);
            }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 427 "def.y"
    { defData->dumb_mode = 1 ; defData->no_num = 1; defData->Prop.clear(); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 429 "def.y"
    {
              if (defData->callbacks->PropCbk) {
                defData->Prop.setPropType("row", (yyvsp[(3) - (5)].string));
                CALLBACK(defData->callbacks->PropCbk, defrPropCbkType, &defData->Prop);
              }
              defData->session->RowProp.setPropType(defData->DEFCASE((yyvsp[(3) - (5)].string)), defData->defPropDefType);
            }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 438 "def.y"
    { defData->dumb_mode = 1 ; defData->no_num = 1; defData->Prop.clear(); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 440 "def.y"
    {
              if (defData->callbacks->PropCbk) {
                defData->Prop.setPropType("componentpin", (yyvsp[(3) - (5)].string));
                CALLBACK(defData->callbacks->PropCbk, defrPropCbkType, &defData->Prop);
              }
              defData->session->CompPinProp.setPropType(defData->DEFCASE((yyvsp[(3) - (5)].string)), defData->defPropDefType);
            }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 448 "def.y"
    { defData->dumb_mode = 1 ; defData->no_num = 1; defData->Prop.clear(); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 450 "def.y"
    {
              if (defData->VersionNum < 5.6) {
                if (defData->nonDefaultWarnings++ < defData->settings->NonDefaultWarnings) {
                  defData->defMsg = (char*)malloc(1000); 
                  sprintf (defData->defMsg,
                     "The NONDEFAULTRULE statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6505, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              } else {
                if (defData->callbacks->PropCbk) {
                  defData->Prop.setPropType("nondefaultrule", (yyvsp[(3) - (5)].string));
                  CALLBACK(defData->callbacks->PropCbk, defrPropCbkType, &defData->Prop);
                }
                defData->session->NDefProp.setPropType(defData->DEFCASE((yyvsp[(3) - (5)].string)), defData->defPropDefType);
              }
            }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 468 "def.y"
    { yyerrok; yyclearin;}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 470 "def.y"
    { defData->real_num = 0 ;}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 471 "def.y"
    {
              if (defData->callbacks->PropCbk) defData->Prop.setPropInteger();
              defData->defPropDefType = 'I';
            }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 475 "def.y"
    { defData->real_num = 1 ;}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 476 "def.y"
    {
              if (defData->callbacks->PropCbk) defData->Prop.setPropReal();
              defData->defPropDefType = 'R';
              defData->real_num = 0;
            }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 482 "def.y"
    {
              if (defData->callbacks->PropCbk) defData->Prop.setPropString();
              defData->defPropDefType = 'S';
            }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 487 "def.y"
    {
              if (defData->callbacks->PropCbk) defData->Prop.setPropQString((yyvsp[(2) - (2)].string));
              defData->defPropDefType = 'Q';
            }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 492 "def.y"
    {
              if (defData->callbacks->PropCbk) defData->Prop.setPropNameMapString((yyvsp[(2) - (2)].string));
              defData->defPropDefType = 'S';
            }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 499 "def.y"
    { if (defData->callbacks->PropCbk) defData->Prop.setNumber((yyvsp[(1) - (1)].dval)); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 502 "def.y"
    {
            if (defData->callbacks->UnitsCbk) {
              if (defData->defValidNum((int)(yyvsp[(4) - (5)].dval)))
                CALLBACK(defData->callbacks->UnitsCbk,  defrUnitsCbkType, (yyvsp[(4) - (5)].dval));
            }
          }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 510 "def.y"
    {
            if (defData->callbacks->DividerCbk)
              CALLBACK(defData->callbacks->DividerCbk, defrDividerCbkType, (yyvsp[(2) - (3)].string));
            defData->hasDivChar = 1;
          }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 517 "def.y"
    { 
            if (defData->callbacks->BusBitCbk)
              CALLBACK(defData->callbacks->BusBitCbk, defrBusBitCbkType, (yyvsp[(2) - (3)].string));
            defData->hasBusBit = 1;
          }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 523 "def.y"
    {defData->dumb_mode = 1;defData->no_num = 1; }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 525 "def.y"
    {
              if (defData->callbacks->CanplaceCbk) {
                defData->Canplace.setName((yyvsp[(3) - (14)].string));
                defData->Canplace.setLocation((yyvsp[(4) - (14)].dval),(yyvsp[(5) - (14)].dval));
                defData->Canplace.setOrient((yyvsp[(6) - (14)].integer));
                defData->Canplace.setDo((yyvsp[(8) - (14)].dval),(yyvsp[(10) - (14)].dval),(yyvsp[(12) - (14)].dval),(yyvsp[(13) - (14)].dval));
                CALLBACK(defData->callbacks->CanplaceCbk, defrCanplaceCbkType,
                &(defData->Canplace));
              }
            }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 535 "def.y"
    {defData->dumb_mode = 1;defData->no_num = 1; }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 537 "def.y"
    {
              if (defData->callbacks->CannotOccupyCbk) {
                defData->CannotOccupy.setName((yyvsp[(3) - (14)].string));
                defData->CannotOccupy.setLocation((yyvsp[(4) - (14)].dval),(yyvsp[(5) - (14)].dval));
                defData->CannotOccupy.setOrient((yyvsp[(6) - (14)].integer));
                defData->CannotOccupy.setDo((yyvsp[(8) - (14)].dval),(yyvsp[(10) - (14)].dval),(yyvsp[(12) - (14)].dval),(yyvsp[(13) - (14)].dval));
                CALLBACK(defData->callbacks->CannotOccupyCbk, defrCannotOccupyCbkType,
                        &(defData->CannotOccupy));
              }
            }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 548 "def.y"
    {(yyval.integer) = 0;}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 549 "def.y"
    {(yyval.integer) = 1;}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 550 "def.y"
    {(yyval.integer) = 2;}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 551 "def.y"
    {(yyval.integer) = 3;}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 552 "def.y"
    {(yyval.integer) = 4;}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 553 "def.y"
    {(yyval.integer) = 5;}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 554 "def.y"
    {(yyval.integer) = 6;}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 555 "def.y"
    {(yyval.integer) = 7;}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 558 "def.y"
    {
            defData->Geometries.Reset();
          }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 562 "def.y"
    {
            if (defData->callbacks->DieAreaCbk) {
               defData->DieArea.addPoint(&defData->Geometries);
               CALLBACK(defData->callbacks->DieAreaCbk, defrDieAreaCbkType, &(defData->DieArea));
            }
          }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 571 "def.y"
    { }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 574 "def.y"
    {
          if (defData->VersionNum < 5.4) {
             if (defData->callbacks->DefaultCapCbk)
                CALLBACK(defData->callbacks->DefaultCapCbk, defrDefaultCapCbkType, ROUND((yyvsp[(2) - (2)].dval)));
          } else {
             if (defData->callbacks->DefaultCapCbk) // write error only if cbk is set 
                if (defData->defaultCapWarnings++ < defData->settings->DefaultCapWarnings)
                   defData->defWarning(7017, "The DEFAULTCAP statement is obsolete in version 5.4 and later.\nThe DEF parser will ignore this statement.");
          }
        }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 590 "def.y"
    {
            if (defData->VersionNum < 5.4) {
              if (defData->callbacks->PinCapCbk) {
                defData->PinCap.setPin(ROUND((yyvsp[(2) - (5)].dval)));
                defData->PinCap.setCap((yyvsp[(4) - (5)].dval));
                CALLBACK(defData->callbacks->PinCapCbk, defrPinCapCbkType, &(defData->PinCap));
              }
            }
          }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 601 "def.y"
    { }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 604 "def.y"
    { }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 607 "def.y"
    { 
            if (defData->callbacks->StartPinsCbk)
              CALLBACK(defData->callbacks->StartPinsCbk, defrStartPinsCbkType, ROUND((yyvsp[(2) - (3)].dval)));
          }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 616 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 617 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 618 "def.y"
    {
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
              defData->Pin.Setup((yyvsp[(3) - (7)].string), (yyvsp[(7) - (7)].string));
            }
            defData->hasPort = 0;
          }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 625 "def.y"
    { 
            if (defData->callbacks->PinCbk)
              CALLBACK(defData->callbacks->PinCbk, defrPinCbkType, &defData->Pin);
          }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 634 "def.y"
    {
            if (defData->callbacks->PinCbk)
              defData->Pin.setSpecial();
          }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 640 "def.y"
    { 
            if (defData->callbacks->PinExtCbk)
              CALLBACK(defData->callbacks->PinExtCbk, defrPinExtCbkType, &defData->History_text[0]);
          }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 646 "def.y"
    {
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
              defData->Pin.setDirection((yyvsp[(3) - (3)].string));
          }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 652 "def.y"
    {
            if (defData->VersionNum < 5.6) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The NETEXPR statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6506, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            } else {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
                defData->Pin.setNetExpr((yyvsp[(3) - (3)].string));

            }
          }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 672 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 673 "def.y"
    {
            if (defData->VersionNum < 5.6) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The SUPPLYSENSITIVITY statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6507, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            } else {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
                defData->Pin.setSupplySens((yyvsp[(4) - (4)].string));
            }
          }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 692 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 693 "def.y"
    {
            if (defData->VersionNum < 5.6) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The GROUNDSENSITIVITY statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6508, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            } else {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
                defData->Pin.setGroundSens((yyvsp[(4) - (4)].string));
            }
          }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 713 "def.y"
    {
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) defData->Pin.setUse((yyvsp[(3) - (3)].string));
          }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 717 "def.y"
    {
            if (defData->VersionNum < 5.7) {
               if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                 if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                     (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                   defData->defMsg = (char*)malloc(10000);
                   sprintf (defData->defMsg,
                     "The PORT in PINS is available in version 5.7 or later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                   defData->defError(6555, defData->defMsg);
                   free(defData->defMsg);
                   CHKERR();
                 }
               }
            } else {
               if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
                 defData->Pin.addPort();
               defData->hasPort = 1;
            }
          }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 737 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 738 "def.y"
    {
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
              if (defData->hasPort)
                 defData->Pin.addPortLayer((yyvsp[(4) - (4)].string));
              else
                 defData->Pin.addLayer((yyvsp[(4) - (4)].string));
            }
          }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 747 "def.y"
    {
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
              if (defData->hasPort)
                 defData->Pin.addPortLayerPts((yyvsp[(8) - (9)].pt).x, (yyvsp[(8) - (9)].pt).y, (yyvsp[(9) - (9)].pt).x, (yyvsp[(9) - (9)].pt).y);
              else
                 defData->Pin.addLayerPts((yyvsp[(8) - (9)].pt).x, (yyvsp[(8) - (9)].pt).y, (yyvsp[(9) - (9)].pt).x, (yyvsp[(9) - (9)].pt).y);
            }
          }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 756 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 757 "def.y"
    {
            if (defData->VersionNum < 5.6) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The POLYGON statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6509, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            } else {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if (defData->hasPort)
                   defData->Pin.addPortPolygon((yyvsp[(4) - (4)].string));
                else
                   defData->Pin.addPolygon((yyvsp[(4) - (4)].string));
              }
            }
            
            defData->Geometries.Reset();            
          }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 782 "def.y"
    {
            if (defData->VersionNum >= 5.6) {  // only add if 5.6 or beyond
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if (defData->hasPort)
                   defData->Pin.addPortPolygonPts(&defData->Geometries);
                else
                   defData->Pin.addPolygonPts(&defData->Geometries);
              }
            }
          }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 792 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 793 "def.y"
    {
            if (defData->VersionNum < 5.7) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The PIN VIA statement is available in version 5.7 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6556, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            } else {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if (defData->hasPort)
                   defData->Pin.addPortVia((yyvsp[(4) - (9)].string), (int)(yyvsp[(7) - (9)].dval),
                                               (int)(yyvsp[(8) - (9)].dval), (yyvsp[(5) - (9)].integer));
                else
                   defData->Pin.addVia((yyvsp[(4) - (9)].string), (int)(yyvsp[(7) - (9)].dval),
                                               (int)(yyvsp[(8) - (9)].dval), (yyvsp[(5) - (9)].integer));
              }
            }
          }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 819 "def.y"
    {
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
              if (defData->hasPort)
                 defData->Pin.setPortPlacement((yyvsp[(1) - (3)].integer), (yyvsp[(2) - (3)].pt).x, (yyvsp[(2) - (3)].pt).y, (yyvsp[(3) - (3)].integer));
              else
                 defData->Pin.setPlacement((yyvsp[(1) - (3)].integer), (yyvsp[(2) - (3)].pt).x, (yyvsp[(2) - (3)].pt).y, (yyvsp[(3) - (3)].integer));
            }
          }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 830 "def.y"
    {
            if (defData->VersionNum <= 5.3) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The ANTENNAPINPARTIALMETALAREA statement is available in version 5.4 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6510, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            }
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
              defData->Pin.addAPinPartialMetalArea((int)(yyvsp[(3) - (4)].dval), (yyvsp[(4) - (4)].string)); 
          }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 848 "def.y"
    {
            if (defData->VersionNum <= 5.3) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The ANTENNAPINPARTIALMETALSIDEAREA statement is available in version 5.4 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6511, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            }
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
              defData->Pin.addAPinPartialMetalSideArea((int)(yyvsp[(3) - (4)].dval), (yyvsp[(4) - (4)].string)); 
          }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 866 "def.y"
    {
            if (defData->VersionNum <= 5.3) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The ANTENNAPINGATEAREA statement is available in version 5.4 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6512, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            }
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
                defData->Pin.addAPinGateArea((int)(yyvsp[(3) - (4)].dval), (yyvsp[(4) - (4)].string)); 
            }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 884 "def.y"
    {
            if (defData->VersionNum <= 5.3) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The ANTENNAPINDIFFAREA statement is available in version 5.4 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6513, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            }
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
              defData->Pin.addAPinDiffArea((int)(yyvsp[(3) - (4)].dval), (yyvsp[(4) - (4)].string)); 
          }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 901 "def.y"
    {defData->dumb_mode=1;}
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 902 "def.y"
    {
            if (defData->VersionNum <= 5.3) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The ANTENNAPINMAXAREACAR statement is available in version 5.4 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6514, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            }
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
              defData->Pin.addAPinMaxAreaCar((int)(yyvsp[(3) - (6)].dval), (yyvsp[(6) - (6)].string)); 
          }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 919 "def.y"
    {defData->dumb_mode=1;}
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 921 "def.y"
    {
            if (defData->VersionNum <= 5.3) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The ANTENNAPINMAXSIDEAREACAR statement is available in version 5.4 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6515, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            }
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
              defData->Pin.addAPinMaxSideAreaCar((int)(yyvsp[(3) - (6)].dval), (yyvsp[(6) - (6)].string)); 
          }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 939 "def.y"
    {
            if (defData->VersionNum <= 5.3) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The ANTENNAPINPARTIALCUTAREA statement is available in version 5.4 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6516, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            }
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
              defData->Pin.addAPinPartialCutArea((int)(yyvsp[(3) - (4)].dval), (yyvsp[(4) - (4)].string)); 
          }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 956 "def.y"
    {defData->dumb_mode=1;}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 957 "def.y"
    {
            if (defData->VersionNum <= 5.3) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The ANTENNAPINMAXCUTCAR statement is available in version 5.4 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6517, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            }
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
              defData->Pin.addAPinMaxCutCar((int)(yyvsp[(3) - (6)].dval), (yyvsp[(6) - (6)].string)); 
          }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 975 "def.y"
    {  // 5.5 syntax 
            if (defData->VersionNum < 5.5) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The ANTENNAMODEL statement is available in version 5.5 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6518, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            }
          }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 993 "def.y"
    { 
           if (defData->validateMaskInput((int)(yyvsp[(2) - (2)].dval), defData->pinWarnings, defData->settings->PinWarnings)) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if (defData->hasPort)
                   defData->Pin.addPortLayerMask((int)(yyvsp[(2) - (2)].dval));
                else
                   defData->Pin.addLayerMask((int)(yyvsp[(2) - (2)].dval));
              }
           }
         }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 1006 "def.y"
    { (yyval.integer) = 0; }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 1008 "def.y"
    { 
           if (defData->validateMaskInput((int)(yyvsp[(2) - (2)].dval), defData->pinWarnings, defData->settings->PinWarnings)) {
             (yyval.integer) = (yyvsp[(2) - (2)].dval);
           }
         }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 1016 "def.y"
    { 
           if (defData->validateMaskInput((int)(yyvsp[(2) - (2)].dval), defData->pinWarnings, defData->settings->PinWarnings)) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if (defData->hasPort)
                   defData->Pin.addPortPolyMask((int)(yyvsp[(2) - (2)].dval));
                else
                   defData->Pin.addPolyMask((int)(yyvsp[(2) - (2)].dval));
              }
           }
         }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 1030 "def.y"
    {
            if (defData->VersionNum < 5.6) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The SPACING statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6519, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            } else {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if (defData->hasPort)
                   defData->Pin.addPortLayerSpacing((int)(yyvsp[(2) - (2)].dval));
                else
                   defData->Pin.addLayerSpacing((int)(yyvsp[(2) - (2)].dval));
              }
            }
          }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 1053 "def.y"
    {
            if (defData->VersionNum < 5.6) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "DESIGNRULEWIDTH statement is a version 5.6 and later syntax.\nYour def file is defined with version %g", defData->VersionNum);
                  defData->defError(6520, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            } else {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if (defData->hasPort)
                   defData->Pin.addPortLayerDesignRuleWidth((int)(yyvsp[(2) - (2)].dval));
                else
                   defData->Pin.addLayerDesignRuleWidth((int)(yyvsp[(2) - (2)].dval));
              }
            }
          }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 1078 "def.y"
    {
            if (defData->VersionNum < 5.6) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "SPACING statement is a version 5.6 and later syntax.\nYour def file is defined with version %g", defData->VersionNum);
                  defData->defError(6521, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            } else {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if (defData->hasPort)
                   defData->Pin.addPortPolySpacing((int)(yyvsp[(2) - (2)].dval));
                else
                   defData->Pin.addPolySpacing((int)(yyvsp[(2) - (2)].dval));
              }
            }
          }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 1101 "def.y"
    {
            if (defData->VersionNum < 5.6) {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if ((defData->pinWarnings++ < defData->settings->PinWarnings) &&
                    (defData->pinWarnings++ < defData->settings->PinExtWarnings)) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The DESIGNRULEWIDTH statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                  defData->defError(6520, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            } else {
              if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk) {
                if (defData->hasPort)
                   defData->Pin.addPortPolyDesignRuleWidth((int)(yyvsp[(2) - (2)].dval));
                else
                   defData->Pin.addPolyDesignRuleWidth((int)(yyvsp[(2) - (2)].dval));
              }
            }
          }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 1125 "def.y"
    { defData->aOxide = 1;
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
              defData->Pin.addAntennaModel(defData->aOxide);
          }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 1130 "def.y"
    { defData->aOxide = 2;
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
              defData->Pin.addAntennaModel(defData->aOxide);
          }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 1135 "def.y"
    { defData->aOxide = 3;
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
              defData->Pin.addAntennaModel(defData->aOxide);
          }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 1140 "def.y"
    { defData->aOxide = 4;
            if (defData->callbacks->PinCbk || defData->callbacks->PinExtCbk)
              defData->Pin.addAntennaModel(defData->aOxide);
          }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 1146 "def.y"
    { (yyval.string) = (char*)"SIGNAL"; }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 1148 "def.y"
    { (yyval.string) = (char*)"POWER"; }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 1150 "def.y"
    { (yyval.string) = (char*)"GROUND"; }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 1152 "def.y"
    { (yyval.string) = (char*)"CLOCK"; }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 1154 "def.y"
    { (yyval.string) = (char*)"TIEOFF"; }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 1156 "def.y"
    { (yyval.string) = (char*)"ANALOG"; }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 1158 "def.y"
    { (yyval.string) = (char*)"SCAN"; }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 1160 "def.y"
    { (yyval.string) = (char*)"RESET"; }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 1164 "def.y"
    { (yyval.string) = (char*)""; }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 1165 "def.y"
    {defData->dumb_mode=1;}
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 1166 "def.y"
    { (yyval.string) = (yyvsp[(3) - (3)].string); }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 1169 "def.y"
    { 
          if (defData->callbacks->PinEndCbk)
            CALLBACK(defData->callbacks->PinEndCbk, defrPinEndCbkType, 0);
        }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 1174 "def.y"
    {defData->dumb_mode = 2; defData->no_num = 2; }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 1176 "def.y"
    {
          if (defData->callbacks->RowCbk) {
            defData->rowName = (yyvsp[(3) - (7)].string);
            defData->Row.setup((yyvsp[(3) - (7)].string), (yyvsp[(4) - (7)].string), (yyvsp[(5) - (7)].dval), (yyvsp[(6) - (7)].dval), (yyvsp[(7) - (7)].integer));
          }
        }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 1184 "def.y"
    {
          if (defData->callbacks->RowCbk) 
            CALLBACK(defData->callbacks->RowCbk, defrRowCbkType, &defData->Row);
        }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 1190 "def.y"
    {
          if (defData->VersionNum < 5.6) {
            if (defData->callbacks->RowCbk) {
              if (defData->rowWarnings++ < defData->settings->RowWarnings) {
                defData->defError(6523, "Invalid ROW statement defined in the DEF file. The DO statement which is required in the ROW statement is not defined.\nUpdate your DEF file with a DO statement.");
                CHKERR();
              }
            }
          }
        }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 1201 "def.y"
    {
          // 06/05/2002 - pcr 448455 
          // Check for 1 and 0 in the correct position 
          // 07/26/2002 - Commented out due to pcr 459218 
          if (defData->hasDoStep) {
            // 04/29/2004 - pcr 695535 
            // changed the testing 
            if ((((yyvsp[(4) - (5)].dval) == 1) && (defData->yStep == 0)) ||
                (((yyvsp[(2) - (5)].dval) == 1) && (defData->xStep == 0))) {
              // do nothing 
            } else 
              if (defData->VersionNum < 5.6) {
                if (defData->callbacks->RowCbk) {
                  if (defData->rowWarnings++ < defData->settings->RowWarnings) {
                    defData->defMsg = (char*)malloc(1000);
                    sprintf(defData->defMsg,
                            "The DO statement in the ROW statement with the name %s has invalid syntax.\nThe valid syntax is \"DO numX BY 1 STEP spaceX 0 | DO 1 BY numY STEP 0 spaceY\".\nSpecify the valid syntax and try again.", defData->rowName);
                    defData->defWarning(7018, defData->defMsg);
                    free(defData->defMsg);
                    }
                  }
              }
          }
          // pcr 459218 - Error if at least numX or numY does not equal 1 
          if (((yyvsp[(2) - (5)].dval) != 1) && ((yyvsp[(4) - (5)].dval) != 1)) {
            if (defData->callbacks->RowCbk) {
              if (defData->rowWarnings++ < defData->settings->RowWarnings) {
                defData->defError(6524, "Invalid syntax specified. The valid syntax is either \"DO 1 BY num or DO num BY 1\". Specify the valid syntax and try again.");
                CHKERR();
              }
            }
          }
          if (defData->callbacks->RowCbk)
            defData->Row.setDo(ROUND((yyvsp[(2) - (5)].dval)), ROUND((yyvsp[(4) - (5)].dval)), defData->xStep, defData->yStep);
        }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 1238 "def.y"
    {
          defData->hasDoStep = 0;
        }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 1242 "def.y"
    {
          defData->hasDoStep = 1;
          defData->Row.setHasDoStep();
          defData->xStep = (yyvsp[(2) - (3)].dval);
          defData->yStep = (yyvsp[(3) - (3)].dval);
        }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 1253 "def.y"
    {defData->dumb_mode = DEF_MAX_INT; }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 1255 "def.y"
    { defData->dumb_mode = 0; }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 1262 "def.y"
    {
          if (defData->callbacks->RowCbk) {
             char propTp;
             char* str = defData->ringCopy("                       ");
             propTp =  defData->session->RowProp.propType((yyvsp[(1) - (2)].string));
             CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "ROW");
             // For backword compatibility, also set the string value 
             sprintf(str, "%g", (yyvsp[(2) - (2)].dval));
             defData->Row.addNumProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].dval), str, propTp);
          }
        }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 1274 "def.y"
    {
          if (defData->callbacks->RowCbk) {
             char propTp;
             propTp =  defData->session->RowProp.propType((yyvsp[(1) - (2)].string));
             CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "ROW");
             defData->Row.addProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
          }
        }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 1283 "def.y"
    {
          if (defData->callbacks->RowCbk) {
             char propTp;
             propTp =  defData->session->RowProp.propType((yyvsp[(1) - (2)].string));
             CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "ROW");
             defData->Row.addProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
          }
        }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 1293 "def.y"
    {
          if (defData->callbacks->TrackCbk) {
            defData->Track.setup((yyvsp[(1) - (2)].string));
          }
        }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 1299 "def.y"
    {
          if (((yyvsp[(5) - (9)].dval) <= 0) && (defData->VersionNum >= 5.4)) {
            if (defData->callbacks->TrackCbk)
              if (defData->trackWarnings++ < defData->settings->TrackWarnings) {
                defData->defMsg = (char*)malloc(1000);
                sprintf (defData->defMsg,
                   "The DO number %g in TRACK is invalid.\nThe number value has to be greater than 0. Specify the valid syntax and try again.", (yyvsp[(5) - (9)].dval));
                defData->defError(6525, defData->defMsg);
                free(defData->defMsg);
              }
          }
          if ((yyvsp[(7) - (9)].dval) < 0) {
            if (defData->callbacks->TrackCbk)
              if (defData->trackWarnings++ < defData->settings->TrackWarnings) {
                defData->defMsg = (char*)malloc(1000);
                sprintf (defData->defMsg,
                   "The STEP number %g in TRACK is invalid.\nThe number value has to be greater than 0. Specify the valid syntax and try again.", (yyvsp[(7) - (9)].dval));
                defData->defError(6526, defData->defMsg);
                free(defData->defMsg);
              }
          }
          if (defData->callbacks->TrackCbk) {
            defData->Track.setDo(ROUND((yyvsp[(2) - (9)].dval)), ROUND((yyvsp[(5) - (9)].dval)), (yyvsp[(7) - (9)].dval));
            CALLBACK(defData->callbacks->TrackCbk, defrTrackCbkType, &defData->Track);
          }
        }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 1327 "def.y"
    {
          (yyval.string) = (yyvsp[(2) - (2)].string);
        }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 1332 "def.y"
    { (yyval.string) = (char*)"X";}
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 1334 "def.y"
    { (yyval.string) = (char*)"Y";}
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 1340 "def.y"
    { 
              if (defData->validateMaskInput((int)(yyvsp[(2) - (3)].dval), defData->trackWarnings, defData->settings->TrackWarnings)) {
                  if (defData->callbacks->TrackCbk) {
                    defData->Track.addMask((yyvsp[(2) - (3)].dval), (yyvsp[(3) - (3)].integer));
                  }
               }
            }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 1350 "def.y"
    { (yyval.integer) = 0; }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 1352 "def.y"
    { (yyval.integer) = 1; }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 1355 "def.y"
    { defData->dumb_mode = 1000; }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 1356 "def.y"
    { defData->dumb_mode = 0; }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 1363 "def.y"
    {
          if (defData->callbacks->TrackCbk)
            defData->Track.addLayer((yyvsp[(1) - (1)].string));
        }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 1370 "def.y"
    {
          if ((yyvsp[(5) - (8)].dval) <= 0) {
            if (defData->callbacks->GcellGridCbk)
              if (defData->gcellGridWarnings++ < defData->settings->GcellGridWarnings) {
                defData->defMsg = (char*)malloc(1000);
                sprintf (defData->defMsg,
                   "The DO number %g in GCELLGRID is invalid.\nThe number value has to be greater than 0. Specify the valid syntax and try again.", (yyvsp[(5) - (8)].dval));
                defData->defError(6527, defData->defMsg);
                free(defData->defMsg);
              }
          }
          if ((yyvsp[(7) - (8)].dval) < 0) {
            if (defData->callbacks->GcellGridCbk)
              if (defData->gcellGridWarnings++ < defData->settings->GcellGridWarnings) {
                defData->defMsg = (char*)malloc(1000);
                sprintf (defData->defMsg,
                   "The STEP number %g in GCELLGRID is invalid.\nThe number value has to be greater than 0. Specify the valid syntax and try again.", (yyvsp[(7) - (8)].dval));
                defData->defError(6528, defData->defMsg);
                free(defData->defMsg);
              }
          }
          if (defData->callbacks->GcellGridCbk) {
            defData->GcellGrid.setup((yyvsp[(2) - (8)].string), ROUND((yyvsp[(3) - (8)].dval)), ROUND((yyvsp[(5) - (8)].dval)), (yyvsp[(7) - (8)].dval));
            CALLBACK(defData->callbacks->GcellGridCbk, defrGcellGridCbkType, &defData->GcellGrid);
          }
        }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 1398 "def.y"
    {
          if (defData->callbacks->ExtensionCbk)
             CALLBACK(defData->callbacks->ExtensionCbk, defrExtensionCbkType, &defData->History_text[0]);
        }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 1404 "def.y"
    { }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 1410 "def.y"
    {
          if (defData->callbacks->ViaStartCbk)
            CALLBACK(defData->callbacks->ViaStartCbk, defrViaStartCbkType, ROUND((yyvsp[(2) - (3)].dval)));
        }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 1419 "def.y"
    {defData->dumb_mode = 1;defData->no_num = 1; }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 1420 "def.y"
    {
              if (defData->callbacks->ViaCbk) defData->Via.setup((yyvsp[(3) - (3)].string));
              defData->viaRule = 0;
            }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 1425 "def.y"
    {
              if (defData->callbacks->ViaCbk)
                CALLBACK(defData->callbacks->ViaCbk, defrViaCbkType, &defData->Via);
              defData->Via.clear();
            }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 1435 "def.y"
    {defData->dumb_mode = 1;defData->no_num = 1; }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 1436 "def.y"
    { 
              if (defData->callbacks->ViaCbk)
                if (defData->validateMaskInput((yyvsp[(5) - (7)].integer), defData->viaWarnings, defData->settings->ViaWarnings)) {
                    defData->Via.addLayer((yyvsp[(4) - (7)].string), (yyvsp[(6) - (7)].pt).x, (yyvsp[(6) - (7)].pt).y, (yyvsp[(7) - (7)].pt).x, (yyvsp[(7) - (7)].pt).y, (yyvsp[(5) - (7)].integer));
                }
            }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 1442 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 1443 "def.y"
    {
              if (defData->VersionNum < 5.6) {
                if (defData->callbacks->ViaCbk) {
                  if (defData->viaWarnings++ < defData->settings->ViaWarnings) {
                    defData->defMsg = (char*)malloc(1000);
                    sprintf (defData->defMsg,
                       "The POLYGON statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                    defData->defError(6509, defData->defMsg);
                    free(defData->defMsg);
                    CHKERR();
                  }
                }
              }
              
              defData->Geometries.Reset();
              
            }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 1461 "def.y"
    {
              if (defData->VersionNum >= 5.6) {  // only add if 5.6 or beyond
                if (defData->callbacks->ViaCbk)
                  if (defData->validateMaskInput((yyvsp[(5) - (10)].integer), defData->viaWarnings, defData->settings->ViaWarnings)) {
                    defData->Via.addPolygon((yyvsp[(4) - (10)].string), &defData->Geometries, (yyvsp[(5) - (10)].integer));
                  }
              }
            }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 1469 "def.y"
    {defData->dumb_mode = 1;defData->no_num = 1; }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 1470 "def.y"
    {
              if (defData->VersionNum < 5.6) {
                if (defData->callbacks->ViaCbk)
                  defData->Via.addPattern((yyvsp[(4) - (4)].string));
              } else
                if (defData->callbacks->ViaCbk)
                  if (defData->viaWarnings++ < defData->settings->ViaWarnings)
                    defData->defWarning(7019, "The PATTERNNAME statement is obsolete in version 5.6 and later.\nThe DEF parser will ignore this statement."); 
            }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 1479 "def.y"
    {defData->dumb_mode = 1;defData->no_num = 1; }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 1481 "def.y"
    {defData->dumb_mode = 3;defData->no_num = 1; }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 1484 "def.y"
    {
               defData->viaRule = 1;
               if (defData->VersionNum < 5.6) {
                if (defData->callbacks->ViaCbk) {
                  if (defData->viaWarnings++ < defData->settings->ViaWarnings) {
                    defData->defMsg = (char*)malloc(1000);
                    sprintf (defData->defMsg,
                       "The VIARULE statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                    defData->defError(6557, defData->defMsg);
                    free(defData->defMsg);
                    CHKERR();
                  }
                }
              } else {
                if (defData->callbacks->ViaCbk)
                   defData->Via.addViaRule((yyvsp[(4) - (24)].string), (int)(yyvsp[(7) - (24)].dval), (int)(yyvsp[(8) - (24)].dval), (yyvsp[(12) - (24)].string), (yyvsp[(13) - (24)].string),
                                             (yyvsp[(14) - (24)].string), (int)(yyvsp[(17) - (24)].dval), (int)(yyvsp[(18) - (24)].dval), (int)(yyvsp[(21) - (24)].dval),
                                             (int)(yyvsp[(22) - (24)].dval), (int)(yyvsp[(23) - (24)].dval), (int)(yyvsp[(24) - (24)].dval)); 
              }
            }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 1506 "def.y"
    { 
            if (defData->callbacks->ViaExtCbk)
              CALLBACK(defData->callbacks->ViaExtCbk, defrViaExtCbkType, &defData->History_text[0]);
          }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 1512 "def.y"
    {
              if (!defData->viaRule) {
                if (defData->callbacks->ViaCbk) {
                  if (defData->viaWarnings++ < defData->settings->ViaWarnings) {
                    defData->defError(6559, "The ROWCOL statement is missing from the VIARULE statement. Ensure that it exists in the VIARULE statement.");
                    CHKERR();
                  }
                }
              } else if (defData->callbacks->ViaCbk)
                 defData->Via.addRowCol((int)(yyvsp[(3) - (4)].dval), (int)(yyvsp[(4) - (4)].dval));
            }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 1524 "def.y"
    {
              if (!defData->viaRule) {
                if (defData->callbacks->ViaCbk) {
                  if (defData->viaWarnings++ < defData->settings->ViaWarnings) {
                    defData->defError(6560, "The ORIGIN statement is missing from the VIARULE statement. Ensure that it exists in the VIARULE statement.");
                    CHKERR();
                  }
                }
              } else if (defData->callbacks->ViaCbk)
                 defData->Via.addOrigin((int)(yyvsp[(3) - (4)].dval), (int)(yyvsp[(4) - (4)].dval));
            }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 1536 "def.y"
    {
              if (!defData->viaRule) {
                if (defData->callbacks->ViaCbk) {
                  if (defData->viaWarnings++ < defData->settings->ViaWarnings) {
                    defData->defError(6561, "The OFFSET statement is missing from the VIARULE statement. Ensure that it exists in the VIARULE statement.");
                    CHKERR();
                  }
                }
              } else if (defData->callbacks->ViaCbk)
                 defData->Via.addOffset((int)(yyvsp[(3) - (6)].dval), (int)(yyvsp[(4) - (6)].dval), (int)(yyvsp[(5) - (6)].dval), (int)(yyvsp[(6) - (6)].dval));
            }
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 1547 "def.y"
    {defData->dumb_mode = 1;defData->no_num = 1; }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 1548 "def.y"
    {
              if (!defData->viaRule) {
                if (defData->callbacks->ViaCbk) {
                  if (defData->viaWarnings++ < defData->settings->ViaWarnings) {
                    defData->defError(6562, "The PATTERN statement is missing from the VIARULE statement. Ensure that it exists in the VIARULE statement.");
                    CHKERR();
                  }
                }
              } else if (defData->callbacks->ViaCbk)
                 defData->Via.addCutPattern((yyvsp[(4) - (4)].string));
            }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 1561 "def.y"
    { defData->Geometries.startList((yyvsp[(1) - (1)].pt).x, (yyvsp[(1) - (1)].pt).y); }
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 1564 "def.y"
    { defData->Geometries.addToList((yyvsp[(1) - (1)].pt).x, (yyvsp[(1) - (1)].pt).y); }
    break;

  case 250:

/* Line 1806 of yacc.c  */
#line 1571 "def.y"
    {
            defData->save_x = (yyvsp[(2) - (4)].dval);
            defData->save_y = (yyvsp[(3) - (4)].dval);
            (yyval.pt).x = ROUND((yyvsp[(2) - (4)].dval));
            (yyval.pt).y = ROUND((yyvsp[(3) - (4)].dval));
          }
    break;

  case 251:

/* Line 1806 of yacc.c  */
#line 1578 "def.y"
    {
            defData->save_y = (yyvsp[(3) - (4)].dval);
            (yyval.pt).x = ROUND(defData->save_x);
            (yyval.pt).y = ROUND((yyvsp[(3) - (4)].dval));
          }
    break;

  case 252:

/* Line 1806 of yacc.c  */
#line 1584 "def.y"
    {
            defData->save_x = (yyvsp[(2) - (4)].dval);
            (yyval.pt).x = ROUND((yyvsp[(2) - (4)].dval));
            (yyval.pt).y = ROUND(defData->save_y);
          }
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 1590 "def.y"
    {
            (yyval.pt).x = ROUND(defData->save_x);
            (yyval.pt).y = ROUND(defData->save_y);
          }
    break;

  case 254:

/* Line 1806 of yacc.c  */
#line 1596 "def.y"
    { (yyval.integer) = 0; }
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 1598 "def.y"
    { (yyval.integer) = (yyvsp[(3) - (3)].dval); }
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 1601 "def.y"
    { 
          if (defData->callbacks->ViaEndCbk)
            CALLBACK(defData->callbacks->ViaEndCbk, defrViaEndCbkType, 0);
        }
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 1607 "def.y"
    {
          if (defData->callbacks->RegionEndCbk)
            CALLBACK(defData->callbacks->RegionEndCbk, defrRegionEndCbkType, 0);
        }
    break;

  case 258:

/* Line 1806 of yacc.c  */
#line 1613 "def.y"
    {
          if (defData->callbacks->RegionStartCbk)
            CALLBACK(defData->callbacks->RegionStartCbk, defrRegionStartCbkType, ROUND((yyvsp[(2) - (3)].dval)));
        }
    break;

  case 260:

/* Line 1806 of yacc.c  */
#line 1620 "def.y"
    {}
    break;

  case 261:

/* Line 1806 of yacc.c  */
#line 1622 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 262:

/* Line 1806 of yacc.c  */
#line 1623 "def.y"
    {
          if (defData->callbacks->RegionCbk)
             defData->Region.setup((yyvsp[(3) - (3)].string));
          defData->regTypeDef = 0;
        }
    break;

  case 263:

/* Line 1806 of yacc.c  */
#line 1629 "def.y"
    { CALLBACK(defData->callbacks->RegionCbk, defrRegionCbkType, &defData->Region); }
    break;

  case 264:

/* Line 1806 of yacc.c  */
#line 1633 "def.y"
    { if (defData->callbacks->RegionCbk)
          defData->Region.addRect((yyvsp[(1) - (2)].pt).x, (yyvsp[(1) - (2)].pt).y, (yyvsp[(2) - (2)].pt).x, (yyvsp[(2) - (2)].pt).y); }
    break;

  case 265:

/* Line 1806 of yacc.c  */
#line 1636 "def.y"
    { if (defData->callbacks->RegionCbk)
          defData->Region.addRect((yyvsp[(2) - (3)].pt).x, (yyvsp[(2) - (3)].pt).y, (yyvsp[(3) - (3)].pt).x, (yyvsp[(3) - (3)].pt).y); }
    break;

  case 268:

/* Line 1806 of yacc.c  */
#line 1644 "def.y"
    {defData->dumb_mode = DEF_MAX_INT; }
    break;

  case 269:

/* Line 1806 of yacc.c  */
#line 1646 "def.y"
    { defData->dumb_mode = 0; }
    break;

  case 270:

/* Line 1806 of yacc.c  */
#line 1648 "def.y"
    {
           if (defData->regTypeDef) {
              if (defData->callbacks->RegionCbk) {
                if (defData->regionWarnings++ < defData->settings->RegionWarnings) {
                  defData->defError(6563, "The TYPE statement already exists. It has been defined in the REGION statement.");
                  CHKERR();
                }
              }
           }
           if (defData->callbacks->RegionCbk) defData->Region.setType((yyvsp[(3) - (3)].string));
           defData->regTypeDef = 1;
         }
    break;

  case 273:

/* Line 1806 of yacc.c  */
#line 1667 "def.y"
    {
          if (defData->callbacks->RegionCbk) {
             char propTp;
             char* str = defData->ringCopy("                       ");
             propTp = defData->session->RegionProp.propType((yyvsp[(1) - (2)].string));
             CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "REGION");
             // For backword compatibility, also set the string value 
             // We will use a temporary string to store the number.
             // The string space is borrowed from the ring buffer
             // in the lexer.
             sprintf(str, "%g", (yyvsp[(2) - (2)].dval));
             defData->Region.addNumProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].dval), str, propTp);
          }
        }
    break;

  case 274:

/* Line 1806 of yacc.c  */
#line 1682 "def.y"
    {
          if (defData->callbacks->RegionCbk) {
             char propTp;
             propTp = defData->session->RegionProp.propType((yyvsp[(1) - (2)].string));
             CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "REGION");
             defData->Region.addProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
          }
        }
    break;

  case 275:

/* Line 1806 of yacc.c  */
#line 1691 "def.y"
    {
          if (defData->callbacks->RegionCbk) {
             char propTp;
             propTp = defData->session->RegionProp.propType((yyvsp[(1) - (2)].string));
             CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "REGION");
             defData->Region.addProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
          }
        }
    break;

  case 276:

/* Line 1806 of yacc.c  */
#line 1701 "def.y"
    { (yyval.string) = (char*)"FENCE"; }
    break;

  case 277:

/* Line 1806 of yacc.c  */
#line 1703 "def.y"
    { (yyval.string) = (char*)"GUIDE"; }
    break;

  case 278:

/* Line 1806 of yacc.c  */
#line 1706 "def.y"
    {
           if (defData->VersionNum < 5.8) {
                if (defData->componentWarnings++ < defData->settings->ComponentWarnings) {
                   defData->defMsg = (char*)malloc(10000);
                   sprintf (defData->defMsg,
                     "The MASKSHIFT statement is available in version 5.8 and later.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
                   defData->defError(7415, defData->defMsg);
                   free(defData->defMsg);
                   CHKERR();
                }
            }
            if (defData->callbacks->ComponentMaskShiftLayerCbk) {
                CALLBACK(defData->callbacks->ComponentMaskShiftLayerCbk, defrComponentMaskShiftLayerCbkType, &defData->ComponentMaskShiftLayer);
            }
         }
    break;

  case 280:

/* Line 1806 of yacc.c  */
#line 1726 "def.y"
    { 
            if (defData->callbacks->ComponentStartCbk)
              CALLBACK(defData->callbacks->ComponentStartCbk, defrComponentStartCbkType,
                       ROUND((yyvsp[(2) - (3)].dval)));
         }
    break;

  case 283:

/* Line 1806 of yacc.c  */
#line 1737 "def.y"
    {
            if (defData->callbacks->ComponentMaskShiftLayerCbk) {
              defData->ComponentMaskShiftLayer.addMaskShiftLayer((yyvsp[(1) - (1)].string));
            }
        }
    break;

  case 286:

/* Line 1806 of yacc.c  */
#line 1748 "def.y"
    {
            if (defData->callbacks->ComponentCbk)
              CALLBACK(defData->callbacks->ComponentCbk, defrComponentCbkType, &defData->Component);
         }
    break;

  case 287:

/* Line 1806 of yacc.c  */
#line 1754 "def.y"
    {
            defData->dumb_mode = 0;
            defData->no_num = 0;
         }
    break;

  case 288:

/* Line 1806 of yacc.c  */
#line 1759 "def.y"
    {defData->dumb_mode = DEF_MAX_INT; defData->no_num = DEF_MAX_INT; }
    break;

  case 289:

/* Line 1806 of yacc.c  */
#line 1761 "def.y"
    {
            if (defData->callbacks->ComponentCbk)
              defData->Component.IdAndName((yyvsp[(3) - (4)].string), (yyvsp[(4) - (4)].string));
         }
    break;

  case 290:

/* Line 1806 of yacc.c  */
#line 1767 "def.y"
    { }
    break;

  case 291:

/* Line 1806 of yacc.c  */
#line 1769 "def.y"
    {
              if (defData->callbacks->ComponentCbk)
                defData->Component.addNet("*");
            }
    break;

  case 292:

/* Line 1806 of yacc.c  */
#line 1774 "def.y"
    {
              if (defData->callbacks->ComponentCbk)
                defData->Component.addNet((yyvsp[(2) - (2)].string));
            }
    break;

  case 307:

/* Line 1806 of yacc.c  */
#line 1789 "def.y"
    {
          if (defData->callbacks->ComponentCbk)
            CALLBACK(defData->callbacks->ComponentExtCbk, defrComponentExtCbkType,
                     &defData->History_text[0]);
        }
    break;

  case 308:

/* Line 1806 of yacc.c  */
#line 1795 "def.y"
    {defData->dumb_mode=1; defData->no_num = 1; }
    break;

  case 309:

/* Line 1806 of yacc.c  */
#line 1796 "def.y"
    {
          if (defData->callbacks->ComponentCbk)
            defData->Component.setEEQ((yyvsp[(4) - (4)].string));
        }
    break;

  case 310:

/* Line 1806 of yacc.c  */
#line 1801 "def.y"
    { defData->dumb_mode = 2;  defData->no_num = 2; }
    break;

  case 311:

/* Line 1806 of yacc.c  */
#line 1803 "def.y"
    {
          if (defData->callbacks->ComponentCbk)
             defData->Component.setGenerate((yyvsp[(4) - (5)].string), (yyvsp[(5) - (5)].string));
        }
    break;

  case 312:

/* Line 1806 of yacc.c  */
#line 1809 "def.y"
    { (yyval.string) = (char*)""; }
    break;

  case 313:

/* Line 1806 of yacc.c  */
#line 1811 "def.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 314:

/* Line 1806 of yacc.c  */
#line 1814 "def.y"
    {
          if (defData->callbacks->ComponentCbk)
            defData->Component.setSource((yyvsp[(3) - (3)].string));
        }
    break;

  case 315:

/* Line 1806 of yacc.c  */
#line 1820 "def.y"
    { (yyval.string) = (char*)"NETLIST"; }
    break;

  case 316:

/* Line 1806 of yacc.c  */
#line 1822 "def.y"
    { (yyval.string) = (char*)"DIST"; }
    break;

  case 317:

/* Line 1806 of yacc.c  */
#line 1824 "def.y"
    { (yyval.string) = (char*)"USER"; }
    break;

  case 318:

/* Line 1806 of yacc.c  */
#line 1826 "def.y"
    { (yyval.string) = (char*)"TIMING"; }
    break;

  case 319:

/* Line 1806 of yacc.c  */
#line 1831 "def.y"
    { }
    break;

  case 320:

/* Line 1806 of yacc.c  */
#line 1833 "def.y"
    {
          if (defData->callbacks->ComponentCbk)
            defData->Component.setRegionName((yyvsp[(2) - (2)].string));
        }
    break;

  case 321:

/* Line 1806 of yacc.c  */
#line 1839 "def.y"
    { 
          // 11/12/2002 - this is obsolete in 5.5, & will be ignored 
          if (defData->VersionNum < 5.5) {
            if (defData->callbacks->ComponentCbk)
               defData->Component.setRegionBounds((yyvsp[(1) - (2)].pt).x, (yyvsp[(1) - (2)].pt).y, 
                                                            (yyvsp[(2) - (2)].pt).x, (yyvsp[(2) - (2)].pt).y);
          }
          else
            defData->defWarning(7020, "The REGION pt pt statement is obsolete in version 5.5 and later.\nThe DEF parser will ignore this statement.");
        }
    break;

  case 322:

/* Line 1806 of yacc.c  */
#line 1850 "def.y"
    { 
          // 11/12/2002 - this is obsolete in 5.5, & will be ignored 
          if (defData->VersionNum < 5.5) {
            if (defData->callbacks->ComponentCbk)
               defData->Component.setRegionBounds((yyvsp[(2) - (3)].pt).x, (yyvsp[(2) - (3)].pt).y,
                                                            (yyvsp[(3) - (3)].pt).x, (yyvsp[(3) - (3)].pt).y);
          }
          else
            defData->defWarning(7020, "The REGION pt pt statement is obsolete in version 5.5 and later.\nThe DEF parser will ignore this statement.");
        }
    break;

  case 323:

/* Line 1806 of yacc.c  */
#line 1862 "def.y"
    {
          if (defData->VersionNum < 5.6) {
             if (defData->callbacks->ComponentCbk) {
               if (defData->componentWarnings++ < defData->settings->ComponentWarnings) {
                 defData->defMsg = (char*)malloc(1000);
                 sprintf (defData->defMsg,
                    "The HALO statement is a version 5.6 and later syntax.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                 defData->defError(6529, defData->defMsg);
                 free(defData->defMsg);
                 CHKERR();
               }
             }
          }
        }
    break;

  case 324:

/* Line 1806 of yacc.c  */
#line 1877 "def.y"
    {
          if (defData->callbacks->ComponentCbk)
            defData->Component.setHalo((int)(yyvsp[(5) - (8)].dval), (int)(yyvsp[(6) - (8)].dval),
                                                 (int)(yyvsp[(7) - (8)].dval), (int)(yyvsp[(8) - (8)].dval));
        }
    break;

  case 326:

/* Line 1806 of yacc.c  */
#line 1885 "def.y"
    {
        if (defData->VersionNum < 5.7) {
           if (defData->callbacks->ComponentCbk) {
             if (defData->componentWarnings++ < defData->settings->ComponentWarnings) {
                defData->defMsg = (char*)malloc(10000);
                sprintf (defData->defMsg,
                  "The HALO SOFT is available in version 5.7 or later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                defData->defError(6550, defData->defMsg);
                free(defData->defMsg);
                CHKERR();
             }
           }
        } else {
           if (defData->callbacks->ComponentCbk)
             defData->Component.setHaloSoft();
        }
      }
    break;

  case 327:

/* Line 1806 of yacc.c  */
#line 1904 "def.y"
    { defData->dumb_mode = 2; defData->no_num = 2; }
    break;

  case 328:

/* Line 1806 of yacc.c  */
#line 1905 "def.y"
    {
        if (defData->VersionNum < 5.7) {
           if (defData->callbacks->ComponentCbk) {
             if (defData->componentWarnings++ < defData->settings->ComponentWarnings) {
                defData->defMsg = (char*)malloc(10000);
                sprintf (defData->defMsg,
                  "The ROUTEHALO is available in version 5.7 or later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                defData->defError(6551, defData->defMsg);
                free(defData->defMsg);
                CHKERR();
             }
           }
        } else {
           if (defData->callbacks->ComponentCbk)
             defData->Component.setRouteHalo(
                            (int)(yyvsp[(3) - (6)].dval), (yyvsp[(5) - (6)].string), (yyvsp[(6) - (6)].string));
        }
      }
    break;

  case 329:

/* Line 1806 of yacc.c  */
#line 1924 "def.y"
    { defData->dumb_mode = DEF_MAX_INT; }
    break;

  case 330:

/* Line 1806 of yacc.c  */
#line 1926 "def.y"
    { defData->dumb_mode = 0; }
    break;

  case 333:

/* Line 1806 of yacc.c  */
#line 1933 "def.y"
    {
          if (defData->callbacks->ComponentCbk) {
            char propTp;
            char* str = defData->ringCopy("                       ");
            propTp = defData->session->CompProp.propType((yyvsp[(1) - (2)].string));
            CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "COMPONENT");
            sprintf(str, "%g", (yyvsp[(2) - (2)].dval));
            defData->Component.addNumProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].dval), str, propTp);
          }
        }
    break;

  case 334:

/* Line 1806 of yacc.c  */
#line 1944 "def.y"
    {
          if (defData->callbacks->ComponentCbk) {
            char propTp;
            propTp = defData->session->CompProp.propType((yyvsp[(1) - (2)].string));
            CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "COMPONENT");
            defData->Component.addProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
          }
        }
    break;

  case 335:

/* Line 1806 of yacc.c  */
#line 1953 "def.y"
    {
          if (defData->callbacks->ComponentCbk) {
            char propTp;
            propTp = defData->session->CompProp.propType((yyvsp[(1) - (2)].string));
            CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "COMPONENT");
            defData->Component.addProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
          }
        }
    break;

  case 336:

/* Line 1806 of yacc.c  */
#line 1963 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 337:

/* Line 1806 of yacc.c  */
#line 1965 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 338:

/* Line 1806 of yacc.c  */
#line 1967 "def.y"
    { 
          if (defData->VersionNum < 5.6) {
            if (defData->callbacks->ComponentCbk) {
              defData->Component.setForeignName((yyvsp[(4) - (6)].string));
              defData->Component.setForeignLocation((yyvsp[(5) - (6)].pt).x, (yyvsp[(5) - (6)].pt).y, (yyvsp[(6) - (6)].integer));
            }
         } else
            if (defData->callbacks->ComponentCbk)
              if (defData->componentWarnings++ < defData->settings->ComponentWarnings)
                defData->defWarning(7021, "The FOREIGN statement is obsolete in version 5.6 and later.\nThe DEF parser will ignore this statement.");
         }
    break;

  case 339:

/* Line 1806 of yacc.c  */
#line 1981 "def.y"
    { (yyval.pt) = (yyvsp[(1) - (1)].pt); }
    break;

  case 340:

/* Line 1806 of yacc.c  */
#line 1983 "def.y"
    { (yyval.pt).x = ROUND((yyvsp[(1) - (2)].dval)); (yyval.pt).y = ROUND((yyvsp[(2) - (2)].dval)); }
    break;

  case 341:

/* Line 1806 of yacc.c  */
#line 1986 "def.y"
    {
          if (defData->callbacks->ComponentCbk) {
            defData->Component.setPlacementStatus((yyvsp[(1) - (3)].integer));
            defData->Component.setPlacementLocation((yyvsp[(2) - (3)].pt).x, (yyvsp[(2) - (3)].pt).y, (yyvsp[(3) - (3)].integer));
          }
        }
    break;

  case 342:

/* Line 1806 of yacc.c  */
#line 1993 "def.y"
    {
          if (defData->callbacks->ComponentCbk)
            defData->Component.setPlacementStatus(
                                         DEFI_COMPONENT_UNPLACED);
            defData->Component.setPlacementLocation(-1, -1, -1);
        }
    break;

  case 343:

/* Line 1806 of yacc.c  */
#line 2000 "def.y"
    {
          if (defData->VersionNum < 5.4) {   // PCR 495463 
            if (defData->callbacks->ComponentCbk) {
              defData->Component.setPlacementStatus(
                                          DEFI_COMPONENT_UNPLACED);
              defData->Component.setPlacementLocation((yyvsp[(3) - (4)].pt).x, (yyvsp[(3) - (4)].pt).y, (yyvsp[(4) - (4)].integer));
            }
          } else {
            if (defData->componentWarnings++ < defData->settings->ComponentWarnings)
               defData->defWarning(7022, "In the COMPONENT UNPLACED statement, point and orient are invalid in version 5.4 and later.\nThe DEF parser will ignore this statement.");
          }
        }
    break;

  case 344:

/* Line 1806 of yacc.c  */
#line 2014 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 345:

/* Line 1806 of yacc.c  */
#line 2015 "def.y"
    {  
          if (defData->callbacks->ComponentCbk) {
            if (defData->validateMaskShiftInput((yyvsp[(4) - (4)].string), defData->componentWarnings, defData->settings->ComponentWarnings)) {
                defData->Component.setMaskShift((yyvsp[(4) - (4)].string));
            }
          }
        }
    break;

  case 346:

/* Line 1806 of yacc.c  */
#line 2024 "def.y"
    { (yyval.integer) = DEFI_COMPONENT_FIXED; }
    break;

  case 347:

/* Line 1806 of yacc.c  */
#line 2026 "def.y"
    { (yyval.integer) = DEFI_COMPONENT_COVER; }
    break;

  case 348:

/* Line 1806 of yacc.c  */
#line 2028 "def.y"
    { (yyval.integer) = DEFI_COMPONENT_PLACED; }
    break;

  case 349:

/* Line 1806 of yacc.c  */
#line 2031 "def.y"
    {
          if (defData->callbacks->ComponentCbk)
            defData->Component.setWeight(ROUND((yyvsp[(3) - (3)].dval)));
        }
    break;

  case 350:

/* Line 1806 of yacc.c  */
#line 2037 "def.y"
    { 
          if (defData->callbacks->ComponentCbk)
            CALLBACK(defData->callbacks->ComponentEndCbk, defrComponentEndCbkType, 0);
        }
    break;

  case 352:

/* Line 1806 of yacc.c  */
#line 2046 "def.y"
    { 
          if (defData->callbacks->NetStartCbk)
            CALLBACK(defData->callbacks->NetStartCbk, defrNetStartCbkType, ROUND((yyvsp[(2) - (3)].dval)));
          defData->netOsnet = 1;
        }
    break;

  case 355:

/* Line 1806 of yacc.c  */
#line 2057 "def.y"
    { 
          if (defData->callbacks->NetCbk)
            CALLBACK(defData->callbacks->NetCbk, defrNetCbkType, &defData->Net);
        }
    break;

  case 356:

/* Line 1806 of yacc.c  */
#line 2068 "def.y"
    {defData->dumb_mode = 0; defData->no_num = 0; }
    break;

  case 357:

/* Line 1806 of yacc.c  */
#line 2071 "def.y"
    {defData->dumb_mode = DEF_MAX_INT; defData->no_num = DEF_MAX_INT; defData->nondef_is_keyword = TRUE; defData->mustjoin_is_keyword = TRUE;}
    break;

  case 359:

/* Line 1806 of yacc.c  */
#line 2074 "def.y"
    {
          // 9/22/1999 
          // this is shared by both net and special net 
          if ((defData->callbacks->NetCbk && (defData->netOsnet==1)) || (defData->callbacks->SNetCbk && (defData->netOsnet==2)))
            defData->Net.setName((yyvsp[(1) - (1)].string));
          if (defData->callbacks->NetNameCbk)
            CALLBACK(defData->callbacks->NetNameCbk, defrNetNameCbkType, (yyvsp[(1) - (1)].string));
        }
    break;

  case 361:

/* Line 1806 of yacc.c  */
#line 2082 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1;}
    break;

  case 362:

/* Line 1806 of yacc.c  */
#line 2083 "def.y"
    {
          if ((defData->callbacks->NetCbk && (defData->netOsnet==1)) || (defData->callbacks->SNetCbk && (defData->netOsnet==2)))
            defData->Net.addMustPin((yyvsp[(3) - (6)].string), (yyvsp[(5) - (6)].string), 0);
          defData->dumb_mode = 3;
          defData->no_num = 3;
        }
    break;

  case 365:

/* Line 1806 of yacc.c  */
#line 2094 "def.y"
    {defData->dumb_mode = DEF_MAX_INT; defData->no_num = DEF_MAX_INT;}
    break;

  case 366:

/* Line 1806 of yacc.c  */
#line 2096 "def.y"
    {
          // 9/22/1999 
          // since the code is shared by both net & special net, 
          // need to check on both flags 
          if ((defData->callbacks->NetCbk && (defData->netOsnet==1)) || (defData->callbacks->SNetCbk && (defData->netOsnet==2)))
            defData->Net.addPin((yyvsp[(2) - (6)].string), (yyvsp[(4) - (6)].string), (yyvsp[(5) - (6)].integer));
          // 1/14/2000 - pcr 289156 
          // reset defData->dumb_mode & defData->no_num to 3 , just in case 
          // the next statement is another net_connection 
          defData->dumb_mode = 3;
          defData->no_num = 3;
        }
    break;

  case 367:

/* Line 1806 of yacc.c  */
#line 2108 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1;}
    break;

  case 368:

/* Line 1806 of yacc.c  */
#line 2109 "def.y"
    {
          if ((defData->callbacks->NetCbk && (defData->netOsnet==1)) || (defData->callbacks->SNetCbk && (defData->netOsnet==2)))
            defData->Net.addPin("*", (yyvsp[(4) - (6)].string), (yyvsp[(5) - (6)].integer));
          defData->dumb_mode = 3;
          defData->no_num = 3;
        }
    break;

  case 369:

/* Line 1806 of yacc.c  */
#line 2115 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1;}
    break;

  case 370:

/* Line 1806 of yacc.c  */
#line 2116 "def.y"
    {
          if ((defData->callbacks->NetCbk && (defData->netOsnet==1)) || (defData->callbacks->SNetCbk && (defData->netOsnet==2)))
            defData->Net.addPin("PIN", (yyvsp[(4) - (6)].string), (yyvsp[(5) - (6)].integer));
          defData->dumb_mode = 3;
          defData->no_num = 3;
        }
    break;

  case 371:

/* Line 1806 of yacc.c  */
#line 2124 "def.y"
    { (yyval.integer) = 0; }
    break;

  case 372:

/* Line 1806 of yacc.c  */
#line 2126 "def.y"
    {
          if (defData->callbacks->NetConnectionExtCbk)
            CALLBACK(defData->callbacks->NetConnectionExtCbk, defrNetConnectionExtCbkType,
              &defData->History_text[0]);
          (yyval.integer) = 0;
        }
    break;

  case 373:

/* Line 1806 of yacc.c  */
#line 2133 "def.y"
    { (yyval.integer) = 1; }
    break;

  case 376:

/* Line 1806 of yacc.c  */
#line 2142 "def.y"
    {  
          if (defData->callbacks->NetCbk) defData->Net.addWire((yyvsp[(2) - (2)].string), NULL);
        }
    break;

  case 377:

/* Line 1806 of yacc.c  */
#line 2146 "def.y"
    {
          defData->by_is_keyword = FALSE;
          defData->do_is_keyword = FALSE;
          defData->new_is_keyword = FALSE;
          defData->nondef_is_keyword = FALSE;
          defData->mustjoin_is_keyword = FALSE;
          defData->step_is_keyword = FALSE;
          defData->orient_is_keyword = FALSE;
          defData->virtual_is_keyword = FALSE;
          defData->rect_is_keyword = FALSE;
          defData->mask_is_keyword = FALSE;
          defData->needNPCbk = 0;
        }
    break;

  case 378:

/* Line 1806 of yacc.c  */
#line 2161 "def.y"
    { if (defData->callbacks->NetCbk) defData->Net.setSource((yyvsp[(3) - (3)].string)); }
    break;

  case 379:

/* Line 1806 of yacc.c  */
#line 2164 "def.y"
    {
          if (defData->VersionNum < 5.5) {
            if (defData->callbacks->NetCbk) {
              if (defData->netWarnings++ < defData->settings->NetWarnings) {
                 defData->defMsg = (char*)malloc(1000);
                 sprintf (defData->defMsg,
                    "The FIXEDBUMP statement is available in version 5.5 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                 defData->defError(6530, defData->defMsg);
                 free(defData->defMsg);
                 CHKERR();
              }
            }
          }
          if (defData->callbacks->NetCbk) defData->Net.setFixedbump();
        }
    break;

  case 380:

/* Line 1806 of yacc.c  */
#line 2180 "def.y"
    { defData->real_num = 1; }
    break;

  case 381:

/* Line 1806 of yacc.c  */
#line 2181 "def.y"
    {
          if (defData->VersionNum < 5.5) {
            if (defData->callbacks->NetCbk) {
              if (defData->netWarnings++ < defData->settings->NetWarnings) {
                 defData->defMsg = (char*)malloc(1000);
                 sprintf (defData->defMsg,
                    "The FREQUENCY statement is a version 5.5 and later syntax.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
                 defData->defError(6558, defData->defMsg);
                 free(defData->defMsg);
                 CHKERR();
              }
            }
          }
          if (defData->callbacks->NetCbk) defData->Net.setFrequency((yyvsp[(4) - (4)].dval));
          defData->real_num = 0;
        }
    break;

  case 382:

/* Line 1806 of yacc.c  */
#line 2198 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1;}
    break;

  case 383:

/* Line 1806 of yacc.c  */
#line 2199 "def.y"
    { if (defData->callbacks->NetCbk) defData->Net.setOriginal((yyvsp[(4) - (4)].string)); }
    break;

  case 384:

/* Line 1806 of yacc.c  */
#line 2202 "def.y"
    { if (defData->callbacks->NetCbk) defData->Net.setPattern((yyvsp[(3) - (3)].string)); }
    break;

  case 385:

/* Line 1806 of yacc.c  */
#line 2205 "def.y"
    { if (defData->callbacks->NetCbk) defData->Net.setWeight(ROUND((yyvsp[(3) - (3)].dval))); }
    break;

  case 386:

/* Line 1806 of yacc.c  */
#line 2208 "def.y"
    { if (defData->callbacks->NetCbk) defData->Net.setXTalk(ROUND((yyvsp[(3) - (3)].dval))); }
    break;

  case 387:

/* Line 1806 of yacc.c  */
#line 2211 "def.y"
    { if (defData->callbacks->NetCbk) defData->Net.setCap((yyvsp[(3) - (3)].dval)); }
    break;

  case 388:

/* Line 1806 of yacc.c  */
#line 2214 "def.y"
    { if (defData->callbacks->NetCbk) defData->Net.setUse((yyvsp[(3) - (3)].string)); }
    break;

  case 389:

/* Line 1806 of yacc.c  */
#line 2217 "def.y"
    { if (defData->callbacks->NetCbk) defData->Net.setStyle((int)(yyvsp[(3) - (3)].dval)); }
    break;

  case 390:

/* Line 1806 of yacc.c  */
#line 2219 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 391:

/* Line 1806 of yacc.c  */
#line 2220 "def.y"
    { 
          if (defData->callbacks->NetCbk && defData->callbacks->NetNonDefaultRuleCbk) {
             // User wants a callback on nondefaultrule 
             CALLBACK(defData->callbacks->NetNonDefaultRuleCbk,
                      defrNetNonDefaultRuleCbkType, (yyvsp[(4) - (4)].string));
          }
          // Still save data in the class 
          if (defData->callbacks->NetCbk) defData->Net.setNonDefaultRule((yyvsp[(4) - (4)].string));
        }
    break;

  case 393:

/* Line 1806 of yacc.c  */
#line 2232 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 394:

/* Line 1806 of yacc.c  */
#line 2233 "def.y"
    { if (defData->callbacks->NetCbk) defData->Net.addShieldNet((yyvsp[(4) - (4)].string)); }
    break;

  case 395:

/* Line 1806 of yacc.c  */
#line 2235 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 396:

/* Line 1806 of yacc.c  */
#line 2236 "def.y"
    { // since the parser still support 5.3 and earlier, can't 
          // move NOSHIELD in net_type 
          if (defData->VersionNum < 5.4) {   // PCR 445209 
            if (defData->callbacks->NetCbk) defData->Net.addNoShield("");
            defData->by_is_keyword = FALSE;
            defData->do_is_keyword = FALSE;
            defData->new_is_keyword = FALSE;
            defData->step_is_keyword = FALSE;
            defData->orient_is_keyword = FALSE;
            defData->virtual_is_keyword = FALSE;
            defData->mask_is_keyword = FALSE;
            defData->rect_is_keyword = FALSE;
            defData->shield = TRUE;    // save the path info in the defData->shield paths 
          } else
            if (defData->callbacks->NetCbk) defData->Net.addWire("NOSHIELD", NULL);
        }
    break;

  case 397:

/* Line 1806 of yacc.c  */
#line 2253 "def.y"
    {
          if (defData->VersionNum < 5.4) {   // PCR 445209 
            defData->shield = FALSE;
            defData->by_is_keyword = FALSE;
            defData->do_is_keyword = FALSE;
            defData->new_is_keyword = FALSE;
            defData->step_is_keyword = FALSE;
            defData->nondef_is_keyword = FALSE;
            defData->mustjoin_is_keyword = FALSE;
            defData->orient_is_keyword = FALSE;
            defData->virtual_is_keyword = FALSE;
            defData->rect_is_keyword = FALSE;
            defData->mask_is_keyword = FALSE;
          } else {
            defData->by_is_keyword = FALSE;
            defData->do_is_keyword = FALSE;
            defData->new_is_keyword = FALSE;
            defData->step_is_keyword = FALSE;
            defData->nondef_is_keyword = FALSE;
            defData->mustjoin_is_keyword = FALSE;
            defData->orient_is_keyword = FALSE;
            defData->virtual_is_keyword = FALSE;
            defData->rect_is_keyword = FALSE;
            defData->mask_is_keyword = FALSE;
          }
          defData->needNPCbk = 0;
        }
    break;

  case 398:

/* Line 1806 of yacc.c  */
#line 2282 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1;
          if (defData->callbacks->NetCbk) {
            defData->Subnet = new defiSubnet(defData);
          }
        }
    break;

  case 399:

/* Line 1806 of yacc.c  */
#line 2287 "def.y"
    {
          if (defData->callbacks->NetCbk && defData->callbacks->NetSubnetNameCbk) {
            // User wants a callback on Net subnetName 
            CALLBACK(defData->callbacks->NetSubnetNameCbk, defrNetSubnetNameCbkType, (yyvsp[(4) - (4)].string));
          }
          // Still save the subnet name in the class 
          if (defData->callbacks->NetCbk) {
            defData->Subnet->setName((yyvsp[(4) - (4)].string));
          }
        }
    break;

  case 400:

/* Line 1806 of yacc.c  */
#line 2297 "def.y"
    {
          defData->routed_is_keyword = TRUE;
          defData->fixed_is_keyword = TRUE;
          defData->cover_is_keyword = TRUE;
        }
    break;

  case 401:

/* Line 1806 of yacc.c  */
#line 2301 "def.y"
    {
          if (defData->callbacks->NetCbk) {
            defData->Net.addSubnet(defData->Subnet);
            defData->Subnet = NULL;
            defData->routed_is_keyword = FALSE;
            defData->fixed_is_keyword = FALSE;
            defData->cover_is_keyword = FALSE;
          }
        }
    break;

  case 402:

/* Line 1806 of yacc.c  */
#line 2311 "def.y"
    {defData->dumb_mode = DEF_MAX_INT; }
    break;

  case 403:

/* Line 1806 of yacc.c  */
#line 2313 "def.y"
    { defData->dumb_mode = 0; }
    break;

  case 404:

/* Line 1806 of yacc.c  */
#line 2316 "def.y"
    { 
          if (defData->callbacks->NetExtCbk)
            CALLBACK(defData->callbacks->NetExtCbk, defrNetExtCbkType, &defData->History_text[0]);
        }
    break;

  case 407:

/* Line 1806 of yacc.c  */
#line 2326 "def.y"
    {
          if (defData->callbacks->NetCbk) {
            char propTp;
            char* str = defData->ringCopy("                       ");
            propTp = defData->session->NetProp.propType((yyvsp[(1) - (2)].string));
            CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "NET");
            sprintf(str, "%g", (yyvsp[(2) - (2)].dval));
            defData->Net.addNumProp((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].dval), str, propTp);
          }
        }
    break;

  case 408:

/* Line 1806 of yacc.c  */
#line 2337 "def.y"
    {
          if (defData->callbacks->NetCbk) {
            char propTp;
            propTp = defData->session->NetProp.propType((yyvsp[(1) - (2)].string));
            CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "NET");
            defData->Net.addProp((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
          }
        }
    break;

  case 409:

/* Line 1806 of yacc.c  */
#line 2346 "def.y"
    {
          if (defData->callbacks->NetCbk) {
            char propTp;
            propTp = defData->session->NetProp.propType((yyvsp[(1) - (2)].string));
            CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "NET");
            defData->Net.addProp((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
          }
        }
    break;

  case 410:

/* Line 1806 of yacc.c  */
#line 2356 "def.y"
    { (yyval.string) = (char*)"NETLIST"; }
    break;

  case 411:

/* Line 1806 of yacc.c  */
#line 2358 "def.y"
    { (yyval.string) = (char*)"DIST"; }
    break;

  case 412:

/* Line 1806 of yacc.c  */
#line 2360 "def.y"
    { (yyval.string) = (char*)"USER"; }
    break;

  case 413:

/* Line 1806 of yacc.c  */
#line 2362 "def.y"
    { (yyval.string) = (char*)"TIMING"; }
    break;

  case 414:

/* Line 1806 of yacc.c  */
#line 2364 "def.y"
    { (yyval.string) = (char*)"TEST"; }
    break;

  case 415:

/* Line 1806 of yacc.c  */
#line 2367 "def.y"
    {
          // vpin_options may have to deal with orient 
          defData->orient_is_keyword = TRUE;
        }
    break;

  case 416:

/* Line 1806 of yacc.c  */
#line 2372 "def.y"
    { if (defData->callbacks->NetCbk)
            defData->Net.addVpinBounds((yyvsp[(3) - (6)].pt).x, (yyvsp[(3) - (6)].pt).y, (yyvsp[(4) - (6)].pt).x, (yyvsp[(4) - (6)].pt).y);
          defData->orient_is_keyword = FALSE;
        }
    break;

  case 417:

/* Line 1806 of yacc.c  */
#line 2377 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1;}
    break;

  case 418:

/* Line 1806 of yacc.c  */
#line 2378 "def.y"
    { if (defData->callbacks->NetCbk) defData->Net.addVpin((yyvsp[(4) - (4)].string)); }
    break;

  case 420:

/* Line 1806 of yacc.c  */
#line 2381 "def.y"
    {defData->dumb_mode=1;}
    break;

  case 421:

/* Line 1806 of yacc.c  */
#line 2382 "def.y"
    { if (defData->callbacks->NetCbk) defData->Net.addVpinLayer((yyvsp[(3) - (3)].string)); }
    break;

  case 423:

/* Line 1806 of yacc.c  */
#line 2386 "def.y"
    { if (defData->callbacks->NetCbk) defData->Net.addVpinLoc((yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].pt).x, (yyvsp[(2) - (3)].pt).y, (yyvsp[(3) - (3)].integer)); }
    break;

  case 424:

/* Line 1806 of yacc.c  */
#line 2389 "def.y"
    { (yyval.string) = (char*)"PLACED"; }
    break;

  case 425:

/* Line 1806 of yacc.c  */
#line 2391 "def.y"
    { (yyval.string) = (char*)"FIXED"; }
    break;

  case 426:

/* Line 1806 of yacc.c  */
#line 2393 "def.y"
    { (yyval.string) = (char*)"COVER"; }
    break;

  case 427:

/* Line 1806 of yacc.c  */
#line 2396 "def.y"
    { (yyval.string) = (char*)"FIXED"; defData->dumb_mode = 1; }
    break;

  case 428:

/* Line 1806 of yacc.c  */
#line 2398 "def.y"
    { (yyval.string) = (char*)"COVER"; defData->dumb_mode = 1; }
    break;

  case 429:

/* Line 1806 of yacc.c  */
#line 2400 "def.y"
    { (yyval.string) = (char*)"ROUTED"; defData->dumb_mode = 1; }
    break;

  case 430:

/* Line 1806 of yacc.c  */
#line 2404 "def.y"
    { if (defData->NeedPathData && defData->callbacks->NetCbk)
          defData->pathIsDone(defData->shield, 0, defData->netOsnet, &defData->needNPCbk);
      }
    break;

  case 431:

/* Line 1806 of yacc.c  */
#line 2408 "def.y"
    { }
    break;

  case 432:

/* Line 1806 of yacc.c  */
#line 2410 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 433:

/* Line 1806 of yacc.c  */
#line 2411 "def.y"
    { if (defData->NeedPathData && defData->callbacks->NetCbk)
          defData->pathIsDone(defData->shield, 0, defData->netOsnet, &defData->needNPCbk);
      }
    break;

  case 434:

/* Line 1806 of yacc.c  */
#line 2416 "def.y"
    {
        if ((strcmp((yyvsp[(1) - (1)].string), "TAPER") == 0) || (strcmp((yyvsp[(1) - (1)].string), "TAPERRULE") == 0)) {
          if (defData->NeedPathData && defData->callbacks->NetCbk) {
            if (defData->netWarnings++ < defData->settings->NetWarnings) {
              defData->defError(6531, "The layerName which is required in path is missing. Include the layerName in the path and then try again.");
              CHKERR();
            }
          }
          // Since there is already error, the next token is insignificant 
          defData->dumb_mode = 1; defData->no_num = 1;
        } else {
          // CCR 766289 - Do not accummulate the layer information if there 
          // is not a callback set 
          if (defData->NeedPathData && defData->callbacks->NetCbk)
              defData->PathObj.addLayer((yyvsp[(1) - (1)].string));
          defData->dumb_mode = 0; defData->no_num = 0;
        }
      }
    break;

  case 435:

/* Line 1806 of yacc.c  */
#line 2435 "def.y"
    { defData->dumb_mode = DEF_MAX_INT; defData->by_is_keyword = TRUE; defData->do_is_keyword = TRUE;
/*
       dumb_mode = 1; by_is_keyword = TRUE; do_is_keyword = TRUE;
*/
        defData->new_is_keyword = TRUE; defData->step_is_keyword = TRUE; 
        defData->orient_is_keyword = TRUE; defData->virtual_is_keyword = TRUE;
        defData->mask_is_keyword = TRUE, defData->rect_is_keyword = TRUE;  }
    break;

  case 436:

/* Line 1806 of yacc.c  */
#line 2445 "def.y"
    { defData->dumb_mode = 0;   defData->virtual_is_keyword = FALSE; defData->mask_is_keyword = FALSE,
       defData->rect_is_keyword = FALSE; }
    break;

  case 437:

/* Line 1806 of yacc.c  */
#line 2450 "def.y"
    {
      if (defData->VersionNum < 5.8) {
              if (defData->callbacks->SNetCbk) {
                if (defData->sNetWarnings++ < defData->settings->SNetWarnings) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The VIRTUAL statement is available in version 5.8 and later.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
                  defData->defError(6536, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
          }
    }
    break;

  case 438:

/* Line 1806 of yacc.c  */
#line 2467 "def.y"
    {
      if (defData->VersionNum < 5.8) {
              if (defData->callbacks->SNetCbk) {
                if (defData->sNetWarnings++ < defData->settings->SNetWarnings) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The RECT statement is available in version 5.8 and later.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
                  defData->defError(6536, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
      }
    }
    break;

  case 441:

/* Line 1806 of yacc.c  */
#line 2490 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
            (defData->callbacks->SNetCbk && (defData->netOsnet==2)))) {
          if (strcmp((yyvsp[(1) - (1)].string), "TAPER") == 0)
            defData->PathObj.setTaper();
          else {
            defData->PathObj.addVia((yyvsp[(1) - (1)].string));
            }
        }
      }
    break;

  case 442:

/* Line 1806 of yacc.c  */
#line 2501 "def.y"
    {
        if (defData->validateMaskInput((int)(yyvsp[(2) - (3)].dval), defData->sNetWarnings, defData->settings->SNetWarnings)) {
            if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
                (defData->callbacks->SNetCbk && (defData->netOsnet==2)))) {
              if (strcmp((yyvsp[(3) - (3)].string), "TAPER") == 0)
                defData->PathObj.setTaper();
              else {
                defData->PathObj.addViaMask((yyvsp[(2) - (3)].dval));
                defData->PathObj.addVia((yyvsp[(3) - (3)].string));
                }
            }
        }
      }
    break;

  case 443:

/* Line 1806 of yacc.c  */
#line 2515 "def.y"
    { if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
            (defData->callbacks->SNetCbk && (defData->netOsnet==2)))) {
            defData->PathObj.addVia((yyvsp[(1) - (2)].string));
            defData->PathObj.addViaRotation((yyvsp[(2) - (2)].integer));
        }
      }
    break;

  case 444:

/* Line 1806 of yacc.c  */
#line 2522 "def.y"
    { 
        if (defData->validateMaskInput((int)(yyvsp[(2) - (4)].dval), defData->sNetWarnings, defData->settings->SNetWarnings)) {
            if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
                (defData->callbacks->SNetCbk && (defData->netOsnet==2)))) {
                defData->PathObj.addViaMask((yyvsp[(2) - (4)].dval));
                defData->PathObj.addVia((yyvsp[(3) - (4)].string));
                defData->PathObj.addViaRotation((yyvsp[(4) - (4)].integer));
            }
        }
      }
    break;

  case 445:

/* Line 1806 of yacc.c  */
#line 2533 "def.y"
    {
        if (defData->validateMaskInput((int)(yyvsp[(2) - (10)].dval), defData->sNetWarnings, defData->settings->SNetWarnings)) {      
            if (((yyvsp[(5) - (10)].dval) == 0) || ((yyvsp[(7) - (10)].dval) == 0)) {
              if (defData->NeedPathData &&
                  defData->callbacks->SNetCbk) {
                if (defData->netWarnings++ < defData->settings->NetWarnings) {
                  defData->defError(6533, "Either the numX or numY in the VIA DO statement has the value. The value specified is 0.\nUpdate your DEF file with the correct value and then try again.\n");
                  CHKERR();
                }
              }
            }
            if (defData->NeedPathData && (defData->callbacks->SNetCbk && (defData->netOsnet==2))) {
                defData->PathObj.addViaMask((yyvsp[(2) - (10)].dval));
                defData->PathObj.addVia((yyvsp[(3) - (10)].string));
                defData->PathObj.addViaData((int)(yyvsp[(5) - (10)].dval), (int)(yyvsp[(7) - (10)].dval), (int)(yyvsp[(9) - (10)].dval), (int)(yyvsp[(10) - (10)].dval));
            }  else if (defData->NeedPathData && (defData->callbacks->NetCbk && (defData->netOsnet==1))) {
              if (defData->netWarnings++ < defData->settings->NetWarnings) {
                defData->defError(6567, "The VIA DO statement is defined in the NET statement and is invalid.\nRemove this statement from your DEF file and try again.");
                CHKERR();
              }
            }
        }
      }
    break;

  case 446:

/* Line 1806 of yacc.c  */
#line 2557 "def.y"
    {
        if (defData->VersionNum < 5.5) {
          if (defData->NeedPathData && 
              defData->callbacks->SNetCbk) {
            if (defData->netWarnings++ < defData->settings->NetWarnings) {
              defData->defMsg = (char*)malloc(1000);
              sprintf (defData->defMsg,
                 "The VIA DO statement is available in version 5.5 and later.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
              defData->defError(6532, defData->defMsg);
              free(defData->defMsg);
              CHKERR();
            }
          }
        }
        if (((yyvsp[(3) - (8)].dval) == 0) || ((yyvsp[(5) - (8)].dval) == 0)) {
          if (defData->NeedPathData &&
              defData->callbacks->SNetCbk) {
            if (defData->netWarnings++ < defData->settings->NetWarnings) {
              defData->defError(6533, "Either the numX or numY in the VIA DO statement has the value. The value specified is 0.\nUpdate your DEF file with the correct value and then try again.\n");
              CHKERR();
            }
          }
        }
        if (defData->NeedPathData && (defData->callbacks->SNetCbk && (defData->netOsnet==2))) {
            defData->PathObj.addVia((yyvsp[(1) - (8)].string));
            defData->PathObj.addViaData((int)(yyvsp[(3) - (8)].dval), (int)(yyvsp[(5) - (8)].dval), (int)(yyvsp[(7) - (8)].dval), (int)(yyvsp[(8) - (8)].dval));
        }  else if (defData->NeedPathData && (defData->callbacks->NetCbk && (defData->netOsnet==1))) {
          if (defData->netWarnings++ < defData->settings->NetWarnings) {
            defData->defError(6567, "The VIA DO statement is defined in the NET statement and is invalid.\nRemove this statement from your DEF file and try again.");
            CHKERR();
          }
        }
      }
    break;

  case 447:

/* Line 1806 of yacc.c  */
#line 2591 "def.y"
    {
        if (defData->VersionNum < 5.5) {
          if (defData->NeedPathData &&
              defData->callbacks->SNetCbk) {
            if (defData->netWarnings++ < defData->settings->NetWarnings) {
              defData->defMsg = (char*)malloc(1000);
              sprintf (defData->defMsg,
                 "The VIA DO statement is available in version 5.5 and later.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
              defData->defError(6532, defData->defMsg);
              CHKERR();
            }
          }
        }
        if (((yyvsp[(4) - (9)].dval) == 0) || ((yyvsp[(6) - (9)].dval) == 0)) {
          if (defData->NeedPathData &&
              defData->callbacks->SNetCbk) {
            if (defData->netWarnings++ < defData->settings->NetWarnings) {
              defData->defError(6533, "Either the numX or numY in the VIA DO statement has the value. The value specified is 0.\nUpdate your DEF file with the correct value and then try again.\n");
              CHKERR();
            }
          }
        }
        if (defData->NeedPathData && (defData->callbacks->SNetCbk && (defData->netOsnet==2))) {
            defData->PathObj.addVia((yyvsp[(1) - (9)].string));
            defData->PathObj.addViaRotation((yyvsp[(2) - (9)].integer));
            defData->PathObj.addViaData((int)(yyvsp[(4) - (9)].dval), (int)(yyvsp[(6) - (9)].dval), (int)(yyvsp[(8) - (9)].dval), (int)(yyvsp[(9) - (9)].dval));
        } else if (defData->NeedPathData && (defData->callbacks->NetCbk && (defData->netOsnet==1))) {
          if (defData->netWarnings++ < defData->settings->NetWarnings) {
            defData->defError(6567, "The VIA DO statement is defined in the NET statement and is invalid.\nRemove this statement from your DEF file and try again.");
            CHKERR();
          }
        }
      }
    break;

  case 448:

/* Line 1806 of yacc.c  */
#line 2625 "def.y"
    {
        if (defData->validateMaskInput((int)(yyvsp[(2) - (11)].dval), defData->sNetWarnings, defData->settings->SNetWarnings)) {
            if (((yyvsp[(6) - (11)].dval) == 0) || ((yyvsp[(8) - (11)].dval) == 0)) {
              if (defData->NeedPathData &&
                  defData->callbacks->SNetCbk) {
                if (defData->netWarnings++ < defData->settings->NetWarnings) {
                  defData->defError(6533, "Either the numX or numY in the VIA DO statement has the value. The value specified is 0.\nUpdate your DEF file with the correct value and then try again.\n");
                  CHKERR();
                }
              }
            }
            if (defData->NeedPathData && (defData->callbacks->SNetCbk && (defData->netOsnet==2))) {
                defData->PathObj.addViaMask((yyvsp[(2) - (11)].dval)); 
                defData->PathObj.addVia((yyvsp[(3) - (11)].string));
                defData->PathObj.addViaRotation((yyvsp[(4) - (11)].integer));;
                defData->PathObj.addViaData((int)(yyvsp[(6) - (11)].dval), (int)(yyvsp[(8) - (11)].dval), (int)(yyvsp[(10) - (11)].dval), (int)(yyvsp[(11) - (11)].dval));
            } else if (defData->NeedPathData && (defData->callbacks->NetCbk && (defData->netOsnet==1))) {
              if (defData->netWarnings++ < defData->settings->NetWarnings) {
                defData->defError(6567, "The VIA DO statement is defined in the NET statement and is invalid.\nRemove this statement from your DEF file and try again.");
                CHKERR();
              }
            }
        }
      }
    break;

  case 451:

/* Line 1806 of yacc.c  */
#line 2651 "def.y"
    { defData->dumb_mode = 6; }
    break;

  case 452:

/* Line 1806 of yacc.c  */
#line 2652 "def.y"
    {
      if (defData->validateMaskInput((int)(yyvsp[(2) - (10)].dval), defData->sNetWarnings, defData->settings->SNetWarnings)) {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2)))) {
          defData->PathObj.addMask((yyvsp[(2) - (10)].dval));
          defData->PathObj.addViaRect((yyvsp[(6) - (10)].dval), (yyvsp[(7) - (10)].dval), (yyvsp[(8) - (10)].dval), (yyvsp[(9) - (10)].dval));
        }
      }
    }
    break;

  case 453:

/* Line 1806 of yacc.c  */
#line 2662 "def.y"
    {
       if (defData->validateMaskInput((int)(yyvsp[(2) - (2)].dval), defData->sNetWarnings, defData->settings->SNetWarnings)) {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2)))) {
          defData->PathObj.addMask((yyvsp[(2) - (2)].dval)); 
        }
       }  
    }
    break;

  case 455:

/* Line 1806 of yacc.c  */
#line 2672 "def.y"
    {
       // reset defData->dumb_mode to 1 just incase the next token is a via of the path
        // 2/5/2004 - pcr 686781
        defData->dumb_mode = DEF_MAX_INT; defData->by_is_keyword = TRUE; defData->do_is_keyword = TRUE;
        defData->new_is_keyword = TRUE; defData->step_is_keyword = TRUE;
        defData->orient_is_keyword = TRUE;
    }
    break;

  case 456:

/* Line 1806 of yacc.c  */
#line 2683 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addPoint(ROUND((yyvsp[(2) - (4)].dval)), ROUND((yyvsp[(3) - (4)].dval))); 
        defData->save_x = (yyvsp[(2) - (4)].dval);
        defData->save_y = (yyvsp[(3) - (4)].dval); 
      }
    break;

  case 457:

/* Line 1806 of yacc.c  */
#line 2691 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addPoint(ROUND(defData->save_x), ROUND((yyvsp[(3) - (4)].dval))); 
        defData->save_y = (yyvsp[(3) - (4)].dval);
      }
    break;

  case 458:

/* Line 1806 of yacc.c  */
#line 2698 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addPoint(ROUND((yyvsp[(2) - (4)].dval)), ROUND(defData->save_y)); 
        defData->save_x = (yyvsp[(2) - (4)].dval);
      }
    break;

  case 459:

/* Line 1806 of yacc.c  */
#line 2705 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
            (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addPoint(ROUND(defData->save_x), ROUND(defData->save_y)); 
      }
    break;

  case 460:

/* Line 1806 of yacc.c  */
#line 2711 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
            (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addFlushPoint(ROUND((yyvsp[(2) - (5)].dval)), ROUND((yyvsp[(3) - (5)].dval)), ROUND((yyvsp[(4) - (5)].dval))); 
        defData->save_x = (yyvsp[(2) - (5)].dval);
        defData->save_y = (yyvsp[(3) - (5)].dval);
      }
    break;

  case 461:

/* Line 1806 of yacc.c  */
#line 2719 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addFlushPoint(ROUND(defData->save_x), ROUND((yyvsp[(3) - (5)].dval)),
          ROUND((yyvsp[(4) - (5)].dval))); 
        defData->save_y = (yyvsp[(3) - (5)].dval);
      }
    break;

  case 462:

/* Line 1806 of yacc.c  */
#line 2727 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addFlushPoint(ROUND((yyvsp[(2) - (5)].dval)), ROUND(defData->save_y),
          ROUND((yyvsp[(4) - (5)].dval))); 
        defData->save_x = (yyvsp[(2) - (5)].dval);
      }
    break;

  case 463:

/* Line 1806 of yacc.c  */
#line 2735 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addFlushPoint(ROUND(defData->save_x), ROUND(defData->save_y),
          ROUND((yyvsp[(4) - (5)].dval))); 
      }
    break;

  case 464:

/* Line 1806 of yacc.c  */
#line 2744 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addVirtualPoint(ROUND((yyvsp[(2) - (4)].dval)), ROUND((yyvsp[(3) - (4)].dval))); 
        defData->save_x = (yyvsp[(2) - (4)].dval);
        defData->save_y = (yyvsp[(3) - (4)].dval);
      }
    break;

  case 465:

/* Line 1806 of yacc.c  */
#line 2752 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addVirtualPoint(ROUND(defData->save_x), ROUND((yyvsp[(3) - (4)].dval))); 
        defData->save_y = (yyvsp[(3) - (4)].dval);
      }
    break;

  case 466:

/* Line 1806 of yacc.c  */
#line 2759 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addVirtualPoint(ROUND((yyvsp[(2) - (4)].dval)), ROUND(defData->save_y)); 
        defData->save_x = (yyvsp[(2) - (4)].dval);
      }
    break;

  case 467:

/* Line 1806 of yacc.c  */
#line 2766 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addVirtualPoint(ROUND(defData->save_x), ROUND(defData->save_y));
      }
    break;

  case 468:

/* Line 1806 of yacc.c  */
#line 2774 "def.y"
    {
        if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2)))) {
          defData->PathObj.addViaRect((yyvsp[(2) - (6)].dval), (yyvsp[(3) - (6)].dval), (yyvsp[(4) - (6)].dval), (yyvsp[(5) - (6)].dval)); 
        }    
    }
    break;

  case 473:

/* Line 1806 of yacc.c  */
#line 2790 "def.y"
    { if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.setTaper(); }
    break;

  case 474:

/* Line 1806 of yacc.c  */
#line 2793 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 475:

/* Line 1806 of yacc.c  */
#line 2794 "def.y"
    { if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addTaperRule((yyvsp[(3) - (3)].string)); }
    break;

  case 476:

/* Line 1806 of yacc.c  */
#line 2799 "def.y"
    { 
        if (defData->VersionNum < 5.6) {
           if (defData->NeedPathData && (defData->callbacks->NetCbk ||
               defData->callbacks->SNetCbk)) {
             if (defData->netWarnings++ < defData->settings->NetWarnings) {
               defData->defMsg = (char*)malloc(1000);
               sprintf (defData->defMsg,
                  "The STYLE statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
               defData->defError(6534, defData->defMsg);
               free(defData->defMsg);
               CHKERR();
             }
           }
        } else
           if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
             (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
             defData->PathObj.addStyle((int)(yyvsp[(2) - (2)].dval));
      }
    break;

  case 479:

/* Line 1806 of yacc.c  */
#line 2824 "def.y"
    { if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
          (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
          defData->PathObj.addShape((yyvsp[(3) - (3)].string)); }
    break;

  case 480:

/* Line 1806 of yacc.c  */
#line 2828 "def.y"
    { if (defData->VersionNum < 5.6) {
          if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
            (defData->callbacks->SNetCbk && (defData->netOsnet==2)))) {
            if (defData->netWarnings++ < defData->settings->NetWarnings) {
              defData->defMsg = (char*)malloc(1000);
              sprintf (defData->defMsg,
                 "The STYLE statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
              defData->defError(6534, defData->defMsg);
              free(defData->defMsg);
              CHKERR();
            }
          }
        } else {
          if (defData->NeedPathData && ((defData->callbacks->NetCbk && (defData->netOsnet==1)) ||
            (defData->callbacks->SNetCbk && (defData->netOsnet==2))))
            defData->PathObj.addStyle((int)(yyvsp[(3) - (3)].dval));
        }
      }
    break;

  case 481:

/* Line 1806 of yacc.c  */
#line 2848 "def.y"
    { 
            CALLBACK(defData->callbacks->NetEndCbk, defrNetEndCbkType, 0);
            defData->netOsnet = 0;
          }
    break;

  case 482:

/* Line 1806 of yacc.c  */
#line 2854 "def.y"
    { (yyval.string) = (char*)"RING"; }
    break;

  case 483:

/* Line 1806 of yacc.c  */
#line 2856 "def.y"
    { (yyval.string) = (char*)"STRIPE"; }
    break;

  case 484:

/* Line 1806 of yacc.c  */
#line 2858 "def.y"
    { (yyval.string) = (char*)"FOLLOWPIN"; }
    break;

  case 485:

/* Line 1806 of yacc.c  */
#line 2860 "def.y"
    { (yyval.string) = (char*)"IOWIRE"; }
    break;

  case 486:

/* Line 1806 of yacc.c  */
#line 2862 "def.y"
    { (yyval.string) = (char*)"COREWIRE"; }
    break;

  case 487:

/* Line 1806 of yacc.c  */
#line 2864 "def.y"
    { (yyval.string) = (char*)"BLOCKWIRE"; }
    break;

  case 488:

/* Line 1806 of yacc.c  */
#line 2866 "def.y"
    { (yyval.string) = (char*)"FILLWIRE"; }
    break;

  case 489:

/* Line 1806 of yacc.c  */
#line 2868 "def.y"
    {
              if (defData->VersionNum < 5.7) {
                 if (defData->NeedPathData) {
                   if (defData->fillWarnings++ < defData->settings->FillWarnings) {
                     defData->defMsg = (char*)malloc(10000);
                     sprintf (defData->defMsg,
                       "The FILLWIREOPC is available in version 5.7 or later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                     defData->defError(6552, defData->defMsg);
                     free(defData->defMsg);
                     CHKERR();
                  }
                }
              }
              (yyval.string) = (char*)"FILLWIREOPC";
            }
    break;

  case 490:

/* Line 1806 of yacc.c  */
#line 2884 "def.y"
    { (yyval.string) = (char*)"DRCFILL"; }
    break;

  case 491:

/* Line 1806 of yacc.c  */
#line 2886 "def.y"
    { (yyval.string) = (char*)"BLOCKAGEWIRE"; }
    break;

  case 492:

/* Line 1806 of yacc.c  */
#line 2888 "def.y"
    { (yyval.string) = (char*)"PADRING"; }
    break;

  case 493:

/* Line 1806 of yacc.c  */
#line 2890 "def.y"
    { (yyval.string) = (char*)"BLOCKRING"; }
    break;

  case 497:

/* Line 1806 of yacc.c  */
#line 2900 "def.y"
    { CALLBACK(defData->callbacks->SNetCbk, defrSNetCbkType, &defData->Net); }
    break;

  case 504:

/* Line 1806 of yacc.c  */
#line 2911 "def.y"
    {
             if (defData->VersionNum >= 5.8) {
                defData->specialWire_routeStatus = (yyvsp[(2) - (2)].string);
             } else {
                 if (defData->callbacks->SNetCbk) {   // PCR 902306 
                   defData->defMsg = (char*)malloc(1024);
                   sprintf(defData->defMsg, "The SPECIAL NET statement, with type %s, does not have any net statement defined.\nThe DEF parser will ignore this statemnet.", (yyvsp[(2) - (2)].string));
                   defData->defWarning(7023, defData->defMsg);
                   free(defData->defMsg);
                 }
             }
            }
    break;

  case 505:

/* Line 1806 of yacc.c  */
#line 2924 "def.y"
    {
            if (defData->callbacks->SNetCbk) defData->Net.addWire((yyvsp[(2) - (2)].string), NULL);
            }
    break;

  case 506:

/* Line 1806 of yacc.c  */
#line 2928 "def.y"
    {
            // 7/17/2003 - Fix for pcr 604848, add a callback for each wire
            if (defData->callbacks->SNetWireCbk) {
               CALLBACK(defData->callbacks->SNetWireCbk, defrSNetWireCbkType, &defData->Net);
               defData->Net.freeWire();
            }
            defData->by_is_keyword = FALSE;
            defData->do_is_keyword = FALSE;
            defData->new_is_keyword = FALSE;
            defData->step_is_keyword = FALSE;
            defData->orient_is_keyword = FALSE;
            defData->virtual_is_keyword = FALSE;
            defData->mask_is_keyword = FALSE;
            defData->rect_is_keyword = FALSE;
            defData->needSNPCbk = 0;
            }
    break;

  case 507:

/* Line 1806 of yacc.c  */
#line 2945 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 508:

/* Line 1806 of yacc.c  */
#line 2946 "def.y"
    { defData->shieldName = (yyvsp[(4) - (4)].string); 
              defData->specialWire_routeStatus = (char*)"SHIELD";
              defData->specialWire_routeStatusName = (yyvsp[(4) - (4)].string); 
            }
    break;

  case 510:

/* Line 1806 of yacc.c  */
#line 2953 "def.y"
    {  
            defData->specialWire_shapeType = (yyvsp[(3) - (3)].string);
          }
    break;

  case 511:

/* Line 1806 of yacc.c  */
#line 2957 "def.y"
    {
            if (defData->validateMaskInput((int)(yyvsp[(3) - (3)].dval), defData->sNetWarnings, defData->settings->SNetWarnings)) {
                defData->specialWire_mask = (yyvsp[(3) - (3)].dval);
            }     
          }
    break;

  case 512:

/* Line 1806 of yacc.c  */
#line 2962 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 513:

/* Line 1806 of yacc.c  */
#line 2963 "def.y"
    {
            if (defData->VersionNum < 5.6) {
              if (defData->callbacks->SNetCbk) {
                if (defData->sNetWarnings++ < defData->settings->SNetWarnings) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The POLYGON statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
                  defData->defError(6535, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            }
            
            defData->Geometries.Reset();
          }
    break;

  case 514:

/* Line 1806 of yacc.c  */
#line 2980 "def.y"
    {
            if (defData->VersionNum >= 5.6) {  // only add if 5.6 or beyond
              if (defData->callbacks->SNetCbk) {
                // defData->needSNPCbk will indicate that it has reach the max
                // memory and if user has set partialPathCBk, def parser
                // will make the callback.
                // This will improve performance
                // This construct is only in specialnet
                defData->Net.addPolygon((yyvsp[(4) - (9)].string), &defData->Geometries, &defData->needSNPCbk, defData->specialWire_mask, defData->specialWire_routeStatus, defData->specialWire_shapeType,
                                                                defData->specialWire_routeStatusName);
                defData->specialWire_mask = 0;
                defData->specialWire_routeStatus = (char*)"ROUTED";
                defData->specialWire_shapeType = (char*)"";
                if (defData->needSNPCbk && defData->callbacks->SNetPartialPathCbk) {
                   CALLBACK(defData->callbacks->SNetPartialPathCbk, defrSNetPartialPathCbkType,
                            &defData->Net);
                   defData->Net.clearRectPolyNPath();
                   defData->Net.clearVia();
                }
              }
            }
          }
    break;

  case 515:

/* Line 1806 of yacc.c  */
#line 3003 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 516:

/* Line 1806 of yacc.c  */
#line 3004 "def.y"
    {
            if (defData->VersionNum < 5.6) {
              if (defData->callbacks->SNetCbk) {
                if (defData->sNetWarnings++ < defData->settings->SNetWarnings) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The RECT statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
                  defData->defError(6536, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
            }
            if (defData->callbacks->SNetCbk) {
              // defData->needSNPCbk will indicate that it has reach the max
              // memory and if user has set partialPathCBk, def parser
              // will make the callback.
              // This will improve performance
              // This construct is only in specialnet
              defData->Net.addRect((yyvsp[(4) - (6)].string), (yyvsp[(5) - (6)].pt).x, (yyvsp[(5) - (6)].pt).y, (yyvsp[(6) - (6)].pt).x, (yyvsp[(6) - (6)].pt).y, &defData->needSNPCbk, defData->specialWire_mask, defData->specialWire_routeStatus, defData->specialWire_shapeType, defData->specialWire_routeStatusName);
              defData->specialWire_mask = 0;
              defData->specialWire_routeStatus = (char*)"ROUTED";
              defData->specialWire_shapeType = (char*)"";
              defData->specialWire_routeStatusName = (char*)"";
              if (defData->needSNPCbk && defData->callbacks->SNetPartialPathCbk) {
                 CALLBACK(defData->callbacks->SNetPartialPathCbk, defrSNetPartialPathCbkType,
                          &defData->Net);
                 defData->Net.clearRectPolyNPath();
                 defData->Net.clearVia();
              }
            }
          }
    break;

  case 517:

/* Line 1806 of yacc.c  */
#line 3036 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 518:

/* Line 1806 of yacc.c  */
#line 3037 "def.y"
    {
          if (defData->VersionNum < 5.8) {
              if (defData->callbacks->SNetCbk) {
                if (defData->sNetWarnings++ < defData->settings->SNetWarnings) {
                  defData->defMsg = (char*)malloc(1000);
                  sprintf (defData->defMsg,
                     "The VIA statement is available in version 5.8 and later.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
                  defData->defError(6536, defData->defMsg);
                  free(defData->defMsg);
                  CHKERR();
                }
              }
          }
        }
    break;

  case 519:

/* Line 1806 of yacc.c  */
#line 3052 "def.y"
    {
          if (defData->VersionNum >= 5.8 && defData->callbacks->SNetCbk) {
              defData->Net.addPts((yyvsp[(4) - (8)].string), (yyvsp[(5) - (8)].integer), &defData->Geometries, &defData->needSNPCbk, defData->specialWire_mask, defData->specialWire_routeStatus, defData->specialWire_shapeType,
                                                          defData->specialWire_routeStatusName);
              defData->specialWire_mask = 0;
              defData->specialWire_routeStatus = (char*)"ROUTED";
              defData->specialWire_shapeType = (char*)"";
              defData->specialWire_routeStatusName = (char*)"";
              if (defData->needSNPCbk && defData->callbacks->SNetPartialPathCbk) {
                 CALLBACK(defData->callbacks->SNetPartialPathCbk, defrSNetPartialPathCbkType,
                          &defData->Net);
                 defData->Net.clearRectPolyNPath();
                 defData->Net.clearVia();
              }
            }
        }
    break;

  case 520:

/* Line 1806 of yacc.c  */
#line 3070 "def.y"
    { if (defData->callbacks->SNetCbk) defData->Net.setSource((yyvsp[(3) - (3)].string)); }
    break;

  case 521:

/* Line 1806 of yacc.c  */
#line 3073 "def.y"
    { if (defData->callbacks->SNetCbk) defData->Net.setFixedbump(); }
    break;

  case 522:

/* Line 1806 of yacc.c  */
#line 3076 "def.y"
    { if (defData->callbacks->SNetCbk) defData->Net.setFrequency((yyvsp[(3) - (3)].dval)); }
    break;

  case 523:

/* Line 1806 of yacc.c  */
#line 3078 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1;}
    break;

  case 524:

/* Line 1806 of yacc.c  */
#line 3079 "def.y"
    { if (defData->callbacks->SNetCbk) defData->Net.setOriginal((yyvsp[(4) - (4)].string)); }
    break;

  case 525:

/* Line 1806 of yacc.c  */
#line 3082 "def.y"
    { if (defData->callbacks->SNetCbk) defData->Net.setPattern((yyvsp[(3) - (3)].string)); }
    break;

  case 526:

/* Line 1806 of yacc.c  */
#line 3085 "def.y"
    { if (defData->callbacks->SNetCbk) defData->Net.setWeight(ROUND((yyvsp[(3) - (3)].dval))); }
    break;

  case 527:

/* Line 1806 of yacc.c  */
#line 3088 "def.y"
    { 
              // 11/12/2002 - this is obsolete in 5.5, & will be ignored 
              if (defData->VersionNum < 5.5)
                 if (defData->callbacks->SNetCbk) defData->Net.setCap((yyvsp[(3) - (3)].dval));
              else
                 defData->defWarning(7024, "The ESTCAP statement is obsolete in version 5.5 and later.\nThe DEF parser will ignore this statement.");
            }
    break;

  case 528:

/* Line 1806 of yacc.c  */
#line 3097 "def.y"
    { if (defData->callbacks->SNetCbk) defData->Net.setUse((yyvsp[(3) - (3)].string)); }
    break;

  case 529:

/* Line 1806 of yacc.c  */
#line 3100 "def.y"
    { if (defData->callbacks->SNetCbk) defData->Net.setStyle((int)(yyvsp[(3) - (3)].dval)); }
    break;

  case 530:

/* Line 1806 of yacc.c  */
#line 3102 "def.y"
    {defData->dumb_mode = DEF_MAX_INT; }
    break;

  case 531:

/* Line 1806 of yacc.c  */
#line 3104 "def.y"
    { defData->dumb_mode = 0; }
    break;

  case 532:

/* Line 1806 of yacc.c  */
#line 3107 "def.y"
    { CALLBACK(defData->callbacks->NetExtCbk, defrNetExtCbkType, &defData->History_text[0]); }
    break;

  case 533:

/* Line 1806 of yacc.c  */
#line 3110 "def.y"
    { (yyval.integer) = 0; }
    break;

  case 534:

/* Line 1806 of yacc.c  */
#line 3111 "def.y"
    {(yyval.integer) = 0;}
    break;

  case 535:

/* Line 1806 of yacc.c  */
#line 3112 "def.y"
    {(yyval.integer) = 1;}
    break;

  case 536:

/* Line 1806 of yacc.c  */
#line 3113 "def.y"
    {(yyval.integer) = 2;}
    break;

  case 537:

/* Line 1806 of yacc.c  */
#line 3114 "def.y"
    {(yyval.integer) = 3;}
    break;

  case 538:

/* Line 1806 of yacc.c  */
#line 3115 "def.y"
    {(yyval.integer) = 4;}
    break;

  case 539:

/* Line 1806 of yacc.c  */
#line 3116 "def.y"
    {(yyval.integer) = 5;}
    break;

  case 540:

/* Line 1806 of yacc.c  */
#line 3117 "def.y"
    {(yyval.integer) = 6;}
    break;

  case 541:

/* Line 1806 of yacc.c  */
#line 3118 "def.y"
    {(yyval.integer) = 7;}
    break;

  case 542:

/* Line 1806 of yacc.c  */
#line 3121 "def.y"
    {
                if (defData->callbacks->SNetCbk) {
                    if (defData->VersionNum < 5.8) { 
                        defData->defMsg = (char*)malloc(1024);
                        sprintf(defData->defMsg, "The SPECIAL NET SHIELD statement doesn't have routing points definition.\nWill be ignored.");
                        defData->defWarning(7025, defData->defMsg);
                        free(defData->defMsg);
                    } else {  // CCR 1244433
                      defData->specialWire_routeStatus = (char*)"SHIELD";
                      defData->specialWire_routeStatusName = defData->shieldName;
                    }
                }
            }
    break;

  case 543:

/* Line 1806 of yacc.c  */
#line 3135 "def.y"
    { // since the parser still supports 5.3 and earlier, 
              // can't just move SHIELD in net_type 
              if (defData->VersionNum < 5.4) { // PCR 445209 
                if (defData->callbacks->SNetCbk) defData->Net.addShield(defData->shieldName);
                defData->by_is_keyword = FALSE;
                defData->do_is_keyword = FALSE;
                defData->new_is_keyword = FALSE;
                defData->step_is_keyword = FALSE;
                defData->orient_is_keyword = FALSE;
                defData->virtual_is_keyword = FALSE;
                defData->mask_is_keyword = FALSE;
                defData->rect_is_keyword = FALSE;
                defData->specialWire_routeStatus = (char*)"ROUTED";
                defData->specialWire_routeStatusName = (char*)"";
                defData->shield = TRUE;   // save the path info in the defData->shield paths 
              } else
                if (defData->callbacks->SNetCbk) defData->Net.addWire("SHIELD", defData->shieldName);
                defData->specialWire_routeStatus = (char*)"ROUTED";
                defData->specialWire_routeStatusName = (char*)"";
            }
    break;

  case 544:

/* Line 1806 of yacc.c  */
#line 3156 "def.y"
    {
              // 7/17/2003 - Fix for pcr 604848, add a callback for each wire
              if (defData->callbacks->SNetWireCbk) {
                 CALLBACK(defData->callbacks->SNetWireCbk, defrSNetWireCbkType, &defData->Net);
                 if (defData->VersionNum < 5.4)
                   defData->Net.freeShield();
                 else
                   defData->Net.freeWire();
              }
              if (defData->VersionNum < 5.4) {  // PCR 445209 
                defData->shield = FALSE;
                defData->by_is_keyword = FALSE;
                defData->do_is_keyword = FALSE;
                defData->new_is_keyword = FALSE;
                defData->step_is_keyword = FALSE;
                defData->nondef_is_keyword = FALSE;
                defData->mustjoin_is_keyword = FALSE;
                defData->orient_is_keyword = FALSE;
                defData->virtual_is_keyword = FALSE;
                defData->mask_is_keyword = FALSE;
                defData->rect_is_keyword = FALSE;
              } else {
                defData->by_is_keyword = FALSE;
                defData->do_is_keyword = FALSE;
                defData->new_is_keyword = FALSE;
                defData->step_is_keyword = FALSE;
                defData->orient_is_keyword = FALSE;
                defData->virtual_is_keyword = FALSE;
                defData->mask_is_keyword = FALSE;
                defData->rect_is_keyword = FALSE;
              }
              defData->needSNPCbk = 0;
            }
    break;

  case 545:

/* Line 1806 of yacc.c  */
#line 3190 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 546:

/* Line 1806 of yacc.c  */
#line 3191 "def.y"
    {
              // 11/12/2002 - this is obsolete in 5.5, & will be ignored 
              if (defData->VersionNum < 5.5)
                 if (defData->callbacks->SNetCbk) defData->Net.setWidth((yyvsp[(4) - (5)].string), (yyvsp[(5) - (5)].dval));
              else
                 defData->defWarning(7026, "The WIDTH statement is obsolete in version 5.5 and later.\nThe DEF parser will ignore this statement.");
            }
    break;

  case 547:

/* Line 1806 of yacc.c  */
#line 3199 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 548:

/* Line 1806 of yacc.c  */
#line 3200 "def.y"
    {
              if (defrData::numIsInt((yyvsp[(4) - (4)].string))) {
                 if (defData->callbacks->SNetCbk) defData->Net.setVoltage(atoi((yyvsp[(4) - (4)].string)));
              } else {
                 if (defData->callbacks->SNetCbk) {
                   if (defData->sNetWarnings++ < defData->settings->SNetWarnings) {
                     defData->defMsg = (char*)malloc(1000);
                     sprintf (defData->defMsg,
                        "The value %s for statement VOLTAGE is invalid. The value can only be integer.\nSpecify a valid value in units of millivolts", (yyvsp[(4) - (4)].string));
                     defData->defError(6537, defData->defMsg);
                     free(defData->defMsg);
                     CHKERR();
                   }
                 }
              }
            }
    break;

  case 549:

/* Line 1806 of yacc.c  */
#line 3217 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 550:

/* Line 1806 of yacc.c  */
#line 3218 "def.y"
    {
              if (defData->callbacks->SNetCbk) defData->Net.setSpacing((yyvsp[(4) - (5)].string),(yyvsp[(5) - (5)].dval));
            }
    break;

  case 551:

/* Line 1806 of yacc.c  */
#line 3222 "def.y"
    {
            }
    break;

  case 554:

/* Line 1806 of yacc.c  */
#line 3230 "def.y"
    {
              if (defData->callbacks->SNetCbk) {
                char propTp;
                char* str = defData->ringCopy("                       ");
                propTp = defData->session->SNetProp.propType((yyvsp[(1) - (2)].string));
                CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "SPECIAL NET");
                // For backword compatibility, also set the string value 
                sprintf(str, "%g", (yyvsp[(2) - (2)].dval));
                defData->Net.addNumProp((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].dval), str, propTp);
              }
            }
    break;

  case 555:

/* Line 1806 of yacc.c  */
#line 3242 "def.y"
    {
              if (defData->callbacks->SNetCbk) {
                char propTp;
                propTp = defData->session->SNetProp.propType((yyvsp[(1) - (2)].string));
                CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "SPECIAL NET");
                defData->Net.addProp((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
              }
            }
    break;

  case 556:

/* Line 1806 of yacc.c  */
#line 3251 "def.y"
    {
              if (defData->callbacks->SNetCbk) {
                char propTp;
                propTp = defData->session->SNetProp.propType((yyvsp[(1) - (2)].string));
                CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "SPECIAL NET");
                defData->Net.addProp((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
              }
            }
    break;

  case 558:

/* Line 1806 of yacc.c  */
#line 3262 "def.y"
    {
              if (defData->callbacks->SNetCbk) defData->Net.setRange((yyvsp[(2) - (3)].dval),(yyvsp[(3) - (3)].dval));
            }
    break;

  case 560:

/* Line 1806 of yacc.c  */
#line 3268 "def.y"
    { defData->Prop.setRange((yyvsp[(2) - (3)].dval), (yyvsp[(3) - (3)].dval)); }
    break;

  case 561:

/* Line 1806 of yacc.c  */
#line 3271 "def.y"
    { (yyval.string) = (char*)"BALANCED"; }
    break;

  case 562:

/* Line 1806 of yacc.c  */
#line 3273 "def.y"
    { (yyval.string) = (char*)"STEINER"; }
    break;

  case 563:

/* Line 1806 of yacc.c  */
#line 3275 "def.y"
    { (yyval.string) = (char*)"TRUNK"; }
    break;

  case 564:

/* Line 1806 of yacc.c  */
#line 3277 "def.y"
    { (yyval.string) = (char*)"WIREDLOGIC"; }
    break;

  case 565:

/* Line 1806 of yacc.c  */
#line 3281 "def.y"
    { 
        if (defData->NeedPathData && defData->callbacks->SNetCbk) {
           if (defData->needSNPCbk && defData->callbacks->SNetPartialPathCbk) { 
              // require a callback before proceed because defData->needSNPCbk must be
              // set to 1 from the previous pathIsDone and user has registered
              // a callback routine.
              CALLBACK(defData->callbacks->SNetPartialPathCbk, defrSNetPartialPathCbkType,
                       &defData->Net);
              defData->needSNPCbk = 0;   // reset the flag
              defData->pathIsDone(defData->shield, 1, defData->netOsnet, &defData->needSNPCbk);
              defData->Net.clearRectPolyNPath();
              defData->Net.clearVia();
           } else
              defData->pathIsDone(defData->shield, 0, defData->netOsnet, &defData->needSNPCbk);
        }
      }
    break;

  case 566:

/* Line 1806 of yacc.c  */
#line 3298 "def.y"
    { }
    break;

  case 567:

/* Line 1806 of yacc.c  */
#line 3300 "def.y"
    { defData->dumb_mode = 1; }
    break;

  case 568:

/* Line 1806 of yacc.c  */
#line 3301 "def.y"
    { if (defData->NeedPathData && defData->callbacks->SNetCbk) {
           if (defData->needSNPCbk && defData->callbacks->SNetPartialPathCbk) {
              // require a callback before proceed because defData->needSNPCbk must be
              // set to 1 from the previous pathIsDone and user has registered
              // a callback routine.
              CALLBACK(defData->callbacks->SNetPartialPathCbk, defrSNetPartialPathCbkType,
                       &defData->Net);
              defData->needSNPCbk = 0;   // reset the flag
              defData->pathIsDone(defData->shield, 1, defData->netOsnet, &defData->needSNPCbk);
              // reset any poly or rect in special wiring statement
              defData->Net.clearRectPolyNPath();
              defData->Net.clearVia();
           } else
              defData->pathIsDone(defData->shield, 0, defData->netOsnet, &defData->needSNPCbk);
        }
      }
    break;

  case 569:

/* Line 1806 of yacc.c  */
#line 3319 "def.y"
    { if (defData->NeedPathData && defData->callbacks->SNetCbk)
           defData->PathObj.addLayer((yyvsp[(1) - (1)].string));
        defData->dumb_mode = 0; defData->no_num = 0;
      }
    break;

  case 570:

/* Line 1806 of yacc.c  */
#line 3327 "def.y"
    { defData->dumb_mode = DEF_MAX_INT; defData->by_is_keyword = TRUE; defData->do_is_keyword = TRUE;
        defData->new_is_keyword = TRUE; defData->step_is_keyword = TRUE;
         defData->orient_is_keyword = TRUE; defData->rect_is_keyword = TRUE, defData->mask_is_keyword = TRUE; 
         defData->virtual_is_keyword = TRUE;  }
    break;

  case 571:

/* Line 1806 of yacc.c  */
#line 3333 "def.y"
    { defData->dumb_mode = 0; defData->rect_is_keyword = FALSE, defData->mask_is_keyword = FALSE, defData->virtual_is_keyword = FALSE; }
    break;

  case 572:

/* Line 1806 of yacc.c  */
#line 3336 "def.y"
    { if (defData->NeedPathData && defData->callbacks->SNetCbk)
          defData->PathObj.addWidth(ROUND((yyvsp[(1) - (1)].dval)));
      }
    break;

  case 573:

/* Line 1806 of yacc.c  */
#line 3341 "def.y"
    { 
        if (defData->callbacks->SNetStartCbk)
          CALLBACK(defData->callbacks->SNetStartCbk, defrSNetStartCbkType, ROUND((yyvsp[(2) - (3)].dval)));
        defData->netOsnet = 2;
      }
    break;

  case 574:

/* Line 1806 of yacc.c  */
#line 3348 "def.y"
    { 
        if (defData->callbacks->SNetEndCbk)
          CALLBACK(defData->callbacks->SNetEndCbk, defrSNetEndCbkType, 0);
        defData->netOsnet = 0;
      }
    break;

  case 576:

/* Line 1806 of yacc.c  */
#line 3358 "def.y"
    {
        if (defData->callbacks->GroupsStartCbk)
           CALLBACK(defData->callbacks->GroupsStartCbk, defrGroupsStartCbkType, ROUND((yyvsp[(2) - (3)].dval)));
      }
    break;

  case 579:

/* Line 1806 of yacc.c  */
#line 3368 "def.y"
    {
        if (defData->callbacks->GroupCbk)
           CALLBACK(defData->callbacks->GroupCbk, defrGroupCbkType, &defData->Group);
      }
    break;

  case 580:

/* Line 1806 of yacc.c  */
#line 3373 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 581:

/* Line 1806 of yacc.c  */
#line 3374 "def.y"
    {
        defData->dumb_mode = DEF_MAX_INT;
        defData->no_num = DEF_MAX_INT;
        /* dumb_mode is automatically turned off at the first
         * + in the options or at the ; at the end of the group */
        if (defData->callbacks->GroupCbk) defData->Group.setup((yyvsp[(3) - (3)].string));
        if (defData->callbacks->GroupNameCbk)
           CALLBACK(defData->callbacks->GroupNameCbk, defrGroupNameCbkType, (yyvsp[(3) - (3)].string));
      }
    break;

  case 583:

/* Line 1806 of yacc.c  */
#line 3386 "def.y"
    {  }
    break;

  case 584:

/* Line 1806 of yacc.c  */
#line 3389 "def.y"
    {
        // if (defData->callbacks->GroupCbk) defData->Group.addMember($1); 
        if (defData->callbacks->GroupMemberCbk)
          CALLBACK(defData->callbacks->GroupMemberCbk, defrGroupMemberCbkType, (yyvsp[(1) - (1)].string));
      }
    break;

  case 587:

/* Line 1806 of yacc.c  */
#line 3400 "def.y"
    { }
    break;

  case 588:

/* Line 1806 of yacc.c  */
#line 3401 "def.y"
    { defData->dumb_mode = DEF_MAX_INT; }
    break;

  case 589:

/* Line 1806 of yacc.c  */
#line 3403 "def.y"
    { defData->dumb_mode = 0; }
    break;

  case 590:

/* Line 1806 of yacc.c  */
#line 3404 "def.y"
    { defData->dumb_mode = 1;  defData->no_num = 1; }
    break;

  case 591:

/* Line 1806 of yacc.c  */
#line 3405 "def.y"
    { }
    break;

  case 592:

/* Line 1806 of yacc.c  */
#line 3407 "def.y"
    { 
        if (defData->callbacks->GroupMemberCbk)
          CALLBACK(defData->callbacks->GroupExtCbk, defrGroupExtCbkType, &defData->History_text[0]);
      }
    break;

  case 593:

/* Line 1806 of yacc.c  */
#line 3413 "def.y"
    {
        // 11/12/2002 - this is obsolete in 5.5, & will be ignored 
        if (defData->VersionNum < 5.5) {
          if (defData->callbacks->GroupCbk)
            defData->Group.addRegionRect((yyvsp[(1) - (2)].pt).x, (yyvsp[(1) - (2)].pt).y, (yyvsp[(2) - (2)].pt).x, (yyvsp[(2) - (2)].pt).y);
        }
        else
          defData->defWarning(7027, "The GROUP REGION pt pt statement is obsolete in version 5.5 and later.\nThe DEF parser will ignore this statement.");
      }
    break;

  case 594:

/* Line 1806 of yacc.c  */
#line 3423 "def.y"
    { if (defData->callbacks->GroupCbk)
          defData->Group.setRegionName((yyvsp[(1) - (1)].string));
      }
    break;

  case 597:

/* Line 1806 of yacc.c  */
#line 3432 "def.y"
    {
        if (defData->callbacks->GroupCbk) {
          char propTp;
          char* str = defData->ringCopy("                       ");
          propTp = defData->session->GroupProp.propType((yyvsp[(1) - (2)].string));
          CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "GROUP");
          sprintf(str, "%g", (yyvsp[(2) - (2)].dval));
          defData->Group.addNumProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].dval), str, propTp);
        }
      }
    break;

  case 598:

/* Line 1806 of yacc.c  */
#line 3443 "def.y"
    {
        if (defData->callbacks->GroupCbk) {
          char propTp;
          propTp = defData->session->GroupProp.propType((yyvsp[(1) - (2)].string));
          CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "GROUP");
          defData->Group.addProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
        }
      }
    break;

  case 599:

/* Line 1806 of yacc.c  */
#line 3452 "def.y"
    {
        if (defData->callbacks->GroupCbk) {
          char propTp;
          propTp = defData->session->GroupProp.propType((yyvsp[(1) - (2)].string));
          CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "GROUP");
          defData->Group.addProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
        }
      }
    break;

  case 601:

/* Line 1806 of yacc.c  */
#line 3463 "def.y"
    { }
    break;

  case 602:

/* Line 1806 of yacc.c  */
#line 3466 "def.y"
    {
        // 11/12/2002 - this is obsolete in 5.5, & will be ignored 
        if (defData->VersionNum < 5.5)
          if (defData->callbacks->GroupCbk) defData->Group.setMaxX(ROUND((yyvsp[(2) - (2)].dval)));
        else
          defData->defWarning(7028, "The GROUP SOFT MAXX statement is obsolete in version 5.5 and later.\nThe DEF parser will ignore this statement.");
      }
    break;

  case 603:

/* Line 1806 of yacc.c  */
#line 3474 "def.y"
    { 
        // 11/12/2002 - this is obsolete in 5.5, & will be ignored 
        if (defData->VersionNum < 5.5)
          if (defData->callbacks->GroupCbk) defData->Group.setMaxY(ROUND((yyvsp[(2) - (2)].dval)));
        else
          defData->defWarning(7029, "The GROUP SOFT MAXY statement is obsolete in version 5.5 and later.\nThe DEF parser will ignore this statement.");
      }
    break;

  case 604:

/* Line 1806 of yacc.c  */
#line 3482 "def.y"
    { 
        // 11/12/2002 - this is obsolete in 5.5, & will be ignored 
        if (defData->VersionNum < 5.5)
          if (defData->callbacks->GroupCbk) defData->Group.setPerim(ROUND((yyvsp[(2) - (2)].dval)));
        else
          defData->defWarning(7030, "The GROUP SOFT MAXHALFPERIMETER statement is obsolete in version 5.5 and later.\nThe DEF parser will ignore this statement.");
      }
    break;

  case 605:

/* Line 1806 of yacc.c  */
#line 3491 "def.y"
    { 
        if (defData->callbacks->GroupsEndCbk)
          CALLBACK(defData->callbacks->GroupsEndCbk, defrGroupsEndCbkType, 0);
      }
    break;

  case 608:

/* Line 1806 of yacc.c  */
#line 3505 "def.y"
    {
        if ((defData->VersionNum < 5.4) && (defData->callbacks->AssertionsStartCbk)) {
          CALLBACK(defData->callbacks->AssertionsStartCbk, defrAssertionsStartCbkType,
                   ROUND((yyvsp[(2) - (3)].dval)));
        } else {
          if (defData->callbacks->AssertionCbk)
            if (defData->assertionWarnings++ < defData->settings->AssertionWarnings)
              defData->defWarning(7031, "The ASSERTIONS statement is obsolete in version 5.4 and later.\nThe DEF parser will ignore this statement.");
        }
        if (defData->callbacks->AssertionCbk)
          defData->Assertion.setAssertionMode();
      }
    break;

  case 609:

/* Line 1806 of yacc.c  */
#line 3519 "def.y"
    {
        if ((defData->VersionNum < 5.4) && (defData->callbacks->ConstraintsStartCbk)) {
          CALLBACK(defData->callbacks->ConstraintsStartCbk, defrConstraintsStartCbkType,
                   ROUND((yyvsp[(2) - (3)].dval)));
        } else {
          if (defData->callbacks->ConstraintCbk)
            if (defData->constraintWarnings++ < defData->settings->ConstraintWarnings)
              defData->defWarning(7032, "The CONSTRAINTS statement is obsolete in version 5.4 and later.\nThe DEF parser will ignore this statement.");
        }
        if (defData->callbacks->ConstraintCbk)
          defData->Assertion.setConstraintMode();
      }
    break;

  case 613:

/* Line 1806 of yacc.c  */
#line 3538 "def.y"
    {
        if ((defData->VersionNum < 5.4) && (defData->callbacks->ConstraintCbk || defData->callbacks->AssertionCbk)) {
          if (defData->Assertion.isConstraint()) 
            CALLBACK(defData->callbacks->ConstraintCbk, defrConstraintCbkType, &defData->Assertion);
          if (defData->Assertion.isAssertion()) 
            CALLBACK(defData->callbacks->AssertionCbk, defrAssertionCbkType, &defData->Assertion);
        }
      }
    break;

  case 614:

/* Line 1806 of yacc.c  */
#line 3548 "def.y"
    { 
        if ((defData->VersionNum < 5.4) && (defData->callbacks->ConstraintCbk || defData->callbacks->AssertionCbk)) {
          if (defData->Assertion.isConstraint()) 
            CALLBACK(defData->callbacks->ConstraintCbk, defrConstraintCbkType, &defData->Assertion);
          if (defData->Assertion.isAssertion()) 
            CALLBACK(defData->callbacks->AssertionCbk, defrAssertionCbkType, &defData->Assertion);
        }
   
        // reset all the flags and everything
        defData->Assertion.clear();
      }
    break;

  case 615:

/* Line 1806 of yacc.c  */
#line 3560 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 616:

/* Line 1806 of yacc.c  */
#line 3561 "def.y"
    {
         if (defData->callbacks->ConstraintCbk || defData->callbacks->AssertionCbk)
           defData->Assertion.addNet((yyvsp[(3) - (3)].string));
      }
    break;

  case 617:

/* Line 1806 of yacc.c  */
#line 3565 "def.y"
    {defData->dumb_mode = 4; defData->no_num = 4;}
    break;

  case 618:

/* Line 1806 of yacc.c  */
#line 3566 "def.y"
    {
         if (defData->callbacks->ConstraintCbk || defData->callbacks->AssertionCbk)
           defData->Assertion.addPath((yyvsp[(3) - (6)].string), (yyvsp[(4) - (6)].string), (yyvsp[(5) - (6)].string), (yyvsp[(6) - (6)].string));
      }
    break;

  case 619:

/* Line 1806 of yacc.c  */
#line 3571 "def.y"
    {
        if (defData->callbacks->ConstraintCbk || defData->callbacks->AssertionCbk)
           defData->Assertion.setSum();
      }
    break;

  case 620:

/* Line 1806 of yacc.c  */
#line 3576 "def.y"
    {
        if (defData->callbacks->ConstraintCbk || defData->callbacks->AssertionCbk)
           defData->Assertion.setDiff();
      }
    break;

  case 622:

/* Line 1806 of yacc.c  */
#line 3583 "def.y"
    { }
    break;

  case 624:

/* Line 1806 of yacc.c  */
#line 3586 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 625:

/* Line 1806 of yacc.c  */
#line 3588 "def.y"
    {
        if (defData->callbacks->ConstraintCbk || defData->callbacks->AssertionCbk)
          defData->Assertion.setWiredlogic((yyvsp[(4) - (8)].string), (yyvsp[(7) - (8)].dval));
      }
    break;

  case 626:

/* Line 1806 of yacc.c  */
#line 3595 "def.y"
    { (yyval.string) = (char*)""; }
    break;

  case 627:

/* Line 1806 of yacc.c  */
#line 3597 "def.y"
    { (yyval.string) = (char*)"+"; }
    break;

  case 630:

/* Line 1806 of yacc.c  */
#line 3604 "def.y"
    {
        if (defData->callbacks->ConstraintCbk || defData->callbacks->AssertionCbk)
          defData->Assertion.setRiseMin((yyvsp[(3) - (3)].dval));
      }
    break;

  case 631:

/* Line 1806 of yacc.c  */
#line 3609 "def.y"
    {
        if (defData->callbacks->ConstraintCbk || defData->callbacks->AssertionCbk)
          defData->Assertion.setRiseMax((yyvsp[(3) - (3)].dval));
      }
    break;

  case 632:

/* Line 1806 of yacc.c  */
#line 3614 "def.y"
    {
        if (defData->callbacks->ConstraintCbk || defData->callbacks->AssertionCbk)
          defData->Assertion.setFallMin((yyvsp[(3) - (3)].dval));
      }
    break;

  case 633:

/* Line 1806 of yacc.c  */
#line 3619 "def.y"
    {
        if (defData->callbacks->ConstraintCbk || defData->callbacks->AssertionCbk)
          defData->Assertion.setFallMax((yyvsp[(3) - (3)].dval));
      }
    break;

  case 634:

/* Line 1806 of yacc.c  */
#line 3625 "def.y"
    { if ((defData->VersionNum < 5.4) && defData->callbacks->ConstraintsEndCbk) {
          CALLBACK(defData->callbacks->ConstraintsEndCbk, defrConstraintsEndCbkType, 0);
        } else {
          if (defData->callbacks->ConstraintsEndCbk) {
            if (defData->constraintWarnings++ < defData->settings->ConstraintWarnings)
              defData->defWarning(7032, "The CONSTRAINTS statement is obsolete in version 5.4 and later.\nThe DEF parser will ignore this statement.");
          }
        }
      }
    break;

  case 635:

/* Line 1806 of yacc.c  */
#line 3636 "def.y"
    { if ((defData->VersionNum < 5.4) && defData->callbacks->AssertionsEndCbk) {
          CALLBACK(defData->callbacks->AssertionsEndCbk, defrAssertionsEndCbkType, 0);
        } else {
          if (defData->callbacks->AssertionsEndCbk) {
            if (defData->assertionWarnings++ < defData->settings->AssertionWarnings)
              defData->defWarning(7031, "The ASSERTIONS statement is obsolete in version 5.4 and later.\nThe DEF parser will ignore this statement.");
          }
        }
      }
    break;

  case 637:

/* Line 1806 of yacc.c  */
#line 3650 "def.y"
    { if (defData->callbacks->ScanchainsStartCbk)
          CALLBACK(defData->callbacks->ScanchainsStartCbk, defrScanchainsStartCbkType,
                   ROUND((yyvsp[(2) - (3)].dval)));
      }
    break;

  case 639:

/* Line 1806 of yacc.c  */
#line 3657 "def.y"
    {}
    break;

  case 640:

/* Line 1806 of yacc.c  */
#line 3660 "def.y"
    { 
        if (defData->callbacks->ScanchainCbk)
          CALLBACK(defData->callbacks->ScanchainCbk, defrScanchainCbkType, &defData->Scanchain);
      }
    break;

  case 641:

/* Line 1806 of yacc.c  */
#line 3665 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1;}
    break;

  case 642:

/* Line 1806 of yacc.c  */
#line 3666 "def.y"
    {
        if (defData->callbacks->ScanchainCbk)
          defData->Scanchain.setName((yyvsp[(3) - (3)].string));
        defData->bit_is_keyword = TRUE;
      }
    break;

  case 645:

/* Line 1806 of yacc.c  */
#line 3678 "def.y"
    { (yyval.string) = (char*)""; }
    break;

  case 646:

/* Line 1806 of yacc.c  */
#line 3680 "def.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 647:

/* Line 1806 of yacc.c  */
#line 3682 "def.y"
    {defData->dumb_mode = 2; defData->no_num = 2;}
    break;

  case 648:

/* Line 1806 of yacc.c  */
#line 3683 "def.y"
    { if (defData->callbacks->ScanchainCbk)
          defData->Scanchain.setStart((yyvsp[(4) - (5)].string), (yyvsp[(5) - (5)].string));
      }
    break;

  case 649:

/* Line 1806 of yacc.c  */
#line 3686 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 650:

/* Line 1806 of yacc.c  */
#line 3687 "def.y"
    { defData->dumb_mode = 0; defData->no_num = 0; }
    break;

  case 651:

/* Line 1806 of yacc.c  */
#line 3689 "def.y"
    {
         defData->dumb_mode = 1;
         defData->no_num = 1;
         if (defData->callbacks->ScanchainCbk)
           defData->Scanchain.addOrderedList();
      }
    break;

  case 652:

/* Line 1806 of yacc.c  */
#line 3696 "def.y"
    { defData->dumb_mode = 0; defData->no_num = 0; }
    break;

  case 653:

/* Line 1806 of yacc.c  */
#line 3697 "def.y"
    {defData->dumb_mode = 2; defData->no_num = 2; }
    break;

  case 654:

/* Line 1806 of yacc.c  */
#line 3698 "def.y"
    { if (defData->callbacks->ScanchainCbk)
          defData->Scanchain.setStop((yyvsp[(4) - (5)].string), (yyvsp[(5) - (5)].string));
      }
    break;

  case 655:

/* Line 1806 of yacc.c  */
#line 3701 "def.y"
    { defData->dumb_mode = 10; defData->no_num = 10; }
    break;

  case 656:

/* Line 1806 of yacc.c  */
#line 3702 "def.y"
    { defData->dumb_mode = 0;  defData->no_num = 0; }
    break;

  case 657:

/* Line 1806 of yacc.c  */
#line 3703 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 658:

/* Line 1806 of yacc.c  */
#line 3705 "def.y"
    {
        if (defData->VersionNum < 5.5) {
          if (defData->callbacks->ScanchainCbk) {
            if (defData->scanchainWarnings++ < defData->settings->ScanchainWarnings) {
              defData->defMsg = (char*)malloc(1000);
              sprintf (defData->defMsg,
                 "The PARTITION statement is available in version 5.5 and later.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
              defData->defError(6538, defData->defMsg);
              free(defData->defMsg);
              CHKERR();
            }
          }
        }
        if (defData->callbacks->ScanchainCbk)
          defData->Scanchain.setPartition((yyvsp[(4) - (5)].string), (yyvsp[(5) - (5)].integer));
      }
    break;

  case 659:

/* Line 1806 of yacc.c  */
#line 3722 "def.y"
    {
        if (defData->callbacks->ScanChainExtCbk)
          CALLBACK(defData->callbacks->ScanChainExtCbk, defrScanChainExtCbkType, &defData->History_text[0]);
      }
    break;

  case 660:

/* Line 1806 of yacc.c  */
#line 3728 "def.y"
    { }
    break;

  case 661:

/* Line 1806 of yacc.c  */
#line 3730 "def.y"
    {
        if (defData->callbacks->ScanchainCbk) {
          if (strcmp((yyvsp[(2) - (4)].string), "IN") == 0 || strcmp((yyvsp[(2) - (4)].string), "in") == 0)
            defData->Scanchain.setCommonIn((yyvsp[(3) - (4)].string));
          else if (strcmp((yyvsp[(2) - (4)].string), "OUT") == 0 || strcmp((yyvsp[(2) - (4)].string), "out") == 0)
            defData->Scanchain.setCommonOut((yyvsp[(3) - (4)].string));
        }
      }
    break;

  case 662:

/* Line 1806 of yacc.c  */
#line 3739 "def.y"
    {
        if (defData->callbacks->ScanchainCbk) {
          if (strcmp((yyvsp[(2) - (8)].string), "IN") == 0 || strcmp((yyvsp[(2) - (8)].string), "in") == 0)
            defData->Scanchain.setCommonIn((yyvsp[(3) - (8)].string));
          else if (strcmp((yyvsp[(2) - (8)].string), "OUT") == 0 || strcmp((yyvsp[(2) - (8)].string), "out") == 0)
            defData->Scanchain.setCommonOut((yyvsp[(3) - (8)].string));
          if (strcmp((yyvsp[(6) - (8)].string), "IN") == 0 || strcmp((yyvsp[(6) - (8)].string), "in") == 0)
            defData->Scanchain.setCommonIn((yyvsp[(7) - (8)].string));
          else if (strcmp((yyvsp[(6) - (8)].string), "OUT") == 0 || strcmp((yyvsp[(6) - (8)].string), "out") == 0)
            defData->Scanchain.setCommonOut((yyvsp[(7) - (8)].string));
        }
      }
    break;

  case 665:

/* Line 1806 of yacc.c  */
#line 3757 "def.y"
    {
        defData->dumb_mode = 1000;
        defData->no_num = 1000;
        if (defData->callbacks->ScanchainCbk)
          defData->Scanchain.addFloatingInst((yyvsp[(1) - (1)].string));
      }
    break;

  case 666:

/* Line 1806 of yacc.c  */
#line 3764 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 667:

/* Line 1806 of yacc.c  */
#line 3767 "def.y"
    { }
    break;

  case 668:

/* Line 1806 of yacc.c  */
#line 3769 "def.y"
    {
        if (defData->callbacks->ScanchainCbk) {
          if (strcmp((yyvsp[(2) - (4)].string), "IN") == 0 || strcmp((yyvsp[(2) - (4)].string), "in") == 0)
            defData->Scanchain.addFloatingIn((yyvsp[(3) - (4)].string));
          else if (strcmp((yyvsp[(2) - (4)].string), "OUT") == 0 || strcmp((yyvsp[(2) - (4)].string), "out") == 0)
            defData->Scanchain.addFloatingOut((yyvsp[(3) - (4)].string));
          else if (strcmp((yyvsp[(2) - (4)].string), "BITS") == 0 || strcmp((yyvsp[(2) - (4)].string), "bits") == 0) {
            defData->bitsNum = atoi((yyvsp[(3) - (4)].string));
            defData->Scanchain.setFloatingBits(defData->bitsNum);
          }
        }
      }
    break;

  case 669:

/* Line 1806 of yacc.c  */
#line 3782 "def.y"
    {
        if (defData->callbacks->ScanchainCbk) {
          if (strcmp((yyvsp[(2) - (8)].string), "IN") == 0 || strcmp((yyvsp[(2) - (8)].string), "in") == 0)
            defData->Scanchain.addFloatingIn((yyvsp[(3) - (8)].string));
          else if (strcmp((yyvsp[(2) - (8)].string), "OUT") == 0 || strcmp((yyvsp[(2) - (8)].string), "out") == 0)
            defData->Scanchain.addFloatingOut((yyvsp[(3) - (8)].string));
          else if (strcmp((yyvsp[(2) - (8)].string), "BITS") == 0 || strcmp((yyvsp[(2) - (8)].string), "bits") == 0) {
            defData->bitsNum = atoi((yyvsp[(3) - (8)].string));
            defData->Scanchain.setFloatingBits(defData->bitsNum);
          }
          if (strcmp((yyvsp[(6) - (8)].string), "IN") == 0 || strcmp((yyvsp[(6) - (8)].string), "in") == 0)
            defData->Scanchain.addFloatingIn((yyvsp[(7) - (8)].string));
          else if (strcmp((yyvsp[(6) - (8)].string), "OUT") == 0 || strcmp((yyvsp[(6) - (8)].string), "out") == 0)
            defData->Scanchain.addFloatingOut((yyvsp[(7) - (8)].string));
          else if (strcmp((yyvsp[(6) - (8)].string), "BITS") == 0 || strcmp((yyvsp[(6) - (8)].string), "bits") == 0) {
            defData->bitsNum = atoi((yyvsp[(7) - (8)].string));
            defData->Scanchain.setFloatingBits(defData->bitsNum);
          }
        }
      }
    break;

  case 670:

/* Line 1806 of yacc.c  */
#line 3804 "def.y"
    {
        if (defData->callbacks->ScanchainCbk) {
          if (strcmp((yyvsp[(2) - (12)].string), "IN") == 0 || strcmp((yyvsp[(2) - (12)].string), "in") == 0)
            defData->Scanchain.addFloatingIn((yyvsp[(3) - (12)].string));
          else if (strcmp((yyvsp[(2) - (12)].string), "OUT") == 0 || strcmp((yyvsp[(2) - (12)].string), "out") == 0)
            defData->Scanchain.addFloatingOut((yyvsp[(3) - (12)].string));
          else if (strcmp((yyvsp[(2) - (12)].string), "BITS") == 0 || strcmp((yyvsp[(2) - (12)].string), "bits") == 0) {
            defData->bitsNum = atoi((yyvsp[(3) - (12)].string));
            defData->Scanchain.setFloatingBits(defData->bitsNum);
          }
          if (strcmp((yyvsp[(6) - (12)].string), "IN") == 0 || strcmp((yyvsp[(6) - (12)].string), "in") == 0)
            defData->Scanchain.addFloatingIn((yyvsp[(7) - (12)].string));
          else if (strcmp((yyvsp[(6) - (12)].string), "OUT") == 0 || strcmp((yyvsp[(6) - (12)].string), "out") == 0)
            defData->Scanchain.addFloatingOut((yyvsp[(7) - (12)].string));
          else if (strcmp((yyvsp[(6) - (12)].string), "BITS") == 0 || strcmp((yyvsp[(6) - (12)].string), "bits") == 0) {
            defData->bitsNum = atoi((yyvsp[(7) - (12)].string));
            defData->Scanchain.setFloatingBits(defData->bitsNum);
          }
          if (strcmp((yyvsp[(10) - (12)].string), "IN") == 0 || strcmp((yyvsp[(10) - (12)].string), "in") == 0)
            defData->Scanchain.addFloatingIn((yyvsp[(11) - (12)].string));
          else if (strcmp((yyvsp[(10) - (12)].string), "OUT") == 0 || strcmp((yyvsp[(10) - (12)].string), "out") == 0)
            defData->Scanchain.addFloatingOut((yyvsp[(11) - (12)].string));
          else if (strcmp((yyvsp[(10) - (12)].string), "BITS") == 0 || strcmp((yyvsp[(10) - (12)].string), "bits") == 0) {
            defData->bitsNum = atoi((yyvsp[(11) - (12)].string));
            defData->Scanchain.setFloatingBits(defData->bitsNum);
          }
        }
      }
    break;

  case 673:

/* Line 1806 of yacc.c  */
#line 3838 "def.y"
    { defData->dumb_mode = 1000; defData->no_num = 1000; 
        if (defData->callbacks->ScanchainCbk)
          defData->Scanchain.addOrderedInst((yyvsp[(1) - (1)].string));
      }
    break;

  case 674:

/* Line 1806 of yacc.c  */
#line 3843 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 675:

/* Line 1806 of yacc.c  */
#line 3846 "def.y"
    { }
    break;

  case 676:

/* Line 1806 of yacc.c  */
#line 3848 "def.y"
    {
        if (defData->callbacks->ScanchainCbk) {
          if (strcmp((yyvsp[(2) - (4)].string), "IN") == 0 || strcmp((yyvsp[(2) - (4)].string), "in") == 0)
            defData->Scanchain.addOrderedIn((yyvsp[(3) - (4)].string));
          else if (strcmp((yyvsp[(2) - (4)].string), "OUT") == 0 || strcmp((yyvsp[(2) - (4)].string), "out") == 0)
            defData->Scanchain.addOrderedOut((yyvsp[(3) - (4)].string));
          else if (strcmp((yyvsp[(2) - (4)].string), "BITS") == 0 || strcmp((yyvsp[(2) - (4)].string), "bits") == 0) {
            defData->bitsNum = atoi((yyvsp[(3) - (4)].string));
            defData->Scanchain.setOrderedBits(defData->bitsNum);
         }
        }
      }
    break;

  case 677:

/* Line 1806 of yacc.c  */
#line 3861 "def.y"
    {
        if (defData->callbacks->ScanchainCbk) {
          if (strcmp((yyvsp[(2) - (8)].string), "IN") == 0 || strcmp((yyvsp[(2) - (8)].string), "in") == 0)
            defData->Scanchain.addOrderedIn((yyvsp[(3) - (8)].string));
          else if (strcmp((yyvsp[(2) - (8)].string), "OUT") == 0 || strcmp((yyvsp[(2) - (8)].string), "out") == 0)
            defData->Scanchain.addOrderedOut((yyvsp[(3) - (8)].string));
          else if (strcmp((yyvsp[(2) - (8)].string), "BITS") == 0 || strcmp((yyvsp[(2) - (8)].string), "bits") == 0) {
            defData->bitsNum = atoi((yyvsp[(3) - (8)].string));
            defData->Scanchain.setOrderedBits(defData->bitsNum);
          }
          if (strcmp((yyvsp[(6) - (8)].string), "IN") == 0 || strcmp((yyvsp[(6) - (8)].string), "in") == 0)
            defData->Scanchain.addOrderedIn((yyvsp[(7) - (8)].string));
          else if (strcmp((yyvsp[(6) - (8)].string), "OUT") == 0 || strcmp((yyvsp[(6) - (8)].string), "out") == 0)
            defData->Scanchain.addOrderedOut((yyvsp[(7) - (8)].string));
          else if (strcmp((yyvsp[(6) - (8)].string), "BITS") == 0 || strcmp((yyvsp[(6) - (8)].string), "bits") == 0) {
            defData->bitsNum = atoi((yyvsp[(7) - (8)].string));
            defData->Scanchain.setOrderedBits(defData->bitsNum);
          }
        }
      }
    break;

  case 678:

/* Line 1806 of yacc.c  */
#line 3883 "def.y"
    {
        if (defData->callbacks->ScanchainCbk) {
          if (strcmp((yyvsp[(2) - (12)].string), "IN") == 0 || strcmp((yyvsp[(2) - (12)].string), "in") == 0)
            defData->Scanchain.addOrderedIn((yyvsp[(3) - (12)].string));
          else if (strcmp((yyvsp[(2) - (12)].string), "OUT") == 0 || strcmp((yyvsp[(2) - (12)].string), "out") == 0)
            defData->Scanchain.addOrderedOut((yyvsp[(3) - (12)].string));
          else if (strcmp((yyvsp[(2) - (12)].string), "BITS") == 0 || strcmp((yyvsp[(2) - (12)].string), "bits") == 0) {
            defData->bitsNum = atoi((yyvsp[(3) - (12)].string));
            defData->Scanchain.setOrderedBits(defData->bitsNum);
          }
          if (strcmp((yyvsp[(6) - (12)].string), "IN") == 0 || strcmp((yyvsp[(6) - (12)].string), "in") == 0)
            defData->Scanchain.addOrderedIn((yyvsp[(7) - (12)].string));
          else if (strcmp((yyvsp[(6) - (12)].string), "OUT") == 0 || strcmp((yyvsp[(6) - (12)].string), "out") == 0)
            defData->Scanchain.addOrderedOut((yyvsp[(7) - (12)].string));
          else if (strcmp((yyvsp[(6) - (12)].string), "BITS") == 0 || strcmp((yyvsp[(6) - (12)].string), "bits") == 0) {
            defData->bitsNum = atoi((yyvsp[(7) - (12)].string));
            defData->Scanchain.setOrderedBits(defData->bitsNum);
          }
          if (strcmp((yyvsp[(10) - (12)].string), "IN") == 0 || strcmp((yyvsp[(10) - (12)].string), "in") == 0)
            defData->Scanchain.addOrderedIn((yyvsp[(11) - (12)].string));
          else if (strcmp((yyvsp[(10) - (12)].string), "OUT") == 0 || strcmp((yyvsp[(10) - (12)].string), "out") == 0)
            defData->Scanchain.addOrderedOut((yyvsp[(11) - (12)].string));
          else if (strcmp((yyvsp[(10) - (12)].string), "BITS") == 0 || strcmp((yyvsp[(10) - (12)].string), "bits") == 0) {
            defData->bitsNum = atoi((yyvsp[(11) - (12)].string));
            defData->Scanchain.setOrderedBits(defData->bitsNum);
          }
        }
      }
    break;

  case 679:

/* Line 1806 of yacc.c  */
#line 3913 "def.y"
    { (yyval.integer) = -1; }
    break;

  case 680:

/* Line 1806 of yacc.c  */
#line 3915 "def.y"
    { (yyval.integer) = ROUND((yyvsp[(2) - (2)].dval)); }
    break;

  case 681:

/* Line 1806 of yacc.c  */
#line 3918 "def.y"
    { 
        if (defData->callbacks->ScanchainsEndCbk)
          CALLBACK(defData->callbacks->ScanchainsEndCbk, defrScanchainsEndCbkType, 0);
        defData->bit_is_keyword = FALSE;
        defData->dumb_mode = 0; defData->no_num = 0;
      }
    break;

  case 683:

/* Line 1806 of yacc.c  */
#line 3930 "def.y"
    {
        if (defData->VersionNum < 5.4 && defData->callbacks->IOTimingsStartCbk) {
          CALLBACK(defData->callbacks->IOTimingsStartCbk, defrIOTimingsStartCbkType, ROUND((yyvsp[(2) - (3)].dval)));
        } else {
          if (defData->callbacks->IOTimingsStartCbk)
            if (defData->iOTimingWarnings++ < defData->settings->IOTimingWarnings)
              defData->defWarning(7035, "The IOTIMINGS statement is obsolete in version 5.4 and later.\nThe DEF parser will ignore this statement.");
        }
      }
    break;

  case 685:

/* Line 1806 of yacc.c  */
#line 3942 "def.y"
    { }
    break;

  case 686:

/* Line 1806 of yacc.c  */
#line 3945 "def.y"
    { 
        if (defData->VersionNum < 5.4 && defData->callbacks->IOTimingCbk)
          CALLBACK(defData->callbacks->IOTimingCbk, defrIOTimingCbkType, &defData->IOTiming);
      }
    break;

  case 687:

/* Line 1806 of yacc.c  */
#line 3950 "def.y"
    {defData->dumb_mode = 2; defData->no_num = 2; }
    break;

  case 688:

/* Line 1806 of yacc.c  */
#line 3951 "def.y"
    {
        if (defData->callbacks->IOTimingCbk)
          defData->IOTiming.setName((yyvsp[(4) - (6)].string), (yyvsp[(5) - (6)].string));
      }
    break;

  case 691:

/* Line 1806 of yacc.c  */
#line 3962 "def.y"
    {
        if (defData->callbacks->IOTimingCbk) 
          defData->IOTiming.setVariable((yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].dval), (yyvsp[(5) - (5)].dval));
      }
    break;

  case 692:

/* Line 1806 of yacc.c  */
#line 3967 "def.y"
    {
        if (defData->callbacks->IOTimingCbk) 
          defData->IOTiming.setSlewRate((yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].dval), (yyvsp[(5) - (5)].dval));
      }
    break;

  case 693:

/* Line 1806 of yacc.c  */
#line 3972 "def.y"
    {
        if (defData->callbacks->IOTimingCbk) 
          defData->IOTiming.setCapacitance((yyvsp[(3) - (3)].dval));
      }
    break;

  case 694:

/* Line 1806 of yacc.c  */
#line 3976 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 695:

/* Line 1806 of yacc.c  */
#line 3977 "def.y"
    {
        if (defData->callbacks->IOTimingCbk) 
          defData->IOTiming.setDriveCell((yyvsp[(4) - (4)].string));
      }
    break;

  case 697:

/* Line 1806 of yacc.c  */
#line 3986 "def.y"
    {
        if (defData->VersionNum < 5.4 && defData->callbacks->IoTimingsExtCbk)
          CALLBACK(defData->callbacks->IoTimingsExtCbk, defrIoTimingsExtCbkType, &defData->History_text[0]);
      }
    break;

  case 698:

/* Line 1806 of yacc.c  */
#line 3992 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 699:

/* Line 1806 of yacc.c  */
#line 3993 "def.y"
    {
        if (defData->callbacks->IOTimingCbk) 
          defData->IOTiming.setTo((yyvsp[(4) - (4)].string));
      }
    break;

  case 702:

/* Line 1806 of yacc.c  */
#line 4000 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 703:

/* Line 1806 of yacc.c  */
#line 4001 "def.y"
    {
        if (defData->callbacks->IOTimingCbk)
          defData->IOTiming.setFrom((yyvsp[(3) - (3)].string));
      }
    break;

  case 705:

/* Line 1806 of yacc.c  */
#line 4008 "def.y"
    {
        if (defData->callbacks->IOTimingCbk)
          defData->IOTiming.setParallel((yyvsp[(2) - (2)].dval));
      }
    break;

  case 706:

/* Line 1806 of yacc.c  */
#line 4013 "def.y"
    { (yyval.string) = (char*)"RISE"; }
    break;

  case 707:

/* Line 1806 of yacc.c  */
#line 4013 "def.y"
    { (yyval.string) = (char*)"FALL"; }
    break;

  case 708:

/* Line 1806 of yacc.c  */
#line 4016 "def.y"
    {
        if (defData->VersionNum < 5.4 && defData->callbacks->IOTimingsEndCbk)
          CALLBACK(defData->callbacks->IOTimingsEndCbk, defrIOTimingsEndCbkType, 0);
      }
    break;

  case 709:

/* Line 1806 of yacc.c  */
#line 4022 "def.y"
    { 
        if (defData->callbacks->FPCEndCbk)
          CALLBACK(defData->callbacks->FPCEndCbk, defrFPCEndCbkType, 0);
      }
    break;

  case 710:

/* Line 1806 of yacc.c  */
#line 4028 "def.y"
    {
        if (defData->callbacks->FPCStartCbk)
          CALLBACK(defData->callbacks->FPCStartCbk, defrFPCStartCbkType, ROUND((yyvsp[(2) - (3)].dval)));
      }
    break;

  case 712:

/* Line 1806 of yacc.c  */
#line 4035 "def.y"
    {}
    break;

  case 713:

/* Line 1806 of yacc.c  */
#line 4037 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1;  }
    break;

  case 714:

/* Line 1806 of yacc.c  */
#line 4038 "def.y"
    { if (defData->callbacks->FPCCbk) defData->FPC.setName((yyvsp[(3) - (4)].string), (yyvsp[(4) - (4)].string)); }
    break;

  case 715:

/* Line 1806 of yacc.c  */
#line 4040 "def.y"
    { if (defData->callbacks->FPCCbk) CALLBACK(defData->callbacks->FPCCbk, defrFPCCbkType, &defData->FPC); }
    break;

  case 716:

/* Line 1806 of yacc.c  */
#line 4043 "def.y"
    { (yyval.string) = (char*)"HORIZONTAL"; }
    break;

  case 717:

/* Line 1806 of yacc.c  */
#line 4045 "def.y"
    { (yyval.string) = (char*)"VERTICAL"; }
    break;

  case 718:

/* Line 1806 of yacc.c  */
#line 4048 "def.y"
    { if (defData->callbacks->FPCCbk) defData->FPC.setAlign(); }
    break;

  case 719:

/* Line 1806 of yacc.c  */
#line 4050 "def.y"
    { if (defData->callbacks->FPCCbk) defData->FPC.setMax((yyvsp[(2) - (2)].dval)); }
    break;

  case 720:

/* Line 1806 of yacc.c  */
#line 4052 "def.y"
    { if (defData->callbacks->FPCCbk) defData->FPC.setMin((yyvsp[(2) - (2)].dval)); }
    break;

  case 721:

/* Line 1806 of yacc.c  */
#line 4054 "def.y"
    { if (defData->callbacks->FPCCbk) defData->FPC.setEqual((yyvsp[(2) - (2)].dval)); }
    break;

  case 724:

/* Line 1806 of yacc.c  */
#line 4061 "def.y"
    { if (defData->callbacks->FPCCbk) defData->FPC.setDoingBottomLeft(); }
    break;

  case 726:

/* Line 1806 of yacc.c  */
#line 4064 "def.y"
    { if (defData->callbacks->FPCCbk) defData->FPC.setDoingTopRight(); }
    break;

  case 730:

/* Line 1806 of yacc.c  */
#line 4071 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 731:

/* Line 1806 of yacc.c  */
#line 4072 "def.y"
    { if (defData->callbacks->FPCCbk) defData->FPC.addRow((yyvsp[(4) - (5)].string)); }
    break;

  case 732:

/* Line 1806 of yacc.c  */
#line 4073 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 733:

/* Line 1806 of yacc.c  */
#line 4074 "def.y"
    { if (defData->callbacks->FPCCbk) defData->FPC.addComps((yyvsp[(4) - (5)].string)); }
    break;

  case 735:

/* Line 1806 of yacc.c  */
#line 4081 "def.y"
    { 
        if (defData->callbacks->TimingDisablesStartCbk)
          CALLBACK(defData->callbacks->TimingDisablesStartCbk, defrTimingDisablesStartCbkType,
                   ROUND((yyvsp[(2) - (3)].dval)));
      }
    break;

  case 737:

/* Line 1806 of yacc.c  */
#line 4089 "def.y"
    {}
    break;

  case 738:

/* Line 1806 of yacc.c  */
#line 4091 "def.y"
    { defData->dumb_mode = 2; defData->no_num = 2;  }
    break;

  case 739:

/* Line 1806 of yacc.c  */
#line 4092 "def.y"
    { defData->dumb_mode = 2; defData->no_num = 2;  }
    break;

  case 740:

/* Line 1806 of yacc.c  */
#line 4093 "def.y"
    {
        if (defData->callbacks->TimingDisableCbk) {
          defData->TimingDisable.setFromTo((yyvsp[(4) - (10)].string), (yyvsp[(5) - (10)].string), (yyvsp[(8) - (10)].string), (yyvsp[(9) - (10)].string));
          CALLBACK(defData->callbacks->TimingDisableCbk, defrTimingDisableCbkType,
                &defData->TimingDisable);
        }
      }
    break;

  case 741:

/* Line 1806 of yacc.c  */
#line 4100 "def.y"
    {defData->dumb_mode = 2; defData->no_num = 2; }
    break;

  case 742:

/* Line 1806 of yacc.c  */
#line 4101 "def.y"
    {
        if (defData->callbacks->TimingDisableCbk) {
          defData->TimingDisable.setThru((yyvsp[(4) - (6)].string), (yyvsp[(5) - (6)].string));
          CALLBACK(defData->callbacks->TimingDisableCbk, defrTimingDisableCbkType,
                   &defData->TimingDisable);
        }
      }
    break;

  case 743:

/* Line 1806 of yacc.c  */
#line 4108 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1;}
    break;

  case 744:

/* Line 1806 of yacc.c  */
#line 4109 "def.y"
    {
        if (defData->callbacks->TimingDisableCbk) {
          defData->TimingDisable.setMacro((yyvsp[(4) - (6)].string));
          CALLBACK(defData->callbacks->TimingDisableCbk, defrTimingDisableCbkType,
                &defData->TimingDisable);
        }
      }
    break;

  case 745:

/* Line 1806 of yacc.c  */
#line 4117 "def.y"
    { if (defData->callbacks->TimingDisableCbk)
          defData->TimingDisable.setReentrantPathsFlag();
      }
    break;

  case 746:

/* Line 1806 of yacc.c  */
#line 4122 "def.y"
    {defData->dumb_mode = 1; defData->no_num = 1;}
    break;

  case 747:

/* Line 1806 of yacc.c  */
#line 4123 "def.y"
    {defData->dumb_mode=1; defData->no_num = 1;}
    break;

  case 748:

/* Line 1806 of yacc.c  */
#line 4124 "def.y"
    {
        if (defData->callbacks->TimingDisableCbk)
          defData->TimingDisable.setMacroFromTo((yyvsp[(3) - (6)].string),(yyvsp[(6) - (6)].string));
      }
    break;

  case 749:

/* Line 1806 of yacc.c  */
#line 4128 "def.y"
    {defData->dumb_mode=1; defData->no_num = 1;}
    break;

  case 750:

/* Line 1806 of yacc.c  */
#line 4129 "def.y"
    {
        if (defData->callbacks->TimingDisableCbk)
          defData->TimingDisable.setMacroThru((yyvsp[(3) - (3)].string));
      }
    break;

  case 751:

/* Line 1806 of yacc.c  */
#line 4135 "def.y"
    { 
        if (defData->callbacks->TimingDisablesEndCbk)
          CALLBACK(defData->callbacks->TimingDisablesEndCbk, defrTimingDisablesEndCbkType, 0);
      }
    break;

  case 753:

/* Line 1806 of yacc.c  */
#line 4145 "def.y"
    {
        if (defData->callbacks->PartitionsStartCbk)
          CALLBACK(defData->callbacks->PartitionsStartCbk, defrPartitionsStartCbkType,
                   ROUND((yyvsp[(2) - (3)].dval)));
      }
    break;

  case 755:

/* Line 1806 of yacc.c  */
#line 4153 "def.y"
    { }
    break;

  case 756:

/* Line 1806 of yacc.c  */
#line 4156 "def.y"
    { 
        if (defData->callbacks->PartitionCbk)
          CALLBACK(defData->callbacks->PartitionCbk, defrPartitionCbkType, &defData->Partition);
      }
    break;

  case 757:

/* Line 1806 of yacc.c  */
#line 4161 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 758:

/* Line 1806 of yacc.c  */
#line 4162 "def.y"
    {
        if (defData->callbacks->PartitionCbk)
          defData->Partition.setName((yyvsp[(3) - (4)].string));
      }
    break;

  case 760:

/* Line 1806 of yacc.c  */
#line 4169 "def.y"
    {
        if (defData->callbacks->PartitionCbk)
          defData->Partition.addTurnOff((yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].string));
      }
    break;

  case 761:

/* Line 1806 of yacc.c  */
#line 4175 "def.y"
    { (yyval.string) = (char*)" "; }
    break;

  case 762:

/* Line 1806 of yacc.c  */
#line 4177 "def.y"
    { (yyval.string) = (char*)"R"; }
    break;

  case 763:

/* Line 1806 of yacc.c  */
#line 4179 "def.y"
    { (yyval.string) = (char*)"F"; }
    break;

  case 764:

/* Line 1806 of yacc.c  */
#line 4182 "def.y"
    { (yyval.string) = (char*)" "; }
    break;

  case 765:

/* Line 1806 of yacc.c  */
#line 4184 "def.y"
    { (yyval.string) = (char*)"R"; }
    break;

  case 766:

/* Line 1806 of yacc.c  */
#line 4186 "def.y"
    { (yyval.string) = (char*)"F"; }
    break;

  case 769:

/* Line 1806 of yacc.c  */
#line 4192 "def.y"
    {defData->dumb_mode=2; defData->no_num = 2;}
    break;

  case 770:

/* Line 1806 of yacc.c  */
#line 4194 "def.y"
    {
        if (defData->callbacks->PartitionCbk)
          defData->Partition.setFromClockPin((yyvsp[(4) - (7)].string), (yyvsp[(5) - (7)].string));
      }
    break;

  case 771:

/* Line 1806 of yacc.c  */
#line 4198 "def.y"
    {defData->dumb_mode=2; defData->no_num = 2; }
    break;

  case 772:

/* Line 1806 of yacc.c  */
#line 4200 "def.y"
    {
        if (defData->callbacks->PartitionCbk)
          defData->Partition.setFromCompPin((yyvsp[(4) - (6)].string), (yyvsp[(5) - (6)].string));
      }
    break;

  case 773:

/* Line 1806 of yacc.c  */
#line 4204 "def.y"
    {defData->dumb_mode=1; defData->no_num = 1; }
    break;

  case 774:

/* Line 1806 of yacc.c  */
#line 4206 "def.y"
    {
        if (defData->callbacks->PartitionCbk)
          defData->Partition.setFromIOPin((yyvsp[(4) - (5)].string));
      }
    break;

  case 775:

/* Line 1806 of yacc.c  */
#line 4210 "def.y"
    {defData->dumb_mode=2; defData->no_num = 2; }
    break;

  case 776:

/* Line 1806 of yacc.c  */
#line 4212 "def.y"
    {
        if (defData->callbacks->PartitionCbk)
          defData->Partition.setToClockPin((yyvsp[(4) - (7)].string), (yyvsp[(5) - (7)].string));
      }
    break;

  case 777:

/* Line 1806 of yacc.c  */
#line 4216 "def.y"
    {defData->dumb_mode=2; defData->no_num = 2; }
    break;

  case 778:

/* Line 1806 of yacc.c  */
#line 4218 "def.y"
    {
        if (defData->callbacks->PartitionCbk)
          defData->Partition.setToCompPin((yyvsp[(4) - (6)].string), (yyvsp[(5) - (6)].string));
      }
    break;

  case 779:

/* Line 1806 of yacc.c  */
#line 4222 "def.y"
    {defData->dumb_mode=1; defData->no_num = 2; }
    break;

  case 780:

/* Line 1806 of yacc.c  */
#line 4223 "def.y"
    {
        if (defData->callbacks->PartitionCbk)
          defData->Partition.setToIOPin((yyvsp[(4) - (5)].string));
      }
    break;

  case 781:

/* Line 1806 of yacc.c  */
#line 4228 "def.y"
    { 
        if (defData->callbacks->PartitionsExtCbk)
          CALLBACK(defData->callbacks->PartitionsExtCbk, defrPartitionsExtCbkType,
                   &defData->History_text[0]);
      }
    break;

  case 782:

/* Line 1806 of yacc.c  */
#line 4235 "def.y"
    { defData->dumb_mode = DEF_MAX_INT; defData->no_num = DEF_MAX_INT; }
    break;

  case 783:

/* Line 1806 of yacc.c  */
#line 4236 "def.y"
    { defData->dumb_mode = 0; defData->no_num = 0; }
    break;

  case 785:

/* Line 1806 of yacc.c  */
#line 4240 "def.y"
    { }
    break;

  case 786:

/* Line 1806 of yacc.c  */
#line 4243 "def.y"
    {
        if (defData->callbacks->PartitionCbk)
          defData->Partition.setMin((yyvsp[(2) - (3)].dval), (yyvsp[(3) - (3)].dval));
      }
    break;

  case 787:

/* Line 1806 of yacc.c  */
#line 4248 "def.y"
    {
        if (defData->callbacks->PartitionCbk)
          defData->Partition.setMax((yyvsp[(2) - (3)].dval), (yyvsp[(3) - (3)].dval));
      }
    break;

  case 789:

/* Line 1806 of yacc.c  */
#line 4255 "def.y"
    { if (defData->callbacks->PartitionCbk) defData->Partition.addPin((yyvsp[(2) - (2)].string)); }
    break;

  case 792:

/* Line 1806 of yacc.c  */
#line 4261 "def.y"
    { if (defData->callbacks->PartitionCbk) defData->Partition.addRiseMin((yyvsp[(2) - (2)].dval)); }
    break;

  case 793:

/* Line 1806 of yacc.c  */
#line 4263 "def.y"
    { if (defData->callbacks->PartitionCbk) defData->Partition.addFallMin((yyvsp[(2) - (2)].dval)); }
    break;

  case 794:

/* Line 1806 of yacc.c  */
#line 4265 "def.y"
    { if (defData->callbacks->PartitionCbk) defData->Partition.addRiseMax((yyvsp[(2) - (2)].dval)); }
    break;

  case 795:

/* Line 1806 of yacc.c  */
#line 4267 "def.y"
    { if (defData->callbacks->PartitionCbk) defData->Partition.addFallMax((yyvsp[(2) - (2)].dval)); }
    break;

  case 798:

/* Line 1806 of yacc.c  */
#line 4275 "def.y"
    { if (defData->callbacks->PartitionCbk)
          defData->Partition.addRiseMinRange((yyvsp[(2) - (3)].dval), (yyvsp[(3) - (3)].dval)); }
    break;

  case 799:

/* Line 1806 of yacc.c  */
#line 4278 "def.y"
    { if (defData->callbacks->PartitionCbk)
          defData->Partition.addFallMinRange((yyvsp[(2) - (3)].dval), (yyvsp[(3) - (3)].dval)); }
    break;

  case 800:

/* Line 1806 of yacc.c  */
#line 4281 "def.y"
    { if (defData->callbacks->PartitionCbk)
          defData->Partition.addRiseMaxRange((yyvsp[(2) - (3)].dval), (yyvsp[(3) - (3)].dval)); }
    break;

  case 801:

/* Line 1806 of yacc.c  */
#line 4284 "def.y"
    { if (defData->callbacks->PartitionCbk)
          defData->Partition.addFallMaxRange((yyvsp[(2) - (3)].dval), (yyvsp[(3) - (3)].dval)); }
    break;

  case 802:

/* Line 1806 of yacc.c  */
#line 4288 "def.y"
    { if (defData->callbacks->PartitionsEndCbk)
          CALLBACK(defData->callbacks->PartitionsEndCbk, defrPartitionsEndCbkType, 0); }
    break;

  case 804:

/* Line 1806 of yacc.c  */
#line 4293 "def.y"
    { }
    break;

  case 805:

/* Line 1806 of yacc.c  */
#line 4295 "def.y"
    {defData->dumb_mode=2; defData->no_num = 2; }
    break;

  case 806:

/* Line 1806 of yacc.c  */
#line 4297 "def.y"
    {
        // note that the defData->first T_STRING could be the keyword VPIN 
        if (defData->callbacks->NetCbk)
          defData->Subnet->addPin((yyvsp[(3) - (6)].string), (yyvsp[(4) - (6)].string), (yyvsp[(5) - (6)].integer));
      }
    break;

  case 807:

/* Line 1806 of yacc.c  */
#line 4304 "def.y"
    { (yyval.integer) = 0; }
    break;

  case 808:

/* Line 1806 of yacc.c  */
#line 4306 "def.y"
    { (yyval.integer) = 1; }
    break;

  case 811:

/* Line 1806 of yacc.c  */
#line 4312 "def.y"
    {  
        if (defData->callbacks->NetCbk) defData->Subnet->addWire((yyvsp[(1) - (1)].string));
      }
    break;

  case 812:

/* Line 1806 of yacc.c  */
#line 4316 "def.y"
    {  
        defData->by_is_keyword = FALSE;
        defData->do_is_keyword = FALSE;
        defData->new_is_keyword = FALSE;
        defData->step_is_keyword = FALSE;
        defData->orient_is_keyword = FALSE;
        defData->needNPCbk = 0;
      }
    break;

  case 813:

/* Line 1806 of yacc.c  */
#line 4324 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 814:

/* Line 1806 of yacc.c  */
#line 4325 "def.y"
    { if (defData->callbacks->NetCbk) defData->Subnet->setNonDefault((yyvsp[(3) - (3)].string)); }
    break;

  case 815:

/* Line 1806 of yacc.c  */
#line 4328 "def.y"
    { (yyval.string) = (char*)"FIXED"; defData->dumb_mode = 1; }
    break;

  case 816:

/* Line 1806 of yacc.c  */
#line 4330 "def.y"
    { (yyval.string) = (char*)"COVER"; defData->dumb_mode = 1; }
    break;

  case 817:

/* Line 1806 of yacc.c  */
#line 4332 "def.y"
    { (yyval.string) = (char*)"ROUTED"; defData->dumb_mode = 1; }
    break;

  case 818:

/* Line 1806 of yacc.c  */
#line 4334 "def.y"
    { (yyval.string) = (char*)"NOSHIELD"; defData->dumb_mode = 1; }
    break;

  case 820:

/* Line 1806 of yacc.c  */
#line 4339 "def.y"
    { if (defData->callbacks->PinPropStartCbk)
          CALLBACK(defData->callbacks->PinPropStartCbk, defrPinPropStartCbkType, ROUND((yyvsp[(2) - (3)].dval))); }
    break;

  case 821:

/* Line 1806 of yacc.c  */
#line 4344 "def.y"
    { }
    break;

  case 822:

/* Line 1806 of yacc.c  */
#line 4346 "def.y"
    { }
    break;

  case 823:

/* Line 1806 of yacc.c  */
#line 4349 "def.y"
    { if (defData->callbacks->PinPropEndCbk)
          CALLBACK(defData->callbacks->PinPropEndCbk, defrPinPropEndCbkType, 0); }
    break;

  case 826:

/* Line 1806 of yacc.c  */
#line 4356 "def.y"
    { defData->dumb_mode = 2; defData->no_num = 2; }
    break;

  case 827:

/* Line 1806 of yacc.c  */
#line 4357 "def.y"
    { if (defData->callbacks->PinPropCbk) defData->PinProp.setName((yyvsp[(3) - (4)].string), (yyvsp[(4) - (4)].string)); }
    break;

  case 828:

/* Line 1806 of yacc.c  */
#line 4359 "def.y"
    { if (defData->callbacks->PinPropCbk) {
          CALLBACK(defData->callbacks->PinPropCbk, defrPinPropCbkType, &defData->PinProp);
         // reset the property number
         defData->PinProp.clear();
        }
      }
    break;

  case 831:

/* Line 1806 of yacc.c  */
#line 4369 "def.y"
    { defData->dumb_mode = DEF_MAX_INT; }
    break;

  case 832:

/* Line 1806 of yacc.c  */
#line 4371 "def.y"
    { defData->dumb_mode = 0; }
    break;

  case 835:

/* Line 1806 of yacc.c  */
#line 4378 "def.y"
    {
        if (defData->callbacks->PinPropCbk) {
          char propTp;
          char* str = defData->ringCopy("                       ");
          propTp = defData->session->CompPinProp.propType((yyvsp[(1) - (2)].string));
          CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "PINPROPERTIES");
          sprintf(str, "%g", (yyvsp[(2) - (2)].dval));
          defData->PinProp.addNumProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].dval), str, propTp);
        }
      }
    break;

  case 836:

/* Line 1806 of yacc.c  */
#line 4389 "def.y"
    {
        if (defData->callbacks->PinPropCbk) {
          char propTp;
          propTp = defData->session->CompPinProp.propType((yyvsp[(1) - (2)].string));
          CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "PINPROPERTIES");
          defData->PinProp.addProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
        }
      }
    break;

  case 837:

/* Line 1806 of yacc.c  */
#line 4398 "def.y"
    {
        if (defData->callbacks->PinPropCbk) {
          char propTp;
          propTp = defData->session->CompPinProp.propType((yyvsp[(1) - (2)].string));
          CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "PINPROPERTIES");
          defData->PinProp.addProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
        }
      }
    break;

  case 839:

/* Line 1806 of yacc.c  */
#line 4410 "def.y"
    { if (defData->callbacks->BlockageStartCbk)
          CALLBACK(defData->callbacks->BlockageStartCbk, defrBlockageStartCbkType, ROUND((yyvsp[(2) - (3)].dval))); }
    break;

  case 840:

/* Line 1806 of yacc.c  */
#line 4414 "def.y"
    { if (defData->callbacks->BlockageEndCbk)
          CALLBACK(defData->callbacks->BlockageEndCbk, defrBlockageEndCbkType, 0); }
    break;

  case 843:

/* Line 1806 of yacc.c  */
#line 4423 "def.y"
    {
        if (defData->callbacks->BlockageCbk) {
          CALLBACK(defData->callbacks->BlockageCbk, defrBlockageCbkType, &defData->Blockage);
          defData->Blockage.clear();
        }
      }
    break;

  case 844:

/* Line 1806 of yacc.c  */
#line 4430 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 845:

/* Line 1806 of yacc.c  */
#line 4431 "def.y"
    {
        if (defData->callbacks->BlockageCbk) {
          if (defData->Blockage.hasPlacement() != 0) {
            if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
              defData->defError(6539, "Invalid BLOCKAGE statement defined in the DEF file. The BLOCKAGE statment has both the LAYER and the PLACEMENT statements defined.\nUpdate your DEF file to have either BLOCKAGE or PLACEMENT statement only.");
              CHKERR();
            }
          }
          defData->Blockage.setLayer((yyvsp[(4) - (4)].string));
          defData->Blockage.clearPoly(); // free poly, if any
        }
        defData->hasBlkLayerComp = 0;
        defData->hasBlkLayerSpac = 0;
        defData->hasBlkLayerTypeComp = 0;
      }
    break;

  case 847:

/* Line 1806 of yacc.c  */
#line 4450 "def.y"
    {
        if (defData->callbacks->BlockageCbk) {
          if (defData->Blockage.hasLayer() != 0) {
            if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
              defData->defError(6539, "Invalid BLOCKAGE statement defined in the DEF file. The BLOCKAGE statment has both the LAYER and the PLACEMENT statements defined.\nUpdate your DEF file to have either BLOCKAGE or PLACEMENT statement only.");
              CHKERR();
            }
          }
          defData->Blockage.setPlacement();
          defData->Blockage.clearPoly(); // free poly, if any
        }
        defData->hasBlkPlaceComp = 0;
        defData->hasBlkPlaceTypeComp = 0;
      }
    break;

  case 851:

/* Line 1806 of yacc.c  */
#line 4471 "def.y"
    {
        if (defData->VersionNum < 5.6) {
          if (defData->callbacks->BlockageCbk) {
            if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
              defData->defMsg = (char*)malloc(1000);
              sprintf (defData->defMsg,
                 "The SPACING statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
              defData->defError(6540, defData->defMsg);
              free(defData->defMsg);
              CHKERR();
            }
          }
        } else if (defData->hasBlkLayerSpac) {
          if (defData->callbacks->BlockageCbk) {
            if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
              defData->defError(6541, "The SPACING statement is defined in the LAYER statement,\nbut there is already either a SPACING statement or DESIGNRULEWIDTH  statement has defined in the LAYER statement.\nUpdate your DEF file to have either SPACING statement or a DESIGNRULEWIDTH statement.");
              CHKERR();
            }
          }
        } else {
          if (defData->callbacks->BlockageCbk)
            defData->Blockage.setSpacing((int)(yyvsp[(3) - (3)].dval));
          defData->hasBlkLayerSpac = 1;
        }
      }
    break;

  case 852:

/* Line 1806 of yacc.c  */
#line 4497 "def.y"
    {
        if (defData->VersionNum < 5.6) {
          if (defData->callbacks->BlockageCbk) {
            if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
              defData->defError(6541, "The SPACING statement is defined in the LAYER statement,\nbut there is already either a SPACING statement or DESIGNRULEWIDTH  statement has defined in the LAYER statement.\nUpdate your DEF file to have either SPACING statement or a DESIGNRULEWIDTH statement.");
              CHKERR();
            }
          }
        } else if (defData->hasBlkLayerSpac) {
          if (defData->callbacks->BlockageCbk) {
            if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
              defData->defError(6541, "The SPACING statement is defined in the LAYER statement,\nbut there is already either a SPACING statement or DESIGNRULEWIDTH  statement has defined in the LAYER statement.\nUpdate your DEF file to have either SPACING statement or a DESIGNRULEWIDTH statement.");
              CHKERR();
            }
          }
        } else {
          if (defData->callbacks->BlockageCbk)
            defData->Blockage.setDesignRuleWidth((int)(yyvsp[(3) - (3)].dval));
          defData->hasBlkLayerSpac = 1;
        }
      }
    break;

  case 855:

/* Line 1806 of yacc.c  */
#line 4523 "def.y"
    {      
        if (defData->validateMaskInput((int)(yyvsp[(3) - (3)].dval), defData->blockageWarnings, defData->settings->BlockageWarnings)) {
          defData->Blockage.setMask((int)(yyvsp[(3) - (3)].dval));
        }
      }
    break;

  case 856:

/* Line 1806 of yacc.c  */
#line 4531 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 857:

/* Line 1806 of yacc.c  */
#line 4532 "def.y"
    {
        if (defData->hasBlkLayerComp) {
          if (defData->callbacks->BlockageCbk) {
            if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
              defData->defError(6542, "The defined BLOCKAGES COMPONENT statement has either COMPONENT, SLOTS, FILLS, PUSHDOWN or EXCEPTPGNET defined.\nOnly one of these statements is allowed per LAYER. Updated the DEF file to define a valid BLOCKAGES COMPONENT statement per layer.");
              CHKERR();
            }
          }
        } else {
          if (defData->callbacks->BlockageCbk) {
            defData->Blockage.setComponent((yyvsp[(4) - (4)].string));
          }
          if (defData->VersionNum < 5.8) {
            defData->hasBlkLayerComp = 1;
          }
        }
      }
    break;

  case 858:

/* Line 1806 of yacc.c  */
#line 4551 "def.y"
    {
        if (defData->hasBlkLayerComp || defData->hasBlkLayerTypeComp) {
          if (defData->callbacks->BlockageCbk) {
            if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
              defData->defError(6542, "The defined BLOCKAGES COMPONENT statement has either COMPONENT, SLOTS, FILLS, PUSHDOWN or EXCEPTPGNET defined.\nOnly one of these statements is allowed per LAYER. Updated the DEF file to define a valid BLOCKAGES COMPONENT statement per layer.");
              CHKERR();
            }
          }
        } else {
          if (defData->callbacks->BlockageCbk) {
            defData->Blockage.setSlots();
          }
          if (defData->VersionNum < 5.8) {
            defData->hasBlkLayerComp = 1;
          }
          if (defData->VersionNum == 5.8) {
            defData->hasBlkLayerTypeComp = 1;
          }
        }
      }
    break;

  case 859:

/* Line 1806 of yacc.c  */
#line 4572 "def.y"
    {
        if (defData->hasBlkLayerComp || defData->hasBlkLayerTypeComp) {
          if (defData->callbacks->BlockageCbk) {
            if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
              defData->defError(6542, "The defined BLOCKAGES COMPONENT statement has either COMPONENT, SLOTS, FILLS, PUSHDOWN or EXCEPTPGNET defined.\nOnly one of these statements is allowed per LAYER. Updated the DEF file to define a valid BLOCKAGES COMPONENT statement per layer.");
              CHKERR();
            }
          }
        } else {
          if (defData->callbacks->BlockageCbk){
            defData->Blockage.setFills();
          }
          if (defData->VersionNum < 5.8) {
            defData->hasBlkLayerComp = 1;
          }
          if (defData->VersionNum == 5.8) {
            defData->hasBlkLayerTypeComp = 1;
          }
        }
      }
    break;

  case 860:

/* Line 1806 of yacc.c  */
#line 4593 "def.y"
    {
        if (defData->hasBlkLayerComp) {
          if (defData->callbacks->BlockageCbk) {
            if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
              defData->defError(6542, "The defined BLOCKAGES COMPONENT statement has either COMPONENT, SLOTS, FILLS, PUSHDOWN or EXCEPTPGNET defined.\nOnly one of these statements is allowed per LAYER. Updated the DEF file to define a valid BLOCKAGES COMPONENT statement per layer.");
              CHKERR();
            }
          }
        } else {
          if (defData->callbacks->BlockageCbk){
            defData->Blockage.setPushdown();
          }
          if (defData->VersionNum < 5.8) {
            defData->hasBlkLayerComp = 1;
          }
        }
      }
    break;

  case 861:

/* Line 1806 of yacc.c  */
#line 4611 "def.y"
    {
        if (defData->VersionNum < 5.7) {
           if (defData->callbacks->BlockageCbk) {
             if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
               defData->defMsg = (char*)malloc(10000);
               sprintf (defData->defMsg,
                 "The EXCEPTPGNET is available in version 5.7 or later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
               defData->defError(6549, defData->defMsg);
               free(defData->defMsg);
               CHKERR();
              }
           }
        } else {
           if (defData->hasBlkLayerComp) {
             if (defData->callbacks->BlockageCbk) {
               if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
                 defData->defError(6542, "The defined BLOCKAGES COMPONENT statement has either COMPONENT, SLOTS, FILLS, PUSHDOWN or EXCEPTPGNET defined.\nOnly one of these statements is allowed per LAYER. Updated the DEF file to define a valid BLOCKAGES COMPONENT statement per layer.");
                 CHKERR();
               }
             }
           } else {
             if (defData->callbacks->BlockageCbk){
               defData->Blockage.setExceptpgnet();
             }
             if (defData->VersionNum < 5.8){
               defData->hasBlkLayerComp = 1;
             }
           }
        }
      }
    break;

  case 864:

/* Line 1806 of yacc.c  */
#line 4648 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 865:

/* Line 1806 of yacc.c  */
#line 4649 "def.y"
    {
        if (defData->hasBlkPlaceComp) {
          if (defData->callbacks->BlockageCbk) {
            if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
              defData->defError(6543, "The defined BLOCKAGES PLACEMENT statement has either COMPONENT, PUSHDOWN, SOFT or PARTIAL defined.\nOnly one of these statements is allowed per LAYER. Updated the DEF file to define a valid BLOCKAGES PLACEMENT statement.");
              CHKERR();
            }
          }
        } else {
          if (defData->callbacks->BlockageCbk){
            defData->Blockage.setComponent((yyvsp[(4) - (4)].string));
          }
          if (defData->VersionNum < 5.8) {
            defData->hasBlkPlaceComp = 1;
          }
        }
      }
    break;

  case 866:

/* Line 1806 of yacc.c  */
#line 4667 "def.y"
    {
        if (defData->hasBlkPlaceComp) {
          if (defData->callbacks->BlockageCbk) {
            if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
              defData->defError(6543, "The defined BLOCKAGES PLACEMENT statement has either COMPONENT, PUSHDOWN, SOFT or PARTIAL defined.\nOnly one of these statements is allowed per LAYER. Updated the DEF file to define a valid BLOCKAGES PLACEMENT statement.");
              CHKERR();
            }
          }
        } else {
          if (defData->callbacks->BlockageCbk){
            defData->Blockage.setPushdown();
          }
          if (defData->VersionNum < 5.8) {
            defData->hasBlkPlaceComp = 1;
          }
        }
      }
    break;

  case 867:

/* Line 1806 of yacc.c  */
#line 4685 "def.y"
    {
        if (defData->VersionNum < 5.7) {
           if (defData->callbacks->BlockageCbk) {
             if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
               defData->defMsg = (char*)malloc(10000);
               sprintf (defData->defMsg,
                 "The PLACEMENT SOFT is available in version 5.7 or later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
               defData->defError(6547, defData->defMsg);
               free(defData->defMsg);
               CHKERR();
             }
           }
        } else {
           if (defData->hasBlkPlaceComp || defData->hasBlkPlaceTypeComp) {
             if (defData->callbacks->BlockageCbk) {
               if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
                 defData->defError(6543, "The defined BLOCKAGES PLACEMENT statement has either COMPONENT, PUSHDOWN, SOFT or PARTIAL defined.\nOnly one of these statements is allowed per LAYER. Updated the DEF file to define a valid BLOCKAGES PLACEMENT statement.");
                 CHKERR();
               }
             }
           } else {
             if (defData->callbacks->BlockageCbk){
               defData->Blockage.setSoft();
             }
             if (defData->VersionNum < 5.8) {
               defData->hasBlkPlaceComp = 1;
             }
             if (defData->VersionNum == 5.8) {
               defData->hasBlkPlaceTypeComp = 1;
             }
           }
        }
      }
    break;

  case 868:

/* Line 1806 of yacc.c  */
#line 4719 "def.y"
    {
        if (defData->VersionNum < 5.7) {
           if (defData->callbacks->BlockageCbk) {
             if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
                defData->defMsg = (char*)malloc(10000);
                sprintf (defData->defMsg,
                  "The PARTIAL is available in version 5.7 or later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
                defData->defError(6548, defData->defMsg);
                free(defData->defMsg);
                CHKERR();
             }
           }
        } else {
           if (defData->hasBlkPlaceComp || defData->hasBlkPlaceTypeComp) {
             if (defData->callbacks->BlockageCbk) {
               if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
                 defData->defError(6543, "The defined BLOCKAGES PLACEMENT statement has either COMPONENT, PUSHDOWN, SOFT or PARTIAL defined.\nOnly one of these statements is allowed per LAYER. Updated the DEF file to define a valid BLOCKAGES PLACEMENT statement.");
                 CHKERR();
               }
             }
           } else {
             if (defData->callbacks->BlockageCbk){
               defData->Blockage.setPartial((yyvsp[(3) - (3)].dval));
             } 
             if (defData->VersionNum < 5.8) {
               defData->hasBlkPlaceComp = 1;
             }
             if (defData->VersionNum == 5.8) {
               defData->hasBlkPlaceTypeComp = 1;
             }
           }
         }
      }
    break;

  case 871:

/* Line 1806 of yacc.c  */
#line 4759 "def.y"
    {
        if (defData->callbacks->BlockageCbk)
          defData->Blockage.addRect((yyvsp[(2) - (3)].pt).x, (yyvsp[(2) - (3)].pt).y, (yyvsp[(3) - (3)].pt).x, (yyvsp[(3) - (3)].pt).y);
      }
    break;

  case 872:

/* Line 1806 of yacc.c  */
#line 4764 "def.y"
    {
        if (defData->callbacks->BlockageCbk) {
            defData->Geometries.Reset();
        }
      }
    break;

  case 873:

/* Line 1806 of yacc.c  */
#line 4770 "def.y"
    {
        if (defData->callbacks->BlockageCbk) {
          if (defData->VersionNum >= 5.6) {  // only 5.6 and beyond
            if (defData->Blockage.hasLayer()) {  // only in layer
              if (defData->callbacks->BlockageCbk)
                defData->Blockage.addPolygon(&defData->Geometries);
            } else {
              if (defData->callbacks->BlockageCbk) {
                if (defData->blockageWarnings++ < defData->settings->BlockageWarnings) {
                  defData->defError(6544, "A POLYGON statement is defined in the BLOCKAGE statement,\nbut it is not defined in the BLOCKAGE LAYER statement.\nUpdate your DEF file to either remove the POLYGON statement from the BLOCKAGE statement or\ndefine the POLYGON statement in a BLOCKAGE LAYER statement.");
                  CHKERR();
                }
              }
            }
          }
        }
      }
    break;

  case 875:

/* Line 1806 of yacc.c  */
#line 4792 "def.y"
    { if (defData->callbacks->SlotStartCbk)
          CALLBACK(defData->callbacks->SlotStartCbk, defrSlotStartCbkType, ROUND((yyvsp[(2) - (3)].dval))); }
    break;

  case 876:

/* Line 1806 of yacc.c  */
#line 4796 "def.y"
    { if (defData->callbacks->SlotEndCbk)
          CALLBACK(defData->callbacks->SlotEndCbk, defrSlotEndCbkType, 0); }
    break;

  case 879:

/* Line 1806 of yacc.c  */
#line 4804 "def.y"
    {
        if (defData->callbacks->SlotCbk) {
          CALLBACK(defData->callbacks->SlotCbk, defrSlotCbkType, &defData->Slot);
          defData->Slot.clear();
        }
      }
    break;

  case 880:

/* Line 1806 of yacc.c  */
#line 4811 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 881:

/* Line 1806 of yacc.c  */
#line 4812 "def.y"
    {
        if (defData->callbacks->SlotCbk) {
          defData->Slot.setLayer((yyvsp[(4) - (4)].string));
          defData->Slot.clearPoly();     // free poly, if any
        }
      }
    break;

  case 885:

/* Line 1806 of yacc.c  */
#line 4824 "def.y"
    {
        if (defData->callbacks->SlotCbk)
          defData->Slot.addRect((yyvsp[(2) - (3)].pt).x, (yyvsp[(2) - (3)].pt).y, (yyvsp[(3) - (3)].pt).x, (yyvsp[(3) - (3)].pt).y);
      }
    break;

  case 886:

/* Line 1806 of yacc.c  */
#line 4829 "def.y"
    {
          defData->Geometries.Reset();
      }
    break;

  case 887:

/* Line 1806 of yacc.c  */
#line 4833 "def.y"
    {
        if (defData->VersionNum >= 5.6) {  // only 5.6 and beyond
          if (defData->callbacks->SlotCbk)
            defData->Slot.addPolygon(&defData->Geometries);
        }
      }
    break;

  case 889:

/* Line 1806 of yacc.c  */
#line 4844 "def.y"
    { if (defData->callbacks->FillStartCbk)
          CALLBACK(defData->callbacks->FillStartCbk, defrFillStartCbkType, ROUND((yyvsp[(2) - (3)].dval))); }
    break;

  case 890:

/* Line 1806 of yacc.c  */
#line 4848 "def.y"
    { if (defData->callbacks->FillEndCbk)
          CALLBACK(defData->callbacks->FillEndCbk, defrFillEndCbkType, 0); }
    break;

  case 893:

/* Line 1806 of yacc.c  */
#line 4856 "def.y"
    {
        if (defData->callbacks->FillCbk) {
          CALLBACK(defData->callbacks->FillCbk, defrFillCbkType, &defData->Fill);
          defData->Fill.clear();
        }
      }
    break;

  case 894:

/* Line 1806 of yacc.c  */
#line 4862 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 895:

/* Line 1806 of yacc.c  */
#line 4863 "def.y"
    {
        if (defData->callbacks->FillCbk) {
          defData->Fill.setVia((yyvsp[(4) - (4)].string));
          defData->Fill.clearPts();
          defData->Geometries.Reset();
        }
      }
    break;

  case 897:

/* Line 1806 of yacc.c  */
#line 4872 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 898:

/* Line 1806 of yacc.c  */
#line 4873 "def.y"
    {
        if (defData->callbacks->FillCbk) {
          defData->Fill.setLayer((yyvsp[(4) - (4)].string));
          defData->Fill.clearPoly();    // free poly, if any
        }
      }
    break;

  case 902:

/* Line 1806 of yacc.c  */
#line 4886 "def.y"
    {
        if (defData->callbacks->FillCbk)
          defData->Fill.addRect((yyvsp[(2) - (3)].pt).x, (yyvsp[(2) - (3)].pt).y, (yyvsp[(3) - (3)].pt).x, (yyvsp[(3) - (3)].pt).y);
      }
    break;

  case 903:

/* Line 1806 of yacc.c  */
#line 4891 "def.y"
    {
        defData->Geometries.Reset();
      }
    break;

  case 904:

/* Line 1806 of yacc.c  */
#line 4895 "def.y"
    {
        if (defData->VersionNum >= 5.6) {  // only 5.6 and beyond
          if (defData->callbacks->FillCbk)
            defData->Fill.addPolygon(&defData->Geometries);
        } else {
            defData->defMsg = (char*)malloc(10000);
            sprintf (defData->defMsg,
              "POLYGON statement in FILLS LAYER is a version 5.6 and later syntax.\nYour def file is defined with version %g.", defData->VersionNum);
            defData->defError(6564, defData->defMsg);
            free(defData->defMsg);
            CHKERR();
        }
      }
    break;

  case 909:

/* Line 1806 of yacc.c  */
#line 4919 "def.y"
    {
        if (defData->VersionNum < 5.7) {
           if (defData->callbacks->FillCbk) {
             if (defData->fillWarnings++ < defData->settings->FillWarnings) {
               defData->defMsg = (char*)malloc(10000);
               sprintf (defData->defMsg,
                 "The LAYER OPC is available in version 5.7 or later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
               defData->defError(6553, defData->defMsg);
               free(defData->defMsg);
               CHKERR();
             }
           }
        } else {
           if (defData->callbacks->FillCbk)
             defData->Fill.setLayerOpc();
        }
      }
    break;

  case 910:

/* Line 1806 of yacc.c  */
#line 4938 "def.y"
    {
        if (defData->callbacks->FillCbk) {
          defData->Fill.addPts(&defData->Geometries);
          CALLBACK(defData->callbacks->FillCbk, defrFillCbkType, &defData->Fill);
          defData->Fill.clear();
        }
    }
    break;

  case 915:

/* Line 1806 of yacc.c  */
#line 4957 "def.y"
    {
        if (defData->VersionNum < 5.7) {
           if (defData->callbacks->FillCbk) {
             if (defData->fillWarnings++ < defData->settings->FillWarnings) {
               defData->defMsg = (char*)malloc(10000);
               sprintf (defData->defMsg,
                 "The VIA OPC is available in version 5.7 or later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
               defData->defError(6554, defData->defMsg);
               free(defData->defMsg);
               CHKERR();
             }
           }
        } else {
           if (defData->callbacks->FillCbk)
             defData->Fill.setViaOpc();
        }
      }
    break;

  case 916:

/* Line 1806 of yacc.c  */
#line 4977 "def.y"
    { 
        if (defData->validateMaskInput((int)(yyvsp[(3) - (3)].dval), defData->fillWarnings, defData->settings->FillWarnings)) {
             if (defData->callbacks->FillCbk) {
                defData->Fill.setMask((int)(yyvsp[(3) - (3)].dval));
             }
        }
      }
    break;

  case 917:

/* Line 1806 of yacc.c  */
#line 4987 "def.y"
    { 
        if (defData->validateMaskInput((int)(yyvsp[(3) - (3)].dval), defData->fillWarnings, defData->settings->FillWarnings)) {
             if (defData->callbacks->FillCbk) {
                defData->Fill.setMask((int)(yyvsp[(3) - (3)].dval));
             }
        }
      }
    break;

  case 919:

/* Line 1806 of yacc.c  */
#line 5000 "def.y"
    { 
        if (defData->VersionNum < 5.6) {
          if (defData->callbacks->NonDefaultStartCbk) {
            if (defData->nonDefaultWarnings++ < defData->settings->NonDefaultWarnings) {
              defData->defMsg = (char*)malloc(1000);
              sprintf (defData->defMsg,
                 "The NONDEFAULTRULE statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g.", defData->VersionNum);
              defData->defError(6545, defData->defMsg);
              free(defData->defMsg);
              CHKERR();
            }
          }
        } else if (defData->callbacks->NonDefaultStartCbk)
          CALLBACK(defData->callbacks->NonDefaultStartCbk, defrNonDefaultStartCbkType,
                   ROUND((yyvsp[(2) - (3)].dval)));
      }
    break;

  case 920:

/* Line 1806 of yacc.c  */
#line 5018 "def.y"
    { if (defData->callbacks->NonDefaultEndCbk)
          CALLBACK(defData->callbacks->NonDefaultEndCbk, defrNonDefaultEndCbkType, 0); }
    break;

  case 923:

/* Line 1806 of yacc.c  */
#line 5025 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 924:

/* Line 1806 of yacc.c  */
#line 5026 "def.y"
    {
        if (defData->callbacks->NonDefaultCbk) {
          defData->NonDefault.clear(); 
          defData->NonDefault.setName((yyvsp[(3) - (3)].string));
        }
      }
    break;

  case 925:

/* Line 1806 of yacc.c  */
#line 5033 "def.y"
    { if (defData->callbacks->NonDefaultCbk)
          CALLBACK(defData->callbacks->NonDefaultCbk, defrNonDefaultCbkType, &defData->NonDefault); }
    break;

  case 928:

/* Line 1806 of yacc.c  */
#line 5041 "def.y"
    {
        if (defData->callbacks->NonDefaultCbk)
          defData->NonDefault.setHardspacing();
      }
    break;

  case 929:

/* Line 1806 of yacc.c  */
#line 5045 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 930:

/* Line 1806 of yacc.c  */
#line 5047 "def.y"
    {
        if (defData->callbacks->NonDefaultCbk) {
          defData->NonDefault.addLayer((yyvsp[(4) - (6)].string));
          defData->NonDefault.addWidth((yyvsp[(6) - (6)].dval));
        }
      }
    break;

  case 932:

/* Line 1806 of yacc.c  */
#line 5054 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 933:

/* Line 1806 of yacc.c  */
#line 5055 "def.y"
    {
        if (defData->callbacks->NonDefaultCbk) {
          defData->NonDefault.addVia((yyvsp[(4) - (4)].string));
        }
      }
    break;

  case 934:

/* Line 1806 of yacc.c  */
#line 5060 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 935:

/* Line 1806 of yacc.c  */
#line 5061 "def.y"
    {
        if (defData->callbacks->NonDefaultCbk) {
          defData->NonDefault.addViaRule((yyvsp[(4) - (4)].string));
        }
      }
    break;

  case 936:

/* Line 1806 of yacc.c  */
#line 5066 "def.y"
    { defData->dumb_mode = 1; defData->no_num = 1; }
    break;

  case 937:

/* Line 1806 of yacc.c  */
#line 5067 "def.y"
    {
        if (defData->callbacks->NonDefaultCbk) {
          defData->NonDefault.addMinCuts((yyvsp[(4) - (5)].string), (int)(yyvsp[(5) - (5)].dval));
        }
      }
    break;

  case 941:

/* Line 1806 of yacc.c  */
#line 5080 "def.y"
    {
        if (defData->callbacks->NonDefaultCbk) {
          defData->NonDefault.addDiagWidth((yyvsp[(2) - (2)].dval));
        }
      }
    break;

  case 942:

/* Line 1806 of yacc.c  */
#line 5086 "def.y"
    {
        if (defData->callbacks->NonDefaultCbk) {
          defData->NonDefault.addSpacing((yyvsp[(2) - (2)].dval));
        }
      }
    break;

  case 943:

/* Line 1806 of yacc.c  */
#line 5092 "def.y"
    {
        if (defData->callbacks->NonDefaultCbk) {
          defData->NonDefault.addWireExt((yyvsp[(2) - (2)].dval));
        }
      }
    break;

  case 944:

/* Line 1806 of yacc.c  */
#line 5099 "def.y"
    { defData->dumb_mode = DEF_MAX_INT;  }
    break;

  case 945:

/* Line 1806 of yacc.c  */
#line 5101 "def.y"
    { defData->dumb_mode = 0; }
    break;

  case 948:

/* Line 1806 of yacc.c  */
#line 5108 "def.y"
    {
        if (defData->callbacks->NonDefaultCbk) {
          char propTp;
          char* str = defData->ringCopy("                       ");
          propTp = defData->session->NDefProp.propType((yyvsp[(1) - (2)].string));
          CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "NONDEFAULTRULE");
          sprintf(str, "%g", (yyvsp[(2) - (2)].dval));
          defData->NonDefault.addNumProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].dval), str, propTp);
        }
      }
    break;

  case 949:

/* Line 1806 of yacc.c  */
#line 5119 "def.y"
    {
        if (defData->callbacks->NonDefaultCbk) {
          char propTp;
          propTp = defData->session->NDefProp.propType((yyvsp[(1) - (2)].string));
          CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "NONDEFAULTRULE");
          defData->NonDefault.addProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
        }
      }
    break;

  case 950:

/* Line 1806 of yacc.c  */
#line 5128 "def.y"
    {
        if (defData->callbacks->NonDefaultCbk) {
          char propTp;
          propTp = defData->session->NDefProp.propType((yyvsp[(1) - (2)].string));
          CHKPROPTYPE(propTp, (yyvsp[(1) - (2)].string), "NONDEFAULTRULE");
          defData->NonDefault.addProperty((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string), propTp);
        }
      }
    break;

  case 952:

/* Line 1806 of yacc.c  */
#line 5141 "def.y"
    {
        if (defData->VersionNum < 5.6) {
          if (defData->callbacks->StylesStartCbk) {
            if (defData->stylesWarnings++ < defData->settings->StylesWarnings) {
              defData->defMsg = (char*)malloc(1000);
              sprintf (defData->defMsg,
                 "The STYLES statement is available in version 5.6 and later.\nHowever, your DEF file is defined with version %g", defData->VersionNum);
              defData->defError(6546, defData->defMsg);
              free(defData->defMsg);
              CHKERR();
            }
          }
        } else if (defData->callbacks->StylesStartCbk)
          CALLBACK(defData->callbacks->StylesStartCbk, defrStylesStartCbkType, ROUND((yyvsp[(2) - (3)].dval)));
      }
    break;

  case 953:

/* Line 1806 of yacc.c  */
#line 5158 "def.y"
    { if (defData->callbacks->StylesEndCbk)
          CALLBACK(defData->callbacks->StylesEndCbk, defrStylesEndCbkType, 0); }
    break;

  case 956:

/* Line 1806 of yacc.c  */
#line 5166 "def.y"
    {
        if (defData->callbacks->StylesCbk) defData->Styles.setStyle((int)(yyvsp[(3) - (3)].dval));
        defData->Geometries.Reset();
      }
    break;

  case 957:

/* Line 1806 of yacc.c  */
#line 5171 "def.y"
    {
        if (defData->VersionNum >= 5.6) {  // only 5.6 and beyond will call the callback
          if (defData->callbacks->StylesCbk) {
            defData->Styles.setPolygon(&defData->Geometries);
            CALLBACK(defData->callbacks->StylesCbk, defrStylesCbkType, &defData->Styles);
          }
        }
      }
    break;



/* Line 1806 of yacc.c  */
#line 11409 "def.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (defData, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (defData, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, defData);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, defData);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (defData, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, defData);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, defData);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 5181 "def.y"


END_LEFDEF_PARSER_NAMESPACE

