#include<iostream>
using namespace std;
struct node{//20 bytes coustom data type
    int value;//4 bytes
    node*next;//8 bytes
    node*prev;//8 bytes
    //constructor
    node(int val){
        value=val;
        next=nullptr;// Ground the forward wire
        prev=nullptr;// Ground the backward wire
    }
};
void insertDLL(node*&head,int val=0,int pos=0){//head pos 0
    node*n1=new node(val);
    if(head==nullptr ||pos==0){
        n1->next=head;
        if(head!=nullptr){
            head->prev=n1;
        }
        head=n1;
        return;
    }   
    node*temp=head;
    for(int i=0;i<pos-1;i++){
        temp=temp->next;
        if(temp==nullptr){
            cout<<"out of dll chain.\n";
            delete n1;// !!!!!!avoid memory leak
            return;
        }
    }
    n1->next=temp->next;
    n1->prev=temp;
    temp->next=n1;
    if(n1->next!=nullptr){
        n1->next->prev=n1;//tail edge case
    }
    //4 pointer to change 
}
void deleteDLL(node*&head,int pos){
    if(head==nullptr){
        cout<<"Empty list so no delete availabe,\n";
        return;
    }
    if(pos==0){//head case
        node*temp=head;
        head=head->next;
        if(head!=nullptr){
            head->prev=nullptr;//only head
        }
        temp->next=nullptr;
        delete temp;
        return;
    }
    node*temp=head;
    for(int i=0;i<pos;i++){
        temp=temp->next;
        if(temp==nullptr){
            cout<<"out of chain delete not possible.\n";
            return;
        }
    }
    temp->prev->next=temp->next;
    if(temp->next!=nullptr){//tail case
        temp->next->prev=temp->prev;
    }
    temp->next=nullptr;//so that from freed we can know info about chain nodes location
    temp->prev=nullptr;//severed the dying node's connections to the living chain before handing it back to the Operating System
    delete temp;//to avoid memory leaks

}
void display_forward(node*head){
    if(head==nullptr){
        cout<<"Empty list.\n";
        return;
    }
    node*temp=head;
    while(temp!=nullptr){
        cout<<temp->value<<"->";
        temp=temp->next;
    }
    cout<<"nullptr\n";
}
void display_backward(node*head){
    if(head==nullptr){
        cout<<"Empty list.\n";
        return;
    }
    node*temp=head;
    while(temp->next!=nullptr){
        temp=temp->next;
    }
    while(temp!=nullptr){
        cout<<temp->value<<"->";
        temp=temp->prev;
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
    head=nullptr;//avoid dangling pointer
}
int main(){
    node*head=nullptr;
    insertDLL(head);
    insertDLL(head,2);
    display_forward(head);
    display_backward(head);
    clear(head);

    cout<<endl;
    insertDLL(head,40);
    insertDLL(head,30);
    insertDLL(head,20);
    insertDLL(head,10);
    display_forward(head);
    deleteDLL(head,2);
    display_forward(head);
    display_backward(head);
    clear(head);
    return 0;
}