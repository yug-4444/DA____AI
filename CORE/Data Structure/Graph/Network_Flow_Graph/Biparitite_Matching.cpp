#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<climits>
using namespace std;
class Bipartite_Matching{
    private:
    vector<vector<int>>capacity;//for O(1)asscess
    const vector<vector<int>>&adjList;//directedd edges
    int s,t;//imaginary created by us
    set<int>U,V;//we will have edges only form U->V side and with in a set there will be no interconnection and may edges may have same vertex
    //take this a U->devloper and V->task with condition devloper may qualifu for multiple tasks but in the end with devlopers endergy it can only do one task and our goal is to find such that we can get max (dev,task)pair in end
    //if greedy we want enough backtracking when optimal ->ford fukerson
    //probem ?sorurce and sink make imaginary and edges of weight 1 to each U and V so to show that inflow ==outfow at intermediate vertex
    int vertex;
    //if either of U or V is empty then it means ans will be 0 as no pair can be formed and this also still work
    public:
    Bipartite_Matching(const vector<vector<int>>&a):
    adjList(a),vertex(a.size()){//assuming no The Index Collision Risk else just count and convert 0->u_count+0 ....
        capacity.resize(vertex+2,vector<int>(vertex+2));
        s=vertex;
        t=vertex+1;//they can be any number it doesn't matter
        for(int u=0;u<vertex;u++){//O(V+E)
            if(adjList[u].size()!=0){
                U.insert(u);
            }
            for(int j=0;j<adjList[u].size();j++){
                int v=adjList[u][j];//edges u->v
                V.insert(v);
                capacity[u][v]=1;
            }
        }
        for (int &u:U){
            capacity[s][u]=1;
        }
        for (int &v:V){
            capacity[v][t]=1;
        }
        vertex+=2;
    }
    pair<bool,vector<int>>path(){//O(V+E)
        vector<int>parent(vertex,-1);
        vector<bool>visit(vertex,false);
        queue<int>q;
        q.push(s);
        visit[s]=true;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int v=0;v<vertex;v++){
                if(!visit[v]&&capacity[u][v]>0){
                    visit[v]=true;
                    q.push(v);
                    parent[v]=u;
                    if(v==t){
                        return{true,parent};
                    }
                }
            }
        }
        return{false,{}};
    }
    int process(){//O((V+E)*MAX(U,V)) F=MAX(U,V) ->O(VE)
        //no two edge will have common vertex
        int maxflow=0;
        bool path_Exist=true;
        while(path_Exist){
            auto[found,path_parent]=path();
            path_Exist=found;
            if(!path_Exist){
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
                v=u;
            }
            maxflow+=bottleneck;
        }
        return maxflow;
    }
};