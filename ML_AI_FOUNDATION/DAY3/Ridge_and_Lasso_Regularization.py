import numpy as np
from sklearn.linear_model import Ridge,Lasso
class Ridge_and_Lasso:
    #assume feature are not constant and uncoreelated
    # Assuming all features are standardized,
    # uncorrelated and non-constant:
    def __init__(self,x,y):
        self.X_raw=np.array(x)
        if self.X_raw.ndim==1:
            self.X_raw=self.X_raw.reshape(-1,1)
        self.y=np.array(y).reshape(-1,1)
        self.m,self.n=self.X_raw.shape
        #but we know that the X_raw features [x1,x2,...,xn] must each we centralized and standardize
        #we don't centralize the intecept column of vector 1 else it becmomes vector 0
        #lets assume our features to be uncorrelated
        x_col_mu=np.mean(self.X_raw,axis=0)
        x_col_sigma=np.std(self.X_raw,axis=0)
        if np.any(x_col_sigma == 0):
            raise ValueError("Constant feature detected.")
        self.X_raw=(self.X_raw-x_col_mu)/x_col_sigma
        self.d=self.n+1
        self.X=np.c_[np.ones((self.m,1)),self.X_raw]
        #now we have X=[1,x1,x2...,xn] feature with intercept column of 1's
        #now in 1/m X.T X we have 1/m 1.1=1 ,1/m 1.xi=0 ,1/m xi.xi=1 ,1/m xi.xj=0 (uncorrealated)
        # Since features are standardized and assumed uncorrelated:
        # (1/m) X.T @ X = I
        # equivalently X.T @ X = mI
        self.beta_ridge=np.zeros((self.d,1))
        self.beta_lasso=np.zeros((self.d,1))
        self.xt_x=self.X.T@self.X
        self.beta_ols=(np.linalg.pinv(self.xt_x)@self.X.T@self.y).reshape(-1,1)

    #==============================================================================================
    #OLS----------------------------------------------------- minimize RSS
    #Beta_ols=(X.T@X)-1 X.T Y
    #it may have issues when X.T X is non-invertible eigenvalue_j our u_j can become 0

    #==============================================================================================
    #RIDGE----------------------------------------------------- minimize RSS under constraint summation(beta_j^2)<=t
    #Beta_ridge=(X.T@X+lamb.I)-1 X.T Y 
    #Beta_ridge=(m*Beta_ols)/(m+lamb) in case when we have XT@X=mI
    #in it X.T@X+lamb.I is always invertible as eigenvalue_j our u_j+lamb then >0
    #one of the major reason
    #it can only reduce the parameters near to zero . no. of parameters in final are equal to d

    #==============================================================================================
    #LASSO----------------------------------------------------- minimize RSS under constraint summation(|beta_j|)<=t
    #Beta_lasso=sign(Beta_ols)*maximum(0,|Beta_ols|-lamb/m) in case when we have XT@X=mI
    #it can reduce the paramters to exact zero . so number of parameter can be reduced from d to less than d

    def process(self,lamb):
        print("L2->Ridge regulation!!!!!!!!!!!!!\n")
        P=np.eye(self.d)
        P[0,0]=0.0
        M=self.xt_x+lamb*P
        print(f"Determinant of X.T@X+lamb.I : {float(np.linalg.det(M)):.4f} (INVERTIBLE)\n")
        self.beta_ridge=np.linalg.pinv(M)@self.X.T@self.y
        check_beta_ridge=self.beta_ols.copy()
        check_beta_ridge[1:]*=(self.m)/(self.m+lamb)
        if np.allclose(self.beta_ridge,check_beta_ridge,atol=1e-8):
            print("beta_ridge are verified\n")
        print(f"print intercept is {float(self.beta_ridge[0,0]):.4f} and check of beta_0 is {float(np.sum(self.y)/self.m):.4f}.\n")
        print(f"parameters :{self.beta_ridge}")

        print("L1->lasso regulation!!!!!!!!!!!!!")
        self.beta_lasso=self.beta_ols.copy()
        self.beta_lasso[1:]=np.sign(self.beta_ols[1:])*np.maximum(0,np.abs(self.beta_ols[1:])-lamb/self.m)
        print(f"parameters :{self.beta_lasso}")
    def check_and_verify(self, lamb):
        print("Let's verify Ridge\n")
        ridge_model = Ridge(alpha=lamb)
        ridge_model.fit(self.X_raw, self.y.ravel())
        print("Custom Ridge intercept:", self.beta_ridge[0, 0])
        print("Sklearn Ridge intercept:", ridge_model.intercept_)
        print("Custom Ridge coefficients:",self.beta_ridge[1:].flatten())
        print("Sklearn Ridge coefficients:",ridge_model.coef_)
        
        np.testing.assert_allclose(self.beta_ridge[0, 0],ridge_model.intercept_,atol=1e-4)
        np.testing.assert_allclose(self.beta_ridge[1:].flatten(),ridge_model.coef_,atol=1e-4)
        print("Ridge verified successfully!\n")
        print("Let's verify Lasso\n")
        lasso_model = Lasso(alpha=lamb / self.m,max_iter=100000,tol=1e-10)
        lasso_model.fit(self.X_raw, self.y.ravel())
        print("Custom Lasso coefficients:",self.beta_lasso[1:].flatten())
        print("Sklearn Lasso coefficients:",lasso_model.coef_)
        print("Custom Lasso nonzero features:",np.count_nonzero(np.abs(self.beta_lasso[1:]) > 1e-8))
        print("Sklearn Lasso nonzero features:",np.count_nonzero(np.abs(lasso_model.coef_) > 1e-8))
        print("\nNote: Lasso coefficients may differ because "
              "the custom soft-thresholding formula assumes "
              "orthogonal features."
              )

import numpy as np

np.random.seed(0)

m = 2000
n = 6

X = np.random.randn(m, n)

beta_true = np.array([
    5,      # intercept
    8,
    -5,
    3,
    0.05,   # tiny
    0.01,   # tiny
    0       # useless
]).reshape(-1,1)

y = np.c_[np.ones((m,1)), X] @ beta_true
y += 0.1*np.random.randn(m,1)

model = Ridge_and_Lasso(X, y)

model.process(lamb=100)

model.check_and_verify(lamb=100)