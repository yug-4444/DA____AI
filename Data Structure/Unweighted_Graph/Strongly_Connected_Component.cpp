#include<stack>
#include<iostream>
#include<vector>
using namespace std;
class SCC{
    private:
    const vector<vector<int>>&adjList;
    int vertex;
    public:
    SCC(const vector<vector<int>>&a):
    adjList(a),vertex(a.size()){}
    
    vector<int> DFS_1_order(){//store the node when they become black
        vector<bool>visit(vertex,false);
        vector<int>order;
        for(int i=0;i<vertex;i++){
            if(visit[i]==false){
                stack<int>st;
                vector<int>jcount(vertex,-1);
                st.push(i);
                while(!st.empty()){
                    int u=st.top();
                    if(visit[u]==false){
                        visit[u]=true;
                    }
                    int &j=jcount[u];
                    j+=1;
                    while(j<adjList[u].size()){
                        int v=adjList[u][j];
                        if(visit[v]==false){
                            st.push(v);
                            break;
                        }
                        j+=1;
                    }
                    if(j==adjList[u].size()){
                        order.push_back(u);
                        st.pop();
                    }
                }
            }
        }
        return order;
    }
    vector<vector<int>> reverse_adjlist(){
        vector<vector<int>>revList(vertex);
        for(int u=0;u<vertex;u++){
            for(int i=0;i<adjList[u].size();i++){
                int v=adjList[u][i];
                //u->v ===> u<-v
                revList[v].push_back(u);
            }
        }
        return revList;
    }
    vector<vector<int>>process_scc(){
        vector<int>order=DFS_1_order();
        vector<vector<int>>revList=reverse_adjlist();
        //now we have the order in which we need to dfs the revlist 
        //a->b->c->a ====>a<-b<-c<-a still so scc
        //order is need so that from left to right in topo sort each dirn from left to right also since cycle is there so its is not topo sort as only for DAG
        //leftest elemnt either has all going right dirn and incoming only if there is a cycle so if reversed then it will only have one outgoing that connects to cycle
        vector<bool>visit(vertex,false); 
        vector<vector<int>>scc_list;
        while(!order.empty()){
            int i=order.back();
            order.pop_back();
            if(visit[i]==false){
                vector<int>component;
                stack<int>st;
                vector<int>jcount(vertex,-1);
                st.push(i);
                while (!st.empty()){
                    int u=st.top();
                    if(visit[u]==false){
                        visit[u]=true;
                    }
                    int &j=jcount[u];
                    j+=1;
                    int limit=revList[u].size();
                    while(j<limit){
                        int v=revList[u][j];
                        if(visit[v]==false){
                            st.push(v);
                            break;
                        }
                        j+=1;
                    }
                    if(j==limit){
                        component.push_back(u);
                        st.pop();
                    }
                }
                scc_list.push_back(component);
            }
        }
        return scc_list;
    }
};