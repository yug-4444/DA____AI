//absolute minimum number of intervals to delete so that the remaining timeline is completely clash-free.#include <vector>
#include<vector>
#include <algorithm>
using namespace std;
//we want maximum no. of non overlapp interval or minimize no. of deletions
class GreedyScheduler {
public:
void sort_by_finish(vector<vector<int>>& interval){
    sort(interval.begin(),interval.end(),[](const vector<int>&a,const vector<int>&b){
            return a[1]<b[1]
        });
}
    pair<int,vector<vector<int>>> eraseOverlapIntervals(vector<vector<int>>& inter) {
        vector<vector<int>>interval=inter;
        sort_by_finish(interval);//O(nlogn)
        int n=interval.size();
        vector<vector<int>>output;
        vector<vector<int>>todel;
        //if incoming don't overlapp with the already existing time interval then vail else required to be deleted
        for(int i=0;i<n;i++){
            vector<int>curr=interval[i];
            if(!output.empty()&&output.back()[1]>=curr[0]&&curr[1]>=output.back()[0]){
                //condition :engulfing another or overlap from right side as finisgh time has to be greater or equal to prev
                //but it doesn't matter that much simply use universal overlapping condition
                todel.push_back(curr);
            }
            else{
                output.push_back(curr);
            }//ensures our time order of finish is maintained
        }
        return {todel.size(),todel};
    }
    pair<int,vector<vector<int>>> eraseOverlapIntervals2(vector<vector<int>>& inter) {
        vector<vector<int>>interval=inter;
        sort_by_finish(interval);//O(nlogn)
        int n=interval.size();
        vector<int>prev;
        vector<vector<int>>todel;
        //if incoming don't overlapp with the already existing time interval then vail else required to be deleted
        for(int i=0;i<n;i++){
            vector<int>curr=interval[i];
            if(!prev.empty()&&prev[1]>curr[0]){//even when equal its valid as not collision 
                //condition :engulfing another or overlap from right side as finisgh time has to be greater or equal to prev
                todel.push_back(curr);
            }
            else{
                prev=curr;
            }//ensures our time order of finish is maintained
        }
        return {todel.size(),todel};
    }
};