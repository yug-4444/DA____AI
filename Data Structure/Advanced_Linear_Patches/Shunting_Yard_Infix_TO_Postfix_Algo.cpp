#include<iostream>
#include<string>
#include<stack>
#include<unordered_map>
#include<cctype>//isspace , isalnum
using namespace std;
class ShuntingYard{
    public:
    void infix_Postfix(const string &infix)const{
        static unordered_map<char, int> map = {{'+', 2},{'-', 2},{'*', 3},{'/', 3},{'^', 4},{'(', 1}};
        stack<char>st;
        int n=infix.size();
        string output="";
        for(int i=0;i<n;i++){
            char curr=infix[i];
            int ascii=int(curr);
            if(curr==' ')continue;//isspace
            if((ascii>=48&&ascii<=57)||(ascii>=65&&ascii<=90)||(ascii>=97&&ascii<=122)){//or use isalnum(curr)
                output+=curr;
            }else if(curr=='('){
                st.push(curr);
            }else if(curr==')'){
                while(!st.empty()&&st.top()!='('){//since ) then there has to be ( so there is no chance of becoming empty
                    output+=st.top();
                    st.pop();
                }
                if(!st.empty())st.pop();
            }else{
                if(curr=='^'){//as its right associative so if ^^ in stack allowed 
                    st.push(curr);
                    continue;
                }
                while(!st.empty()&&map[curr]<=map[st.top()]){//++ in stack not allowed
                    output+=st.top();
                    st.pop();
                }
                st.push(curr);
            }
        }
        while(!st.empty()){
            output+=st.top();
            st.pop();
        }
        cout<<"Postfix :"<<output<<"\n";
    }
};