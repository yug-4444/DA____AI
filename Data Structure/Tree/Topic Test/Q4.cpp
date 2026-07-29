#include<iostream>
#include<queue>
#include<map>
using namespace std;
struct treenode{
    int value;
    treenode*right;
    treenode*left;
    treenode(int val){
        value=val;
        right=left=nullptr;
    }
};
class sat_view{
    private:
    treenode*root;
    public:
    sat_view(treenode*r){
        root=r;
    }
    void top_view(){
        if(root==nullptr){
            cout<<"No tree .\n";
            return;
        }
        queue<pair<treenode*,int>>q;
        map<int,treenode*>mp;
        q.push({root,0});
        while(!q.empty()){
            auto [curr,x]=q.front();
            if(mp.find(x)==mp.end()){//not present
                mp[x]=curr;
            }
            q.pop();
            if(curr->right!=nullptr){
                q.push({curr->right,x+1});
            }
            if(curr->left!=nullptr){
                q.push({curr->left,x-1});
            }
        }
       for(auto&[x,node]:mp){
        cout<<" { "<<x<<" , "<<node->value<<" } ---> ";
       } 
    }
}