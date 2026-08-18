#include<iostream>
#include<vector>
using namespace std;
class FindSingleNumber{
    public:
    int process(vector<int>&array){//O(n)time and O(1)space
        int ans=0;// The XOR Identity Law protects us here
        for(int i=0;i<array.size();i++){
            ans=ans^array[i];
        }
        return ans;
    }
};