/*ID:fuxiang2
PROG: zerosum
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
 
#define REP(i, n) for (int i=0;i<int(n);++i)
#define FOR(i, a, b) for (int i=int(a);i<int(b);++i)
#define DWN(i, b, a) for (int i=int(b-1);i>=int(a);--i)
#define REP_1(i, n) for (int i=1;i<=int(n);++i)
#define FOR_1(i, a, b) for (int i=int(a);i<=int(b);++i)
#define DWN_1(i, b, a) for (int i=int(b);i>=int(a);--i)
#define EACH(it, A) for (typeof(A.begin()) it=A.begin(); it != A.end(); ++it)
 
using namespace std;
ofstream fout ("zerosum.out");
ifstream fin ("zerosum.in");
 
const int N = 10;
int flag[N];
int n;
int ans ;
 
int hash[1100000];
int compute()
{
    int num = 0;
    FOR_1(i,1,n)
        num = num *4 + flag[i];
    return num;
}
void dfs(int deep)
{
    if(deep == n  ){
        flag[0] = 2;
        int num = 0;
        int t = 1;
        int pre = 0;
        FOR_1(i,1,n){
 
            if(flag[i-1] ==0 )
                return ;
            if(flag[i-1] == 1)
                t = t*10 + i;
            else if(flag[i-1] == 2){
                if(pre == 2)
                    num += t;
                else if(pre == 3)
                    num -= t;
                t = i;
                pre = 2;
            }
            else if(flag[i-1] == 3){
                if(pre ==2)
                    num += t;
                else if(pre == 3)
                    num -= t;
                t = i;
                pre = 3;
            }
        }
        if(pre == 2)
            num += t;
        else if(pre ==3)
            num -= t;
 
        if(num ==0 ){
            fout<<1;
            FOR_1(i,2,n){
                if(flag[i-1] == 1)
                    fout<< " ";
                else if(flag[i-1] == 2)
                    fout<< "+";
                else if(flag[i-1] == 3)
                    fout<<"-";
                fout<<i;
 
            }
            fout << endl;
        }
    }// end if
 
    FOR_1(i,1,3){
        flag[deep] = i;
        int num = compute();
        if(hash[num] == 0){
            hash[num] = 1;
            dfs(deep + 1);
        }
        flag[deep] = 0;
 
    }
 
}
int main()
{
    fin>>n;
 
    dfs(1);
    return 0;
}
