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
const int N = 300;
int data[N];
int n;


int ans ;
int max_pos;
int max_num;

int main()
{
    freopen("in","r",stdin);
    int t;
    cin>>t;
    for(int i = 1 ; i<= t ; i++){
        cin>>n;
        max_num = 0;
        for(int j = 1 ; j <= n ; j ++){
            cin>>data[j];
            if(data[j] > max_num){
                max_num = data[j];
                max_pos = j;
            }
        }

        cout << ans <<endl;
        ans = 0;
    }
}
