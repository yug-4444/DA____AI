//THE HYDRAULIC PRESSURE (TRAPPING RAIN WATER)
//Constraint 1: $O(N)$ Time.Constraint 2: Absolute $O(1)$ Space (No extra arrays, strictly a Two-Pointer architecture).
#include <vector>
#include <algorithm>
using namespace std;

class CrucibleEngine {
public:
    int trap(vector<int>& height) {
        int n=height.size();
        if(n<=2){
            return 0;
        }
        int water=0;
        int maxleft=0;
        int left=1;
        int maxright=n-1;
        int right=n-2;
        while(left<=right){//case :2,0,3
            if(height[maxleft]<=height[maxright]){
                //we go to left side pointer take care that boundary can't hold water above it will spill
                if(height[left]<height[maxleft]){
                    water+=(height[maxleft]-height[left]);
                }else{
                    maxleft=left;
                }
                left+=1;
            }else{
                if(height[right]<height[maxright]){
                    water+=(height[maxright]-height[right]);
                }else{
                    maxright=right;
                }
                right-=1;
            }
        }
        return water;
    }
};