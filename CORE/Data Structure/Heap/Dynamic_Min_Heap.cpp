#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class MIN_HEAP{//THE DYNAMIC HEAP
    private:
    vector<int>heap;
    int n;
    public:
    MIN_HEAP(){
        n=0;
    }
    //left ->2i+1,right ->2i+2,parent->(i-1)/2 ,last leaf node->n/2+1
    void min_heapify(int i){//top->down , parent<=both child nodes
        int lc=2*i+1,rc=2*i+2,smallest=i;
        if(lc<n&&heap[lc]<heap[smallest])smallest=lc;
        if(rc<n&&heap[rc]<heap[smallest])smallest=rc;
        if(smallest!=i){
            swap(heap[smallest],heap[i]);
            min_heapify(smallest);
        }
    }
    void insert(int val){
        n++;
        heap.push_back(val);
        int i=n-1;
        while(i>0&&heap[(i-1)/2]>heap[i]){//as root at index 0 will have no parent
            swap(heap[(i-1)/2],heap[i]);
            i=(i-1)/2;
        }
    }
    void pop(){
        if(n==0)return;
        if(n==1){
            heap.pop_back();
            n--;
            return;
        }
        heap[0]=heap[n-1];
        heap.pop_back();
        n--;
        min_heapify(0);
    }
    int top(){
        if(n==0)return INT_MAX;
        return heap[0];
    }
    bool empty(){
        if(n==0)return true;
        return false;
    }
    int size(){
        return n;
    }
};