#!/usr/bin/env python

import sys
import pandas as pd
import math
import myhw6mod as mymod
import matplotlib
import matplotlib.pyplot as plt


"""
try: 
    if sys.argv[1] == "-":
        lines = sys.stdin.readlines()
    else:
        # use open() to open a file 
        lines = open(sys.argv[1]).readlines()
except:
    print("Usage: %s <filename|->" % sys.argv[0])
    sys.exit(1)
"""

try:
    file_name = sys.argv[1]
    data = pd.read_csv(file_name)
except:
    print("Please provide a valid file name.")
    sys.exit(1)

xlist = []
ylist = []
sse = 0
bad_obs = 0

for i in range(1,data.shape[0]):
    x = mymod.haversine(data.loc[i,'pickup_longitude'],data.loc[i,'pickup_latitude'],data.loc[i,'dropoff_longitude'],data.loc[i,'dropoff_latitude'])
    if x == 0:
        bad_obs = 0
        continue
    xlist.append(x)
    y = data.loc[i,'total_amount']/x
    ylist.append(y)
    sse += math.pow(x-data.loc[i,'trip_distance'],2)


plt.scatter(xlist, ylist, marker = 'o', c= 'r', s = 40)
plt.xlabel("Distance");
plt.ylabel("Cost per Mile")
plt.show()

rmse = math.sqrt(sse/(data.shape[0]-bad_obs))
print("rmse is",rmse)
