
% integration with built-in function
%%
a = 0;    % lower integration limit
b = 0.8;  % upper integration limit

% use the inbuilt 'integral' function to get the (almost) exact value of the integral
Qexact = integral(@sin,a,b);

disp(sprintf('The exact value of the integral is: %11.8f',Qexact));

% integration with the trapezoidal rule
%%
h      = 0.5;
n      = 16;

h_vec  = cumprod(h(ones(1,n)));
Qrect  = zeros(n,1);
Qcount = zeros(n,1);
Qerr   = zeros(n,1);

disp(' ')
disp('Results for the trapezoidal integration rule (function subroutine)');
disp('      Qrect         error   fcn count');
tic
for i = 1 : n
    [Qrect(i),Qcount(i)] = quad_trapz(@sin,a,b,h_vec(i));
    Qerr(i)  = Qrect(i) - Qexact;
    fprintf('%11.8f  %11.8f   %7g\n', Qrect(i), Qerr(i), Qcount(i));
end
toc

disp(' ')
disp('Results for the trapezoidal integration rule (anonymous function)');
disp('     Qrect        error   fcn count');
tic
for i = 1 : n
    [Qrect(i),Qcount(i)] = quad_trapz(@(x) sin(x),a,b,h_vec(i));
    Qerr(i)  = Qrect(i) - Qexact;
    fprintf('%11.8f  %11.8f   %7g\n', Qrect(i), Qerr(i), Qcount(i));
end
toc

disp(' ')
disp('Results for the trapezoidal integration rule (vectorized)');
disp('      Qrect         error   fcn count');
tic
for i = 1 : n
    [Qrect(i),Qcount(i)] = quad_trapz_vec('sin',a,b,h_vec(i));
    Qerr(i)  = Qrect(i) - Qexact;
    fprintf('%11.8f  %11.8f   %7g\n', Qrect(i), Qerr(i), Qcount(i));
end
toc
% end of integration.m
