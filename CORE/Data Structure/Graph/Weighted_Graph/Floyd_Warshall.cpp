#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class MultiSourceWar{
    private:
    const vector<vector<pair<int,int>>>&adjList;
    vector<vector<int>>adjMatrix;
    int vertex;
    public:
    MultiSourceWar(const vector<vector<pair<int,int>>>&a):
    adjList(a),vertex(adjList.size()){
        adjMatrix.resize(vertex,vector<int>(vertex,INT_MAX));
        //u->u chepest will be 0
        for(int u=0;u<vertex;u++){
            adjMatrix[u][u]=0;
            for(int j=0;j<adjList[u].size();j++){
                int v=adjList[u][j].first;
                int w=adjList[u][j].second;
                adjMatrix[u][v]=w;
            }
        }
    }
    vector<vector<int>>process(){
        //middle man concept k 
        for(int k=0;k<vertex;k++){
            for(int i=0;i<vertex;i++){
                for(int j=0;j<vertex;j++){
                    //can't skip i==j as in negitive edge case things might change
                    //i->k and k->j 
                    if(adjMatrix[i][k]!=INT_MAX&&adjMatrix[k][j]!=INT_MAX&&adjMatrix[i][k]+adjMatrix[k][j]<adjMatrix[i][j]){
                        adjMatrix[i][j]=adjMatrix[i][k]+adjMatrix[k][j];
                    }
                }
            }
        }
        return adjMatrix;
    }
};