#include<iostream>
#include<vector>
using namespace std;
class DutchFlag{
    //we have any array that have three different input color flags 0,1,2 's now we want to sort them in O(n)time in a single pass and inplace
    public:
    void sort_flags(vector<int>&input){
        //lets do it in a similar fasion as of quick sort here we will divide in 4 regions 1.0's 2.1's 3.unexplored 4.2's
        int n=input.size();
        int zero_boundary=-1,two_boundary=n,i=0;
        while(i<two_boundary){
            if(input[i]==0){
                zero_boundary++;
                swap(input[i],input[zero_boundary]);
                i++;//newly swapped is suerly 1
            }else if(input[i]==2){
                two_boundary--;
                swap(input[i],input[two_boundary]);//still need to check wheather newly is 0 or 1
            }else{
                i++;
            }
        }
    }
};