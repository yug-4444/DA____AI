//2D data structure
#include<iostream>
#include <algorithm>
using namespace std;
//1D data structure comsumes a lot of time in searching among billions of element
//2D data structure breaks universe in half with the main root at the top of hierarchy
struct treenode{
    //coustom data type that hold it value and left down side first node pointer similar for right side
    //4bytes+8bytes+8bytes=20 bytes each node
    //on a 64-bit system, the compiler will output 24 bytes, not 20. CPUs read memory in chunks (usually 8 bytes at a time)
    //as of Memory alingment OS reads in 8bytes each time so 4 bytes of empty "padding" after int to align the pointers perfectly.
    int value;
    treenode *right;
    treenode *left;
    treenode(int val){
        value=val;
        right=nullptr;//to prevent dangling pointers
        left=nullptr;
    }
};
//******THEORY*********
//fracture the memory
//memory branches outwards like an upside-down tree.
//bianry tree
//it uses a invisible stack manages by OS itself when at a fork and choses a path and rech dead end along it, then this
//stack act as respown point from where we can revind and enter right path at that fork
//this invisible stack:::CALL STACK:::Recursion
//stack holds all the fork points from the root including root itself
//at top it hols the latest fork point and each time it hits a dead end it pop the latest fork point from top and try path along it
//even if all the forks along it fails then it goes to fork point before this point and tries from there 
//this goes on till all possible path or node have been checked or visited--->navigate the entire tree
//**********************
//three ways to navigate as depth forst search types ---using stack ---os call stack
//1. pre-order-DLR-1st process data then move left and then right                     ---->CLONE ORDER
//2. in-order-LRD-gives data in sorted order that is in our binary tree               ---->SORTED ORDER
//3. post-order-LRD-only when a nodes all child have been explored my we process data ---->DELETION ORDER
void preOrder(treenode*root){
    if(root==nullptr){
        return;
    }
    cout<<root->value<<" -> ";
    preOrder(root->left);
    preOrder(root->right);
}
void inOrder(treenode*root){
    if(root==nullptr){
        return;//we hit a dead end and need a path to move forward so we go back to the latest fork point and see for available paths or choices
    }
    inOrder(root->left);//root becomes our fork point and left is our 1st choice 
    cout<<root->value<<" -> ";//intermediate required to be fullfilled before 2nd choice which is proccessing our data at this fork
    inOrder(root->right);//2nd choics
    //no more choices reach a dead end so go back to previous fork before this one 
}
void postOrder(treenode*root){
    if(root==nullptr){
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    cout<<root->value<<" -> ";
}
//let see level by level traversal ::: root at level 0 then boths it child at level 1 and so on
#include<queue>
void leveltraversal(treenode*root){
    if(root==nullptr){
        return;//no tree available
    }
    queue<treenode*>q;
    q.push(root);
    while(!q.empty()){//in a full tree level 0 1 element ,lv 1 ->2 ,lv 2->4 ,lv n 2^n
        treenode* temp=q.front();//normal binary tree with manual wiring
        cout<<temp->value<<" -> ";
        q.pop();
        if(temp->left!=nullptr){
            q.push(temp->left);
        }
        if(temp->right!=nullptr){
            q.push(temp->right);
        }//queue is a FIFO
    }
}
//now we have to types to tree traversals
//but still we haven't taken into account of bsae problem that how should or where should our input data be pust 
//such that duing search O(n) traversals can be avoided
//we have BST tree binary search tree O(n) ->O(logn) reduced rule::: w.r.t node greater on right and smaller on left no random places to fill allowed
//BST is a subset of Binary tree

//insert in bst where we return the main root
treenode* insertBST(treenode*root,int val){//we return a pointer to root so no need to pass root as a refrence
    if(root==nullptr){
        root=new treenode(val);//only create new node when we find a empty space else memory leak
        return root;
    }
    if(root->value>=val){
        root->left=insertBST(root->left,val);
    }else{
        root->right=insertBST(root->right,val);
    }
    return root;//This guarantees that as the Call Stack rewinds, every parent safely locks onto its children without breaking the wires.
}
void insertBST2(treenode*&root,int val){//we return a pointer to root 
    if(root==nullptr){
        root=new treenode(val);//only create new node when we find a empty space else memory leak
        return;
    }
    if(root->value>=val){
        insertBST2(root->left,val);
    }else{
        insertBST2(root->right,val);
    }
}
bool searchBST(treenode*root,int target){
    if(root==nullptr){
        return false;//we reached the end of unvivese within its splits still dindn't found target
    }
    if(root->value==target){//return as bool type so some thing has to be returned
        return true;
    }else if(root->value>target){//magic of log(n) to be particular log_2 n as only two choices at each fork and till the end we will only chose one so it is in if condition
        return searchBST(root->left,target);
    }else{
        return searchBST(root->right,target);
    }
}
//deletion of a node in bst
//deletion engine 
//it will have three cases
//1: no child i.e a leaf node just delete it and get over withit
//2: one child just delete parent nad replace it with child node
//3: two child if parent is delete we are left with two rootless weeds/subtrees 
//option find largest in left tree or smallest in right subtree so that bst rules remain
//we chose inorder sucessor smallest in right subtree
treenode* getmin(treenode*root){//inorder traversal 1st cout we do is our minimum so leftest possible
    if(root==nullptr){
        return nullptr;
    }
    while(root->left!=nullptr){//iterative approch more good than our recursive approch as well as we don't have to store our fork points in this so iterative way is good as not history required
        root=root->left;
    }
    return root;//we want to return min node address not root address
}
void deletenode(treenode*&root,int target){
    if(root==nullptr){
        return ;
    }
    if(target==root->value){
        if(root->left==nullptr&&root->right==nullptr){//0 childcase
            root->value=0;
            delete root;
            root=nullptr;
            return;
        }
        else if(root->left==nullptr||root->right==nullptr){//can only be valid for one child case not two as if above case passess then dont come to it
            treenode*temp=root;
            if(root->left!=nullptr){
                root=root->left;
            }else{
                root=root->right;
            }
            temp->value=0;//physically disconnected it from the universe before destroying it so that no radiation could leak into the tree.
            temp->left=temp->right=nullptr;
            delete temp;
            return;
        }
        else{//now it has to be two child case
            treenode*replace=getmin(root->right);//there has to be atleast 1 node on right subtree else become 1 child case
            int val=replace->value;
            //now we need to delete this min node this will be 1 chil or no child case already covered
            deletenode(root,val);//!!!!!order of lines matter
            root->value=val;
            return;
        }
    }else if(target<root->value){
        deletenode(root->left,target);
    }else{
        deletenode(root->right,target);
    }
}
//O(logn)only if it doesn't collapse to straight line and reduced to O(n)
int treehight(treenode*root){//monitor for above problem
    if (root==nullptr){
        return 0;
    }
    int left_height=treehight(root->left);//scout to left
    int right_height=treehight(root->right);//scout to right
    return 1+max(left_height,right_height);//maximum height of the subtrees +1 = total height the close to logn better 
    //farter to logn and closer to n is closer to becoming 1D theough still is 2D 
}
void deletetree(treenode*&root){//as root will be edited so pass by reference
    //before deleteing a node we want that both its childer have been processed through deleting process else memory leak 
    //think of visiting nodes inorder of post
    if(root==nullptr){
        return;
    }
    deletetree(root->left);
    deletetree(root->right);
    root->value=0;
    root->left=nullptr;//to avoid dangling pointer
    root->right=nullptr;
    delete root;
    root=nullptr;
}
int main(){
    treenode* root = nullptr;
    insertBST2(root, 100);
    insertBST2(root, 50);
    insertBST2(root, 150);
    insertBST2(root, 25);
    insertBST2(root, 75);

    cout << "In-order before deletion: ";
    inOrder(root); cout << "nullptr\n";

    deletenode(root, 50);

    cout << "In-order after deleting 50: ";
    inOrder(root); cout << "nullptr\n";

    deletenode(root, 100);

    cout << "In-order after deleting 100: ";
    inOrder(root); cout << "nullptr\n";
    cout << "Tree height: " << treehight(root) << endl;
    deletetree(root);
    return 0;
}