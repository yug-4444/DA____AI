#include<iostream>
#include<queue>
#include<climits>
using namespace std;
class MedianFinder {
    private:
    priority_queue<int>left_half;//defauly max heap
    int lcount;
    priority_queue<int,vector<int>,greater<int>>right_half;//min heap
    int rcount;
    public:
    MedianFinder() {
        lcount=rcount=0;
    }
    //make sure lcount is equal or 1 greater tha rcount
    void addNum(int num) {
        left_half.push(num);
        lcount+=1;
        if(lcount==rcount||lcount==rcount+1){
            if(right_half.empty()||left_half.top()<right_half.top()){
                return;
            }
            int shi=right_half.top();
            right_half.pop();
            right_half.push(left_half.top());
            left_half.pop();
            left_half.push(shi);
            return;
            
        }
        //lcount have 1 extra element than the required
        int shift=left_half.top();//max will go so that sort balance remains
        left_half.pop();//left half can't become empty will have atleast 1 element even after pop
        lcount-=1;
        right_half.push(shift);
        rcount+=1;
    }
    double findMedian() {
        if(lcount==0){
            return INT_MAX;
        }
        else if(lcount==rcount+1){
            return left_half.top();
        }else{
            return (right_half.top()+left_half.top())/2.0;
        }
    }
};
class Medianfind{
    private:
    //queues self destruct after function/object is done so no need for destructor
    priority_queue<int>lower;
    priority_queue<int,vector<int>,greater<int>>upper;
    public:
    Medianfind(){}
    void addnum(int val){
        lower.push(val);//just simple enter into lower half
        //check
        if(!upper.empty()&&lower.top()>upper.top()){
            int swi=upper.top();
            upper.pop();
            upper.push(lower.top());
            lower.pop();
            lower.push(swi);
            //now all elements of lower <= all elements of upper if upper exists
        }
        if(lower.size()==upper.size()||lower.size()==upper.size()+1){
            return;
        }else{//as well as right half count can never be greater than lower half count as every element pass through lower half
            int move=lower.top();
            lower.pop();
            upper.push(move);
        }

    }
    double findMedian(){
        if(lower.size()==0){
            return INT_MAX;
        }else if(lower.size()==upper.size()+1){
            return lower.top();
        }else{
            return (lower.top()+upper.top())/2.0;
        }
    }
};
class Medianfind3{//it will be the best optimal solution up till now as both methords used till now we have used many if statements as the  no. of if statements increases the cpu till also increases that is not optimal
    //so best would be if time complexity manatian and no. of if statements decreases
    private:
    priority_queue<int>lower;
    priority_queue<int,vector<int>,greater<int>>upper;
    public:
    Medianfind3(){}
    void addnum(int val){
        //blindless push in lower half and then shift the top to the upper half
        lower.push(val);
        upper.push(lower.top());
        lower.pop();
        //we can be rest essure that the elemnts on leftside less than or equal rightside
        if(lower.size()<upper.size()){
            lower.push(upper.top());
            upper.pop();
        }
    }
    double findMedian(){
        if(lower.size()==0){
            return INT_MAX;
        }else if(lower.size()==upper.size()+1){
            return lower.top();
        }else{
            return (lower.top()+upper.top())/2.0;
        }
    }
}