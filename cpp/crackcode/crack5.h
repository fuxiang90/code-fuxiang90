#ifndef CRACK5_H_INCLUDED
#define CRACK5_H_INCLUDED

#include "my.h"

void fun1(){}


void fun5p3(int num)
{
    int ones_num = 0;
    int temp = num;
    int first_one_pos = -1;

    for(int i = 0 ; i < 32 ; i ++ ){
        if(temp & 1 == 1){
            ones_num ++;
            if(first_one_pos == -1){
                first_one_pos = i;
            }
        }
        temp >>=1;
    }
    int min_num = num + (1<<first_one_pos);
    int max_num = (~0) & ( (~0) << (32- ones_num) );

    cout << min_num << " " << max_num << endl;

}

#endif // CRACK5_H_INCLUDED
