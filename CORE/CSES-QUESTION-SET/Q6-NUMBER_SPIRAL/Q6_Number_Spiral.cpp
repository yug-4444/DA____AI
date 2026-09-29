#include<iostream>
using namespace std;
long long process(long long row,long long column){
    long long layer=max(row,column);
    if(layer==row){
        if(layer%2==0){
            return 1LL*layer*layer-column+1;
        }else{
            return 1LL*(layer-1)*(layer-1)+column;
        }
    }else{
        if(layer%2==0){
            return 1LL*(layer-1)*(layer-1)+row;
        }else{
            return 1LL*layer*layer-row+1;
        }
    }
}
int main(){
    long long t;
    cin>>t;
    for(int i=1;i<=t;i++){
        long long row,column;
        cin>>row>>column;
        cout<<process(row,column)<<'\n';
    }
    return 0;
}