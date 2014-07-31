% Model generated from ex14_2_4.gms
% Created 02-Aug-2007 10:36:52 using YALMIP R20070725

% Setup a clean YALMIP environment 
yalmip('clear') 

% Define all variables 
x1 = sdpvar(1);
x2 = sdpvar(1);
x3 = sdpvar(1);
x4 = sdpvar(1);
x6 = sdpvar(1);

% Define objective function 
objective = -(0-x6-0);

% Define constraints 
F = set([]);
F=[F,(0.549337520233386*x2+1.1263896788319*x3)/(x1+0.816722116903399*x2+0.538540530229217*x3)+0.0910522583583458*x2/(0.972203312166101*x1+x2+0.394821041898112*x3)-0.273994101407968*x3/(1.07810138009609*x1+0.707289137797622*x2+x3)-(x1*(0.549337520233386*x2+1.1263896788319*x3)/sqr(x1+0.816722116903399*x2+0.538540530229217*x3)+0.972203312166101*x2*(0.0910522583583458*x1+1.03765878646318*x3)/sqr(0.972203312166101*x1+x2+0.394821041898112*x3)+1.07810138009609*x3*(0.692718766203089*x2-0.273994101407968*x1)/sqr(1.07810138009609*x1+0.707289137797622*x2+x3))-3667.70490156687/(226.184+x4)-x6<=-12.0457123581059];
F=[F,(0.0910522583583458*x1+1.03765878646318*x3)/(0.972203312166101*x1+x2+0.394821041898112*x3)+0.549337520233386*x1/(x1+0.816722116903399*x2+0.538540530229217*x3)+0.692718766203089*x3/(1.07810138009609*x1+0.707289137797622*x2+x3)-(0.816722116903399*x1*(0.549337520233386*x2+1.1263896788319*x3)/sqr(x1+0.816722116903399*x2+0.538540530229217*x3)+x2*(0.0910522583583458*x1+1.03765878646318*x3)/sqr(0.972203312166101*x1+x2+0.394821041898112*x3)+0.707289137797622*x3*(0.692718766203089*x2-0.273994101407968*x1)/sqr(1.07810138009609*x1+0.707289137797622*x2+x3))-2904.34268119711/(221.969+x4)-x6<=-9.63112952618865];
F=[F,(0.692718766203089*x2-0.273994101407968*x1)/(1.07810138009609*x1+0.707289137797622*x2+x3)+1.1263896788319*x1/(x1+0.816722116903399*x2+0.538540530229217*x3)+1.03765878646318*x2/(0.972203312166101*x1+x2+0.394821041898112*x3)-(0.538540530229217*x1*(0.549337520233386*x2+1.1263896788319*x3)/sqr(x1+0.816722116903399*x2+0.538540530229217*x3)+0.394821041898112*x2*(0.0910522583583458*x1+1.03765878646318*x3)/sqr(0.972203312166101*x1+x2+0.394821041898112*x3)+x3*(0.692718766203089*x2-0.273994101407968*x1)/sqr(1.07810138009609*x1+0.707289137797622*x2+x3))-3984.92283948829/(233.426+x4)-x6<=-11.9515596536534];
F=[F,(-(0.549337520233386*x2+1.1263896788319*x3)/(x1+0.816722116903399*x2+0.538540530229217*x3))-(0.0910522583583458*x2/(0.972203312166101*x1+x2+0.394821041898112*x3)-0.273994101407968*x3/(1.07810138009609*x1+0.707289137797622*x2+x3))+x1*(0.549337520233386*x2+1.1263896788319*x3)/sqr(x1+0.816722116903399*x2+0.538540530229217*x3)+0.972203312166101*x2*(0.0910522583583458*x1+1.03765878646318*x3)/sqr(0.972203312166101*x1+x2+0.394821041898112*x3)+1.07810138009609*x3*(0.692718766203089*x2-0.273994101407968*x1)/sqr(1.07810138009609*x1+0.707289137797622*x2+x3)+3667.70490156687/(226.184+x4)-x6<=12.0457123581059];
F=[F,(-(0.0910522583583458*x1+1.03765878646318*x3)/(0.972203312166101*x1+x2+0.394821041898112*x3))-(0.549337520233386*x1/(x1+0.816722116903399*x2+0.538540530229217*x3)+0.692718766203089*x3/(1.07810138009609*x1+0.707289137797622*x2+x3))+0.816722116903399*x1*(0.549337520233386*x2+1.1263896788319*x3)/sqr(x1+0.816722116903399*x2+0.538540530229217*x3)+x2*(0.0910522583583458*x1+1.03765878646318*x3)/sqr(0.972203312166101*x1+x2+0.394821041898112*x3)+0.707289137797622*x3*(0.692718766203089*x2-0.273994101407968*x1)/sqr(1.07810138009609*x1+0.707289137797622*x2+x3)+2904.34268119711/(221.969+x4)-x6<=9.63112952618865];
F=[F,(-(0.692718766203089*x2-0.273994101407968*x1)/(1.07810138009609*x1+0.707289137797622*x2+x3))-(1.1263896788319*x1/(x1+0.816722116903399*x2+0.538540530229217*x3)+1.03765878646318*x2/(0.972203312166101*x1+x2+0.394821041898112*x3))+0.538540530229217*x1*(0.549337520233386*x2+1.1263896788319*x3)/sqr(x1+0.816722116903399*x2+0.538540530229217*x3)+0.394821041898112*x2*(0.0910522583583458*x1+1.03765878646318*x3)/sqr(0.972203312166101*x1+x2+0.394821041898112*x3)+x3*(0.692718766203089*x2-0.273994101407968*x1)/sqr(1.07810138009609*x1+0.707289137797622*x2+x3)+3984.92283948829/(233.426+x4)-x6<=11.9515596536534];
F=[F,x1+x2+x3==1];
F=[F,1e-006<=x1<=1];
F=[F,1e-006<=x2<=1];
F=[F,1e-006<=x3<=1];
F=[F,40<=x4<=90];
F=[F,0<=x6 <= 1000];

% Solve problem
x = recover(F);
sol = solvesdp(F+[-1000 <= x <= 1000],objective,sdpsettings('solver','bmibnb','allownonconvex',1));
mbg_assertfalse(sol.problem);
mbg_asserttolequal(double(objective), 0, 1e-3);