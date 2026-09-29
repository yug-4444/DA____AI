#include<iostream>
#include<vector>
using namespace std;
class DSU{
    private:
    vector<int>bigboss;
    vector<int>rank;
    public:
    DSU(int vertex){
        bigboss.resize(vertex);
        rank.resize(vertex,1);
        for(int i=0;i<vertex;i++){
            bigboss[i]=i;//initially all servers are diconnected so the bigboss/root of the self set is themself
        }
    }
    int find(int u){
        //points towards bigboss of set which is root
        if(bigboss[u]!=u){
            bigboss[u]=find(bigboss[u]);
        }
        return bigboss[u];//O(1)time
    }

    void unite(int u,int v){
        int root_u=find(u);
        int root_v=find(v);
        if(root_u==root_v){
            return;//as we can't have loop within already connected components
        }
        if(rank[root_u]>rank[root_v]){//shallow tree connected to deeper tree so that depth doesn't change
            bigboss[root_v]=root_u;
        }
        else if(rank[root_u]<rank[root_v]){//shallow tree connected to deeper tree so that depth doesn't change
            bigboss[root_u]=root_v;
        }
        else{
            bigboss[root_v]=root_u;
            rank[root_u]+=1;
        }
    }
};