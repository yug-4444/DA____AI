#include<iostream>
#include<vector>
using namespace std;
class Circular_House{
    private:
    const vector<int>&arr;
    int n;
    public:
    Circular_House(const vector<int>&input):
    arr(input),n(arr.size()){}
    int bottom_up(int start,int end){
        if (start == end) return arr[start];
        int dp_2=arr[start],dp_1=max(arr[start],arr[start+1]);
        for(int i=start+2;i<=end;i++){
            int curr=max(dp_1,dp_2+arr[i]);
            dp_2=dp_1;
            dp_1=curr;
        }
        return dp_1;
    }
    int circular_ans(){
        if(n==0)return 0;
        if(n==1)return arr[0];
        return max(bottom_up(0,n-2),bottom_up(1,n-1));
    }
};