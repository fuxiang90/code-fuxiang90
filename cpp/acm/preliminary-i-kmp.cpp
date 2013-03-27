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

const int N = (10e6) + 10;
int fail[N];
int pos_arr[N];
char str_s[N];
char str_t[N];
int dp[N];
int len_s;
int len_t;


int pos_i;


void make_fail(char* pat,int pat_len,int start)
{
    int i,k;
    memset(fail, -1, sizeof(fail));
    for (i = start + 1; pat[i]; ++i) {
        for (k=fail[i-1]; k>=0 && pat[i]!=pat[k+1];
                k=fail[k]);
        if (pat[k + 1] == pat[i]) fail[i] = k + 1;
    }
}
int kmp(char* str, char* pat,int pat_len)
{

    int i, j;
    i = j = 0;
    while( str[i] && pat[j] ) { // By Fandywang
        if( pat[j] == str[i] ) ++i, ++j;
        else if(j == 0)++i;//第一个字符匹配失败，从str下个字符开始
        else j = fail[j-1]+1;

        if(!pat[j]){
            pos_arr[pos_i ++] = i-j;
            j = 0;
        }
    }

    return 0;
}
int main()
{
    freopen("in","r",stdin);
    int t ;
    scanf("%d",&t);

    for(int i = 1 ; i <= t ; i ++) {
        scanf("%s",str_s);
        scanf("%s",str_t);
        len_t = strlen(str_t);
        len_s = strlen(str_s);
        make_fail(str_t,len_t,0);
        kmp(str_s,str_t,len_t);
        //cout <<"pos is " <<pos << endl;
        if(pos_i == 0) {
            cout << 0<<endl;
        } else {
            if(pos_i == 1) {
                cout << len_t << endl;
            } else {

                dp[ pos_arr[0] ] = 1;
                for(int i = i ; i < pos_i ; i ++){
                    dp[pos_arr[i]] = dp[ pos_arr[i] - len_t]  + 1;
                }
                printf("%d\n",dp[pos_arr[pos_i-1]]);

            }
        }
    }// end for
}




