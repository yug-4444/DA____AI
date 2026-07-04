//Floyd's Cycle-Finding Algorithm
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
bool cycle_Detect(node*head){
    if(head==nullptr){
        cout<<"empty list so no cycle\n";
        return false;
    }
    //two pointer at different speed
    //if no cycle then fast will win i.e reach the end and no cycle
    //if cycle then at some step faster one will come face to face with slower one hence showing presence of cycle
    node*slow=head;
    node*fast=head;
    while(fast!=nullptr && fast->next!=nullptr){//fast->next later in condition as it might not even exist if fast becomes nullptr 
        slow=slow->next;
        fast=fast->next->next;
        if (slow==fast){
            return true;
        }
    }
    return false;
}
int main() {
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);

    // Create a cycle: 4 -> 2
    head->next->next->next->next = head->next;

    if (cycle_Detect(head)) {
        cout << "Cycle detected!\n";
    } else {
        cout << "No cycle.\n";
    }
}