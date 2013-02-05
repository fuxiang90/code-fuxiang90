#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
using namespace  std;
int ans = 0 ; //用来统计比较的次数


void swap(int *a ,int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

//用第一个元素做为分割点
int partition1(int *data ,int s ,int e)
{
	int x = data[s];
	int j = s;
	int i = 0;
	for(i = s +1 ; i <= e ; i ++)
	{
		if(data[i]  < x)
		{
			j ++;
			swap(&data[i],&data[j]);
		}
	}
	swap(&data[s],&data[j]);
	return j;

}
//用最后一个元素做为分割点
int partition2(int *data ,int s ,int e)
{
	int x = data[e];
	int j = s-1;
	int i = 0;
	for(i = s  ; i < e ; i ++)
	{
		if(data[i]  < x)
		{
			j ++;
			swap(&data[i],&data[j]);
		}
	}
	swap(&data[e],&data[j+1]);
	return j + 1;

}
void quicksort(int *data ,int s,int e)
{
	if(s < e)
	{
		ans += e-s;
		swap(&data[s],&data[e]);
		int p  = partition1(data,s,e);
		/*quicksort(data,s,p);
		quicksort(data,p +1 ,e);*/

		quicksort(data,s,p-1);
		quicksort(data,p +1 ,e);


	}
}

int find_mid(int *data ,int s,int e)
{
	int temp[3] = {0};
	temp[0] = data[s];
	temp[1] = data[(s+e)/2];
	temp[2] = data[e];
	sort(temp,temp+3);
	int mid;
	if(temp[1] == data[s])
		mid = s;
	else if(temp[1] == data[e])
		mid = e;
	else
		mid = (s+e)/2;
	return mid;

}
//快速排序 随机化 ，然后这里我们选择
//using the "median-of-three" pivot rule
void quicksort_rand(int *data ,int s,int e)
{		
	int temp[3] = {0};
	if(s < e)
	{
		
		int mid = find_mid(data,s,e); // 找出三个数字中处于中间数的下标
		
		swap(&data[s],&data[mid]) ;//将他和第一个数交换 这样可以重用 partition1 函数		
		ans += e-s;
		int p  = partition1(data,s,e);
		quicksort_rand(data,s,p-1);
		quicksort_rand(data,p+1 ,e);
	}
}

void init()
{


}
int main()
{
	//int data[9] = {0,2,8,7,1,3,5,6,4};

	freopen("out","w",stdout);
	int data[10000 + 10] = {0};
	FILE *fp  = fopen("QuickSort.txt","r");
	int i = 0;
	// while(fscanf(fp,"%d",&data[i++]) != EOF) 
	//一个隐藏的bug  ，QuickSort文件中是有 10000 个数字，按照我最初的想法，结束后i = 10000，但是这样的写法是i= 10001；
	//因为在最后读取文件末尾的时候 i ++ 仍被执行了一次
	while(fscanf(fp,"%d",&data[i]) != EOF) 
	{
		i ++;
	}
	//quicksort(data,0,i-1);
	quicksort_rand(data,0,i-1);
	int len  = i-1;
	for(i = 0 ; i <= len   ; i ++)
	{

		printf("%d\n",data[i]);
	}
	printf("%d",ans);
	//fclose(fp)
	return 0;
}
