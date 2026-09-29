//3-Pass Interweaving
#include<iostream>
using namespace std;
struct node{
    int value;
    node*next;
    node*random;
    node(int val){
        value=val;
        next=nullptr;
        random=nullptr;
    }
};
class linklistform{
    private:
    node*&head;
    node*clone_head;
    public:
    linklistform(node*&h){
        head=h;
        clone_head=nullptr;
    }
    node*copy(){
        if (!head) {
            return nullptr;
        }
        node*curr=head;
        while(curr!=nullptr){
            node*clone=new node(curr->value);
            clone->next=curr->next;
            curr->next=clone;
            curr=curr->next->next;
        }
        //A->A'->B->B'->C->C'.....
        //We could have also solved it using hash table but consume extra space 
        //now connect random
        curr=head;
        while(curr!=nullptr){
            node*clone=curr->next;
            if(curr->random!=nullptr){
                clone->random=curr->random->next;
            }else{
                clone->random=nullptr;
            }
            curr=clone->next;
        }
        //now also random connected with the required clones
        //now what left is to seperate it from the orignal and remake orignal
        clone_head=head->next;
        curr=head;
        node*clone_curr=clone_head;
        while(curr!=nullptr){
            curr->next=curr->next->next;
            if(clone_curr->next!=nullptr){
                clone_curr->next=clone_curr->next->next;
            }
            curr=curr->next;
            clone_curr=clone_curr->next;
        }
        //now copy clone and orignal are seperated and are not wired to each other in any way
        return clone_head;
    }
};