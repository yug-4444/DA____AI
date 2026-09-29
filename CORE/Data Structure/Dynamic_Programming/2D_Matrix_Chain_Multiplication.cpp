#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class MCM{
    public:
    pair<vector<vector<int>>,int>process(const vector<int>&p){//O(N^3)time and O(N^2)space
        int n=p.size()-1;
        vector<vector<int>>dp(n,vector<int>(n,0)),pos(n,vector<int>(n));
        for(int l=2;l<=n;l++){
            for(int i=0;i<=n-l;i++){
                int j=i+l-1;
                int mini=INT_MAX;
                for(int k=i;k<j;k++){
                    int curr=dp[i][k]+dp[k+1][j]+p[i]*p[k+1]*p[j+1];
                    if(mini>curr){
                        mini=curr;
                        pos[i][j]=k;
                    }
                }
                dp[i][j]=mini;
            }
        }
        return{pos,dp[0][n-1]};
    }
};