#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class Lazy_Segment_Tree{
    public:
    vector<int>&arr;
    vector<int>tree;
    vector<int>lazy_tag;
    int n;
    public:
    Lazy_Segment_Tree(vector<int>&input):
    arr(input),n(arr.size()){
        tree.resize(4*n);
        lazy_tag.resize(4*n,0);
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
    void update_range(int i,int start,int end,int L,int R,int val){
        int lc=2*i+1,rc=2*i+2,mid=start+(end-start)/2;
        if(lazy_tag[i]!=0){
            tree[i]+=(end-start+1)*lazy_tag[i];
            if(start!=end){
                lazy_tag[lc]+=lazy_tag[i];
                lazy_tag[rc]+=lazy_tag[i];
            }
            lazy_tag[i]=0;
        }
        if(start>R||end<L)return;
        if(start>=L&&end<=R){
            tree[i]+=(end-start+1)*val;
            if(start!=end){
                lazy_tag[lc]+=val;
                lazy_tag[rc]+=val;
            }
            return;
        }
        update_range(lc,start,mid,L,R,val);
        update_range(rc,mid+1,end,L,R,val);
        tree[i]=tree[lc]+tree[rc];
    }
    int range_query(int i,int start,int end,int L,int R){
        int lc=2*i+1,rc=2*i+2,mid=start+(end-start)/2;
        if(lazy_tag[i]!=0){
            tree[i]+=(end-start+1)*lazy_tag[i];
            if(start!=end){
                lazy_tag[lc]+=lazy_tag[i];
                lazy_tag[rc]+=lazy_tag[i];
            }
            lazy_tag[i]=0;
        }
        if(start>R||end<L)return 0;
        if(start>=L&&end<=R)return tree[i];
        return range_query(lc,start,mid,L,R)+range_query(rc,mid+1,end,L,R);
    }
};//O(logn)both query and update even when we have to update like from index 10 to 90 add 5 to each now takes O(log n)time