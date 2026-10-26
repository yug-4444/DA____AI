import numpy as np
from sklearn.linear_model import LogisticRegression
class logistic_regression:#binary classification y= 0 or 1 case
    def __init__(self,x,y):
        self.x_raw=np.array(x)
        if self.x_raw.ndim==1:
            self.x_raw=self.x_raw.reshape(-1,1)
        self.y=np.array(y).reshape(-1,1)
        self.m,self.n=self.x_raw.shape
        self.X=np.c_[np.ones((self.m,1)),self.x_raw]
        self.d=self.n+1
        self.beta=np.zeros((self.d,1))

    def sigmoid(self,z):
        #y->actual whuch is 1 or 0
        #y'=h(x)=sigmoid(B.T X)=sigmoid(z)=1/(1+e^(-z))
        z=np.clip(z,-500,500)
        return 1/(1+np.exp(-z))
    
    def cross_entropy(self,y_pred):
        #as cost fun is= -ylogh-(1-y)log(1-h)
        p_safe=np.clip(y_pred,1e-15,1.0-1e-15)
        return -np.mean(self.y*(np.log(p_safe))+(1-self.y)*np.log(1-p_safe))
    
    def gradient_descent_methord(self,iteration,alpha,lamb):
        for steps in range(iteration):
            y_pred=self.sigmoid(self.X@self.beta)
            gradient=1/self.m*self.X.T@(y_pred-self.y)
            l2_penalize=lamb/self.m*self.beta
            l2_penalize[0,0]=0
            gradient+=l2_penalize
            if np.linalg.norm(gradient)<1e-6:
                print(f"early break in steps:{steps}.")
                break
            self.beta=self.beta-alpha*gradient

    def newton_methord(self,iteration,lamb):
        #q_j:=q_j-(delta_2 l)-1(delta l)
        for steps in range(iteration):
            y_pred=self.sigmoid(self.X@self.beta)
            gradient=1/self.m*self.X.T@(y_pred-self.y)
            l2_penalize=lamb/self.m*self.beta
            l2_penalize[0,0]=0
            gradient+=l2_penalize
            if np.linalg.norm(gradient)<1e-6:
                print(f"early break in steps: {steps}.")
                break
            W=(y_pred*(1-y_pred)).flatten()
            H=1/self.m*self.X.T@(self.X*W[:,None])
            R=np.eye(self.d)
            R[0,0]=0
            H+=lamb/self.m*R
            self.beta=self.beta-np.linalg.pinv(H)@gradient

    def gradient_predict(self,x_i,iteration,alpha,lamb,threshold=0.5):
        self.gradient_descent_methord(iteration,alpha,lamb)
        x_i=np.array(x_i)
        if x_i.ndim==1:
            x_i=x_i.reshape(1,-1)
        X=np.c_[np.ones((x_i.shape[0],1)),x_i]
        prob=self.sigmoid(X@self.beta)
        return (prob>=threshold).astype(int)
    
    def newton_predict(self,x_i,iteration,lamb,threshold=0.5):
        self.newton_methord(iteration,lamb)
        x_i=np.array(x_i)
        if x_i.ndim==1:
            x_i=x_i.reshape(1,-1)
        X=np.c_[np.ones((x_i.shape[0],1)),x_i]
        prob=self.sigmoid(X@self.beta)
        return (prob>=threshold).astype(int)

    def predict_proba(self,x_i):
        x_i=np.array(x_i)
        if x_i.ndim==1:
            x_i=x_i.reshape(1,-1)
        X=np.c_[np.ones((x_i.shape[0],1)),x_i]
        return self.sigmoid(X@self.beta)

    def accuracy(self):
        y_pred=self.sigmoid(self.X@self.beta)
        y_class=(y_pred>=0.5).astype(int)
        return np.mean(y_class==self.y)

#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
# ----------------------
# Generate Training Data
# ----------------------
np.random.seed(42)
m = 10000
n = 5
X = np.random.randn(m, n)
# True model
beta_true = np.array([
    [1.5],   # intercept
    [-2.0],
    [0.8],
    [1.2],
    [-1.0],
    [0.5]
])
X_full = np.c_[np.ones((m,1)), X]
# Probabilities
p = 1 / (1 + np.exp(-(X_full @ beta_true)))
# Binary labels
y = (np.random.rand(m,1) < p).astype(int)

# ----------------------
# Train Your Model
# ----------------------
model = logistic_regression(X, y)
print("Initial Cost:")
print(
    model.cross_entropy(
        model.sigmoid(model.X @ model.beta)
    )
)
model.gradient_descent_methord(
    iteration=5000,
    alpha=0.1,
    lamb=0.1
)
print("\nCost After Training:")
print(
    model.cross_entropy(
        model.sigmoid(model.X @ model.beta)
    )
)
print("\nLearned Beta:")
print(model.beta)

y_pred = model.predict_proba(X)
y_pred = (y_pred >= 0.5).astype(int)

accuracy = np.mean(y_pred == y)

