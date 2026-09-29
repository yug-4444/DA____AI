//rotated binary search
#include <vector>
#include <iostream>
using namespace std;
class DatabaseQuery {
public:
// O(log N)
    int search(vector<int>& nums, int target) {
        int n=nums.size();
        if(n==0){
            return -1;
        }
        if(n==1){
            if(nums[0]==target){
                return 0;
            }else{
                return -1;
            }
        }
        int low=0;
        int high=n-1;
        int pivot=-1;//prevent int overflow
        //1,2,3,4,5,6
        //3,4,5,6,1,2
        //we want to find index of 1 but without extensive search 
        if (nums[0]<= nums[n-1]) {
            pivot = -1;
        }
        else{
            while(low<=high){
                //we may also try to check if pivot == target but it will increase if statement each time and each time chances of finding target here will be low so rather not check it
                int mid=low+(high-low)/2;
                if(mid>0&&nums[mid]<nums[mid-1]){
                    pivot=mid;
                    break;
                }
                if(nums[mid]>=nums[0]){//nums[low] will fail !!!!!!!
                    low=mid+1;
                }else{
                    high=mid-1;
                }
            }
        }
        int li=0;
        int ri=n-1;
        if(pivot!=-1){
            if(target>=nums[0]){
                ri=pivot-1;
            }else{
                li=pivot;
            }
        }
        while(li<=ri){
            int mid=li+(ri-li)/2;
            if(nums[mid]==target){
                return mid;
            }else if(nums[mid]>target){
                ri=mid-1;
            }else{
                li=mid+1;
            }
        }
        return -1;
    }
};
//THE 1-PASS SHIFTED VECTOR
//You are strictly forbidden from doing a 2-Pass search. You cannot find the pivot first. You must find the target in a single while loop.
class Rotated_binary_search{
     public:
     int search(vector<int>&input,int target){
        int n=input.size();
        int low=0;
        int high=n-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(input[mid]==target){
                return mid;
            }
            else if(input[mid]>=input[low]){
                if(target>=input[low]&&target<input[mid]){
                    high=mid-1;
                }else{
                    low=mid+1;
                }
            }else{
                if(target<input[low]&&target>input[mid]){//target<=input[high]&&target>input[mid]
                    low=mid+1;
                }else{
                    high=mid-1;
                }
            }
        }
        return -1;
     }
};