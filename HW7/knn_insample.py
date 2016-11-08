# -*- coding: utf-8 -*-
"""
knn.py
Created on Sun Aug 10 12:51:35 2014

@author: Dongwook Shin, Yash Kanoria

User input (in the main function):
    - 'knn_train_data.csv' 
        Data samples in rows, outcome variable in first col
    - 'knn_test_data.csv'  Data samples in rows
    - k: the number of nearest neighbors desired

Output:
    - [x_train, y_train]: train data read from the file
    - [x_test, y_test]: test data matrix, x_test, 
                        and corresponding predicted values, y_test
"""

import numpy as np
import scipy.spatial.distance as ssd
import time
import matplotlib
import matplotlib.pyplot as plt

def knn_predict_insample(x_train, y_train, x_test, k):
    """ function for out-of-sample prediction using k-NN algorithm 
        Inputs:            
            x_train: 2D array containing training samples in rows
            y_train: 1D array containing outcomes for training samples
            x_test:  2D array containing test samples in rows
            k:       Number of neighbors to use
        
        Output:
            List containing predictions for test samples
    """
    # initialize list to store predicted class
    y_test = []
    # for each instance in data testing,
    # calculate distance in respect to data training
    for i, di in enumerate(x_test):
        distances = []  # initialize list to store distance
        for j, dj in enumerate(x_train):
            # calculate distances
            distances.append((dist_euclidean(di,dj), y_train[j]))
        # k-neighbors
        sorted_distances = sorted(distances)[:k]

        # predict the outcome for the instance
        y_test.append(np.mean(sorted_distances, axis = 0)[1])
        # return mean of y
        # or do np.mean([y for (dist, y) in temp])
 
    # return predicted outcome
    return y_test
 
def dist_euclidean(di,dj):
    """ Distance calculation between di and dj"""
    return ssd.euclidean(di,dj) # built-in Euclidean fn
 

""" The main code starts here """
 
# initialize runtime
start = time.clock()

# <codecell>
#FILL CODE TO READ DATA
# read data from .csv files
train_data = np.loadtxt('facebook_data.csv', delimiter= ',', dtype="float")
test_data = np.loadtxt('facebook_data_test.csv', delimiter= ',', dtype="float")


# <codecell>

# translate data to x_train, y_train, and x_test array
y_train = train_data[:, 0]
x_train = train_data[:,1:]
x_test = test_data[:, :]

# <codecell>

# set k, the number of nearest neighbors desired
# k = 3
# run k-NN algorithm to predict y_test values for x_test data
# y_pred = knn_predict_insample(x_train, y_train, x_train, k)

# rmse
# rmse = np.sqrt(sum(y_pred-y_train))/len(y_train)

y_pred_all = []
rmse_all = []
k_all = np.arange(1,len(y_train),1)

for i in k_all:
    y_pred.append(knn_predict_insample(x_train, y_train, x_train, i))
    rmse_all.append(np.sqrt(sum((y_pred[i]-y_train)*(y_pred[i]-y_train))/len(y_train)))

smallest_k = np.argmin(rmse_all)
plt.scatter(k_all, rmse_all, marker = 'o', c= 'r', s = 40)
plt.xlabel("K");
plt.ylabel("RMSE")
plt.show()

y_test = knn_predict_insample(x_train, y_train, x_test, smallest_k)

# print out results
print("\nk-NN train data:")
print("x_train \t\t | y_train")
for i, di in enumerate(x_train):
    a = ','.join('{:5.1f}'.format(k) for ik, k in enumerate(di))
    #Can use  '%5.1f' % k  instead of '{:5.1f}'.format(k)
    strTrainRow = a + "\t\t | " + '{:5.1f}'.format(y_train[i])
    print(strTrainRow)

print("\nk-NN prediction results for test data with k = %d" % k)
print("x_test \t\t\t | y_test")
for i, di in enumerate(x_test):
    a = ','.join('{:5.1f}'.format(k) for ik, k in enumerate(di))
    strTestRow = a + "\t\t | " + '{:5.2f}'.format(y_test[i])
    print(strTestRow)

# # Find runtime
run_time = time.clock() - start
print("\nRuntime:", '%.4f' % run_time, "seconds")