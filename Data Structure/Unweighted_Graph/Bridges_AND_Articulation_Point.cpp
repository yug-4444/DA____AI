//bridge with both iterative and call stack approch
//articulation point with both iterative and call stack approch
#include <iostream>
#include<stack>
#include<vector>
using namespace std;
//only for UNDIRECTED GRAPH not valid for directed as in directed graph case when we encounter cross or forward edges it will completely shatter logic below so insted we use strongly conected component concept in them
class Bridge{//TARJAN'S
    private:
    const vector<vector<int>>&adjList;
    vector<pair<int,int>>bri;
    int vertex;
    public:
    Bridge(const vector<vector<int>>&a):
    adjList(a),vertex(a.size()){}

    void DFS_visit(int u,int &time,vector<int>&parent,vector<int>&discover,vector<int>&lowest_time,vector<bool>&state){
        time+=1;
        discover[u]=time;
        lowest_time[u]=discover[u];//atlest reach itself
        state[u]=true;
        for(int i=0;i<adjList[u].size();i++){
            int v=adjList[u][i];
            if(parent[u]==v){
                continue;
            }
            if(state[v]==false){
                parent[v]=u;
                DFS_visit(v,time,parent,discover,lowest_time,state);
                lowest_time[u]=min(lowest_time[u],lowest_time[v]);
                if(lowest_time[v]>discover[u]){//stricty greater as well as equal means it can loop back to it parent without the parent and child cable itself 
                    bri.push_back({u,v});
                }
            }
            else if(state[v]==true){//back edge 
                lowest_time[u]=min(lowest_time[u],discover[v]);//directly say lowest_time[u]=discovery[v] as must be found before our current node that is only in cases edges are not repeated else min is for besy
                //as well as we use discover[v] not lowest_time[v] as we are only to check just one back edge to ancestor so to avoid bridge
            }

        }
        //desn't matter wheater we increase time here or not as we have no need for finish time
    }
    vector<pair<int,int>> process(){
        bri.clear();
        vector<int>parent(vertex,-1);
        vector<int>discover(vertex,-1);
        vector<int>lowest_time(vertex,-1);
        vector<bool>state(vertex,false);
        int time=-1;
        //dfs
        for(int i=0;i<vertex;i++){
            if(state[i]==false){
                DFS_visit(i,time,parent,discover,lowest_time,state);
            }
        }
        return bri;
    }

    vector<pair<int,int>> process_iter(){
        bri.clear();
        vector<int>parent(vertex,-1);
        vector<int>discover(vertex,-1);
        vector<int>lowest_time(vertex,-1);
        vector<bool>state(vertex,false);
        int time=-1;
        //dfs
        for(int i=0;i<vertex;i++){
            if(state[i]==false){
                stack<int>st;
                vector<int>jcount(vertex,-1);
                st.push(i);
                while(!st.empty()){
                    int u=st.top();
                    if(state[u]==false){
                        state[u]=true;
                        time+=1;
                        discover[u]=time;
                        lowest_time[u]=time;
                    }
                    int &j=jcount[u];
                    j+=1;
                    while(j<adjList[u].size()){
                        int v=adjList[u][j];
                        if(parent[u]==v){
                            j+=1;
                            continue;
                        }
                        if(state[v]==true){
                            lowest_time[u]=min(lowest_time[u],discover[v]);
                        }
                        else{
                            parent[v]=u;
                            st.push(v);
                            break;
                        }
                        j+=1;
                    }
                    if(j==adjList[u].size()){
                        if(parent[u]!=-1){
                            int v=u;
                            u=parent[v];
                            lowest_time[u]=min(lowest_time[u],lowest_time[v]);
                            if(lowest_time[v]>discover[u]){
                                bri.push_back({u,v});
                            }
                        }
                        st.pop();
                    }
                }
            }
        }
        return bri;
    }

};
class ArticulationPoint{
    //articulation points are those whose deactivation diconnects the whole graph
    private:
    const vector<vector<int>>&adjList;
    vector<int>points;
    int vertex;
    public:
    ArticulationPoint(const vector<vector<int>>&a):
    adjList(a),vertex(a.size()){}
    void DFS_visit(int u,int &time,vector<int>&parent,vector<int>&discover,vector<int>&lowest_time,vector<bool>&visit,vector<bool>&ap){
        time+=1;
        visit[u]=true;
        discover[u]=time;
        lowest_time[u]=time;
        int child=0;
        for(int i=0;i<adjList[u].size();i++){
            int v=adjList[u][i];
            if(parent[u]==v){
                continue;
            }
            if(visit[v]==true){
                //back edge
                lowest_time[u]=min(lowest_time[u],discover[v]);
            }
            else{
                parent[v]=u;
                child+=1;
                DFS_visit(v,time,parent,discover,lowest_time,visit,ap);
                lowest_time[u]=min(lowest_time[u],lowest_time[v]);
                if(parent[u]!=-1&&lowest_time[v]>=discover[u]){//only when not root case 
                    ap[u]=true;
                }
            }
        }
        if(parent[u]==-1&&child>1){//only when root case 
            ap[u]=true;
        }
    }
    vector<int>process(){
        points.clear();
        vector<int>parent(vertex,-1);
        vector<int>discover(vertex,-1);
        vector<int>lowest_time(vertex,-1);
        vector<bool>visit(vertex,false);
        vector<bool>ap(vertex,false);
        int time=-1;
        for(int i=0;i<vertex;i++){
            if(visit[i]==false){
                DFS_visit(i,time,parent,discover,lowest_time,visit,ap);
            }
        }
        for(int i=0;i<vertex;i++){
            if(ap[i]==true){
                points.push_back(i);
            }
        }
        return points;
    }
    vector<int>process_iter(){
        points.clear();
        vector<int>parent(vertex,-1);
        vector<int>discover(vertex,-1);
        vector<int>lowest_time(vertex,-1);
        vector<bool>visit(vertex,false);
        vector<bool>ap(vertex,false);
        int time=-1;
        for(int i=0;i<vertex;i++){
            if(visit[i]==false){
                stack<int>st;
                vector<int>jcount(vertex,-1);
                st.push(i);
                int child=0;//in a one dfs root each time reset to zero in case when there is another root
                while(!st.empty()){
                    int u=st.top();
                    if(visit[u]==false){
                        visit[u]=true;
                        time+=1;
                        discover[u]=time;
                        lowest_time[u]=time;
                    }
                    int&j=jcount[u];
                    j+=1;
                    while(j<adjList[u].size()){
                        int v=adjList[u][j];
                        if(parent[u]==v){
                            j+=1;
                            continue;
                        }
                        if(visit[v]==false){
                            parent[v]=u;
                            if(parent[u]==-1){
                                child+=1;
                            }
                            st.push(v);
                            break;
                        }
                        else{
                            lowest_time[u]=min(lowest_time[u],discover[v]);
                        }
                        j+=1;
                    }
                    if(j==adjList[u].size()){
                        st.pop();
                        int v=u;
                        u=parent[v];
                        if(u!=-1){
                            lowest_time[u]=min(lowest_time[u],lowest_time[v]);
                            if(parent[u]!=-1&&lowest_time[v]>=discover[u]){
                                ap[u]=true;
                            }
                        }
                    }
                }
                if(child>1){
                    ap[i]=true; 
                }
            }
        }
        for(int i=0;i<vertex;i++){
            if(ap[i]==true){
                points.push_back(i);
            }
        }
        return points;
    }
};
class Bridge__AND__ArticulationPoint{
    private:
    const vector<vector<int>>&adjList;
    vector<int>points;
    vector<pair<int,int>>bri;
    int vertex;
    public:
    Bridge__AND__ArticulationPoint(const vector<vector<int>>&a):
    adjList(a),vertex(a.size()){}

