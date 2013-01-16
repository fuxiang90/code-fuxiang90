# include"common.h"

# include<map>

using namespace std;
class DijkstraEngine
{
public:
	DijkstraEngine()
	{
		getLocationInfo();
		getNodeInfo();


	}

	void Solve(int starti ,int endi )
	{

		if( false == check(starti) || false == check(endi) )
		{
			cout << " the id is not in map"<<endl;
			return ;
		}

		StartNode = starti;
		EndNode = endi;
		int nodeId = 0;
		
		int count = 0;

		bool isfind = false;
		init();
		while ( !nonuseSet.empty() )
		{
			map<int ,double>::iterator iter1;
			nodeId = extraMin();
			
			if(nodeId == -1)
			{
				break;
			}
			useSet.insert(map<int,double>::value_type(nodeId,nonuseSet.find(nodeId)->second));
			nonuseSet.erase(nonuseSet.find(nodeId)); 
			
			count ++;
			if(isTarget(nodeId ,endi))
			{
				isfind = true;
				break;
			}
			map<int ,map<int ,double> >::iterator nodeIter1 = NodeLinkInfoMap.find(nodeId) ;
			map<int ,double > nodelink = nodeIter1->second;
		
			for (  iter1 = nodelink.begin(); iter1 != nodelink.end() ; iter1 ++)
			{
				int nonode = iter1->first;

				// 首先这个节点要不在 useSet 即没有被使用过
				if( useSet.find(nonode) == useSet.end()  ) 
				{
					// start -> nodeid -> nonode ; start -> nonde 
					// m1 is distance of  nodeid -> nonode 
					// m2 is min of start -> nonede
					// m3 is min of start -> nodeid ,this is in useSet
					double m1 ,m2 ,m3;

					//m1 = (nodeIter1->second).find(nonode)->second;
				/*	if( (nodeIter1->second).find(nonode)  != (nodeIter1->second).end())
					{*/
						m1 = (nodeIter1->second).find(nonode)->second;
			/*		}
					else
						m1 = maxDouble;*/
					
					
					
					if ( nonuseSet.find(nonode) == nonuseSet.end())
						m2 = maxDouble;
					else
						m2 = nonuseSet.find(nonode)->second;
					
					if ( useSet.find(nodeId) == useSet.end())
						m3 = maxDouble;
					else
						m3 = useSet.find(nodeId)->second;

					if( m3 + m1 < m2)
					{
						nonuseSet.find(nonode)->second = m3 + m1;
						ParentNode[nonode] = nodeId;
					}

				}//end if


			}//end for

		}//end while

#ifndef CPMTIME
		cout << "Dijstra :" <<endl;
		
		if(isfind == true)
		{
			cout << "Yes you can get  : " << count << endl;
			Path = makePath(endi);

			PrintPath();
		}
		else
		{
			cout << "can not get " << count << endl;
		}
#endif		
		

	}

	void PrintPath()
	{
		list<int>::iterator iter = Path.begin();

		cout<< "The Path is : " ;
		for(;  iter != Path.end() ;iter ++)
		{
			cout << "   " << *iter ;
		}
		cout << endl;
	}


private:
	map< int ,map<int ,double> > NodeLinkInfoMap; // 记录网络的拓扑图的信息 用map 可以更方便的查找
	map< int ,NodeInfo>   NodeInfoMap;  //记录某个节点 的信息
	map< int ,double> useSet;
	map< int ,double> nonuseSet;
	vector<int > ParentNode;
	list<int > Path;
	int StartNode ,EndNode,CountNode;

	double maxDouble;

