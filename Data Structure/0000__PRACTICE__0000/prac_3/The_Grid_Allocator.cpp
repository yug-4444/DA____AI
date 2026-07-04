#include<iostream>
#include <vector>
using namespace std;

class GridAllocator {
    public:
    //findlargest contiguous rectangular block of functional ('1') nodes.
    int maximalRectangle(vector<vector<char>>& matrix) {//input of row*column bytes
        if (matrix.empty()){ 
            return 0;
        }
        int row=matrix.size();
        int column=matrix[0].size();
        vector<int>prev(column,0);
        int max_1s=0;
        for(int i=0;i<row;i++){
            for(int j=0;j<column;j++){
                if(matrix[i][j]=='0'){
                    prev[j]=0;
                }else{
                    prev[j]+=1;
                }
            }//now we have prev according to latest state
            vector<int>st;
            //now we will also have zero columns al well 
            for(int k=0;k<column;k++){
                while(!st.empty()&&prev[st.back()]>prev[k]){
                    int length=prev[st.back()];
                    st.pop_back();
                    int breath=st.empty()?k:(k-st.back()-1);
                    max_1s=max(max_1s,length*breath);
                }
                //By pushing the index of the 0 into the stack, it gave all future columns a solid left boundary to collide against. It prevents columns on the right from illegally bleeding their area calculations into the columns on the left.
                //col of 0 won't have much of effect as lenght is zero and when ever it comes it tries to empty out full stack to the bottom so if zero in middle it is nessesary to push on st so to know at which index 0 comes else error
                st.push_back(k);
            }
            while(!st.empty()){
                int length=prev[st.back()];
                st.pop_back();
                int breath=st.empty()?column:(column-st.back()-1);
                max_1s=max(max_1s,length*breath);
            }
        }
        return max_1s;
    }
};
//O(rowxcolumn) time
//as well as no new space is allocated and vector self destruct after use so no need for destructor