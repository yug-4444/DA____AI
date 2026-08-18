#include<iostream>
#include<vector>
using namespace std;
class Power_Engine{//BINARY CHOICE TOPOLOGY
    private:
    vector<int>&array;
    vector<vector<int>>output;
    int n;
    public:
    Power_Engine(vector<int>&input):
    array(input),n(array.size()){}
    void generate(int index,vector<int>&curr_subset){
        if(index==n){
            output.push_back(curr_subset);
            return;
        }
        //we don't pick
        generate(index+1,curr_subset);

       //we pick
        curr_subset.push_back(array[index]);
        generate(index+1,curr_subset);
        curr_subset.pop_back();
    }
    vector<vector<int>>process(){
        vector<int>curr_subset;
        generate(0,curr_subset);
        return output;
    }
};