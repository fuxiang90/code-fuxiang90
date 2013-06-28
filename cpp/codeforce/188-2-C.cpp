#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

long long x ,y ,m;


int ans;

void dfs(long long  x , long long y)
{
    if( x >= m ) return ;

    ans ++;
    long long t = x+ y;
    if (t < x) swap(t,x);
    dfs(t ,x );

}

long long no_dfs(long long  x , long long y)
{
    long long op = 0;
    while(x < m){
        long long t = x+ y;
        if (t < x) swap(t,x);


        y = x;
        x = t;

        op++;
    }
    return op;

}


int main()
{

    freopen("in","r",stdin);
    cin>>x>>y>>m;



    if(x < y) swap(x,y);


    if(x >= m ) cout << 0 <<endl;
    else if ( (x+y) <= 0  && x <= 0  ) cout << -1 <<endl;
    else {
        ans = 0;
        ans = no_dfs(x,y);
        cout << ans <<endl;
    }


	return 0;
}
