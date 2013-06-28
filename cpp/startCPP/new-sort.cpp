#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;


struct node{
    int a;
    int b[100];
};
struct node arr[3];


int Cmp(const void * a  ,const void * b)
{
    return arr[ *(int*)a].a - arr[ *(int*)b].a;

}
int main()
{

    arr[0].a = 3;
    arr[1].a = 2;
    arr[2].a = 4;

    int data[3] = {0,1,2};

    qsort(data,3,4,Cmp);


	return 0;
}
