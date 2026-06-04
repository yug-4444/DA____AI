#include<iostream>
#include <algorithm>
#include<stack>
#include<queue>
using namespace std;
struct treenode{
    int value;
    treenode *right;
    treenode *left;
    treenode(int val){
        value=val;
        right=nullptr;//to prevent dangling pointers
        left=nullptr;
    }
};
void iterativeInOrder(treenode* root){//without using call stack ---OS that is in stack memory we are building manual stack space in heap memory so it call hold upto gigabytes of data instead of megabytes
    //LDR
    if(root==nullptr){
        return;
    }
    stack<treenode*>manualstack;
    treenode*curr=root;
    //now we are down to the left most element along with all the pointer along the path
    //slide down to the left most
    while(curr!=nullptr||!manualstack.empty()){
        while(curr!=nullptr){
            manualstack.push(curr);
            curr=curr->left;
        }//go to as much as left possible
        curr=manualstack.top();
        cout<<curr->value<<" -> ";
        curr=curr->right;
    }
}
void iterativePreOrder(treenode* root){
    //DLR
    stack<treenode*>manualstack;
    manualstack.push(root);
    while(!manualstack.empty()){
        treenode*curr;
        curr=manualstack.top();
        manualstack.pop();
        if(curr==nullptr){
            continue;
        }
        cout<<curr->value<<" -> ";
        manualstack.push(curr->right);
        manualstack.push(curr->left);
    }
}
void iterativePostOrder(treenode* root){
    //LRD
    stack<treenode*>s1,s2;
    //D->L->R
    //D->R->L
    //L->R->D
    //so instead when we suppose to print data we store this every time in stack2 so that ultimatelly result is reversed
    //s1 as a normal stack
    s1.push(root);
    while(!s1.empty()){
        treenode*curr=s1.top();
        s1.pop();
        //route d->r->l
        if(curr==nullptr){
            continue;
        }
        s2.push(curr);//now push the data to be processed in stack so to print/proceess order in reverse
        s1.push(curr->right);
        s1.push(curr->left);
    }
    while(!s2.empty()){
        treenode*curr=s2.top();
        cout<<curr->value;
        s2.pop();
    }
}

//space constraint O(depth)  ,depth:height of tree

//height for a bfs tree uses queue
int iterativeMaxDepth(treenode* root){
    if(root==nullptr){
        return 0;
    }
    queue<pair<treenode*,int>>q;
    q.push({root,1});
    int maxh=1;
    while(!q.empty()){
        treenode*curr;
        int h;
        [curr,h]=q.front();
        q.pop();
        if(curr->left!=nullptr){
            q.push({curr->left,h+1});
        }
        if(curr->right!=nullptr){
            q.push({curr->right,h+1});
        }
        if(h>maxh){
            maxh=h;
        }
    }
    return maxh;
}
//it uses extra 4 byte space each time
//now 
int iterativeMaxDepth2(treenode* root){
    if(root==nullptr){
        return 0;
    }
    queue<treenode*>q;
    q.push(root);
    int h=0;
    while(!q.empty()){
        int iter=q.size();//no. of nodes in each level
        //total height is no. of total levels
        h+=1;
        for(int i=1;i<=iter;i++){
            treenode*curr=q.front();
            q.pop();
            if(curr->left!=nullptr){
                q.push(curr->left);
            }
            if(curr->right!=nullptr){
                q.push(curr->right);
            }
        }
    }
    return h;
}