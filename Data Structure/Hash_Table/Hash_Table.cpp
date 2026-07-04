//to look for the target every time we have to traverse our structure wheather 1D-array or link list OR 2d-bst trees
//but if we want to find the target instantainiously O(1) there comes only one struct to my mind that is array
//if we have index directly arr[i] but problem arrises if billion of users then to make arra of 4 billion bytes of contiuos memory in heap is a huge difficult task for OS
//rather we try to constrint saying every id of our data represent data and we say take array of 1000 elements rather than a billion a huge difference
//each time we modulo id with 1000 to get the index it may occpy
//but now a new problem arrises that is we can crerly see multiple points will have same index then what
//then the solution is to make array of pointer rather than int so that it may act a starting point to head of a individual link list

#include<iostream>
#include<climits>
#include <cmath>
using namespace std;
struct listnode{//coustom data type 4+4+8=16bytes
    int id;
    int data;
    listnode*next;
    listnode(int i,int d){
        id=i;
        data=d;
        next=nullptr;
    }
};
struct treenode{//4+4+8+8=24bytes
    int id;
    int data;
    treenode*left;
    treenode*right;
    treenode(int i,int d){
        id=i;
        data=d;
        right=left=nullptr;//grounded wire to avoid dangling pointer
    }
};
struct tablenode{//8+8+4=20bytes ->24bytes multiple of 8bytes as cpu read
    treenode*tree;
    listnode*list;
    int currsize;
    tablenode(){//initialzation
        tree=nullptr;
        list=nullptr;
        currsize=0;
    }
};
class HashTable{
    private:
    int n;//table size
    int total;//toatal inputs to be expected
    int boundary;//like limit at which out list converts to tree at specific no. of inputs accumulate over a ht node linker
    tablenode*ht;
    public:
    HashTable(int tsize,int tinputs){
        n=tsize;
        total=tinputs;
        boundary=ceil(0.75*total/n);//its genrally 75% of total input/size of hash table
        ht=new tablenode[n];
    }
    //we asume no two key will ever be same even through data may be same that doesn't matter
    void listinput(listnode*&head,int key,int val){
        listnode*ln=new listnode(key,val);
        //we insert at head else at tail we have to traverse O(currsize) which is not good
        //so inset at head O(1)
        ln->next=head;
        head=ln;
    }
    void treeinput(treenode*&root,int key,int val){//we use bst so not to travere whole tree during search
        if(root==nullptr){
            root=new treenode(key,val);
            return;
        }
        if(root->id>key){
            treeinput(root->left,key,val);
        }
        else{
            treeinput(root->right,key,val);
        }
    }
    void htinsert(int key,int val){
        int index=key%n;
        //it will be the index we will fill our current node
        //now let check with bounday and currsize to see what list/1D or tree/2D
        tablenode*currht=&ht[index];//we want changes to reflect 
        if(currht->currsize<boundary){
            listinput(currht->list,key,val);
            currht->currsize+=1;
        }
        else if(currht->currsize==boundary){
            listnode*&head=currht->list;//changes in head reflect in list info stored in ht else just a copy 
            currht->tree=new treenode(key,val);
            while(head!=nullptr){//rip of all the list and attach all info to tree to reduce time during search in fractured universe
                listnode*temp=head;
                head=head->next;
                treeinput(currht->tree,temp->id,temp->data);
                temp->next=nullptr;
                temp->data=temp->id=0;
                delete temp;
            }
            currht->currsize+=1;
        }else{
            treeinput(currht->tree,key,val);
            currht->currsize+=1;
        }
    }
    //search
    listnode*listsearch(listnode*head,int key){//no changes will be made in orignal head
        if(head==nullptr){
            return nullptr;
        }
        while(head!=nullptr&&head->id!=key){
            head=head->next;
        }
        return head;
    }
    treenode*treesearch(treenode*root,int key){
        if(root==nullptr){
            return nullptr;
        }
        if(root->id==key){
            return root;
        }
        else if(root->id>key){
            return treesearch(root->left,key);
        }
        else{
            return treesearch(root->right,key);
        }
    }
    int htsearch(int key){//we return data at that key
        int index=key%n;
        //we just want to search if present or not .Not edit in universe .so a copy will do as a safety net
        tablenode* currht=&ht[index];
        if(currht->currsize==0){
            return INT_MAX;
        }
        if(currht->currsize<boundary){
            listnode*ans=listsearch(currht->list,key);
            if(ans==nullptr){
                return INT_MAX;
            }
            return ans->data;
        }
        else{
            treenode*ans=treesearch(currht->tree,key);
            if(ans==nullptr){
                return INT_MAX;
            }
            return ans->data;
        }
    }
    void listdelete(listnode*&head,int key){
        if(head==nullptr){
            return ;
        }
        listnode*temp=head;
        listnode*prev=nullptr;
        while(temp!=nullptr&&temp->id!=key){
            prev=temp;
            temp=temp->next;
        }
        if(prev==nullptr){
            head=head->next;
        }
        else{
            prev->next=temp->next;
        }
        temp->data=temp->id=0;
        temp->next=nullptr;
        delete temp;
    }
    treenode*getmin(treenode*root){
        //go to left side as much as possible
        while(root->left!=nullptr){
            root=root->left;
        }
        return root;
    }
    void treedelete(treenode*&root,int key){
        if(root==nullptr){
            return;//no such node exist;
        }
        if(root->id>key){
            treedelete(root->left,key);
        }
        else if(root->id<key){
            treedelete(root->right,key);
        }
        else{
            //three cases of deleting node :0 or 1 or 2 childs possible
            if(root->left==nullptr&&root->right==nullptr){//0 child case 
                root->data=root->id=0;
                delete root;
                root=nullptr;
            }
            else if(root->left==nullptr||root->right==nullptr){//1 child case
                treenode*replace=nullptr;
                if(root->left==nullptr){
                    replace=root->right;
                }
                else{
                    replace=root->left;
                }
                root->data=root->id=0;
                root->left=root->right=nullptr;
                delete root;
                root=replace;

            }else{//2 child case now have to think what to replace
                //sucseccor of indorder i.e. the next buggest element that is right subtrees smallest
                treenode*replace=getmin(root->right);
                root->data=replace->data;
                root->id=replace->id;
                treedelete(root->right,replace->id);
            }
        }
    }
    void htdelete(int key){
        int index=key%n;
        tablenode*currht=&ht[index];
        if(currht->currsize<boundary){
            listdelete(currht->list,key);
            currht->currsize-=1;
        }
        else{
            treedelete(currht->tree,key);
        }//we don't edit currht->currsize as if in case if we -1 and we get size to be 7 then in case we thibk about rearrange tree to list
        //but this has no profit as you see time in search for bst will still be less and the conversion will cover unwanted time that is a waste
    }
    void listdest(listnode*&head){
        if(head==nullptr){
            return;
        }
        while(head!=nullptr){
            listnode*temp=head;
            head=head->next;
            temp->data=temp->id=0;
            temp->next=nullptr;//avoid dangling pointer
            delete temp;
        }
    }
    void treedest(treenode*&root){
        if(root==nullptr){
            return;
        }
        //when all childs have been discovered
        treedest(root->left);
        treedest(root->right);
        root->id=root->data=0;
        root->left=root->right=nullptr;
        delete root;
        root=nullptr;
    }
    ~HashTable(){
        for (int i=0;i<n;i++){
            tablenode*currht=&ht[i];
            currht->currsize=0;
            if(currht->list!=nullptr){
                listdest(currht->list);
            }
            else if(currht->tree!=nullptr){
                treedest(currht->tree);
            }
        }
        delete[] ht;
    }
};
//unrefined verion:::
struct hashnode{
    int id;
    int data;
    hashnode*next;
    hashnode(int i,int val){
        id=i;
        data=val;
        next=nullptr;
    }
};
struct hashtreenode{
    int id;
    int data;
    hashtreenode*right;
    hashtreenode*left;
    hashtreenode(int i,int val){
        id=i;
        data=val;
        right=nullptr;
        left=nullptr;
    }
};
struct htbst_struct{
    hashnode*head;
    hashtreenode*root;
    int size;
    htbst_struct(){
        head=nullptr;
        root=nullptr;
        size=0;
    }
};
class hashTable2{
    private:
    int n;
    //hashnode* ht; → one street with houses linked one after another.
    //hashnode** ht; → an array of streets. Each index is a different street, and each street has its own chain of houses.
    hashnode**ht;// array of pointers to hashnode
    htbst_struct*htbst;
    public:
    hashTable2(int size){
        n=size;
        ht=new hashnode*[n];
        for(int i = 0; i < n; i++){
            ht[i] = nullptr;//to avoid garbage pointers
        }
        htbst=new htbst_struct[n];
    }
    void bstinsert(hashtreenode*&root,int key,int val){
        if(root==nullptr){
            root=new hashtreenode(key,val);
            return;
        }
        if(root->id>key){//type of constaint in data that key or id value can't be same
            bstinsert(root->left,key,val);
        }else{
            bstinsert(root->right,key,val);
        }
    }
    hashtreenode*getmin(hashtreenode*root){
        if(root==nullptr){
            return nullptr;
        }
        while(root->left!=nullptr){
            root=root->left;
        }
        return root;//left most element meanis min
    }
    void bstdelete(hashtreenode*&root,int key){
        if (root==nullptr){
            return;
        }
        if(root->id==key){
            //three cases
            if(root->left==nullptr&&root->right==nullptr){
                root->id=root->data=0;
                delete root;
                root=nullptr;
                return;
            }
            else if(root->left==nullptr||root->right==nullptr){
                hashtreenode*replace=nullptr;
                if(root->left==nullptr){
                    replace=root->right;
                }else{
                    replace=root->left;
                }
                root->data=root->id=0;
                root->left=root->right=nullptr;
                root=replace;
                return;
            }else{
                hashtreenode*replace=getmin(root->right);//sucesor of root inorder
                root->data=replace->data;
                root->id=replace->id;
                bstdelete(root->right,replace->id);
            }
        }
        else{
            if(root->id>key){
                bstdelete(root->left,key);
            }else{
                bstdelete(root->right,key);
            }
        }
    }
    void htinsert(int key,int val){
        hashnode*temp=new hashnode(key,val);
        int index=key%n;
        //now we think wheather to insert at head or middle or tail of a link list
        //head more okay as we know O(1) time in other it is O(n)
        temp->next=ht[index];
        ht[index]=temp;
    }
    void htinsert2(int key,int val){//when size of linklist>8 then bst for of it to reduce search time 
        //use htbst
        int index=key%n;
        htbst_struct *&curr=htbst[index];//not a pointer but name of htbst[index]
        if(curr->size+1<8){//normal link list
            hashnode*temp=new hashnode(key,val);
            temp->next=curr->head;
            curr->head=temp;
            curr->size+=1;
        }else if(htbst[index]->size+1==8){
            hashtreenode*root=new hashtreenode(key,val);
            while(curr->head!=nullptr){
                bstinsert(root,curr->head->id,curr->head->data);
                hashnode*todel=curr->head;
                curr->head=curr->head->next;
                todel->data=todel->id=0;
                todel->next=nullptr;
                delete todel;
            }
            curr->head=nullptr;
            curr->root=root;
            curr->size=8;
        }else{
            bstinsert(curr->root,key,val);
            curr->size+=1;
        }
    }
    int htsearch(int key){
        int index=key%n;
        hashnode*head=ht[index];
        while(head!=nullptr&&head->id!=key){
            head=head->next;
        }
        if(head==nullptr){
            return INT_MAX;
        }
        return head->data;
    }
    hashtreenode* searchbst(hashtreenode*&root,int key){
        if(root==nullptr){
            return nullptr;
        }
        if(root->id==key){
            return root;
        }
        else if(root->id>key){
            return searchbst(root->left,key);
        }
        else{
            return searchbst(root->right,key);
        }
    }
    int htbstsearch(int key){
        int index=key%n;
        htbst_struct*&curr=htbst[index];
        if(curr->size<8){
            hashnode*head=curr->head;
            while(head!=nullptr&&head->id!=key){
                head=head->next;
            }
            if(head==nullptr){
                return INT_MAX;
            }
            return head->data;
        }else{
            hashtreenode*ans=searchbst(curr->root,key);
            if(ans==nullptr){
                return INT_MAX;
            }
            return ans->data;
        }
    }
    void hash
    void deletebst(hashtreenode*&root){
        if(root==nullptr){
            return;
        }
        deletebst(root->left);
        deletebst(root->right);
        root->left=root->right=nullptr;
        root->id=root->data=0;
        delete root;
    }
    ~hashTable2(){
        for(int i=0;i<n;i++){
            hashnode*&head=ht[i];
            while (head!=nullptr){
                hashnode*temp=head;
                head=head->next;
                temp->next=nullptr;//avoid dangling pointer
                temp->data=temp->id=0;//avoid previous data iformation to float to avoid access to senstive information
                delete temp;//free memory
            }
        }
        delete[]ht;
        for(int i=0;i<n;i++){
            htbst_struct*&curr=htbst[i];
            curr->size=0;
            if(curr->root!=nullptr){
                deletebst(curr->root);
            }else{
                while(curr->head!=nullptr){
                    hashnode*temp=curr->head;
                    curr->head=curr->head->next;
                    temp->next=nullptr;
                    temp->data=temp->id=0;
                    delete temp;
                }
            }
        }
        delete[]htbst;
    }
};
int main() {
    HashTable ht(1000, 10000);

    ht.htinsert(101, 500);
    ht.htinsert(1101, 600); // same bucket, collision
    ht.htinsert(2101, 700); // more collisions...
    
    cout << ht.htsearch(1101) << endl; // should print 600
    return 0;
}
