#ordinary least square <==> LINEAR REGRESSION
import numpy as np
from sklearn.linear_model import LinearRegression
#=============================================CLASS========================================================
class linear_regression:
    def __init__(self,x,y):
        self.x=np.array(x)
        self.y=np.array(y)
        if self.x.ndim==1:
            self.x=self.x.reshape(-1,1)
        if self.y.ndim==1:
            self.y=self.y.reshape(-1,1)
        self.n_features=self.x.shape[1]
        self.m_samples=self.x.shape[0]

        one_bais_col=np.ones((self.m_samples,1))
        X=np.c_[one_bais_col,self.x]
        self.beta=np.linalg.inv(X.T@X)@X.T@self.y #self.beta = np.linalg.pinv(X) @ self.y for case when x is not full column rank matrix

    def predict(self,x=None):
        if x is None:
            x=self.x
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(-1,1)
        X=np.c_[np.ones((x.shape[0],1)),x]
        return X@self.beta

    def rss(self):
        y_pred=self.predict()
        error=self.y-y_pred
        return float((error.T@error)[0,0])

    def summary(self):

        print(f"Number of samples : {self.m_samples}")
        print(f"Number of features: {self.n_features}")
        print(f"Intercept (beta_0): {self.beta[0,0]:.4f}")

        for i in range(1, len(self.beta)):
            print(f"beta_{i}: {self.beta[i,0]:.4f}")

        print(f"RSS: {self.rss():.4f}")

#==========================================================================================================================

#raw data
x=np.array([[1],
            [2],
            [3]])
y=np.array([[2],
            [3],
            [6]])
#beta=[b0,b1]T is column vector
#y'=1*b0+x*b1=X beta 
#X=[1 x] in which each 1 and x is a column vector R->nx1
N=x.shape[0]
ones_columns=np.ones((N,1))
X=np.c_[ones_columns,x]

#------------------------------------------------------------------------------------------------
# beta=(X^T X)^(-1)X^T y
# e=y-X beta
# residual sum of square: rss=e^T e
#------------------------------------------------------------------------------------------------

beta=(np.linalg.inv(X.T@X))@(X.T)@y #2x1
e=y-X@beta #nx1
rss=(e.T)@e

print(f"intercept (beta_0) :{float(beta[0,0]):.4f}")
print(f"slope (beta_1) :{float(beta[1,0]):.4f}")
print(f"residual sum of square (rss) :{float(rss[0,0]):.4f}")

#--------------------AUTOMATED GRADER-------------------------------------------
reference_model=LinearRegression()
reference_model.fit(x,y)
np.testing.assert_almost_equal(float(beta[0,0]),float(reference_model.intercept_[0]))
np.testing.assert_almost_equal(float(beta[1,0]),float(reference_model.coef_[0,0]))
print("\n!!!! Successfull !!!!")



x1 = [[1,2],[3,4],[3,6]]
y1 = [2,3,6]

model = linear_regression(x1,y1)
model.predict()
model.predict([[2,3]])
model.summary()