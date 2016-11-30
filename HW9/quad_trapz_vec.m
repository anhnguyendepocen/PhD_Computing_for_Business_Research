function  [Q,fcount] = quad_trapz_vec(F,a,b,h,varargin)
%QUAD_TRAPZ_VEC Evaluate definite integral numerically via the trapezoidal rule.
%   Q = QUAD_TRAPZ_VEC(F,A,B,h) approximates the integral of F(x) from A to B
%   using a stepsize h.  F is a a function handle or function name.
%
%   Arguments beyond the first four, Q = QUAD_TRAPZ_VEC(F,a,b,h,p1,p2,...),
%   are passed on to the integrand, F(x,p1,p2,..).
%
%   [Q,fcount] = QUAD_TRAPZ_VEC(F,...) also counts the number of evaluations
%   of F(x).
%

x_vec = [ a : h : b];
Q = feval(F,x_vec,varargin{:});
Q = h*(sum(Q)-0.5*sum(feval(F,[a,b])));
fcount = length(x_vec);

% end of function quad_rectangle_vec.m