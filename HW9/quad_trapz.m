function  [Q,fcount] = quad_trapz(F,a,b,h,varargin)
%QUAD_TRAPZ Evaluate definite integral numerically via the trapezoidal rule.
%   Q = QUAD_TRAPZ(F,a,b,h) approximates the integral of F(x) from a to
%   b using a stepsize h. F is a function handle or function name.
%
%   Arguments beyond the first four, Q = QUAD_RECTANGLE(F,a,b,tol,p1,p2,...),
%   are passed on to the integrand, F(x,p1,p2,..).
%
%   [Q,fcount] = QUAD_TRAPZ(F,...) also counts the number of evaluations
%   of F(x).
%


x_vec = [ a : h : b];
Q = 0;
for x = x_vec
    if x == a || x == b
        Q = Q + 0.5*feval(F,x,varargin{:});
    else
        Q = Q + feval(F,x,varargin{:});
    end
end

Q = h*Q;
fcount = length(x_vec);

% end of function quad_trapz.m