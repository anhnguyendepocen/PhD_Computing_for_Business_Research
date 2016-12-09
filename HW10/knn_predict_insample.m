function [y_pred, rmse] = knn_predict_insample(x_train, y_train, k)

numObs = size(x_train, 1);
y_pred = zeros(numObs, 1);

for i = 1: numObs
% For person i, compute distance from all the other people
dist = dist_euclidean(x_train (i, :), x_train);
% Sort pts by distance from other points in the training set
[~, sortpos ] = sort(dist , 'ascend');
% The prediction is the mean of y_train for the k closest points
y_pred(i) = mean(y_train(sortpos(2:(k+1))));

% Compute rmse
rmse = std(y_train - y_pred);

end