#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<bool>avail(n+1,false);
    for(int i=1;i<=n-1;i++){
        int j;
        cin>>j;
        avail[j]=true;
    }
    for(int i=1;i<=n;i++){
        if(!avail[i]){
            cout<<i;
            break;
        }
    }
    return 0;
};