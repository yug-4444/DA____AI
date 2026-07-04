//in an undirected graph there can only be two types back and tree edge
//where as in directed graph there can be tree, back ,forward and cross edges
//lets check for the directed graph
#include<vector>
#include<stack>
#include<iostream>
using namespace std;
enum color{
    white=0,//undiscovered
    gray=1,//active in pocessing or in frontier
    black=2,//dead or retired
};
class direcGraph{
    private:
    int vertex;
    vector<vector<int>>adjList;
    vector<pair<int,int>>treeEdge;
    vector<pair<int,int>>backEdge;
    vector<pair<int,int>>forwardEdge;
    vector<pair<int,int>>CrossEdge;
    public:
    direcGraph(int v){//0,1,2  --- v=3
        vertex=v;
        adjList.resize(vertex);//create {{},{},{}.....v times}
    }
    void addEdge(int u,int v){//we are adding a directed edge from u to v   u->v
        if(u>=vertex||v>=vertex||u<0||v<0){
            return;
        }
        adjList[u].push_back(v);
    }
    void dfs_visit(int u,int &time,vector<color>&state,vector<int>&discover,vector<int>&finished){
        time+=1;
        state[u]=gray;//dicover[v]!=-1 && finish=-1
        discover[u]=time;
        for(int i=0;i<adjList[u].size();i++){
            int v=adjList[u][i];
            if(state[v]==white){//disover[v]=-1
                treeEdge.push_back({u,v});//tree edge
                dfs_visit(v,time,state,discover,finished);
            }
            else if(state[v]==gray){//dicover[v]!=-1 && finish=-1
                backEdge.push_back({u,v});//backedge in it current node points toward the ancestor
            }
            else{//state[v]==black dicover[v]!=-1&&finish[v]!=-1
                //timeline is already done so can't move forward
                if(discover[u]<discover[v]){
                    forwardEdge.push_back({u,v});//points to already dead descendant
                }
                else{
                    CrossEdge.push_back({u,v});//points to another node that is not in same sub tree
                }
            }
        }
        time+=1;
        state[u]=black;
        finished[u]=time;
    }
    void edge_classify(){
        vector<int>discover(vertex,-1);
        vector<int>finished(vertex,-1);
        vector<color>state(vertex,white);
        int time=-1;
        for(int i=0;i<vertex;i++){
            if(state[i]==white){
                dfs_visit(i,time,state,discover,finished);
            }
        }
    }
    void edge_classify_iter(){//no call stack
        vector<int>discover(vertex,-1);
        vector<int>finished(vertex,-1);
        vector<color>state(vertex,white);
        int time=-1;
        for(int i=0;i<vertex;i++){
            if(state[i]==white){
                stack<int>st;
                vector<int>jcount(vertex,-1);
                st.push(i);
                while(!st.empty()){
                    int u=st.top();
                    if(state[u]==white){
                        time+=1;
                        state[u]=gray;
                        discover[u]=time;
                    }
                    int j=jcount[u];
                    j+=1;
                    while(j<adjList[u].size()){//u is in gray state since it is in stack
                        int v=adjList[u][j];
                        if(state[v]==white){
                            st.push(v);
                            treeEdge.push_back({u,v});
                            break;
                        }
                        else if(state[v]==gray){
                            backEdge.push_back({u,v});
                        }
                        else{
                            if(discover[u]<discover[v]){
                                forwardEdge.push_back({u,v});
                            }
                            else{
                                CrossEdge.push_back({u,v});
                            }
                        }
                    }
                    jcount[u]=j;
                    if(j==adjList[u].size()){
                        st.pop();
                        time+=1;
                        finished[u]=time;
                        state[u]=black;
                    }
                }
            }
        }
    }
};