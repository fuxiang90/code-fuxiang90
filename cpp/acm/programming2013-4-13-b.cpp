#include <iostream>
#include <map>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;


const int N = 50000 + 10;
int n,m;
char src[N];
char dest[N];
int main()
{
    freopen("in","r",stdin);
    int t;
    scanf("%d",&t);
    //while(getchar() != '\n');
    for(int i =1 ; i <= t ; i ++){
        scanf("%s",src);
        scanf("%s",dest);
        int len_src = strlen(src);
        int len_dest = strlen(dest);
        int min_dist = N ;

        for(int j = 0 ; j + len_dest <= len_src ; j ++){
            int dist = 0;
            for(int k = 0 ; k < len_dest ; k ++ ){
                if(src[j+k] != dest[k]){
                        dist ++;
                }
                if(dist > min_dist){
                    break;
                }
            }
            if(dist < min_dist ) min_dist = dist;

        }
        printf("Case #%d: %d\n",i,min_dist);

    }
	return 0;
}
