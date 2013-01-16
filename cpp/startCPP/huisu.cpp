# include<iostream>
# include<cstdio>

using namespace std;

const int N = 3;
int data[N] = {1,2,3};

const int maxdeep = 3;
int used[N];
int subset[N];
void work(int deep )
{

    for(int i = 0 ; i < deep ; i ++)
    {
        printf("%d\t",subset[i]);
    }
    printf("\n");

    if(deep >= maxdeep)
        return ;
    //
    for(int i = deep ; i < N ; i ++){
        if(used[i] == 0)
        {
            used[i] = 1;
            subset[deep] = data[i];
            work(deep + 1);
            used[i] = 0;
        }
    }

}


int main()
{

    //生成非空子集
    for(int i = 0 ; i < N  ; i ++){
        used[i] = 1;
        subset[0] = data[i];
        work(1);
    }
    // 如果直接work(0) 那么就会生成全排列

    return 0;
}
