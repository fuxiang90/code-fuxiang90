#include <iostream>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

const int N = 100000+10;
int n,m,h;
vector<int> hi;

void work(int g)
{
    int l = g;
    int  r = g;
    hi[g] = h;
    for(int i = 1 ; i <= h ; i ++){
        if(h - i  < 0 ) break;
        if(hi[r+i] < h-i)
            hi[r+i]  = h-i;
        if(l -i >= 1 && hi[l-i] < h-i)
            hi[l-i]  = h-i;
    }
}
int main()
{
    freopen("in","r",stdin);
    int T;

    cin>>T;
    hi.reserve(N);
    for(int i = 1; i <= T ; i ++){
        fill_n(hi.begin(),N-1,0);
        cin>>n>>m>>h;

        for(int j = 1 ; j <= m ; j ++){
            int num;
            cin>>num;
            work(num);
        }


        for(int j = 0 ; j < n ; j ++){
            cout<<hi[j+1] <<endl;
        }
    }
    return 0;
}
