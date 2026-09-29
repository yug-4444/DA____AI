#include<iostream>
using namespace std;
struct node{
    int key;
    node*right;
    node*left;
    node(int v):key(v),left(nullptr),right(nullptr){}
};
class Morris_Traversal{//O(1)auxillary space and O(n)time
    public:
    void traversal(node*root){
        node*curr=root;
        while(curr){
            if(!curr->left){
                cout<<curr->key<<"->";
                curr=curr->right;
            }else{
                node*pred=curr->left;
                while(pred->right!=nullptr&&pred->right!=curr){
                    pred=pred->right;
                }
                if(!pred->right){
                    pred->right=curr;
                    curr=curr->left;
                }else{
                    pred->right=nullptr;
                    cout<<curr->key<<"->";
                    curr=curr->right;
                }
            }
        }
    }
};