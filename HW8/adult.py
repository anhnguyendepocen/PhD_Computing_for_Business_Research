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
n1 = cur.execute("SELECT Income, Age, Education_Num, Hours_Per_Week FROM adult_train")
obstrain = cur.rowcount;
data = cur.fetchall()
n2 = cur.execute("SELECT Income, Age, Education_Num, Hours_Per_Week FROM adult_test")
obstest = cur.rowcount;
data2 = cur.fetchall()
cur.close()
conn.close()

print("First 10 rows of training data:")
for i in range(10):
    print(data[i])

print("First 10 rows of test data:")
for i in range(10):
    print(data2[i])

print("Training data has", obstrain, "observations")
print("Test data has", obstest, "observations")

Xtr=np.zeros((obstrain,3)); 
ytr=np.empty((obstrain,1));
Xte=np.zeros((obstest,3)); 
yte=np.empty((obstest,1));


for i,rowtuple in enumerate(data): # Transform Income into a dummy variable
    if rowtuple[0]==' <=50K\r':
        ytr[i]=0
    elif rowtuple[0]==' >50K\r':
        ytr[i]=1
    else:
        print("Problem in first entry in row index", i)
    
    Xtr[i,0:] = rowtuple[1:]    

for i,rowtuple in enumerate(data2): # Transform Income into a dummy variable
    if rowtuple[0]==' <=50K.\r':
        yte[i]=0
    elif rowtuple[0]==' >50K.\r':
        yte[i]=1
    else:
        print("Problem in first entry in row index", i)
    
    Xte[i,0:] = rowtuple[1:]    


print("First 10 rows of X training:\n", Xtr[:10,:]);
print("First 10 rows of y training:\n", ytr[:10,:]);
print("First 10 rows of X test:\n", Xte[:10,:]);
print("First 10 rows of y test:\n", yte[:10,:]);

# Logistic Regression (on training set)
logreg = lm.LogisticRegression()
logreg.fit(Xtr, ytr.ravel())
np.set_printoptions(precision=3)
print("Intercept: ",logreg.intercept_, "\n Coefficients: ", logreg.coef_)
print("Error probability of logistic classifier (in sample): ", 1-logreg.score(Xte,yte))

# Interpretation
# The coefficients suggest that the log odds ratio of being in the high-income associated with a one year increase in age is about 0.045,
# that the log odds ratio of being in the high-income associated with a one year increase in education is about 0.338,
# and that the log odds ratio of being in the high-income associated with a one hour increase in working hours per week is about 0.041. 

# Logistic Regression (on test set)
stdte = np.std(yte)
rmsete = np.std(yte.ravel() - logreg.predict(Xte))
Rsqte = 1 - rmsete**2/stdte**2
print("Test (logistic regression):")
print("Std deviation of y:", '%.3f' % stdte)
print("RMSE: ", '%.3f' % rmsete)
print("Rsq: ", '%.3f' % Rsqte)
print("")

logreg_pred = logreg.predict_proba(Xte)
print("The model predicts", 100*sum(logreg_pred)[1]/obstest,"% of total population to be high income individuals")

# print(logreg_pred[1][1])

high_income_proportion = []
for i in range(10):
	Num_high = 0
	Num_total = 0
	for j in range(obstest):
		if logreg_pred[j][1] > i/10 and logreg_pred[j][1] < (i+1)/10:
			Num_total +=1
			if yte[j] == 1:
				Num_high +=1
	high_income_proportion.append(Num_high/Num_total)

# Visualization
matplotlib.rcParams.update({'font.size': 15})
ind = np.arange(0,1,0.1)
width = 0.1
bar_high_income = plt.bar(ind,high_income_proportion,width)
plt.xlim([0,1])
plt.xlabel('Probability of High Income from Model')
plt.ylabel('Fraction of High Income from Data (Hit Rate)')
plt.show()

