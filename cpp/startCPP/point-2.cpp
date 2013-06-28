#include <iostream>

using namespace std;


//
//int * fun()
//{
//    int a = 2 ;
//    return  &a;
//}
//void fun2(int * a){
//    cout << *a <<endl;
//
//    //*a = 3;
//}
//
//int* fun3()
//{
//    int d[10] ;
//    return d;
//}
int main()
{
//    int *p = fun();
//
//
//    //cout << *p << endl;
//
//    cout << *p <<endl;
//    fun2(p) ;
//    cout << *p <<endl;



    int a[2] = {1,2};
    cout <<*(a+1) <<endl;

    int * p = a;

    cout <<*(p++) <<endl;
    //int *p = ++a;
//    cout << *(a)<<endl;
//    pp[1] = 10;
//
//    for(int i = 0 ; i < 10 ; i ++){
//        pp[i] = i;
//    }
	return 0;
}
