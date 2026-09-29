//Given a massive array of n = 10^5 integers and a target value,
// find if there are two numbers in the array that add up to the target.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
int main(){
    int n=100000;
    int*ptr=new int[n];//allocate memory in heap
    //not use int ptr[n] as OS may have thrown STACK OVERFLOW ERROR
    srand(time(0));
    for(int i=0;i<n;i++){
        ptr[i]=rand()%(100*n);
    }
    int target =rand()%(500*n);
    sort(ptr,ptr+n);  //O(nlogn)
    int i=0,j=n-1;
    bool found=false;
    while(i<j){   //O(n)
        int sum=ptr[i]+ptr[j];
        if(sum==target){
            found=true;
            cout<<"find at :("<<i<<","<<j<<") where target ="<<target<<" and ( "<<ptr[i]<<" + "<<ptr[j]<<" ).";
            break;
        }
        else if(sum<target)i++;
        else j--;
    }
    if(!found)cout<<"not found\n";
    delete[] ptr;//deallocate memory
    return 0;
}