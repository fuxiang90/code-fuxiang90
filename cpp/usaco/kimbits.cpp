/*
ID:fuxiang2
PROG: kimbits
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <algorithm>
#include <set>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;
ofstream fout ("kimbits.out");
ifstream fin ("kimbits.in");

long long c(long a,long b)
{
    if(a<b)
        return 0;
    long long res=1;
    for(long i=1; i<=b; i++)
    {
        res*=(a-i+1);
        res/=i;
    }
    return res;
}
long long superC(long a,long b)
{
    long long res=0;
    for(long i=0; i<=b; i++)
        res+=c(a,i);
    return res;
}
long long ans[100];
long long iindex,maxGe,wei;
void fun(long wei,long long iindex,long left)
{
    if(wei==0)
        return ;
    long long done=superC(wei-1,left);
    ans[wei]=!(done>=iindex);
    if(done>=iindex)
        fun(wei-1,iindex,left);
    else
        fun(wei-1,iindex-done,left-1);
}

int main()
{
    fin>>wei>>maxGe>>iindex;
    fun(wei,iindex,maxGe);
    for(long i=wei; i>=1; i--)
        fout<<ans[i];
    fout<<endl;
    return 0;
}
