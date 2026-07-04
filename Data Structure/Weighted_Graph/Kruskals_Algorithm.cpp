#include<iostream>
#include<vector>
#include<queue>
#include<algorithum>
using namespace std;
class DUS{
    private:
    vector<int>bigboss;
    vector<int>rank;
    public:
    DUS(int vertex){
        bigboss.resize(vertex);
        for(int i=0;i<vertex;i++){
            bigboss[i]=i;
        }
        rank.resize(vertex,1);
    }
    int find(int u){
        if(u!=bigboss[u]){
            bigboss[u]=find(bigboss[u]);
        }
        return bigboss[u];
    }
    void unite(int u,int v){
        int root_u=find(u);
        int root_v=find(v);
        if(root_u==root_v){
            return;
        }
        if(rank[root_u]>rank[root_v]){
            bigboss[root_v]=root_u;
        }
        else if(rank[root_u]<rank[root_v]){
            bigboss[root_u]=root_v;
        }
        else{
            bigboss[root_v]=root_u;
            rank[root_u]+=1;
        }
    }
};
struct e{
    int u,v,w;
};
class Kruskal{
    private:
    const vector<vector<pair<int,int>>>&adjList;
    int vertex;
    DUS dsu;
    public:
    Kruskal(const vector<vector<pair<int,int>>>&a):
    adjList(a),vertex(a.size()),dsu(vertex){}
    
    pair<int,vector<e>>process(){
        vector<e>mst;
        vector<e>edges;
        for(int u=0;u<vertex;u++){
            for(int j=0;j<adjList[u].size();j++){
                int v=adjList[u][j].first;
                int w=adjList[u][j].second;
                edges.push_back({u,v,w});
            }
        }
        sort(edges.begin(),edges.end(),[](const e&a,const e&b){
            return a.w>b.w;//now min will be in last of vector and pop from bask
        });
        int cost=0;
        while(!edges.empty()&&mst.size()<vertex-1){
            auto[u,v,w]=edges.back();
            edges.pop_back();
            if(dsu.find(u)==dsu.find(v)){
                continue;
            }
            cost+=w;
            dsu.unite(u,v);
            mst.push_back({u,v,w});
        }
        return{cost,mst};
    }
};