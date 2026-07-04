#include<iostream>
#include<stack>
#include<vector>
#include<climits>
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
class lca{//lowest common ancestor of two nodes when they exists in a bst tree
    private:
    treenode*root;
    treenode*p;
    treenode*q;
    int pval,qval;
    public:
    lca(treenode*r,treenode*n1,treenode*n2){
        root=r;
        p=n1;
        q=n2;
        pval=p->value;
        qval=q->value;
    }
    //one methord is to make vector that store pointer aong path from root of both p and q and then after reaching both we start by comparing vectors and get ans but in this both time and space is of healthy amount
    //simlarly we can make a stack that store recntly fork points along path and then we can compare two stacks by pop out and compare till they match and this match is anwser
    // but both require full paths of each and additional space to store and this below methord fits best acording to constraints
    treenode*lca_node(){
        treenode*curr=root;
        while (true){//total cases when mix smaller and larger and in else  one is a part of subtree of another also there
            if(curr->value>pval&&curr->value>qval){//while(curr != nullptr) in case given that node might not be present but given that they are present in tree
                curr=curr->left;
            }
            else if((curr->value<pval&&curr->value<qval)){
                curr=curr->right;
            }
            else{//we can be confirm at this point lca as well as till this node to the top have to send data at above this is common path of both
                //include then become equal in any along path i.e then one is a part of subtree of another then also discovered meaning one node is the direct ancestor of the other
                return curr;
            }
        }
        //O(h)time and O(1)space
    }

}