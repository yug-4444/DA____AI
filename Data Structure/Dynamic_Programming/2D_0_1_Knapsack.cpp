#include<iostream>
#include<vector>
using namespace std;
class Knap{
    public:
    int max_carry(const vector<int>&weight,const vector<int>&price,int W){
        int n=weight.size();
        vector<vector<int>>dp(n+1,vector<int>(W+1,0));//max price of the first $i$ items that can fit in bag of $w$ cap for now
        for(int i=1;i<n+1;i++){
            for(int j=1;j<W+1;j++){
                if(weight[i-1]>j)dp[i][j]=dp[i-1][j];
                else dp[i][j]=max(price[i-1]+dp[i-1][j-weight[i-1]],dp[i-1][j]);
            }
        }
        return dp[n][W];
    }
    int optimized(const vector<int>&weight,const vector<int>&price,int W){
        int n=weight.size();
        vector<int>prev_row(W+1,0);
        for(int i=0;i<n;i++){
            vector<int>curr_row(W+1,0);
            for(int j=1;j<W+1;j++){
                if(weight[i]>j)curr_row[j]=prev_row[j];
                else curr_row[j]=max(price[i]+prev_row[j-weight[i]],prev_row[j]);
            }
            swap(prev_row,curr_row);//O(1)time else O(W)time as swap just exchange pointers not copy and paste them
        }
        return prev_row[W];
    }
};