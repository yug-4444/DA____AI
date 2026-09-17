#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main(){
    string input;
    cin>>input;
    int n=input.size();
    vector<int>count(26,0);
    for(auto&c:input)count[c-'A']++;
    int odds=0;
    for(auto&i:count)if(i%2!=0)odds++;
    if((n%2==0&&odds!=0)||(n%2!=0&&odds!=1)){
        cout<<"NO SOLUTION";
        return 0;
    }
    vector<char>ans(n);
    int p=0;
    if(n%2==0){
        for(int i=0;i<26;i++){
            while(count[i]){
                ans[p]='A'+i;
                ans[n-1-p]='A'+i;
                count[i]-=2;
                p++;
            }
        }
    }else{
        for(int i=0;i<26;i++){
            if(count[i]%2!=0){
                ans[n/2]='A'+i;
                count[i]--;
            }
            while(count[i]){
                ans[p]='A'+i;
                ans[n-1-p]='A'+i;
                count[i]-=2;
                p++;
            }
        }
    }
    for(auto&c:ans)cout<<c;
    return 0;
}