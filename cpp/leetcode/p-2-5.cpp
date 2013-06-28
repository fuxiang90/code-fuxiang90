//返回一个数组的前k个最大的数字

#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;


//s 和e 表示能访问的最大 最小下标
int Partition(int * data ,int s ,int e )
{
    if(s == e) return  s;
    int p = s;
    int l = s + 1;
    int r = e;
    while(l  <= r){
        while(l <= e && data[l] < data[p]){
            l ++;
        }

        while(r > s && data[r] >= data[p]){
            r --;
        }
        if(l < r)
        swap(data[l] ,data[r]);
    }

    swap(data[r] ,data[p]);

    return r;

}

int Partition2(int * data ,int s ,int e )
{
    if(s == e) return  s;
    int p = s;
    int i = p;

    for(int j = p + 1 ;j <= e ;j++ ){
        if(data[j] < data[p]){
            i ++;
            swap(data[i],data[j]);
            //i ++;
        }
    }

    swap(data[i],data[s]);

    return i;

}

int Partition3(int * data ,int s ,int e )
{
    if(s == e) return s;
    int i ,j ,key;
    i = s;j = e;key = data[i];

    while(i<j){
        while(i<j && data[j] > key) j--;

        if(i < j ) data[i++] = data[j];

        while(i < j &&data[i] < key) i ++;
        if(i < j ) data[j--] = data[i];

    }
    data[i] = key;
    return i;
}

int * getMaxK(int *data,int s ,int e,int k)
{
    if(e -s + 1 <= k ){
        return data;
    }

    int p = Partition2(data,s,e);

    if(e - p + 1 > k  ){
        return getMaxK(data,p+1,e,k);
    }else if ( e- p + 1 == k){
        int *new_data = (int *)malloc(sizeof(int)*k);
        for(int i = 0 ; i < k  ; i ++ ){
            new_data[i] = data[p+i];
        }

        return new_data;
    }else {
        int k2 = e-p+1;
        int *new_data = (int *)malloc(sizeof(int)*k);
        for(int i = 0 ; i < k2  ; i ++ ){
            new_data[i] = data[p+i];
        }

        int * data2 = getMaxK(data,s,p-1, k-k2);

        for(int i = 0 ; i < k -k2 ; i ++){
            new_data[k2 + i] = data2[i];
        }
        free(data2);
        data2 = NULL;
        return new_data;

    }


}
void getMaxK2(int *data,int s ,int e,int k)
{
    if(e -s + 1 <= k ){
        return ;
    }

    int p = Partition2(data,s,e);

    if(e - p + 1 > k  ){
        getMaxK(data,p+1,e,k);
    }else if ( e- p + 1 == k){
        ;
    }else {
        int k2 = e-p+1;
        getMaxK(data,s,p-1, k-k2);
    }

}
int main()
{
    int data[10] = {3,2,-2,0,2,3,4,5,100,2};



//	int *result = getMaxK(data,0,9,5);
//	for(int i = 0 ; i < 5 ; i ++){
//        printf("%d\n",result[i] );
//	}

	getMaxK2(data,0,9,5);

	for(int i = 9 ; i >= 5  ; i --){
        printf("%d\n",data[i] );
	}
	return 0;
}
