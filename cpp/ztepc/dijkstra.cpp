#include "dijkstra.h"

 int s_flag = 0;
 int * s_path = NULL;

void dijkstra_create(Road * * road_arr , Node * * node_arr ,char * filename)
{
    road_create(road_arr ,node_arr );
    //char * filename = INPUT_FILE;
    road_init(*road_arr ,*node_arr ,filename);
}

int dijkstra_path(Road * road_arr , Node * node_arr ,int src ,int dest,int * *path)
{

    int road_count = road_get_real_road_count() + 1;
    int node_count = road_get_real_node_count() + 1;
    int is_find_dest = 0;
    double * open_dist = (double *) malloc(node_count * sizeof(double ));
    int * used = (int *) malloc(node_count * sizeof(int ));
    int * parent = (int *) malloc(node_count * sizeof(int ));
    (*path) = (int *) malloc(node_count * sizeof(int ));
    if(open_dist == NULL  || used == NULL  || parent == NULL) {
        fprintf(stdout ,"dijkstra_path memmory error\n");
        exit(0);
    }
    memset(used ,0,node_count * sizeof(int ));
    memset(parent ,0,node_count * sizeof(int ));
    memset(open_dist ,0,node_count * sizeof(double ));


    for(int i = 1 ; i < node_count ; i ++) {
        open_dist[i] = MAX_DIST;
    }

    /*把一些节点设置为不能经过*/
    if(s_flag == 1 && s_path != NULL) {
        for(int i = 1 ; s_path[i] != dest && s_path[i] != 0  ; i ++) {
            used[s_path[i]] = 1;
        }
    }

    for(unsigned int i = 0 ; i < node_arr[src].road_out->len ; i++) {
        //if(node_arr[i].road_out -> len == 0) continue;

        int road_seq =( ( int *)(node_arr[src].road_out->data) )[i] ;
        int end_node = road_arr[ road_seq ].end_id;
        open_dist[end_node] = road_arr[ road_seq ].length;
    }
    used[src] = 1;

    for(int i = 1 ; i < node_count -1 ; i ++) {

        // get the min dist
        int min_pos = 0;
        int min_dist = MAX_DIST;
        for(int j = 1 ; j < node_count ; j ++) {
            if(used[j] == 0 && open_dist [j] < min_dist ) {
                min_pos = j;
                min_dist = open_dist [j];
            }
        }
        if(min_pos == 0) break;
        used[min_pos] = 1;
        for(unsigned int j = 0  ; j < node_arr[min_pos].road_out->len ; j ++) {
            int road_seq =( ( int *)(node_arr[min_pos].road_out->data) )[j] ;
            int end_node = road_arr[ road_seq ].end_id;

            double length = road_arr[ road_seq ].length;

            if(open_dist[end_node]  > length + open_dist[min_pos]) {
                open_dist[end_node]  = length + open_dist[min_pos] ;
                parent[end_node]  = min_pos ;
            }
        }

        if(min_pos == dest ) {
            is_find_dest = 1;
            break;
        }
    }

    int id = dest;
    int path_id = 0;

    //如果找到了
    if (is_find_dest == 1) {
        (*path)[path_id ++] = dest;
        while(parent[id]) {
            (*path)[path_id ] = parent[id];
            path_id ++;
            id = parent[id] ;
        }
        (*path)[path_id ++] = src;
        //swap 数组前后倒置 ，使起点是第一个
        for(int i = 0 ; i < path_id/2 ; i++) {
            int t = (*path)[i];
            (*path)[i] = (*path)[path_id - i - 1];
            (*path)[path_id - i - 1] = t;
        }
    }



    free(used);
    free(open_dist);
    free(parent);
    return path_id;

}
int dijkstra_backup_path(   Road * road_arr ,
                            Node * node_arr ,
                            int src ,
                            int dest ,
                            int * path  ,
                            int n ,
                            int * * back_path,
                            int flag )
{

    if(flag == 2)
        road_update(road_arr , node_arr ,path ,n );
    else if (flag == 1) {
        s_flag = 1;
        s_path = path;
    }

    int backup_road_len = dijkstra_path(road_arr , node_arr ,src,dest ,back_path );


    return  backup_road_len ;

}
int dijkstra_release(Road * road_arr , Node * node_arr)
{
    road_release(road_arr , node_arr);

}
void dijkstra_main(int src ,int dest ,int flag ,char * file_in ,char *file_out )
{
    Road * road_arr;
    Node * node_arr ;

    dijkstra_create(&road_arr ,&node_arr ,file_in);


    int *path;
    int path_len = dijkstra_path(road_arr ,node_arr ,src,dest,&path);

    int * backup_path ;

    int backup_path_len = dijkstra_backup_path(road_arr ,node_arr ,src,dest ,path,path_len,&backup_path ,flag );

    //backup_path_len = dijkstra_backup_path(road_arr ,node_arr ,20,32 ,path,path_len,&backup_path ,1 );

    FILE *fout = fopen(file_out ,"w");
    fprintf(fout ,"main:");
    for(int i =  0 ; i < path_len ; i ++) {
        fprintf(fout ," %d",path[i]);
    }
    fprintf(fout ,"\nbackup:");
    for(int i =  0 ; i < backup_path_len ; i ++) {
        fprintf(fout ," %d",backup_path[i]);
    }
    fclose(fout);

    free(backup_path);
    free(path);
}
void dijkstra_test()
{

    Road * road_arr;
    Node * node_arr ;

    dijkstra_create(&road_arr ,&node_arr ,INPUT_FILE);
    int *path;
    int path_len = dijkstra_path(road_arr ,node_arr ,20,32,&path);

    int * backup_path ;

    int backup_path_len = dijkstra_backup_path(road_arr ,node_arr ,20,32 ,path,path_len,&backup_path ,2 );

    //backup_path_len = dijkstra_backup_path(road_arr ,node_arr ,20,32 ,path,path_len,&backup_path ,1 );


    free(backup_path);
    free(path);

}
