#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class MAX_HEAP{//THE DYNAMIC HEAP
    private:
    vector<int>heap;
    public:
    //left ->2i+1,right ->2i+2,parent->(i-1)/2 ,last leaf node->n/2+1
    void max_heapify(int i){//top->down , parent>=both child nodes
        int lc=2*i+1,rc=2*i+2,largest=i,n=heap.size();
        if(lc<n&&heap[lc]>heap[largest])largest=lc;
        if(rc<n&&heap[rc]>heap[largest])largest=rc;
        if(largest!=i){
            swap(heap[largest],heap[i]);
            max_heapify(largest);
        }
    }
    void insert(int val){
        heap.push_back(val);
        int i=heap.size()-1;
        while(i>0&&heap[(i-1)/2]<heap[i]){//as root at index 0 will have no parent
            swap(heap[(i-1)/2],heap[i]);
            i=(i-1)/2;
        }
    }
    void pop(){
        int n=heap.size();
        if(n==0)return;
        if(n==1){
            heap.pop_back();
            return;
        }
        heap[0]=heap[n-1];
        heap.pop_back();
        max_heapify(0);
    }
    int top(){
        if(heap.size()==0)return INT_MIN;
        return heap[0];
    }
    bool empty(){
        if(heap.size()==0)return true;
        return false;
    }
    int size(){
        return heap.size();
    }
};