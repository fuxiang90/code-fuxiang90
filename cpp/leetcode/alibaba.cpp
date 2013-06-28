#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

void mergesort(int *data ,int start ,int end)
{
    if(start >= end) return ;

//    if(end - start  == 1 ) {
//        if(data[start] > data[end]){
//            int t = data[start] ;
//            data[start] = data[end];
//            data[end] = t;
//        }
//        return ;
//    }

    int mid = (start + end) /2;

    mergesort(data,start ,mid);
    mergesort(data,mid+1 ,end);


    int *new_data = (int*)malloc(sizeof(int)*(end-start +1));
    if(new_data== NULL){
        exit(-1);
    }

    int l1 = start;
    int l2 = mid+1;
    int pos = 0;
    while(l1 <= mid && l2 <= end){
        if(data[l1] <= data[l2]){
            new_data[pos++] = data[l1++];
        }else{
            new_data[pos++] = data[l2++];
        }
    }

    while(l2 <= end){
        new_data[pos++] = data[l2++];
    }

    while(l1 <= mid){
        new_data[pos++] = data[l1++];
    }

    memcpy(data + start , new_data ,(end-start+1)*sizeof(int) );
    free(new_data);

}
int main()
{

    int data[10] = {2,-1,2,2, -100,2,3,6,9999,33423};

    mergesort(data,0,9);

    //mergesort(data,0,1);


	return 0;
}


