# ============================================================
# MINI PROJECT
#
# IMPLEMENTATION OF GAUSSIAN DISCRIMINANT ANALYSIS (GDA),
# LINEAR DISCRIMINANT ANALYSIS (LDA),
# AND QUADRATIC DISCRIMINANT ANALYSIS (QDA)
# FROM SCRATCH USING NUMPY
#
# Features:
# 1. Binary LDA/GDA
# 2. Multiclass LDA/GDA
# 3. Multiclass QDA
# 4. Covariance Estimation
# 5. Class Prior Estimation
# 6. Pseudoinverse-based Singular Covariance Handling
# 7. Validation Against Scikit-Learn Implementations
#
# Author: Yug Bansal
# Course: Machine Learning Foundations
# ============================================================


import numpy as np
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.discriminant_analysis import QuadraticDiscriminantAnalysis

#under assumption that our X=[x1 x2 .... xn]T features
#1. (x|Y=k)~N(u_k,cov)
#2. cov_k=cov_j=cov means contours of all gaussian suface have same elliptical shape/circle as cov eigenvalue and eigenvector dictates the shape of contours that is centered u_k
#bysen probability -> P(y=k|x)=P(x|Y=k).P(Y=k)/P(x) and P(x)=sum_i_from_1_to_k((P(x|y=i).P(y=i)) which will be sme for all class k so it can assumed to invidsible during comparision
#linear score:log(P(Y=k|x))=delta_k(x)=X.T(cov_inv)u_k-1/2*u_k.T.(cov_inv).u_k+log(pie_k) ;pie_k=P(Y=k)
#in compare of tow class(k and p) if becomes delta_k=delta_p ->
#X.T(cov_inv)(u_k-u_p)-1/2(u_k+u_p).t(cov_inv)(u_k-u_p)+log(pie_k/pie_p)=0=X.T B+B_0
class LDA_OR_GDA_k_2_classes:
    def __init__(self,x,y):
        self.k=2
        self.X=np.array(x)
        if self.X.ndim==1:
            self.X=self.X.reshape(-1,1)
        self.y=np.array(y).reshape(-1,1)
        self.m,self.n=self.X.shape
        self.X_0=self.X[self.y.ravel()==0]
        self.X_1=self.X[self.y.ravel()==1]
        self.m_0=self.X_0.shape[0]
        self.m_1=self.m-self.m_0
        self.u_0=np.mean(self.X_0,axis=0,keepdims=True)
        self.u_1=np.mean(self.X_1,axis=0,keepdims=True)
        center_x_0=self.X_0-self.u_0
        center_x_1=self.X_1-self.u_1
        self.sigma=1/(self.m-self.k)*(center_x_0.T@center_x_0+center_x_1.T@center_x_1)
        self.sigma_inv=np.linalg.pinv(self.sigma)
        self.pie_0=self.m_0/self.m
        self.pie_1=self.m_1/self.m
        self.b_0=(-1/2*(self.u_1+self.u_0)@self.sigma_inv@(self.u_1-self.u_0).T+np.log(self.pie_1/self.pie_0)).item()
        self.b_=self.sigma_inv@(self.u_1-self.u_0).T

    def sigmoid(self,z):
        z=np.clip(z,-700,700)
        return 1/(1+np.exp(-z))
    
    def predict_prob(self,x_inp):
        x=np.array(x_inp)
        if x.ndim==1:
            x=x.reshape(1,-1)
        linear_score=x@self.b_+self.b_0
        return self.sigmoid(linear_score)
    
    def predict_class(self,x_inp):
        x=np.array(x_inp)
        if x.ndim==1:
            x=x.reshape(1,-1)
        linear_score=x@self.b_+self.b_0
        return(linear_score>=0).astype(int)
    
    def accuracy(self,x_i,y_i):
        x=np.array(x_i)
        if x.ndim==1:
            x=x.reshape(1,-1)
        y=np.array(y_i).reshape(-1,1)
        pred=self.predict_class(x)
        return np.mean(y.ravel()==pred.ravel())

