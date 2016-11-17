# HW8 sz2622

import pymysql
import numpy as np
from sklearn import linear_model as lm
import matplotlib
from matplotlib import pyplot as plt

try:
    conn= pymysql.connect(host='localhost', port=3306, user='root', 
                          db='adult', passwd='1234')
except Exception as ex:
    print(ex)
cur=conn.cursor() # cur will allow us to run queries on the db

# Obtain data from the table adult_train
n2 = cur.execute("SELECT Income, Age, Education_Num, Hours_Per_Week FROM adult_train")
numobs = cur.rowcount;
data = cur.fetchall()
cur.close()
conn.close()

print("First 10 rows of data:")
for i in range(10):
    print(data[i])

# Split dataset into training and test set
obstrain = int(0.8*numobs);
obstest = numobs - obstrain;

X=np.zeros((numobs,3)); 
y=np.empty((numobs,1));

for i,rowtuple in enumerate(data): # Transform Income into a dummy variable
    if rowtuple[0]==' <=50K\r':
        y[i]=0
    elif rowtuple[0]==' >50K\r':
        y[i]=1
    else:
        print("Problem in first entry in row index", i)
    
    X[i,0:] = rowtuple[1:]    

    
print("First 10 rows of X:\n", X[:10,:]);
print("First 10 rows of y:\n", y[:10,:]);
# Split data into training and test
Xtr = X[:obstrain,:]
ytr = y[:obstrain,:]
Xte = X[obstrain:,:]
yte = y[obstrain:,:]

# Logistic Regression (on training set)
logreg = lm.LogisticRegression(C=1e5)
logreg.fit(Xtr, ytr.ravel())
np.set_printoptions(precision=3)
print("Intercept: ",logreg.intercept_, "\n Coefficients: ", logreg.coef_)

# Logistic Regression (on test set)
stdte = np.std(yte)
rmsete = np.std(yte.ravel() - logreg.predict(Xte))
Rsqte = 1 - rmsete**2/stdte**2
print("Test (logistic regression):")
print("Std deviation of y:", '%.3f' % stdte)
print("RMSE: ", '%.3f' % rmsete)
print("Rsq: ", '%.3f' % Rsqte)

print("The model predicts",100*sum(logreg.predict(Xte))/obstest,"% of total population to be high income individuals")

# Interpretation
# 


# Visualization
matplotlib.rcParams.update({'font.size': 15})
plt.scatter(logreg.predict(Xte), yte.ravel() - logreg.predict(Xte))
plt.xlabel('Prediction')
plt.ylabel('Error in prediction')
plt.show()

