#include<iostream>
#include<vector>
#include<climits>
#include<unordered_map>
using namespace std;
class LIS{
    public:
    pair<int,vector<int>> process_Nsquare(const vector<int>&nums){//O(n^2)time and O(n)space
        int n=nums.size();
        vector<int>dp(n,1);
        vector<int>s(n);
        for(int i=0;i<n;i++)s[i]=i;
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[j]<nums[i]){
                    if(dp[j]+1>dp[i]){
                        dp[i]=dp[j]+1;
                        s[i]=j;
                    }
                }
            }
        }
        int maxi=0;
        for(int i=1;i<n;i++){
            if(dp[i]>dp[maxi])maxi=i;
        }
        int a=maxi;
        vector<int>seq;
        while(maxi!=s[maxi]){
            seq.push_back(maxi);
            maxi=s[maxi];
        }
        seq.push_back(maxi);
        vector<int>ans;
        for(int i=seq.size()-1;i>=0;i--){
            ans.push_back(nums[seq[i]]);
        }
        return{dp[a],ans};
    }
    int optimized(const vector<int>&nums){//O(nlogn)time
        int n=nums.size();
        if(n==0)return 0;
        vector<int>trail;
        trail.push_back(nums[0]);
        for(int i=1;i<n;i++){
            if(trail.back()<nums[i]){
                trail.push_back(nums[i]);
            }else{
                int low=0,high=trail.size()-1;
                while(low<high){//so size of atleast 2
                    int mid=low+(high-low)/2;
                    if(trail[mid]<nums[i])low=mid+1;
                    else high=mid;
                }
                trail[low]=nums[i];
            }
        }
        return trail.size();
    }
    pair<int,vector<int>>opti_retrace(vector<int>&nums){
        int n=nums.size();
        if(n==0)return {0,{}};
        vector<int>trail;
        vector<int>trail_index;
        vector<int>parents(n,-1);
        trail.push_back(nums[0]);
        trail_index.push_back(0);
        for(int i=1;i<n;i++){
            if(nums[i]>trail.back()){
                parents[i]=trail_index.back();
                trail.push_back(nums[i]);
                trail_index.push_back(i);
                continue;
            }
            int low=0,high=trail.size()-1;
            while(low<high){
                int mid=low+(high-low)/2;
                if(trail[mid]<nums[i])low=mid+1;
                else high=mid;
            }
            int pos=low;
            trail[pos]=nums[i];
            trail_index[pos]=i;
            if(pos>0){
                parents[i]=trail_index[pos-1];
            }
        }
        int length=trail.size();
        vector<int>lic;
        int start=trail_index.back();
        while(parents[start]!=-1){
            lic.push_back(nums[start]);
            start=parents[start];
        }
        lic.push_back(nums[start]);
        vector<int>ans;
        for(int i=lic.size()-1;i>=0;i--){
            ans.push_back(lic[i]);
        }
        return{length,ans};
    }
};