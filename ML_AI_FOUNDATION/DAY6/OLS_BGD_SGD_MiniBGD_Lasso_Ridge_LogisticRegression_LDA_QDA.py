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


#================================================================================================
#================================================================================================
#================================================================================================
#================================================================================================
# Linear Regression From Scratch
# ----------------------------------------------------------------------------
# Features Implemented:
#
# 1. Ordinary Least Squares (OLS)
#    - Closed Form Solution (Normal Equation using Moore-Penrose Pseudoinverse)
#    - Batch Gradient Descent (BGD)
#    - Stochastic Gradient Descent (SGD)
#    - Mini-Batch Gradient Descent
#    - Newton-Raphson Optimization
#
# 2. Regularization Support
#    - No Regularization
#    - Ridge Regression (L2)
#         * Closed Form Solution
#         * BGD / SGD / Mini-BGD / Newton
#    - Lasso Regression (L1)
#         * Subgradient Descent Based Optimization
#         * Orthogonal Design Closed-Form Soft Thresholding Case
#
# 3. Optimization Enhancements
#    - Feature Standardization (Zero Mean, Unit Variance)
#    - Intercept Excluded from Regularization
#    - Exact Line Search:
#         alpha = (g^T g) / (g^T H g)
#    - Spectral Learning Rate Initialization
#         alpha ≈ 2/(λ_min + λ_max)  [BGD]
#         alpha ≈ 1/λ_max            [Mini-BGD]
#         alpha ≈ 0.5/λ_max          [SGD]
#    - Early Stopping via Gradient Norm Monitoring
#    - Random Data Shuffling for SGD / Mini-BGD
#
# 4. Numerical Stability Features
#    - Moore-Penrose Pseudoinverse for Singular Systems
#    - Protection Against Zero Feature Variance
#    - Safe Eigenvalue-Based Step Size Selection
#
# 5. Utility Functions
#    - Prediction API
#    - Automatic Data Preparation
#    - Automatic Feature Normalization
#    - Gradient and Hessian Abstractions
#    - Comparison Against sklearn Implementations
#================================================================================================
#================================================================================================
#================================================================================================
#================================================================================================

