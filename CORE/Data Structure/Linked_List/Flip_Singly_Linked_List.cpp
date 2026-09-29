//physically flip the arrows of a Singly Linked List without breaking the chain or causing a memory leak
//You must do it in-place. You are not allowed to ask the Heap for any new nodes. You are not allowed to change the integers inside the nodes

#include<iostream>
using namespace std;
struct node{
    int value;
    node*next;
    node(int val){
        value=val;
        next=nullptr;
    }
};
//valid under the “in-place, O(1) extra space” rule.
void flipSLL(node*&head){//1st think about reversing
    if(head==nullptr){
        cout<<"empty list \n";
        return;
    }
    node*tail=head;
    while(tail->next!=nullptr){
        tail=tail->next;
    }
    node*ptr=head;
    while(ptr!=tail){
        node*temp=ptr;
        ptr=ptr->next;
        temp->next=tail->next;
        tail->next=temp;
    }
    head=tail;
}
void reverse3pointer(node*&head){//more optimized and it’s elegant, efficient, and demonstrates mastery of the standard reversal pattern.
    node*prev=nullptr;
    node*curr=head;
    node*next=nullptr;
    while(curr!=nullptr){
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    head=prev;
}
void insertAtHead(node*&head ,int val){
    node*n1=new node(val);
    n1->next=head;
    head=n1;
}
void display(node*head){
    if(head==nullptr){
        cout<<"Empty list\n";
        return;
    }
    node*temp=head;
    while(temp!=nullptr){
        cout<<temp->value<<"->";
        temp=temp->next;
    }
    cout<<"nullptr\n";
}
void clear(node*&head){
    node*current=head;
    while(current!=nullptr){
        node*temp=current;
        current=current->next;
        delete temp;
    }
    head=nullptr;
}
int main(){
    node*head=nullptr;
    insertAtHead(head,50);
    insertAtHead(head,40);
    insertAtHead(head,30);
    insertAtHead(head,20);
    insertAtHead(head,10);
    display(head);
    flipSLL(head);
    display(head);
    reverse3pointer(head);
    display(head);
    return 0;
}