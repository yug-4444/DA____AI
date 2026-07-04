#include <vector>
#include<iostream>
using namespace std;
//even thouhgt the conecpt we will using of stack but we don't use in build stack because it uses deque hardware type strcture bsae in which memory is stored as chunk where each chuch itself contain vector of ints
//chunks at differnt location in heap so L1/2 cache miss occurrs not ggod
//so by applying cocept of LIFO on vector which have continous memory we increse our cache hits and performance increases
//The Stack is the Logic (The Protocol): It is simply a set of behavioral rules—Last-In, First-Out (LIFO). It dictates how data behaves, not where it lives.
class PhysicsEngine {
public:
    vector<int> simulateCollisions(vector<int>& asteroids) {
        vector<int>result;
        for(int i=0;i<asteroids.size();i++){
            int now=asteroids[i];
            //every astroid will have some weight wheather + or - to exist wrt speed
            while(!result.empty()&&result.back()>0&&now<0){
                //they will smash and anhilate
                int belt=result.back();
                result.pop_back();
                if(abs(belt)==abs(now)){
                    now=0;
                    break;
                }
                else if(abs(belt)>abs(now)){
                    now=belt;
                }//else now=now
            }
            if(now==0){//it got anhilated along with our back of astroid and can't makes any more waves
                continue;
            }
            //now if still reach this point means needed to be pushed on result 
            result.push_back(now);
        }
        return result;
    }
};