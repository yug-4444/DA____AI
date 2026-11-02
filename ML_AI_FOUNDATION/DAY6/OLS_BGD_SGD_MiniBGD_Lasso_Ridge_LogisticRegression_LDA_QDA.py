import numpy as np
from sklearn.linear_model import LinearRegression ,LogisticRegression ,Lasso ,Ridge 
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis ,QuadraticDiscriminantAnalysis 
from sklearn.naive_bayes import BernoulliNB ,GaussianNB
#Linear Regression
#Logistic Regression
#Locally Weighted Linear Regression
#LDA,QDA
#penalize->none ,L1(lambda) , L2(lambda)
#solver->closed form (normal), BGD(alpha) ,SGD(alpha) ,MiniBGD(alpha,batch_size) ,Newton (epoches)

class linear_regression:
    def __init__(self,penality=None,
                lamb=None,
                solver="normal"):
        self.solver=solver
        self.lamb=lamb
        self.penality=penality
        self.beta=None

    def normal_methord(self,X,y):
        x=np.array(X)
        if x.ndim==1:
            x=np.reshape(-1,1)
        y=np.array(y).reshape(-1,1)
        m,n=x.shape
        
    def fit_methord(self):
        if self.solver=="normal":
            pass
        elif self.solver=="bgd":
            pass
        elif self.solver=="sgd":
            pass
        elif self.solver=="mini_batch":
            pass
        elif self.solver=="newton":
            pass
        else:
            print("use a vaild solver methord -> 1.normal(default), \n2. bgd, \n3. sgd, \n4.mini_batch, \n 5.newton\n")
            return None
        