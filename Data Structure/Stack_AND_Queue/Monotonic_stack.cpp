#include <iostream>
#include<climits>
#include<stack>
using namespace std;
class monotonic{
    private:
    stack<int>st;
    int n;
    int*list;
    int*ans;
    public:
    monotonic(int *arr,int size){//no need for vector or dynamic array as q=size is fixed to tha of input
        list=arr;
        n=size;
        ans=new int[n];
    }
    void solve(){//next greater not to compare with current
        //next means compare to today or current as we travel future or to right the 1st geater than current not future greatest in whole timline
        //if 1st element itself is greatest on list then it hides the full upcoming time line and made it imposible for upcoming elements to use this methord
        //so we traerse from future / right side to past /left side.
        for(int i=n-1;i>=0;i--){
            int curr=list[i];
            while(!st.empty()&&curr>=st.top()){
                st.pop();
            }
            if(st.empty()){
                ans[i]=-1;
            }else{
                ans[i]=st.top();
            }
            st.push(curr);
        }
    }
    void anwser(){
        for(int i=0;i<n;i++){
            cout<<list[i]<<"---->"<<ans[i]<<endl;
        }
    }
    ~monotonic() {
        delete[] ans;
    }
};

int main() {
    int arr[] = {4, 5, 2, 25};
    int len = sizeof(arr) / sizeof(arr[0]);

    monotonic m(arr, len);
    m.solve();
    m.anwser();

    return 0;
}