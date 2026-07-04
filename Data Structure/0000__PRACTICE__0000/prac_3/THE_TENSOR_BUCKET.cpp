#include <vector>
using namespace std;

class MemoryOptimizer {
    private:
    const vector<int>&col;
    public:
    MemoryOptimizer(const vector<int>& heights):
    col(heights){}
    //we can be rest assured given input of col each heght is >=1 as 0 means we are breaking question into two part around the 0 column so 0 column makes no sense
    int largestRectangleArea() {
        int max_area=0;
        vector<int>st;
        int n=col.size();
        for(int i=0;i<n;i++){
            while(!st.empty()&&col[st.back()]>col[i]){
                int length=col[st.back()];
                st.pop_back();
                int breath=st.empty()?i:(i-st.back()-1);
                max_area=max(max_area,length*breath);
            }
            st.push_back(i);
        }
        while(!st.empty()){
            int length=col[st.back()];
            st.pop_back();
            int breath=st.empty()?n:(n-st.back()-1);
            max_area=max(max_area,length*breath);
        }
        return max_area;
    }
};