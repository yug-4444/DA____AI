#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n,m;
        cin>>n>>m;
        if(n>2*m||m>2*n){
            cout<<"NO\n";
            continue;
        }
        while(n>0&&m>0){
            if(n>m){
                n-=2;
                m-=1;
            }else{
                m-=2;
                n-=1;
            }
        }
        if(n==0&&m==0)cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
};O(m+n)time