#---------------------------------------------------------------CONTENTS---------------------------------------------------------------------
#SOLUTION OF SYSTEM OF LINEAR EQUATIONS
#RANK AND NULLITY OF MATRIX



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

class MatrixAnalyzer:
    def __init__(self, A):
        self.a=np.array(A,dtype=float)
        self.row=self.a.shape[0]
        self.col=self.a.shape[1]
    #RANK-NULLITY::: RANK(A)+NULLITY(A)=NUMBER OF COLUMNS
    def rank_and_null(self):
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

#-------------execute--------------
#if __name__=="__main__":
#    A=[[1, -2,  3],[2, -3,  5],[1,  1,  0]]
#    system=MatrixAnalyzer(A)
#    system.rank_and_null()
        

#------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------
