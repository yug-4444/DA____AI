#include<iostream>
using namespace std;
struct listnode{
    int value;
    listnode*next;
    listnode(int val){
        value=val;
        next=nullptr;
    }
};
class reform{
    private:
    listnode*&head;
    listnode*reinsert;
    public:
    reform(listnode*&h){
        head=h;
        reinsert=nullptr;
    }
    listnode* middle_and_reverse_and_rearrange(){//assume more than 2 nodes
        if(head==nullptr||head->next==nullptr||head->next->next==nullptr){
            return head;
        }
        listnode*slow=head;
        listnode*fast=head;
        while(fast->next!=nullptr&&fast->next->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
        }
        //now break from slow->next
        reinsert=slow->next;
        slow->next=nullptr;
        //l0->l1->l2->l3->l4->l5->l6->nullptr   7 total
        //at l3 slow stops now we will consider two seprate linklists l0->l1->l2->l3->nullptr and l4->l5->l6->nullptr
        //reverse seprated list l6->l5->l4->nullptr and then start inserting in middle b/w each pair of 1st list then completed
        //stuffing
        //reverse our reinsert
        listnode*prev=nullptr;
        listnode*curr=reinsert;
        while(reinsert!=nullptr){
            reinsert=reinsert->next;
            curr->next=prev;
            prev=curr;
            curr=reinsert;
        }
        reinsert=prev;
        //now reversed
        //now we will insert
        listnode*temp=head;
        while(reinsert!=nullptr){
            listnode*ins=reinsert;
            reinsert=reinsert->next;
            ins->next=temp->next;
            temp->next=ins;
            temp=temp->next->next;
        }
        return head;
    }
    void print(){
        listnode*temp=head;
        while(temp!=nullptr){
            cout<<temp->value<<" -> ";
            temp=temp->next;
        }
        cout<<"nullptr"<<endl;
    }
    //no need for destructor as no new space was asked from head
};