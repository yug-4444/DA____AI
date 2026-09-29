#include<iostream>
using namespace std;
class GCD_LCM{//O(log(min(A,B)))time complexity
    public:
    long long GCD(long long A,long long B){
        if(B==0)return A;
        long long remainder=A%B;//it does't matter A%B or B%A
        return GCD(B,remainder);
        

    }
    pair<long long,long long>process(long long A,long long B){
        long long gcd=GCD(A,B);
        if(A==0||B==0){
            return{gcd,0};
        }
        long long lcm=(A/gcd)*B;//diect AxB might overflow so firs A/gcd then multiply B
        return{gcd,lcm};
    }
};