#include <unordered_map>
#include <vector>
#include<climits>
#include<random>
#include<iostream>
using namespace std;

class RandomizedSet {
    //hash map ---O(1) for insert and delete
    //vector good for random ---O(1)
    unordered_map<int,int>present;//store value:index
    int n;
    vector<int>store;//store value
public:
    RandomizedSet() {
        n=-1;//index in vector 
    }
    
    bool insert(int val) {
        if(!present.empty()&&present.find(val)!=present.end()){//O(1) average case
            return false;
        }
        n+=1;
        store.push_back(val);//amortized O(1)
        present[val]=n;//O(1)
        return true;
        //hence totaly O(1)
    }
    
    bool remove(int val) {
        if(present.empty()||present.find(val)==present.end()){//O(1)
            return false;
        }
        int index=present[val];
        present.erase(val);//O(1)
        //now in vector a hole will be created we need to patch it ,keep in mind order of things are not impotant 
        //what important is info about there indexes stored in the hash map
        if(index==n){
            store.pop_back();//O(1)
        }else{//now atleast 2 elements 
            store[index]=store.back();
            present[store.back()]=index;//store.back() will definatly be present in our present pool
            store.pop_back();//O(1)
        }
        n-=1;
        return true;
        //O(1) achived along with O(1) in patching hole
    }
    
    int getRandom() {
        if(n==-1){
            return INT_MIN;
        }
        //range :[0,n]
        random_device rd;//ensures a different seed each run (unlike srand(time(0)) which can repeat if run quickly).
        mt19937 gen(rd()); // Mersenne Twister engine seeded with rd()
        // Uniform distribution in [low, high]
        uniform_int_distribution<> dist(0,n);
        // Generate random number
        int r = dist(gen);//O(1) time
        return store[r];
    }
    // now O(1) in insert ,delete along with hole patch and get random in direct O(1) time
};