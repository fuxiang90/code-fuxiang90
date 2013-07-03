#include <queue>
#include "road.h"

static  int real_road_count = 0;
static  int real_key_node_count = 0;

int road_get_real_road_count()
{
    return real_road_count;
}
int road_get_real_node_count()
{
    return real_key_node_count ;
}


void road_init(Road * road_arr , Node   *node_arr ,char * filename)
{

    FILE * fin = fopen(filename ,"r");

    int road_seq = 1;
    int node_start;
    int node_end;
    char  str[1024] ;
    fgets( str ,1023 ,fin );
    while(fscanf(fin,"%d,%d",&node_start,&node_end) != EOF) {

        road_arr[road_seq].road_seq  = road_seq;
        road_arr[road_seq].start_id = node_start;
        road_arr[road_seq].end_id = node_end;
        road_arr[road_seq].length = 1;


        CArrayPush ( node_arr[node_start].road_out , &road_seq);


        CArrayPush ( node_arr[node_end].road_in , &road_seq);

        road_seq ++;
        real_road_count ++;

        if(real_key_node_count < node_start )
            real_key_node_count = node_start;
        if(real_key_node_count < node_end)
            real_key_node_count = node_end;
    }

    for(int i = 0 ; i <= real_key_node_count ; i ++){
        node_arr[i].node_seq = i;
    }




    fclose(fin);
    return ;


}

void road_create(Road * * road_arr , Node * * node_arr)
{

    (*road_arr) = (Road *)malloc(sizeof(Road)*MAX_ROAD);



    if((*road_arr) == NULL) {
        printf("memory error\n");
        exit(0);
    }
    memset(*road_arr,0,sizeof(Road)*MAX_ROAD);


    (*node_arr) = (Node *)malloc(sizeof(Node)*MAX_KEY_NODE);
    if((*node_arr) == NULL) {
        printf("memory error\n");
        exit(0);
    }
    memset(*node_arr , 0, sizeof(Node)*MAX_KEY_NODE);
    for(int i = 0 ; i < MAX_KEY_NODE ; i ++){
        (*node_arr) [i].road_out =CArrayCreate(10 ,sizeof(int));
        (*node_arr) [i].road_in =CArrayCreate(10 ,sizeof(int));
    }

}
void road_release(Road * road_arr , Node *  node_arr)
{

    free(road_arr);
    road_arr = NULL;

    for(int i = 0 ; i < MAX_KEY_NODE ; i ++ ){
        CArrayRelease(node_arr[i].road_in);
        CArrayRelease(node_arr[i].road_out);

    }
    free(node_arr);
    node_arr = NULL;
}
void road_show(Road  *road_arr , Node   *node_arr)
{
     for(int i = 0 ; i < MAX_KEY_NODE ; i ++ ){
        if(node_arr[i].road_out->len )
            printf("%d \n",  road_arr [( ( int *)(node_arr[i].road_out->data) )[0] ].start_id);

    }

}
void road_test()
{
    Road * road_arr;
    Node * node_arr ;

    char * filename = INPUT_FILE;

    road_create(&road_arr ,&node_arr);
    road_init(road_arr ,node_arr ,filename);

    road_show(road_arr ,node_arr );
}
