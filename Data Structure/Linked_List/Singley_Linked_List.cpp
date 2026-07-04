#include<iostream>
using namespace std;

struct node{ //coustom data type that holds the int and pointer to next node(not int) as in scattered memory
    int value;   //4 bytes
    node*next; //64 bits or 8 bytes for 64 bit system

    //construct
    node(int a){
        value=a;
        next=nullptr;
    }
};
void insertAtHead(node*&head ,int val){ // we used refrence operator & so that change in head in reflected back in our main head that we used in parmeter to the function
    node*n1=new node(val);
    n1->next=head;
    head=n1;//O(1)
}
void insertAtTail(node*&head,int val){// we used & only for one case in which head will be nullptr else head don't change
    node*n1=new node(val);
    if(head==nullptr){
        head=n1;
        return;//O(1)
    }
    node*temp=head;
    while(temp->next!=nullptr){
        temp=temp->next;
    }
    temp->next=n1;//O(n)
}
void insertAtPosition(node*&head,int val,int pos){//assume head at 0 position
    if(pos < 0) {
        cout << "Invalid position\n";
        return;
    }
    if(head==nullptr || pos==0){
        insertAtHead(head, val);
        return;
    }
    node*n1=new node(val);
    node*temp=head;
    for(int i=0;i<pos-1;i++){
        temp=temp->next;
        if(temp==nullptr){
            cout<<"out of link list chain so this position is not possible\n";
            return;
        }
    }
    n1->next=temp->next;
    temp->next=n1;
}
void deleteAtPosition(node*&head,int pos){
    if(head==nullptr){
        cout<<"no list available so can't delete \n";
        return;
    }
    if(pos==0){
        node*todelete=head;;
        head=head->next;
        delete todelete;
        return;
    }
    node*temp=head;
    for(int i=0;i<pos-1;i++){
        temp=temp->next;
        if(temp->next==nullptr){
            cout<<"out of link list chain so this position is not possible\n";
            return;
        }
    }
    if(temp->next==nullptr){ // THE GHOST NODE SHIELD required if loop never come in play mean we only have 1 node that is head and pos to delete is 1
        cout<<"out of link list chain so this position is not possible\n";
        return;
    }
    node*todelete=temp->next;
    temp->next=temp->next->next;
    delete todelete;
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
void clear(node*&head){//& to avoid dangling pointer and resets head to nullptr
    node*current=head;
    while(current!=nullptr){
        node*temp=current;
        current=current->next;
        delete temp;
    }
    head=nullptr;//else segmentation falut may arise if head is tried to access again for that first node address
    //explicitly required so that we don't have dangling pointer as delete only frees up memory but the head pointer 
    //still points at deleted node1 address which is no longer in page table hence segmentation fault may occur so 
    //require head to be nullptr
}
int main(){
    node*ptr1=new node(10);
    node*ptr2=new node(20);
    ptr1->next=ptr2;
    node*ptr3=new node(30);
    ptr2->next=ptr3;

    node*ptr=ptr1;
    while(ptr!=nullptr){
        cout<<ptr->value<<"->";
        ptr=ptr->next; 
    }
    cout<<"nullptr\n";
    ptr=ptr1;
    while(ptr!=nullptr){
        node*temp=ptr;
        ptr=ptr->next;
        delete temp;
    }

    node*head=nullptr;
    insertAtHead(head,30);
    insertAtHead(head,20);
    insertAtHead(head,10);
    
    display(head);
    clear(head);


    node*head1=nullptr;
    insertAtTail(head1,10);
    insertAtTail(head1,20);
    insertAtTail(head1,30);

    display(head1);
    clear(head1);
    

    node*head2=nullptr;
    insertAtHead(head2,40);
    insertAtHead(head2,20);
    insertAtHead(head2,10);
    insertAtPosition(head2,30,2);

    display(head2);
    clear(head2);


    node*head3=nullptr;
    insertAtHead(head3,40);
    insertAtHead(head3,30);
    insertAtHead(head3,20);
    insertAtHead(head3,10);
    deleteAtPosition(head3,2);

    display(head3);
    clear(head3);
    return 0;

}