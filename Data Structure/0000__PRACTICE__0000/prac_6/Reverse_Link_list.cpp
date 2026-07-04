#include<iosteam>
using namespace std;
struct node{
    int value;
    node*next;
    node(int val){
        value=val;
    }
};
class linklistrev{
    private:
    node*&head;
    public:
    linklistrev(node*&h):
    head(h){}
    void reverse(){//O(n)
        //it handles case when head=nullptr or head->next=nullptr case as well as perfectly
        if(head==nullptr){
            return;
        }
        node*prev=nullptr;
        node*curr=head;
        while(curr!=nullptr){
            node*temp=curr;
            curr=curr->next;
            temp->next=prev;
            prev=temp;
        }
        head=prev;
    }
    void reverse2(){//O(2n)---O(n)
        if(head==nullptr){
            return;
        }
        node*temp=head;
        while(temp->next!=nullptr){
            temp=temp->next;
        }
        node*tail=temp;
        node*curr=head;
        while(curr!=tail){
            node*t=curr;
            curr=curr->next;
            t->next=tail->next;
            tail->next=t;
        }
        head=tail;
    }
};
