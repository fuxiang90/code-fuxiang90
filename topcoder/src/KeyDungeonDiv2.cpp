// BEGIN CUT HERE

// END CUT HERE
#line 5 "KeyDungeonDiv2.cpp"


#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <climits>
#include <queue>
 
using namespace std;
 

class KeyDungeonDiv2
{
public:
    int countDoors(vector <int> doorR, vector <int> doorG, vector <int> keys)
    {
        int res = 0;
        for(int i = 0 ; i < 4 ; i ++){
            int red = keys[0] ;
            int green = keys[1];
            int white = keys[2];
            
            int sum = doorR[i] + doorG[i];
            if(red + green + white >= sum && red + white >= doorR[i]
                        && green + white >= doorG[i]){
                res += 1 ;
            }
        }
        return res;
    }
    
};
// BEGIN CUT HERE
int main()
{
    KeyDungeonDiv2 ___test;
    ___test.run_test(-1);
}
// END CUT HERE
