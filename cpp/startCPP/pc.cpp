//批处理作业调度问题
#include <iostream>
#include <climits>
using namespace std;

class Flowshop
{
    friend intFlow(int **,int ,int []);
private:
    voidBacktrack(int);
    int**M,            //各作业所需的处理时间
    *x,             //当前作业调度
    *bestx,         //当前最优作业调度
    *f2,            //机器2完成处理时间
    f1,             //机器1完成处理时间
    f,              //完成时间和
    bestf,          //当前最优值
    n;              //作业数
};
void Swap(int &a, int &b)
{
    int temp;
    temp = a ;
    a = b;
    b = temp;
}
void Flowshop :: Backtrack(int i)     //搜索第i层结点
{
    if(i > n)                                             //到达结点
    {
        for(int j= 1; j <= n; j++)
        {
            bestx[j] = x[j];              //当前最优作业调度
        }
        bestf =f;                                //当前最优完成时间和
    }
    else
    {
        for(int j= i; j <= n; j++)
        {
            f1 +=M[x[j]][1];
            f2[i]= ((f2[i-1] > f1) ? f2[i-1]:f1) + M[x[j]][2];
            f +=f2[i];
            if(f< bestf)                  //完成时间和小于当前最优值
            {
                Swap(x[i],x[j]);
                Backtrack(i+1);
                Swap(x[i],x[j]);
            }
            f1-= M[x[j]][1];
            f-= f2[i];
        }
    }
}
int Flow(int **M, int n, int bestx[])
{
    int ub =INT_MAX;
    Flowshop X;
    //初始化X
    X.x = newint[n+1];
    X.f2 = newint[n+1];
    X.M = M;
    X.n = n;
    X.bestx =bestx;
    X.bestf = ub;
    X.f1 = 0;
    X.f = 0;
    for(int i =0; i <= n; i++)
    {
        X.f2[i] =0;
        X.x[i] =i;
    }
    X.Backtrack(1);
    delete []X.x;
    delete []X.f2;
    returnX.bestf;
}
int main()
{
    int**M,*bestx,n;
    cout<<"输入作业数:"<<endl;
    cin>>n;
    M = newint*[n+1];
    for(int i =1; i <= n; i++)
    {
        M[i] =new int[2];
    }
    for(int k =1; k <= n; k++)
    {
        for(int j= 1; j <= 2; j++)
        {
            cout<<"输入第"<<k<<"个作业在机器"<<j<<"上的处理时间:";
            cin>>M[k][j];
        }
    }
    bestx = newint[n+1];
    for(int t =1; t <= n; t++)
    {
        bestx[t]= 0;
    }
    cout<<"最优完成时间:\n"<<Flow(M,n,bestx)<<endl;
    cout<<"最佳调度方案:"<<endl;
    for(int l =1; l <= n; l++)
    {
        cout<<bestx[l]<<" ";
    }
    cout<<endl;
    return 0;
}
