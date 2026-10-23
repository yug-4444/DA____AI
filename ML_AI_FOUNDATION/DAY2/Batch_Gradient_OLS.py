import numpy as np
from sklearn.linear_model import LinearRegression
X_raw=np.array([[1.0],
                [2.0],
                [3.0],
                [4.0]])#4samples and 1 feature
y=np.array([[3.0],
            [5.0],
            [7.0],
            [9.0]])
m=X_raw.shape[0]
n=X_raw.shape[1]
d=n+1
col_1=np.ones((m,1))
X=np.c_[col_1,X_raw]
#hyperparametes and initalization
beta=np.zeros((d,1))
alpha=0.1
iterations=500
#J(B)=1/2m(XB-Y)T (XB-Y)=1/2m eT e
#delta J(B)=1/m XT (XB-Y)=1/m XT e =1/mXTXB-1/mXTY=HB-1/mXTY
#delta_2 J(B)=H=hessian curvature matrix=1/m XT X

for step in range(iterations):
    #y_pred=XB=b0*1+b1*x1.....
    y_pred=X@beta
    # #error=e=y_pred-y_actual
    error=y_pred-y
    gradient=1/m*(X.T)@error
    beta=beta-alpha*gradient
print(f"GD intercept->beta_0 :{float(beta[0,0]):.4f}\n")
print(f"GD slope->beta_1 :{float(beta[1,0]):.4f}")
print("now lets see using buildin function")
model=LinearRegression().fit(X_raw,y)
np.testing.assert_almost_equal(float(beta[0,0]),float(model.intercept_[0]),decimal=3)
np.testing.assert_almost_equal(float(beta[1,0]),float(model.coef_[0,0]),decimal=3)
print("\nSuccess: Your Batch Gradient Descent converged to the exact OLS parameters!")

#-------------------------------lets make a general class-----------------------------------------------------------------
#---------------------------------------------------------------------------------------------------------------------------------------------------------------
class Batch_GD_OLS:
    def __init__(self,x,y):
        self.x=np.array(x)
        if self.x.ndim==1:
            self.x=self.x.reshape(-1,1)
        self.y=np.array(y).reshape(-1,1)
        self.m,self.n=self.x.shape
        self.d=self.n+1
        self.X=np.c_[np.ones((self.m,1)),self.x]
        self.beta=np.zeros((self.d,1))
        self.H=1/(self.m)*(self.X.T)@(self.X)
    
    def error(self):
        y_pred=self.X@self.beta
        return y_pred-self.y
    
    def best_alpha_small_d(self,g):
        #gtg/gtHg work good for small dataset but problem arrises for large dataset as largespace and opertaions for time XTX
        return (((g.T)@g)[0,0])/((g.T @ self.H @ g)[0,0])
    
    def best_alpha_large_d(self):
        #0<alpha<2/lambda(max)(of H)
        eigenvalue=np.linalg.eigvalsh(self.H)#return sorted order and works only for symmetric matrix
        #chose 1.5/eigen_max as i makes (1-alpha*eigen) -ve which allows it to mave zig-zag and coverge eventuall
        return 1.5/eigenvalue[-1]
    
    def process(self):
        tol=1e-8
        iterations=1000
        if self.d<1000:
            for steps in range(iterations):
                gradient=1/self.m*(self.X.T)@(self.error())
                if np.linalg.norm(gradient)<tol:
                    print(f"early convergence in steps:{steps}\n")
                    break
                alp_opt=self.best_alpha_small_d(gradient)
                self.beta=self.beta-alp_opt*gradient
        else:
            alp_fix=self.best_alpha_large_d()
            for steps in range(iterations):
                gradient=1/self.m*(self.X.T)@(self.error())
                if np.linalg.norm(gradient)<tol: #or np.allclose(gradient,0,atol=tol)
                    print(f"early convergence in steps:{steps}\n")
                    break
                self.beta=self.beta-alp_fix*gradient
    
    def validate_check(self):
        print("lets check wheather our gradient descent result satisfy!!!\n")
        model=LinearRegression().fit(self.x,self.y)
        np.testing.assert_almost_equal(float(self.beta[0,0]),float(model.intercept_[0]),decimal=3)
        for i in range(1,self.d,1):
            np.testing.assert_almost_equal(float(self.beta[i,0]),float(model.coef_[0,i-1]),decimal=3)
        print("testing succesfull!!!!!!\n")
    
    def summary(self):
        print(f"Samples   : {self.m}")
        print(f"Features  : {self.n}")
        print(f"Parameters: {self.d}")
        print("\nCoefficients:")
        print(self.beta)

# Small d:
#   Uses exact line search alpha = (g^T g)/(g^T H g)
#
# Large d:
#   Uses fixed alpha = 1.5/lambda_max(H)
#   to avoid repeated expensive line-search computations.
#----------------------------------------------------------------------------------------------------------------------------
#----------------------------example------------------------------
print("lets check clas for a example\n")
X = np.array([
    [1, 2, 1],
    [2, 1, 3],
    [3, 0, 2],
    [4, 2, 1],
    [5, 1, 4],
    [6, 3, 2],
    [7, 2, 5],
    [8, 4, 3],
    [9, 3, 6],
    [10, 5, 4]
], dtype=float)

y = np.array([
    5 + 2*1 - 3*2 + 4*1,
    5 + 2*2 - 3*1 + 4*3,
    5 + 2*3 - 3*0 + 4*2,
    5 + 2*4 - 3*2 + 4*1,
    5 + 2*5 - 3*1 + 4*4,
    5 + 2*6 - 3*3 + 4*2,
    5 + 2*7 - 3*2 + 4*5,
    5 + 2*8 - 3*4 + 4*3,
    5 + 2*9 - 3*3 + 4*6,
    5 + 2*10- 3*5 + 4*4
], dtype=float)

print(y)
model = Batch_GD_OLS(X, y)
model.process()
print(model.beta)
model.validate_check()
model.summary()

print("another example used!!!!\n")
np.random.seed(42)
m = 10000
n = 100
X = np.random.randn(m, n)
beta_true = np.random.randn(n + 1, 1)
noise = 0.1 * np.random.randn(m, 1)
y = np.c_[np.ones((m,1)), X] @ beta_true + noise
model = Batch_GD_OLS(X, y)
model.process()
coef_error = np.linalg.norm(model.beta - beta_true)
print(f"Coefficient Error = {coef_error:.6e}")
model.validate_check()

print("another example used!!!!\n")
np.random.seed(42)
m = 10000
n = 1001
X = np.random.randn(m, n)#generates zero-mean, unit-variance independent columns
beta_true = np.random.randn(n + 1, 1)
noise = 0.1 * np.random.randn(m, 1)
y = np.c_[np.ones((m,1)), X] @ beta_true + noise
model = Batch_GD_OLS(X, y)
model.process()
coef_error = np.linalg.norm(model.beta - beta_true)
print(f"Coefficient Error = {coef_error:.6e}")
model.validate_check()