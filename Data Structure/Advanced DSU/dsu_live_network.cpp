#include<iostream>
#include<vector>
using namespace std;
class LiveDSU{
    //when we have millions of servers and millons of quirey per second and we want to solve each quiry of check in O(1)time 
    private:
    vector<int>bigboss;//root point towards highest representative of subset and each subset will only have 1 representative(unique)
    vector<int>rank;
    public:
    //in this dynamic system cables constantly plugged in 
    //dsu can't delete a connection as it is flattened
    LiveDSU(int server){
        bigboss.resize(server);
        rank.resize(server,1);
        for(int i=0;i<server;i++){
            bigboss[i]=i;//in initalize all servers self subset
        }
    }
    int find(int u){
        if(u!=bigboss[u]){
            bigboss[u]=find(bigboss[u]);
        }
        return bigboss[u];
    }
    void unite(int u,int v){
        int root_u=find(u);
        int root_v=find(v);
        if(root_u==root_v){
            return;
        }
        if(rank[root_u]>rank[root_v]){
            bigboss[root_v]=root_u;
        }else if(rank[root_u]<rank[root_v]){
            bigboss[root_u]=root_v;
        }else{
            bigboss[root_v]=root_u;
            rank[root_u]+=1;
        }
    }
    bool check(int u,int v){//O(1)time
        bool c= find(u)==find(v);
        if(c){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
        return c;
    }
};