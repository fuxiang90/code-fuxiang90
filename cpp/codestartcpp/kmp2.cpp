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

const int N = 1000010;
int fail[N];
char str_s[N];
char str_t[N];
int len_s;
int len_t;
int top;
int ans[N];

int dp[N];
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

void kmp(char* str, char* pat,int pat_len, int ans[])
{

    int i, j;
    i = j = 0;
    top = 0;
    while( str[i] && pat[j] ) { 	// By Fandywang
        if( pat[j] == str[i] ) ++i, ++j;
        else if(j == 0)++i;
        else j = fail[j-1]+1;
        if(pat[j]==0)
        {
			ans[top++] = i-j;
			j = fail[j-1]+1;
		}
    }
}

int main()
{
   // freopen("in","r",stdin);
    int t ;
    scanf("%d",&t);

    for(int i = 1 ; i <= t ; i ++) {
        scanf("%s",str_s);
        scanf("%s",str_t);
        memset(ans,0,sizeof(ans));

        len_t = strlen(str_t);
        len_s = strlen(str_s);
        make_fail(str_t,len_t);

        kmp(str_s,str_t,len_t,ans);
        //cout <<"pos is " <<pos << endl;
        if(top == 0) {
            cout << 0<<endl;
            continue;
        }


        int en=ans[0]+len_t-1;

        for(int i = 1; i <= N ; i ++){
            dp[i] = 0;
        }

        dp[ ans[0] ] = 1;
        for(int i = 1 ; i < top ; i ++){
            dp[ans[i]] = dp[ ans[i] - len_t]  + 1;
        }
        printf("%d\n",dp[ans[top-1]]);

//        for(j=1; j<top; j++)
//        {
//			printf("%d %d\n",ans[j],en);
//        	if(ans[j]<=en) en=ans[j]+len_t;
//        	else
//        	{
//				if(en-st+1>ret) ret=en-st+1;
//				st = ans[j];
//				en = ans[j]+len_t-1;
//			}
//		}
//    printf("%d\n",ret);

    }// end for
}
