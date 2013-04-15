//剑指offer  面试题
//循环递增数组中最小的那个数的下标

#include <iostream>

using namespace std;


int fun(int data[],int s,int e)
{
    if(s > e) return -1;
    if(s==e) return s;

    int flag = 0;
    int n = e + 1;
    int mid = -1;
    int l = s;
    int r = e;
    while(flag == 0 && l <= r){

        mid = (l+r)>>1;

        if( data[mid] <  data[(mid-1+n)%n] &&data[mid] < data[(mid+1+n)%n]  ){
            flag = 1;
        }else if (data[mid] > data[r]){
            l = mid + 1;
        }else if(data[mid] < data[r]){
            r = mid -1;
        }else {
            int mid_new = mid;
            while(data[mid_new] == data[r]) mid_new ++;

            if(mid_new -1  == r) r = mid -1;
            else l = mid + 1;

        }

    }
    return mid;

}

int main()
{
    int data[10] = {3,3,4,5,6,7,1,2,3,3};
    int data2[10] = {1,2,3,4,5,6,7,8,9,10};
    int data3[1] = {1};
    int data4[2] = {2,1};
    cout << fun(data,0,9) <<endl;
    cout << fun(data2,0,9) <<endl;
    cout << fun(data3,0,0) <<endl;
    cout << fun(data4,0,1) <<endl;
	return 0;
}
