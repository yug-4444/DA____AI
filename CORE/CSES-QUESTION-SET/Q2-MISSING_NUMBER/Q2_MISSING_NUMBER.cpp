#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n;
    cin>>n;
    int given_set=0;
    for(int i=0;i<n-1;i++){
        int j;
        cin>>j;
        given_set=given_set^j;
    }
    int full_set=0;
    for(int i=1;i<=n;i++)full_set=full_set^i;
    int missing=given_set^full_set;
    cout<<missing;
    return 0;
};