#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    long long given_sum=0;
    for(int i=1;i<=n-1;i++){
        int j;
        cin>>j;
        given_sum+=j;
    }
    long long total_sum=1LL*n*(n+1)/2;
    long long miss=total_sum-given_sum;
    cout<<miss;
    return 0;
};