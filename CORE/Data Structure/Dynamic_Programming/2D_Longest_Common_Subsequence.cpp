#include<iostream>
#include<string>
#include<vector>
using namespace std;
enum dir{nil,diag,up,left};
class LCS{
    public:
    pair<int,string> process(string p,string q){
        int m=p.size(),n=q.size();
        vector<vector<int>>dp(m+1,vector<int>(n+1,0));
        vector<vector<dir>>move(m+1,vector<dir>(n+1,nil));
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(p[i-1]==q[j-1]){
                    dp[i][j]=1+dp[i-1][j-1];
                    move[i][j]=diag;
                }else{
                    if(dp[i][j-1]>dp[i-1][j]){
                        dp[i][j]=dp[i][j-1];
                        move[i][j]=left;
                    }else{
                        dp[i][j]=dp[i-1][j];
                        move[i][j]=up;
                    }
                }
            }
        }
        int i=m,j=n;
        dir s=move[i][j];
        vector<char>output;
        while(i>0&&j>0&&s!=nil){
            if(s==diag){
                output.push_back(p[i-1]);
                i-=1;j-=1;
            }else if(s==left){
                j-=1;
            }else if(s==up){
                i-=1;
            }
            s=move[i][j];
        }
        string ans="";
        i=output.size()-1;
        while(i>=0){
            ans+=output[i--];
        }
        return {dp[m][n],ans};
    }
};