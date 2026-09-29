#include<iostream>
#include<vector>
using namespace std;
class Inversion_Count{
    private:
    long long inver_count;
    int n;
    vector<int>input;
    vector<int>temp;
    public:
    Inversion_Count(vector<int>i):
    input(i),n(input.size()){
        inver_count=0;
        temp.resize(n);
    }
    //An inversion is a pair (i,j) such that i<j and input[i]>input[j]

    void merge(int low,int mid,int high){
        for(int i=low;i<=high;i++){
            temp[i]=input[i];
        }
        int i=low,j=mid+1,k=low;
        while(i<=mid&&j<=high){
            if(temp[i]>temp[j]){
                inver_count+=mid-i+1;
                input[k++]=temp[j++];
            }else{
                input[k++]=temp[i++];
            }
        }
        while (i <= mid) input[k++] = temp[i++];
        while (j <= high) input[k++] = temp[j++];
    }
    void merge_sort(int low,int high){
        if(low<high){
            int mid=low+(high-low)/2;
            merge_sort(low,mid);
            merge_sort(mid+1,high);
            merge(low,mid,high);
        }
    }
    long long countInversions(){
        merge_sort(0,n-1);
        return inver_count;
    }
};