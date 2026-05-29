#---------------------------------------------------------------CONTENTS---------------------------------------------------------------------
#SOLUTION OF SYSTEM OF LINEAR EQUATIONS
#RANK AND NULLITY OF MATRIX
#LU decomposition
#PLU decomposition



#--------------------------------------------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------------------------------------------
#code for gaussian elimination to REF then find unqique, no ,infinite solution case and result

import numpy as np
#GAUSSIAN ELIMINATION 
class LinearSystem:
    def __init__(self, A, b):
        self.a=np.array(A,dtype=float)
        self.b=np.array(b,dtype=float)
        self.n=self.b.size
    
    def solve_and_verify(self):
        #augmented matrix
        aug=np.hstack((self.a,self.b.reshape(-1,1)))
        #(n,n+1)
        for i in range(self.n):
            pivot_i=i+np.argmax(abs(aug[i:,i]))
            aug[[i,pivot_i],:]=aug[[pivot_i,i],:]
            #exchange with max in a column in case orignal i was 0
            if np.isclose(aug[i,i],0):
                continue
            #undesirable situation will result in dimensional reduction but wheather infinite or no solution that can be said for sure so not terminated
            aug[i,:]=aug[i,:]/aug[i,i]#pivot becomes 1
            for j in range(i+1,self.n,1):
                factor=aug[j,i]
                aug[j,:]=aug[j,:]-factor*aug[i,:]
            #now in row echelon form
        #now let check for any zero row and if zero row then there will either be no or infinte solution
        #!!!! it is possible to have 0=0 row first and later get 0=float row which in total represent no solution so we use infinite bool
        infinite=False
        for row_i in range(0,self.n,1):
            if np.allclose(aug[row_i,:self.n],0):
                if np.isclose(aug[row_i,self.n],0):
                    infinite=True
                else:
                    raise ValueError("!!!!!! No solution exists !!!!!!")
        if infinite:
            raise ValueError("!!!!!! infinite solution exists !!!!!!")
        #now solutions
        #Back Substitution
        x=np.zeros(self.n)   #1d array
        for i in range(self.n-1,-1,-1):
            x[i]=aug[i,-1]-np.dot(aug[i,i+1:self.n],x[i+1:])
        
        # Verification
        residual=np.dot(self.a,x)-self.b #Ax-b as we have Ax=b
        print(f"Verification (Ax - b): {residual}")
        if np.allclose(residual,0):
            print("Status: SUCCESS. Manual Gaussian Elimination verified.")
        print("Solution vector x:", x)

# --- Execution ---
#if __name__ == "__main__":
  #  A_input = [[1,-1,2], [-2,2,-4], [3,-3,6]]
  #  b_input = [5,-10,15]
  # system = LinearSystem(A_input, b_input)
    ### Added a try-except block to gracefully handle the ValueErrors
  #   try:
  #      system.solve_and_verify()
  #   except ValueError as e:
  #       print(f"System Check Failed: {e}")
        

#------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------
# Write a method that takes a matrix as input and returns its Rank and nullity
# LU decomposition Your code must return both matrices and include an internal check to verify the math 
# PLU decomposition Your code must return all three matrices and include an internal check to verify the math 
# solving equation through plu and lu 

