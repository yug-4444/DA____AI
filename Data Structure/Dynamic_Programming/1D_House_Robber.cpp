#include<vector>
#include<iostream>
using namespace std;
class HRdp{
    private:
    const vector<int>&arr;
    int n;
    public:
    HRdp(const vector<int>&input):
    arr(input),n(arr.size()){}
    int bottom_up(){//O(n)time and O(n)space 
        if(n==0) return 0;
        if(n==1) return arr[0];
        vector<int>dp(n);//dp[i]--->means the max money robbed till this house (include the ith house)
        dp[0]=arr[0];
        dp[1]=max(arr[0],arr[1]);
        for(int i=2;i<n;i++){
            dp[i]=max(dp[i-1],dp[i-2]+arr[i]);
        }
        return dp[n-1];
    }
    int bottom_up_optimized(){//O(n)time and O(1)space ->best methord
        if(n==0) return 0;
        if(n==1) return arr[0];
        int prev_2=arr[0],prev_1=max(arr[0],arr[1]);
        for(int i=2;i<n;i++){
            int curr=max(prev_1,prev_2+arr[i]);
            prev_2=prev_1;
            prev_1=curr;
        }
        return prev_1;
    }
    int top_down_methord(int i,vector<int>&dp){//O(n)time and O(n)stack space 
        if(i==0)return arr[0];
        if(i==1)return max(arr[0],arr[1]);
        if(dp[i]!=-1)return dp[i];//means already solved
        dp[i]= max(top_down_methord(i-1,dp),top_down_methord(i-2,dp)+arr[i]);
        return dp[i];
    }
    int solve_top_down(){
        if(n==0) return 0;
        if(n==1) return arr[0];
        vector<int>dp(n,-1);
        return top_down_methord(n-1,dp);
    }
};