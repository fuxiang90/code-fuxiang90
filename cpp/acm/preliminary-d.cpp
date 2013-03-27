#include <set>
#include <map>
#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 110;
 struct node{
    double x,y;
} ;
typedef struct node Point;
Point data[N];
Point data2[N];
double mul_(Point p1,Point p2,Point p0)
{
    return((p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y));
}

double distance_(Point p1,Point p2)
{
    return(sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)));
}
double polygonarea(Point *polygon,int N)
{
    int i,j;
    double area = 0;

    for (i=0;i<N;i++) {
        j = (i + 1) % N;
        area += polygon[i].x * polygon[j].y;
        area -= polygon[i].y * polygon[j].x;
        }

    area /= 2;
    return(area < 0 ? -area : area);
}
void Graham_scan(Point PointSet[],Point ch[],int n,int &len)
{
    int i,j,k=0,top=2;
    Point tmp;

   for(i=1;i<n;i++)
    if ((PointSet[i].y<PointSet[k].y)||((PointSet[i].y==PointSet[k].y)&&(PointSet[i].x<PointSet[k].x)))
    k=i;
    tmp=PointSet[0];
    PointSet[0]=PointSet[k];
    PointSet[k]=tmp;
    for (i=1;i<n-1;i++)
        {
        k=i;
        for (j=i+1;j<n;j++)
            if ( (mul_(PointSet[j],PointSet[k],PointSet[0])>0) ||
                     ((mul_(PointSet[j],PointSet[k],PointSet[0])==0)
                         &&(distance_(PointSet[0],PointSet[j])<distance_(PointSet[0],PointSet[k])))   )
                k=j;
        tmp=PointSet[i];
        PointSet[i]=PointSet[k];
        PointSet[k]=tmp;
        }
    ch[0]=PointSet[0];
    ch[1]=PointSet[1];
    ch[2]=PointSet[2];
    for (i=3;i<n;i++)
        {
        while (mul_(PointSet[i],ch[top],ch[top-1])>=0) top--;
        ch[++top]=PointSet[i];
        }
    len=top+1;
}

int n;

int main()
{
    freopen("in","r",stdin);
    while(cin>>n){

        for(int i = 0 ; i <= n -1 ; i ++){

            cin>>data[i].x >> data[i].y;
        }
        int len = n;
        Graham_scan(data,data2,n,len);
        double d = polygonarea(data,len );
        printf("%.1lf\n",d);
        //cout << polygonarea(data,n )<<endl;

    }

}
