#include<iostream>
#include<climits>
#include<queue>
#include<vector>
using namespace std;
class Dijikstras{
    private:
    const vector<vector<pair<int,int>>>&adjList;//{u,weight}
    int vertex;
    int source;
    public:
    Dijikstras(const vector<vector<pair<int,int>>>&a,int s):
    adjList(a),vertex(a.size()),source(s){}
    bool vaildity(){
        for(int i=0;i<vertex;i++){
            for(int j=0;j<adjList[i].size();j++){
                int w=adjList[i][j].second;
                if(w<0){
                    return false;
                }
            }
        }
        return true;
    }
    vector<int> process(){
        if (!validity()){
            cout << "Negative weights detected. Dijkstra aborting." << endl;
            return {};
        }
        vector<int>dis(vertex,INT_MAX);//cost from single source to all vertex
        dis[source]=0;
        vector<int>parent(vertex,-1);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>min_heap;
        min_heap.push({dis[source],source});//// The Min-Heap stores {distance, vertex_id}
        while (!min_heap.empty()){
            int curr_dis=min_heap.top().first;
            int u=min_heap.top().second;
            min_heap.pop();
            if(dis[u]<curr_dis){
                continue;//as weight will be positive so one we get a vertex out of min-heap that means it will be shortest overall can't be more shorter
            }
            //dis[u]=curr_dis auto maticcaly as dis either be greater or equal as we are dealing with +ve weights with time path weight increses
            for(int i=0;i<adjList[u].size();i++){
                int v=adjList[u][i].first;
                int w=adjList[u][i].second;
                if(dis[u]+w<dis[v]){
                    dis[v]=dis[u]+w;
                    parent[v]=u;
                    min_heap.push({dis[v],v});
                }
            }
        }
        return dis;
    }
};