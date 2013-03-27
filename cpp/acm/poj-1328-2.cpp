#include<iostream>
#include<set>
#include<map>
#include<vector>
#include<string>
#include<queue>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;


struct node{
    double x;
    double y;

};
bool cm (struct node a ,struct node b) { return (a.x - b.x < 10e-7) ; }
const int N = 1000+10;
struct node data[N];
int n,d;


int work()
{
    int ans = 1;
    if(d <= 0 ) return -1;

    double right_x = data[1].y;
    for(int i = 2 ; i <= n ; i ++){
        if(data[i].x - right_x > 10e-7){
            ans ++;
            right_x = data[i].y;
        }else {
            if(data[i].y - right_x < 10e-7)
                right_x = data[i].y;
        }
    }
//    int i = 1;
//    while(i <= n){
//
//        double rigth_x = data[i].y;
//        ans ++;
//
//        while(i <= n && data[i].x <= rigth_x ){
//                i ++;
//        }
//            //i--;
//
//    }
    return ans;
}
int main()
{
    freopen("in","r",stdin);
    int T = 1;
    while(cin>>n>>d){
        if(n ==0 && d == 0){
            break;
        }
        int flag = 0;
        for(int i = 1 ; i <= n ; i++){
            int x,y;
            cin>>x>>y;
            if(y > d) flag = 1;
            data[i].x = -1*sqrt(1.0*d*d - y*y) + x;
            data[i].y = sqrt(1.0*d*d - y*y) + x;
            //cin>> data[i].x >> data[i].y;
        }
        int ans = 0;
        if(flag == 1){
            ans = -1;
        }else{
            sort(data+1 ,data+n +1 ,cm);
            ans = work();
        }

        cout <<"Case "<< T <<": " <<ans <<endl;
        T++;
    }
	return 0;
}
