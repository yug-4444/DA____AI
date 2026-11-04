#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------LINEAR_ALGEBRA----------------------------------------------------------------------------------------
#----------CONTENT --------no inbuilt library function use for automatic martix or vector calculation
#gaussian elimnation mxn and determinant
#inverse of matrix 
#rank and nullity of matrix
#linear independent or dependent along with genrating set
#LU and PLU decomposition along with solving equation
#trace and determinant
#LDU AND PAP^T=LDL^T
#surviving subspace
#eigenvalue and eigenvector manullay using Faddeev-LeVerrier not QR algorithum
#matrix diagonalization engine that handles everything from eigenvalue extraction and null-space analysis to defect detection and basis inversion
#solve matrix power A^n using diagonalization 
#SVD
#PseudoInverse
#rank compresssion
#Symmetric positive definite for hessian matrix identification
#Cholesky decomposition and its use in linerar regression
#projection matrix and find projected shadow
#L_p,L_1,L_2,L_infinity norms
#Gram-Schmidt Orthogonalization
#QR Algorithum to find eigenvalues and linaer regression
#Untwist bowls

import numpy as np
class LinearSystem:
    def __init__(self,A,b):
        self.a=np.array(A,dtype=float)
        self.b=np.array(b,dtype=float)
        # Ax=b -> (mxn)x(nx1)=(mx1)
        self.m,self.n=self.a.shape
    def __GassianElemination__(self):#for mxn matrix not just square matrix bet det only in case of square matrix
        aug=np.hstack((self.a,self.b.reshape(-1,1)))
        if(self.m==self.n):
            det=1
            swap=0
        else:
            det=None
        curr_row=0
        pivots=0
        for col in range(self.n):
            if(curr_row>=self.m):
                break
            pivot_i=curr_row+np.argmax(abs(aug[curr_row:,col]))
            aug[[curr_row,pivot_i],:]=aug[[pivot_i,curr_row],:]
            if np.isclose(aug[curr_row,col],0) :#if this happens then unique solution impossible
                continue
            pivots+=1
            if pivot_i!=curr_row:
                swap+=1
            if not det is None:
                det*=aug[curr_row,curr_row]
            aug[curr_row,:]/=aug[curr_row,col]
            for j in range(curr_row+1,self.m,1):
                factor=aug[j,col]
                aug[j,:]-=aug[curr_row,:]*factor
            curr_row+=1
        if self.m<self.n:#there will definately be some free variables
            infinity=True#or use pivots<self.n
        else:
            infinity=False
        #now check for zero rows keep in mind when a 0=0 or nonzero rows come then that means that row below them must also be of same type i.e no pivots will come from either of them
        for i in range(self.m):
            if np.allclose(aug[i,:self.n],0):
                if np.isclose(aug[i,self.n],0):
                    infinity=True
                else:
                    raise ValueError("NO SOLUTION POSSIBLE")
        if infinity and pivots<self.n:#specifically for case where rows>col where unique , no and infinite solution possible
            raise ValueError("INFINITE SOLUTIONS")
        x=np.zeros(self.n)
        for i in range(self.n-1,-1,-1):#since we reach this point it means unique solution exists that means we will have our pivots for each col that will be in the first n rows
            x[i]=aug[i,self.n]-np.dot(aug[i,i+1:self.n],x[i+1:])
        residual=np.dot(self.a,x)-self.b
        if not np.isclose(residual,0):
            raise ValueError("CALUCULATION ERROR")
        print("PROCESS SUCESSFULL")
        if not det is None:
            det=det*(-1)**swap
            print("For Square matrix: ",det)
        print("solution x:",x)
        return x


