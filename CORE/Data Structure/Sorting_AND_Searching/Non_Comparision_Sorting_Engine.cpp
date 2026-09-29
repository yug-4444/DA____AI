//counting, radix ,bucket non-comparision sorts
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
class non_comparision{
    public:
    //1.COUNTING SORT -> stable and not in-place
    //O(n+k) time and space complexity
    //frequency tally
    //its normal form won't directly work in case when we have -ve or float data type we wound at that time need to offset it by something so that it may work
    void counting_sort(vector<int>&input){
        int n=input.size(),k=input[0];
        for(int i=1;i<n;i++){
            if(k<input[i])k=input[i];
        }
        vector<int>count_array(k+1,0);
        for(int i=0;i<n;i++){
            count_array[input[i]]++;
        }
        for(int i=1;i<=k;i++){
            count_array[i]+=count_array[i-1];//prefix sum which will now directly tell us the start index
        }
        vector<int>output(n);
        for(int i=n-1;i>=0;i++){//to maintain stability
            output[--count_array[input[i]]]=input[i];
        }
        input=output;
    }

    //2.RADIX SORT -> stable and not in-place
    //O(d(n+b))time complexity and O(n+b)space complexity
    //digit processor 
    //we move from LSD to MSD not reverse as of counting sort stability
    void radix_sort(vector<int>&input){
        int n=input.size();
        int b=10;
        int maxi=input[0];
        for(int i=1;i<n;i++){
            if(maxi<input[i])maxi=input[i];
        }
        for(int exp=1;maxi/exp>0;exp*=b){
            vector<int>count(b,0);
            for(int i=0;i<n;i++){
                int curr=(input[i]/exp)%b;
                count[curr]++;
            }
            for(int i=1;i<b;i++){
                count[i]+=count[i-1];
            }
            vector<int>output(n);
            for(int i=n-1;i>=0;i--){
                int curr=(input[i]/exp)%b;
                output[--count[curr]]=input[i];
            }
            input=output;
        }
    }

    //3.BUCKET SORT ->stable and not in-place
    //O(n)time and space complexity
    //genrally buckets size are very small so fastest sort will be insertion sort not quick sort
    //float poiny engine
    void insertion_sort_helper(vector<float>&array){
        int n=array.size();
        for(int i=1;i<n;i++){
            float curr=array[i];
            int j=i-1;
            while(j>=0&&array[j]>curr){
                array[j+1]=array[j--];
            }
            array[j+1]=curr;
        }
    }
    void bucket_sort(vector<float>&array){
        int n=array.size();
        vector<vector<float>>bucket(n);
        for(int i=0;i<n;i++){
            int index=floor(array[i]*n);
            bucket[index].push_back(array[i]);
        }
        for(int i=0;i<n;i++){
            insertion_sort_helper(bucket[i]);
        }
        int k=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<bucket[i].size();j++){
                array[k++]=bucket[i][j];
            }
        }
    }
};