#include<iostream>
#include<climits>
#include<cmath>
#include<cfloat>
#include<algorithm>
#include<vector>
using namespace std;
struct Point{
    double x,y;
};
class find_distance{
    private:
    vector<Point>input_point;
    double ecludian_distance(Point a,Point b){
        return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    }
    double brute_search(vector<Point>&P,int left,int right){
        double min_dis=DBL_MAX;
        for(int i=left;i<=right;i++){
            for(int j=i+1;j<=right;j++){
                min_dis=min(min_dis,ecludian_distance(P[i],P[j]));
            }
        }
        return min_dis;
    }
    double strip_closest(vector<Point>&strip,double d){
        double min_dis=d;
        sort(strip.begin(),strip.end(),[](const Point&a,const Point&b){return a.y<b.y;});
        for(int i=0;i<strip.size();i++){
            for(int j=i+1;j<strip.size();j++){
                if(fabs(strip[i].y-strip[j].y)>=min_dis)break;
                min_dis=min(min_dis,ecludian_distance(strip[i],strip[j]));
            }
        }
        return min_dis;
    }
    double closest_recursive(vector<Point>&P,int left,int right){
        if(right-left<=2)return brute_search(P,left,right);
        int mid=left+(right-left)/2;
        Point p_mid=P[mid];
        double d_l=closest_recursive(P,left,mid);
        double d_r=closest_recursive(P,mid+1,right);
        double min_dis=min(d_l,d_r);
        vector<Point>strip;
        for(int i=left;i<=right;i++){
            if(fabs(p_mid.x-P[i].x)<min_dis)strip.push_back(P[i]);
        }
        return min(min_dis,strip_closest(strip,min_dis));
    }
    public:
    find_distance(vector<Point>p):
    input_point(p){}
    double process(){
        sort(input_point.begin(),input_point.end(),[](const Point&a,const Point&b){return a.x<b.x;});
        return closest_recursive(input_point,0,input_point.size()-1);
    }
};