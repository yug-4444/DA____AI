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
class cycleRemoval{
    private:
    listnode*&head;
    public:
    cycleRemoval(listnode*&h){
        head=h;
    }
    bool cylce_detect_and_removal(){
        if(head->next==nullptr){
            return false;
        }
        if(head->next==head){
            head->next=nullptr;
            return true;
        }
        listnode*fast=head;
        listnode*slow=head;
        while(fast!=nullptr&&fast->next!=nullptr){
            fast=fast->next->next;
            slow=slow->next;
            if(fast==slow){
                break;
            }
        }
        if(fast==nullptr||fast->next==nullptr){
            return false;
        }
        slow=head;
        //by trying to see how nodes distribute around cycle connect point and collision point of fast and slow 
        //it can be seen as we try to move a nodes forward from head and that colloision point then they will meet at the cycle connection point at tail->next not tail will be given 
        while(slow!=fast){
            slow=slow->next;
            fast=fast->next;
        }
        listnode*curr=fast;
        while(curr->next!=fast){
            curr=curr->next;
        }
        curr->next=nullptr;//sever only the rogue wire
        //now cycle is sucessfully removed
        return true;
    }
    void print(){
        listnode*curr=head;
        while(curr!=nullptr){
            cout<<curr->value<<" -> ";
            curr=curr->next;
        }
        cout<<"nullptr"<<endl;
    }
    //no extra memory used so no destructor is required
}