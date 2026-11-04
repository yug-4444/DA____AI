import numpy as np
from sklearn.linear_model import LinearRegression ,LogisticRegression ,Lasso ,Ridge 
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis ,QuadraticDiscriminantAnalysis 
from sklearn.naive_bayes import BernoulliNB ,GaussianNB
import sys
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
        
    def bgd_method(self,X,y,alpha=0.001,Threshold_alpha=1000,epoch=1000):
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
                numerator=(gradient.T@gradient).item()
                denominator=(gradient.T@H@gradient).item()
                if denominator >1e-12:
                    alpha=numerator/denominator
                else:
                    alpha=alpha
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

    def sgd_method(self,X,y,alpha=0.001,epoch=1000):
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
                    yi=y[i:i+1,:]
                    gradient=self.compute_gradient(xi,yi)
                    self.beta=self.beta-alpha*gradient

    def mini_bgd_method(self,X,y,alpha_default=0.001,epoch=1000,batch_size=10,Threshold_alpha=1000):
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
        x,y,m,d=self.centralize_and_normalize_data(X,y)
        self.beta=np.zeros((d,1))
        H=self.compute_hessian(x)
        H_inv=np.linalg.pinv(H)
        for steps in range(epoch):
            grad=self.compute_gradient(x,y)
            if np.linalg.norm(grad)<1e-8:
                print(f"newton rapson take {int(steps)} step.\n")
                break
            self.beta-=H_inv@grad

    def fit_method(self,X,y,alpha=0.001,Threshold_alpha=1000,epoch=1000,batch_size=None):
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


#================================================================================================
#================================================================================================
#================================================================================================
#================================================================================================
# Locally Weighted Linear Regression (LWLR)
#------------------------------------------------------------------------------------------------
# Lazy learning algorithm:
# For every query point x_c, a new linear regression model
# is fitted using weights determined by the distance from x_c.
#
# Nearby points:
#       large weights
#
# Distant points:
#       small weights
#
# Gaussian Kernel:
#
# w_i = exp(||x_i - x_c||²/-2σ²)
#       
# Weighted Normal Equation:
#
# β = (XᵀWX)^+ XᵀWy
#
# Prediction:
#
# ŷ_c = x_c β
#
# σ controls locality:
#
# Small σ  -> highly local fit (high variance)
# Large σ  -> smoother/global fit
# σ → ∞    -> Ordinary Least Squares
#
# Complexity:
# A new β is computed for every prediction.
# Training cost is almost zero.
# Prediction is expensive.
#================================================================================================
#================================================================================================
#================================================================================================
#================================================================================================

class LWLR:
    def __init__(self,X,y):
        self.x=np.array(X)
        if self.x.ndim==1:
            self.x=self.x.reshape(-1,1)
        self.y=np.array(y).reshape(-1,1)
        self.m,self.n=self.x.shape
        self.d=self.n+1
        intecept_column_one=np.ones((self.m,1))
        self.x=np.c_[intecept_column_one,self.x]
        self.W=np.eye(self.m)
        self.beta=np.zeros((self.d,1))

    def sample_weighted(self,x_c,sigma):
        x_c=np.array(x_c).reshape(1,-1)
        diff=self.x[:,1:]-x_c
        dist_sq=np.sum(diff**2,axis=1)
        self.W=np.diag(np.exp(-dist_sq/(2*sigma**2)))

    def predict(self,x_c,sigma=1):
        self.sample_weighted(x_c,sigma)
        x_c=np.array(x_c).reshape(1,-1)
        x_c=np.c_[np.ones((1,1)),x_c]
        self.beta=np.linalg.pinv(self.x.T@self.W@self.x)@self.x.T@self.W@self.y
        y_c=x_c@self.beta
        print(f"locally apply linear regression on {x_c}\n to get solution {y_c}.\n")
        return float(y_c)


