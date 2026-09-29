#include<iostream>
#include<climits>
using namespace std;
struct node{
    int value;
    node*next;
    node(int val){
        value=val;
        next=nullptr;
    }
};
class Queue{
    //not array as they can't be optimized to O(1) and without ay methord to optimize holes or full space without O(n) opertations
    private:
    node*head;
    node*tail;
    public:
    Queue(){
        head=nullptr;//with help of nullptr we can tell when our queue is empty
        tail=nullptr;//Groundwire as well as avoid dangling pointers
    }
    void enqueue(int val){
        node*temp=new node(val);
        if(head==nullptr){
            head=temp;
            tail=temp;
            return;
        }
        tail->next=temp;
        tail=tail->next;
    }
    void dequeue(){
        if(head==nullptr){
            cout<<"Underflow!!!\n";
            return;
        }
        node*temp=head;
        if(head==tail){
            tail=nullptr;
        }
        head=head->next;
        temp->value=0;
        temp->next=nullptr;
        delete temp;
    }
    int front(){
        if(head==nullptr){
            cout<<"Queue is empty!!!\n";
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
    ~Queue(){
        while(head!=nullptr){
            node*temp=head;
            head=head->next;
            temp->value=0;
            temp->next=nullptr;
            delete temp;
        }
        tail=nullptr;//avoid dangling pointer as before this tail still pointed at some unaccessable data
    }
};
int main(){
    Queue q;
    q.enqueue(1999);
    q.enqueue(1000);
    q.enqueue(8899);
    q.dequeue();
    q.enqueue(777779);
    while(!q.isEmpty()){
        cout<<q.front()<<"\n";
        q.dequeue();
    }
}