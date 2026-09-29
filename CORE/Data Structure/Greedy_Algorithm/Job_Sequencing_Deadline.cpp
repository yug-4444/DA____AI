#include<iostream>
#include<vector>
using namespace std;
class Job_Max_Profit{
    private:
    const vector<int>&profit;
    const vector<int>&deadline;
    int n;
    public:
    Job_Max_Profit(const vector<int>&p,const vector<int>&d):
    profit(p),deadline(d),n(profit.size()){}
    int partition(vector<int>&input,int low,int high){
        int pivot=profit[input[low+(high-low)/2]];
        int i=low-1,j=high+1;
        while(true){
            do{i++;}while(pivot<profit[input[i]]);
            do{j--;}while(pivot>profit[input[j]]);
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
    pair<int,vector<int>>process(){//O(n^2)time complexity
        int timeline=0;
        vector<int>order(n);
        for(int i=0;i<n;i++){
            if(deadline[i]>timeline)timeline=deadline[i];
            order[i]=i;
        }
        quick_sort(order,0,n-1);
        int total_profit=0;
        vector<int>schedule(timeline,-1);
        for(int i=0;i<n;i++){
            for(int j=deadline[order[i]]-1;j>=0;j--){
                if(schedule[j]==-1){
                    schedule[j]=order[i];
                    total_profit+=profit[order[i]];
                    break;
                }
            }
        }
        return {total_profit,schedule};
    }
    int find_root(vector<int>&parent,int curr){
        if(curr==-1)return -1;// GUARD: If we've fallen off the timeline, return instantly
        if(parent[curr]!=curr){
            parent[curr]=find_root(parent,parent[curr]);
        }
        return parent[curr];
    }
    pair<int,vector<int>>optimized(){//O(nlogn)time complexity
        int timeline=0;
        vector<int>order(n);
        for(int i=0;i<n;i++){
            if(deadline[i]>timeline)timeline=deadline[i];
            order[i]=i;
        }
        quick_sort(order,0,n-1);
        int total_profit=0;
        vector<int>parents(timeline);
        vector<int>schedule(timeline,-1);
        for(int i=0;i<timeline;i++)parents[i]=i;
        for(int i=0;i<n;i++){
            int currProfit=profit[order[i]];
            int lasttime=deadline[order[i]]-1;
            int pos=find_root(parents,lasttime);
            if(pos>=0){
                schedule[pos]=order[i];
                total_profit+=currProfit;
                if(pos>0)parents[pos]=parents[pos-1];
                else parents[0]=-1;
            }
        }
        return{total_profit,schedule};
    }
};
