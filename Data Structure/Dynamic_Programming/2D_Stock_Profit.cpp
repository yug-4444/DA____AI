#include<iostream>
#include<vector>
using namespace std;
enum state{hold,sell,rest};
class Profit{
    public:
    pair<int,vector<state>> process(const vector<int>&prices){
        int n=prices.size();
        if(n==0)return {0,{}};
        vector<vector<int>>dp(n,vector<int>(3));//hold->0,sell->1,rest->2 col
        dp[0][0]=-prices[0];
        dp[0][1]=0;
        dp[0][2]=0;
        for(int i=1;i<n;i++){
            dp[i][0]=max(dp[i-1][0],dp[i-1][2]-prices[i]);
            dp[i][1]=dp[i-1][0]+prices[i];
            dp[i][2]=max(dp[i-1][2],dp[i-1][1]);
        }
        vector<state>task(n);
        if(dp[n-1][1]>dp[n-1][2])task[n-1]=sell;
        else task[n-1]=rest;
        for(int i=n-2;i>=0;i--){
            if(task[i+1]==sell)task[i]=hold;
            else if(task[i+1]==rest){
                if(dp[i][1]>dp[i][2])task[i]=sell;
                else task[i]=rest;
            }else{
                if(dp[i][0]>dp[i][2]-prices[i+1])task[i]=hold;
                else task[i]=rest;
            }
        }
        return{dp[n-1][task[n-1]],task};
    }
};