//DEQUE ---- DOUBLE ENDED QUEUE
#include<iostream>
#include<climits>
using namespace std;
//think of a queue where insertion and deletion at both ends
//array ->problem as O(n) for shift due to holes
//singly link list -> problem at tail delete take O(n) traversal
//Doubly link list ->fits criteria
struct node{
    int value;
    node*next;
    node*prev;
    node(int val){
        value=val;
        next=nullptr;//Grounded wire to avoid dangling pointers
        prev=nullptr;
    }
};
class Deque{
    private:
    node* head;
    node* tail;
    public:
    Deque(){
        head=nullptr;
        tail=nullptr;
    }
    void push_front(int val){
        node*temp=new node(val);
        if(head==nullptr){
            head=tail=temp;
            return;
        }
        temp->next=head;
        head->prev=temp;
        head=temp;
    }
    void push_back(int val){
        node*temp=new node(val);
        if(head==nullptr){
            head=tail=temp;
            return;
        }
        temp->prev=tail;
        tail->next=temp;
        tail=temp;
    }
    void pop_front(){
        if(head==nullptr){
            cout<<"No Elements !!! Underflow!!!\n";
            return;
        }
        if(head==tail){
            tail=nullptr;
        }
        node*temp=head;
        head=head->next;
        if(head!=nullptr){
            head->prev=nullptr;
        }
        temp->next=nullptr;
        temp->value=0;
        delete temp;
    }
    void pop_back(){
        if(head==nullptr){
            cout<<"No Elements !!! Underflow!!!\n";
            return;
        }
        if(head==tail){
            head=nullptr;
        }
        node*temp=tail;
        tail=tail->prev;
        if(tail!=nullptr){
            tail->next=nullptr;
        }
        temp->prev=nullptr;
        temp->value=0;
        delete temp;
    }
    int front(){
        if(head==nullptr){
            cout<<"Empty Deque!!!\n";
            return INT_MAX;
        }
        return head->value;
    }
    int back(){
        if(head==nullptr){
            cout<<"Empty Deque!!!\n";
            return INT_MAX;
        }
        return tail->value;
    }
    bool isEmpty(){
        if(head==nullptr){
            return true;
        }
        return false;
    }
    ~Deque(){
        while (head!=nullptr){
            node*temp=head;
            head=head->next;
            temp->value=0;
            temp->next=nullptr;
            temp->prev=nullptr;
            delete temp;
        }
        tail=nullptr;//to avoid dangling pointer
    }
};
int main(){
    Deque q;
    q.push_back(10);
    q.push_front(20);
    q.push_back(30);
    cout << "Front: " << q.front() << endl;
    cout << "Back: " << q.back() << endl;
    q.pop_front();
    cout << "Front after pop_front: " << q.front() << endl;
    q.pop_back();
    cout << "Back after pop_back: " << q.back() << endl;
    return 0;
}