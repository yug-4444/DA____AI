#include<iostream>
#include<functional>
using namespace std;
class Monotonic_Search{//monotonic means that our data will either have a contionous T or F single time in a data [T,T,T,T,T,F,F,F,F,F,F] OR [F,F,F,T,T,T,T,T,T,T,T]
    //[T,F,F,T,T,F,F,F,F,T] IS INVALID MONOTONIC SEQUENCE
    //like when we pull weights we have a limit upto which we are able to lift a weight and at that limit weifgt we know that 1. all weight below can be lifted and 2. all weights above this weight can't be lifted
    //LIMIT SEARCH
    public:
    long long findfirstlimit(long long low,long long high,function<bool(long long)>isValid){
        long long first=-1;
        while(low<=high){
            long long mid=low+(high-low)/2;
            if(isValid(mid)){
                first=mid;
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        return first;
    }
    long long findlastlimit(long long low,long long high,function<bool(long long)>isValid){
        long long last=-1;
        while(low<=high){
            long long mid=low+(high-low)/2;
            if(isValid(mid)){
                last=mid;
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return last;
    }
};