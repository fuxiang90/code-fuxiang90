#include<stdio.h>

struct node{
    int x;
};

typedef struct node * nodeptr;

void test(nodeptr a){
    a->x = 3;
}

int main()
{
    char a[5] = {'a','b','c','d','\0'};
    char *p = a;
//运行下面这句后, vc6.0 提示的错误为:cannot convert from 'char (*)[5]' to 'char *',&a 的类型应该是指向一个数组的指针
//char *pa = &a;
//所以,应该定义一个指向相同类型和大小的数组的指针来获得“&a”的值
    char (*point_to_str)[5];
    point_to_str = &a;
    printf("%x\n%x\n",&p, &point_to_str);
    printf("%s\n%s\n", p, point_to_str);

    int b[2][3] = { { 1,2,3} ,{2,3,4} };

    int (*pb)[3] = b; //t
    for(int i = 0 ; i < 3 ; i ++)
        printf("%x  %d\n",*(pb)+i ,**(pb+i));
    int (*ppb)[3] = &b[1];
    for(int i = 0 ; i < 3 ; i ++)
        printf("%x\n",*(ppb+i));
    int (*pppb)[3] = &b[1];

    struct node nodea;
    nodea.x = 2;

    printf("%d",nodea.x);
    struct node * nodep = &nodea;

    test(nodep);
    printf("%d",nodea.x);

}


