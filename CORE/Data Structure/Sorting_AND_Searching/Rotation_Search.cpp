#include<iostream>
#include<vector>
using namespace std;
class Rotation_Search{
    public:
    int rot_seaarch(const vector<int>&array,int target)const{//O(logn)average but in case where whole data is fully duplicate then O(n^2)
        int low=0,high=array.size()-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(array[mid]==target)return mid;
            if(array[low]==array[mid]&&array[mid]==array[high]){//duplicate handle
                low++;
                high--;
            }else if(array[mid]>=array[low]){
                if(target>=array[low]&&target<array[mid]){
                    high=mid-1;
                }else{
                    low=mid+1;
                }
            }else{
                if(target<=array[high]&&target>array[mid]){
                    low=mid+1;
                }else{
                    high=mid-1;
                }
            }
        }
        return -1;
    }
};