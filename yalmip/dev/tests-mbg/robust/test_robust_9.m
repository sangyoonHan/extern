function test_robust_9

yalmip('clear')
sdpvar x w t1 t2;
F = set(abs(x) + w <= 1) + set(w == t1*(-0.5) + t2*0.5) + set([t1 t2]>=0)+set(t1+t2 == 1)
sol = solverobust(F,-x,[],[w;t1;t2]);
mbg_asserttolequal(double(x), 1/2, 1e-5);
mbg_asserttolequal(sol.problem, 0, 1e-5);

sdpvar x w t
F = set(x+sum(w) <= 10)
W = set(-1/2 <= w <= 1/2)
objective = (x-5)'*(x-5) + x*w;
sol = solverobust(F + W,objective,[],[w])
mbg_asserttolequal(double(x), 4.75, 1e-2);