print("Training Accuracy =", accuracy)

X_test = np.array([
    [0.5, -1.2, 0.8, 0.1, -0.4],
    [2.0, 0.5, -1.5, 1.2, 0.7],
    [-1.5, 0.2, 2.1, -0.5, 1.3]
])

print("Probabilities:")
print(model.predict_proba(X_test))

print("\nPredictions:")
print((model.predict_proba(X_test) >= 0.5).astype(int))

clf = LogisticRegression(
    penalty="l2",
    C=10,      # roughly λ=0.1
    max_iter=5000
)

clf.fit(X, y.ravel())

print("Sklearn Accuracy:")
print(clf.score(X, y))

print("True Beta:")
print(beta_true.flatten())

print("\nYour Beta:")
print(model.beta.flatten())

print("\nSklearn Beta:")
print(
    np.concatenate(
        [clf.intercept_, clf.coef_.flatten()]
    )
)

print("============================================================")
print("another stress test")
print("============================================================")
import numpy as np

np.random.seed(42)

# ----------------------
# Large Dataset
# ----------------------
m = 100000
n = 20

X = np.random.randn(m, n)

# True coefficients
beta_true = np.random.randn(n + 1, 1)

# Generate labels from logistic model
X_full = np.c_[np.ones((m,1)), X]

p = 1 / (1 + np.exp(-(X_full @ beta_true)))

y = (np.random.rand(m,1) < p).astype(int)

print("X Shape :", X.shape)
print("y Shape :", y.shape)
model = logistic_regression(X, y)

print("Initial Cost:")
print(
    model.cross_entropy(
        model.sigmoid(model.X @ model.beta)
    )
)

model.gradient_descent_methord(
    iteration=3000,
    alpha=0.1,
    lamb=0.01
)

print("\nFinal Cost:")
print(
    model.cross_entropy(
        model.sigmoid(model.X @ model.beta)
    )
)
y_pred = model.predict_proba(X)

y_class = (y_pred >= 0.5).astype(int)

accuracy = np.mean(y_class == y)

print("\nTraining Accuracy:")
print(accuracy)
from sklearn.linear_model import LogisticRegression

clf = LogisticRegression(
    penalty="l2",
    C=100,          # ~ lambda=0.01
    max_iter=3000
)

clf.fit(X, y.ravel())

print("Sklearn Accuracy:")
print(clf.score(X, y))
print("Your Beta Shape:")
print(model.beta.shape)

print("Sklearn Beta Shape:")
print(1 + clf.coef_.shape[1])

print("\nFirst 10 Coefficients\n")

print("Yours:")
print(model.beta[:10].flatten())

print("\nSklearn:")
print(
    np.concatenate(
        [clf.intercept_, clf.coef_.flatten()]
    )[:10]
)
x_test = np.random.randn(5, 20)

print("Probabilities:")
print(model.predict_proba(x_test))

print("\nClasses:")
print(
    (model.predict_proba(x_test) >= 0.5).astype(int)
)


print("============================================================")
print("another stress test")
print("============================================================")

np.random.seed(42)

m = 10000
n = 20

X = np.random.randn(m, n)

beta_true = np.random.randn(n + 1, 1)

X_full = np.c_[np.ones((m,1)), X]

p = 1/(1+np.exp(-(X_full @ beta_true)))

y = (np.random.rand(m,1) < p).astype(int)
gd_model = logistic_regression(X, y)

initial_loss = gd_model.cross_entropy(
    gd_model.sigmoid(gd_model.X @ gd_model.beta)
)

print("GD Initial Loss =", initial_loss)

gd_model.gradient_descent_methord(
    iteration=8000,
    alpha=0.05,
    lamb=0.01
)

final_loss = gd_model.cross_entropy(
    gd_model.sigmoid(gd_model.X @ gd_model.beta)
)

print("GD Final Loss =", final_loss)

print("GD Accuracy =", gd_model.accuracy())
newton_model = logistic_regression(X, y)

initial_loss = newton_model.cross_entropy(
    newton_model.sigmoid(newton_model.X @ newton_model.beta)
)

print("Newton Initial Loss =", initial_loss)

newton_model.newton_methord(
    iteration=1000,
    lamb=0.01
)

final_loss = newton_model.cross_entropy(
    newton_model.sigmoid(newton_model.X @ newton_model.beta)
)

print("Newton Final Loss =", final_loss)

print("Newton Accuracy =", newton_model.accuracy())
print("True Beta")
print(beta_true.flatten())

print("\nGradient Descent Beta")
print(gd_model.beta.flatten())

print("\nNewton Beta")
print(newton_model.beta.flatten())
print("Index | True | GD | Newton")

for i in range(len(beta_true)):
    print(
        f"{i:2d} | "
        f"{beta_true[i,0]:8.4f} | "
        f"{gd_model.beta[i,0]:8.4f} | "
        f"{newton_model.beta[i,0]:8.4f}"
    )

#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
#=====================================================================================================================================
