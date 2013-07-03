#include "dijkstra.h"

void dijkstra_create(Road * * road_arr , Node * * node_arr)
{
    road_create(road_arr ,node_arr );
    char * filename = INPUT_FILE;
    road_init(*road_arr ,*node_arr ,filename);
}

int dijkstra_path(Road * road_arr , Node * node_arr ,int src ,int dest,int * *path)
{

    int road_count = road_get_real_road_count() + 1;
    int node_count = road_get_real_node_count() + 1;

    double * open_dist = (double *) malloc(node_count * sizeof(double ));
    int * used = (int *) malloc(node_count * sizeof(int ));
    int * parent = (int *) malloc(node_count * sizeof(int ));
    (*path) = (int *) malloc(node_count * sizeof(int ));
    if(open_dist == NULL  || used == NULL  || parent == NULL){
        fprintf(stdout ,"dijkstra_path memmory error\n");
        exit(0);
    }
    memset(used ,0,node_count * sizeof(int ));
    memset(parent ,0,node_count * sizeof(int ));
    memset(open_dist ,0,node_count * sizeof(double ));

    for(int i = 1 ; i < node_count ; i ++){
        open_dist[i] = 1000000000.0;
    }

    for(unsigned int i = 0 ; i < node_arr[src].road_out->len ; i++){
        //if(node_arr[i].road_out -> len == 0) continue;

        int road_seq =( ( int *)(node_arr[src].road_out->data) )[i] ;
        int end_node = road_arr[ road_seq ].end_id;
        open_dist[end_node] = road_arr[ road_seq ].length;
    }
    used[src] = 1;

    for(int i = 1 ; i < node_count -1 ; i ++){

        // get the min dist
        int min_pos = 0;
        int min_dist = 1000000000.0;
        for(int j = 1 ; j < node_count ; j ++){
            if(used[j] == 0 && open_dist [j] < min_dist ){
                min_pos = j;
                min_dist = open_dist [j];
            }
        }
        if(min_pos == 0) break;
        used[min_pos] = 1;
        for(unsigned int j = 0  ; j < node_arr[min_pos].road_out->len ; j ++){
            int road_seq =( ( int *)(node_arr[min_pos].road_out->data) )[j] ;
            int end_node = road_arr[ road_seq ].end_id;

            double length = road_arr[ road_seq ].length;

            if(open_dist[end_node]  > length +open_dist[min_pos]){
                open_dist[end_node]  = length +open_dist[min_pos] ;
                parent[end_node]  = min_pos ;
            }
        }

        if(min_pos == dest ) break;
    }

    int id = dest;
    int path_id = 0;

    (*path)[path_id ++] = dest;
    while(parent[id]){
        (*path)[path_id ] = parent[id];
        path_id ++;
        id = parent[id] ;
    }

    return path_id;

}
int dijkstra_release(Road * road_arr , Node * node_arr)
{
    road_release(road_arr , node_arr);

}
void dijkstra_test()
{

    Road * road_arr;
    Node * node_arr ;

    dijkstra_create(&road_arr ,&node_arr);
    int *path;
    dijkstra_path(road_arr ,node_arr ,20,32,&path);

    free(path);

}