#lets see for general k classes
class GDA_K_CLASS:
    def __init__(self,X,y):
        self.x=np.array(X)
        if self.x.ndim==1:
            self.x=self.x.reshape(-1,1)
        self.y=np.array(y).reshape(-1,1)
        self.classes=np.unique(self.y.ravel())
        self.k=len(self.classes)
        self.m,self.n=self.x.shape

        self.u={}
        self.pie={}
        for k in self.classes:
            x_k=self.x[self.y.ravel()==k]
            self.pie[k]=x_k.shape[0]/self.m
            self.u[k]=np.mean(x_k,axis=0,keepdims=True)

        self.sigma=np.zeros((self.n,self.n))
        for k in self.classes:
            x_k=self.x[self.y.ravel()==k]
            x_c=x_k-self.u[k]
            self.sigma+=x_c.T@x_c
        self.sigma=self.sigma/(self.m-self.k)
        self.sigma_inv=np.linalg.pinv(self.sigma)
        #linear score:log(P(Y=k|x))=delta_k(x)=X.T(cov_inv)u_k-1/2*u_k.T.(cov_inv).u_k+log(pie_k) ;pie_k=P(Y=k)
        #each class k for any x delta_k: X.T B_1+B_0
        self.B_0={}
        self.B_1={}
        for k in self.classes:
            self.B_0[k]=(-1/2*self.u[k]@self.sigma_inv@self.u[k].T+np.log(self.pie[k])).item()
            self.B_1[k]=self.sigma_inv@self.u[k].T
    
    def score_delta_k(self,x,k):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(1,-1)
        return x@self.B_1[k]+self.B_0[k]

    def predict_class(self,x):
        scores=[]
        for k in self.classes:
            scores.append(self.score_delta_k(x,k))
        delta_score=np.hstack(scores)
        pred=np.argmax(delta_score,axis=1)
        return self.classes[pred]

    def accuracy(self,x,y):
        y=np.array(y).reshape(-1,1)
        pred=np.array(self.predict_class(x))
        return np.mean(y.ravel()==pred.ravel())


class QDA_K_CLASS:
    def __init__(self,X,y):
        self.x=np.array(X)
        if self.x.ndim==1:
            self.x=self.x.reshape(-1,1)
        self.y=np.array(y).reshape(-1,1)
        self.classes=np.unique(self.y.ravel())
        self.k=len(self.classes)
        self.m,self.n=self.x.shape

        self.u={}
        self.pie={}
        for k in self.classes:
            x_k=self.x[self.y.ravel()==k]
            self.pie[k]=x_k.shape[0]/self.m
            self.u[k]=np.mean(x_k,axis=0,keepdims=True)

        self.sigma_inv={}
        self.sigma_log_det={}
        for k in self.classes:
            x_k=self.x[self.y.ravel()==k]
            x_c=x_k-self.u[k]
            sigma_k=(x_c.T@x_c)/(x_k.shape[0]-1)
            _,self.sigma_log_det[k]=np.linalg.slogdet(sigma_k)
            self.sigma_inv[k]=np.linalg.pinv(sigma_k)
        #quadratic score:log(P(Y=k|x))=delta_k(x)=-1/2Log|sigma_k|-1/2*(x-u_k)(sigma_k_inv)(x-u_k).T+log(pie_k) ;pie_k=P(Y=k)
        #-1/2(x-u_k)(sigma_k_inv)(x-u_k).T+b_k ->b_k=-1/2Log|sigma_k|+log(pie_k)
        self.b={}
        for k in self.classes:
            self.b[k]=-1/2*self.sigma_log_det[k]+np.log(self.pie[k])
    
    def score_delta_k(self,x,k):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(1,-1)
        diff=x-self.u[k]
        return -1/2*np.sum((diff@self.sigma_inv[k])*(diff),axis=1,keepdims=True)+self.b[k]#!!!!!!!!!!!!!!!!!!!!!!!!!

    def predict_class(self,x):
        scores=[]
        for k in self.classes:
            scores.append(self.score_delta_k(x,k))
        delta_score=np.hstack(scores)
        pred=np.argmax(delta_score,axis=1)
        return self.classes[pred]

    def accuracy(self,x,y):
        y=np.array(y).reshape(-1,1)
        pred=np.array(self.predict_class(x))
        return np.mean(y.ravel()==pred.ravel())

