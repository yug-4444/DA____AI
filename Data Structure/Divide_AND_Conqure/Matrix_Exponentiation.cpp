//Matrix Exponentiation
#include<vector>
#include<iostream>
using namespace std;
//BINARY EXPONEANTATION
//MATRIX POWER MULTIPLICATION
//like if M matrix and its M^100 normal will require 99 matrix multiplications but using below methord it will only require 8 matrix multiplications
class Fn{//O(log n)time instead of O(n)time 
    private:
    vector<vector<int>>M;
    int n;
    public:
    Fn(int p):
    n(p){
        M.resize(2,vector<int>(2,1));
        M[1][1]=0;
    }
    void matrix_multiply(vector<vector<int>>&a,vector<vector<int>>&b){
        vector<vector<int>>c(2,vector<int>(2));
        c[0][0]=a[0][0]*b[0][0]+a[0][1]*b[1][0];
        c[0][1]=a[0][0]*b[0][1]+a[0][1]*b[1][1];
        c[1][0]=a[1][0]*b[0][0]+a[1][1]*b[1][0];
        c[1][1]=a[1][0]*b[0][1]+a[1][1]*b[1][1];
        a=c;
    }
    void divide(vector<vector<int>>&P,int power){
        if(power==0||power==1)return;
        
        divide(P,power/2);
        matrix_multiply(P,P);
        if(power%2!=0){
            matrix_multiply(P,M);
        }
    }
    vector<vector<int>>process(){
        vector<vector<int>>P=M;
        divide(P,n);
        return P; 
    }
};