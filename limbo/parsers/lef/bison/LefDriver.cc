// $Id: driver.cc 39 2008-08-03 10:07:15Z tb $
/** \file driver.cc Implementation of the example::Driver class. */

#include "LefDriver.h"
#include "LefScanner.h"
#include <cctype>

namespace LefParser {

Driver::Driver(LefDataBase& db)
    : trace_scanning(false),
      trace_parsing(false),
      m_db(db)
{
	lefNamesCaseSensitive = TRUE;  // always true in 5.6
	lefReaderCaseSensitive = FALSE;  // default to 0

	lefrShiftCase = 0;     // if user wants to shift to all uppercase

	lefrRelaxMode = FALSE;    // relax mode?
	///////////////////////////////////s
	//
	//   copied from Global variables
	//
	/////////////////////////////////////

	lefrUserData = 0;
	lefrFileName = 0;
	lefrRegisterUnused = 0;
	lefrFile = 0;
	lefrAntennaPWLPtr = 0;
//	lefrArray;
//	lefrCorrectionTable;
//	lefrDensity;
	lefrGcellPatternPtr = 0;
	lefrGeometriesPtr = 0;
//	lefrIRDrop;
//	lefrLayer;
//	lefrMacro;
//	lefrMaxStackVia;  // 5.5
//	lefrMinFeature;
//	lefrNoiseMargin;
//	lefrNoiseTable;
//	lefrNonDefault;
//	lefrObstruction;
//	lefrPin;
//	lefrProp;
//	lefrSite;
	lefrSitePatternPtr = 0;
//	lefrSpacing;
//	lefrTiming;
	lefrTrackPatternPtr = 0;
//	lefrUnits;
//	lefrUseMinSpacing;
//	lefrVia;
//	lefrViaRule;
	lefrIsReset = 0;
	lefrDoGcell = 0;
	lefrDoGeometries = 0;
	lefrDoTrack = 0;
	lefrDoSite = 0;
	lefrHasLayer = 0;    // 5.5 this & lefrHasMaxVS is to keep track that
	lefrHasMaxVS = 0;    // MAXVIASTACK has to be after all layers
//	lefrHasSpacingTbl;   // keep track of spacing table in a layer
//	lefrHasSpacing;      // keep track of spacing in a layer
	userHasSetVer = 0;   // if user has set default version value
	doneLib = 1;         // keep track if the library is done parsing
	// 5.6 END LIBRARY is optional.
	ge56almostDone = 0;  // have reached the EXTENSION SECTION
	ge56done = 0;        // a 5.6 and it has END LIBRARY statement

	// The following global variables are for storing the propertydefination
	// types.  Only real & integer need to store since the parser can
	// distinguish string and quote string
//	lefrLibProp;
//	lefrCompProp;
//	lefrPinProp;
//	lefrMacroProp;
//	lefrViaProp;
//	lefrViaRuleProp;
//	lefrLayerProp;
//	lefrNondefProp;

	// The following global variables are used in lef.y
	use5_3 = 0;          /* keep track if there is any 5.3 on 5.4 file */
	use5_4 = 0;          /* keep track if only 5.4 is allowed */
	hasVer = 0;          /* keep track if version is in file */
	hasNameCase = 0;     /* keep track if namescasesensitive is in file */
	hasBusBit = 0;       /* keep track if bustbitchars is in file */
	hasDivChar = 0;      /* keep track if dividerchar is in file */
	aOxide = 0;          /* keep track for oxide */
	versionNum = m_db.current_version();

	////////////////////////////////////
	//
	//  Flags to control number of warnings to print out, max will be 999
	//  I don't know if it is useful, but they are used in .yy 
	//
	////////////////////////////////////

	lefrAntennaInoutWarnings = 999;
	lefrAntennaInputWarnings = 999;
	lefrAntennaOutputWarnings = 999;
	lefrArrayWarnings = 999;
	lefrCaseSensitiveWarnings = 999;
	lefrCorrectionTableWarnings = 999;
	lefrDielectricWarnings = 999;
	lefrEdgeRateThreshold1Warnings = 999;
	lefrEdgeRateThreshold2Warnings = 999;
	lefrEdgeRateScaleFactorWarnings = 999;
	lefrInoutAntennaWarnings = 999;
	lefrInputAntennaWarnings = 999;
	lefrIRDropWarnings = 999;
	lefrLayerWarnings = 999;
	lefrMacroWarnings = 999;
	lefrMaxStackViaWarnings = 999;
	lefrMinFeatureWarnings = 999;
	lefrNoiseMarginWarnings = 999;
	lefrNoiseTableWarnings = 999;
	lefrNonDefaultWarnings = 999;
	lefrNoWireExtensionWarnings = 999;
	lefrOutputAntennaWarnings = 999;
	lefrPinWarnings = 999;
	lefrSiteWarnings = 999;
	lefrSpacingWarnings = 999;
	lefrTimingWarnings = 999;
	lefrUnitsWarnings = 999;
	lefrUseMinSpacingWarnings = 999;
	lefrViaRuleWarnings = 999;
	lefrViaWarnings = 999;

	lefNdRule = 0;// for communicating with parser
	lefDefIf = FALSE;
	inDefine = 0;
}

bool Driver::parse_stream(std::istream& in, const std::string& sname)
{
    streamname = sname;

    Scanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->lexer = &scanner;

    Parser parser(*this);
    parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}

bool Driver::parse_file(const std::string &filename)
{
    std::ifstream in(filename.c_str());
    if (!in.good()) return false;
    return parse_stream(in, filename);
}

bool Driver::parse_string(const std::string &input, const std::string& sname)
{
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void Driver::error(const class location& l,
		   const std::string& m)
{
    std::cerr << l << ": " << m << std::endl;
}

void Driver::error(const std::string& m)
{
    std::cerr << m << std::endl;
}

/***************** custom callbacks here ******************/

void Driver::resetVars()
{
     hasVer = 0;
     hasNameCase = 0;
     hasBusBit = 0;
     hasDivChar = 0;
     hasManufactur = 0;
     hasMinfeature = 0;
     hasSite = 0;
     antennaInoutWarnings = 0;
     antennaInputWarnings = 0;
     antennaOutputWarnings = 0;
     arrayWarnings = 0;
     caseSensitiveWarnings = 0;
     correctionTableWarnings = 0;
     dielectricWarnings = 0;
     edgeRateThreshold1Warnings = 0;
     edgeRateThreshold2Warnings = 0;
     edgeRateScaleFactorWarnings = 0;
     inoutAntennaWarnings = 0;
     inputAntennaWarnings = 0;
     iRDropWarnings = 0;
     layerWarnings = 0;
     macroWarnings = 0;
     maxStackViaWarnings = 0;
     minFeatureWarnings = 0;
     noiseMarginWarnings = 0;
     noiseTableWarnings = 0;
     nonDefaultWarnings = 0;
     noWireExtensionWarnings = 0;
     outputAntennaWarnings = 0;
     siteWarnings = 0;
     spacingWarnings = 0;
     timingWarnings = 0;
     unitsWarnings = 0;
     useMinSpacingWarnings = 0;
     viaRuleWarnings = 0;
     viaWarnings = 0;
     return;
}
void Driver::lefSetNonDefault(const char* nd_name)
{
   ndName = nd_name;
}
void Driver::lefUnsetNonDefault() 
{
   lefNdRule = 0;
}
void Driver::lefAddStringDefine(string const&token, string const& val) 
{
	// rewrite it in c++ style 
	// maybe buggy 
	if (!lefNamesCaseSensitive)
	{
		string token_lc = token;
		for (string::iterator it = token_lc.begin(); it != token_lc.end(); ++it)
			(*it) = tolower(*it);
		defines_set.insert(std::make_pair(token_lc, val));
	}
	else 
	{
		defines_set.insert(std::make_pair(token, val));
	}
	lefDefIf = FALSE;
	inDefine = 0;
}
void Driver::lefAddBooleanDefine(string const& token, int val) 
{
	// rewrite it in c++ style 
	// maybe buggy 
	if (!lefNamesCaseSensitive)
	{
		string token_lc = token;
		for (string::iterator it = token_lc.begin(); it != token_lc.end(); ++it)
			(*it) = tolower(*it);
		defineb_set.insert(std::make_pair(token_lc, val));
	}
	else 
	{
		defineb_set.insert(std::make_pair(token, val));
	}
}
void Driver::lefAddNumDefine(string const& token, double val) 
{
	// rewrite it in c++ style 
	// maybe buggy 
	if (!lefNamesCaseSensitive)
	{
		string token_lc = token;
		for (string::iterator it = token_lc.begin(); it != token_lc.end(); ++it)
			(*it) = tolower(*it);
		definen_set.insert(std::make_pair(token_lc, val));
	}
	else 
	{
		definen_set.insert(std::make_pair(token, val));
	}
}
/* Store the message data in a stack */
void Driver::lefAddStringMessage(string const& token, string const& val) 
{
	// rewrite it in c++ style 
	// maybe buggy 
	if (!lefNamesCaseSensitive)
	{
		string token_lc = token;
		for (string::iterator it = token_lc.begin(); it != token_lc.end(); ++it)
			(*it) = tolower(*it);
		message_set.insert(std::make_pair(token_lc, val));
	}
	else 
	{
		message_set.insert(std::make_pair(token, val));
	}
}

/***************** static variables ******************/
int Driver::ignoreVersion = 0; // ignore checking version number
char Driver::temp_name[258];
std::string Driver::layerName;
std::string Driver::viaName;
std::string Driver::viaRuleName;
std::string Driver::nonDefaultRuleName;
std::string Driver::siteName;
std::string Driver::arrayName;
std::string Driver::macroName;
std::string Driver::pinName;

int Driver::siteDef;
int Driver::symDef;
int Driver::sizeDef;
int Driver::pinDef;
int Driver::obsDef;
int Driver::origDef;
int Driver::useLenThr;
int Driver::layerCut;
int Driver::layerMastOver;
int Driver::layerRout;
int Driver::layerDir;
lefiAntennaEnum Driver::antennaType = lefiAntennaAR;  /* 5.4 - antenna type */
int Driver::arrayCutsVal;       /* keep track the arraycuts value */
int Driver::arrayCutsWar;       /* keep track if warning has already printed */
int Driver::viaRuleLayer;       /* keep track number of layer in a viarule */
int Driver::viaLayer;           /* keep track number of layer in a via */
std::string Driver::ndName;
int Driver::ndLayer;            /* keep track number of layer in a nondefault */
int Driver::numVia;             /* keep track number of via */
int Driver::viaRuleHasDir;      /* viarule layer has direction construct */
int Driver::viaRuleHasEnc;      /* viarule layer has enclosure construct */
int Driver::ndRule = 0;         /* keep track if inside nondefaultrule */
int Driver::ndLayerWidth;       /* keep track if width is set at ndLayer */
int Driver::ndLayerSpace;       /* keep track if spacing is set at ndLayer */
int Driver::isGenerate;         /* keep track if viarule has generate */
int Driver::hasType;            /* keep track of type in layer */
int Driver::hasPitch;           /* keep track of pitch in layer */
int Driver::hasWidth;           /* keep track of width in layer */
int Driver::hasDirection;       /* keep track of direction in layer */
int Driver::hasParallel;        /* keep track of parallelrunlength */
int Driver::hasInfluence;       /* keep track of influence */
int Driver::hasTwoWidths;       /* keep track of twoWidths */
int Driver::hasLayerMincut;     /* keep track of layer minimumcut */
int Driver::hasManufactur = 0;  /* keep track of manufacture is after unit */
int Driver::hasMinfeature = 0;  /* keep track of minfeature is after unit */
int Driver::hasPRP;             /* keep track if path, rect or poly is def */
int Driver::needGeometry;       /* keep track if path/rect/poly is defined */
int Driver::hasViaRule_layer = 0; /* keep track at least viarule or layer */
int Driver::hasSamenet;         /* keep track if samenet is defined in spacing */
int Driver::hasSite = 0;        /* keep track if SITE has defined for pre 5.6 */
int Driver::hasSiteClass = 0;   /* keep track if SITE has CLASS */
int Driver::hasSiteSize = 0;    /* keep track if SITE has SIZE */
int Driver::hasSpCenter = 0;    /* keep track if LAYER SPACING has CENTER */
int Driver::hasSpSamenet = 0;   /* keep track if LAYER SPACING has SAMENET */
int Driver::hasSpParallel = 0;  /* keep track if LAYER SPACING has PARALLEL */
int Driver::hasSpLayer = 0;     /* keep track if LAYER SPACING has LAYER */
int Driver::hasGeoLayer = 0;    /* keep track if Geometries has LAYER */


// the following variables to keep track the number of warnings printed.
int Driver::antennaInoutWarnings = 0;
int Driver::antennaInputWarnings = 0;
int Driver::antennaOutputWarnings = 0;
int Driver::arrayWarnings = 0;
int Driver::caseSensitiveWarnings = 0;
int Driver::correctionTableWarnings = 0;
int Driver::dielectricWarnings = 0;
int Driver::edgeRateThreshold1Warnings = 0;
int Driver::edgeRateThreshold2Warnings = 0;
int Driver::edgeRateScaleFactorWarnings = 0;
int Driver::inoutAntennaWarnings = 0;
int Driver::inputAntennaWarnings = 0;
int Driver::iRDropWarnings = 0;
int Driver::layerWarnings = 0;
int Driver::macroWarnings = 0;
int Driver::maxStackViaWarnings = 0;
int Driver::minFeatureWarnings = 0;
int Driver::noiseMarginWarnings = 0;
int Driver::noiseTableWarnings = 0;
int Driver::nonDefaultWarnings = 0;
int Driver::noWireExtensionWarnings = 0;
int Driver::outputAntennaWarnings = 0;
int Driver::pinWarnings = 0;
int Driver::siteWarnings = 0;
int Driver::spacingWarnings = 0;
int Driver::timingWarnings = 0;
int Driver::unitsWarnings = 0;
int Driver::useMinSpacingWarnings = 0;
int Driver::viaRuleWarnings = 0;
int Driver::viaWarnings = 0;
double Driver::layerCutSpacing = 0;

bool read(LefDataBase& db, const string& lefFile)
{
	Driver driver (db);
	//driver.trace_scanning = true;
	//driver.trace_parsing = true;

	return driver.parse_file(lefFile);
}

} // namespace example
