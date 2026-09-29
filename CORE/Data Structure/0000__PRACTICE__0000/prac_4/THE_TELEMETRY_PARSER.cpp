#include<iostream>
#include<vector>
#include<climits>
#include<string>
#include<unordered_map>
using namespace std;
class NetworkSwitch {
public:
    string minWindow(string stream, string target) {
        int n=stream.size();
        int m=target.size();
        if(n==0||m==0||m>n){
            return "";
        }
        unordered_map<char,int>target_map;
        for(int i=0;i<m;i++){
                target_map[target[i]]+=1;//if don't exist then automaticall adds it then default value 0 then increment by 1
            }
        int unique=target_map.size();
        int count_uniq=0;
        unordered_map<char,int>window;
        int right=0;
        int left=0;
        int min_left=-1;
        int min_length=INT_MAX;
        while(right<n){//enlongate
            char curr=stream[right];
            if(target_map.count(curr)){
                window[curr]+=1;
            }
            if(target_map.count(curr)&&window[curr]==target_map[curr]){
                count_uniq+=1;
            }
            // Trigger: We have a mathematically valid window. Time to trim the fat.
            while(left<=right&&unique==count_uniq){//compress
                curr=stream[left];
                if(target_map.count(curr)){
                    window[curr]-=1;
                    // If dropping this byte broke our target requirement, the window is dead.
                    // We drop the 'formed' count, which breaks the while loop and forces Expansion to resume.
                    if(target_map[curr]>window[curr]){
                        count_uniq-=1;
                        int length=right-left+1;
                        if(length<min_length){
                            min_length=length;
                            min_left=left;
                        }
                    }
                }
                left+=1;
            }
            right+=1;
        }
        return min_length==INT_MAX?"":stream.substr(min_left,min_length);
    }
};
class NetworkSwitch1 {
public:
    string minWindow(string stream, string target) {
        int n=stream.size();
        int m=target.size();
        if(n==0||m==0||m>n){
            return "";
        }
        unordered_map<char,int>target_map;
        for(int i=0;i<m;i++){
                target_map[target[i]]+=1;//if don't exist then automaticall adds it then default value 0 then increment by 1
            }
        int unique=target_map.size();
        int count_uniq=0;
        unordered_map<char,int>window;
        int right=0;
        int left=0;
        int min_left=-1;
        int min_length=INT_MAX;
        while(right<n){//enlongate
            char curr=stream[right];
            if(target_map.count(curr)){
                window[curr]+=1;
            }
            if(target_map.count(curr)&&window[curr]==target_map[curr]){
                count_uniq+=1;
            }
            // Trigger: We have a mathematically valid window. Time to trim the fat.
            while(left<=right&&unique==count_uniq){//compress
                curr=stream[left];
                int length=right-left+1;
                if(length<min_length){
                    min_length=length;
                    min_left=left;
                }
                if(target_map.count(curr)){
                    window[curr]-=1;
                    // If dropping this byte broke our target requirement, the window is dead.
                    // We drop the 'formed' count, which breaks the while loop and forces Expansion to resume.
                    if(target_map[curr]>window[curr]){
                        count_uniq-=1;
                    }
               }
                left+=1;
            }
            right+=1;
        }
        return min_length==INT_MAX?"":stream.substr(min_left,min_length);
    }
};