Minimize
5437 x0_0 + 4689 x0_1 + 3223 x1_0 + 7654 x1_1 + 8765 xd1 + 8320 xd0

Subject To
node_constr_0: 1 x0_0 + 1 x0_1 - x0 = 0
node_constr_1: 1 x1_0 + 1 x1_1 - x1 = 0
subg_constr_0: 1 x0_0 + 1 x1_0 + 1 xd0 = 1
subg_constr_1: 1 x0_1 + 1 x1_1 + 1 xd1 = 1
weight_constr: 1 x0   + 1 x1 = 1
Bounds
0 <= x0 <= 1
0 <= x0_0 <= 1
0 <= x0_1 <= 1
0 <= x1 <= 1
0 <= x1_0 <= 1
0 <= x1_1 <= 1
0 <= xd0 <= 1
0 <= xd1 <= 1
Generals
End
