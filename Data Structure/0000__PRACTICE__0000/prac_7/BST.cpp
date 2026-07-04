#include<iostream>
#include<stack>
#include<vector>
#include<climits>
#include<queue>
using namespace std;
struct node{
    int value;
    node*left;
    node*right;
    node(int val){
        value=val;
        right=left=nullptr;
    }
};
class bst{
    public:
    //we have 1D stuctures in we can move our pointer in dirction of single path 
    //so traversing to search for a object takes O(n) time BUT 
    //what if we break our universe such that serch time can be reduced so we have Tree
    //binary tree is one in which each node can have atmost 2 childrens
    //binary search tree are one that are binary tree with property that left child of a node is less than or equal to parent node and right child is greater or equal to parent node
    //this reduces our search time O(logn)
    //at each fork points we have two paths or optional ways to go to
    bst(){}
    //insertion in a bst tree while maintaining bst tree property
    void insert_bst(node*&root,int val){//uses call stack  O(logn) space
        if(root==nullptr){
            root=new node(val);
            return;
        }
        else if(root->value>val){
            insert_bst(root->left,val);//changes in root as a paremeter will reflect back in orignal
        }
        else{
            insert_bst(root->right,val);
        }
    }
    void insert_bst_iter(node*&root,int val){//made using minspace and without call stack 
        if(root==nullptr){
            root=new node(val);
            return;
        }
        node*curr=root;
        node*parent=nullptr;
        while(curr!=nullptr){
            parent=curr;
            if(curr->value>val){
                curr=curr->left;
            }
            else{
                curr=curr->right;
            }
        }
        if(parent->value>val){
            parent->left=new node(val);
        }
        else{
            parent->right=new node(val);
        }
    }
    node*insert_BST_2(node*root,int val){//uses call stack  O(logn) space
        if(root==nullptr){
            root=new node(val);
        }
        else if(root->value>val){
            root->left=insert_BST_2(root->left,val);//changes in root as a paremeter will not reflect back in orignal so requires direction to be specified
        }
        else{
            root->right=insert_BST_2(root->right,val);
        }
        return root;
    }
    
    //call stack is a internal stack in a stack space of limited size of gew megabytes managed automatically by OS directly
    void preorder_call_stack(node*root){//O(h) space
        //preorder --- DLR :it means when ever a node is disovered first we directly process it first and then we move onto it left chid path first and then on right child path second
        if(root==nullptr){//when current path have no more possibility we visit our latest previous fork point and chose another unvisited and available path from that fork point else we keep checking all prev fork points in order till new path found
            return;
        }
        cout<<root->value<<" -> ";
        preorder_call_stack(root->left);
        preorder_call_stack(root->right);
    }
    void inorder_call_stack(node*root){//O(h)space
        //inorder --- LDR :it is order version of all numbers present in out tree it is very usefull
        if(root==nullptr){
            return ;
        }
        inorder_call_stack(root->left);
        cout<<root->value<<" -> ";
        inorder_call_stack(root->right);
    }
    void postorder_call_stack(node*root){//O(h)space
        //postorder --- LRD :when both childs of a node are visited then we process that node
        if(root==nullptr){
            return;
        }
        postorder_call_stack(root->left);
        postorder_call_stack(root->right);
        cout<<root->value<<" -> ";

    }
    
    //since call stack have a limited space after which it will overflow we will made our manual stack in heap space whose space is very large
    void preorder_iter(node*root){//O(2h)---O(h) space and O(n)time
        //DLR
        stack<pair<node*,bool>>st;
        st.push({root,false});
        while(!st.empty()){
            node*curr=nullptr;
            bool pro=false;
            [curr,pro]=st.top();
            st.pop();
            if(curr==nullptr){
                continue;
            }
            if(pro==true){
                cout<<curr->value<<" -> ";
                continue;
            }
            //last in first out concept
            //D->L->R
            st.push({curr->right,false});
            st.push({curr->left,false});
            st.push({curr,true});
        }
    }
    void inorder_iter(node*root){//O(3h)---O(h) space and O(n)time
        stack<pair<node*,bool>>st;
        st.push({root,false});
        while(!st.empty()){
            node*curr=nullptr;
            bool pro=false;
            [curr,pro]=st.top();
            st.pop();
            if(curr==nullptr){
                continue;

            }
            if(pro==true){
                cout<<curr->value<<" -> ";
            }
            //L->D->R
            st.push({curr->right,false});
            st.push({curr,true});
            st.push({curr->left,false});
        }
    }
    void postorder_iter(node*root){//O(3h)---O(h) space and O(n)time
        stack<pair<node*,bool>>st;
        st.push({root,false});
        while(!st.empty()){
            node*curr=nullptr;
            bool pro=false;
            [curr,pro]=st.top();
            st.pop();
            if(curr==nullptr){
                continue;

            }
            if(pro==true){
                cout<<curr->value<<" -> ";
            }
            //L->R->D
            st.push({curr,true});
            st.push({curr->right,false});
            st.push({curr->left,false});
        }
    }
    
