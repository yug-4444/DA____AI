#include<iostream>
#include<stack>
#include<vector>
#include<set>
using namespace std;
class BiconnectivityEngine{
    private:
    const vector<vector<pair<int,int>>>&adjList;//u->v and edge id to avoid the multi-graph (parallel edge) vulnerability.
    int vertex;
    public:
    BiconnectivityEngine(const vector<vector<pair<int,int>>>&a):
    adjList(a),vertex(a.size()){}

    pair<vector<int>,vector<pair<int,int>>>AP_and_Bridge(){//for undirected unweighted graph
        //we have use dfs as we want to visit one one node at a time
        set<int>ap;//articualtion pont
        vector<pair<int,int>>bridge;
        vector<int>discover(vertex,-1);
        vector<int>lower_time(vertex,-1);
        vector<int>parent(vertex,-1);
        vector<int>parent_edge_id(vertex,-1);
        int time=-1;
        vector<int>j_count(vertex,-1);
        for(int i=0;i<vertex;i++){
            if(discover[i]==-1){
                stack<int>st;
                st.push(i);
                int child=0;
                while(!st.empty()){
                    int u=st.top();
                    if(discover[u]==-1){
                        time+=1;
                        discover[u]=time;
                        lower_time[u]=time;
                    }
                    int &j=j_count[u];
                    j+=1;
                    while(j<adjList[u].size()){
                        int v=adjList[u][j].first;
                        int id=adjList[u][j].second;
                        if(parent[u]==v&&parent_edge_id[u]==id){
                            j+=1;
                            continue;
                        }
                        if(discover[v]==-1){//tree edge
                            parent[v]=u;
                            parent_edge_id[v]=id;
                            if(u==i){
                                child+=1;
                            }
                            st.push(v);
                            break;
                        }
                        else{
                            lower_time[u]=min(lower_time[u],discover[v]);
                        }
                        j+=1;
                    }
                    if(j==adjList[u].size()){
                        int v=st.top();
                        st.pop();
                        if(parent[v]!=-1){
                            u=parent[v];
                            lower_time[u]=min(lower_time[u],lower_time[v]);
                            if(discover[u]<lower_time[v]){
                                bridge.push_back({u,v});
                            }
                            if(parent[u]!=-1&&discover[u]<=lower_time[v]){
                                ap.insert(u);
                            }
                        }
                    }
                }
                if(child>1){
                    ap.insert(i);
                }
            }
        }
        vector<int>AP(ap.begin(),ap.end());
        return {AP,bridge};
    }
};