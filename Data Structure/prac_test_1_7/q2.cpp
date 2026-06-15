struct node{
    int value;
    node*next;
    node(int val){
        value=val;
        next=nullptr;
    }
};
class CrucibleEngine2 {
public:
    void reorderList(node* head) {
        if(head==nullptr||head->next==nullptr||head->next->next==nullptr){
            return;//require atleast 3 elements
        }
        //get to middle
        node*slow=head->next;
        node*fast=head->next->next;
        while(fast!=nullptr&&fast->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
        }
        node*temp=slow;
        slow=slow->next;
        temp->next=nullptr;
        //now we have a seprate list from slow now we need to reverse this second list
        node*prev=nullptr;
        node*curr=slow;
        while(curr!=nullptr){
            node*t1=curr;
            curr=curr->next;
            t1->next=prev;
            prev=t1;
        }
        slow=prev;//reversed
        //now fit in spaces b/w nodes of list one 
        curr=head;
        while(slow!=nullptr){
            node*t1=slow;
            slow=slow->next;
            t1->next=curr->next;
            curr->next=t1;
            curr=t1->next;
        }
    }
};