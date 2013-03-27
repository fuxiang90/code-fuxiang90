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
int pos_arr[N];
int pos_i;
void get_nextval(char T[ ],int nextval[ ])
{
    int i=1,j=0;
    int length;
    nextval[1]=0;
    length=strlen(T);

    while(i<length) {
        if(j==0||T[i]==T[j]) {
            ++i;
            ++j;
            if(T[i]==T[j])
                nextval[i]=nextval[j];
            else
                nextval[i]=j;
        } else
            j=nextval[j];
    }
}



int Index_KMP(char S[ ],char T[ ],int nextval[ ])
{
    int i=1;
    int j=1;
    int count = 0;
    while(i<=S[0]&&j<=T[0]) {
        if( j==0 || S[i]==T[j] ) {
            ++i;
            ++j;            //继续比较后继字符
        } else
            j=nextval[j];  //模式串向后移动
        if(j>T[0]) {
            pos_arr[pos_i++] = i-T[0];
            //printf("%d ",i-T[0]);
            j=nextval[j]; //特别注意这个j的变化
        }
    }
    return count;

}

int main( )
{
    char S[256],T[256];
    char *P,*Q;
    int nextval[256];
    while(1) {
        P=&S[1];
        Q=&T[1];
        gets(P);
        gets(Q);
        S[0]=strlen(P);
        T[0]=strlen(Q);  //得到两个字符串的长度
        get_nextval(T,nextval);
        Index_KMP(S,T,nextval);
        getchar( );
    }
    return 0;
}
