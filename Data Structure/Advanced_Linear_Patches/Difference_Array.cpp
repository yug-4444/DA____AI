#include<iostream>
#include<vector>
using namespace std;
class Difference_Array{//Offline query so that O(1)time i.e all range updates given at a time and result asked in end 
    private:
    vector<int>&arr;
    vector<int>diff;
    int n;
    public:
    Difference_Array(vector<int>&input):
    arr(input),n(arr.size()){
        diff.resize(n);
        diff[0]=arr[0];//initialization imaginary arr[-1]=0 so diff[0]=arr[0]-arr[-1]=arr[0]
        for(int i=1;i<n;i++){
            diff[i]=arr[i]-arr[i-1];
        }
    }
    void update(int val,int L,int R){
        diff[L]+=val;
        if(R+1<n)diff[R+1]-=val;
    }
    void reconstruct(){//O(n)time and O(1)space
        arr[0]=diff[0];
        for(int i=1;i<n;i++){
            arr[i]=arr[i-1]+diff[i];
        }
    }
};//O(1) Range Update 