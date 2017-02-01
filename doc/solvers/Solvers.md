Limbo.Solvers {#Solvers}
---------

[TOC]

# Introduction {#Solvers_Introduction}

Solvers and API for specialized problems, such as solving special linear programming problems with min-cost flow algorithms. 
It also wraps solvers like semidefinite programming solver [Csdp](https://projects.coin-or.org/Csdp "Csdp") and convex optimization solver [Gurobi](www.gurobi.com "Gurobi"). 

# Examples {#Solvers_Examples}

See documented version: [test/solvers/lpmcf/test_lpmcf.cpp](@ref test_lpmcf.cpp)
\include test/solvers/lpmcf/test_lpmcf.cpp

Compiling and running commands (assuming LIMBO_DIR is exported as the environment variable to the path where limbo library is installed)

# References {#Solvers_References}

- [limbo/solvers/lpmcf/Lgf.h](@ref Lgf.h)
- [limbo/solvers/lpmcf/LpDualMcf.h](@ref LpDualMcf.h)
- [limbo/solvers/api/CsdpEasySdpApi.h](@ref CsdpEasySdpApi.h)
- [limbo/solvers/api/GurobiApi.h](@ref GurobiApi.h)
