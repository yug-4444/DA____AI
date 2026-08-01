//open Addressing ->closed hashing i.e it means no distributed memory
//we have linear probing
#include<iostream>
#include<vector>
#include<climits>
#include<functional>
using namespace std;
class LinearProbing{
    private:
    float bottleneck;
    int current,size;
    vector<int>array;
    hash<int>h;
    public:
    //INT_MAX ->empty , INT_MIN ->deleted tombstone
    LinearProbing(int n):
    size(n){
        array.resize(n,INT_MAX);//INT_MAX means that empty
        bottleneck=0.75;//when alpha>=0.75 resize and rehash all elements and alpha=current/size
        current=0;
    }
    //resize,insert,delete,find 
    void resize(){
        size*=2;
        vector<int>copy=array;
        array.assign(size,INT_MAX);//remake prev array elemnts reinitialize else in resize they remain same
        for(int i=0;i<size/2;i++){
            int key=copy[i];
            if(key!=INT_MAX&&key!=INT_MIN){
                int index=h(key)%size;
                while(array[index]!=INT_MAX){
                    index=(index+1)%size;
                }
                array[index]=key;
            }
        }
    }
    void ht_insert(int key){
        int index=(h(key))%size;
        //when we have resize at bottleneck that means that we will always find a index available to be filled with key
        while(array[index]!=INT_MAX&&array[index]!=INT_MIN){
            index=(index+1)%size;
        }
        array[index]=key;
        current+=1;
        if((float)current/size>=bottleneck)resize();
    }
    void ht_delete(int key){
        int index=(h(key))%size;
        while(array[index]!=INT_MAX){
            if(array[index]==key){
                current-=1;
                array[index]=INT_MIN;
                return;
            }
            index=(index+1)%size;
        }
    }
    int find(int key){
        int index=(h(key))%size;
        while(array[index]!=INT_MAX){
            if(array[index]==key)return index;
            index=(index+1)%size;
        }
        return -1;//not found
    }
};