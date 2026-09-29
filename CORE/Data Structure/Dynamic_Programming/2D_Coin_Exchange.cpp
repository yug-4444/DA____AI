#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class Exchange{
    public:
    pair<vector<int>,int> process(vector<int>coins,int amount){
        if(amount==0)return {{},0};
        int n=coins.size();
        vector<vector<int>>dp(n+1,vector<int>(amount+1,INT_MAX/2));//int_max/2 to prevent overflow when int_max+1
        for(int i=0;i<=n;i++)dp[i][0]=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=amount;j++){
                if(j<coins[i-1]){
                    dp[i][j]=dp[i-1][j];
                }else{
                    dp[i][j]=min(dp[i-1][j],1+dp[i][j-coins[i-1]]);
                }
            }
        }
        if(dp[n][amount]==INT_MAX/2)return {{},-1};
        int i=n,j=amount;
        vector<int>ex_list;
        while(i>0&&j>0&&dp[i][j]!=INT_MAX/2){
            if(dp[i][j]==dp[i-1][j]){
                i--;
            }else{
                ex_list.push_back(coins[i-1]);
                j=j-coins[i-1];
            }
        }
        return {ex_list,dp[n][amount]};
    }
    int optimized(vector<int>coins,int amount){
        if(amount==0)return 0;
        int n=coins.size();
        vector<int>dp(amount+1,INT_MAX/2);
        dp[0]=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<=amount;j++){
                if(j>=coins[i]){
                    dp[j]=min(dp[j],1+dp[j-coins[i]]);
                }
            }
        }
        return dp[amount]==INT_MAX/2?-1:dp[amount];
    }
};