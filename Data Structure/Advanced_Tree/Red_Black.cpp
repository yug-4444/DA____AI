#include<iostream>
using namespace std;
//first see base diagrams of basic delete and insert 
enum colors{red,black};
struct node{
    node*parent;
    node*right;
    node*left;
    int key;
    colors color;
    node():key(0),color(black),right(nullptr),left(nullptr),parent(nullptr){}
    node(int k):key(k),color(red),right(nullptr),left(nullptr),parent(nullptr){}
};
class RBT{
    private:
    node*nil;
    public:
    RBT(){
        nil=new node();
        nil->parent=nil->right=nil->left=nil;
    }
    node*create_node(int k){
        node*temp=new node(k);
        temp->left=temp->right=temp->parent=nil;
        return temp;
    }
    void RightRotate(node*&root,node*y){
        node*x=y->left;
        if(x==nil)return;

        x->parent=y->parent;
        if(y->parent==nil)root=x;
        else if(y->parent->left==y)y->parent->left=x;
        else y->parent->right=x;

        y->left=x->right;
        if(y->left!=nil)y->left->parent=y;
        x->right=y;
        y->parent=x;
    }
    void LeftRotate(node*&root,node*y){
        node*x=y->right;
        if(x==nil)return;

        x->parent=y->parent;
        if(y->parent==nil)root=x;
        else if(y->parent->left==y)y->parent->left=x;
        else y->parent->right=x;

        y->right=x->left;
        if(y->right!=nil)y->right->parent=y;
        x->left=y;
        y->parent=x;
    }
    void insertion_fix_rbt(node*&root,node*z){
        while(z->parent!=nil&&z->parent->parent!=nil&&z->parent->color==red){
            if(z->parent->parent->left==z->parent){
                node*uncle=z->parent->parent->right;
                if(uncle!=nil&&uncle->color==red){
                    z->parent->color=black;
                    uncle->color=black;
                    z->parent->parent->color=red;
                    z=z->parent->parent;
                }else{
                    if(z->parent->right==z){
                        z=z->parent;
                        LeftRotate(root,z);
                    }
                    z->parent->color=black;
                    z->parent->parent->color=red;
                    RightRotate(root,z->parent->parent);
                }
            }else{
                node*uncle=z->parent->parent->left;
                if(uncle!=nil&&uncle->color==red){
                    z->parent->color=black;
                    uncle->color=black;
                    z->parent->parent->color=red;
                    z=z->parent->parent;
                }else{
                    if(z->parent->left==z){
                        z=z->parent;
                        RightRotate(root,z);
                    }
                    z->parent->color=black;
                    z->parent->parent->color=red;
                    LeftRotate(root,z->parent->parent);
                }
            }
        }
        root->color=black;
    }
    void insert_rbt(node*&root,int k){
        node*temp=create_node(k);//red color
        if(root==nil){
            root=temp;
            temp->color=black;
            return;
        }
        node*curr=root;
        node*prev=nil;
        while(curr!=nil){
            prev=curr;
            if(curr->key<k)curr=curr->right;
            else curr=curr->left;
        }
        curr=prev;
        if(curr->key<k)curr->right=temp;
        else curr->left=temp;
        temp->parent=curr;
        insertion_fix_rbt(root,temp);
    }
    void transplant(node*&root,node*u,node*v){
        if(root==nil||u==nil)return;
        if(u->parent==nil)root=v;
        else if(u->parent->left==u)u->parent->left=v;
        else u->parent->right=v;
        if(v!=nil)v->parent=u->parent;
    }
    node*get_min(node*root){
        while(root->left!=nil){
            root=root->left;
        }
        return root;
    }
    void delete_fix_rbt(node*root,node*x){//x node is considered as a double black node
        while(x!=nil&&x!=root&&x->color==black){
            if(x->parent->left==x){
                node*w=x->parent->right;
                if(w!=nil&&w->color==red){
                    w->color=black;
                    x->parent->color=red;
                    LeftRotate(root,x->parent);
                    w=x->parent->right;
                }
                else{
                    if(w!=nil&&w->left->color==black&&w->right->color==black){
                        w->color=red;
                        x=x->parent;//x is position of double black
                    }else{
                        if(w!=nil&&w->right->color!=red){
                            w->color=red;
                            w->left->color=black;
                            RightRotate(root,w);
                            w=x->parent->right;
                        }
                        w->color=x->parent->color;
                        x->parent->color=black;
                        w->right->color=black;
                        LeftRotate(root,x->parent);
                        x=root;//only root can swallow double black to single black
                    }
                }
            }else{
                node*w=x->parent->left;
                if(w!=nil&&w->color==red){
                    w->color=black;
                    x->parent->color=red;
                    RightRotate(root,x->parent);
                    w=x->parent->left;
                }
                else{
                    if(w!=nil&&w->right->color==black&&w->left->color==black){
                        w->color=red;
                        x=x->parent;//x is position of double black
                    }else{
                        if(w!=nil&&w->left->color!=red){
                            w->color=red;
                            w->right->color=black;
                            LeftRotate(root,w);
                            w=x->parent->left;
                        }
                        w->color=x->parent->color;
                        x->parent->color=black;
                        w->left->color=black;
                        RightRotate(root,x->parent);
                        x=root;//only root can swallow double black to single black
                    }
                }
            }
        }
        if(x!=nil)x->color=black;
    }
    void delete_rbt(node*root,node*z){
        node*y=z;
        colors del_col=y->color;
        node*x=nil;
        if(y->right==nil&&y->left==nil){
            if(root==z){
                root=nil;
                delete z;
                return;
            }
            if(y->color==black)delete_fix_rbt(root,y);//so that when we delete y it would already have given a black above means its delteion of y will not destroy black property
            transplant(root,y,nil);
            delete z;
            return;
        }else if(y->right==nil){
            x=y->left;
            transplant(root,z,z->left);
        }else if(y->left==nil){
            x=y->right;
            transplant(root,z,z->right);
        }else{
            node*replace=get_min(z->right);
            y=replace;
            del_col=y->color;
            x=y->right;

            if(replace!=z->right){
                transplant(root,y,y->right);
                y->right=z->right;
                y->right->parent=y;
            }
            transplant(root,z,y);
            y->left=z->left;
            y->left->parent=y;
            y->color=z->color;
        }
        delete z;
        if(del_col==black)delete_fix_rbt(root,x);
    }
};