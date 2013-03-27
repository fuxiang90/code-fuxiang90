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
const int N = 1010;
int dp[N][4];
string str;
int work()
{
    //memset(dp,0,sizeof(int)*N*4); 竟然没有起作用
    for(int i = 0 ; i< N ; i++){
        for(int j = 1 ; j<= 3 ; j ++)
            dp[i][j] = 0;
    }
    dp[0][1] = 1;
    dp[0][2] = 0;
    dp[0][3] = 0;

    dp[1][1] = 1;
    if(str[0] == '0')
        dp[1][2] = 0;
    else
        dp[1][2] = 1;
    dp[1][3] = 0;
    int len = str.size();
    for(int i = 2; i < len ; i ++){

        int num = (str[i-2] -'0')*100 + (str[i-1]-'0')*10 + str[i] - '0';

        dp[i][1] = (dp[i-1][1]%1234567 +dp[i-1][2]%1234567 +dp[i-1][3]%1234567)%1234567;
        if(str[i-1] != '0')
            dp[i][2] = dp[i-1][1]%1234567;
        else
            dp[i][2] = 0;
        if(num <= 255 ) {
           dp[i][3] = dp[i-1][2]%1234567;
        }else
            dp[i][3] = 0;
    }

    return (dp[len-1][1]%1234567 + dp[len-1][2]%1234567 +dp[len-1][3]%1234567)%1234567;
}
int main()
{
    int n;
    cin>>n;
    for(int i = 1 ; i <= n ;i ++){
        cin>>str;
        cout << work() <<endl;
    }
    return 0;
}
