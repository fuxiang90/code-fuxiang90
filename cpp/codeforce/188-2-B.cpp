#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;


const int N = 1000000 + 10;
int pos_arr[N];
int hash_count [N];
int pos_arr2[N];

int main()
{

    freopen("in","r",stdin);
    char * str = (char *)malloc(N);

    if(str == NULL) return 1;
    while(scanf("%s",str)!=EOF){
        int len = strlen(str);

        int pos_1 = 0;
        int pos_2 = 0;
        for(int i = 0 ; str[i] != '\0' ; i ++){

            if(str[i] == 'h' &&  i + 4 < len){

                if( str[i+ 1] == 'e' &&
                        str[i+2 ] == 'a' &&
                        str[i+ 3] == 'v' &&
                        str[i+ 4] == 'y' ){

                    pos_arr[pos_1 ++] = i;
                }

            }else if(str[i] == 'm' &&  i + 4 < len){

                if( str[i+ 1] == 'e' &&
                        str[i+2 ] == 't' &&
                        str[i+ 3] == 'a' &&
                        str[i+ 4] == 'l' ){

                    pos_arr2[pos_2 ++] = i;
                }

            }
        }//end for

        for(int i = 0 ; i < pos_1 ; i ++){
            if(i == 0 )
                hash_count[pos_arr[i]] = 1;
            else
                hash_count[pos_arr[i]] = hash_count[pos_arr[i-1]] + 1;
        }
        int count = 0;
        for(int i = 0 ; i < len ; i ++){
            if(hash_count[i] == 0)
               hash_count[i] = count;
            else
                count = hash_count[i];
        }

        long long  all= 0;

        for(int i = pos_2 -1 ;i >= 0 ; i --){
            int pos = pos_arr2[i];

            all += hash_count[pos-1];
        }

        cout << all  << endl;
        //printf("%d\n",all);

    }
	return 0;
}
