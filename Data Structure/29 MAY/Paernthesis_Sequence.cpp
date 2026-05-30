//use parentheses (), curly braces {}, and square brackets []
#include<iostream>
#include<climits>
using namespace std;
class sequece{
    private:
    int top_index;
    string input;
    char*st;
    int n;
    public:
    sequece(string se){
        input=se;
        n=input.size();
        top_index=-1;
        st=new char[n];
    }
    bool solve(){
        for(int i=0;i<n;i++){
            char curr=input[i];
            if(curr=='('||curr=='{'||curr=='['){
                top_index+=1;
                st[top_index]=curr;//pop in stack as well there won't ever be time it overflow
            }
            else{
                char to_check=curr;
                if(top_index==-1){
                    return false;
                }
                else if(to_check==')'&&st[top_index]=='('){
                    top_index-=1;
                }
                else if(to_check=='}'&&st[top_index]=='{'){
                    top_index-=1;
                }
                else if(to_check==']'&&st[top_index]=='['){
                    top_index-=1;
                }
                else{
                    return false;
                }
            }
        }
        if(top_index==-1){
            return true;
        }
        return false;
    }
    ~sequece() {
        delete[] st;
    }
};
int main(){
    string se1="([(){[]}])";
    string se2="{{[}]}";
    sequece s1(se1);
    if(s1.solve()){
        cout<<"yes";
    }else{
        cout<<"no";
    }
    cout<<endl;
    sequece s2(se2);
    if(s2.solve()){
        cout<<"yes";
    }else{
        cout<<"no";
    }
    return 0;
}