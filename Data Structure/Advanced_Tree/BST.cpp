//when data quantity is so huge that we are unable to find a continous block of memory space in heap memory , we have to move to distributed memory that is nodes
//we have link list but search in it takes like forever O(n) time , but that if we divide the universe to reduce to O(logn)time complexity
//when divide rule is such that at the junction node all greater elements to its right and lesser to its left
#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<climits>
using namespace std;
struct treenode{//20 bytes ->24 bytes due to padding as system 8 multiples bytes
    int data;//4 bytes
    treenode*left;
    treenode*right;//8 bytes each
    treenode(int val){
        data=val;
        left=right=nullptr;
    }
};
class Tree{
    public:
    void insert_bst_rec(treenode*&root,int value){//O(logn)time and O(logn)stack space
        if(root==nullptr){
            root=new treenode(value);
            return;
        }
        else if(root->data<value)insert_bst_rec(root->right,value);
        else insert_bst_rec(root->left,value);
    }
    void insert_bst_ite(treenode*&root,int value){//O(logn)time and O(1)space
        if(root==nullptr){
            root=new treenode(value);
            return;
        }
        treenode*ptr=root;
        treenode*parent=nullptr;
        while(ptr){
            parent=ptr;
            if(ptr->data<value)ptr=ptr->right;
            else ptr=ptr->left;
        }
        if(parent->data<value)parent->right=new treenode(value);
        else parent->left=new treenode(value);
    }
    //traversals preorder,inorder,postorder in call stack, my iterative methord , standard iterative methord
    void preorder_call_stack(treenode*root){//O(n)time and O(logn)stack space
        //ROOT->L->R
        if(root==nullptr)return;
        cout<<root->data<<"->";
        preorder_call_stack(root->left);
        preorder_call_stack(root->right);
    }
    void inorder_call_stack(treenode*root){//O(n)time and O(logn)stack space
        //L->ROOT->R
        if(root==nullptr)return;
        inorder_call_stack(root->left);
        cout<<root->data<<"->";
        inorder_call_stack(root->right);
    }
    void postorder_call_stack(treenode*root){//O(n)time and O(logn)stack space
        //L->R->ROOT
        if(root==nullptr)return;
        postorder_call_stack(root->left);
        postorder_call_stack(root->right);
        cout<<root->data<<"->";
    }

    void preorder_my_ite(treenode*root){
        stack<pair<treenode*,bool>>st;
        st.push({root,false});
        while(!st.empty()){
            auto[curr,wr]=st.top();
            st.pop();
            if(!curr)continue;
            if(wr){
                cout<<curr->data<<"->";
                continue;
            }
            st.push({curr->right,false});
            st.push({curr->left,false});
            st.push({curr,true});
        }
    }
    void inorder_my_ite(treenode*root){
        stack<pair<treenode*,bool>>st;
        st.push({root,false});
        while(!st.empty()){
            auto[curr,wr]=st.top();
            st.pop();
            if(!curr)continue;
            if(wr){
                cout<<curr->data<<"->";
                continue;
            }
            st.push({curr->right,false});
            st.push({curr,true});
            st.push({curr->left,false});
        }
    }
    void postorder_my_ite(treenode*root){
        stack<pair<treenode*,bool>>st;
        st.push({root,false});
        while(!st.empty()){
            auto[curr,wr]=st.top();
            st.pop();
            if(!curr)continue;
            if(wr){
                cout<<curr->data<<"->";
                continue;
            }
            st.push({curr,true});
            st.push({curr->right,false});
            st.push({curr->left,false});
        }
    }

