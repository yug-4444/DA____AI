#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class bellman{
    private:
    const vector<vector<pair<int,int>>>&adjList;
    int vertex;
    int source;
    public:
    bellman(const vector<vector<pair<int,int>>>&a,int s):
    source(s),vertex(a.size()),adjList(a){}
    //valid for any type of weight as well as its a negative weight detector
    //when we have a negative cycle its become imposible to find shortes as in infinity loop it doesn't stop but keep going on as it gets cheper
    pair<bool,vector<int>>process(){//bute force methord that takes into consideration if the order of the edges arranged by be worst case 
        vector<int>dis(vertex,INT_MAX);
        vector<int>parent(vertex,-1);
        dis[source]=0;
        bool cycle=false;
        for(int i=0;i<vertex-1;i++){
            //all vertex largest no cycle path will have v-1 cables
            //to detect when not worst mameroy scrabled case
            bool update=false;
            for(int u=0;u<vertex;u++){
                for(int j=0;j<adjList[u].size();j++){
                    int v=adjList[u][j].first;
                    int w=adjList[u][j].second;
                    if(dis[u]!=INT_MAX && dis[u]+w<dis[v]){
                        update=true;
                        dis[v]=dis[u]+w;
                        parent[v]=u;
                    }
                }
            }
            if (!update){
                break;
            }
        }
        //if at vth time still get a change or relaxed then cycle
        for(int u=0;u<vertex;u++){
            for(int j=0;j<adjList[u].size();j++){
                int v=adjList[u][j].first;
                int w=adjList[u][j].second;
                if(dis[u]!=INT_MAX && dis[u]+w<dis[v]){//rechable and -ve cycle
                    cycle=true;
                    return{cycle,{}};
                }
            }
        }
        return{cycle,dis};
    }
};