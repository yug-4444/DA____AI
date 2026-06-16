#include<vector>
#include<stack>
#include<queue>
using namespace std;
class CycleDetector {
    const vector<vector<int>>&adjList;
    int vertex;
    public:
    CycleDetector(const vector<vector<int>>&adj):
    adjList(adj),vertex(adj.size()){}
    void dfs_visit(int u,vector<int>&parent,vector<bool>&visited,bool &cycle,vector<pair<int,int>>&rem){
        visited[u]=true;
        for(int i=0;i<adjList[u].size();i++){
            int v=adjList[u][i];
            if(visited[v]==true&&parent[u]!=v){
                cycle=true;
                rem.push_back({u,v});
            }
            if(visited[v]==false){
                parent[v]=u;
                dfs_visit(v,parent,visited,cycle,rem);
            }
        }
    }
    pair<bool,vector<pair<int,int>>> cycle1(){//dfs call stack so limited size
        vector<bool>visited(vertex,false);
        vector<int>parent(vertex,-1);
        bool cycle=false;
        vector<pair<int,int>>rem;
        for(int i=0;i<vertex;i++){
            if(visited[i]==false){
                dfs_visit(i,parent,visited,cycle,rem);
            }
        }
        return {cycle,rem};
    }
    pair<bool,vector<pair<int,int>>> cycle2(){//dfs iterative 
        vector<bool>visited(vertex,false);
        vector<int>parent(vertex,-1);
        bool cycle=false;
        vector<pair<int,int>>rem;
        for(int i=0;i<vertex;i++){
            if(visited[i]==false){
                stack<int>st;
                vector<int>jcount(vertex,-1);
                while(!st.empty()){
                    int u=st.top();
                    if(visited[u]==false){
                        visited[u]=true;
                    }
                    int j=jcount[u];
                    j+=1;
                    while(j<adjList[u].size()){
                        int v=adjList[u][j];
                        if(visited[v]==true&&parent[u]!=v){
                            cycle=true;
                            rem.push_back({u,v});
                        }
                        if(visited[v]==false){
                            parent[v]=u;
                            st.push(v);
                            break;
                        }
                        j+=1;
                    }
                    jcount[u]=j;
                    if(j==adjList[u].size()){
                        st.pop();
                    }
                }
            }
        } 
        return {cycle,rem};
    }
    pair<bool,vector<pair<int,int>>> cycle2(int start){//bfs
        queue<int>q;
        bool cycle=false;
        vector<pair<int,int>>rem;
        vector<int>parent(vertex,-1);
        vector<bool>visited(vertex,false);
        q.push(start);
        visited[start]=true;
        while(!q.empty()){
            int n=q.size();
            for(int i=0;i<n;i++){
                int u=q.front();
                q.pop();
                for(int j=0;j<adjList[u].size();j++){
                    int v=adjList[u][j];
                    if(visited[v]==true&&parent[u]!=v){
                        cycle=true;
                        rem.push_back({u,v});
                    }
                    if(visited[v]==false){
                        q.push(v);
                        visited[v]=true;
                        parent[v]=u;
                    }
                }
            }
        }
        return {cycle,rem};
    }
};