#include<iostream>
#include <algorithm>
#include<stack>
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
    stack<pair<treenode*, bool>> manualstack;
    manualstack.push({root, false});//LIFO rule
    //try to store our recent fork pont address
    while(!manualstack.empty()){
        treenode*curr;
        bool d;
        [curr,d]=manualstack.top();
        manualstack.pop();
        if(curr==nullptr){
            continue;
        }
        if(d==true){
            cout<<curr->value<<"->";
            continue;
        }
        manualstack.push({curr->right,false});
        manualstack.push({curr,true});
        manualstack.push({curr->left,false});
    }
}
void iterativePreOrder(treenode* root){
    //DLR
    stack<pair<treenode*, bool>> manualstack;
    manualstack.push({root, false});//LIFO rule
    //try to store our recent fork pont address
    while(!manualstack.empty()){
        treenode*curr;
        bool d;
        [curr,d]=manualstack.top();
        manualstack.pop();
        if(curr==nullptr){
            continue;
        }
        if(d==true){
            cout<<curr->value<<"->";
            continue;
        }
        manualstack.push({curr->right,false});
        manualstack.push({curr->left,false});
        manualstack.push({curr,true});
    }
}
void iterativePostOrder(treenode* root){
    //LRD
    stack<pair<treenode*, bool>> manualstack;
    manualstack.push({root, false});//LIFO rule
    //try to store our recent fork pont address
    while(!manualstack.empty()){
        treenode*curr;
        bool d;
        [curr,d]=manualstack.top();
        manualstack.pop();
        if(curr==nullptr){
            continue;
        }
        if(d==true){
            cout<<curr->value<<"->";
            continue;
        }
        manualstack.push({curr,true});
        manualstack.push({curr->right,false});
        manualstack.push({curr->left,false});
    }
}
int iterativeMaxDepth(treenode* root){
    stack<pair<treenode*,int>> manualstack;
    manualstack.push({root,1});//root counted at depth of 1
    int max=0;//empty tree
    while(!manualstack.empty()){
        treenode*curr;
        int ph;
        [curr,ph]=manualstack.top();
        manualstack.pop();
        if(curr==nullptr){
            continue;
        }
        manualstack.push({curr->right,ph+1});
        manualstack.push({curr->left,ph+1});//order of right left will not mater this time
        if(max<ph){
            max=ph;
        }
    }
    return max;
}

//only constraint it that it take O(n) space but is a type of universal methord