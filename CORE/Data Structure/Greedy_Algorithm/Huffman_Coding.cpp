#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<tuple>
using namespace std;
struct node{
    int freq;
    char c;
    node*right;
    node*left;
    node(int f,char ch='$'):freq(f),c(ch),right(nullptr),left(nullptr){}
};
struct Compare {
    bool operator()(node* a, node* b) {
        return a->freq > b->freq; // min-heap
    }
};
class huffman{
    private:
    const vector<int>&frequency;
    const vector<char>&characters;
    int n;
    public:
    huffman(const vector<int>&f,const vector<char>&ch):
    frequency(f),characters(ch),n(frequency.size()){}
    void traversal(node*root,vector<tuple<char,int,string>>&table,string &s){//post->LRD
        if(!root)return;
        if(!root->left&&!root->right){
            table.push_back(make_tuple(root->c, root->freq, s));
            delete root;
            return;
        }
        s.push_back('0');
        traversal(root->left,table,s);
        s.pop_back();
        s.push_back('1');
        traversal(root->right,table,s);
        s.pop_back();
        delete root;
    }
    pair<int,vector<tuple<char,int,string>>>process(){
        if(n==1)return{frequency[0]*1,{make_tuple(characters[0],frequency[0],"0")}};
        priority_queue<node*,vector<node*>,Compare>pq;
        for(int i=0;i<n;i++){
            node*temp=new node(frequency[i],characters[i]);
            pq.push(temp);
        }
        while(pq.size()!=1){
            node*smaller=pq.top();
            pq.pop();
            node*bigger=pq.top();
            pq.pop();
            node*temp=new node(smaller->freq+bigger->freq);
            temp->left=smaller;
            temp->right=bigger;
            pq.push(temp);
        }
        node*root=pq.top();
        vector<tuple<char,int,string>>table;
        string s="";
        traversal(root,table,s);
        int compressedbits=0;
        for(int i=0;i<n;i++){
            compressedbits+=get<1>(table[i])*(get<2>(table[i]).size());
        }
        return{compressedbits,table};
    }
};