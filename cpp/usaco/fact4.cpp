/*
ID:fuxiang2
PROG: fact4
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
ofstream fout ("fact4.out");
ifstream fin ("fact4.in");

int main()
{
    long long re  = 0;
    int n ;
    fin >>n;

    re = 1;
    for(int i = 1 ; i <= n ; i ++){
        re = re *i;
        while(re %10 == 0){
            re = re/10;
        }
        re = re%10000;
    }
    fout << re%10 <<endl;
    return 0;
}
