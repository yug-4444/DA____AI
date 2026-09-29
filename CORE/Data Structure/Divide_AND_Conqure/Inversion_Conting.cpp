#include<iostream>
#include<vector>
using namespace std;
class Inversion_counting{
    private:
    vector<int>&array;
    int n;
    long long inversion_count;
    vector<int>temp;
    public:
    Inversion_counting(vector<int>&a):
    array(a),n(array.size()){
        inversion_count=0;
        temp.resize(n);
    }
    void merge(int low,int mid,int high){
        for(int i=low;i<=high;i++)temp[i]=array[i];
        int i=low,j=mid+1,k=i;
        while(i<=mid&&j<=high){
            if(temp[i]>temp[j]){
                inversion_count+=mid-i+1;
                array[k++]=temp[j++];
            }
            else{
                array[k++]=temp[i++];
            }
        }
        while(i<=mid)array[k++]=temp[i++];
        while(j<=high)array[k++]=temp[j++];
    }
    void merge_sort(int low,int high){
        if(low<high){
            int mid=low+(high-low)/2;
            merge_sort(low,mid);
            merge_sort(mid+1,high);
            merge(low,mid,high);
        }
    }
    long long process(){
        merge_sort(0,n-1);
        return inversion_count;
    }
};