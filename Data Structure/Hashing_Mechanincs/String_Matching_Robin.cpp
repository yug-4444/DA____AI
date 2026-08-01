#include<iostream>
#include<string>
#include<vector>
using namespace std;
class StringMatching{
    public:
    pair<int,vector<int>>robin(string&input,string&target){//window size also needs to be of target size
        int L=target.size(),n=input.size();
        if(L > n) return {0, {}};
        vector<int>list;
        int count=0,P=53;
        long long hash_target=0,hash_window=0,M=1000000007;
        vector<long long>powers(L);
        powers[0]=1;
        for(int i=1;i<L;i++)powers[i]=(powers[i-1]*P)%M;
        for(int i=0;i<L;i++){
            hash_target=(hash_target+(target[i]-'a'+1)*powers[L-i-1]%M)%M;//we need to add 1 so that 'a' ,'aaaaa' , 'aaaaaaaaaa' are not identified as same making a=1,b=2,c=3,d=4...........
            hash_window=(hash_window+(input[i]-'a'+1)*powers[L-i-1]%M)%M;
        }
        hash_target=hash_target%M;
        hash_window=hash_window%M;
        if(hash_target==hash_window){
            bool match=true;
            for(int i=0;i<L;i++){
                if(target[i]!=input[i]){
                    match=false;
                    break;
                }
            }
            if(match){
                count+=1;
                list.push_back(0);
            }
        }
        for(int i=L;i<n;i++){
            hash_window=(hash_window-(input[i-L]-'a'+1)*powers[L-1])%M;
            if (hash_window<0)hash_window=(hash_window+M)%M;
            hash_window=(hash_window*P%M+(input[i]-'a'+1))%M;
            if(hash_window==hash_target){
                bool match=true;
                for(int j=0;j<L;j++){
                    if(target[j]!=input[i-L+1+j]){
                        match=false;
                        break;
                    }
                }
                if(match){
                    count+=1;
                    list.push_back(i-L+1);
                }
            }
        }
        return {count,list};
    }
};