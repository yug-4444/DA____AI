//linear,binary SEARCH
#include<iostream>
#include<vector>
using namespace std;
class SearchEngine{
    private:
    const vector<int>&info;
    int n;
    public:
    SearchEngine(const vector<int>&i):
    info(i),n(info.size()){}
    int linearSearch(int target)const{//O(n) time complexity
        for (int i=0;i<n;i++){
            if(info[i]==target){
                return i;//index
            }
        }
        return -1;//not found
    }
    int rec_binary_Serach_Helper(int low,int high,int target)const{//binary search requires data to be sorted so assuming data is already sorted input
        if(low<=high){
            int mid=low+(high-low)/2;
            if(info[mid]==target){
                return mid;
            }
            else if(info[mid]>target){
                return rec_binary_Serach_Helper(low,mid-1,target);
            }
            else{
                return rec_binary_Serach_Helper(mid+1,high,target);
            }
        }
        return -1;
    }
    int recru_binary_search(int target)const{
        return rec_binary_Serach_Helper(0,n-1,target);
    }
    //binary search -> O(logn) time complexity
    int iter_binary_Serach(int target)const{//binary search requires data to be sorted so assuming data is already sorted input
        int low=0;
        int high=n-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(info[mid]==target){
                return mid;
            }
            else if(info[mid]>target){
                high=mid-1;
            }
            else{
                low=mid+1;
            }
        }
        return -1;
    }
};