class linear_regression:
    def __init__(self,penalty=None,
                lamb=None,
                solver="normal"):
        self.solver=solver
        self.lamb=lamb
        self.penalty=penalty
        self.beta=None
        self.mu=None
        self.std=None
        self.diag_l=None

    def prepare_data(self,X,y):
        x=np.array(X)
        if x.ndim==1:
            x=x.reshape(-1,1)
        y=np.array(y).reshape(-1,1)
        m,n=x.shape
        intecept_column_one=np.ones((m,1))
        x=np.c_[intecept_column_one,x]
        d=n+1
        self.diag_l=np.eye(d)
        self.diag_l[0,0]=0
        self.mu=np.zeros((1,n))
        self.std=np.ones((1,n))
        return x,y,m,d

    def centralize_and_normalize_data(self,X,y):
        x=np.array(X)
        if x.ndim==1:
            x=x.reshape(-1,1)
        y=np.array(y).reshape(-1,1)
        m,n=x.shape
        mu_col=np.mean(x,axis=0,keepdims=True)
        self.mu=mu_col
        x=x-mu_col
        sigma_col=np.std(x,axis=0,keepdims=True)
        sigma_col[sigma_col==0]=1
        self.std=sigma_col
        x=x/sigma_col
        intecept_column_one=np.ones((m,1))#we don't normalize the intecept else our y_i also changes since beta_0=sum(y_i)/m fix
        x=np.c_[intecept_column_one,x]
        d=n+1
        self.diag_l=np.eye(d)
        self.diag_l[0,0]=0
        return x,y,m,d

    def compute_gradient(self,x,y):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(-1,1)
        y=np.array(y).reshape(-1,1)
        m,d=x.shape
        if self.penalty=="l2":
            return 1/m*x.T@(x@self.beta-y)+self.lamb*self.diag_l@self.beta
        if self.penalty=="l1":
            return 1/m*x.T@(x@self.beta-y)+self.lamb*np.sign(self.diag_l@self.beta)
        return 1/m*x.T@(x@self.beta-y)

    def compute_hessian(self,x):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(-1,1)
        m,d=x.shape
        if self.penalty=="l1":
            raise ValueError("Newton/Hessian methods not supported for L1.")
        if self.penalty=="l2":
            return 1/m*x.T@x+self.lamb*self.diag_l
        return 1/m*x.T@x
    
    def normal_method(self,X,y):
        x,y,m,d=self.prepare_data(X,y)
        self.beta=np.zeros((d,1))
        if self.penalty=="l2":
            self.beta=np.linalg.pinv(x.T@x+self.lamb*self.diag_l)@x.T@y#alway work even if rank(x)<d due to features collinear or m<d
            return
        elif self.penalty=="l1":
            if not np.allclose(x.T@x,np.eye(d),atol=1e-7):
                raise ValueError("Closed form Lasso requires X.T@X = I")
            self.beta=x.T@y
            self.beta=np.sign(self.beta)*np.maximum(0,np.abs(self.beta)-self.lamb)
            return
        self.beta=np.linalg.pinv(x.T@x)@x.T@y
        
    def bgd_method(self,X,y,alpha=None,Threshold_alpha=1000,epoch=1000):
        x,y,m,d=self.centralize_and_normalize_data(X,y)#to prevent zig-zag slow approch now princilar axis of contours reduced to 0 to 1 hence fast approch now
        self.beta=np.zeros((d,1))
        if(d<=Threshold_alpha and self.penalty!="l1"):
            H=self.compute_hessian(x)
            for steps in range(epoch):
                gradient=self.compute_gradient(x,y)
                if np.allclose(gradient,0,atol=1e-8):
                    print(f"bgd early break in {int(steps)} steps.\n")
                    break
                #since we have less number of fatues we can have most optimal step size at every iteration rather than fixed
                numerator=gradient.T@gradient
                denominator=gradient.T@H@gradient
                alpha=(numerator/denominator).item()
                self.beta=self.beta-alpha*gradient
        else:
            #use a fixed size step size as caluclation cost high for optimalo at everystep
            if(alpha is None and self.penalty!="l1"):
                H=self.compute_hessian(x)
                eigenvalues=np.linalg.eigvalsh(H)
                alpha=2/(max(eigenvalues[0],1e-8)+eigenvalues[-1])#in case eigen_min becomes 0 and to keep condition alpha<2/eigen_max
            if(alpha is None):
                alpha=0.1 
            for steps in range(epoch):
                gradient=self.compute_gradient(x,y)
                if np.allclose(gradient,0,atol=1e-8):
                    print(f"bgd early break in {int(steps)} epoches.\n")
                    break                
                self.beta=self.beta-alpha*gradient

    def sgd_method(self,X,y,alpha=None,epoch=1000):
        x,y,m,d=self.centralize_and_normalize_data(X,y)#to prevent zig-zag slow approch now princilar axis of contours reduced to 0 to 1 hence fast approch now
        self.beta=np.zeros((d,1))
        #use a fixed size step size as caluclation cost high for optimalo at everystep
        if(alpha is None and self.penalty!="l1"):
            H=self.compute_hessian(x)
            eigenvalues=np.linalg.eigvalsh(H)
            eigen_max=max(eigenvalues[-1],1e-8)
            alpha=0.5/eigen_max#in case eigen_min becomes 0 and to keep condition alpha<2/eigen_max 
        if alpha is None:
            alpha=0.1
        for steps in range(epoch):
            if(steps%10==0):
                gradient=self.compute_gradient(x,y)
                if np.linalg.norm(gradient)<1e-7:
                    print(f"sgd early break in {int(steps)} epoches.\n")
                    break                
            indices=np.random.permutation(m)#to prevent ossilation of path in case our data is very sequential in output for train
            for i in indices:
                    xi=x[i:i+1,:]
                    yi=y[i,0]
                    gradient=self.compute_gradient(xi,yi)
                    self.beta=self.beta-alpha*gradient

    def mini_bgd_method(self,X,y,alpha_default=None,epoch=1000,batch_size=10,Threshold_alpha=1000):
        x,y,m,d=self.centralize_and_normalize_data(X,y)#to prevent zig-zag slow approch now princilar axis of contours reduced to 0 to 1 hence fast approch now
        if batch_size==m:
            self.bgd_method(X,y,alpha_default,Threshold_alpha,epoch)
            return
        if batch_size==1:
            self.sgd_method(X,y,alpha_default,epoch)
            return
        self.beta=np.zeros((d,1))
        if(alpha_default is None and self.penalty!="l1"):
            H=self.compute_hessian(x)
            eigenvalues=np.linalg.eigvalsh(H)
            eigen_max=max(eigenvalues[-1],1e-8)
            alpha_default=1/eigen_max
        if alpha_default is None:
            alpha_default=0.1
        if batch_size/m>=0.75 and d<=Threshold_alpha and self.penalty != "l1":#near bgd so use optimal step 
            for steps in range(epoch):
                g=self.compute_gradient(x,y)
                if np.linalg.norm(g) < 1e-7:
                    print(f"mini_bgd early break in {int(steps)} epoches.\n")
                    break                
                indices=np.random.permutation(m)
                for start in range(0,m,batch_size):
                    batch_idx=indices[start:start+batch_size]
                    b=len(batch_idx)
                    x_data=x[batch_idx,:]
                    y_data=y[batch_idx,:]
                    H_batch=self.compute_hessian(x_data)
                    gradient=self.compute_gradient(x_data,y_data)
                    numerator=(gradient.T@gradient).item()
                    denominator=(gradient.T@H_batch@gradient).item()
                    if denominator>1e-12:
                        alpha=numerator/denominator
                    else:
                        alpha=alpha_default
                    self.beta-=alpha*gradient
        else:
            alpha=alpha_default
            for steps in range(epoch):
                g=self.compute_gradient(x,y)
                if np.linalg.norm(g) < 1e-7:
                    print(f"bgd early break in {int(steps)} epoches.\n")
                    break                
                indices=np.random.permutation(m)
                for start in range(0,m,batch_size):
                    batch_idx=indices[start:start+batch_size]
                    b=len(batch_idx)
                    x_data=x[batch_idx,:]
                    y_data=y[batch_idx,:]
                    gradient=self.compute_gradient(x_data,y_data)
                    self.beta-=alpha*gradient

    def newton_method(self,X,y,epoch):
        x,y,m,d=self.prepare_data(X,y)
        self.beta=np.zeros((d,1))
        H=self.compute_hessian(x)
        H_inv=np.linalg.pinv(H)
        for steps in range(epoch):
            grad=self.compute_gradient(x,y)
            if np.linalg.norm(grad)<1e-8:
                print(f"newton rapson take {int(steps)} step.\n")
                break
            self.beta-=H_inv@grad

    def fit_method(self,X,y,alpha=None,Threshold_alpha=1000,epoch=1000,batch_size=None):
        if self.solver=="normal":
            self.normal_method(X,y)
        elif self.solver=="bgd":
            self.bgd_method(X,y,alpha,Threshold_alpha,epoch)
        elif self.solver=="sgd":
            self.sgd_method(X,y,alpha,epoch)
        elif self.solver=="mini_batch":
            self.mini_bgd_method(X,y,alpha,epoch,batch_size,Threshold_alpha)
        elif self.solver=="newton":
            self.newton_method(X,y,epoch)
        else:
            print("use a vaild solver methord -> 1.normal(default), \n2. bgd, \n3. sgd, \n4.mini_batch, \n 5.newton\n")
            return None

    def predict(self,X):
        x=np.array(X)
        if x.ndim==1:
            x=x.reshape(-1,1)
        x=(x-self.mu)/self.std
        x=np.c_[np.ones((x.shape[0],1)),x]
        return x@self.beta

    def compare_sklearn(self,X,y):
        y=np.array(y).reshape(-1,1)
        if self.penalty is None:
            model=LinearRegression()
        elif self.penalty=="l2":
            model=Ridge(alpha=self.lamb)
        elif self.penalty=="l1":
            model=Lasso(alpha=self.lamb,max_iter=10000)
        model.fit(X,y.ravel())
        pred_sklearn=model.predict(X).reshape(-1,1)
        pred_ours=self.predict(X)
        mse=np.mean((pred_sklearn-pred_ours)**2)
        print("Prediction MSE =",mse)