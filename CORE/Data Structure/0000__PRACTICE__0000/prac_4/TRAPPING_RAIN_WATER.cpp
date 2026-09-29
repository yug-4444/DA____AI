#include<iostream>
#include<vector>
using namespace std;
class Water_Flow{
    public:
    int calculate(vector<int>&height){
        int water=0;
        int n=height.size();
        vector<int>st;
        for(int i=0;i<n;i++){
            while(!st.empty()&&height[i]>height[st.back()]){
                int top=st.back();
                st.pop_back();
                if(st.empty()){
                    break;
                }
                int length=i-st.back()-1;
                int bound_height=min(height[st.back()],height[i])-height[top];
                water+=length*bound_height;
            }
            st.push_back(i);
        }
        return water;
    }
    //2nd methord : The Two-Pointer Convergence
    //Instead of calculating horizontal puddles with O(N) extra memory (The Stack), we are going to calculate vertical columns using absolute O(1)Space.
    int claculation2(vector<int>&input){
        int n=input.size();
        int max_left=0,max_right=n-1;
        int left=max_left,right=max_right;
        int water=0;
        while(left<right){//as boundays don't contribute in water left<=right also fine
            if(input[max_left]<input[max_right]){
                left+=1;
                if(input[left]>=input[max_left]){//since height greter and act as a boundary any water above it will spill out 
                    max_left=left;
                    continue;
                }
                water+=input[max_left]-input[left];
            }else{
                right-=1;
                if(input[right]>=input[max_right]){
                    max_right=right;
                    continue;
                }
                water+=input[max_right]-input[right];
            }
        }
        return water;
    }
};