    //now we will use standard methord used in this manual stack methord
    //O(h)space and O(n) time
    void preorder_iter_stand(node*root){
        //D ->L ->R
        stack<node*>st;//it stores the fork points in order of their prev use time like the latest fork point at top
        st.push(root);
        while(!st.empty()){
            node*curr=st.top();
            st.pop();
            if(curr==nullptr){
                continue;
            }
            cout<<curr->value;
            st.push(curr->right);
            st.push(curr->left);
        }
    }
    void inorder_iter_stand(node*root){
        //L-> D-> R
        stack<node*>st;
        node*curr=root;
        while(!st.empty()||curr!=nullptr){
            while(curr!=nullptr){
                st.push(curr);
                curr=curr->left;
            }
            curr=st.top();
            st.pop();
            cout<<curr->value<<" -> ";
            curr=curr->right;
        }
    }
    void postorder_iter_stand(node*root){
        // L->R->D  ---- D->R->L reverse anwser
        stack<node*>st,ans;
        st.push(root);
        while(!st.empty()){
            node*curr=st.top();
            st.pop();
            if(curr==nullptr){
                continue;
            }
            ans.push(curr);
            st.push(curr->left);
            st.push(curr->right);
        }
        while(!ans.empty()){
            cout<<ans.top()->value<<" -> ";
            ans.pop();
        }
    }
    
    //traverse nodes in the level by level from left to right in a level
    void level_traversal(node*root){//O(n)space and O(n)time
        if(root==nullptr){
            return;
        }
        queue<node*>q;
        q.push(root);
        while(!q.empty()){
            node*curr=q.front();
            q.pop();
            cout<<curr->value<<" -> ";
            if(curr->left!=nullptr){
                q.push(curr->left);
            }
            if(curr->right!=nullptr){
                q.push(curr->right);
            }
        }
    }
    node* searchBST(node*root,int val){//call stack used O(h) space and time
        if(root==nullptr){
            return root;
        }
        if(root->value==val){
            return root;
        }
        else if(root->value>val){
            return searchBST(root->left,val);
        }
        else{
            return searchBST(root->right,val);
        }
    }
    node* searchBST_iter(node*root,int val){//O(h)time and O(1)space
        while(root!=nullptr){
            if(root->value==val){
                return root;
            }
            else if(root->value>val){
                root=root->left;
            }
            else{
                root=root->right;
            }
        }
        return root;
    }
    //return a pair that tell us total levels and no. of nodes in each level present
    pair<int,vector<int>> count_levels(node*root){//O(n)space and O(n)time
        if(root==nullptr){
            return {0,{}};
        }
        queue<node*>q;
        q.push(root);
        vector<int> level;
        while(!q.empty()){
            int size=q.size();
            level.push_back(size);
            for(int i=0;i<size;i++){
                node*curr=q.front();
                q.pop();
                if(curr->left!=nullptr){
                    q.push(curr->left);
                }
                if(curr->right!=nullptr){
                    q.push(curr->right);
                }
            }
        }
        return {level.size(),level};
    }
    //we want to know the height of our bst tree
    int height_call_stack(node*root){//limited space as assingned by OS stack
        if(root==nullptr){
            return 0;
        }
        int lh=height_call_stack(root->left);
        int rh=height_call_stack(root->right);//order of root->left and right doesn't matter in this case
        return 1+max(lh,rh);

    }
    int height_iter(node*root){//no space problem
        stack<pair<node*,int>>st;
        int maxh=0;
        if(root==nullptr){
            return 0;
        }
        st.push({root,1});
        while(!st.empty()){
            int currh=0;
            node* curr=nullptr;
            [curr,currh]=st.top();
            st.pop();
            if(curr==nullptr){
                continue;
            }
            if(currh>maxh){
                maxh=currh;
            }
            st.push({curr->left,currh+1});
            st.push({curr->right,currh+1});
        }
        return maxh;
    }

