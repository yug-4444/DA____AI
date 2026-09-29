//tree reconstructions both iterative and recurssive
#include<iostream>
#include<climits>
#include<stack>
#include<vector>
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
class reconstruct{
    private:
    const vector<int> &order;
    int size,i,i2;
    public:
    reconstruct(vector<int>&arr){
        order=arr;
        size=order.size();
        i=0;
        i2=size-1;
    }
    treenode* rec_preOrder(int bound){//Bound starts INT_MAX
        //d->l->r
        if(i==size||bound<order[i]){
            return nullptr;
        }
        treenode*root=new treenode(order[i]);
        i+=1;
        root->left=rec_preOrder(root->value);
        root->right=rec_preOrder(bound);
        return root;
    }
    treenode* ite_preOrder(){
        if(size==0){
            return nullptr;
        }
        stack<treenode*>st;
        treenode*root=new treenode(order[0]);
        st.push(root);
        for(int j=1;j<size;j++){
            treenode*temp=new treenode(order[j]);
            //we want to place it in its rightfull position
            if(st.top()->value>temp->value){
                st.top()->left=temp;
                st.push(temp);
            }
            else{//if not smaller then has to to be greter then latest fork point now also need to check till lesser than forks parent i.e forks fork compare till st is empty since order is valid then stack will definatly find such condition else invalid order
                treenode*pos=nullptr;
                while(!st.empty()&&st.top()->value>temp->value){//this will run atleast one time
                    pos=st.top();
                    st.pop();
                }
                pos->right=temp;
                //now laest is temp
                st.push(temp);
                //not reinsert pos a left is already done then only do we go to right now after insert there will be no place left as well as order move forwards this node 
            }
        }
        return root;
    }
    treenode* rec_inOrder(){//L->D->R
        //it will fail as impossible to reconstruct alone with inorder given 
        //mathematically impossible to reconstruct a unique Binary Search Tree using only an In-Order array.
        //In-Order strips away all structural "entropy" (the sequence of how the root was placed), the OS has no idea who the parent is. You can never build a BST from just an In-Order array.
        return nullptr;
    }
    treenode* ite_inOrder(){//L->D->R
        //it will fail as impossible to reconstruct alone with inorder given 
        //mathematically impossible to reconstruct a unique Binary Search Tree using only an In-Order array.
        //In-Order strips away all structural "entropy" (the sequence of how the root was placed), the OS has no idea who the parent is. You can never build a BST from just an In-Order array.
        return nullptr;
    }
    treenode* rec_postOrder(int bound){//bound from INT_MIN
        //L->R->D
        //only when both chids be done will it give or simply 
        //just reverse the given oder then reapply the preorder similar but not exact logic to get correct postorder
        //reverse order becomes D->R->L
        if(i2==-1||order[i2]<bound){
            return nullptr;
        }
        treenode*root=new treenode(order[i2]);
        i2-=1;
        root->right=rec_postOrder(root->value);
        root->left=rec_postOrder(bound);
        return root;
    }
    treenode* ite_postOrder(){
        stack<treenode*>st;
        treenode*root=new treenode(order[size-1]);
        st.push(root);
        for(int j=size-2;j>-1;j--){
            treenode*temp=new treenode(order[j]);
            if(st.top()->value<temp->value){
                st.top()->right=temp;
                st.push(temp);
            }
            else{
                //now it has to be less but greater than parent to the fork point
                treenode*pos=nullptr;
                while(!st.empty()&&st.top()->value>temp->value){//will run atleat once
                    pos=st.top();
                    st.pop();
                }
                pos->left=temp;
                st.push(temp);
            }
        }
        return root;
    }
};