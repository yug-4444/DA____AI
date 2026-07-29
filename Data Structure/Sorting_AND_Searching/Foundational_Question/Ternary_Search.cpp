#include<iostream>
#include<vector>
#include<functional>
using namespace std;
class TernarySearchEngine{
    private:
    const vector<int>&input;
    int n;
    public:
    TernarySearchEngine(const vector<int>&i):
    input(i),n(input.size()){}
    //valid only for unimodal curves while its will be stricly increasing and then stricly decreasing no pleatue
    //pleatue problem [2,3,4,5,6,6,6,6,6,6,6,6,6,6,6,6,6,9,10,0] this will casuse serious problem with normal approch
    int findPeak(){
        int low=0,high=n-1;
        while(high-low>=3){
            int mid1=low+(high-low)/3,mid2=high-(high-low)/3;
            if(input[mid1]<input[mid2])low=mid1+1;
            else if(input[mid1]>input[mid2])high=mid2-1;
            else low=mid1+1,high=mid2-1;
        }
        int highest=low;
        if(low+1<=high&&input[highest]<input[low+1])highest=low+1;
        if(low+2<=high&&input[highest]<input[low+2])highest=low+2;
        return highest;
    }
    int findValley(){
        int low=0,high=n-1;
        while(high-low>=3){
            int mid1=low+(high-low)/3,mid2=high-(high-low)/3;
            if(input[mid1]>input[mid2])low=mid1+1;
            else if(input[mid1]<input[mid2])high=mid2-1;
            else low=mid1+1,high=mid2-1;
        }
        int smallest=low;
        if(low+1<=high&&input[smallest]>input[low+1])smallest=low+1;
        if(low+2<=high&&input[smallest]>input[low+2])smallest=low+2;
        return smallest;
    }
};
class Ternary_contionus_space{
    public:
    double findpeak(double low,double high,function<double(double)>f,double eps=1e-9){//// Find maximum of unimodal function f in [left, right]
        while(high-low>eps){
            double mid1=low+(high-low)/3.0;
            double mid2=high-(high-low)/3.0;
            if(f(mid1)<f(mid2)){
                low=mid1;
            }else{
                high=mid2;
            }
        }
        return (low+high)/2.0;//approx peak location
    }
    double findvalley(double low,double high,function<double(double)>f,double eps=1e-9){//// Safe alternative: use a fixed loop `for (int i = 0; i < 100; ++i)` to prevent infinite loops
        while(high-low>eps){
            double mid1=low+(high-low)/3.0;
            double mid2=high-(high-low)/3.0;
            if(f(mid1)>f(mid2))low=mid1;
            else high=mid2;
        }
        return (high+low)/2.0;
    }
};