    //min or max of a subtree with a iven root of that subtree
    node*getmin(node*root){//leftest node of the subtree
        if(root==nullptr){
            return nullptr;
        }
        while(root->left!=nullptr){//go left as much as possible
            root=root->left;
        }
        return root;
    }
    node*getmax(node*root){//rightest node of the subtree
        if(root==nullptr){
            return nullptr;
        }
        while(root->right!=nullptr){//go right as much as possible
            root=root->right;
        }
        return root;
    }
    //inorder --- in this order all numbers are in their sorted order 
    node* inorder_successor(node*root,int val){//successor means next to root means greater or equal to val 
        //so lie in val->right subtree this may not always be true so
        ///its not neccessary that a node will always have a right child even when its not the last element in order
        stack<node*>st;
        node*curr=root;
        bool succ=false;
        while(!st.empty()||curr!=nullptr){
            while(curr!=nullptr){
                st.push(curr);
                curr=curr->left;
            }
            curr=st.top();
            st.pop();
            if(succ==true){
                return curr;
            }
            if(curr->value==val){
                succ=true;
            }
            curr=curr->right;
        }
        return nullptr;
    }
    node* inorder_predecessor(node*root,int val){
        stack<node*>st;
        node*curr=root;
        node*prev=nullptr;
        while(!st.empty()||curr!=nullptr){
            while(curr!=nullptr){
                st.push(curr);
                curr=curr->left;
            }
            curr=st.top();
            st.pop();
            if(curr->value==val){
                return prev;
            }
            prev=curr;
            curr=curr->right;
        }
        return nullptr;
    }
    node* inorder_successor_optimized(node*root,int val){
        node*succ=nullptr;
        while(root!=nullptr){
            if(root->value<=val){
                root=root->right;
            }else{
                succ=root;
                root=root->left;
            }
        }
        return succ;
    }
    node* inorder_predecessor_optimized(node*root,int val){
        node*pred=nullptr;
        while(root!=nullptr){
            if(root->value>=val){
                root=root->left;
            }else{
                pred=root;
                root=root->right;
            }
        }
        return pred;
    }
    void delete_val(node*&root,int val){
        //what we want to delete have three possibilities:::0,1,2 child cases
        //1st we have to reach that node
        if(root==nullptr){
            return;//no such val exists in tree
        }
        if(root->value==val){
            if(root->right==nullptr&&root->left==nullptr){//0 child case
                root->value=0;
                delete root;
                root=nullptr;
            }
            else if(root->left==nullptr||root->right==nullptr){//it has to be 1 child case
                node*todel=root;
                if(root->left==nullptr){
                    root=root->right;
                }else{
                    root=root->left;
                }
                todel->value=0;
                todel->left=todel->right=nullptr;
                delete todel;
            }else{//2 child case
                //we can suery find successor of this node in its right subtree
                node*replace=getmin(root->right);//this will definatly be 1 or 0 child node 
                root->value=replace->value;
                delete_val(root->right,root->value);
            }
        }
        else if(root->value>val){
            delete_val(root->left,val);
        }
        else{
            delete_val(root->right,val);
        }
    }
    node*Lowest_common_ancestor(node*root,node*n1,node*n2){
        while(root!=nullptr){
            if(root->value>n1->value&&root->value>n2->value){
                root=root->left;
            }
            else if(root->value<n1->value&&root->value<n2->value){
                root=root->right;
            }else{//it includes all case such as becoming ancestor of another or division node
                return root;
            }
        }
        return nullptr;
    }
    bool validateBST(node*root){
        node*curr=root;
        node* prev=nullptr;
        stack<node*>st;
        while(!st.empty()||curr!=nullptr){
            while(curr!=nullptr){
                st.push(curr);
                curr=curr->left;
            }
            curr=st.top();
            st.pop();
            if(prev!=nullptr&&prev->value>curr->value){
                return false;
            }
            prev=curr->value;
            curr=curr->right;
        }
        return true;
    }
    bool is_balanced(node*root){//O(n^2)time
        if(root==nullptr){
            return true;
        }
        return is_balanced(root->left)&&is_balanced(root->right)&&abs(height_iter(root->left)-height_iter(root->right))<=1;
    }
    int check_height(node*root){
        if(root==nullptr){
            return 0;
        }
        int left=check_height(root->left);
        if(left==-1){
            return -1;
        }
        int right=check_height(root->right);
        if(right==-1){
            return -1;
        }
        if (abs(left-right)>1){//start of mistortune that is carried back to start root in telling that at this moment itself this tree got unbalanced so no need to check further 1st need to resolve here then check if inbalanced in above part of tree
            return -1;
        }
        return max(left,right)+1;
    }
    bool is_balanced_optimized(node*root){//O(n)time 
        return check_height(root)!=-1;
    }
    
