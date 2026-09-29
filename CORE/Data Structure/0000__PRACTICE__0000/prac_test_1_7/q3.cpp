#include<deque>
#include<stack>
using namespace std;
struct node{
    int value;
    node*left;
    node*right;
    node(int val){
        value=val;
        left=right=nullptr;
    }
};
class CrucibleEngine3 {
    public://!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!for binary tree not bst !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    node* lowestCommonAncestor(node* root,node* p,node* q) {
        deque<pair<node*,bool>>st;
        deque<node*>path,pp,pq;
        st.push_back({root,false});
        bool fp=false,fq=false;
        while(!st.empty()&&(!fp||!fq)){
            node*curr;bool del;
            [curr,del]=st.back();
            st.pop_back();
            if(del==true){
                path.pop_back();
                continue;
            }
            else{
                path.push_back(curr);
                if(curr==p){
                    fp=true;
                    pp=path;
                }
                if(curr==q){
                    fq=true;
                    pq=path;
                }
                st.push_back({curr,true});
                if(curr->right!=nullptr){
                    st.push_back({curr->right,false});
                }
                if(curr->left!=nullptr){
                    st.push_back({curr->left,false});
                }
            }
        }
        node*lca=nullptr;
        while(!pp.empty()&&!pq.empty()&&pp.front()==pq.front()){
            lca=pp.front();
            pp.pop_front();
            pq.pop_front();
        }
        return lca;
    }
    node* lowestCommonAncestor_optimized(node* root,node* p,node* q){//uses call stack
        if(root==nullptr||root==p||root==q){//stops diving and returns signal
            return root;//The Scout hits the void, or finds a target
        }
        node*leftsignal=lowestCommonAncestor_optimized(root->left,p,q);
        node*rightsignal=lowestCommonAncestor_optimized(root->right,p,q);
        if(leftsignal!=nullptr&&rightsignal!=nullptr){//division point
            return root;//If both return a signal, THIS node is the split
        }
        return leftsignal?leftsignal:rightsignal;//pass signal up since not lca node
        //Bubble Up the surviving signal (If only one side found something, pass it up
    }
};