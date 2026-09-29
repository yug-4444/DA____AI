#include<iostream>
using namespace std;
struct node{
    int value;
    node*next;
    node*random;
    node(int val){
        value=val;
        next=random=nullptr;
    }
};
class clone{
    private:
    node*&head;
    node*clone_head;
    public:
    clone(node*&h){
        head=h;
        clone_head=nullptr;
    }
    node* process(){
        node*curr=head;
        while(curr!=nullptr){
            node*temp=new node(curr->value);
            temp->next=curr->next;
            curr->next=temp;
            curr=curr->next->next;
        }
        clone_head=head->next;
        curr=head;
        while(curr!=nullptr){
            node*nclone=curr->next;
            if(curr->random!=nullptr){
                nclone->random=curr->random->next;
            }else{
                nclone->random=nullptr;
            }
            curr=nclone->next;
        }
        curr=head;
        while(curr!=nullptr){
            node*nclone=curr->next;
            curr->next=nclone->next;
            if(nclone->next!=nullptr){
                nclone->next=nclone->next->next;
            }
            curr=curr->next;
        }
        return clone_head;
    }
};