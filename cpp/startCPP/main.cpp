#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stack>
#include <iostream>

using namespace std;
const int N = 1000;

int a[N],d[N];
stack<int> b,c;
int M;

//void cp(stack<int> &src ,)

void foo(int n,int m)
{
    int tmp = 0;
    if(m < 0 || n <0 )
        return ;
    if(m == 0 && n ==0)
    {
        int i = 1;
        while(!c.empty() )
        {
            tmp = c.top();
            c.pop();
            d[i++] = tmp;
        }
        for(i = M ; i > 0 ; i --)
        {
            printf("%d%c",d[i],(i==1)?'\n':' ');
            c.push(d[i]); //恢复栈C 的内容
        }

    }
    if(n > 0)
    {
        tmp = a[n];
        b.push(tmp);
        foo(n-1,m+1);
        b.pop();
    }

    if( m >0 && !b.empty())
    {
        tmp = b.top();
        b.pop();
        c.push(tmp);
        foo(n,m-1);
        c.pop();
    }

}

int main()
{
    M = 4;
    for(int i = 1 ; i <= M ; i ++)
        a[i] = i;

    foo(M,0);

	return 0;
}