#================================================================================================
#================================================================================================
#================================================================================================
#================================================================================================
#Logistic Regression
#
# Implemented Features:
#
# Binary Logistic Regression
#   - Batch Gradient Descent (BGD)
#   - Stochastic Gradient Descent (SGD)
#   - Mini-Batch Gradient Descent
#   - Newton-Raphson / IRLS Optimization
#
# Multiclass Classification
#   - One-vs-Rest (OvR)
#   - Softmax Regression (Multinomial Logistic Regression)
#
# Regularization
#   - Unregularized Logistic Regression
#   - L2 Ridge Regularization
#   - Intercept term excluded from regularization
#
# Optimization Enhancements
#   - Feature mean-centering and normalization
#   - Adaptive Hessian-based step-size estimation
#   - Early stopping using gradient norm convergence
#   - Randomized sample shuffling for SGD/Mini-BGD
#
# Numerical Stability Improvements
#   - Sigmoid input clipping to prevent overflow
#   - Stable softmax using max-subtraction trick
#   - Log clipping for cross-entropy computations
#
# Prediction Utilities
#   - Class prediction
#   - Probability prediction
#   - Accuracy evaluation
#
# Implemented entirely using NumPy without machine learning libraries.
# 
#================================================================================================
#================================================================================================
#================================================================================================
#================================================================================================

#bernolli k=2 classes
#methord->newton,bgd,sgd,mini_bgd
#L2(ridge),unregularize
# k classes genral ->softmax(best),one_vs_rest
#there is no closed solution for logistic regression

