#include<vector>
#include<string>
#include<stack>
using namespace std;
struct trieNode{
    trieNode*doors[26];
    bool is_end_of_word;
    trieNode(){
        is_end_of_word=false;
        for(int i=0;i<26;i++)doors[i]=nullptr;
    }
};
//tries insertion ,deletion ,search ,prefix search
class Tries{//O(L)time complexity for insert,search,prefix search :::: . It does not matter if your Trie contains 10 words or 10,000,000 words; finding "APPLE" will always take exactly 5 steps.
    //O(n x L x 26)space complexity :::: Every single node physically instantiates an array of 26 pointers
    trieNode*root_room;
    vector<string>output;
    public:
    Tries(){root_room = new trieNode();}
    //insert in tries
    void insert(string word){
        trieNode*curr=root_room;
        for(char&c:word){
            int index=c-'a';
            if(curr->doors[index]==nullptr){
                trieNode*next_room=new trieNode();
                curr->doors[index]=next_room;
            }
            curr=curr->doors[index];
        }
        curr->is_end_of_word=true;
    }
    //search exact word
    bool search(string word){
        trieNode*curr=root_room;
        for(char&c:word){
            int index=c-'a';
            if(!curr->doors[index])return false;
            curr=curr->doors[index];
        }
        return curr->is_end_of_word;
    }
    bool PrefixSearch(string word){
        trieNode*curr=root_room;
        for(char &c:word){
            int index=c-'a';
            if(!curr->doors[index])return false;
            curr=curr->doors[index];
        }
        return true;
    }
    void solve(trieNode*curr,string &pre){
        if(curr->is_end_of_word){
            output.push_back(pre);
        }
        for(int i=0;i<26;i++){
            if(curr->doors[i]){
                pre.push_back(char(int('a'+i)));
                solve(curr->doors[i],pre);
                pre.pop_back();//backtrack
            }
        }
    }
    pair<bool,vector<string>>autocomplete(string &word){
        output.clear();
        trieNode*curr=root_room;
        for(char &c:word){
            int index=c-'a';
            if(!curr->doors[index])return {false,{}};
            curr=curr->doors[index];
        }
        string pre=word;
        solve(curr,pre);
        return {true,output};
    }
    bool delete_word(string &word){
        stack<pair<trieNode*,int>>st;
        trieNode*curr=root_room;
        for(char&c:word){
            int index=c-'a';
            if(!curr->doors[index])return false;//word not found
            st.push({curr,index});
            curr=curr->doors[index];
        }
        curr->is_end_of_word=false;
        while(!st.empty()){
            bool have_child=false;
            for(int i=0;i<26;i++){
                if(curr->doors[i]){
                    have_child=true;
                    break;
                }
            }
            if(have_child||curr->is_end_of_word){
                break;
            }
            trieNode*parent=st.top().first;
            int index=st.top().second;
            st.pop();
            delete curr;
            parent->doors[index]=nullptr;
            curr=parent;
        }
        return true;
    }
    bool check_no_childre(trieNode*curr){
        for(int i=0;i<26;i++){
            if(curr->doors[i]){
                return false;
            }
        }
        return true;
    }
    bool delete_helper(trieNode*curr,string&word,int depth){
        if(depth==word.size()){
            curr->is_end_of_word=false;
            return check_no_childre(curr);//true (meaning "delete me"). Otherwise, return false ("keep me").
        }
        int index=word[depth]-'a';
        if(!curr->doors[index])return false;
        bool should_delete_child=delete_helper(curr->doors[index],word,depth+1);
        if (should_delete_child){
            delete curr->doors[index];
            curr->doors[index]=nullptr;
        }
        if(!curr->is_end_of_word&&check_no_childre(curr))return true;
        return false;
    }
};