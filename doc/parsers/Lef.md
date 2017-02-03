Limbo.Parsers.LefParser {#Parsers_LefParser}
---------

[TOC]

# Introduction {#Parsers_LefParser_Introduction}

[LEF](https://en.wikipedia.org/wiki/Library_Exchange_Format) together with [DEF](https://en.wikipedia.org/wiki/Design_Exchange_Format) is a common file format in VLSI physical design. 
Generally LEF/DEF formats are quit complicated due to the complex cases in chip design. 
This parser is adjusted from the open source LEF parser released by [Cadence Design Systems](https://www.cadence.com) with C++ wrappers. 
Users have to follow the [LICENSE](@ref Parsers_LefParser_License) agreement from the original release. 
It is tested under various academic benchmarks for VLSI placement. 

# Examples {#Parsers_LefParser_Examples}

## Flex/Bison Parser {#Parsers_LefParser_Flex_Bison}

See documented version: [test/parsers/lef/test_bison.cpp](@ref lef/test_bison.cpp)
\include test/parsers/lef/test_bison.cpp

Compiling and running commands (assuming LIMBO_DIR is exported as the environment variable to the path where limbo library is installed)
~~~~~~~~~~~~~~~~
g++ -o test_bison test_bison.cpp -I $LIMBO_DIR/include -L $LIMBO_DIR/lib -llefparser
./test_bison benchmarks/cells.lef
~~~~~~~~~~~~~~~~

## All Examples {#Parsers_LefParser_Examples_All}

- [test/parsers/lef/test_bison.cpp](@ref lef/test_bison.cpp)


# References {#Parsers_LefParser_References}

- [limbo/parsers/lef/bison/LefDataBase.h](@ref LefDataBase.h)
- [limbo/parsers/lef/bison/LefDriver.h](@ref LefDriver.h)
- [/limbo/parsers/lef/bison/lefiArray.hpp](@ref lefiArray.hpp)      
- [/limbo/parsers/lef/bison/lefiKRDefs.hpp](@ref lefiKRDefs.hpp)  
- [/limbo/parsers/lef/bison/lefiNonDefault.hpp](@ref lefiNonDefault.hpp)  
- [/limbo/parsers/lef/bison/lefiUser.hpp](@ref lefiUser.hpp)
- [/limbo/parsers/lef/bison/lefiCrossTalk.hpp](@ref lefiCrossTalk.hpp)  
- [/limbo/parsers/lef/bison/lefiLayer.hpp](@ref lefiLayer.hpp)   
- [/limbo/parsers/lef/bison/lefiProp.hpp](@ref lefiProp.hpp)        
- [/limbo/parsers/lef/bison/lefiUtil.hpp](@ref lefiUtil.hpp)
- [/limbo/parsers/lef/bison/lefiDebug.hpp](@ref lefiDebug.hpp)      
- [/limbo/parsers/lef/bison/lefiMacro.hpp](@ref lefiMacro.hpp)   
- [/limbo/parsers/lef/bison/lefiPropType.hpp](@ref lefiPropType.hpp)    
- [/limbo/parsers/lef/bison/lefiVia.hpp](@ref lefiVia.hpp)
- [/limbo/parsers/lef/bison/lefiDefs.hpp](@ref lefiDefs.hpp)       
- [/limbo/parsers/lef/bison/lefiMisc.hpp](@ref lefiMisc.hpp)    
- [/limbo/parsers/lef/bison/lefiUnits.hpp](@ref lefiUnits.hpp)       
- [/limbo/parsers/lef/bison/lefiViaRule.hpp](@ref lefiViaRule.hpp)

# License {#Parsers_LefParser_License}

\include limbo/parsers/lef/bison/LICENSE.TXT
