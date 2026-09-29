#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
class Prime_Numbers_Sieve{
    public:
    vector<int>process(int n){//O(nloglogn)time complexity
        vector<bool>is_prime_number(n+1,true);
        is_prime_number[0]=false;
        is_prime_number[1]=false;
        for(int i=2;i*i<=n;i++){//optimize 1
            if(is_prime_number[i]){
                for(int j=i*i;j<=n;j=j+i){//optimize 2
                    is_prime_number[j]=false;
                }
            }
        }
        vector<int>prime;
        for(int i=0;i<=n;i++)if(is_prime_number[i])prime.push_back(i);
        return prime;
    }
};