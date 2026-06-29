#include<iostream>
#include<vector>
#include<stack>
#include <algorithm>
using namespace std;
class Eulerian_Path{
    //a path such that all the bridges/edges are visited exactly one
    //path or circuit 
    private:
    vector<vector<int>>adjList;
    int vertex;
    bool directed;
    public:
    Eulerian_Path(vector<vector<int>>a,bool dir):
    adjList(a),vertex(a.size()),directed(dir){}
    pair<int,bool> check_math_possiblility(){
        if (directed){
            //we check indegeree and outdegree
            vector<int>indegree(vertex,0);
            vector<int>outdegree(vertex,0);
            for(int i=0;i<vertex;i++){
                int u=i;
                for(int j=0;j<adjList[i].size();j++){
                    int v=adjList[u][j];
                    //u->v edge
                    indegree[v]+=1;
                    outdegree[u]+=1;
                }
            }
            //now we will exactly have two possibilites 1st all outdegree=indegree which is a circuit and we have no need for start 
            //if we have exactly one outdegree=indegree-1 and one indegree=outdegree-1 and all other out=in then this a path with start and end 
            //if any other case arises then its not a eulerian_path
            int s=-1;
            int e=-1;
            for (int i=0;i<vertex;i++){
                if(outdegree[i]!=indegree[i]){
                    if(outdegree==indegree){
                        continue;
                    }
                    else if(outdegree[i]==indegree[i]-1){
                        if(s==-1){
                            s=i;
                        }else{
                            //problem arrises as there can only be one start point
                            cout<<"NO VALID\n";
                            return{-1,false};
                        }
                    }
                    else if(outdegree[i]-1==indegree[i]){
                        if(e==-1){
                            e=i;
                        }else{
                            //problem arrises as there can only be one start point
                            cout<<"NO VALID\n";
                            return{-1,false};
                        }
                    }
                    else{
                        cout<<"NO VALID\n";
                        return{-1,false};
                    }
                }
            }
            if(s==-1&&e==-1||s!=-1&&e!=-1){
                return{s,true};
            }
            else{//in case we only get either start but not end vice-versa
                cout<<"NO VALID\n";
                return{-1,false};
            }
        }
        else{
            //in undirected graph we have to check even and odd edges count
            vector<int>count(vertex,0);
            int s=-1;
            int odd=0;
            for(int i=0;i<vertex;i++){
                count[i]=adjList[i].size();
                if(count[i]%2==0){//even amount of edges
                    continue;
                }
                else{//odd amount of edges
                    s=i;
                    odd+=1;
                    if(odd>2){
                        cout<<"NO VALID\n";
                        return{-1,false};
                    }
                }
            }
            if(odd==0||odd==2){
                return{s,true};
            }else{
                cout<<"NO VALID\n";
                return{-1,false};
            }
        }
    }
    vector<int> eul_path(){
        bool possible;
        int start;
        [start,possible]=check_math_possiblility();
        if(possible==false){
            cout<<"PATH NOT POSSIBLE\n";
            return {};
        }
        if(start==-1){//this means we will have a circuit else we will have path with two end points
            start=0;
        }
        vector<int>path;
        stack<int>st;
        st.push(start);
        while(!st.empty()){
            int u=st.top();
            if(adjList[u].size()==0){
                path.push_back(u);
                st.pop();
            }
            else{
                int v=adjList[u].back();
                adjList[u].pop_back();
                if (!directed) {
                    // We must hunt down the reverse cable (v -> u) and destroy it too.
                    auto it = find(adjList[v].begin(), adjList[v].end(), u);
                    if (it != adjList[v].end()) {
                        adjList[v].erase(it);
                    }
                }
                st.push(v);
            }
        }
        reverse(path.begin(), path.end());
        return path;
    }
};