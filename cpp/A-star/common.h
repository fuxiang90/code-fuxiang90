#ifndef COMMON_H
#define COMMON_H


//# define CPMTIME 0
# include<iostream>
# include<list>
# include<algorithm>
# include<vector>
# include<set>
# include<map>
# include<fstream>
# include<cmath>
using namespace std;




struct NodeEntityInfo
{
	int Id;
	int StartId;
	int EndId;
	int Length;
	int Classic;
	int Direct;
};



class CostNode
{
public:
	int p;
	double sum;// 总的花费
	double dist;// 已经花费的
	CostNode(int _p,double _dist,double _sum = 0.0)
	{
		this->p = _p;
		this->dist = _dist;
		this->sum = _sum;
	}
	void toCostNode(int _p,double _dist,double _sum = 0.0)
	{
		this->p = _p;
		this->dist = _dist;
		this->sum = _sum;
	}

};
class NodeInfo
{
public:
	double x;
	double y;
	int Direct;
	NodeInfo(double x,double y,int direct = 1)
	{
		this->x = x;
		this->y = y;
		this->Direct = direct;
	}
};

#endif