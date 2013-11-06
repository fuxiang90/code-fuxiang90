#line 5 "GUMIAndSongsDiv2.cpp"


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
 

class GUMIAndSongsDiv2
{
public:
    int maxSongs(vector <int> duration, vector <int> tone, int T)
    {
        int res = 0;
        int len = duration.size();
        int ret = 0;
        for(int i = 0 ; i < len ; i ++ ){
            int pre = tone[i];
            int sum = T ;
            ret = 0;
            for(int j = i ; j < len ; j ++){
                sum -= abs(pre - tone[j]);
                pre = tone[j];
                if( sum >= duration[j] ){
                    sum -= duration[j];
                    ret ++;
                }

            }

            if(res  < ret ){
                res = ret ;
            }
        }
        return res;
    }
    
};


// Powered by FileEdit


// Powered by FileEdit
