#include<iostream>
#include<unordered_map>
using namespace std;
//Absolute $O(1)$ Time: Every single call to get() and every single call to put() must execute in $O(1)$ average time.The Ban: You cannot use an array or a standard std::vector to loop through and find the oldest item. Looping takes $O(N)$ time. Erasing from the middle of a vector takes $O(N)$ time
//because of these constraints we are required to have a doubly link list so mid erase to O(1) and to imediaty get stored info we require use of hash map
struct node{
    int id;
    int data;
    node*next;
    node*prev;
    node(int key,int val){
        id=key;
        data=val;
        next=nullptr;
        prev=nullptr;
    }
};
class LRUCache {
    private:
    node*head;
    node*tail;
    int count;
    unordered_map<int,node*>map;
    int size_cache;
    public:
    LRUCache(int capacity) {
        size_cache=capacity;//atleast has to be 1
        head=nullptr;
        tail=nullptr;
        count=0;
    }
    // OUTPUT: The integer 'value' associated with that key. If the key does not exist, return -1.
    int get(int key) {
        if(map.find(key)==map.end()){
            cout<<"no such key with data in our cache so require insert";
            return -1;
        }
        //before we return value our this get will make our data/key become recently used
        // now we have tpo delete from b/w
        node*update=map[key];//we have direct address
        if(update==head){
            return map[key]->data;
        }
        //now it has to be that list capacity have atleast 2 element else it would have been head due to it already handled
        if(update->prev!=nullptr){//not neccesary as can't be head
            update->prev->next=update->next;
        }
        if(update->next!=nullptr){
            update->next->prev=update->prev;
        }else{
            tail=tail->prev;
        }
        update->prev=nullptr;
        update->next=head;
        head->prev=update;
        head=update;
        return map[key]->data;
    }
    //insert in the memory of cache while checking if capacity is full or not if full then we eject our least recently used and what we inserting becomes our head
    //since to be deleted is at tail so if we have singly link list takes extra O(n) time each time but if doubly then O(1)time in deleting LRU
    void put(int key, int value) {//we will also have update if key is duplicate
        if(size_cache<=0){
            cout<<"no cache in system";
            return ;
        }
        if(map.find(key)!=map.end()){//update thing that already exist
            node*update=map[key];
            //since already exist head can't be nullptr
            update->data=value;
            //now shift it to most recenlty used pos i.e. head
            if(update==head){
                return;
            }
            update->prev->next=update->next;
            if(update->next!=nullptr){
                update->next->prev=update->prev;
            }else{
                tail=tail->prev;
            }
            update->prev=nullptr;
            update->next=head;
            head->prev=update;
            head=update;
            return;
        }
        node*temp=new node(key,value);
        if(head==nullptr){//or count ==0
            head=temp;
            tail=temp;
            count+=1;
        }else if(count<size_cache){
            temp->next=head;
            head->prev=temp;
            head=temp;
            count+=1;
        }else{//count==size_cache and we will maintain our system such that 0<=count<=size_cache
            //1st we will make space and then insert not in reverse
            node*todel=nullptr;
            if(head==tail){
                todel=head;
                map.erase(todel->id);//erase before deleting and adding
                head=tail=nullptr;
                head=tail=temp;
            }else{
            todel=tail;
            map.erase(todel->id);//erase before deleting and adding
            tail=tail->prev;
            tail->next=nullptr;
            head->prev=temp;
            temp->next=head;
            head=temp;
            }
            todel->data=todel->id=0;
            todel->prev=nullptr;//avoided dangling pointer
            delete todel;
        }
        map[key]=temp;
    }
    ~LRUCache(){
        while(head!=nullptr){//The map will be destroyed automatically when the object is destroyed, so clearing it manually is redundant.
            node*temp=head;
            temp->data=temp->id=0;
            head=head->next;
            temp->next=temp->prev=nullptr;
            delete temp;
        }
    }
};