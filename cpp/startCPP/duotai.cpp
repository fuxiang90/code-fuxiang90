#include <iostream>
#include <cstdio>
using namespace std;
struct A {
    void *vptr;
    int i;
};

struct B{
    void *vptr;
    int i;
    char c;
    int j;
}b[2] ={
    {(void*)0x01, 100, 'a', -1},
    {(void*)0x02, 200, 'A', -2}
};


int main()
{
    struct A *pa1 = (struct A*)(b);

    printf("%d %d ",b[1].i ,pa1[1].i);  //pa1[1].i 直接读取的b[0].j 的值，按照内存寻址
	return 0;
}
