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
char str[N];
int head,tail;
int fail[N];
char str_s[N];
char str_t[N];
int len_s;
int len_t;


struct node {
    node *next[52];
    node *fail;
    int count;
    node () {
        count=0;
        fail=NULL;
        //memset(next,0,sizeof(next));
        for(int i = 0 ; i < 52 ; i ++) {
            next[i] = NULL;
        }
    }
} *q[N];

int compute_index(char ch)
{
    if(ch >= 'a' &&ch <= 'z') {
        return ch-'a';
    } else {
        return ch-'a' + 26;
    }
}
void insert(node *root,char *str ,int c)
{
    node *p=root;
    int i=0,index;
    while(str[i]) {
        index=compute_index(str[i]) ;//str[i]-'a';
        if(p->next[index]==NULL)  p->next[index]=new node();
        p=p->next[index];
        i++;
    }
//   printf("%d\n",i);
    //p->count++;
    p->count = c;
}
void build_ac(node *root)
{
    root->fail=NULL;
    q[head++]=root;
    while(head!=tail) {
        node *temp=q[tail++];
        node *p=NULL;
        for(int i=0; i<52; i++) {
            if(temp->next[i]!=NULL) {
                if(temp==root) temp->next[i]->fail=root;
                else {
                    p=temp->fail;
                    while(p!=NULL) {
                        if(p->next[i]!=NULL) {
                            temp->next[i]->fail=p->next[i];
                            break;
                        }
                        p=p->fail;
                    }
                    if(p==NULL)  temp->next[i]->fail=root;
                }
                q[head++]=temp->next[i];
            }
        }
    }
}
int query(node *root)
{
    int i=0,cnt=0,index;
    node *p = root;
    while(str[i]) {
        index=compute_index(str[i]) ;//str[i]-'a';
        while(p->next[index]==NULL&&p!=root) p=p->fail;
        p=p->next[index];
        p=(p==NULL)?root:p;
        node *temp=p;
        while(temp!=root&&temp->count!=-1) {
            cnt=temp->count;
            temp->count=-1;
            temp=temp->fail;
        }
        i++;
    }
    return cnt;
}

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
    int t;
    scanf("%d",&t);
    for(int i = 1 ; i <= t ; i ++) {
        head=tail=0;
        node *root = new node();

        scanf("%s",str_s);
        scanf("%s",str_t);
        len_t = strlen(str_t);
        len_s = strlen(str_s);

        if(str_t[0] != str_t[len_t-1]) {
            make_fail(str_t,len_t);
            int pos = kmp(str_s,str_t,len_t);
            if(pos != -1) {
                cout << len_t << endl;
            } else {
                cout <<"0" <<endl;
            }

        } else {
            int len_new = len_t;
            while(len_new<=len_s) {
                len_new += len_t -1;
                for(int i = 1 ; i <= len_t -1 ; i++) {
                    str_t[len_new + i - len_t] =  str_t[i] ;
                }
                str_t[len_new] = '\0';
                cout << "len   " << strlen(str_t) <<endl;
                insert(root,str_t,len_new);
            }
            build_ac(root);
        }
        printf("%d\n",query(root));
    }
    return 0;

}
