#include<iostream>
using namespace std;
struct node{
    int key;
    node*left;
    node*right;
    int height;
    node(int k){
        key=k;
        left=right=nullptr;
        height=1;
    }
};
class AVL{
    public:
    int get_height(node*ptr){
        if(!ptr)return 0;
        return ptr->height;
    }
    int balance_factor(node*ptr){
        return get_height(ptr->left)-get_height(ptr->right);
    }
    node* RightRotation(node*y){//when LL imbalance
        node*x=y->left;
        node*T2=x->right;
        x->right=y;
        y->left=T2;
        y->height=max(get_height(y->left),get_height(y->right))+1;
        x->height=max(get_height(x->left),get_height(x->right))+1;
        return x;//root
    }
    node* LeftRotation(node*y){
        node*x=y->right;
        node*T2=x->left;
        x->left=y;
        y->right=T2;
        y->height=max(get_height(y->left),get_height(y->right))+1;
        x->height=max(get_height(x->left),get_height(x->right))+1;
        return x;
    }
    void insert(node*&root,int k){
        if(!root){
            root=new node(k);
            return;
        }
        else if(root->key<k)insert(root->right,k);
        else if(root->key>k)insert(root->left,k);
        else return;
        root->height=max(get_height(root->left),get_height(root->right))+1;
        int bf=balance_factor(root);
        if(bf>1&&balance_factor(root->left)>=0){//or root->left->key>k
            root=RightRotation(root);
        }else if(bf<-1&&balance_factor(root->right)<=0){//or root->right->key<k
            root=LeftRotation(root);
        }else if(bf>1&&balance_factor(root->left)<0){//or root->left->key<k
            root->left=LeftRotation(root->left);
            root=RightRotation(root);
        }else if(bf<-1&&balance_factor(root->right)>0){//or root->right->key>k
            root->right=RightRotation(root->right);
            root=LeftRotation(root);
        }
    }
    node*get_minimum(node*root){
        if(!root)return nullptr;
        while(root->left){
            root=root->left;
        }
        return root;
    }
    void delete_avl(node*&root,int k){
        if(root==nullptr)return;
        if(root->key<k)delete_avl(root->right,k);
        else if(root->key>k)delete_avl(root->left,k);
        else{
            if(!root->left&&!root->right){
                root->key=0;
                delete root;
                root=nullptr;
            }else if(!root->left||!root->right){
                node*temp=root;
                if(root->left)root=root->left;
                else root=root->right;
                temp->key=temp->height=0;
                temp->left=temp->right=nullptr;
                delete temp;
            }else{
                node*replace=get_minimum(root->right);
                root->key=replace->key;
                delete_avl(root->right,replace->key);
            }
        }
        if(!root)return;
        root->height=max(get_height(root->left),get_height(root->right))+1;
        int bf=balance_factor(root);

        if(bf>1&&balance_factor(root->left)>=0){
            root=RightRotation(root);
        }else if(bf<-1&&balance_factor(root->right)<=0){
            root=LeftRotation(root);
        }else if(bf>1&&balance_factor(root->left)<0){
            root->left=LeftRotation(root->left);
            root=RightRotation(root);
        }else if(bf<-1&&balance_factor(root->right)>0){
            root->right=RightRotation(root->right);
            root=LeftRotation(root);
        }
    }
};