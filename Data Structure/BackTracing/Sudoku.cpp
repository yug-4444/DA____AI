#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Sudoku{
    private:
    vector<string>sudo;
    vector<string>output;
    public:
    Sudoku(vector<string>&s):
    sudo(s){
        string s(9,'.');
        output.resize(9,s);
    }//intially all '.' else already filled in 
    bool isSafe(int row,int column,char ch){
        int r=row,c=0;
        while(c<9){//A Sudoku board starts with numbers scattered everywhere
            if(sudo[r][c]==ch)return false;
            c++;
        }
        c=column,r=8;
        while(r>=0){
            if(sudo[r][c]==ch)return false;
            r--;
        }
        r=(row/3)*3,c=(column/3)*3;
        for(int i=0;i<=2;i++){
            for(int j=0;j<=2;j++){
                if(sudo[r+i][c+j]==ch)return false;
            }
        }
        return true;
    }
    bool solve(){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(sudo[i][j]=='.'){
                    for(char c='1';c<='9';c++){
                        if(isSafe(i,j,c)){
                            sudo[i][j]=c;
                            if(solve()){
                                return true;
                            }
                            sudo[i][j]='.';   
                        }
                    }
                    return false;//reached here means unable to satisfy any result so no anwser return false
                }
            }
        }
        //reached there that means we have sutaible anwser
        output=sudo;
        return true;
    }
    vector<string>process(){
        solve();
        return output;
    }
};