    node*reconstruct_preorder_iter(const vector<int>&order){
        //D ->L -> R
        int n=order.size();
        if(n==0){
            return nullptr;
        }
        stack<node*>st;
        node*root=new node(order[0]);
        st.push(root);
        for(int i=1;i<n;i++){
            node*temp=new node(order[i]);
            if(!st.empty()&&order[i]<st.top()->value){
                st.top()->left=temp;
                st.push(temp);
            }else{
                node*prev=nullptr;
                while(!st.empty()&&st.top()->value<order[i]){
                    prev=st.top();
                    st.pop();
                }
                prev->right=temp;
                st.push(temp);

            }
        }
        return root;
    }
    node*reconstruct_preorder_call_stack(const vector<int>&order,int boundary,int &i){//boundary start from intmax initially and i start from 0
        if(i==order.size()||order[i]>boundary){
            return nullptr;
        }
        node*root=new node(order[i]);
        i+=1;
        root->left=reconstruct_preorder_call_stack(order,root->value,i);
        root->right=reconstruct_preorder_call_stack(order,boundary,i);
        return root;
    }
    node*reconstruct_postorder_iter(const vector<int>&order){
        //LRD --- DRL
        int n=order.size();
        if(n==0){
            return nullptr;
        }
        stack<node*>st;
        node*root=new node(order[n-1]);
        st.push(root);
        for(int i=n-2;i>-1;i--){
            node*temp=new node(order[i]);
            if(!st.empty()&&order[i]>st.top()->value){
                st.top()->right=temp;
                st.push(temp);
            }else{
                node*prev=nullptr;
                while(!st.empty()&&st.top()->value>order[i]){
                    prev=st.top();
                    st.pop();
                }
                prev->left=temp;
                st.push(temp);
            }
        }
        return root;
    }
    node*reconstruct_postorder_call_stack(const vector<int>&order,int boundary,int &i){//boundary start from intmin initially and i starts from n
        //lrd --- drl
        if(i==-1||order[i]<boundary){
            return nullptr;
        }
        node*root=new node(order[i]);
        i-=1;
        root->right=reconstruct_postorder_call_stack(order,root->value,i);
        root->left=reconstruct_postorder_call_stack(order,boundary,i);
        return root;
    }
    
    node*reconstruct_inorder_iter(const vector<int>&order){
        //we can't construct a tree just alone with the inorder information
        return nullptr;
    }
    node*reconstruct_inorder_call_stack(const vector<int>&order){
        //we can't construct a tree just alone with the inorder information
        return nullptr;
    }

    void delete_full_bst(node*&root){//using call stack limited space
        if(root==nullptr){
            return;
        }
        delete_full_bst(root->left);
        delete_full_bst(root->right);
        root->value=0;
        delete root;//left and right are already nullptr
        root=nullptr;
    }
    void destroy_tree(node*& root){//it is itrative and better than call stack in caae or tree is very big then using call stack will overload
        //destructor we must delete node in order such that both its chid nodes have been dicovered so that no leaks 
        //so postorder
        stack<node*>st,todel;
        st.push(root);
        while(!st.empty()){
            node*curr=st.top();
            st.pop();
            if(curr==nullptr){
                continue;
            }
            todel.push(curr);
            st.push(curr->left);
            st.push(curr->right);
        }
        while(!todel.empty()){
            node*curr=todel.top();
            todel.pop();
            curr->value=0;
            curr->right=curr->left=nullptr;
            delete curr;
        }
        root=nullptr;//to avoid dangling pointer
    }
    ~bst(){}
};