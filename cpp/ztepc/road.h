#ifndef ROAD_H_INCLUDED
#define ROAD_H_INCLUDED

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <map>
#include <list>
#include <vector>

#include "CArray.h"
#include "config.h"
using namespace std;

struct Road_t{

    int start_id;
    int end_id;
    int road_seq;
    double length;
};
typedef struct Road_t Road;

struct Node_t
{
    int node_seq;

    CArray * road_out ;
    CArray * road_in ;
};
typedef struct Node_t Node;






//初始化 分配内存
void road_create(Road * * road_arr , Node * * node_arr);

void road_init(Road  *road_arr , Node   *node_arr,char * filename);

void road_release(Road * road_arr , Node *  node_arr);

void road_show(Road  *road_arr , Node   *node_arr);

int road_get_real_road_count();
int road_get_real_node_count();


//for test

void road_test();

#endif // ROAD_H_INCLUDED
