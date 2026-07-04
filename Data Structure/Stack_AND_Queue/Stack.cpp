#include<iostream>
#include<climits>
using namespace std;
class static_array_STACK{
    private:
    int capacity;
    int topindex;
    int st[1000];
    public:
    static_array_STACK(int size){
        capacity=size;//limit of stack we required to be
        topindex=-1;// // Grounding wire: empty stack
    }
    void push(int val){
        if(topindex==capacity-1){
            cout<<"Stack Overflow\n";
            return;
        }
        topindex+=1;
        st[topindex]=val;
    }
    void pop(){
        if(topindex==-1){
            cout<<"Stack Underflow\n";
            return ;
        }
        topindex-=1;
    }
    int top(){
        if(topindex==-1){
            cout<<"!!!empty stack!!!\n";
            return INT_MAX;
        }
        return st[topindex];
    }
    bool isEmpty(){
        if(topindex==-1){
            return true;
        }
        return false;
    }
};
struct node{
    int value;
    node*next;
    node(int val){
        value=val;
        next=nullptr;//grounded wire to avoid segmentation fault
    }
};
class Infinite_Stack{//stack is one which use O(1) operations for both insertion and deletion while remaining in protected shell 
    //rule LIFO
    private:
    node*head;//top
    public:
    Infinite_Stack(){
        head=nullptr;//grounded wire to avoid segmentation fault
    }
    void push(int val){
        node*temp=new node(val);
        temp->next=head;
        head=temp;
    }
    void pop(){
        if(head==nullptr){
            cout<<"Stack Underflow!!!\n";
            return;
        }
        node*temp=head;
        head=head->next;
        temp->value=0;
        temp->next=nullptr;
        delete temp;
    }
    int top(){
        if(head==nullptr){
            cout<<"Empty stack";
            return INT_MAX;
        }
        return head->value;
    }
    bool isEmpty(){
        if(head==nullptr){
            return true;
        }
        return false;
    }
    ~Infinite_Stack(){
        while(head!=nullptr){
            node*temp=head;
            head=head->next;
            temp->value=0;
            temp->next=nullptr;
            delete temp;
        }
    }
};

int main(){
    Infinite_Stack myStack;
    myStack.push(20);
    myStack.push(199999);
    myStack.pop();
    myStack.push(222);
    while(!myStack.isEmpty()){
        cout<<myStack.top()<<endl;
        myStack.pop();
    }
    return 0;
}