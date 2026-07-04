#include<iostream>
#include<climits>
using namespace std;
class CircularQueue{
    //we don't use link list or dynamic array as in it as taking nodes kill the meaning of saving time or fast operation
    //allocating new node or resize a dynamic array takes time by each time requesting OS system 
    //espacially bad when we have to do millions of operation each second 
    //we can both either use stack space for small array size requirement or heap space for larger arry size requirement for static array 
    private:
    int head;
    int tail;
    int capacity;
    int*cq;
    public:
    CircularQueue(int size){
        tail=head=-1;
        capacity=size;
        cq=new int[capacity];//or small we may use stack space int cq[10]
    }
    //we insert at tail/back and delete at head/front
    void enqueue(int val){
        if((tail+1)%capacity==head){
            cout<<"Queue Overflow!!!\n";
            return;
        }
        if(head==-1){
            head=tail=0;
            cq[0]=val;
            return;
        }
        tail=(tail+1)%capacity;
        cq[tail]=val;
    }
    void dequeue(){
        if(head==-1){
            cout<<"Underflow!!!\n";
            return;
        }
        if(head==tail){
            head=tail=-1;
            return;
        }
        head=(head+1)%capacity;
    }
    int front(){
        if(head==-1){
            cout<<"Empty queue!!!\n";
            return INT_MAX;
        }
        return cq[head];
    }
    int back(){
        if(head==-1){
            cout<<"Empty queue!!!\n";
            return INT_MAX;
        }
        return cq[tail];
    }
    bool isEmpty(){
        if(head==-1){
            return true;
        }
        return false;
    }
    bool isfull(){
        if((tail+1)%capacity==head){
            return true;
        }
        return false;
    }
    ~CircularQueue(){//if only use heap memory
        for(int i=0;i<capacity;i++){
            cq[i]=0;
        }
        delete[] cq;
    }
};
int main(){
    CircularQueue q(5);
    q.enqueue(1999);
    q.enqueue(1000);
    q.enqueue(8899);
    q.enqueue(99);
    q.dequeue();
    q.enqueue(777779);
    q.dequeue();
    q.enqueue(111);
    while (!q.isEmpty()) {
        cout << q.front() << "\n";//take care
        q.dequeue();
    }
}