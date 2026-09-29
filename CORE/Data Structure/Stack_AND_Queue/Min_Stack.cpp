//we can use two stck s1 normal stack s2 our history 
//bundle stack 
#include <iostream>
#include<climits>
#include<stack>
using namespace std;
class minSTACK1{
    private:
    stack<int> s1;//normal
    stack<int> s2;//min history uptill current top stored in s1
    public:
    minSTACK1(){}
    ~minSTACK1(){}
    void push(int val){
        s1.push(val);
        if(s2.empty()||s2.top()>=val){
            s2.push(val);
        }
    }
    void pop(){
        if(s1.empty()){
            cout<<"Empty stack!!!Underflow!!!\n";
            return;
        }
        int top=s1.top();
        s1.pop();
        if(s2.top()==top){
            s2.pop();
        }
    }
    int getmin(){
        if(s1.empty()){
            cout<<"Stack empty!!!\n";
            return INT_MAX;
        }
        return s2.top();
    }
    int top(){
        if(s1.empty()){
            cout<<"Stack empty!!!\n";
            return INT_MAX;
        }
        return s1.top();
    }
};
struct node{//coustom data type 8 bytes
    int value;
    int his_min;
    node(int val,int m){
        value=val;
        his_min=m;
    }
};
class minSTACK2{
    private:
    stack<node> st;
    public:
    minSTACK2(){}
    ~minSTACK2(){}
    void push(int val){
        int hist_m=INT_MAX;
        if(st.empty()){
            hist_m=val;
            st.push(node(val,hist_m));
            return;
        }
        hist_m=st.top().his_min;
        if(val<hist_m){
            hist_m=val;
        }
        st.push(node(val,hist_m));
    }
    void pop(){
        if(st.empty()){
            cout<<"Undeflow!!!\n";
            return;
        }
        st.pop();
    }
    int getmin(){
        if(st.empty()){
            cout<<"Stack empty!!!\n";
            return INT_MAX;
        }
        return st.top().his_min;
    }
    int top(){
        if(st.empty()){
            cout<<"Stack empty!!!\n";
            return INT_MAX;
        }
        return st.top().value;
    }
};
int main() {
    minSTACK1 ms1;
    ms1.push(5);
    ms1.push(2);
    ms1.push(8);
    cout << "Min in ms1: " << ms1.getmin() << endl; // 2
    ms1.pop();
    cout << "Top in ms1: " << ms1.top() << endl;    // 2

    minSTACK2 ms2;
    ms2.push(7);
    ms2.push(3);
    ms2.push(9);
    cout << "Min in ms2: " << ms2.getmin() << endl; // 3
    ms2.pop();
    cout << "Top in ms2: " << ms2.top() << endl;    // 3

    return 0;
}
