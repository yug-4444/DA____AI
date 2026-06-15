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
class check{
    private:
    treenode*root;
    vector<int>arr;
    public:
    check(treenode*r){
        root=r;
    }
    void inorder(){
        //LDR
        stack<treenode*>st;
        treenode*curr=root;
        while(curr!=nullptr||!st.empty()){
            while(curr!=nullptr){
                st.push(curr);
                curr=curr->left;
            }
            curr=st.top();
            st.pop();
            arr.push_back(curr->value);
            curr=curr->right;
        }
    }
    bool valid(){
        if(arr.size()==0){
            return true;
        }
        for(int i =1;i<arr.size();i++){
            if(arr[i]<arr[i-1]){
                return false;
            }
        }
        return true;
    }
};//O(n)time but O(n)space as well due to dynamic array and O(h)space for stack
class check2{
    private:
    treenode*root;
    public:
    check2(treenode*r){
        root=r;
    }
    bool valid(){
        stack<treenode*>st;
        treenode*curr=root;
        int prev=INT_MIN;
        while(curr!=nullptr||!st.empty()){
            while(curr!=nullptr){
                st.push(curr);
                curr=curr->left;
            }
            curr=st.top();
            //now we don't have to print we have to check with prev and if valid then remember it
            if(curr->value<prev){
                return false;
            }
            prev=curr->value;
            st.pop();
            curr=curr->right;
        }
        return true;
    }
};//now this may even have time less than O(n) but in previous code time is atleast O(n)
//space is O(h) for stack may even be less but in previous code space is fixed about O(n)+O(h)
