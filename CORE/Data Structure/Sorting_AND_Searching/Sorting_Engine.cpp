//insertiion,selection,bubble,merge,quick,heap SORTS
#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class Sort_Engine{
    private:
    vector<int>&list;
    vector<int>temp;
    int n;
    public:
    Sort_Engine(vector<int>&l):
    list(l),n(list.size()){
        temp.resize(n);
    }

    //1.MERGE SORT ->stable and not in-place
    //O(nlogn)time and O(n)space complexity
    //cache locality->good
    void merge_conquer(int low,int high,int mid){
        for(int i=low;i<=high;i++){
            temp[i]=list[i];
        }
        int i=low,j=mid+1,k=low;//i and j run on temp where as k run on main array
        while(i<=mid&&j<=high){
            if(temp[i]<=temp[j]){
                list[k++]=temp[i++];
            }else{
                list[k++]=temp[j++];
            }
        }
        while(i<=mid) list[k++]=temp[i++];
        while(j<=high) list[k++]=temp[j++];
    }
    void merge_sort(int low,int high){
        if(low<high){
            int mid=low+(high-low)/2;
            merge_sort(low,mid);
            merge_sort(mid+1,high);
            merge_conquer(low,high,mid);
        }
        //when low==high it means size 1 no further divide so return so we can move towards merge
    }

    //2. QUICK SORT ->  unstable and in-place
    //O(nlogn)time complexity and O(logn) recrussive stack space
    //worst case may happen when data is already sorted or data is a full duplicate then O(n^2)time complexity we will try to resolve these cases
    //99:1 case or 1000:1 case even in these near extreme cases the complexity don't become O(n^2) but remain O(nlogn)
    //cache locality->excellent
    //Lomuto Quick sort
    int Lomuto_Partition(int low,int high){
        int mid=low+(high-low)/2;
        swap(list[mid],list[high]);//this can prevent worst case when input data is already sorted but we can't prevent the duplicate data in this methord 
        int pivot=list[high];
        int i=low-1;
        for(int j=low;j<high;j++){
            if(list[j]<=pivot){
                i++;
                swap(list[j],list[i]);
            }
        }
        i++;
        swap(list[high],list[i]);
        return i;
    }
    void Lomuto_Quick_Sort(int low,int high){
        if(low<high){
            int p=Lomuto_Partition(low,high);
            Lomuto_Quick_Sort(low,p-1);
            Lomuto_Quick_Sort(p+1,high);
        }//if low==high then it mean size is 1 which itself is already sorted
    }
    //Hoare Quick sort
    int Hoare_Partition(int low,int high){//both sorted and duplicated resolved
        int mid=low+(high-low)/2;
        int pivot=list[mid];
        int i=low-1,j=high+1;
        while(i<j){
            do{i++;}while(list[i]<pivot);//we can't have =< as this will become wort case in the case of dulplicated data 
            do{j--;}while(list[j]>pivot);
            if(i<j) swap(list[i],list[j]);
        }
        return j;//this the position of last element less than pivot
    }
    void Hoare_Quick_Sort(int low,int high){
        if(low<high){
            int p=Hoare_Partition(low,high);
            Hoare_Quick_Sort(low,p);
            Hoare_Quick_Sort(p+1,high);
        }
    }

    //3.HEAP SORT -> unstable and in-place
    //O(nlogn)time complexity and O(1)space complexity
    //cache locality->very bad
    //max-heap-sort
    void max_heapify(int heap_size,int i){
        int lc=2*i+1,rc=2*i+2,largest=i;
        if(lc<heap_size&&list[largest]<list[lc])largest=lc;
        if(rc<heap_size&&list[largest]<list[rc])largest=rc;
        if(largest!=i){
            swap(list[largest],list[i]);
            max_heapify(heap_size,largest);
        }
    }
    void build_max_heap(int heap_size){
        for(int i=heap_size/2-1;i>=0;i--){
            max_heapify(heap_size,i);
        }
    }
    void max_heap_sort(){
        build_max_heap(n);
        for(int i=n-1;i>=1;i--){
            swap(list[0],list[i]);
            max_heapify(i,0);
        }
    }

    //min-heap-sort
    void min_heapify(int heap_size,int i){
        int lc=2*i+1,rc=2*i+2,smallest=i;
        if(lc<heap_size&&list[smallest]>list[lc])smallest=lc;
        if(rc<heap_size&&list[smallest]>list[rc])smallest=rc;
        if(smallest!=i){
            swap(list[smallest],list[i]);
            min_heapify(heap_size,smallest);
        }
    }
    void build_min_heap(int heap_size){
        for(int i=heap_size/2-1;i>=0;i--){
            min_heapify(heap_size,i);
        }
    }
    void min_heap_sort(){
        build_min_heap(n);
        for(int i=n-1;i>=1;i--){
            swap(list[0],list[i]);
            min_heapify(i,0);
        }
    }

    //4.INSERTION SORT -> stable and in-place
    //O(n^2)average case time complexity and O(1) space complexity
    //O(n)time complexity when data already sorted or fully duplicate
    //Card game
    void insertion_sort(){
        //1st element is already considered in the sorted zone at start and we are trying to make a gap where it can fit
        for(int i=1;i<n;i++){
            int curr=list[i];
            int j=i-1;
            while(j>=0&&list[j]>curr){
                list[j+1]=list[j];
                j--;
            }
            list[j+1]=curr;
        }
    }

    //5.SELECTION SORT -> unstable and in-place
    //O(n^2)time complexity in all cases and O(1)space complexity
    //minimum hunter
    void selection_sort(){
        for(int i=0;i<n-1;i++){
            int min_element=i;
            for(int j=i;j<n;j++){
                if(list[j]<list[min_element])min_element=j;
            }
        swap(list[i],list[min_element]);//fix amount of O(n) swaps regardless of distribution in data
        }
    }

    //6.BUBBLE SORT -> stable and in-place
    //O(n^2) time complexity and O(1)space complexity
    //heavy sinker
    //although its cache locality is good buts its have a large amount of swaps in its operations 
    //optimized to O(n)time when data fully duplicate or sorted
    void bubble_sort(){
        for(int i=0;i<n-1;i++){
            bool swapped=false;
            for(int j=0;j<n-i-1;j++){
                if(list[j]>list[j+1]){
                    swapped=true;
                    swap(list[j],list[j+1]);
                }
            }
            if(!swapped)break;//early finish to save time as now remining data should already be sorted
        }
    }
};