    void preorder_sta_ite(treenode*root){
        stack<treenode*>st;
        st.push(root);
        while(!st.empty()){
            treenode*curr=st.top();
            st.pop();
            if(!curr)continue;
            cout<<curr->data<<"->";
            st.push(curr->right);
            st.push(curr->left);
        }
    }
    void inorder_sta_ite(treenode*root){
        stack<treenode*>st;
        treenode* curr=root;
        while(!st.empty()||curr!=nullptr){
            while(curr){
                st.push(curr);
                curr=curr->left;
            }
            curr=st.top();
            st.pop();
            cout<<curr->data;
            curr=curr->right;
        }
    }
    void postorder_sta_ite(treenode*root){
        //L->R->ROOT -INV-> ROOT->R->L
        stack<treenode*>st,ans;
        st.push(root);
        while(!st.empty()){
            treenode*curr=st.top();
            if(!curr)continue;
            ans.push(curr);
            st.push(curr->left);
            st.push(curr->right);
        }
        while(!ans.empty()){
            cout<<ans.top()->data<<"->";
            ans.pop();
        }
    }

    pair<int,vector<vector<treenode*>>>level_traversal(treenode*root){
        if(root==nullptr)return{0,{}};
        queue<treenode*>q;
        vector<vector<treenode*>>list;
        q.push(root);
        while(!q.empty()){
            int lv_size=q.size();
            vector<treenode*>level;
            for(int i=0;i<lv_size;i++){
                treenode*curr=q.front();
                if(curr->left)q.push(curr->left);
                if(curr->right)q.push(curr->right);
                q.pop();
                level.push_back(curr);
            }
            list.push_back(level);
        }
        return {list.size(),list};
    }
    pair<int,vector<int>>count_levels(treenode*root){
        if(root==nullptr)return{0,{}};
        queue<treenode*>q;
        vector<int>list;
        q.push(root);
        while(!q.empty()){
            int lv_size=q.size();
            list.push_back(lv_size);
            for(int i=0;i<lv_size;i++){
                treenode*curr=q.front();
                if(curr->left)q.push(curr->left);
                if(curr->right)q.push(curr->right);
                q.pop();
            }
        }
        return {list.size(),list};
    }
    
    treenode*search_BST_call_stack(treenode*root,int value){//O(h)time and stack space
        if(root==nullptr)return nullptr;
        if(root->data==value)return root;
        else if(root->data<value)return search_BST_call_stack(root->right,value);
        else search_BST_call_stack(root->left,value);
    }
    treenode*search_BST_ite(treenode*root,int value){//O(h)time 
        while(root){
            if(root->data==value)return root;
            else if(root->data<value)root=root->right;
            else root=root->left;
        }
        return nullptr;
    }

    treenode*getmin(treenode*root){//O(h)time
        if(!root)return nullptr;
        while(root->left){
            root=root->left;
        }
        return root;
    }
    treenode*getmax(treenode*root){
        if(!root)return nullptr;
        while(root->right){
            root=root->right;
        }
        return root;
    }
    treenode*inorder_successor(treenode*root,int value){
        //after the value the first larger
        bool find=false;
        treenode*curr=root;
        stack<treenode*>st;
        while(!st.empty()||curr){
            while(curr){
                st.push(curr);
                curr=curr->left;
            }
            curr=st.top();
            st.pop();
            if(curr->data==value)find=true;
            if(find)return curr;
            curr=curr->right;
        }
        return nullptr;
    }
    treenode*inorder_predecessor(treenode*root,int value){
        //before the value the first smaller
        treenode*curr=root;
        treenode*prev=nullptr;
        stack<treenode*>st;
        while(!st.empty()||curr){
            while(curr){
                st.push(curr);
                curr=curr->left;
            }
            curr=st.top();
            st.pop();
            if(curr->data==value)return prev;
            prev=curr;
            curr=curr->right;
        }
        return nullptr;
    }
    treenode*inorder_successor_opti(treenode*root,int value){
        treenode*succ=nullptr;
        while(root){
            if(root->data<value){
                root=root->right;
            }else if(root->data>value){
                succ=root;
                root=root->left;
            }else{
                break;
            }
        }
        if(!root)return nullptr;
        treenode*next=getmin(root->right);
        if(!next)return succ;
        return next;
    }
    treenode*inorder_predecessor_opti(treenode*root,int value){
        treenode*pred=nullptr;
        while(root){
            if(root->data<value){
                pred=root;
                root=root->right;
            }else if(root->data>value){
                root=root->left;
            }else{
                break;
            }
        }
        if(!root)return nullptr;
        treenode*prev=getmax(root->left);
        if(!prev)return pred;
        return prev;
    }

