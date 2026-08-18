#include<iostream>
#include<vector>
#include<string>
using namespace std;
class KMP{
    private:
    string&text;
    string&pattern;
    vector<int>lps;
    vector<int>output;
    public:
    KMP(string&t,string&p):
    text(t),pattern(p){
        lps.resize(pattern.size(),0);
    }
    void LPS_Table(){
        int i=1,len=0,n=pattern.size();
        while(i<n){
            if(pattern[i]==pattern[len]){
                len++;
                lps[i]=len;
                i++;
            }else{
                if(len==0){
                    i++;
                }else{
                    len=lps[len-1];// Fallback
                }
            }
        }
    }
    vector<int> process(){
        int n=pattern.size();
        if(n==0)return{};
        LPS_Table();
        int i=0,j=0;
        while(i<text.size()){
            if(pattern[j]==text[i]){
                i++;
                j++;
                if(j==n){
                    output.push_back(i-n);
                    j=lps[j-1];//n-1 th
                }
            }else{
                if(j!=0)j=lps[j-1];
                else i++;
            }
        }
        return output;
    }
};