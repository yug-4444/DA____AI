#include<iostream>
using namespace std;
struct node{
    int value;
    node*next;
    node(int val){
        value=val;
        next=nullptr;//avoid dangling pointer
    }
};
class cycle_detecte{
    private:
    node*&head;
    public:
    cycle_detecte(node*&h):
    head(h){}
    bool detect(){
        if(head==nullptr||head->next==nullptr){
            return false;
        }
        node*slow=head->next;
        node*fast=head->next->next;
        while(fast!=nullptr&&fast->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
            if(fast==slow){
                return true;
            }
        }
        return false;
    }
    void cycle_removal(){
        //cycle has to exist
        node*slow=head->next;
        node*fast=head->next->next;
        while(fast!=slow){
            slow=slow->next;
            fast=fast->next->next;
        }
        slow=head;
        if(slow==fast){//full perfect cycle detect !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            while(fast->next!=slow){
                fast=fast->next;
            }
        }
        else{
            while(slow->next!=fast->next){
                slow=slow->next;
                fast=fast->next;
            }
        }
        fast->next=nullptr;
    }
}