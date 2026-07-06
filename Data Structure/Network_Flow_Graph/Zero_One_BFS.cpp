//bfs normal each edge considered weight same but if weights vary too much and we have to go from A->B in shortest time 
//we think of applying dijikstras but time O(logV(V+E))
//we want to further reduce time thinking since two tyes of weight then why not use deque ->O(V+E)time now
#include<iostream>
#include<vector>
#include<deque>
#include<climits>
#include<algorithm>
using namespace std;
class ZeroOneBFS{
    private:
    const vector<vector<pair<int,int>>>&adjList;
    int vertex;
    int start,finish;
    public:
    ZeroOneBFS(const vector<vector<pair<int,int>>>&a,int s,int f):
    adjList(a),vertex(a.size()),start(s),finish(f){}
    vector<pair<int,int>> process(){
        deque<int>dq;//[0.....0,1......1]type weight format and since shortest weight path ->pop from front
        vector<int>parents(vertex,-1);
        vector<int>dis(vertex,INT_MAX);
        vector<pair<int,int>>path;
        dis[start]=0;
        dq.push_back(start);
        while(!dq.empty()){
            int u=dq.front();
            dq.pop_front();
            for(int i=0;i<adjList[u].size();i++){
                int v=adjList[u][i].first;
                int w=adjList[u][i].second;
                if(dis[u]!=INT_MAX&&dis[u]+w<dis[v]){
                    parents[v]=u;
                    dis[v]=dis[u]+w;
                    if(w==0){
                        dq.push_front(v);
                    }else{
                        dq.push_back(v);
                    }
                }
            }
        }
        if(dis[finish]==INT_MAX){
            cout<<"NO SUCH PATH EXIST\n";
            return {};
        }
        int v=finish;
        while(v!=start){
            int u=parents[v];
            path.push_back({u,v});
            v=u;
        }
        reverse(path.begin(), path.end());
        return path;
    }
};