#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class MinCostMaxFlow{
    private:
    vector<vector<int>>cost;
    vector<vector<int>>capacity;
    int vertex,s,t;
    public:
    MinCostMaxFlow(vector<vector<int>>cos,vector<vector<int>>cap,int source,int sink):
    cost(cos),capacity(cap),s(source),t(sink),vertex(cos.size()){}
    //we want path w.r.t cost that minimum and valid path i.e water or capacity is allowed>0 
    //cost can be negative so we can use dijikstras to find min cost path instead we will use bellmans ford  
    
    tuple<bool,int,vector<int>>bellman_path(){
        vector<int>parents(vertex,-1);
        vector<int>curr_cost(vertex,INT_MAX);
        curr_cost[s]=0;
        for(int i=0;i<vertex-1;i++){
            for(int u=0;u<vertex;u++){
                for(int v=0;v<vertex;v++){
                    if(curr_cost[u]!=INT_MAX && capacity[u][v]>0 &&curr_cost[u]+cost[u][v]<curr_cost[v]){
                        parents[v]=u;
                        curr_cost[v]=curr_cost[u]+cost[u][v];
                    }
                }
            }
        }
        for(int u=0;u<vertex;u++){
            for(int v=0;v<vertex;v++){
                if(curr_cost[u]!=INT_MAX && capacity[u][v]>0 &&curr_cost[u]+cost[u][v]<curr_cost[v]){
                    return{false,INT_MAX,{}};//-ve cycle
                }
            }
        }
        if(curr_cost[t]==INT_MAX){
            //unreachable
            return{false,INT_MAX,{}};
        }
        return {true,curr_cost[t],parents};
    }
    pair<int,int> process(){
        int total_cost=0;
        bool path_exist=true;
        int maxflow=0;
        while(path_exist){
            auto[found,path_cost,path_parent]=bellman_path();
            path_exist=found;
            if(!path_exist){
                break;
            }
            int bottleneck=INT_MAX;

            int v=t;
            while(v!=s){
                int u=path_parent[v];
                if(bottleneck>capacity[u][v]){
                    bottleneck=capacity[u][v];
                }
                v=u;
            }
            v=t;
            while(v!=s){
                int u=path_parent[v];
                capacity[u][v]-=bottleneck;
                capacity[v][u]+=bottleneck;
                cost[v][u]=-cost[u][v];
                v=u;
            }
            total_cost+=bottleneck*path_cost;
            maxflow+=bottleneck;
        }
        return {total_cost,maxflow};
    }
};