	void init()
	{
		nonuseSet.erase(nonuseSet.begin(),nonuseSet.end());
		useSet.erase(useSet.begin(),useSet.end());
		ParentNode.erase(ParentNode.begin(),ParentNode.end());
		ParentNode.resize(CountNode + 1);

		Path.erase(Path.begin(),Path.end());
		
		
		map<int ,NodeInfo>::iterator iter;
		maxDouble = 9999999.0;
		
		//useSet.insert(map<int ,double>::value_type(StartNode,0));
		nonuseSet.insert(map<int,double>::value_type(StartNode ,0));
		for( iter = NodeInfoMap.begin() ; iter != NodeInfoMap.end() ; iter ++)
		{
			map<int ,map<int ,double> >::iterator nodeIter1 = NodeLinkInfoMap.find(StartNode) ;
			map<int ,double> link= nodeIter1->second;
			if(StartNode != iter->first  && link.find(iter->first) != link.end())
			{
				nonuseSet.insert(map<int,double>::value_type(iter->first ,link.find(iter->first)->second) );
				ParentNode[iter->first] = StartNode;
			}
			else
				nonuseSet.insert(map<int,double>::value_type(iter->first ,maxDouble) );

		}

	
	}
	int extraMin()
	{
		double  minCost = maxDouble;
		int minId = -1;
		map<int ,double>::iterator iter;
		for(iter = nonuseSet.begin() ;iter != nonuseSet.end(); iter ++)
		{
			if(iter->second < minCost)
			{
				minId = iter->first;
				minCost = iter->second;
			}
		}

		return minId;

	}

	bool  isTarget(int nodei, int endnode)
	{
		if(nodei == endnode)
			return true;
		return false;
	}
	list<int> makePath(int inode)
	{
		int pre = inode;
		Path.push_front(pre);
		while(pre != StartNode)
		{
			pre = ParentNode[pre];
			Path.push_front(pre);			
		}
		return Path;
	}
	bool check(int nodeid)
	{
		if(NodeInfoMap.find(nodeid) == NodeInfoMap.end())
			return false;
		return true;
	}
	void getNodeInfo()
	{
		int isnode ,ienode;
		char *filename = "data-road.txt";
		ifstream inputfile(filename);
		if(!inputfile)
		{
			cout<< "file open error" <<endl;
		}
		while(inputfile >> isnode  >> ienode )
		{
			map<int, map <int,double > >::iterator iter = NodeLinkInfoMap.find(isnode);

			if(iter == NodeLinkInfoMap.end())
			{
				map<int,double> tmp;
				tmp.insert(map<int,double>::value_type(ienode,getCost(isnode,ienode)) );
				NodeLinkInfoMap.insert(map<int,map<int ,double > >::value_type(isnode,tmp ) );
			}
			else
			{
				iter->second.insert(map<int,double>::value_type(ienode,getCost(isnode,ienode)));
			}

			//这里暂且认为 道路是双连通的 即是一个无向图
			iter =  NodeLinkInfoMap.find(ienode);
			if(iter == NodeLinkInfoMap.end())
			{
				map<int,double> tmp;
				tmp.insert(map<int,double>::value_type(isnode,getCost(isnode,ienode)) );
				NodeLinkInfoMap.insert(map<int,map<int ,double > >::value_type(ienode,tmp ) );
			}
			else
			{
				iter->second.insert(map<int,double>::value_type(ienode,getCost(isnode,ienode)));
			}

		}

		//printNodeLinkInfoMap();

		inputfile.close();





	}


	//得到每个节点的坐标
	void getLocationInfo()
	{
		double  x,y;
		int i;
		ifstream inputfile("location.txt");
		if(!inputfile)
		{
			cout << "file  open  error" << endl;
		}

		while(inputfile >> i >> x >> y)
		{
			//map<int ,NodeInfo >::iterator iter = NodeInfoMap.find(i)
			NodeInfo temp(x,y);
			NodeInfoMap.insert(map<int ,NodeInfo>::value_type(i,temp));

			if(CountNode < i)  CountNode = i;//获取数据中最大的节点下表
		}


		inputfile.close();

	}
	double getCost(int nodei ,int enode,int condition = 1)
	{
		NodeInfo inodeInfo = NodeInfoMap.find(nodei)->second;
		NodeInfo jnodeInfo = NodeInfoMap.find(enode)->second;
		double i_x = inodeInfo.x ;double i_y = inodeInfo.y;
		double j_x = jnodeInfo.x ;double j_y= jnodeInfo.y;

		return sqrt((i_x-j_x)*(i_x-j_x) + (i_y-j_y)*(i_y-j_y));

	}

};