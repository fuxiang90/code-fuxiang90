#include<iostream>
#include<cmath>

using namespace std;
int p;
int x;
int main()
{

    cin>>p;
    if(p == 3 ){
        cout << 1<<endl;
        return 0;
    }
    for(x = 1 ;x <= p ; x ++){
        int flag = 1;
        for(int i = 1 ; i <= p-2 ; i++ ){
            long l = long(pow(x*1.0,i)-1);
            if(l && l%p == 0){
                flag = 0;
                break;
            }
        }
        if( flag && long(pow(x*1.0,p-1)-1) % p == 0 ){
            cout << x <<endl;
            break;
        }
    }
    return 0;
}
