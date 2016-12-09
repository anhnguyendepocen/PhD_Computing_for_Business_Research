function ypred_test = knn_predict ( x_train , y_train , x_test , k)

numObsTest = size( x_test , 1);
ypred_test = zeros( numObsTest , 1);

for i = 1: numObsTest
    dist = dist_euclidean( x_test(i, :) , x_train );
    % Sort training sample pts by distance from test point
    [~, sortpos ] = sort (dist , 'ascend');
    % The prediction is the mean of y_train for the k closest points
    ypred_test(i) = mean( y_train( sortpos(1:k)));
end