#include<iostream>
#include<deque>
#include<vector>
using namespace std;
class sliding_window{
    private:
    deque<int>dq;//it will store our index in such a way that our signals over that index are in decreasing order since we add our latest signal toward bacck 
    //since it is latest hence it will expire in last so we will eliminate all the no. smaller than this as well as as window slides our required indixes range will shift as well we will always check at front if in range good if not then pop it from front
    int k;
    int n;
    const vector<int> &array;
    vector<int>response;
    public:
    sliding_window(const vector<int>&input,int slide)
    :array(input),k(slide),n(input.size()){}
    vector<int> radarScanner(){
        if(k<=0){//no sliding possible in this case
            return response;
        }
        if(k==1){
            response=array;
            return response;
        }
        //first we will intialize our list till k elements where k>=2

        for(int i=0;i<=k-1;i++){//in initalize we will try to not conserve our elements that are old and less strength
            int now=array[i];
            while(!dq.empty()&&array[dq.back()]<now){
                dq.pop_back();
            }
            dq.push_back(i);//necssary to store indexes so that we can identify our late and early arrivals of various indexs
        }
        response.push_back(array[dq.front()]);

        //initalized first k elements in deque such that they are now in strict decreasing order now we will start from k+1th element i.e from s=1 as s=0 done in initalize
        //when our window becomes full and take the max from front then move till last element of array but each time our range of index shifts keep in mind
        for(int i=k;i<n;i++){
            int s=i-k+1;//range of window set or no. of slides 
            int now=array[i];
            while(!dq.empty()&&array[dq.back()]<now){//dq will never be empty as we have already done initalizing
                dq.pop_back();
            }
            dq.push_back(i);
            while(!dq.empty()&&dq.front()<s){//dq will never become empty due to similar cases
                dq.pop_front();
            }
            response.push_back(array[dq.front()]);
        }

        return response;
    }
    //done in O(n) time not O(nk)
};
int main() {
    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    sliding_window sw(arr, k);
    vector<int> result = sw.radarScanner();

    for (int x : result) cout << x << " ";
    // Output: 3 3 5 5 6 7
}
