#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class SegmentTree_range_sum{
    private:
    vector<int>&arr;
    vector<int>tree;
    int n;
    public:
    SegmentTree_range_sum(vector<int>&input):
    arr(input),n(arr.size()){
        tree.resize(4*n);
    }
    void build(int i,int start,int end){
        if(start==end){
            tree[i]=arr[start];
            return;
        }
        int mid=start+(end-start)/2;
        int lc=2*i+1,rc=2*i+2;
        build(lc,start,mid);
        build(rc,mid+1,end);
        tree[i]=tree[lc]+tree[rc];
    }
    void update(int i,int start,int end,int index,int val){
        if(start==end&&start==index){
            tree[i]=val;
            arr[index]=val;
            return;
        }
        int lc=2*i+1,rc=2*i+2;
        int mid=start+(end-start)/2;
        if(index<=mid)update(lc,start,mid,index,val);
        else update(rc,mid+1,end,index,val);
        tree[i]=tree[lc]+tree[rc];
    }
    int queries(int i,int start,int end,int L,int R){
        if(L>end||start>R)return 0;//no overlap
        if(L<=start&&R>=end)return tree[i];//fully overlap
        int lc=2*i+1,rc=2*i+2,mid=start+(end-start)/2;
        return queries(lc,start,mid,L,R)+queries(rc,mid+1,end,L,R);//partial overlap
    }
};


class SegmentTree_range_min{
    private:
    vector<int>&arr;
    vector<int>tree;
    int n;
    public:
    SegmentTree_range_min(vector<int>&input):
    arr(input),n(arr.size()){
        tree.resize(4*n);
    }
    void build(int i,int start,int end){
        if(start==end){
            tree[i]=arr[start];
            return;
        }
        int mid=start+(end-start)/2,lc=2*i+1,rc=2*i+2;
        build(lc,start,mid);
        build(rc,mid+1,end);
        tree[i]=tree[rc]>tree[lc]?tree[lc]:tree[rc];
    }
    void update(int i,int start,int end,int index,int val){
        if(start==end&&start==index){
            arr[index]=val;
            tree[i]=val;
            return;
        }
        int mid=start+(end-start)/2,lc=2*i+1,rc=2*i+2;
        if(index<=mid)update(lc,start,mid,index,val);
        else update(rc,mid+1,end,index,val);
        tree[i]=tree[rc]>tree[lc]?tree[lc]:tree[rc];
    }
    int queries(int i,int start,int end,int L,int R){
        if(start>R||end<L)return INT_MAX;
        if(L<=start&&R>=end)return tree[i];
        int mid=start+(end-start)/2,lc=2*i+1,rc=2*i+2;
        return min(queries(lc,start,mid,L,R),queries(rc,mid+1,end,L,R));
    }
};


class SegmentTree_range_max{
    private:
    vector<int>&arr;
    vector<int>tree;
    int n;
    public:
    SegmentTree_range_max(vector<int>&input):
    arr(input),n(arr.size()){
        tree.resize(4*n);
    }
    void build(int i,int start,int end){
        if(start==end){
            tree[i]=arr[start];
            return;
        }
        int mid=start+(end-start)/2,lc=2*i+1,rc=2*i+2;
        build(lc,start,mid);
        build(rc,mid+1,end);
        tree[i]=tree[rc]<tree[lc]?tree[lc]:tree[rc];
    }
    void update(int i,int start,int end,int index,int val){
        if(start==end&&start==index){
            arr[index]=val;
            tree[i]=val;
            return;
        }
        int mid=start+(end-start)/2,lc=2*i+1,rc=2*i+2;
        if(index<=mid)update(lc,start,mid,index,val);
        else update(rc,mid+1,end,index,val);
        tree[i]=tree[rc]<tree[lc]?tree[lc]:tree[rc];
    }
    int queries(int i,int start,int end,int L,int R){
        if(start>R||end<L)return INT_MIN;
        if(L<=start&&R>=end)return tree[i];
        int mid=start+(end-start)/2,lc=2*i+1,rc=2*i+2;
        return max(queries(lc,start,mid,L,R),queries(rc,mid+1,end,L,R));
    }
};