#====================================================================================================================
#====================================================================================================================
#====================================================================================================================
#====================================================================================================================
#-------------------------------------------TESTING-----------------------------------------------------------------
#====================================================================================================================
#====================================================================================================================
#====================================================================================================================
 
#-----------------------------------------------------------------------------------EXAMPLES TO TEST ON
print("Example 1----------------------------------------")
import numpy as np
from sklearn.datasets import make_classification
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis

np.random.seed(42)

X,y = make_classification(
    n_samples=2000,
    n_features=15,
    n_informative=10,
    n_redundant=3,
    n_repeated=0,
    n_classes=2,
    class_sep=2.0,
    random_state=42
)

my_model = LDA_OR_GDA_k_2_classes(X,y)

print("My LDA Accuracy:")
print(my_model.accuracy(X,y))

print()

sk_model = LinearDiscriminantAnalysis()
sk_model.fit(X,y)

sk_pred = sk_model.predict(X)

print("Sklearn Accuracy:")
print(np.mean(sk_pred==y))
print("\n\nEXAMPLE 2-----------------------------------------------------------------")
import numpy as np
from sklearn.datasets import make_classification
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis

np.random.seed(42)

X,y = make_classification(
    n_samples=3000,
    n_features=20,
    n_informative=15,
    n_redundant=3,
    n_classes=4,
    n_clusters_per_class=1,
    class_sep=2.5,
    random_state=42
)

my_model = GDA_K_CLASS(X,y)

print("My Multiclass LDA Accuracy:")
print(my_model.accuracy(X,y))

print()

sk_model = LinearDiscriminantAnalysis()
sk_model.fit(X,y)

sk_pred = sk_model.predict(X)

print("Sklearn Accuracy:")
print(np.mean(sk_pred==y))
print("\n\nEXAMPLE 3-----------------------------------------------------------------")
np.random.seed(42)

X,y = make_classification(
    n_samples=5000,
    n_features=20,
    n_informative=8,
    n_redundant=8,
    n_classes=3,
    class_sep=1.0,
    flip_y=0.05,
    random_state=42
)
my_model = GDA_K_CLASS(X,y)

print("My Multiclass LDA Accuracy:")
print(my_model.accuracy(X,y))

print()

sk_model = LinearDiscriminantAnalysis()
sk_model.fit(X,y)

sk_pred = sk_model.predict(X)

print("Sklearn Accuracy:")
print(np.mean(sk_pred==y))
print("\n\nEXAMPLE 4-----------------------------------------------------------------")
np.random.seed(42)

X,y = make_classification(
    n_samples=1000,
    n_features=20,
    n_informative=5,
    n_redundant=15,
    n_classes=3,
    random_state=42
)
my_model = GDA_K_CLASS(X,y)

print("My Multiclass LDA Accuracy:")
print(my_model.accuracy(X,y))

print()

sk_model = LinearDiscriminantAnalysis()
sk_model.fit(X,y)

sk_pred = sk_model.predict(X)

print("Sklearn Accuracy:")
print(np.mean(sk_pred==y))
print("\n\nEXAMPLE 5-----------------------------------------------------------------")
np.random.seed(42)

X,y = make_classification(
    n_samples=10000,
    n_features=20,
    n_informative=15,
    n_redundant=3,
    n_classes=5,
    class_sep=2.0,
    random_state=42
)
my_model = GDA_K_CLASS(X,y)

print("My Multiclass LDA Accuracy:")
print(my_model.accuracy(X,y))

