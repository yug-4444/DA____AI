#include<vector>
#include<stack>
#include<queue>
using namespace std;
enum color{
    white=0,//initiate a undisovered node
    red=1,
    blue=2,
};
//for bipartite no consective same color of node adjacent to each other
class BiparytiteGraphCheck {
    const vector<vector<int>>&adjList;
    int vertex;
    public:
    BiparytiteGraphCheck(const vector<vector<int>>&adj):
    adjList(adj),vertex(adj.size()){}
//keep in mind if node is undiscovered then it has to white 
    bool bfs_methord(){
        vector<color>status(vertex,white);
        //lets consider situation where graph may not be connected still using bfs
        for(int i=0;i<vertex;i++){
            if(status[i]==white){
                queue<int>q;
                q.push(i);
                status[i]=red;
                while(!q.empty()){
                    int u=q.front();
                    q.pop();
                    color &col_u=status[u];
                    for(int j=0;j<adjList[u].size();j++){
                        int v=adjList[u][j];
                        color &col_v=status[v];
                        if(col_v==white){
                            q.push(v);
                            if(col_u==red){
                                col_v=blue;
                            }else{
                                col_v=red;
                            }
                        }else{
                            if(col_v==col_u){
                                return false;
                            }
                            //differnt color means if one is red naother must be blue which is fine
                        }
                    }
                }
            }
        }
        return true;
    }
    bool dfs_methord(){
        vector<color>status(vertex,white);
        for(int i=0;i<vertex;i++){
            if(status[i]==white){
                stack<int>st;
                vector<int>jcount(vertex,-1);
                st.push(i);
                status[i]=red;
                while(!st.empty()){
                    int u=st.top();
                    color &col_u=status[u];
                    int &j=jcount[u];
                    j+=1;
                    while(j<adjList[u].size()){
                        int v=adjList[u][j];
                        color &col_v=status[v];
                        if(col_v==white){
                            st.push(v);
                            if(col_u==red){
                                col_v=blue;
                            }else{
                                col_v=red;
                            }
                            break;
                        }
                        else{
                            if(col_u==col_v){
                                return false;
                            }
                        }
                        j+=1;
                    }
                    if(j==adjList[u].size()){
                        st.pop();
                    }
                }
            }
        }
        return true;
    }
};