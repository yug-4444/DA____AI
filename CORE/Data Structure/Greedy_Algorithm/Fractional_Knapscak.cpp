#include<iostream>
#include<vector>
using namespace std;
class Fractional_Knapscak{
    private:
    const vector<int>&items_weight;
    const vector<int>&items_prices;
    int n;
    int capacity;
    public:
    Fractional_Knapscak(const vector<int>&w,const vector<int>&p,int cap):
    items_prices(p),items_weight(w),n(items_prices.size()),capacity(cap){}

    int partition(vector<pair<double,int>>&input,int low,int high){
        double pivot=input[low+(high-low)/2].first;
        int i=low-1,j=high+1;
        while(i<j){
            do{i++;}while(input[i].first>pivot);
            do{j--;}while(input[j].first<pivot);
            if(i<j)swap(input[i],input[j]);
        }
        return j;
    }
    void quick_sorted_order(vector<pair<double,int>>&input,int low,int high){
        if(low<high){
            int pivot=partition(input,low,high);
            quick_sorted_order(input,low,pivot);
            quick_sorted_order(input,pivot+1,high);
        }//if low==high then already sorted position
    }
    pair<double,vector<pair<int,int>>>process(){
        if(capacity==0)return {0,{}};
        vector<pair<double,int>>ratios(n);
        for(int i=0;i<n;i++){
            ratios[i]={(double)items_prices[i]/items_weight[i],i};
        }
        quick_sorted_order(ratios,0,n-1);//in dscending order in O(nlogn)strict time
        double profit=0;
        vector<pair<int,int>>list;//{item,weight taken}
        int i=0;
        while(capacity>0&&i<n){
            int item=ratios[i].second;
            int curr_weight=items_weight[item];
            if(curr_weight<=capacity){
                list.push_back({item,curr_weight});
                profit+=ratios[i].first*curr_weight;
                capacity-=curr_weight;
                i++;
            }else{
                profit+=capacity*ratios[i].first;
                list.push_back({item,capacity});
                capacity=0;
            }
        }
        return {profit,list};
    }
};