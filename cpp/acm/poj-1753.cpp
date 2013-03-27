/*
关键在于两
*/

#include <set>
#include <map>
#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 66000;
int hash_table[N];
int bit_key ;
int dir[4][2] = { {-1,0} ,{1,0},{0,-1},{0,1} };
struct node{
    int x;
    int y ;
};

/*
从右开始数
0-3 》 第一行 0 是第一行第一个
4-7
8-11
12-15
*/
bool isOk(int pos){
    return (pos>=0 ) && (pos < 16);
}
int turn(int  key ,int x ,int y)
{
    int pos = x*4 + y;
    int up = (x-1)*4 + y;
    int down = (x+1)*4 + y;
    int left = (x)*4 + y -1;
    int right = x*4 + y + 1;

    if(isOk(pos) && (pos ) >= 0){
        key ^= (1<<(pos ));
    }
    if(isOk(up) && x > 0){
        key ^= (1<<up );
    }
    if(isOk(down) && x < 3){
       key ^= (1<<down );
    }

    if(isOk(left) && y > 0){
       key ^= (1<<left );
    }

    if(isOk(right) && y < 3){
       key ^= (1<<right );
    }
    return key;
}



void work()
{
    hash_table[bit_key] = 1;
    queue<int> q;
    q.push(bit_key);

    while(!q.empty() ){
        int key = q.front();
        q.pop();
        for(int i = 0 ; i < 4 ; i ++){
            for(int j = 0 ; j < 4 ; j ++){
                int new_key = turn(key,i,j);
                if(hash_table[new_key] == 0){
                    hash_table[new_key] = hash_table[key]  + 1;
                    q.push(new_key);
                }

                if(new_key == 0xFFFF || new_key == 0x0000){
                    cout << hash_table[new_key] -1 <<endl;
                    return ;
                }

            }
        }//end for
    }// end while

    cout << "Impossible" <<endl;

}
int main()
{
    freopen("in","r",stdin);
    char ch;
    bit_key = 0;
    for(int i = 0 ; i < 4 ; i ++){
        for(int j = 0 ; j < 4 ; j ++){
            scanf("%c",&ch);
            if(ch == 'w'){
                bit_key ^= (1<<(i*4 + j));
                //turn(bit_key ,i,j);
            }

        }getchar();
    }
    if(bit_key == 0xFFFF || bit_key == 0x0000)
        cout << 0 << endl;
    else
        work();
    return 0;
}
