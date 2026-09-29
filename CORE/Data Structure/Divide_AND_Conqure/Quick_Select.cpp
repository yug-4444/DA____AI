#include<vector>
#include<iostream>
#include<climits>
using namespace std;
class QuickSelect{
    private:
    vector<int>array;
    int n;
    int k;
    public:
    //kth smallest is k-1 postion in sorted ascending array
    QuickSelect(vector<int>a,int kth):
    array(a),n(array.size()),k(kth){}
    int Lamuto_partition(int low,int high){
        swap(array[high],array[low+(high-low)/2]);
        int pivot=array[high];
        int i=low-1;
        for(int j=low;j<high;j++){
            if(array[j]<=pivot){
                i++;
                swap(array[i],array[j]);
            }
        }
        i++;
        swap(array[i],array[high]);
        return i;
    }
    int quick_select(int low,int high){
        if(low<=high){
            int p=Lamuto_partition(low,high);
            if(p==k-1)return array[p];
            else if(p>k-1)return quick_select(low,p-1);
            else return quick_select(p+1,high);
        }
        return INT_MAX;
    }
    int process(){//O(n)time complexity
        if(k<1||k>n)return INT_MAX;
        return quick_select(0,n-1);
    }
};