class MatrixAnalyzer:
    def __init__(self, A):
        self.a=np.array(A,dtype=float)
        self.row=self.a.shape[0]
        self.col=self.a.shape[1]


    def rank_and_null(self):#RANK-NULLITY::: RANK(A)+NULLITY(A)=NUMBER OF COLUMNS
        m=self.a
        r=self.row
        #rank = no. of pivot columns < minimum(no. of rows ,no. of columns)
        if (r>self.col):#for case when number of rows may be greater than number of columns else i excede its possiblity
            r=self.col
        for i in range(r):
            pivot_i=i+np.argmax(abs(m[i:,i]))
            m[[i,pivot_i],:]=m[[pivot_i,i],:]
            if np.isclose(m[i,i],0):
                continue
            m[i,:]=m[i,:]/m[i,i]
            for j in range(i+1,self.row,1):
                factor=m[j,i]
                m[j,:]-=factor*m[i,:]
        #now in REF
        #now lets calculate either number of pivots or either number of nonzero row in REF
        non_zr=0
        for i in range(self.row):
            if not np.allclose(m[i,:],0):
                non_zr+=1
        #number of non zero row represent our rank or total independent direction available
        rank=non_zr
        #nullity=total columns -rank = total number of free variables
        nullity=self.col-rank
        print("RANK :",rank)
        print("NULLITY :",nullity)
    
    def decompose_lu(self):#matrix will be nxn only this rule
        if self.col != self.row:
            raise ValueError("!!!!!! MATRIX SHOULD BE SQUARE NXN !!!!!!")
        n=self.row
        A=self.a.copy() #A(nxn) matrix now well will decompose A=LxU

        #L->lower triangle matrix nxn with constaint of diagonal of 1's ->recipt
        #U->Upper triangle matrix nxn ->ref resultant
        #diagonal of 1's so that resultant LU is not with many combinations but be unique
        #don’t build U directly; you let A evolve into U during elimination, then copy it.

        L=np.eye(n,dtype=float)
        U=np.zeros((n,n),dtype=float)
        #now we will go with Gaussians elimination
        for i in range(n):
            #this is a standard LU decomposition so no row swaps allowed else become PLU
            if np.isclose(A[i,i],0):
                if np.allclose(A[i,:],0):
                    continue
                else:
                    raise ValueError("!!!!!! Principle Minor crashes and zero pivot in b/w non zero rows!!!!!!")
            for j in range(i+1,n,1):
                factor=A[j,i]/A[i,i] #store in L[j,i]
                L[j,i]=factor
                A[j,:]-=factor*A[i,:]
        U=A.copy()
        #check if LxU=A then result fine else fail
        res=np.dot(L,U)
        if not np.allclose(self.a,res):  #compare with orignal matrix not ref one
            raise ValueError("!!!!!error in calculation")
        print("L :\n",L)
        print("U :\n",U)
        print("result is confirmed. with A=LxU\n")
        return L, U
    
    def decompose_Plu(self):#PA=LU  -> A=P'LU where P'=transpose or inverse of P since P is a permutation matrix
        #P is our row excange recipt of nxn 
        #P orignal a Identity matrix as row exchanges during elimination we reflect them in P 
        if self.col!=self.row:
            raise ValueError("!!!!!! MATRIX SHOULD BE SQUARE NXN !!!!!!")
        n=self.row
        orignal_A=self.a.copy()
        A=self.a.copy()

        P=np.eye(n,dtype=float)#row exchange recipt
        L=np.eye(n,dtype=float)#factor subtraction of row recipt
        U=np.zeros((n,n),dtype=float)#REF

        for i in range(n):
            #The Danger of Small Pivots: If your pivot is a tiny fraction (like 0.000001), dividing by it creates massive numbers in the rest of your matrix
            # ENHANCEMENT: Partial pivoting for numerical stability
            exchange=i+np.argmax(abs(A[i:,i]))
                          #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            if np.allclose(A[exchange, i], 0):
                if np.allclose(A[i, :], 0):
                    continue
                raise ValueError("!!!!!! LU decomposition fails due to zero column !!!!!!")
            if exchange != i:#L is filled column wise and U is row wise both alternate 1st U row and L column
                A[[exchange,i],:]=A[[i,exchange],:]
                P[[exchange,i],:]=P[[i,exchange],:]
                #i = 0: No columns exist to the left of the pivot. There is no history to swap. The if i > 0: guard blocks the operation.
                if i>0: #this for no. of col to exchanged during pivot row swap
                    L[[exchange,i],:i]=L[[i,exchange],:i]
                                  #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            for j in range(i+1,n,1):
                factor=A[j,i]/A[i,i]
                L[j,i]=factor
                A[j,:]-=factor*A[i,:]
        U=A.copy()
        P_t=np.transpose(P)
        res=np.dot(np.dot(P_t,L),U)
        if not np.allclose(orignal_A,res):  #or np.allclose(np.dot(P, original_A), np.dot(L, U))
            raise ValueError("!!!!!error in calculation")
        print("P :\n",P)
        print("L :\n",L)
        print("U :\n",U)
        print("result is confirmed. with A=P_t x L x U\n")
        #as well as det(P)=1x(-1)power(no. of times row exchange)
        #det(L)=1 ,det(U)=product of all diaganol elements
        #det(A)=det(U)/det(P)
        return P,L,U
    
    def solve_with_Plu(self,P,L,U,b):#if strict lu decomposition then let P=identity matrix of nxn no changes to it
        #ONLY AFTER decomposition is possible
        n=self.row
        #Ax=b ==> PA=LU ==>A=P'LU ==>PP'=I ==>IM=MI=M ==>===>==> P'LUx=b =>PP'LUx=Pb => LUx=Pb
        #Ux= y =>SOLVE 1ST Ly=Pb AND GET y ==> THEN SOLVE Ux=y AND GET x
        #so first forward substitution and then backward substitution
        x=np.zeros(n,dtype=float)
        y=np.zeros(n,dtype=float)
        #replace Ux with y
        b=np.dot(P,b)
        for i in range(n):#forward sub for y
            y[i]=b[i]-np.dot(L[i,:i],y[:i]) #L[i,i]=1 fix
        for i in range(n-1,-1,-1):#backward sub for x
            if np.isclose(U[i, i], 0):
                raise ValueError("!!!!!! Singular system so check for infinite or no solution as now we have a free variable !!!!!")
            x[i]=(y[i]-np.dot(U[i,i+1:],x[i+1:]))/U[i,i]
        print("Solution :",x)  #O(n^2) opteration now each time for Ax=b calculation when P,L,U already known
        return x





#------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------
