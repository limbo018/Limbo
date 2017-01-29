Limbo.Parsers {#Parsers}
---------

## Components 
| Components              | Languages & Libraries           | Description                                              |
| ----------------------- | ------------------------------- | -------------------------------------------------------- |
| Bookshelf Parser        | Flex/Bison                      | Placement file format from UCSD                          |
| DEF Parser              | Flex/Bison                      |                                                          |
|                         | Boost.Spirit                    | Deprecated due to efficiency                             |
| Ebeam parser            | Flex/Bison                      |                                                          |
|                         | Boost.Spirit                    | Deprecated due to efficiency                             |
| LEF Parser              | Flex/Bison                      |                                                          |
|                         | Boost.Spirit                    | Deprecated due to efficiency                             |
| GDF Parser              | Flex/Bison                      | Routing file format from Jason Cong's group at UCLA      |
| GDSII Parser            | Stream parser: C/C++            | Support .gds and .gds.gz when Boost and Zlib available   |
|                         | ASCII parser: Boost.Spirit      | Deprecated due to memory efficiency                      |
|                         | GdsDB wrapper: C/C++, boost     | High level wrapper for full layout import/export/flatten |
| Tf Parser               | Boost.Spirit                    | Read technology file for physical design                 |
| Verilog netlist parser  | Flex/Bison                      | Read verilog netlist to initialize nets during placement |
| LP Parser               | Flex/Bison                      | Read linear programming problem, compatible with Gurobi  |
