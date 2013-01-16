# include"common.h"
class AStarEngine
{
public:

	AStarEngine()
	{
		getNodeInfo();
		getLocationInfo();
	}
	
	//得到要道路拓扑节点的信息
	
	list<NodeInfo> Execute(NodeInfo startnode ,NodeInfo endnode, int Condition)
	{

	}
	void Solve(int starti,int endi)
	{
	
		if( false == check(starti) || false == check(endi) )
		{
			cout << " the id is not in map"<<endl;
			return ;
		}

		StartNode = starti;EndNode  = endi;

		bool noFindFlag = true;
		int p = starti;
		double cost = getCost(p,endi);
		CostNode costnode(p,0,cost);
		
		
		int count = 0;
		init();
		//首先要把startnode 放到close 集合中
		//closeSet.insert(starti);
		openSet.insert(map<int,CostNode>::value_type(p,costnode));
		ParentNode[p] = p;
		while(noFindFlag)
		{
			/*extendRoad(p);	
			if( openSet.empty() )
			{
				cout << "can not get" << endl;
				return ;
			}
			int besti = getBest();

			if(isTarget(besti,endi) )
			{
				noFindFlag =  false;
			}
			
			p = besti;
			closeSet.insert(besti);
			openSet.erase(besti);*/

			if( openSet.empty() )
			{
				break;
			}

			int besti =getBest();
			map<int ,CostNode>::iterator iter = openSet.find(besti);
			closeSet.insert(map<int ,CostNode >::value_type(besti,iter->second) );
			if(isTarget(besti,endi) )
			{
				noFindFlag =  false;
			}
			extendRoad(besti);
			
			openSet.erase(besti);//
			count ++;

		}
#ifndef CPMTIME
		cout << "A* :" <<endl;
		if(noFindFlag == false)
		{
			cout << "Yes you can get  : " << count << endl;
			makePath(EndNode);
			PrintPath();
		}
		else 
		{
			cout << "can not get it : "<< count  << endl;
		}
#endif
		

	}
	void PrintPath()
	{
		list<int>::iterator iter = Path.begin();

		cout << "The Path is : " ;
		for(;  iter != Path.end() ;iter ++)
		{
			cout << "   " << *iter ;
		}
		cout << endl;
	}
 
	

private:
	map< int ,list<int> > NodeLinkInfoMap;
	map< int ,NodeInfo>   NodeInfoMap;
	map< int ,CostNode> openSet;
	vector<int > ParentNode;
	list<int > Path;
	int StartNode ,EndNode,CountNode;
	//map< int ,CostNode> closeSet;
	map<int ,CostNode> closeSet;

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
			map<int, list <int > >::iterator iter = NodeLinkInfoMap.find(isnode);

			if(iter == NodeLinkInfoMap.end())
			{
				list<int> tmp(1,ienode);
				NodeLinkInfoMap.insert(map<int,list<int> > ::value_type(isnode,tmp ) );
			}
			else
			{
				iter->second.push_back(ienode);
			}

