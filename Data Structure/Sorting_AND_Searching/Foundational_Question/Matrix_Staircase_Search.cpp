#include<iostream>
#include<vector>
using namespace std;
class Matrix_Staircase{
    public:
    //O(m+n)time complexity
    pair<bool,pair<int,int>>search_2D_matrix(const vector<vector<int>>&matrix,int target){
        //we have two chocis either go up or go down i.e top-right corner or bottom-left corner to start from as only these two points gives us stiuation where either of one row or column is < and another >
        int m=matrix.size();//m,n=row,column
        int n=matrix[0].size();//since its a 2D matrix then atleast have row and column
        //we chose top right corner
        int r=0,c=n-1;
        while(c>=0&&r<=m-1){
            if(matrix[r][c]==target)return {true,{r,c}};
            else if(matrix[r][c]>target)c--;//column is wasted
            else r++;//that row is wasted
        }
        return{false,{-1,-1}};
    }
};