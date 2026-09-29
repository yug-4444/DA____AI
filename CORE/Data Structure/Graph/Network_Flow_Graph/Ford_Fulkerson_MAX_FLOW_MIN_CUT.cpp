//network flow
#include<iostream>
#include<queue>
#include<vector>
#include<climits>
using namespace std;
class MaxFlow{
    private:
    const vector<vector<pair<int,int>>>&adjList;
    vector<vector<int>>capacity;
    int vetrex;
    int s;//source
    int t;//sink
    public:
    MaxFlow(const vector<vector<pair<int,int>>>&ad):
    adjList(ad),vetrex(adjList.size()){
        capacity.resize(vetrex,vector<int>(vetrex,0));//adj matrix type so that O(1)time
        vector<bool>incomeing(vetrex,false);
        for (int u=0;u<vetrex;u++){
            if(adjList[u].size()==0){//all incoming no outgoing
                t=u;
            }
            for(int j=0;j<adjList[u].size();j++){
                int v=adjList[u][j].first;
                int cap=adjList[u][j].second;
                incomeing[v]=true;
                capacity[u][v]=cap;//initially all forward flow as capacity and all backflow as 0 initialize
            }
        }
        for(int i=0;i<vetrex;i++){
            if(!incomeing[i]){
                s=i;
                break;//as there will only be exactly one source and one sink in entire network
            }
        }
    }
    pair<bool,vector<int>> path(){
        bool validPath=true;
        vector<int>parent(vetrex,-1);
        vector<bool>visit(vetrex,false);
        queue<int>q;
        //s->....->t path
        q.push(s);
        visit[s]=true;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int v=0;v<vetrex;v++){
                if(visit[v]==false&&capacity[u][v]>0){
                    visit[v]=true;
                    parent[v]=u;
                    if(v==t){
                        return {true,parent};
                    }
                    q.push(v);
                }
            }
        }
        //if we reach here then it means no such path exist where water can further flow i.e it means that we have our anwser
        return {false,{}};//{stop,parent}
    }
    int process(){
        int MaximumFlow=0;
        bool pathexist=true;//stop the loop if no path exist further more to carry more weight
        while(pathexist){
            auto [found,path_parent]=path();
            pathexist=found;
            if(!pathexist){
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
            MaximumFlow+=bottleneck;
            //create pantom pipes and reduce forward pipe capacities
            v=t;
            while(v!=s){
                int u=path_parent[v];
                //u->v forwaard and v->>u backward
                capacity[u][v]-=bottleneck;
                capacity[v][u]+=bottleneck;
                v=u;
            }
        }
        return MaximumFlow;
    }
};
class Mincut{
    private:
    const vector<vector<pair<int,int>>>&adjList;
    vector<vector<int>>capacity;
    int s,t,vetrex;
    public:
    Mincut(const vector<vector<pair<int,int>>>&a):
    adjList(a),vetrex(a.size()){
        capacity.resize(vetrex,vector<int>(vetrex,1));
        vector<bool>source(vetrex,true);
        for(int u=0;u<vetrex;u++){
            if(adjList[u].size()==0){
                t=u;
            }
            for(int j=0;j<adjList[u].size();j++){
                int v=adjList[u][j].first;
                int cap=adjList[u][j].second;
                capacity[u][v]=cap;
                source[v]=false;
            }
        }
        for(int u=0;u<vetrex;u++){
            if(source[u]){
                s=u;
            }
        }
    }
    pair<bool,vector<int>>path(){
        //bfs
        queue<int>q;
        vector<int>parent(vetrex,-1);
        vector<bool>visit(vetrex,false);
        q.push(s);
        visit[s]=true;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int v=0;v<vetrex;v++){
                if(visit[v]==false&&capacity[u][v]>0){
                    visit[v]=true;
                    parent[v]=u;
                    q.push(v);
                    if(v==t){
                        return{true,parent};
                    }
                }
            }
        }
        return {false,{}};
    }
    pair<int,vector<tuple<int,int,int>>>process(){
        int maxflow=0;
        bool pathExist=true;
        while(pathExist){
            auto[found,path_parents]=path();
            pathExist=found;
            if(!pathExist){
                break;
            }
            int v=t;
            int bottleneck=INT_MAX;
            while(v!=s){
                int u=path_parents[v];
                if(bottleneck>capacity[u][v]){
                    bottleneck=capacity[u][v];
                }
                v=u;
            }
            v=t;
            while(v!=s){
                int u=path_parents[v];
                capacity[u][v]-=bottleneck;
                capacity[v][u]+=bottleneck;
                v=u;
            }
            maxflow+=bottleneck;
        }
        queue<int>q;
        vector<int>parent(vetrex,-1);
        vector<bool>visit(vetrex,false);
        q.push(s);
        visit[s]=true;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int v=0;v<vetrex;v++){
                if(visit[v]==false&&capacity[u][v]>0){
                    visit[v]=true;
                    parent[v]=u;
                    q.push(v);
                }
            }
        }
        //set S-> visit->true and set T ->visit->false
        int min_cut=0;
        vector<tuple<int,int,int>>cut_edges;
        //use orignal capcity
        for(int u=0;u<vetrex;u++){
            for(int j=0;j<adjList[u].size();j++){
                int v=adjList[u][j].first;
                int cap=adjList[u][j].second;
                if(visit[u]&&!visit[v]){
                    cut_edges.push_back({u,v,cap});
                    min_cut+=cap;
                }
                // All nodes 'visit[i] == true' belong to set S
                // All nodes 'visit[i] == false' belong to set T
            }
        }
        return{min_cut,cut_edges};
    }
};//mincut will be equal to that of max flow 