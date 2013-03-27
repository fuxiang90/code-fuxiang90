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
    bool operator < (struct node & m)const {
        return x < m.x;
    }
};
bool cm (struct node a ,struct node b) { return (a.x < b.x); }
const int N = 1000+10;
struct node data[N];
int n,d;

double getX(int i)
{
    return sqrt(d*d - data[i].y*data[i].y) + data[i].x;
}
int work()
{
    int ans = 0;
    for(int i = 1 ; i <= n ; i ++ ,ans ++){
        if(data[i].y > d){
            return -1;
        }
        double mx = getX(i);
        if(i+1 <= n && ( (data[i+1].x-mx)*(data[i+1].x-mx) + data[i+1].y*data[i+1].y <= d*d) ){
            while(i +1 <= n && (data[i+1].x-mx)*(data[i+1].x-mx) + data[i+1].y*data[i+1].y <= d*d ){
                i ++;
            }
            i --;
        }
    }
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

        for(int i = 1 ; i <= n ; i++){
            cin>> data[i].x >> data[i].y;
        }
        sort(data+1 ,data+n +1 ,cm);
        int ans = work();
        cout <<"Case "<< T <<": " <<ans <<endl;
        T++;
    }
	return 0;
}
