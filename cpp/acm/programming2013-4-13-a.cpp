#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;


int main()
{
    freopen("in","r",stdin);
    int t;
    scanf("%d",&t);
    int n,a,b;
    for(int i = 1 ; i <= t ; i ++){
        scanf("%d%d%d",&n,&a,&b);

        printf("Case #%d: ",i);
        int flag = -3;
        if(a -b >= 1){
            flag = 1;
        }else if(a == b){
            if(n==1)flag = -1;
            else if(n==2)flag = 0;
            else flag = 1;
        }else {
            // a < b ;
            int wina = 0;
            int winb = 0;
            if(2*a <= b){
                flag = -1;
            }else if(2*a > b){
                winb = b/2;
                wina = (a-b/2);
                if(wina + winb < n){
                    if(b%2 == 1)
                        winb ++;
                }

                if(winb > wina) flag = -1;
                else if(wina == winb) flag = 0;
                else flag = 1;
            }
        }

        printf("%d\n",flag );

    }
    return 0;
}
