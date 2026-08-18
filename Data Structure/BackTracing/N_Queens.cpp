#include<iostream>
#include<vector>
#include<string>
using namespace std;
class N_Queens{//The basic version is great for learning and small boards
    private:
    vector<string>board;
    vector<vector<string>>output;
    int n;
    public:
    N_Queens(int N):
    n(N){
        string s(n, '.');
        for (int i = 0; i < n; i++) {
            board.push_back(s);
        }
    }
    bool is_safe(int row,int column){
        int r=row;
        int c=column;
        while(r>=0&&c>=0){
            if(board[r][c]=='Q')return false;
            r--;c--;
        }//upper left diagnol
        r=row;c=column;
        while(r<n&&c>=0){
            if(board[r][c]=='Q')return false;
            r++;c--;
        }//lower left diagnol
        r=row;c=column;
        while(c>=0){
            if(board[r][c]=='Q')return false;
            c--;
        }//check row
        //as for column it will definatly be single Q
        return true;

    }
    void solve(int column){//fill Q column by column
        if(column==n){
            output.push_back(board);
            return;
        }
        for(int row=0;row<n;row++){
            if(is_safe(row,column)){
                board[row][column]='Q';
                solve(column+1);
                board[row][column]='.';
            }
        }
    }
    vector<vector<string>>process(){
        solve(0);
        return output;
    }
};
class optimized_N_queens{//faster
    //The optimized version is the practical choice when you want to solve larger boards quickly.
    private:
    vector<string>board;
    vector<vector<string>>output;
    vector<int>up_diagnol;
    vector<int>down_diagnol;
    vector<int>left_row;
    int n;
    public:
    optimized_N_queens(int N):
    n(N){
        string s(n, '.');
        for (int i = 0; i < n; i++) {
            board.push_back(s);
        }
        up_diagnol.resize(2*n-1,0);
        down_diagnol.resize(2*n-1,0);
        left_row.resize(n,0);
    }
    void solve(int column){
        if(column==n){
            output.push_back(board);
            return;
        }
        for(int row=0;row<n;row++){
            if(up_diagnol[row+column]==0&&down_diagnol[n-1+column-row]==0&&left_row[row]==0){
                board[row][column]='Q';
                up_diagnol[row+column]=1;
                down_diagnol[n-1+column-row]=1;
                left_row[row]=1;

                solve(column+1);

                board[row][column]='.';
                up_diagnol[row+column]=0;
                down_diagnol[n-1+column-row]=0;
                left_row[row]=0;
            }
        }
    }
    vector<vector<string>>process(){
        solve(0);
        return output;
    }
};