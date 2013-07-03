#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include "road.h"

void dijkstra_create(Road * * road_arr , Node * * node_arr);

int dijkstra_path(Road * road_arr , Node * node_arr ,int src ,int dest ,int * *path);

int dijkstra_release(Road * road_arr , Node * node_arr);

//
void dijkstra_test();
#endif // DIJKSTRA_H_INCLUDED
