#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include "road.h"

#define MAX_DIST 1000000000.0


 extern int s_flag ;
 extern int * s_path ;
/*
    从文件中读取道路拓扑结果
*/
void dijkstra_create(Road * * road_arr , Node * * node_arr, char * filename);

/*
dijkstra 算法的实现 结果保存在 path 中 返回path 的大小
*/
int dijkstra_path(Road * road_arr , Node * node_arr ,int src ,int dest ,int * *path);

/*
在已经得到一条主路径的情况下，再去计算一条备选路径
path  是主路径

返回backup的长度
*/
int dijkstra_backup_path(  Road * road_arr ,
                            Node * node_arr ,
                            int src ,
                            int dest ,
                            int * path  ,
                            int n ,
                            int * * back_path,
                            int flag );

int dijkstra_release(Road * road_arr , Node * node_arr);

void dijkstra_main(int src ,int dest ,int flag ,char * file_in ,char *file_out );

//void dijkstra_store_path(int * path ,int )
//
void dijkstra_test();
#endif // DIJKSTRA_H_INCLUDED
