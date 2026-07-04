#include<queue>
#include<iostream>
#include<vector>
using namespace std;
class Shortest_Path_unweighted{
    //using bfs to find shortest path b/w two points is the best way since if we use our dfs logic then it will fail as it will give path but that path is not shortest always , so dfs fails
    private:
    const vector<vector<int>>&adjList;
    int vertex;
    public:
    Shortest_Path_unweighted(const vector<vector<int>>&a):
    adjList(a),vertex(a.size()){}

    void process(int a,int b){
        //BFS
        if(a==b){
            cout<<"distance is: 0\n";
            return;
        }
        queue<int>q;
        vector<bool>visit(vertex,false);
        vector<int>parent(vertex,-1);
        q.push(a);
        int dis=0;
        visit[a]=true;
        while(!q.empty()){
            int n=q.size();
            for(int i=0;i<n;i++){
                int u=q.front();
                q.pop();
                for(int j=0;j<adjList[u].size();j++){
                    int v=adjList[u][j];
                    if(visit[v]==false){
                        visit[v]=true;
                        q.push(v);
                        parent[v]=u;
                        if(v==b){
                            int track=v;
                            while(track!=a){
                                dis+=1;
                                cout<<track<<" -> ";
                                track=parent[track];
                            }
                            cout<<a<<"\n distance is :"<<dis<<endl;
                            return;
                        }
                    }
                }
            }
        }
        cout<<"not conncted to distance b/q them is infinite\n";
        return ;
    }
};