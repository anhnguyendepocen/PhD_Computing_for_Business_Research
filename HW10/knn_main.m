
% Ask for user input
trainFileName = 'facebook_data.csv';

% Read data from .csv
train_data = csvread(trainFileName);
numObsTrain = size(train_data, 1);
numParams = size(train_data,2) - 1;

rmse_all = zeros(2,numObsTrain-1);

for k = 1:(numObsTrain-1)
    
    % Check correctness of input data
    if numObsTrain <= k
    disp('File read error : Number of observations must be greater than k');
    end

    x_train = train_data(:, 2: end );
    y_train = train_data(:, 1);
    
    % Run kNN
    [ypred, rmse] = knn_predict_insample( x_train, y_train, k);
    rmse_all(:,k) = [rmse k];
    
    % Print result
    disp('k-NN train data: ');
    disp('[ x_train y_train ] = ');
    disp([x_train y_train]);
    disp(['k-NN prediction result with k = ' num2str(k) ':']);
    disp([ x_train ypred]);
    disp('RMSE is now: ')
    disp(rmse);
    
end

% Find the best k
plot(rmse_all(2,:),rmse_all(1,:));

[rmse_min, k_min] = min(rmse_all(1,:));
disp('The k with the smallest rmse is: ');
disp(k_min);


% Out of sample prediction
x_test = [1 177; 8 10; 13 57];
y_test_pred = knn_predict(x_train, y_train, x_test, k_min);

disp('The predictions for y_test are: ');
disp(y_test_pred);