print()

sk_model = LinearDiscriminantAnalysis()
sk_model.fit(X,y)

sk_pred = sk_model.predict(X)

print("Sklearn Accuracy:")
print(np.mean(sk_pred==y))

# ============================================================
# QDA TESTING SUITE
# Compare:
# My QDA
# Sklearn QDA
# My LDA
# Sklearn LDA
# ============================================================

import numpy as np
from sklearn.discriminant_analysis import (
    LinearDiscriminantAnalysis,
    QuadraticDiscriminantAnalysis
)

# ------------------------------------------------------------
# EXAMPLE 1
# Binary Classification
# Different Covariances (QDA should win)
# ------------------------------------------------------------
print("\n\nEXAMPLE 1 -----------------------------------------------------")

np.random.seed(42)

n = 2000
p = 15

mu0 = np.zeros(p)
cov0 = np.diag(np.ones(p))

mu1 = np.ones(p) * 2
cov1 = np.diag(np.linspace(1,10,p))

X0 = np.random.multivariate_normal(mu0, cov0, n)
X1 = np.random.multivariate_normal(mu1, cov1, n)

X = np.vstack((X0,X1))
y = np.hstack((np.zeros(n),np.ones(n)))

my_qda = QDA_K_CLASS(X,y)
my_lda = GDA_K_CLASS(X,y)

print("My QDA Accuracy:")
print(my_qda.accuracy(X,y))

print()

print("My LDA Accuracy:")
print(my_lda.accuracy(X,y))

print()

sk_qda = QuadraticDiscriminantAnalysis()
sk_qda.fit(X,y)

print("Sklearn QDA Accuracy:")
print(np.mean(sk_qda.predict(X)==y))

print()

sk_lda = LinearDiscriminantAnalysis()
sk_lda.fit(X,y)

print("Sklearn LDA Accuracy:")
print(np.mean(sk_lda.predict(X)==y))


# ------------------------------------------------------------
# EXAMPLE 2
# 4-Class, 20 Features
# Different Covariance For Every Class
# ------------------------------------------------------------
print("\n\nEXAMPLE 2 -----------------------------------------------------")

np.random.seed(42)

n = 1000
p = 20

means = [
    np.zeros(p),
    np.ones(p)*2,
    np.ones(p)*4,
    np.ones(p)*6
]

covs = [
    np.diag(np.linspace(1,3,p)),
    np.diag(np.linspace(2,5,p)),
    np.diag(np.linspace(1,8,p)),
    np.diag(np.linspace(3,10,p))
]

X = []
y = []

for cls in range(4):

    X_cls = np.random.multivariate_normal(
        means[cls],
        covs[cls],
        n
    )

    X.append(X_cls)

    y.extend([cls]*n)

X = np.vstack(X)
y = np.array(y)

my_qda = QDA_K_CLASS(X,y)
my_lda = GDA_K_CLASS(X,y)

print("My QDA Accuracy:")
print(my_qda.accuracy(X,y))

print()

print("My LDA Accuracy:")
print(my_lda.accuracy(X,y))

print()

sk_qda = QuadraticDiscriminantAnalysis()
sk_qda.fit(X,y)

print("Sklearn QDA Accuracy:")
print(np.mean(sk_qda.predict(X)==y))

print()

sk_lda = LinearDiscriminantAnalysis()
sk_lda.fit(X,y)

print("Sklearn LDA Accuracy:")
print(np.mean(sk_lda.predict(X)==y))


# ------------------------------------------------------------
# EXAMPLE 3
# Nearly Singular Covariance Matrix
# Tests pinv()
# ------------------------------------------------------------
print("\n\nEXAMPLE 3 -----------------------------------------------------")

np.random.seed(42)

n = 3000

z = np.random.randn(n,5)

X = np.hstack([
    z,
    z[:,0:1]*2,
    z[:,1:2]*3,
    z[:,2:3]*5,
    z[:,3:4]*7,
    z[:,4:5]*4
])