    int height_call_stack(treenode*root){
        if(!root)return 0;
        int lh=height_call_stack(root->left);
        int rh=height_call_stack(root->right);
        return lh>rh?lh+1:rh+1;
    }
    int height_ite_1(treenode*root){
        return count_levels(root).first;
    }
    int height_ite_2(treenode*root){
        int maxh=0;
        if(root==nullptr)return 0;
        stack<pair<treenode*,int>>st;
        st.push({root,1});
        while(!st.empty()){
            treenode*curr=st.top().first;
            int currh=st.top().second;
            st.pop();
            if(currh>maxh)maxh=currh;
            if(curr->right)st.push({curr->right,currh+1});
            if(curr->left)st.push({curr->left,currh+1});
        }
        return maxh;
    }

    void delete_node(treenode*&root,int value){
        if(!root)return;
        if(root->data>value)delete_node(root->left,value);
        else if(root->data<value)delete_node(root->right,value);
        else{
            if(root->right==nullptr&&root->left==nullptr){
                root->data=0;
                delete root;
                root=nullptr;
            }
            else if(root->right!=nullptr&&root->left!=nullptr){
                treenode*replace=getmin(root->right);
                root->data=replace->data;
                delete_node(root->right,replace->data);
            }else{
                treenode*temp=root;
                if(root->right)root=root->right;
                else root=root->left;
                temp->data=0;
                temp->right=temp->left=nullptr;
                delete temp;
            }
        }
    }

    treenode*lowest_common_ancestor_bst(treenode*root,treenode*p,treenode*q){
        if(!root)return nullptr;
        if(root->data>p->data&&root->data>q->data)return lowest_common_ancestor_bst(root->left,p,q);
        else if(root->data<p->data&&root->data<q->data)return lowest_common_ancestor_bst(root->right,p,q);
        else return root;
    }
    treenode*lowest_common_ancestor_binary_tree(treenode*root,treenode*p,treenode*q){
        stack<pair<treenode*,bool>>st;
        deque<treenode*>path,path_p,path_q;
        st.push({root,false});
        bool find_p=false,find_q=false;
        while(!st.empty()&&(!find_p||!find_q)){
            treenode*curr=st.top().first;
            bool remove=st.top().second;
            st.pop();
            if(remove){//boths its child have been explored and not usefull 
                path.pop_back();
                continue;
            }else{
                path.push_back(curr);
                if(curr==p){
                    find_p=true;
                    path_p=path;
                }
                if(curr==q){
                    find_q=true;
                    path_q=path;
                }
                st.push({curr,true});
                if(curr->right)st.push({curr->right,false});
                if(curr->left)st.push({curr->left,false});
            }
        }
        treenode*lca=nullptr;
        while(!path_p.empty()&&!path_q.empty()&&path_p.front()==path_q.front()){
            lca=path_p.front();
            path_p.pop_front();
            path_q.pop_front();
        }
        return lca;
    }
    treenode*lowest_common_ancestor_binary_tree_opti(treenode*root,treenode*p,treenode*q){
        if(!root||root==p||root==q)return root;
        treenode*left_signal=lowest_common_ancestor_binary_tree_opti(root->left,p,q);
        treenode*right_signal=lowest_common_ancestor_binary_tree_opti(root->right,p,q);
        if(left_signal&&right_signal)return root;
        return left_signal?left_signal:right_signal;
    }

