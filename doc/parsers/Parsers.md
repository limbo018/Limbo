Limbo.Parsers {#Parsers}
---------

## Components 
| Components                                              | Languages & Libraries           | Description                                              |
| ------------------------------------------------------- | ------------------------------- | -------------------------------------------------------- |
| [Bookshelf Parser](@ref Parsers_BookshelfParser)        | Flex/Bison                      | Placement file format from UCSD                          |
| [DEF Parser](@ref Parsers_DefParser)                    | Flex/Bison                      |                                                          |
|                                                         | Boost.Spirit                    | Deprecated due to efficiency                             |
| [Ebeam Parser](@ref Parsers_EbeamParser)                | Flex/Bison                      |                                                          |
|                                                         | Boost.Spirit                    | Deprecated due to efficiency                             |
| [LEF Parser](@ref Parsers_LefParser)                    | Flex/Bison                      |                                                          |
|                                                         | Boost.Spirit                    | Deprecated due to efficiency                             |
| [GDF Parser](@ref Parsers_GdfParser)                    | Flex/Bison                      | Routing file format from Jason Cong's group at UCLA      |
| [GDSII Parser](@ref Parsers_GdsiiParser)                | Stream parser: C/C++            | Support .gds and .gds.gz when Boost and Zlib available   |
|                                                         | ASCII parser: Boost.Spirit      | Deprecated due to memory efficiency                      |
|                                                         | GdsDB wrapper: C/C++, boost     | High level wrapper for full layout import/export/flatten |
| [Tf Parser](@ref Parsers_TfParser)                      | Boost.Spirit                    | Read technology file for physical design                 |
| [Verilog Netlist Parser](@ref Parsers_VerilogParser)    | Flex/Bison                      | Read verilog netlist to initialize nets during placement |
| [LP Parser](@ref Parsers_LpParser)                      | Flex/Bison                      | Read linear programming problem, compatible with Gurobi  |
