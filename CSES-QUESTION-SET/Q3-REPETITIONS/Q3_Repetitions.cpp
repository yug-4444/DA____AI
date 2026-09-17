#include<iostream>
#include<climits>
#include<string>
using namespace std;
int main(){
    string input;
    cin>>input;
    int max_length=0;
    char prev='@';
    int curr_length=0;
    for(auto&&curr:input){
        if(prev==curr){
            curr_length++;
        }else{
            max_length=max(max_length,curr_length);
            prev=curr;
            curr_length=1;
        }
    }
    max_length=max(max_length,curr_length);
    cout<<max_length;
    return 0;
}