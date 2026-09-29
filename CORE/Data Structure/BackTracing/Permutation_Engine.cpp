#include<iostream>
#include<vector>
using namespace std;
class Permutation_Engine{//SWAP TOPOLOGY
    private:
    vector<int>&array;
    vector<vector<int>>output;
    int n;
    public:
    Permutation_Engine(vector<int>&a):
    array(a),n(array.size()){}
    void genrate(int index){
        if(index==n){
            output.push_back(array);
            return;
        }
        for(int i=index;i<n;i++){
            swap(array[index],array[i]);
            genrate(index+1);
            swap(array[index],array[i]);//undo effects
        }
    }
    vector<vector<int>>process(){
        genrate(0);
        return output;
    }
};