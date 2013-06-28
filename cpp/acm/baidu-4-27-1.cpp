#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;


const int N = 400 +10;
double arr[N];
double sum[N];

void work()
{
    arr[1] = 1;
    arr[2] = 2;

    //sun[3] = 3;

    for(int i = 3 ;i <= 400 ; i ++){
        double x = 1.0/i;
        double sum = 0;
        for(int j = 1 ; j <= i ; j ++){
            if(j ==1 || j == i ){
                sum += (1 + arr[i-1]);
            }else {
                sum += 1 + max(arr[j-1] , arr[i-j]);
            }
        }
        sum *= x;
        arr[i] = sum;
    }

}
char * src = "aaaa";
void fun( char * const  src2)
{

    src2[1] = '3';
    //src2 = src;
}

void fun2(const char * src2)
{
    //src2[1] = '3';
    src2 = src;
    printf("%c\n",*(src2+1));
    printf("%c\n",*(src+1));
}
int main()
{

    char * src2 = (char *)malloc(20);
    strcpy(src2 ,"12345");
    //src[2] = 'A';
    fun2(src2);
    printf("%c\n",*(src2+1));
    printf("%c\n",*(src+1));
    int t;
    work();
    scanf("%d",&t);
    int num;
    for(int i = 0 ; i < t ; i ++){
        scanf("%d",&num);

        printf("%.5lf\n",arr[num]);

    }
	return 0;
}
