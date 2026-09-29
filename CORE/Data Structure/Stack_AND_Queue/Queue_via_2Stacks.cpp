#include<iostream>
#include <climits>
#include<stack>
using namespace std;
class QueueEmulator{
    private:
    stack<int> s1;//input stack 
    stack<int> s2;//output stack
    int element_back;
    public:
    QueueEmulator(){
        element_back=0;
    }

    void enqueue(int val){//O(1)
        s1.push(val);
        element_back=val;
    }
    void dequeue(){// Amortized O(1)
        if(s2.empty()){
            //stop and fill all the elemts from s1 to s2 such that order of things remain
            while(!s1.empty()){
                int top=s1.top();
                s1.pop();
                s2.push(top);
            }
            if(s2.empty()){
                cout<<"NO ELEMENTS IN QUEUE!!!SO Underflow!!!\n";
                return;
            }
        }
        s2.pop();
    }
    int front(){// Amortized O(1)
        if(s2.empty()){
            while(!s1.empty()){
                int top=s1.top();
                s1.pop();
                s2.push(top);
            }
            if(s2.empty()){
                cout<<"NO ELEMENTS IN QUEUE!!!\n";
                return INT_MAX;
            }
        }
        return s2.top();
    }
    //int back()// althoug normally Amortized O(1) but if coninous use back and front break this O(1)timeamortized even when we shift with while
    int back(){//keep back() in O(1) time without having to reshuffle stacks
        if(s1.empty()&&s2.empty()){
            return INT_MAX;
        }
        return element_back;
    }
        
    bool isEmpty(){
        if(s1.empty()&&s2.empty()){
            return true;
        }
        return false;
    }
    ~QueueEmulator(){}//they’re objects of type stack<int>. The compiler will automatically clean them up
};
int main(){
    QueueEmulator q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    cout<<q.front()<<endl;
    q.dequeue();
    q.enqueue(40);
    cout<<q.front()<<endl;
    q.dequeue();
    return 0;
}