class logistic_regression:
    def __init__(self,penalty=None,
                lamb=None,
                solver="bgd",version="softmax"):
        self.solver=solver
        self.lamb=lamb
        self.penalty=penalty
        self.beta=None
        self.k_beta={}
        self.soft_beta=None
        self.version=version
        self.mu=None
        self.std=None
        self.diag_l=None
        self.W=None
        self.k_class=[]
        self.k=0

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

    def sigmoid_function(self,z):
        z=np.clip(z,-700,700)
        return 1/(1+np.exp(-z))

    def compute_gradient(self,x,y,beta):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(-1,1)
        y=np.array(y).reshape(-1,1)
        beta=np.array(beta).reshape(-1,1)
        m,d=x.shape
        if self.penalty=="l2":
            return 1/m*x.T@(self.sigmoid_function(x@beta)-y)+self.lamb*self.diag_l@beta
        return 1/m*x.T@(self.sigmoid_function(x@beta)-y)

    def compute_hessian(self,x,beta):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(-1,1)
        m,d=x.shape
        beta=np.array(beta).reshape(-1,1)
        p=self.sigmoid_function(x@beta)
        self.W=np.diag((p*(1-p)).ravel())
        if self.penalty=="l2":
            return 1/m*x.T@self.W@x+self.lamb*self.diag_l
        return 1/m*x.T@self.W@x

    def bgd_method(self,X,y,alpha=0.001,Threshold_alpha=1000,epoch=1000):
        x,y,m,d=self.centralize_and_normalize_data(X,y)#to prevent zig-zag slow approch now princilar axis of contours reduced to 0 to 1 hence fast approch now
        beta=np.zeros((d,1))
        if(d<=Threshold_alpha):
            for steps in range(epoch):
                H=self.compute_hessian(x,beta)
                gradient=self.compute_gradient(x,y,beta)
                if np.allclose(gradient,0,atol=1e-8):
                    print(f"bgd early break in {int(steps)} steps.\n")
                    break
                #since we have less number of fatues we can have most optimal step size at every iteration rather than fixed
                numerator=(gradient.T@gradient).item()
                denominator=(gradient.T@H@gradient).item()
                if denominator >1e-12:
                    alpha=numerator/denominator
                else:
                    alpha=alpha
                beta-=alpha*gradient
        else:
            #use a fixed size step size as caluclation cost high for optimalo at everystep
            if(alpha is None):
                H=self.compute_hessian(x,beta)
                eigenvalues=np.linalg.eigvalsh(H)
                alpha=2/(max(eigenvalues[0],1e-8)+eigenvalues[-1])#in case eigen_min becomes 0 and to keep condition alpha<2/eigen_max
            for steps in range(epoch):
                gradient=self.compute_gradient(x,y,beta)
                if np.allclose(gradient,0,atol=1e-8):
                    print(f"bgd early break in {int(steps)} epoches.\n")
                    break                
                beta-=alpha*gradient
        return beta

    def sgd_method(self,X,y,alpha=0.001,epoch=1000):
        x,y,m,d=self.centralize_and_normalize_data(X,y)#to prevent zig-zag slow approch now princilar axis of contours reduced to 0 to 1 hence fast approch now
        beta=np.zeros((d,1))
        #use a fixed size step size as caluclation cost high for optimalo at everystep
        if(alpha is None):
            H=self.compute_hessian(x,beta)
            eigenvalues=np.linalg.eigvalsh(H)
            eigen_max=max(eigenvalues[-1],1e-8)
            alpha=0.5/eigen_max#in case eigen_min becomes 0 and to keep condition alpha<2/eigen_max 
        for steps in range(epoch):
            if(steps%10==0):
                gradient=self.compute_gradient(x,y,beta)
                if np.linalg.norm(gradient)<1e-7:
                    print(f"sgd early break in {int(steps)} epoches.\n")
                    break                
            indices=np.random.permutation(m)#to prevent ossilation of path in case our data is very sequential in output for train
            for i in indices:
                    xi=x[i:i+1,:]
                    yi=y[i:i+1,:]
                    gradient=self.compute_gradient(xi,yi,beta)
                    beta-=alpha*gradient
        return beta

    def mini_bgd_method(self,X,y,alpha_default=0.001,epoch=1000,batch_size=10,Threshold_alpha=1000):
        x,y,m,d=self.centralize_and_normalize_data(X,y)#to prevent zig-zag slow approch now princilar axis of contours reduced to 0 to 1 hence fast approch now
        if batch_size==m:
            return self.bgd_method(X,y,alpha_default,Threshold_alpha,epoch)
        if batch_size==1:
            return self.sgd_method(X,y,alpha_default,epoch)
        beta=np.zeros((d,1))
        if(alpha_default is None):
            H=self.compute_hessian(x,beta)
            eigenvalues=np.linalg.eigvalsh(H)
            eigen_max=max(eigenvalues[-1],1e-8)
            alpha_default=1/eigen_max
        if batch_size/m>=0.75 and d<=Threshold_alpha:#near bgd so use optimal step 
            for steps in range(epoch):
                if(steps%10==0):
                    g=self.compute_gradient(x,y,beta)
                    if np.linalg.norm(g) < 1e-7:
                        print(f"mini_bgd early break in {int(steps)} epoches.\n")
                        break                
                indices=np.random.permutation(m)
                for start in range(0,m,batch_size):
                    batch_idx=indices[start:start+batch_size]
                    b=len(batch_idx)
                    x_data=x[batch_idx,:]
                    y_data=y[batch_idx,:]
                    H_batch=self.compute_hessian(x_data,beta)
                    gradient=self.compute_gradient(x_data,y_data,beta)
                    numerator=(gradient.T@gradient).item()
                    denominator=(gradient.T@H_batch@gradient).item()
                    if denominator>1e-12:
                        alpha=numerator/denominator
                    else:
                        alpha=alpha_default
                    beta-=alpha*gradient
        else:
            alpha=alpha_default
            for steps in range(epoch):
                g=self.compute_gradient(x,y,beta)
                if np.linalg.norm(g) < 1e-7:
                    print(f"bgd early break in {int(steps)} epoches.\n")
                    break              
                indices=np.random.permutation(m)
                for start in range(0,m,batch_size):
                    batch_idx=indices[start:start+batch_size]
                    b=len(batch_idx)
                    x_data=x[batch_idx,:]
                    y_data=y[batch_idx,:]
                    gradient=self.compute_gradient(x_data,y_data,beta)
                    beta-=alpha*gradient
        return beta

    def newton_method(self,X,y,epoch):
        x,y,m,d=self.centralize_and_normalize_data(X,y)
        beta=np.zeros((d,1))
        for steps in range(epoch):
            H=self.compute_hessian(x,beta)
            H_inv=np.linalg.pinv(H)
            grad=self.compute_gradient(x,y,beta)
            if np.linalg.norm(grad)<1e-8:
                print(f"newton rapson take {int(steps)} step.\n")
                break
            beta-=H_inv@grad
        return beta

    def binary_cross_entropy_cost(self,x,y):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(-1,1)
        y=np.array(y).reshape(-1,1)
        m=x.shape[0]
        x=np.c_[np.ones((m,1)),x]
        h_x=self.sigmoid_function(x@self.beta)
        h_x=np.clip(h_x,1e-15,1-1e-15)
        if(self.penalty=="l2"):
            return -1/m*np.sum(y*np.log(h_x)+(1-y)*np.log(1-h_x))+self.lamb/2*(self.beta.T@self.diag_l@self.beta).item()
        return -1/m*np.sum(y*np.log(h_x)+(1-y)*np.log(1-h_x))
    
    def fit_method(self,X,y,alpha=0.001,Threshold_alpha=1000,epoch=1000,batch_size=None,tol=1e-6):
        if(self.version=="binary"):
            if self.solver=="bgd":
                self.beta=self.bgd_method(X,y,alpha,Threshold_alpha,epoch)
            elif self.solver=="sgd":
                self.beta=self.sgd_method(X,y,alpha,epoch)
            elif self.solver=="mini_batch":
                self.beta=self.mini_bgd_method(X,y,alpha,epoch,batch_size,Threshold_alpha)
            elif self.solver=="newton":
                self.beta=self.newton_method(X,y,epoch)
            else:
                print("use a vaild solver methord -> 1. bgd(default), \n2. sgd, \n3.mini_batch, \n 4.newton\n")
                return None
        elif(self.version=="one_vs_rest"):
            self.one_vs_rest_version(X,y,alpha,Threshold_alpha,epoch,batch_size)
        elif(self.version=="softmax"):
            self.softmax_version(X,y,alpha,epoch,batch_size,tol)
        else:
            print("use a vaild version-> 1. softmax(default), \n2. binary, \n3.one_vs_rest\n")
            return None
        
    def predict_binary(self,x,threshold=0.5):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(1,-1)
        x=(x-self.mu)/self.std
        x=np.c_[np.ones((x.shape[0],1)),x]
        p=self.sigmoid_function(x@self.beta)
        return (p>=threshold).astype(int)

    def predict_proba_binary(self,x):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(1,-1)
        x=(x-self.mu)/self.std
        x=np.c_[np.ones((x.shape[0],1)),x]
        return self.sigmoid_function(x@self.beta)

    def beta_for_class(self,X,y,alpha=0.001,Threshold_alpha=1000,epoch=1000,batch_size=None):
        if self.solver=="sgd":
            return self.sgd_method(X,y,alpha,epoch)
        elif self.solver=="mini_batch":
            return self.mini_bgd_method(X,y,alpha,epoch,batch_size,Threshold_alpha)
        elif self.solver=="newton":
            return self.newton_method(X,y,epoch)
        else:
            return self.bgd_method(X,y,alpha,Threshold_alpha,epoch)

    def one_vs_rest_version(self,x,y,alpha=0.001,Threshold_alpha=1000,epoch=1000,batch_size=None):
        y=np.array(y).reshape(-1,1)
        self.k_class=np.unique(y)
        for k in self.k_class:
            yi=(y==k).astype(int)
            b_k=self.beta_for_class(x,yi,alpha,Threshold_alpha,epoch,batch_size)
            self.k_beta[k]=b_k

    def predict_one_vs_rest(self,x):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(1,-1)
        x=(x-self.mu)/self.std
        x=np.c_[np.ones((x.shape[0],1)),x]
        score_k=[]
        for k in self.k_class:
            score_k.append(self.sigmoid_function(x@self.k_beta[k]))
        scores=np.hstack(score_k)
        indices=np.argmax(scores,axis=1)
        return self.k_class[indices]

    def softmax_version(self,X,y,alpha=0.001,epoch=1000,batch_size=None,tol=1e-6):
        x,y,m,d=self.centralize_and_normalize_data(X,y)
        self.beta_class=np.unique(y)
        self.k=len(self.beta_class)
        self.soft_beta=np.zeros((d,self.k))
        Y=np.zeros((m,self.k))
        for i,j in enumerate(self.beta_class):
            Y[:,i]=(y.ravel()==j).astype(int)
        y=Y
        if self.solver=="sgd":
            self.soft_sgd_method(x,y,alpha,epoch,tol)
        elif self.solver=="mini_batch":
            self.soft_mini_bgd_method(x,y,alpha,epoch,batch_size,tol)
        elif self.solver=="bgd":
            self.soft_bgd_method(x,y,alpha,epoch,tol)
        else:
            print("use a vaild solver for softmax version-> 1.bgd , \n2.sgd, \n3.mini_bgd\n")
    
    def soft_probability(self,x):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(1,-1)
        z=x@self.soft_beta
        z-=np.max(z,axis=1,keepdims=True)
        exp_z=np.exp(z)
        return exp_z/np.sum(exp_z,axis=1,keepdims=True)
    
    def soft_gradient(self,x,y):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(1,-1)
        y=np.array(y)
        if y.ndim==1:
            y=y.reshape(1,-1)
        m=x.shape[0]
        P=self.soft_probability(x)        
        return x.T@(P-y)/m

    def Loss(self,x,y):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(1,-1)
        y=np.array(y)
        if y.ndim==1:
            y=y.reshape(1,-1)
        m=x.shape[0]
        P=self.soft_probability(x)
        loss=-np.sum(y*np.log(P+1e-16))/m
        return loss,P
    
    def soft_bgd_method(self,X,y,alpha=0.001,epoch=1000,tol=1e-6):
        for step in range(epoch):
            grad=self.soft_gradient(X,y)
            if np.linalg.norm(grad) < tol:
                print(f"Converged at epoch {step}")
                break
            self.soft_beta-=alpha*grad

    def soft_sgd_method(self,x,y,alpha=0.001,epoch=1000,tol=1e-6):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(1,-1)
        y=np.array(y)
        if y.ndim==1:
            y=y.reshape(1,-1)
        m=x.shape[0]
        for steps in range(epoch):
            if(steps%10==0):
                g=self.soft_gradient(x,y)
                if np.linalg.norm(g) <tol:
                    print(f"sgd early break in {int(steps)} epoches.\n")
                    break 
            for i in range(m):
                grad=self.soft_gradient(x[i:i+1,:],y[i:i+1,:])
                self.soft_beta-=alpha*grad

    def soft_mini_bgd_method(self,x,y,alpha=0.001,epoch=1000,batch_size=10,tol=1e-6):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(1,-1)
        y=np.array(y)
        if y.ndim==1:
            y=y.reshape(1,-1)
        m=x.shape[0]
        if batch_size==m:
            return self.soft_bgd_method(x,y,alpha,epoch,tol)
        if batch_size==1:
            return self.soft_sgd_method(x,y,alpha,epoch,tol)
        for steps in range(epoch):
            if(steps%10==0):
                g=self.soft_gradient(x,y)
                if np.linalg.norm(g) < tol:
                    print(f"mini_bgd early break in {int(steps)} epoches.\n")
                    break                
            indices=np.random.permutation(m)
            for start in range(0,m,batch_size):
                batch_idx=indices[start:start+batch_size]
                x_data=x[batch_idx,:]
                y_data=y[batch_idx,:]
                grad=self.soft_gradient(x_data,y_data)
                self.soft_beta-=alpha*grad

    def predict_softmax(self,x):
        x=np.array(x)
        if x.ndim==1:
            x=x.reshape(1,-1)
        x=(x-self.mu)/self.std
        x=np.c_[np.ones((x.shape[0],1)),x]
        P=self.soft_probability(x)
        ans=np.argmax(P,axis=1)
        return self.beta_class[ans]

    def accuracy(self,y_true,y_pred):
        y_true=np.array(y_true).ravel()
        y_pred=np.array(y_pred).ravel()
        return np.mean(y_true==y_pred)


#================================================================================================
#================================================================================================
#================================================================================================
#================================================================================================
#DISCRIMINATION ANALYSES

#================================================================================================
#================================================================================================
#================================================================================================
#================================================================================================
#Lda
#qda




#================================================================================================
#================================================================================================
#================================================================================================
#================================================================================================
#NAIVE BAYES

#================================================================================================
#================================================================================================
#================================================================================================
#================================================================================================