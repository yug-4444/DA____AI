#include<iostream>
#include<vector>
using namespace std;
class Max_Activity{
    private:
    const vector<int>&start_time;
    const vector<int>&end_time;
    int n;
    public:
    Max_Activity(const vector<int>&s,const vector<int>&e):
    start_time(s),end_time(e),n(start_time.size()){}
    int partition(vector<int>&input,int low,int high){
        int pivot=end_time[input[low+(high-low)/2]];
        int i=low-1,j=high+1;
        while(true){
            do{i++;}while(pivot>end_time[input[i]]);
            do{j--;}while(pivot<end_time[input[j]]);
            if(i>=j)return j;
            swap(input[i],input[j]);
        }
    }
    void quick_sort(vector<int>&input,int low,int high){
        if(low<high){
            int p=partition(input,low,high);
            quick_sort(input,low,p);
            quick_sort(input,p+1,high);
        }
    }
    pair<int,vector<pair<int,int>>>process(){
        vector<int>acti(n);
        for(int i=0;i<n;i++)acti[i]=i;
        quick_sort(acti,0,n-1);//absolute O(nlogn)time even in worst case
        vector<int>ans;
        ans.push_back(acti[0]);
        for(int i=1;i<n;i++){
            if(end_time[ans.back()]<=start_time[acti[i]])ans.push_back(acti[i]);
        }
        vector<pair<int,int>>result;
        for(int i=0;i<ans.size();i++){
            result.push_back({start_time[ans[i]],end_time[ans[i]]});
        }
        return{result.size(),result};
    }
};