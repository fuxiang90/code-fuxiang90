# include"AStar.h"
# include"Dijkstra.h"
# include<iostream>
# include<time.h>
using namespace std;


clock_t start;
clock_t end;
double itime ;

int main()
{
	freopen("in.txt","r",stdin);

	AStarEngine * aTest = new AStarEngine();
	cout << "data had read" << endl;

	double Atime = 0.0;
	double Dtime = 0.0;
	int s,e;
	//while(1)
	//{
	//	scanf("%d%d",&s,&e);
	//	if(s == 0 && e ==0)
	//		break;
	//	test->Solve(s,e);
	//}

	DijkstraEngine *dTest = new DijkstraEngine();

	while(scanf("%d%d",&s,&e) != EOF)
	{
		//scanf("%d%d",&s,&e);
		if(s == 0 && e ==0)
			break;
		start = clock();
		dTest->Solve(s,e);
		end = clock();
		Dtime +=(double)(end-start)/CLOCKS_PER_SEC ;

		start = clock();
		aTest->Solve(s,e);
		end = clock();
		Atime += (double)(end-start)/CLOCKS_PER_SEC ;

	}

	cout << "A* : " << Atime << endl << "Dijstra : " << Dtime <<endl;
	//cout << " dijstra runing " << endl;
	return 0;
}
