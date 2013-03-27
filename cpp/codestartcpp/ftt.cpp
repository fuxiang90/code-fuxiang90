#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstdlib>

#include<complex>
using namespace std;

const double pi=acos(-1);
const complex<double> I(0,1);
const double eps=1e-8;
int N;
const int MAXL = 1 << 15;
long long L[6][6][MAXL * 4];
int M[10], Y[10][5010];

complex<double> a[4*MAXL],b[4*MAXL];//an-1,an-2,¡­¡­,a1,a0
int n;

void initial(long long* A, long long* B, int LA, int LB)
{
    int nn = max(LA, LB);
    double t=log2(nn);
    int tt=int(t);
    if(t-tt>0)tt++;
    n=1<<(tt+1);//double length
    int i;
    for(i=0; i<LA; i++)a[i]=A[i];
    while(i<n)a[i++]=0;
    for(i=0; i<LB; i++)b[i]=B[i];
    while(i<n)b[i++]=0;
}

void bitReverse(complex<double> * a)
{
    for(int i=1; i<n-1; i++)
    {
        int j=0;
        for(int k=1,tmp=i; k<n; j=((j<<1)|(tmp&1)),k<<=1,tmp>>=1);
        if(j>i)swap(a[i],a[j]);
    }
}
void iterative_FFT(complex<double> *a,int sig)
{
    bitReverse(a);
    for(int m=2; m<=n; m<<=1)//ÊÇ°Ña[]°ŽmµÄ³€¶È·Ö×é£¬
    {
        int mh =m>>1;
        for(int i=0; i<mh; i++)
        {
            complex<double> wi=exp(i*sig*pi/mh*I);
            for(int j=i; j<n; j+=m)
            {
                int k=j+mh;
                complex<double> u=a[j],t=wi*a[k];;
                a[j]=u+t;
                a[k]=u-t;
            }
        }
    }

    if(sig==-1)for(int i=0; i<n; i++)a[i]/=n;
}

void convolution()
{
    iterative_FFT(a,1);
    iterative_FFT(b,1);
    for(int i=0; i<n; i++)a[i]*=b[i];//a*b
    iterative_FFT(a,-1);
}

void output(long long* ans)
{
    //int k=0;
    ans[0]=0;
    for(int i=0; i<MAXL; i++)//
    {
        ans[i] = (long long) round(a[i].real());//four ignore five increase
        // ans[i]+=tmp;
        //if(ans[i])k=i,ans[i+1]=ans[i]/10,ans[i]%=10;
        //else ans[i+1]=0;
    }
    //while(k>=0)cout<<ans[k--];//[0,k]
    //cout<<endl;
}





void MUL(long long * A, long long * B, long long * C, int LB, int LC) {
    initial(B, C, LB, LC);
    convolution();
    output(A);
}


void DFS(int st, int ed) {
    if (st > ed) return;
    memset(L[st][ed], 0, sizeof(L[st][ed]));

    if (st == ed) {
        L[st][ed][0] = 1;
        return;
    }
    if (st == ed - 1) {
        for (int i = 0; i < M[st]; i++) {
            L[st][ed][Y[st][i]]++;
        }
        return;
    }
    int mid = (st + ed) >> 1;
    DFS(st, mid);
    DFS(mid, ed);
    int A, B;
    A = (mid - st) * 5000;
    B = (ed - mid) * 5000;
    MUL(L[st][ed], L[st][mid], L[mid][ed], A + 1, B + 1);

//    for (int i = 0; i < A; i++) if (L[st][mid][i]) {
//        for (int j = 0; j < B; j++) {
//            L[st][ed][i + j] += L[st][mid][i] * L[mid][ed][j];
//        }
//    }
}




int main() {
    // freopen("a.txt", "r", stdin);
    // freopen("o3.txt", "w+", stdout);
    while (scanf("%d", &N) != EOF) {
        for (int i = 0; i < N - 1; i++) {
            scanf("%d", M + i);
            for (int j = 0; j < M[i]; j++)
            {
                scanf("%d", Y[i] + j);
            }
        }

        DFS(0, N - 1);

        for (int i = 0; i <= (N - 1) * 5000; i++) if (L[0][N - 1][i]) {
            printf("%d %lld\n", i, L[0][N - 1][i]);
        }
    }
    //while (1);
}
