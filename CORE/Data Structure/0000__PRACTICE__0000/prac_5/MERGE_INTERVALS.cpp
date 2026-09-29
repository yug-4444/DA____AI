#include <vector>
#include <algorithm>
#include<iostream>
using namespace std;

class TemporalScheduler {
    public:
    void sort_by_start(vector<vector<int>>&input){
        sort(input.begin(),input.end(),
        [](const vector<int>&a,const vector<int>&b){
            return a[0]<b[0];
        });
    }
    vector<vector<int>> merge(vector<vector<int>>& input) {//now intervals will be sorted
        sort_by_start(input);
        int n=input.size();
        vector<vector<int>>output;
        for(int i=0;i<n;i++){
            if(!output.empty()&&input[i][0]<=output.back()[1]){
                output.back()[1]=max(input[i][1],output.back()[1]);//!!!!!!
                continue;
            }
            output.push_back(input[i]);
        }
        return output;
    }
};