y = np.random.randint(0,3,n)

my_qda = QDA_K_CLASS(X,y)
my_lda = GDA_K_CLASS(X,y)

print("My QDA Accuracy:")
print(my_qda.accuracy(X,y))

print()

print("My LDA Accuracy:")
print(my_lda.accuracy(X,y))

print()

sk_qda = QuadraticDiscriminantAnalysis()
sk_qda.fit(X,y)

print("Sklearn QDA Accuracy:")
print(np.mean(sk_qda.predict(X)==y))

print()

sk_lda = LinearDiscriminantAnalysis()
sk_lda.fit(X,y)

print("Sklearn LDA Accuracy:")
print(np.mean(sk_lda.predict(X)==y))


# ------------------------------------------------------------
# EXAMPLE 4
# True Gaussian Data
# QDA assumptions exactly satisfied
# ------------------------------------------------------------
print("\n\nEXAMPLE 4 -----------------------------------------------------")

np.random.seed(42)

p = 20

sizes = [1500,1500,1500]

means = [
    np.random.uniform(-2,2,p),
    np.random.uniform(3,5,p),
    np.random.uniform(-5,-3,p)
]

covs = []

for i in range(3):

    A = np.random.randn(p,p)

    covs.append(
        A @ A.T + np.eye(p)
    )

X = []
y = []

for cls in range(3):

    X_cls = np.random.multivariate_normal(
        means[cls],
        covs[cls],
        sizes[cls]
    )

    X.append(X_cls)

    y.extend([cls]*sizes[cls])

X = np.vstack(X)
y = np.array(y)

my_qda = QDA_K_CLASS(X,y)
my_lda = GDA_K_CLASS(X,y)

print("My QDA Accuracy:")
print(my_qda.accuracy(X,y))

print()

print("My LDA Accuracy:")
print(my_lda.accuracy(X,y))

print()

sk_qda = QuadraticDiscriminantAnalysis()
sk_qda.fit(X,y)

print("Sklearn QDA Accuracy:")
print(np.mean(sk_qda.predict(X)==y))

print()

sk_lda = LinearDiscriminantAnalysis()
sk_lda.fit(X,y)

print("Sklearn LDA Accuracy:")
print(np.mean(sk_lda.predict(X)==y))


# ------------------------------------------------------------
# EXAMPLE 5
# Large Scale Stress Test
# 10,000 samples
# ------------------------------------------------------------
print("\n\nEXAMPLE 5 -----------------------------------------------------")

np.random.seed(42)

p = 20

sizes = [2000,2000,2000,2000,2000]

means = [
    np.random.uniform(-5,-3,p),
    np.random.uniform(-2,0,p),
    np.random.uniform( 1,3,p),
    np.random.uniform( 4,6,p),
    np.random.uniform( 7,9,p)
]

covs = []

for i in range(5):

    A = np.random.randn(p,p)

    covs.append(
        A @ A.T + np.eye(p)
    )

X = []
y = []

for cls in range(5):

    X_cls = np.random.multivariate_normal(
        means[cls],
        covs[cls],
        sizes[cls]
    )

    X.append(X_cls)

    y.extend([cls]*sizes[cls])

X = np.vstack(X)
y = np.array(y)

my_qda = QDA_K_CLASS(X,y)
my_lda = GDA_K_CLASS(X,y)

print("My QDA Accuracy:")
print(my_qda.accuracy(X,y))

print()

print("My LDA Accuracy:")
print(my_lda.accuracy(X,y))

print()

sk_qda = QuadraticDiscriminantAnalysis()
sk_qda.fit(X,y)

print("Sklearn QDA Accuracy:")
print(np.mean(sk_qda.predict(X)==y))

print()

sk_lda = LinearDiscriminantAnalysis()
sk_lda.fit(X,y)

print("Sklearn LDA Accuracy:")
print(np.mean(sk_lda.predict(X)==y))