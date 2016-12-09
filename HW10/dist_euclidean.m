function dist = dist_euclidean ( xi , x_train )
% Distance calculation between xi (ith row of x_train matrix ) and the other rows
numObsTrain = size ( x_train , 1);
dist = sum (( repmat(xi, numObsTrain , 1) - x_train ).^2 , 2);