#include<iostream>
using namespace std;
class Exponentiation{
    public:
    long long process(long long A,long long B,long long M){//O(logB)time complexity
        long long result=1;
        long long base =A%M;
        while(B>0){
            if(B%2==1){
                result*=base;
            }
            base=(base*base)%M;
            B=B/2;
        }
        return result;
    }
};