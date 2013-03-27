#include <set>
#include <map>
#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    int a;
    while(cin>>a  ){
        double d = sqrt(a);
        for(int i = 1 ;  ; i ++){
            int t = int(sqrt(i)*d);
            if(t*t == i * a){
                cout << (i + 2*t + a)<<endl;
                break;
            }
        }
    }
    return 0;
}
