#include<iostream>
#include<vector>
using namespace std;
class Heap_Sort{//space-time compramise
    public:
    //heap sort is most optimized version used purely using arithematic in this it has both strict O(nlogn)time and O(1)auxilary space 
    //left child->2i+1 ; right child->2i+2  ;  parent->(i-1)/2
    //max heap 
    void max_heapify(vector<int>&array,int heap_size,int i){//parent>=its child property
        //sinking
        int lc=2*i+1,rc=2*i+2;
        int largest=i;
        if(lc<heap_size&&array[largest]<array[lc]) largest=lc;
        if(rc<heap_size&&array[largest]<array[rc]) largest=rc;
        
        if(largest!=i){
            swap(array[largest],array[i]);
            max_heapify(array,heap_size,largest);
        }
    }
    void build_max_heap(vector<int>&array,int heap_size){//takes O(n)time*********************************************************************
        //last non-leaf node as posn n/2-1
        for(int i=heap_size/2-1;i>=0;i--){
            max_heapify(array,heap_size,i);
        }
    }
    void max_heap_sort(vector<int>&array){
        int n=array.size();
        build_max_heap(array,n);
        for(int i=n-1;i>=1;i--){
            swap(array[0],array[i]);
            max_heapify(array,i,0);
        }
    }

    //min heap 
    void min_heapify(vector<int>&array,int heap_size,int i){//parent=<its child property
        int lc=2*i+1,rc=2*i+2,smallest=i;
        if(lc<heap_size&&array[smallest]>array[lc])smallest=lc;
        if(rc<heap_size&&array[smallest]>array[rc])smallest=rc;
        if(smallest!=i){
            swap(array[smallest],array[i]);
            min_heapify(array,heap_size,smallest);
        }
    }
    void build_min_heap(vector<int>&array,int heap_size){//takes O(n)time*********************************************************************
        for(int i=heap_size/2-1;i>=0;i--){
             min_heapify(array,heap_size,i);
        }
    }
    void min_heap_sort(vector<int>&array){
        int n=array.size();
        build_min_heap(array,n);
        for(int i=n-1;i>=1;i--){
            swap(array[0],array[i]);
            min_heapify(array,i,0);
        }
    }
};