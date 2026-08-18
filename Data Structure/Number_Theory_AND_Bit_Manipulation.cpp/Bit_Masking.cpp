#include<iostream>
using namespace std;
class Bit_Masking{//O(1)time each operation
    public:
    bool check_i_th_bit_1(int n,int i){
        if(n&(1<<i))return true;
        return false;
    }
    void set_i_th_bit_1(int &n,int i){
        n=n|(1<<i);
    }
    void clear_i_th_bit_0(int &n,int i){
        n=n&~(1<<i);
    }
    bool power_of_2(int n){
        if((n&(n-1))==0)return true;//== more precedence than & so () required
        return false;
    }
};