class MatrixAnalyzer:
    def __init__(self,A,b):
        self.a=np.array(A,dtype=float)
        self.b=np.array(b,dtype=float)
        # Ax=b -> (mxn)x(nx1)=(mx1)
        self.m,self.n=self.a.shape
    
    def inverse(self):#also known as undo button for a square matrix where det is not equals to zero
        if(self.n!=self.m):
            print("MATRIX A IS NOT A SQUARE MATRIX ")
            return None
        n=self.n
        identity=np.eye(n)
        aug=np.hstack((self.a,identity))
        #[A|I]->[I|A inv] by rref methord
        curr_row=0
        for col in range(0,n,1):
            if(curr_row>=self.m):
                break
            pivot_row= curr_row+np.argmax(abs(aug[curr_row:,col]))
            aug[[curr_row,pivot_row],:]=aug[[pivot_row,curr_row],:]
            if np.isclose(aug[curr_row,col],0):
                print("DETEMINANT BECOMES 0 . AND INFORMATION IS LOST DUE TO ACTION OF SQUARE MATRIX A.")
                return None
            aug[curr_row,:]/=aug[curr_row,col]#well if we reach here the col==curr_row everytime
            for j in range(curr_row+1,n,1):
                factor=aug[j,col]
                aug[j,:]-=aug[curr_row,:]*factor
            curr_row+=1
        #if reach till here then it means all digonal elements are non-zero
        for i in range(n-1,-1,-1):
            for j in range (i-1,-1,-1):
                factor=aug[j,i]
                aug[j,i:]-=factor*aug[i,i:]
        ans=aug[:,n:]
        print("inverse matrix :",ans)
        return ans

    def rank_and_nullity(self):
        #null theorm : rank(a)+null(a)=no. of colmns of a which is no. of directions given
        #during gaussian elemination total count of pivots or total count of non-zero rows
        a=self.a.copy()
        pivots=0
        curr_row=0
        for col in range(self.n):
            if(curr_row>=self.m):
                break
            poivot_row=curr_row+np.argmax(abs(a[curr_row:,col]))
            a[[curr_row,poivot_row],:]=a[[poivot_row,curr_row],:]
            if np.isclose(a[curr_row,col],0):
                continue
            pivots+=1
            a[curr_row,:]/=a[curr_row,col]
            for j in range(curr_row+1,self.m,1):
                factor=a[j,col]
                a[j,:]-=factor*a[curr_row,:]
            curr_row+=1
        rank=pivots
        null=self.n-rank
        print("RANK :",rank)
        print("NULL:",null)
        return {"RANK":rank,"NULL":null} #retuen a dictionary    

    def dependence_and_genrating_set(self):
        #consider A as a set of directonal vectors [v1,v2,v3,.....,vn]
        #linear combination sumation(w_i*v_i)=0 for a trival sol w_i=0 and if
        #no non trival sol then independent else dependent also if dependent we can extract those independet set and return it so that it is minmal gentate set of that subspace 
        pivots_col=[]
        curr_row=0
        a=self.a.copy()
        for col in range(self.n):
            if curr_row>=self.m:
                break
            pivot_row=curr_row+np.argmax(abs(a[curr_row:,col]))
            a[[curr_row,pivot_row],:]=a[[pivot_row,curr_row],:]
            if np.isclose(a[curr_row,col],0):
                continue
            pivots_col.append(col)
            a[curr_row,:]/=a[curr_row,col]
            for j in range(curr_row+1,self.m,1):
                factor=a[j,col]
                a[j,:]-=factor*a[curr_row,:]
            curr_row+=1
        if len(pivots_col)==self.n:
            print("LINEAR INDEPEDENT SET OF VECTOR.\nValid GENRATING SET OF BASIS for subspace")
            return True
        print("linear dependent set so can't be basis\n")
        print("this subset from set of vectors are valid independent set :",pivots_col)
        return False

    def LU_decomposition(self):
        #A=LU form so that AX=b_i where i is milllions of time is optimally solved
        #AX=B ->LUX=B ->UX=Y ->LY=B --->NOW ONLY REQUIRED BACK AND FORWARD SUB TIME O(N^2)
        #CALCULATION OF LU FOR FIRST TIME WILL TAKE O(N^3) BUT LATER EACH TIME O(N^2) ---- SAVES TIME
        #LU is only valid for square matrix in which it doesn't matter wheater out det is 0 or not 
        #what matter is the principle minor Aii from top left till i=n-1 not n
        #benifit of principle minor is that at the moment which i's principle minor becomes zero that means the pivot at bottom right side becomes zero
        #Lu decompostion disallows row swap 
        #if zero in middle then it fails as zero is only allowed to be at bottom rows
        #L->lower traingle matrix nxn with all digonals to be 1 it record history like row2=row2-3row1 then in 3 is stored in L[2,1]
        #U->upper triangle matirx nxn which store its state after ref 
        if(self.m!=self.n):
            print("VALID ONLY FOR SQUARE MATRIX\n")
            return None
        n=self.m
        L=np.eye(n)
        U=self.a.copy()
        curr_row=0
        for col in range(n):
            if np.isclose(U[curr_row,col],0):#col==cur_row
                print("Zero in middle and row swap restriced as just LU alone can't store full recipt so failed\n")
                return None
            for j in range(curr_row+1,n,1):
                factor=U[j,col]/U[curr_row,col]
                L[j,col]=factor
                U[j,:]-=U[curr_row,:]*factor
            curr_row+=1
        if not np.allclose(self.a,np.dot(L,U)):
            raise ValueError("ERROR IN CALCULATION\n")
        print("RESULT VERFIED A=LxU\n")
        return {"L":L,"U":U}

    def PLU_decomposition(self):
        #when Pinciple minor becomes 0 in middle we can swap row hence making that principle minor non-zero 
        #AX=B ->PA=LU ->A=P'LU ->P'LUX=B ->LUX=PB ->UX=Y ->LY=B'  X'=inverse of X  since P is idendity matrix its inverse is equal to its transpose
        #just make sure whenever row swap occures it should also be reflected onto L 
        #P is our permutation matrix that store information about row swap
        if(self.m!=self.n):
            print("VALID ONLY FOR SQUARE MATRIX\n")
            return None
        n=self.m
        P=np.eye(n)
        L=np.eye(n)
        U=self.a.copy()
        curr_row=0
        swap=0
        det_u=1
        for col in range(n):
            #The Danger of Small Pivots: If your pivot is a tiny fraction (like 0.000001), dividing by it creates massive numbers in the rest of your matrix
            #Partial pivoting brings for numerical stability
            pivot_row=curr_row+np.argmax(abs(U[curr_row:,col]))
            if pivot_row!=curr_row:
                swap+=1
                U[[curr_row,pivot_row],:]=U[[pivot_row,curr_row],:]
                if col>0:#else if col =0 then there will be problemin reaching col -1 from 0 which is invalid
                    L[[curr_row,pivot_row],:col]=L[[pivot_row,curr_row],:col]#this will maintain diagnol to be 1
                P[[curr_row,pivot_row],:]=P[[pivot_row,curr_row],:]
            if np.isclose(U[curr_row,col],0):
                curr_row+=1
                continue
            det_u*=U[curr_row,col]
            for j in range(curr_row+1,n,1):
                factor=U[j,col]/U[curr_row,col]
                L[j,col]=factor
                U[j,:]-=U[curr_row,:]*factor
            curr_row+=1
        if not np.allclose(np.dot(P,self.a),np.dot(L,U)):
            raise ValueError("ERROR IN CALCULATION\n")
        #we can also calculate det ---> det(P)xdet(A)=det(L)xdet(U) and we know det(L)=1
        #det(P)=1x(-1)**swap and det(U)=dignol elements
        det=det_u*(-1)**swap
        print("DETERMINANT OF A :",det)
        print("RESULT VERFIED PA=LxU\n")
        return {"L":L,"U":U,"P":P,'det':det}

    def solve_using_PLU(self):
        if(self.m!=self.n):
            print("VALID ONLY FOR SQUARE MATRIX\n")
            return None
        data=self.PLU_decomposition()
        P=data['P']
        L=data['L']
        U=data['U']
        n=self.m
        #O(N^2)time
        #P'=P^T -> AX=B ->P'LUX=B ->LUX=PB ->LUX=b'
        b=np.dot(P,self.b)
        #LY=b solve using forward sub and get Y and after solve Y for X using back substitution where Y=UX
        y=np.zeros(n)
        for i in range(n):
            y[i]=b[i]-np.dot(L[i,:i],y[:i])
        x=np.zeros(n)
        for i in range(n-1,-1,-1):
            x[i]=(y[i]-np.dot(U[i,i:],x[i:]))/U[i,i]
        print("solution : ",x)
        return x
    
    def calculate_trace(self):#trace is only valid for a square matrix
        if self.m!=self.n:
            print("VALID ONLY FOR SQUARE MATRIX")
            return None
        n=self.m
        trace=0#sum of all diaganol elements
        for i in range(n):
            trace+=self.a[i,i]
        return trace
    
    def calculate_determinant(self):
        if(self.m!=self.n):
            print("VALID ONLY FOR SQUARE MATRIX\n")
            return None
        data=self.PLU_decomposition()
        return data['det']
    
    def LDU_symmetric(self):
        #PAP^T =LDU =LDL^T =U^TDU  we have to use PAP^T to maintain the symmetry else problem
        n=self.m
        u=self.a.copy()
        #u^T=l so to save computation time ignore l for now 
        p=np.eye(n)
        d=np.zeros((n,n))
        #we just have to make sure all pivots along the diagnol through row swaps
        #if any zero pivots then push then to bottom
        curr_row=0
        for col in range(n):
            #partial pivot will fail as PAP^T will only allow diagnol elements to swap wit each other and non-diagnol elements are trapped
            pivot_i=curr_row
            #!!!!!!!!!!!!!!every time after elemination submatrix below will still matian its symmetric not symetric full matrix but submatrix
            for i in range(curr_row+1,n,1):#we get max diagnol element for exchange
                if abs(u[i,i])>abs(u[curr_row,curr_row]):
                    pivot_i=i
            if pivot_i!=curr_row:
                u[[curr_row,pivot_i],:]=u[[pivot_i,curr_row],:]
                u[:,[col,pivot_i]]=u[:,[pivot_i,col]]
                p[[curr_row,pivot_i],:]=p[[pivot_i,curr_row],:]
            d[curr_row,col]=u[curr_row,col]#curr_row=col
            u[curr_row,:]/=u[curr_row,col]#now diagnol of u will also be 1
            #all strech/compress will be bore by d alone
            for j in range(curr_row+1,n,1):
                factor=u[j,col]
                u[j,:]-=u[curr_row,:]*factor#don't do for col eles in end it will just becone diagnol matrix that we don't want
            curr_row+=1
        p_t=np.transpose(p)
        l=np.transpose(u)
        #PAP^T=LDU=LDL^T=U^TDU
        if not np.allclose(np.dot(p,np.dot(self.a,p_t)),np.dot(l,np.dot(d,u))):
            print("CALCULATION ERROR\n")
            return None
        print("RESULT VERIFIED PAP^T=LDU")
        #l is lower and u is upper triangle matrix where both responsible puerly for shear
        #d is pure strech and compress matrix along diagnol reponsible puerly for strech along orignal axes
        #A is suerly a non-symmetric matrix since we reach here
        return {'P':p,'P^T':p_t,'L':l,'U':u,'D':d}

    def LDU_genral(self):
        if(self.m!=self.n):
            print("VALID ONLY FOR SQUARE MATRIX\n")
            return None
        n=self.m
        sym=True #check for symmetric matrix
        for i in range(n):
            for j in range(n):
                if i!=j and self.a[i,j]!=self.a[j,i]:
                    sym=False
        if sym:
            return self.LDU_symmetric()
        #PA=LDU 
        u=self.a.copy()
        l=np.eye(n)
        p=np.eye(n)
        d=np.zeros((n,n))
        #we just have to make sure all pivots along the diagnol through row swaps
        #if any zero pivots then push then to bottom
        curr_row=0
        for col in range(n):
            pivot_row=curr_row+np.argmax(abs(u[curr_row:,col]))
            if curr_row!=pivot_row:
                u[[curr_row,pivot_row],:]=u[[pivot_row,curr_row],:]
                p[[curr_row,pivot_row],:]=p[[pivot_row,curr_row],:]
                if col>0:
                    l[[curr_row,pivot_row],:col]=l[[pivot_row,curr_row],:col]
            d[curr_row,col]=u[curr_row,col]#curr_row=col
            u[curr_row,:]/=u[curr_row,col]#now diagnol of u will also be 1
            #all strech/compress will be bore by d alone
            for j in range(curr_row+1,n,1):
                factor=u[j,col]
                l[j,col]=factor
                u[j,:]-=u[curr_row,:]*factor
            curr_row+=1
        #PA=LDU
        if not np.allclose(np.dot(p,self.a),np.dot(l,np.dot(d,u))):
            print("CALCULATION ERROR\n")
            return None
        print("RESULT VERIFIED PA=LDU")
        #l is lower and u is upper triangle matrix where both responsible puerly for shear
        #d is pure strech and compress matrix along diagnol reponsible puerly for strech along orignal axes
        #A is suerly a non-symmetric matrix since we reach here
        return {'P':p,'L':l,'U':u,'D':d}
    
    def surviving_subspace(self):#it means we want to remove all those columns that are dependent and create a matrix that is independent
        #we only need to know pivoting columns by end 
        if(self.m!=self.n):
            print("VALID ONLY FOR SQUARE MATRIX\n")
            return None
        pivot_col=[]
        curr_row=0
        a=self.a.copy()
        for col in range(self.n):
            if curr_row>=self.m:
                break
            pivot_row=curr_row+np.argmax(abs(a[curr_row:,col]))
            if pivot_row!=curr_row:
                a[[curr_row,pivot_row],:]=a[[pivot_row,],:]
            if np.isclose(a[curr_row,col],0):
                continue
            pivot_col.append(col)
            a[curr_row,:]/=a[curr_row,col]
            for j in range(curr_row+1,self.m,1):
                factor=a[j,col]
                a[j,:]-=a[curr_row,:]*factor
            curr_row+=1
        a_sub=self.a[:,pivot_col]#we can't delete rows else plane dimention reduced or prespective changes without mentioning our prespective
        print("Dimension of surviving subspace is :",self.m,"",self.n,".\n")
        print("Dimension of surviving subspace is : ",len(pivot_col)," x",len(pivot_col),".\n")
        print("Independent Column Indices: ",pivot_col)
        return a_sub
    
    def eigenValues__AND__eigenVectors(self):
        #for a square matrix A , when it physcially transforms the space some vector that remain unrotated and unsheared are known as eigenvectors and they may be scaled by value equals to eigenvalue
        #Av=L*v ->(A-LI)v=0 ->v!=0 so det(A-LI)=0 so it reduce dimension of it and make it zero so this is characteristic equation
        #Genralized Characteristic Equation : 1*L^N + C_1*L^(N-1)+C_2^L(N-2)+..........+C_N=0 
        #in above equation after finding roots of equation we total n amount of eigen values for which we have to check wheather they satisfy or not
        #we also have to find C_i i=0 to n where this c_i tries to capture spartial properties of M at different states
        if self.m!=self.n:
            print("VALID ONLY FOR SQUARE MATRIX.\n")
            return None
        n=self.m
        M=np.zeros((n,n))
        c=np.zeros(n+1)
        c[0]=1
        for k in range(1,n+1,1):    
            if k==1:
                M=self.a.copy()
            else:
                M=np.dot(self.a,M+c[k-1]*np.eye(n))#c[k-1]*np.eye(n) each time else become A^k : advantage is that it deducts the total strech of previous state and when it multiply with A its axes don't explode in strech when we caluate current states strech
            trace=sum(M[i,i] for i in range(n))
            c[k]=-trace/k
        #now we have all const values
        poly_const=[1.0]+[c[i] for i in range(1,n+1)] #formed a list
        #roots are eigenvalues
        eigen_value=np.roots(poly_const)
        #we get n amount of roots but as we know for a nxn matrix it should have n amount of independent direction eigenvectors to be non defective
        #else it can't be diagonalized
        eigen_vector=[]
        # Clean up duplicate eigenvalues using a tolerance threshold
        unique_eigen_value= np.unique(np.round(eigen_value,decimals=5))
        pair=[]
        for L in unique_eigen_value:#for repeted roots if AM=GM its good else in last total amount of eigenvector less than required 
            #as well as if root is imaginary then also problem as that dirn than not exist in reality
            if abs(L.imag)>1e-5:
                continue
            L=L.real
            #A-LI =a det(a)=0 so atleast one pivot has to be zero
            a=self.a-L*np.eye(n)
            b=np.zeros(n)
            #ax=b where b=0 and x=v=eigenvector so we apply gaussian elemination now
            pivot_pair=[]
            zero_pivot_column=[]#as det =0 so altest 1 col amount each time
            curr_row=0
            for col in range(n):
                if curr_row>=n:
                    break
                pivot_row=curr_row+np.argmax(abs(a[curr_row:,col]))
                a[[curr_row,pivot_row],:]=a[[pivot_row,curr_row],:]
                if np.isclose(a[curr_row,col],0):
                    continue
                pivot_pair.append((curr_row,col))
                a[curr_row,:]/=a[curr_row,col]
                for j in range(curr_row+1,n,1):
                    factor=a[j,col]
                    a[j,:]-=a[curr_row]*factor
                curr_row+=1
            pivot_column=[col for (row,col) in pivot_pair]
            zero_pivot_column = [i for i in range(n) if i not in pivot_column]
            #now lets use back substitution to find our eigenvector where each time we assign our free variable equal to 1.0
            #Ax=b solve
            #if multiple free variables then we take one ateach time and others equal to zero
            for free_var in zero_pivot_column:
                x=np.zeros(n)
                x[free_var]=1.0
                #n-all free_variables=total pivots we found 
                for other_free in zero_pivot_column:
                    if other_free!=free_var:
                        x[other_free]=0.0

                for (p_row,p_col) in reversed(pivot_pair):
                    x[p_col]=-np.dot(a[p_row,p_col+1:],x[p_col+1:])   #b[i]=0 and each pivot pos in a is 1
                #now we get x which is eigenvector
                #we need to normalize it  x=x/||x|| so length=1
                s=sum(x[i]**2 for i in range(n))
                if np.isclose(s,0):
                    continue #as v!=0
                s=s**(1/2)
                v=x/s
                is_present=False
                for e_vec in eigen_vector:
                    # cosQ=s.d/(|s|.|d|) if angle is zero which means cosQ=1 that is a copy meaning
                    # e_vec stored is normalized means length =1 as well as for v we are checking in
                    cos_Q=np.dot(v,e_vec) 
                    if np.isclose(abs(cos_Q),1.0):#repeted independent dir
                        is_present=True
                        break
                if is_present==False:
                    eigen_vector.append(v)
                    pair.append((v,L))
        
        if len(eigen_vector) < n:
            print("Matrix is defective (not diagonalizable in real space).\n")
        else:
            print("Matrix is fully diagonalizable!\n")
        det=1
        trace=0
        for i in range(n):
            det*=eigen_value[i]
            trace+=eigen_value[i]
        
        print("Determinant :",det,"\nTrace :",trace,"\n")
        return pair
    #While Faddeev-LeVerrier is mathematically beautiful, be aware that in the real world of 10,000 x 10,000 matrices, it becomes numerically unstable due to floating-point rounding. Modern ML libraries use the QR Algorithm instead

    def diagonalize(self):#this is valid real world of upto 10,000 x 10,000 matrices, it becomes numerically unstable due to floating-point rounding. Modern ML libraries use the QR Algorithm instead
        #only valid for square matrix 
        if self.m!=self.n:
            print("VALID ONLY FOR SQUARE MATRIX\n")
            return False
        n=self.m
        #1st find eigenvalue ->eigenvector if eigenvector amount less than n the non-diagonizble else make P ->D ->P' then recheck A=PDP' then return P,D,P'
        #1st EIGENVALUE
        # 1*L^(N)+C_1*L^(N-1).......+C_N=0 characteristic equation roots are eigenvalue
        c=np.zeros(n+1)
        c[0]=1.0
        M=self.a.copy()
        c[1]=-(sum(M[i,i] for i in range(n)))#k=1 solved here 
        for k in range(2,n+1):
            M=np.dot(self.a,M-c[k-1]*np.eye(n))
            trace=sum(M[i,i] for i in range(n))
            c[k]=-trace/k
        #put all c_i in list so we can process it to find roots
        poly_coff=list(c)
        roots=np.roots(poly_coff)
        #we will get n roots by the end all of which will be our eigenvalue and consider all root that come out to be real
        eigen_values=roots
        eigen_vectors=[]
        eigen_pair=[]
        unique=[]
        count=[]
        for val in eigen_values:
            found=False
            for j in range(len(unique)):
                check=unique[j]
                if np.isclose(check,val):
                    count[j]+=1
                    found=True
                    break
            if not found:
                unique.append(val)
                count.append(1)
        unique_eigen_values=list(zip(unique,count))
        for (L,AM) in unique_eigen_values:#if AM>GM then defect is definatly there so no need for further calculation
            #(A-LI)=a det(a)=0 so atleast 1 zero pivot point
            a=self.a-L*np.eye(n)
            b=np.zeros(n)
            #ax=b form gaussian elemination to find no. of free variables
            curr_row=0
            pivot_pair=[]
            for col in range(n):
                if curr_row>=n:
                    break
                pivot_row=curr_row+np.argmax(abs(a[curr_row:,col]))
                a[[curr_row,pivot_row],:]=a[[pivot_row,curr_row],:]
                if np.isclose(a[curr_row,col],0):
                    continue
                pivot_pair.append((curr_row,col))
                a[curr_row,:]/=a[curr_row,col]
                for j in range(curr_row+1,n,1):
                    factor=a[j,col]
                    a[j,:]-=a[curr_row,:]*factor
                curr_row+=1
            pivot_columns=[col for (row,col) in pivot_pair]
            All_free_variables=[i for i in range(n) if i not in pivot_columns]
            GM=len(All_free_variables)
            if AM!=GM:#if this happens then it means in the end the no. of independent dir columns for P will be dependent and det of P =0 and non-invertible so NOT DIAGONIZABLE
                print("NOT DIGANIZABLE\n")
                return None
            #else AM=GM so we will get GM amount of eigenvector from this eigenvalue
            for free_var in All_free_variables:
                x=np.zeros(n)
                x[free_var]=1.0
                for other_free in All_free_variables:
                    if free_var!=other_free:
                        x[other_free]=0.0
                #Ax=b backsubstitution methord
                for (row,col) in reversed(pivot_pair):
                    x[col]=-np.dot(a[row,col+1:],x[col+1:])
                #now we have dirn and need to normalize to length=1
                length=sum(x[i]**2 for i in range(n))
                length=length**(1/2)
                v=x/length
                is_duplicate=False
                for e_vec in eigen_vectors:
                    #e_vec and v are normalized so cosQ=e_vect.v
                    cos_Q=np.dot(e_vec,v)
                    if np.isclose(abs(cos_Q),1):
                        is_duplicate=True
                        break
                if not is_duplicate:
                    eigen_vectors.append(v)
                    eigen_pair.append((v,L))
        if len(eigen_vectors)<n:
            print("AMOUNT OF INDEPENDENT DIRECTION INSUFFICENT SO NON DIAGNALIZABLE\n")
            return None            
        #now that amount is suffient that means we will be able to form P :prespective matrix
        P=np.zeros((n,n))
        col=0
        D=np.zeros((n,n))
        for (v,L) in eigen_pair:
            P[:,col]=v
            D[col,col]=L
            col+=1
        #now we have P and D now we calculate P^-1
        #if A=A^T then symmetric and P is pure rotation matrix so P^-1=P^T
        A_T=self.a.transpose()
        P_inv=np.zeros((n,n))
        if np.allclose(self.a,A_T):
            P_inv=P.transpose()
        else:
            I=np.eye(n)
            aug=np.hstack((P,I))
            #[P|I]--->[I|P_inv] we know that no pivot will become zeo as of invertibility property
            for i in range(n):
                pivot_i=i+np.argmax(abs(aug[i:,i]))
                aug[[i,pivot_i],:]=aug[[pivot_i,i],:]
                #no pivot will be zero byy this step or moment
                aug[i,:]/=aug[i,i]
                for j in range(i+1,n,1):
                    factor=aug[j,i]
                    aug[j,:]-=aug[i,:]*factor
            for i in range(n-1,-1,-1):
                for j in range(i-1,-1,-1):
                    factor=aug[j,i]
                    aug[j,i:]-=aug[i,i:]*factor
            P_inv=aug[:,n:]
        #A=PDP_inv
        if not np.allclose(self.a,np.dot(P,np.dot(D,P_inv))):
            print("CALCULATION ERROR OCCURED\n")
            return None
        print("RESULT VERIFIED\n")
        return {'P':P,'D':D,'P_inv':P_inv}

    def matrix_power(self, power):
        #if want martix A^k then doing manually will take k*n^3 time 
        #we have A=PDP_inv and PP_inv=I so A^k=PD^KP_inv and as we know D is diagnol matrix then just simply make each diagnol element as a power of k which takes no time so a very large amount of time saved just need to diagonalize and remaultiply them
        obj=self.diagonalize()
        if(obj==None):
            print("NON_DIAGANIZABLE\n")
            return None
        P=obj['P']
        D_k=obj['D'].copy()
        P_inv=obj['P_inv']  
        n=self.m
        for i in range(n):
            D_k[i,i]=D_k[i,i]**power
        A_n=np.dot(P,np.dot(D_k,P_inv))
        return A_n
        
    def prespective_and_sigmas_OFsymmetric(self,S):
        #we can be rest asured that input matix it definatly a symmteric matrix kxk
        #since symmetric then by spectral therom we can be guranteed that we will definatly get a k amount of orthonormal eigenvectors
        A=np.array(S,dtype=float)
        n=A.shape[0]
        #eigen value using charcteristic equation |A-LI|=0
        #1*L^N+C_1*l^(N-1)......+C_N=0 total n+1 constants
        c=np.zeros(n+1)
        M=A.copy()
        c[0]=1.0
        c[1]=-sum(M[i,i] for i in range(n))#-trace/1
        for k in range(2,n+1):
            M=np.dot(A,M+c[k-1]*np.eye(n))
            c[k]=-sum(M[i,i] for i in range(n))/k#-trace/k

        poly_coff=list(c)
        roots=np.roots(poly_coff).real
        sorted_roots=sorted(list(roots), key=abs, reverse=True)
        #although there is no need to sort root/eigrnvalue to find eigen vectors we are doing it so that when we need to do compressing by k rank then highest level/variance is concentrated to top left side
        eigen_values=sorted_roots#also roots are gurranted to be real else spectral property break
        #by the way when we have repated root at that time eigenvectors will be also of same amount so eigenvector and eigenvalue pair natrually form 
        eigen_vectors=[]
        unique_eigen_values=[]
        for e_val in eigen_values:
            present=False
            for ue_val in unique_eigen_values:
                if np.isclose(e_val,ue_val):
                    present=True
                    break
            if not present:
                unique_eigen_values.append(e_val)
        for L in unique_eigen_values:
            #A-LI=a and det(a)=0 so atleat 1 zero pivot 
            a=A-L*np.eye(n)
            b=np.zeros(n)
            #ax=b where x is eigenvector and amount of eigenvector corresponds to no. of free variable=n-pivot_columns_amount
            #Gaussian_Elimination
            pivot_pair=[]
            curr_row=0
            for col in range(n):
                if curr_row>=n:
                    break
                pivot_row=curr_row+np.argmax(abs(a[curr_row:,col]))
                a[[curr_row,pivot_row],:]=a[[pivot_row,curr_row],:]
                if np.isclose(a[curr_row,col],0):
                    continue
                pivot_pair.append((curr_row,col))
                a[curr_row,:]/=a[curr_row,col]#so that all pivots are 1
                for j in range(curr_row+1,n,1):
                    factor=a[j,col]
                    a[j,:]-=a[curr_row,:]*factor
                curr_row+=1
            pivot_columns=[col for (row,col) in pivot_pair]
            all_free_variables=[i for i in range(n) if i not in pivot_columns]
            #AM=GM that is guranteed
            for free_var in all_free_variables:
                x=np.empty(n)
                x[free_var]=1.0
                for other_var in all_free_variables:
                    if other_var!=free_var:
                        x[other_var]=0.0
                #now back substitution ax=b ->ax=0
                for row,col in reversed(pivot_pair):
                    x[col]=-np.dot(a[row,col+1:],x[col+1:])
            length=sum(x[i]**2 for i in range(n))**(1/2)
            v=x/length#normalized
            is_duplicate=False
            valid=True
            for e_vector in eigen_vectors:
                #e_vector and v both normal so just require to be othonormal even though its guranteed we still do it to gurantee
                cos_Q=np.dot(e_vector,v)#if cosQ=1or-1 then means same dir and not valid and if cosQ=0 then perpendicular
                if np.isclose(abs(cos_Q),1):
                    is_duplicate=True
                    break
                if not np.isclose(cos_Q,0):
                    valid=False
                    break
            if valid and not is_duplicate:
                eigen_vectors.append(v)
        #we will definatly get n amount of eigenvector corresponding to their eigenvalues as AM=GM        
        P=np.empty((n,0))
        for e_vec in eigen_vectors:
            e_v=np.array(e_vec).reshape(-1,1)
            P=np.hstack((P,e_v))
        #we get prepective matrix nxn in the end its set of eigenvalues n
        return {'P':P,'eigen':eigen_values}
    
    def SVD__Singular_Value_decomposition(self):
        #it is valid decomposition for all type of matrix wheather square, rectangle ,zeros .....
        m=self.m
        n=self.n
        #A=USV^T    mxn
        #where V is input prespective rigid rotation which is nxn obtained using A^TxA AND VV^T=I as V made of orthnormal eigenvectors
        #where U is output prespective rigid rotation which is mxm obtained using AxA^T AND UU^T=I
        #where S is a dignol matrix which dianol are sigmal axes strech  mxn size so extract eigen vector for smallest of m,n if m then U if n then V
        #when any matrix is multipled by its transpose we will suerly get a symmetric square matrix
        #in A=USV^T AND A^T=VS^TU^T AND AxA^T=USS^TU^T we know V^T=V_inv so VV^T=I and since S is dignol matrix SS^T=S^2
        #AA^T=A'=PDP_inv and so US^2U_inv so S contain sigma where as D contain eigen values so for them to be equal sigma=(eigen)**(1/2)
        input_1=np.dot(self.a.transpose(),self.a)
        obj_v=self.prespective_and_sigmas_OFsymmetric(input_1)
        V=np.array(obj_v['P'])
        V_T=V.transpose()
        U=np.zeros((m,m))
        S=np.zeros((m,n))
        eigen_val=obj_v['eigen']
        #even though the eigenvalues in both U and V will same give same EigenVectors but vector is a line and has two directors in case both have different dirn stored for same eigen value then flipped and problem arrises
        #A=USV^T  ->VV^T=I=V^TV -> AV=US ->a_ixv_i/s_i=u_i so not flipped
        det=1
        for i in range(min(m,n)):
            S[i,i]=abs(eigen_val[i])**(1/2)
            det*=S[i,i]
            #Av_i=sigma*u_i so, u[i]=Av_i/sigma  mxn nx1 V is nxn
            if not np.isclose(S[i,i],0):
                v_i=V[:,i]
                u_i=np.dot(self.a,v_i)/S[i,i]  #mxn nx1 ->mx1 
                U[:,i]=u_i
            else:
                #in case sigma is 0 that means that dimention of A collapses to show and maintain square matrix U just make that dimenstion =1 in U so to have a orthonomal dirn along crushed dimension
                U[i,i]=1.0    
        #now we have U S V^T
        residual=self.a-np.dot(U,np.dot(S,V_T))
        if not np.allclose(residual,0):
            print("CLACULATION PROBLEM!!!!\n")
            return None
        print("----RESULT VERIFIED AND SVD SUCESSFULL----\n")
        if m==n:
            print("deteminant :",det)
        return {'U':U,'S':S,'V_T':V_T}
    
    def Pseudo_Inverse(self):
        #we apply this only when our martix is rectangle or when square matrix det=0 or non-invertible 
        #need of this is because every kind data we have is not necessarly a square invertible matrix
        #since in real world when we require a inverse of above type of matrix A is A^(+)orA_inv
        #but since its real world then this propery AxA_inv=A_invxA=I not hold 
        #if m>n A_inv x A =I which is nxn hold here that is left inverse as when a nx1 vector is introduced and then convert to m dimension through A in it no loss of data since m>n then then A_inv converts back to n in it no majir loss of info so A_inv x A=I approx hold
        #if n>m A x A_inv -I which is mxm hold here that is right inverse when mx1 vector is is introduced and then convert to n dimension through A_inv in it no loss of data since m<n then then A converts back to m in it no majir loss of info so A x A_inv=I approx hold
        #svd -> A=USV^T as V and U are righd rotation matrix made of orthonormal eigenvectors VV^T=I and UU^T=I
        #A_inv =VS_invU_inv =VS_invU^T so only need to find S_inv which is sigma->1/sigma just if sigma<tolarance we treat it as 0 as well as when sigma =0 then left it as it is as 0 so to avoid noise from diturbing calculation
        #tolrance=E*sigma_max *max(m,n) and E=2.22*10^(-16)
        m=self.m
        n=self.n
        obj=self.SVD__Singular_Value_decomposition()
        U=np.array(obj['U'])
        S=np.array(obj['S']) #mxn
        V_T=np.array(obj['V_T'])
        sigma_max=abs(S[0,0])
        e=2.22*10**(-16)
        tolarance=e*max(m,n)*sigma_max
        #[1000,122,33,4,0.000000002]-> sigma->1/sigma  ->then last 10^20 something will create a noise so its better to let it become 0 in it we trade a little bit of accuray for precision of calclation
        for i in range(min(m,n)):
            sigma=S[i,i]
            if sigma==0:
                continue
            if abs(sigma)<tolarance:
                S[i,i]=0
            else:
                sigma=1/sigma
                S[i,i]=sigma
        #VS_invU^T
        V=V_T.transpose()
        S_inv=S.transpose()
        U_T=U.transpose()
        A_inv=np.dot(V,np.dot(S_inv,U_T))
        #A_invA=I may fail in case when we don't have full matrix i.e when dimensions are destroyed so 
        #universal check AxA_invxA=A
        residual=self.a-np.dot(self.a,np.dot(A_inv,self.a))
        # We use atol=1e-7 to allow for tiny floating point noise
        if not np.allclose(residual, 0, atol=1e-7):
            print("CALCULATION ERROR: Penrose condition failed\n")
            return None
        print("RESULT VERIFIED\n")
        return {'A_inv':A_inv,'V':V,'S_inv':S_inv,'U_T':U_T}
    
    def Rank_K_compression(self,k):#ECKART-yOUNG THEORM
        #when we want to compress a file or imagewe use this
        # ->svd -> [u1,u2,u3.......,um][s1,s2,s3.......][vT1,vT2,......,vTn] ->sumation(sigma_i*(u_ixvT_i)) which can be seen as layers k where k is min(m,n)
        # Av=sigmaxu now we know that sigma are arnged from large to small so we take first k so that engergy loss can be minimum
        # U->mxk  S->kxk V_T->kxn  ->mxn through this we can see that A is still mxn but after removing noises or compression we have inluded layes that have most of significant impact within matrix A
        # energy of matrix=sum(sigma_i**(2))
        #frobenius norm ||A-A_k|| is min fir this top-left k's as there are the largest k values among the sigma_i
        #error=Energy_total-Energy_rank_K_compression
        #frobenius norm error =(error)**(1/2)
        m=self.m
        n=self.n
        obj=self.SVD__Singular_Value_decomposition()
        U=np.array(obj['U'])
        S=np.array(obj['S']) #mxn
        V_T=np.array(obj['V_T'])
        U_mxk=U[:,:k]
        V_T_kxn=V_T[:k,:]
        S_kxk=S[:k,:k]
        energy_total=0
        energy_k_compress=0
        for i in range(min(m,n)):
            sigma=S[i,i]
            if i<k:
                energy_k_compress+=sigma**2
            energy_total+=sigma**2
        error=energy_total-energy_k_compress
        norm_error=error**(1/2)
        information_retain=energy_k_compress/energy_total*100
        print("information retained is :",information_retain,"%.\n")
        print("frobenius norm error is :",norm_error,".\n")
        return{'U_comp':U_mxk,'S_comp':S_kxk,'V_T_comp':V_T_kxn}
    
    def simple_symmetric_positive_definate(self):
        #upawrd curved bowl 
        #it means that ant vector that drops on this landscape it has the potential to reach minimal point
        #when ever a vector is transformed then transformed angle is not largerr than 90 degrees 
        #x nx1 and Ax nxn nx1 nx1 so (x^T)(Ax)>0 i.e it means ||x|| ||Ax|| cosQ so depend on cosQ if cosQ>0 then up 
        #as well if all eigenvalues are L_i>0 
        #if all pinciple mirors >0 d1,d2,....,dn
        if self.m!=self.n or not np.allclose(self.a,self.a.transpose()):
            return False
        n=self.m
        #lets use eigrnvalue methord
        #1*L^N+C_1*L^(N-1)...............+C_0=0
        c=np.zeros(n+1)
        M=self.a.copy()
        c[0]=1.0
        c[1]=-sum(M[i,i] for i in range(n))
        for k in range(2,n+1):
            M=np.dot(self.a,M+c[k-1]*np.eye(n))
            c[k]=-sum(M[i,i] for i in range(n))/k
        poly_coff=list(c)
        eigen_values=np.roots(poly_coff)
        if min(eigen_values)<=0:
            return False
        return True
    
    def cholesky_decomposition(self):
        #A=LL^T ONLY WHEN OUR A IS SPD symmetric positive definate
        #in LU decomposition of A
        #A=LU -> A=LDU where diagnol of both L&U are 1 as for D it holds expnsions along the axes since A is symmetric U=L^T s they skew towards each other by same angle
        #A=LDL^T= (LD_r)(D_rL^T) ->D=(D_r)^r and for diagnol matrix D=D^T
        #A=(LD_r)(LD_r)^T ====> L_cho=LD_r
        if self.m!=self.n or not np.allclose(self.a,self.a.transpose()):
            print("VALID ONLY FOR SYMETRIC MATRIX\n")
            return False
        n=self.m
        U=self.a.copy().astype(float)
        D=np.zeros((n,n),dtype=float)
        #no row swaps will be needed as if row swapp needed it itself shows that zero pic=vot is there as well as row swap while maintaining symmertic means that in end only diagnol elements are swapped
        #SPD det=product of eigrnvalues since L is a lower tri matrix then all pivots along diagnol so if any diagnol is zero or less than 0 the fail
        for i in range(n):
            if np.isclose(U[i,i],0) or U[i,i]<0:
                return False
            D[i,i]=U[i,i]
            U[i,:]/=U[i,i]
            for j in range(i+1,n,1):
                factor=U[j,i]
                U[j,:]-=U[i,:]*factor
        D_r=D.copy()
        for i in range(n):
            D_r[i,i]=D_r[i,i]**(1/2)#D[i,i] won't be -ve since it reached this step
        L=np.array(np.dot(U.transpose(),D_r))
        residual =np.dot(L,L.transpose())-self.a
        if not np.allclose(residual,0):
            return False
        return {'L':L}
    
    def optimized_symmetric_positive_definate(self):#O(N^4)->O(N^3) timecomplexity differ from simple methord
        obj=self.cholesky_decomposition()
        if obj==False:
            print("NOT SPD\n")
            return False
        else:
            print("VALID SPD\n")
            return True
        
    def SPD_cholesky_decomposition(self,M):#M as SPD
        a=np.array(M,dtype=float)
        n=a.shape[0]
        U=a.copy().astype(float)
        D=np.zeros((n,n),dtype=float)
        for i in range(n):
            #since a is surely a SPD no need to check as we will definatly get valid pivots
            D[i,i]=U[i,i]
            U[i,:]/=U[i,i]
            for j in range(i+1,n,1):
                factor=U[j,i]
                U[j,:]-=U[i,:]*factor
        D_r=D.copy()
        for i in range(n):
            D_r[i,i]=D_r[i,i]**(1/2)#D[i,i] won't be -ve since it reached this step
        L=np.array(np.dot(U.transpose(),D_r))
        return {'L':L}
    
    def liner_regression_cholesky(self):
        #Ax=b ->A can be a rec, singular, non-sigulaar any in real world 
        #so to solve it A^TAx=A^Tb now A'=A^TA which will surely be a SPD as x^TA'x=x^TA^TAx=(Ax)^T(Ax) ->let Ax=v ->v^Tv=||v||^2>=0 and v=0 only when Ax=0 i.e A=0 i.e columns of a are dependent
        #columns of A should be independent so for wide A directly invalid for square and tall valid 
        #A^TA is SPD so if apply chlesky we get LL^T where L is lower triangle so now we can apply backsub and forward sub now instead to finding inverse and then multiplying matrixes again it saves time
        m=self.m
        n=self.n
        if self.n>self.m:#as no. of pivots will definatly be less so will become dependent columns
            return None
        #check for linear independence
        check=self.a.copy()
        pivots=0
        curr_row=0
        for col in range(n):
            if curr_row>=m:
                break
            pivot_row=curr_row+np.argmax(abs(check[curr_row:,col]))
            check[[curr_row,pivot_row],:]=check[[pivot_row,curr_row],:]
            if np.isclose(check[curr_row,col],0):
                print("Linerly dependent columns !!!!!!!")
                return None
            for j in range(curr_row+1,m,1):
                factor=check[j,col]/check[curr_row,col]
                check[j,:]-=check[curr_row,:]*factor
            curr_row+=1
        #A^TAx=A^Tb->Mx=B 
        M=np.dot(self.a.transpose(),self.a)#nxm mxn =nxn
        B=np.dot(self.a.transpose(),self.b)
        obj=self.SPD_cholesky_decomposition(M)
        L=np.array(obj['L'])# nxn
        #LL^Tx=B now we apply ->L^Tx=y Ly=B ->forward substitution
        x=np.zeros(n)
        y=np.zeros(n)
        y[0]=B[0]/L[0,0]
        for i in range(1,n):
            y[i]=(B[i]-np.dot(L[i,:i],y[:i]))/L[i,i]#no diagnol element will ever be zero
        #L^Tx=y
        L_T=L.transpose()
        #backsub
        for i in range(n-1,-1,-1):
            x[i]=(y[i]-np.dot(L_T[i,i+1:],x[i+1:]))/L_T[i,i]
        residual=np.dot(self.a,x)-self.b
        if not np.allclose(residual,0):
            print("calculation error!!!!!!!!\n")
            return None
        print("Result verified!!!!!!!!\n")
        return {'x':x}
    
    def Projection_Matrix_solve_projected_shadow(self,b):
        # when we want to solve Ax=b but is unreachable then we project our object over matrix p=Ag  mxn nx1->mx1
        #error=e=b-p  mx1
        #error will be perpendicular to plane which is A as a result orthogonal projrction in which light source is cast directly from above
        #A^Te=0->A^T(b-Ag)->A^Tb-A^TAg=0->A^TAg=A^Tb->g=(A^TA)_invA^T->Ag=p=A(A^TA)_invA^Tb
        #Projection matrix is P=A(A^TA)_invA^T so p=Pb
        #orthogonal->P^2=P and P^T=P 
        #>P^2=P it makes sure that we can't take shadow of the shadow itself i.e shadow remains there itself
        #P^T=P ensures that 90 degrees by p^Te=(Pb)^T(b-Pb)=b^T(P^Tb-P^TPb) =0 only when P^T=P 
        #p=A(A^TA)_invA^Tb  b->mx1  nxm mx1 ->nx1  ->nxn nx1 ->nx1 ->mxn nx1 ->mx1 . so, A^TA is SPD so also inverse possible as det!= 0 and square matrix
        n=self.n
        A_=np.dot(self.a.transpose(),self.a)
        I=np.eye(n)
        aug=np.hstack((A_,I)).astype(float)
        for i in range(n):
            pivot_i=i+np.argmax(abs(aug[i:,i]))
            aug[[i,pivot_i],:]=aug[[pivot_i,i],:]
            if np.isclose(aug[i,i],0):
                print("A^TA Singular matrix . projection impossible")#I have redundant columns! I cannot be inverted!
                return None
            aug[i,:]/=aug[i,i]
            for j in range(i+1,n,1):
                factor=aug[j,i]
                aug[j,:]-=aug[i,:]*factor
        for i in range(n-1,-1,-1):
            for j in range(i-1,-1,-1):
                factor=aug[j,i]
                aug[j,i:]-=aug[i,i:]*factor
        inv=aug[:,n:]
        P=np.dot(self.a,np.dot(inv,self.a.transpose()))
        p=np.dot(P,b)
        return{'p':p}

    def L1_manhatan_norm(self,v):
        x=np.array(v,dtype=float).flatten()#so that wheater input is 2d or 1d .... don't matter
        #||x||p =(sum((|x_i|)^p))^(1/p)
        n=x.shape[0]
        x_1=np.sum(np.abs(x))
        return x_1
    
    def L2_ecludian_norm(self,v):
        x=np.array(v,dtype=float).flatten()
        #||x||p =(sum((|x_i|)^p))^(1/p)
        n=x.shape[0]
        x_2=np.sqrt(np.sum(x**2))
        return x_2
    
    def L_infinity_norm(self,v):
        x=np.array(v,dtype=float).flatten()
        #||x||p =(sum((|x_i|)^p))^(1/p)
        n=x.shape[0]
        x_inf=np.max(np.abs(x))
        return x_inf
    
    def Gram_Shmidt_Othogalization(self):
        #A=[v1,v2,v3,v4......,vn]  v_i->mx1 order  we want to untangle these messy direction and make these basis set such that they each are othogonal to each other such that we get [u1,u2,u3,.....,un] set of basis 
        #to straingten them we have to remove the shadows they project other settled basis and continueing till all n basis are covered then we normalize each base so that they re orthonormal
        #P=U(U^TU)_invU^T and p=Pv_i   we project v_i on u_i since order mx1 P------>U^TU->1x1 scalar->inv->scalar so scalar U(U^Tv_i)->scalar*U

        #confirm if they form basis i.e are linear independent columns
        m=self.m
        n=self.n
        if n>m:
            print("These don't form basis for space/subspace\n")
            return None
        a=self.a.copy().astype(float)
        for i in range(n):
            pivot_i=i+np.argmax(abs(a[i:,i]))
            a[[i,pivot_i],:]=a[[pivot_i,i],:]
            if np.isclose(a[i,i],0):
                print("These don't form basis for space/subspace\n")
                return None
            a[i,:]/=a[i,i]
            for j in range(i+1,m,1):
                factor=a[j,i]
                a[j,:]-=a[i,:]*factor
        #if reached here then col form bases as columns are independent dirn of subspace nxn
        V=self.a.copy()
        U=np.zeros((m,n),dtype=float)
        for curr in range(n):
            v=V[:,curr]
            u=v.copy()#create new space through copy else become reference
            for prev in range(curr):
                u_prev=U[:,prev]
                scalar=np.dot(u_prev,v)#as ||u_orev||=1
                p=scalar*u_prev
                u-=p
            length=np.sqrt(np.sum(u**2))
            u/=length
            U[:,curr]=u
        return {'U_orthonormal_basis':U}
    
    def QR_Algorithm(self,M):
        #A=QR where Q is orthogonal using gram shmidt and our R is recipie upper triangle
        #mxn then mxn nxn
        A=np.array(M).astype(float)
        a=A.copy().astype(float)
        m,n=a.shape
        if n>m:
            return None
        Q=np.zeros((m,n),dtype=float)
        R=np.zeros((n,n),dtype=float)
        for curr in range(n):
            v=a[:,curr]
            u=v.copy()
            for prev in range(curr):
                u_pro=Q[:,prev]
                scale=np.dot(u_pro,v)
                p=scale*u_pro
                u-=p
                R[prev,curr]=scale
            length=np.sqrt(np.sum(u**2))
            if np.isclose(length,0):
                return None
            u/=length
            R[curr,curr]=length
            Q[:,curr]=u
        residual=np.dot(Q,R)-A
        if not np.allclose(residual,0,atol=1e-8):
            print("Calculation error")
            return None
        return {'Q':Q,'R':R}
    
    def eigenvalue_QR_ALgorithum(self,max_iter=100):
        #A_i=Q_iR_i where R is upper traingle and Q is orthogonormal set Q^TQ=I and  A_(i+1)=R_iQ_i
        #whenver simplified trnsofomation R_iQ_i=Q^T_iA_iQ_i ,Q^T=Q_inv as well as Q^T_iA_i(QQ^T)v_i=Q^T_iLv_i->(Q^TAQ)(Q^Tv)=L(Q^Tv) ->A_transY=LY
        #we do these step till A becomes a upper triangle agter so our eigen values remain same that hung on diagnol directly as if we do |A-LI|=0 now we find that the eigenvalues all equal to diagnol values
        #A will be nxn 
        n=self.m
        A_i=self.a.copy().astype(float)
        for _ in range(max_iter):
            check=np.tril(A_i,-1)
            if np.allclose(check,0):
                break 
            obj=self.QR_Algorithm(A_i)
            Q_i=np.array(obj['Q']).astype(float)
            R_i=np.array(obj['R']).astype(float)
            A_i=np.dot(R_i,Q_i)
        #eigen value can be zero
        eigen_values=[A_i[i,i] for i in range(n)]
        return {'eigen_values':eigen_values}
    
    def Linear_Regression_QR_Algorithum(self):
        #Ax=b ->A=QR ->QRx=b Q^TQ=I ->Rx=Q^Tb  best version as there will be numerical stability as well if we do A^TAx=A^Tb ->LL^Tx=b in this A^TA there may be numerical instability
        #mxn nx1 =mx1
        m=self.m
        n=self.n
        if n>m:
            print("No. Variable greater than equation\n")
            return None
        A=self.a
        obj=self.QR_Algorithm(A)
        Q=np.array(obj['Q']).astype(float)
        R=np.array(obj['R']).astype(float)
        Q_T=Q.transpose()
        x=np.zeros(n)
        B=np.dot(Q_T,self.b)
        #Rx=B where R is upper triangle so back substitution
        for i in range(n-1,-1,-1):
                x[i]=(B[i]-np.dot(R[i,i+1:],x[i+1:]))/R[i,i]
        return {'x':x}

    def Quadratic_Form(self):
        #A will be nxn x=[x1,x2] AND f(x)=x^TAx when 
        #A is symmetric and diagnol matrix then only bowl shape maintained if A is  symmetric and nondiagnol matrix then there will be strech along differnt dirn which twists bowl
        #M=(M+M^T)/2+(M-M^T)/2=sym+skew=S+k
        #x^TMx=x^T(s)x+x^T(k)x AND skew->K^T=-K q=x^Tkx then q sclar q=q^T and q^T=x^Tk^Tx=-x^Tkx=-q so q=-q when q=0
        #x^Mx=x^T(M')x and M'=(M+M^T)/2 now we convert M' into diagnoanlize PDP_inv and since M' is sym then P_inv=P^T where D holds eigenvalue  when we compare L_i to see orientation of bowl
        n=self.n
        if self.m!=self.n:
            S=np.dot(self.a.transpose(),self.a)#symmetri
        else:
            M=self.a.copy().astype(float)
            S=(M+M.transpose())/2 #symmetric
        #lets find eigenvalues 
        #QR algorithum as symmetric due to spectral therom we will definatly get vaild eigenvalues
        A_i=S.copy().astype(float)
        for _ in range(100):
            check=np.tril(A_i,-1)
            if np.allclose(check,0):
                break
            obj=self.QR_Algorithm(A_i)
            Q_i=np.array(obj['Q']).astype(float)
            R_i=np.array(obj['R']).astype(float)
            A_i=np.dot(R_i,Q_i)
        eigen_value=[A_i[i,i] for i in range(n)]
        max_eig=max(eigen_value)
        min_eig=min(eigen_value)
        eigen_vector=[]
        unique_eigen=np.unique(eigen_value)
        for L in unique_eigen:
            #|A-LI|=0 AND (A-LI)x=0
            a=S.copy().astype(float)-L*np.eye(n)
            b=np.zeros(n)
            #ax=b
            pivot_pair=[]
            curr_row=0
            for col in range(n):
                if curr_row>=n:
                    break
                pivot_row=curr_row+np.argmax(abs(a[curr_row:,col]))
                a[[curr_row,pivot_row],:]=a[[pivot_row,curr_row],:]
                if np.isclose(a[curr_row,col],0):
                    continue
                a[curr_row,:]/=a[curr_row,col]
                pivot_pair.append((curr_row,col))
                for j in range(curr_row+1,n,1):
                    factor=a[j,col]
                    a[j,:]-=a[curr_row,:]*factor
                curr_row+=1
            pivot_columns=[col for row,col in pivot_pair]
            free_variables=[i for i in range(n) if i not in pivot_columns]
            for free_var in free_variables:
                x=np.zeros(n).astype(float)
                x[free_var]=1.0#all other free var automatically zero
                for row,col in reversed(pivot_pair):
                    x[col]=-np.dot(a[row,col+1:],x[col+1:])
                length=sum(x[i]**2 for i in range(n))**(1/2)
                v=x/length#normalized
                is_dup=False
                for e_vec in eigen_vector:
                    #ince its symmetric matrix then eigenvectors will be orthonormal
                    cosQ=np.dot(e_vec,v)
                    if np.isclose(abs(cosQ),1):
                        is_dup=True
                        break
                if not is_dup:
                    eigen_vector.append(v)
        P=np.empty((n,0))
        for v in eigen_vector:
            P=np.hstack((P,np.array(v).reshape(-1,1)))
        #symmetric matrix eigrnvectors are orthogonal to each other spectral or gram-shmidt   
        Up=False
        Down=False  
        saddle=False    
        if not np.isclose(min_eig,0) and min_eig>0:
            Up=True
            print("UPWARD BOWL and positive definate after we move axes along eigenvectors P\n")
        elif not np.isclose(max_eig,0) and max_eig<0:
            Down=True
            print("DOWNWARD BOWL and negative definate after we move axes along eigenvectors P\n")
        else:
            saddle=True
            print("INDEFINATE SHAPE")
        return{'P':P,"Upward":Up,'Downward':Down,'Saddle_Point':saddle}



#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------------------------------------------------------------------