    void DFS_visit(int u,int &time,vector<int>&parent,vector<int>&discover,vector<int>&lowest_time,vector<bool>&visit,vector<bool>&ap){
        time+=1;
        visit[u]=true;
        discover[u]=time;
        lowest_time[u]=time;
        int child=0;
        for(int i=0;i<adjList[u].size();i++){
            int v=adjList[u][i];
            if(parent[u]==v){
                continue;
            }
            if(visit[v]==true){
                //back edge
                lowest_time[u]=min(lowest_time[u],discover[v]);
            }
            else{
                parent[v]=u;
                child+=1;
                DFS_visit(v,time,parent,discover,lowest_time,visit,ap);
                lowest_time[u]=min(lowest_time[u],lowest_time[v]);
                if(parent[u]!=-1&&lowest_time[v]>=discover[u]){//only when not root case 
                    ap[u]=true;
                }
                if(lowest_time[v]>discover[u]){
                    bri.push_back({u,v});
                }
            }
        }
        if(parent[u]==-1&&child>1){//only when root case 
            ap[u]=true;
        }
    }
    pair<vector<int>,vector<pair<int,int>>>process(){
        points.clear();
        bri.clear();
        vector<int>parent(vertex,-1);
        vector<int>discover(vertex,-1);
        vector<int>lowest_time(vertex,-1);
        vector<bool>visit(vertex,false);
        vector<bool>ap(vertex,false);
        int time=-1;
        for(int i=0;i<vertex;i++){
            if(visit[i]==false){
                DFS_visit(i,time,parent,discover,lowest_time,visit,ap);
            }
        }
        for(int i=0;i<vertex;i++){
            if(ap[i]==true){
                points.push_back(i);
            }
        }
        return {points,bri};
    }
    pair<vector<int>,vector<pair<int,int>>>process_iter(){
        points.clear();
        bri.clear();
        vector<int>parent(vertex,-1);
        vector<int>discover(vertex,-1);
        vector<int>lowest_time(vertex,-1);
        vector<bool>visit(vertex,false);
        vector<bool>ap(vertex,false);
        int time=-1;
        for(int i=0;i<vertex;i++){
            if(visit[i]==false){
                stack<int>st;
                vector<int>jcount(vertex,-1);
                st.push(i);
                int child=0;//in a one dfs root each time reset to zero in case when there is another root
                while(!st.empty()){
                    int u=st.top();
                    if(visit[u]==false){
                        visit[u]=true;
                        time+=1;
                        discover[u]=time;
                        lowest_time[u]=time;
                    }
                    int&j=jcount[u];
                    j+=1;
                    while(j<adjList[u].size()){
                        int v=adjList[u][j];
                        if(parent[u]==v){
                            j+=1;
                            continue;
                        }
                        if(visit[v]==false){
                            parent[v]=u;
                            if(parent[u]==-1){
                                child+=1;
                            }
                            st.push(v);
                            break;
                        }
                        else{
                            lowest_time[u]=min(lowest_time[u],discover[v]);
                        }
                        j+=1;
                    }
                    if(j==adjList[u].size()){
                        st.pop();
                        int v=u;
                        u=parent[v];
                        if(u!=-1){
                            lowest_time[u]=min(lowest_time[u],lowest_time[v]);
                            if(parent[u]!=-1&&lowest_time[v]>=discover[u]){
                                ap[u]=true;
                            }
                            if(lowest_time[v]>discover[u]){
                                bri.push_back({u,v});
                            }
                        }
                    }
                }
                if(child>1){
                    ap[i]=true; 
                }
            }
        }
        for(int i=0;i<vertex;i++){
            if(ap[i]==true){
                points.push_back(i);
            }
        }
        return {points,bri};
    }
};