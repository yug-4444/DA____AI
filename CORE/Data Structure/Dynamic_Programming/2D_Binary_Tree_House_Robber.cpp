#include<iostream>
#include<vector>
using namespace std;
struct node{
    int val;
    node*left;
    node*right;
    node(int v):val(v),left(nullptr),right(nullptr){}
};
class Binary_robber{
    public:
    pair<int,int>dfs(node*root){//0->rob 1->skip
        if(!root)return{0,0};

        // Post-Order Traversal: Go all the way to the leaves first
        pair<int,int>left=dfs(root->left);
        pair<int,int>right=dfs(root->right);

        int rob=root->val+left.second+right.second;
        int skip=max(left.first,left.second)+max(right.first,right.second);
        return{rob,skip};
    }
    int solution(node*root){
        pair<int,int>ans=dfs(root);
        return max(ans.first,ans.second);
    }
};