    bool validBST(treenode*root){
        //if inorder is valid order
        treenode*curr=root;
        int prev=INT_MIN;
        stack<treenode*>st;
        while(!st.empty()||curr){
            while(curr){
                st.push(curr);
                curr=curr->left;
            }
            curr=st.top();
            st.pop();
            if(curr->data<=prev)return false;
            curr=curr->right;
        }
        return true;
    }
    bool isBalanced(treenode*root){
        if(!root)return true;
        return isBalanced(root->right)&&isBalanced(root->left)&&abs(height_ite_2(root->right)-height_ite_2(root->left))<=1;
    }
    int height_check(treenode*root){
        if(!root)return 0;
        int lh=height_check(root->left);
        if(lh==-1)return -1;
        int rh=height_check(root->right);
        if(rh==-1)return -1;
        if(abs(lh-rh)>1)return -1;
        return lh>rh?lh+1:rh+1;
    }
    bool isBalanced_opti(treenode*root){
        return height_check(root)!=-1;
    }

    treenode*reconstruct_preorder_iter(const vector<int>&order){
        int n=order.size();
        if(n==0)return nullptr;
        treenode*root=new treenode(order[0]);
        stack<treenode*>st;
        st.push(root);
        for(int i=1;i<n;i++){
            treenode*temp=new treenode(order[i]);
            if(!st.empty()&&st.top()->data>order[i]){
                st.top()->left=temp;
                st.push(temp);
            }else{
                treenode*prev=nullptr;
                while(!st.empty()&&st.top()->data<order[i]){
                    prev=st.top();
                    st.pop();
                }
                prev->right=temp;
                st.push(temp);
            }
        }
        return root;
    }
    treenode*reconstruct_preorder_call_stack(const vector<int>&order,int boundary,int &i){//bounday at start intmax
        if(i==order.size()||order[i]>boundary)return nullptr;
        treenode*root=new treenode(order[i]);
        i++;
        root->left=reconstruct_preorder_call_stack(order,root->data,i);
        root->right=reconstruct_preorder_call_stack(order,boundary,i);
        return root;

    }
    treenode*reconstruct_postorder_iter(const vector<int>&order){
        //L->R->ROOT
        int n=order.size();
        if(n==0)return nullptr;
        treenode*root=new treenode(order[n-1]);
        stack<treenode*>st;
        st.push(root);
        for(int i=n-2;i>=0;i--){
            treenode*temp=new treenode(order[i]);
            if(!st.empty()&&st.top()->data<order[i]){
                st.top()->right=temp;
                st.push(temp);
            }else{
                treenode*prev=nullptr;
                while(!st.empty()&&st.top()->data>order[i]){
                    prev=st.top();
                    st.pop();
                }
                prev->left=temp;
                st.push(temp);
            }
        }
        return root;
    }
    treenode*reconstruct_postorder_call_stack(const vector<int>&order,int boundary,int &i){
        if(i==-1||order[i]<boundary)return nullptr;
        treenode*root=new treenode(order[i]);
        i--;
        root->right=reconstruct_postorder_call_stack(order,root->data,i);
        root->left=reconstruct_postorder_call_stack(order,boundary,i);
        return root;
    }
    treenode*reconstruct_inorder_iter(const vector<int>&order){
        return nullptr;
    }
    treenode*reconstruct_inorder_call_stack(const vector<int>&order){
        return nullptr;
    }

    void delete_tree_call_stack(treenode*&root){
        if(!root)return;
        delete_tree_call_stack(root->left);
        delete_tree_call_stack(root->right);
        root->data=0;
        delete root;
        root=nullptr;
    }
    void delete_tree_ite(treenode*&root){
        //using postorer to delete nodes
        stack<treenode*>st,order;
        st.push(root);
        while(!st.empty()){
            treenode*curr=st.top();
            st.pop();
            order.push(curr);
            if(curr->left)st.push(curr->left);
            if(curr->right)st.push(curr->right);
        }
        while(!order.empty()){
            treenode*curr=order.top();
            order.pop();
            curr->data=0;
            curr->right=curr->left=nullptr;
            delete curr;
        }
        root=nullptr;
    }
};