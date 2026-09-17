#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n;
    cin>>n;
    long long moves=0;
    int prev=0;
    for(int i=1;i<=n;i++){
        int j;
        cin>>j;
        if(j<prev){
            moves+=prev-j;
        }else{
            prev=j;
        }
    }
    cout<<moves;
    return 0;
};