# include<iostream>
#include <cstdio>
#include <cstdlib>
struct node
{
};

struct nodeOne
{
    int value;
    int p [];
};

void test1()
{
    printf("%d\n",sizeof(struct node));

    printf("%d\n",sizeof(struct nodeOne));
    struct nodeOne  *ptr = (struct nodeOne *)malloc(sizeof(struct nodeOne) + sizeof(int)*100);
    for(int i = 0 ; i < 100 ; i ++){
        ptr->p[i] = i;
    }
    for(int i = 0 ; i < 100 ; i ++){
        printf("%d\n",ptr->p[i] = i);
    }


    printf("%s \n",__FILE__);
    printf("%s, %s",__DATE__,__TIME__);
}

void test2()
{
  int i = 2 ;
    int *p = (int *)&i;
    *p = NULL;
    p = NULL;
}

void test3()
{
    int a[4]={1,2,3,4};
    int *ptr1=(int *)(&a+1);
    int *ptr2=(int *)((int)a+1);
    printf("%x,%x",ptr1[-1],*ptr2);
}


void fun()
{
    printf(" function pointer\n");
}
void test4()
{
    void (*p ) () ;
    p = fun;
    (*p)();
}
int main()
{
    return 0;
}
