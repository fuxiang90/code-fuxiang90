#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;


const int N = 10000+20;
int data[N];
int main()
{

    freopen("in","r",stdin);
    int t;
    scanf("%d",&t);
    int maxN = 0;
    for(int i =1 ; i <= t ; i ++){
        int a,b;
        scanf("%d%d",&a,&b);
        for(int j = a ; j <= b ; j ++)data[j] ++;

        if(maxN < b) maxN = b;
    }
    int max_len = 0;
    for(int i = 0 ; i <= maxN ; i++){

        if(data[i]){
            int j = i;
            while(data[j]){
                j++;
            }
            if(max_len < (j-i -1)) max_len = j-i -1;

            i = j -1;
        }
    }

    printf("%d\n",max_len);
	return 0;
}
