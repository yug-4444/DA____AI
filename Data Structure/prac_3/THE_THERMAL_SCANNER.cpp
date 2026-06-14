#include<iostream>
#include<stack>
#include<vector>
using namespace std;
class next_temp_increase{
    //if manual check for each index we will have to iterate each time O(n^2)
    //but using a stack to store temprateures day index such that it mantain decreasing order
    //i.e when ever higher temprature appear than top we will know it is top ans and may also be belows anwser till lesser than top and then push again ----O(n)
    private:
    const vector<int>&record;
    vector<int> display;
    public:
    next_temp_increase(const vector<int>&temp):
    record(temp),display(temp.size(),0){}
    vector<int> process(){
        stack<int>st;//store indexes of temp days
        for(int i=0;i<record.size();i++){
                while(!st.empty()&&record[st.top()]<record[i]){
                    display[st.top()]=i-st.top();
                    st.pop();
                }
                st.push(i);
            }
        return display;
    }
};
int main() {
    vector<int> temps = {73, 74, 75, 71, 69, 72, 76, 73};
    next_temp_increase solver(temps);
    vector<int> ans = solver.process();

    for (int x : ans) cout << x << " ";
    // Output: 1 1 4 2 1 1 0 0
}