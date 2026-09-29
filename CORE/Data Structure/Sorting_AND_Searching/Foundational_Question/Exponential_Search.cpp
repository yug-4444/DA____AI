#include<iostream>
#include<vector>
using namespace std;
//suppose what we have constant stream to in coming data that means use od size() is invalid and we still we to find the target
class Exponential_Search{
    public:
    Exponential_Search(){}
    int search(const vector<int>&stream,int target)const{
        if(stream.size()==0)return -1;
        if(stream[0]==target)return 0;
        int i=1;
        while(i<stream.size()&&stream[i]<=target){
            if(stream[i]==target)return i;
            i*=2;//using 2 is good as it reduces multiplication time as only one bit shift required
        }
        int low=i/2+1;
        int high=i>=stream.size()?stream.size()-1:i-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(stream[mid]==target)return mid;
            else if(stream[mid]>target)high=mid-1;
            else low=mid+1;
        }
        return -1;
    }

}