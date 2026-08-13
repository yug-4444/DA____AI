#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class MinPath{
    public:
    int solve(const vector<vector<int>>&grid){//O(mn)time and O(mn)space 
        int m=grid.size(),n=grid[0].size();
        vector<vector<int>>dp(m+1,vector<int>(n+1,INT_MAX));
        dp[1][1]=grid[0][0];
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(i==1&&j==1)continue;
                dp[i][j]=min(dp[i-1][j],dp[i][j-1])+grid[i-1][j-1];
            }
        }
        return dp[m][n];
    }
    int solve_optimized(const vector<vector<int>>&grid){//O(mn)time and O(n)space 
        int m=grid.size(),n=grid[0].size();
        vector<int>dp(n);
        dp[0]=grid[0][0];
        for(int i=1;i<n;i++){
            dp[i]=dp[i-1]+grid[0][i];
        }
        for(int i=1;i<m;i++){
            dp[0]=dp[0]+grid[i][0];
            for(int j=1;j<n;j++){
                dp[j]=min(dp[j],dp[j-1])+grid[i][j];
            }
        }
        return dp[n-1];
    }
};