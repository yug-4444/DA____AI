#include<stack>
#include<vector>
#include<iostream>
using namespace std;
class TopologicalSort{
    private:
    const vector<vector<int>>&adjList;
    vector<int>order;//finished will be pusshed and it will act as a stack
    int vertex;
    public:
    TopologicalSort(const vector<vector<int>>&l):
    adjList(l),vertex(l.size()){}
    //we don't just assume that input graph may nessecaraly be a DAG
    bool process(){//iterative
        //topological sort only works for DAG system so in case if we get back edge all becomes void
        //cross and foward edges work just fine
        vector<bool>visit(vertex,false);
        vector<int>discover(vertex,-1);
        vector<int>finish(vertex,-1);
        int time=-1;
        for(int i=0;i<vertex;i++){
            if(visit[i]==false){
                vector<int>st;
                vector<int>jcount(vertex,-1);
                st.push_back(i);
                while(!st.empty()){
                    int u=st.back();
                    if(visit[u]==false){
                        visit[u]=true;
                        time+=1;
                        discover[u]=time;
                    }
                    int j=jcount[u];
                    j+=1;
                    while(j<adjList[u].size()){
                        int v=adjList[u][j];
                        if(visit[v]==false){
                            //tree edge
                            st.push_back(v);
                            break;
                        }
                        else{
                            if(finish[v]==-1){//means back edge
                                return false;
                                //no need to process further as  back edge occured
                            }
                            //no problem with cross or forward eges as they don't make a infinite loop
                        }
                        j+=1;
                    }
                    jcount[u]=j;
                    if(j==adjList[u].size()){
                        st.pop_back();
                        time+=1;
                        finish[u]=time;
                        order.push_back(u);
                    }
                }
            }
        }
        return true;
    }
    void sorted(){
        bool nocycle=process();
        if(nocycle==false){
            cout<<"Cycle detected in directed graph so topological sort not possible";
        }else{
            while(!order.empty()){
                cout<<order.back()<<" -> ";
                order.pop_back();
            }
            cout<<"end\n";
        }
    }
};