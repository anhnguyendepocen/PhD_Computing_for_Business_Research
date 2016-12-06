%% gbm_sim .m
%% Parameter initialization
% Initialize simulation parameters
n = 1000; % number of simulation trials
m = 30; % number of time steps
s = 110; % initial stock price
mu = 0.07; % growth rate
sig = 0.25; % volatility
t = 20; % time period
dt = t/m; % time step
%% a) Simulation
% s_mat (i,j) = stock price at time i, simulation trial j.
% s_mat has m+1 rows ( row 1 is the current time ) and n columns
rng(0);
s_mat = exp((mu - 0.5*sig*sig)*dt + sig*sqrt(dt)*randn(m,n));
s_mat = cumprod([s(:,ones(1,n)); s_mat]);
s_t = s_mat(m+1,:);

%% b) Plots
figure (1) ; plot ( linspace (0,t,m+1) ,s_mat ); xlabel ('Time '); ylabel ('Stock Price');
title('Stock Price versus Time'); set(gcf,'color','white');
figure (2) ; plot ( linspace (0,t,m+1) ,log( s_mat )); xlabel ('Time'); ylabel('Log Stock Price');
title ('Log Stock Price versus Time'); set(gcf ,'color','white');
figure (3) ; hist (s_t ,15) ; xlabel ('Stock Price'); ylabel ('Frequency');
title ('Stock Price Histogram '); set (gcf ,'color','white');
figure (4) ; hist ( log ( s_t ) ,15); xlabel ('Log Stock Price '); ylabel ('Frequency');
title ('Log Stock Price Histogram '); set(gcf ,'color','white ');


%% c) Averages

% Result 1
disp(['average S(T) is: ' num2str(mean(s_t)) ' std err : ' num2str(std(s_t)/sqrt(n))]);

% Result 2: reset seed
rng(0);
s_mat = exp((mu - 0.5*sig*sig)*dt + sig*sqrt(dt)*randn(m,n));
s_mat = cumprod([s(:,ones(1,n)); s_mat]);
s_t = s_mat(m+1,:);
disp(['average S(T) is: ' num2str(mean(s_t)) ' std err : ' num2str(std(s_t)/sqrt(n))]);

% Result 3: if we do not reset seed
s_mat = exp((mu - 0.5*sig*sig)*dt + sig*sqrt(dt)*randn(m,n));
s_mat = cumprod([s(:,ones(1,n)); s_mat]);
s_t = s_mat(m+1,:);
disp(['average S(T) is: ' num2str(mean(s_t)) ' std err : ' num2str(std(s_t)/sqrt(n))]);
% end of gbm_sim .m



