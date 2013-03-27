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
const int N = 110;
int data[N];
int n;
int main()
{
    int t ;
    cin>>t;
    for(int i = 1 ; i <= t ;i ++){
        cin>>n;
        for(int i = 1 ; i <= N ; i ++){
            data[i] = 0;
        }

        for(int j = 1 ; j <= n;j ++){
            int num;
            cin>>num;
            data[num] ++;
        }
        int ans =0;
        for(int i = 1; i <= N ; i ++){
            if(data[i]>=3){
                ans ++;
            }
        }
        cout << ans <<endl;

    }
    return 0;
}
