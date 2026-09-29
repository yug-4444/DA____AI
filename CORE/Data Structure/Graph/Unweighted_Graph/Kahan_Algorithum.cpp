//topological sort order using bfs while assuming that grapgh must be DAG
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
class TopologicalSortKahan{
    private:
    int vertex;
    const vector<vector<int>>&adjList;
    queue<int>order;
    public:
    TopologicalSortKahan(const vector<vector<int>>&a):
    adjList(a),vertex(a.size()){}
    void process(){
        vector<int>incount(vertex,0);
        for(int u=0;u<vertex;u++){//O(V+E)time
            for(int i=0;i<adjList[u].size();i++){
                int v=adjList[u][i];
                incount[v]+=1;
            }
        }
        queue<int>q;
        for(int i=0;i<vertex;i++){
            if(incount[i]==0){
                q.push(i);
            }
        }
        //now we get all nodes that don't have any dependencys before them to occur
        //as well as if it is a DAG then there will nessecarray be atleast one vertex whose incoming edge count is zero and in sort order stood at the leftmost side
        while(!q.empty()){
            int u=q.front();
            q.pop();
            order.push(u);
            for(int i=0;i<adjList[u].size();i++){
                int v=adjList[u][i];
                incount[v]-=1;
                if(incount[v]==0){
                    q.push(v);
                }
            }
        }
        if(order.size()!=vertex){//queue becomes empty but some vertex sets a cycle among them preventing topological sort
            cout<<"Cycle occurred";
            return;
        }
        while(!order.empty()){
            cout<<order.front()<<" -> ";
            order.pop();
        }
        cout<<"end"<<endl;
    }
    //in case it is mentioned that when multiple tasks present execute one with smallest the we use priorit_queue<int,vector<int>,greater<iny>>
};