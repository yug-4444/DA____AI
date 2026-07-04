#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Prims{//valid only for undirected graph
    //growth stratergy and always remain connected
    private:
    const vector<vector<pair<int,int>>>&adjList;
    int vertex;
    public:
    Prims(const vector<vector<pair<int,int>>>&a):
    adjList(a),vertex(a.size()){}
    pair<int,vector<tuple<int,int,int>>>process(){//{u,v,w} u->v
        vector<tuple<int,int,int>>mst;
        vector<bool>present(vertex,false);
        int start=0;//start anywhere
        priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>>minheap;//{w,u,v}
        int cost=0;
        for(int j=0;j<adjList[start].size();j++){
            int v=adjList[start][j].first;
            int w=adjList[start][j].second;
            minheap.push({w,start,v});
        }
        present[start]=true;
        while(!minheap.empty() && mst.size() < vertex-1){
            auto[w,u,v]=minheap.top();
            if(present[v]){
                continue;
            }
            present[v]=true;
            cost+=w;
            mst.push_back({u,v,w});
            u=v;
            for(int j=0;j<adjList[u].size();j++){
                v=adjList[u][j].first;
                w=adjList[u][j].second;
                if(!present[v]){
                    minheap.push({w,u,v});
                }
            }
        }
        return {cost,mst};
    }
};