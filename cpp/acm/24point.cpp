#include<iostream>
#include<vector>

int op[3];//1 2 3 4
int used[5];
int data[5];
int num[5];
using namespace std;
int compute(){
    int result = data[0];
    for(int i = 1 ; i <= 3 ; i ++){
        if(op[i-1] == 1){
            result += data[i];
        }else if(op[i-1]  == 2){
            result -= data[i];
        }else if (op[i-1] == 3){
            result *= data[i];
        }else{
            result /= data[i];
        }

    }
    return result;
}
void dfs(int deep )
{
    if(deep == 4 ){
        int re = compute();
        if(re == 24){
            //cout <<  "get it "<<endl;
            for(int i = 0 ; i < 3 ; i ++){
                cout << data[i] << " " << op[i] ;
            }
            cout << data[3] <<endl;
        }
        return ;
    }

    for(int j = 1 ; j <= 4 ; j ++){
        if(used[j] == 0 ){
            used[j] = 1;
            data[deep] = num[j];
            for(int i = 1 ; i <= 3 ; i ++){
                op[deep] =  i;
                dfs(deep + 1);
            }
            used[j]  = 0;
        }
    }

}

int main()
{
    num[1] = 3;
    num[2] = 8;
    num[3] = 3;
    num[4] = 1;
    dfs(0);
    return 0;
}
