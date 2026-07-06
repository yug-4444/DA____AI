#include<iostream>
#include<vector>
using namespace std;
class TimeReversalDSU{
    private:
    vector<int>bigboss;
    vector<int>rank;
    const vector<pair<int,int>>&cut;//cut at T0,T1,T2.....Tn-1 time 
    const vector<pair<int,int>>&afterstate;
    vector<int>independent_components;
    int n;
    int comp;
    public:
    TimeReversalDSU(int server,const vector<pair<int,int>>&c,const vector<pair<int,int>>&a):
    afterstate(a),cut(c){
        n=server;
        bigboss.resize(server);
        rank.resize(server,1);
        for(int i=0;i<server;i++){
            bigboss[i]=i;//in initalize all servers self subset
        }
        independent_components.resize(c.size());
        comp=n;
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
            return ;
        }
        if(rank[root_u]>rank[root_v]){
            bigboss[root_v]=root_u;
        }else if(rank[root_u]<rank[root_v]){
            bigboss[root_u]=root_v;
        }else{
            bigboss[root_v]=root_u;
            rank[root_u]+=1;
        }
        comp-=1;
        return ;
    }
    void initalize(){//we move in backward time so we 1st reach state after destroyed
        for(int i=0;i<afterstate.size();i++){
            int u=afterstate[i].first;
            int v=afterstate[i].second;
            unite(u,v);
        }
    }
    vector<int> process(){
        initalize();
        //as we are moving back in time we see cuts from backward
        for(int i=cut.size()-1;i>=0;i--){
            int u=cut[i].first;
            int v=cut[i].second;
            unite(u,v);
            independent_components[i]=comp;
        }
        return independent_components;
    }
};