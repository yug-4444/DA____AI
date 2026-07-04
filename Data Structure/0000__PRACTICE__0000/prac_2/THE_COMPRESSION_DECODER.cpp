#include <string>
#include <stack>
#include<iostream>
#include<cctype>
using namespace std;
class CompressionDecoder {
public:
    string decodeString(string s) {
        stack<string>ans;
        stack<int>num;
        int curr_num=0;
        string curr_ans="";
        for(auto&c:s){
            if(isdigit(c)){
                curr_num=10*curr_num+c-'0';
            }
            else if(c=='['){
                num.push(curr_num);
                ans.push(curr_ans);
                curr_num=0;
                curr_ans="";
            }
            else if(c==']'){//at bottom of ans "" is stored always
                if(num.empty()||ans.empty()){
                    cout<<"wrong input";
                    return "";
                }
                string result="";
                for(int i=0;i<num.top();i++){
                    result+=curr_ans;
                }
                num.pop();
                curr_ans=ans.top()+result;
                ans.pop();
            }else{
                curr_ans+=c;
            }
        }
        return curr_ans;
    }
};