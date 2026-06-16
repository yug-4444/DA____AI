#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
class UndirGraph{
    private:
    int vertex;
    vector<vector<int>>adjList;//each index represent the vertex no. and it stores our edges
    public:
    UndirGraph(int v){
        vertex=v;
        adjList.resize(vertex);//resize adds vertex no. of indexes where each are empty in list to represent each vertex's corresponding edges
    //creates vertex empty vectors inside adjList
    }
    void addEdge(int u,int v){//O(1) undirected wiring
        if(u>=vertex||v>=vertex||u<0||v<0){
            return;
        }
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    void printGraph(){//O(V+E)time
        for (int i=0;i<vertex;i++){
            cout<<i<<" -> ";
            for(int j=0;j<adjList[i].size();j++){
                cout<<adjList[i][j]<<",";
            }
            cout<<"nullptr"<<endl;//nullptr to indicate that it all not any node 
        }
    }
    pair<int,vector<vector<int>>> BFS(int startNode){//breadth first search acts radiating outwards from the startpoint in cocentric rings
        vector<bool>visited(vertex,false);//initially all vertex are not touched
        visited[startNode]=true;
        //first in first out concept --- use queue
        queue<int>q;
        vector<vector<int>>time;
        time.push_back({startNode});
        q.push(startNode);
        while(!q.empty()){//till there is no more neighbourhod left that can be infected
            int size=q.size();
            vector<int>sub;
            for(int i=0;i<size;i++){
                int u=q.front();
                q.pop();
                for(int j=0;j<adjList[u].size();j++){
                    int v=adjList[u][j];
                    if(visited[v]==true){
                        continue;
                    }
                    visited[v]=true;
                    q.push(v);
                    sub.push_back(v);
                }
            }
            time.push_back(sub);
        }
        return{time.size(),time};
    }
    void DFS_visit(int u,int &time,vector<int>&parent,vector<bool>&visited,vector<int>&discovery,vector<int>&finished){
        time+=1;
        visited[u]=true;
        discovery[u]=time;
        for(int i=0;i<adjList[u].size();i++){
            int v=adjList[u][i];
            if(visited[v]==false){
                parent[v]=u;
                DFS_visit(v,time,parent,visited,discovery,finished);
            }
        }
        time+=1;
        finished[u]=time;
    }
    void DFS(){//using call stack limited space
        vector<int>parent(vertex,-1);//-1 represents no parent
        vector<bool>visited(vertex,false);
        vector<int>discovery(vertex,-1);
        vector<int>finished(vertex,-1);
        int time=-1;//time starts from 0th second so initiate it at -1 here
        for(int i=0;i<vertex;i++){
            if(visited[i]==false){
                DFS_visit(i,time,parent,visited,discovery,finished);
            }
        }
        //no. of subtree amount to no. -1 in parent
        //we may return discovey,finished,parent according to needs
    }
    void DFS_iter(){
        vector<int>parent(vertex,-1);//-1 represents no parent
        vector<bool>visited(vertex,false);
        vector<int>discovery(vertex,-1);
        vector<int>finished(vertex,-1);
        int time=-1;//time starts from 0th second so initiate it at -1 here
        for(int i=0;i<vertex;i++){
            if(visited[i]==false){
                stack<int>st;
                vector<int>jcount(vertex,-1);
                st.push(i);
                while(!st.empty()){
                    int u=st.top();
                    if(visited[u]==false){
                        time+=1;
                        discovery[u]=time;
                        visited[u]=true;
                    }
                    int j=jcount[u];
                    j+=1;
                    while(j<adjList[u].size()){
                        int v=adjList[u][j];
                        if(visited[v]==false){
                            parent[v]=u;
                            st.push(v);
                            break;
                        }
                        j++;
                    }
                    jcount[u]=j;
                    if(j==adjList[u].size()){//it means we were unable to find any unvisited node
                        time+=1;
                        finished[u]=time;
                        st.pop();
                    }
                }
            }
        }
    }
    //no need for destructor since vector automatically destored
};