			//这里暂且认为 道路是双连通的 即是一个无向图
			iter =  NodeLinkInfoMap.find(ienode);
			if(iter == NodeLinkInfoMap.end())
			{
				list<int> tmp(1,isnode);
				NodeLinkInfoMap.insert(map<int,list<int> > ::value_type(ienode,tmp ) );
			}
			else
			{
				iter->second.push_back(isnode);
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

	
	bool check(int nodeid)
	{
		if(NodeInfoMap.find(nodeid) == NodeInfoMap.end())
			return false;
		return true;
	}
	void printNodeLinkInfoMap()
	{
		map<int, list <int > >::iterator iter2 = NodeLinkInfoMap.begin();
		while(iter2 != NodeLinkInfoMap.end())
		{
			cout << iter2->first ;
			//for_each(iter2->second.begin(),iter2->second.end(),print);
			list<int>::iterator liter = iter2->second.begin();
			while(liter != iter2->second.end())
			{
				cout << *liter++ ;

			}
			cout <<endl;
			iter2 ++;
		}
	}
	bool  isTarget(int nodei, int endnode)
	{
		if(nodei == endnode)
			return true;
		return false;
	}
	
	void init()
	{
		closeSet.erase(closeSet.begin(),closeSet.end());
		openSet.erase(openSet.begin(),openSet.end());
		ParentNode.erase(ParentNode.begin(),ParentNode.end());
		ParentNode.resize(CountNode);

		Path.erase(Path.begin(),Path.end());
	}

	//这个用来扩展从该节点可以到达的所有结果
	void extendRoad(int nodei)
	{
		map<int ,list<int > >::iterator iter = NodeLinkInfoMap.find(nodei);
		if (iter == NodeLinkInfoMap.end())
		{
			return ;
		}

		list<int>::iterator liter = iter->second.begin();

		map<int ,CostNode>::iterator openiter = openSet.find(nodei);
		map<int ,CostNode>::iterator closeiter ;
		CostNode prenode(0,0,0); 
		if(openiter  == openSet.end())
		{
			prenode.toCostNode(nodei,getCost(nodei,StartNode),getCost(nodei,EndNode));
		}
		else 
			prenode = openiter->second ;


		for(; liter != iter->second.end() ;  liter ++)
		{
			int tnode = *liter;
			CostNode tmpNode(nodei,prenode.dist + getCost(nodei,tnode),prenode.dist + getCost(nodei,tnode)+ getCost(tnode,EndNode));
			if(closeSet.find(tnode)  == closeSet.end())
			{
				openiter = openSet.find(tnode);
				if(openiter == openSet.end())
				{
					openSet.insert( map<int ,CostNode>::value_type(tnode,tmpNode));
					ParentNode[tnode] = nodei;
				}
				else //如果 tnode 在openSet 中已经存在
				{
					//如果原来的花费 要大于现在的花费 ，那么就需要更新
					if(openiter->second.sum  > tmpNode.sum )
					{
						openiter->second.dist = tmpNode.dist;
						openiter->second.sum = tmpNode.sum;
						openiter->second.p = tmpNode.p;
						ParentNode[tnode] = nodei;
					}
				}

				
			}
			else
			{
				//如过tnode 在closeSet 中，那如果tnode 要由于之前的closeSet ，那么把这个节点从closeset 中删除，并加入到openSet 中去
				closeiter = closeSet.find(tnode);
				if(tmpNode.sum < closeiter->second.sum)
				{
					closeSet.erase(closeiter);
					openSet.insert(map<int ,CostNode>::value_type(tnode,tmpNode) );
					ParentNode[tnode] = nodei;
				}
				
			}


		}
	}

	double getCost(int nodei ,int enode,int condition = 1)
	{
		NodeInfo inodeInfo = NodeInfoMap.find(nodei)->second;
		NodeInfo jnodeInfo = NodeInfoMap.find(enode)->second;
		double i_x = inodeInfo.x ;double i_y = inodeInfo.y;
		double j_x = jnodeInfo.x ;double j_y= jnodeInfo.y;

		return sqrt((i_x-j_x)*(i_x-j_x) + (i_y-j_y)*(i_y-j_y));

	}
	int getBest()
	{
		int besti = 0;
		double bestvalue  = 999999999.9;

		map<int ,CostNode>::iterator iter = openSet.begin();
		for( ; iter != openSet.end() ; iter ++)
		{
			if(iter->second.sum  < bestvalue)
			{
				bestvalue = iter->second.sum;
				besti = iter->first;
			}
		}
		return besti;		
	}





	list<int> getPath(int enode)
	{

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

};







////一个简单的A星算法，
//class AStarEngineSimple
//{
//public:
//	
//	//得到要道路拓扑节点的信息
//	void GetNodeInfo()
//	{
//		fp = ostream("map","r");
//		while()
//	}
//	List<NodeInfo> Execute(NodeInfo startnode ,NodeInfo endnode, int Condition)
//	{
//
//	}
//private:
//	int countNode;
//	set<struct NodeInfo> openset;
//	set<struct NodeInfo> closeset;
//	list<struct NodeInfo> path;
//	vector< vector <int > > graph;
//	struct NodeInfo startnode;
//	struct NodeInfo endnode;
//
//	bool  IsTarget(struct NodeInfo node,struct NodeInfo Endnode)
//	{
//		if(node.x == Endnode.x  && node.y == Endnode.y)
//			return true;
//
//		return false;
//	}
//	bool Check(int x ,int y)
//	{
//		if(x >= 0 && x < countNode && y >=0 && y < countNode)
//			return true;
//
//		return false;
//	}
//
//	//这个用来扩展从该节点可以到达的所有结果
//	void Extend_road(struct NodeInfo node)
//	{
//		从8个方向
//		int dx[8] = (-1, 0, 1, -1, 1, -1, 0, 1)
//        int dy[8] = (-1,-1,-1,  0, 0,  1, 1, 1)
//		int x = node.x;
//		int y = node.y;
//		int nx,ny;
//		for(int i = 0 ; i < 8 ; i ++)
//		{
//			nx = x + dx[i];
//			ny = y + dy[i];
//			struct NodeInfo newNode = new NodeInfo(nx,ny);
//			if(graph[nx][ny] == 1 && Check(nx,ny) && !closeset.find(newNode) )
//			{				
//				openset.insert(newNode);
//			}
//		}
//
//	}
//
//
//}