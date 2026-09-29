#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n,m;
        cin>>n>>m;
        if(max(m,n)<=2*min(m,n)&&(m+n)%3==0)cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
};//O(1)time