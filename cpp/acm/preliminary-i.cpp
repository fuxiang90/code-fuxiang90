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
char str_s[N];
char str_t[N];
int len_s;
int len_t;

void make_fail(char* pat,int pat_len)
{
    int i,k;
    memset(fail, -1, sizeof(fail));
    for (i = 1; pat[i]; ++i) {
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
    }
    if( pat[j] ) return -1;
    else return i-j;
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
        make_fail(str_t,len_t);
        int pos = kmp(str_s,str_t,len_t);
        //cout <<"pos is " <<pos << endl;
        if(pos == -1) {
            cout << 0<<endl;
        } else {
            if(str_t[0] != str_t[len_t-1]) {
                if(pos != -1) {
                    cout << len_t << endl;
                }
            } else {
                int next_pos = pos + len_t -1;
                int new_pos = -1;
                int ans = 1;
                int max_ans = 1;
                while( next_pos < len_s &&(new_pos = kmp(str_s+next_pos,str_t ,len_t)) != -1){
                    if(new_pos == 0){
                        next_pos += len_t -1;
                        ans ++;
                        if(ans > max_ans){
                            max_ans = ans;
                        }
                    }else{
                        ans = 1;
                        next_pos += len_t -1;
                    }
                }

                cout << (max_ans-1)*(len_t-1) + len_t<< endl;
            }
        }
    }// end for
}




