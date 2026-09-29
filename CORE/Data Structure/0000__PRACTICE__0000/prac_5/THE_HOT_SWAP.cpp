#include <vector>
#include <algorithm>
using namespace std;

class HotSwapEngine {
public:
    vector<vector<int>> insert(vector<vector<int>>& interval, vector<int>& newInterval) {
        vector<vector<int>>output;
        int n=interval.size();
        //lets consider our interval is not sorted
        //considering intreval is alredy in nonoverlapping form
        vector<int>ni=newInterval;
        for(int i=0;i<n;i++){
            vector<int>ci=interval[i];
            if(ci[1]>=ni[0]&&ni[1]>=ci[0]){//with this condition it doesn't matter wheather our ni is intersecting ci from front or from behind it handles both cases
                ni[0]=min(ni[0],ci[0]);
                ni[1]=max(ni[1],ci[1]);
            }else{
                output.push_back(ci);
            }
        }
        output.push_back(ni);
        return output;
        //O(n)time complexity
    }
     vector<vector<int>> insert2(vector<vector<int>>& interval, vector<int>& newInterval) {
        vector<vector<int>>output;
        int n=interval.size();
        //lets consider our interval is  sorted
        //considering intreval is alredy in nonoverlapping form
        vector<int>ni=newInterval;
        int i=0;
        while(i<n&&interval[i][1]<ni[0]){
            output.push_back(interval[i]);
            i++;
        }
        //pure Universal Overlap Theorem
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        while(i<n&&interval[i][1]>=ni[0]&&interval[i][0]<=ni[1]){//this condition is a  universal condition to which it doesn't matter from where intervals overlapp or engulf just check if they overlapp in any way
            ni[0]=min(interval[i][0],ni[0]);
            ni[1]=max(interval[i][1],ni[1]);
            i++;
        }
        output.push_back(ni);
        while(i<n){
            output.push_back(interval[i]);
            i++;
        }
        return output;
     }
};