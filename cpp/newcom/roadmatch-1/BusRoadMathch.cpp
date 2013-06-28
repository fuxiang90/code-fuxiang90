
#include "BusRoadMatch.h"


static const char * BUS_ROAD_FILE = "../roadid_GIROAD.txt" ;
static const char * BUS_KEYNODE_FILE = "../roadid_GINODE.txt";
static const char * BUS_ROADNODE_FILE = "../roadid_GIROADNODE.txt";


static const int MAX_BUS_ROAD = 35000;
static const int MAX_BUS_ROAD_NODE = 200000;

static  struct roadnode * bus_road_node_arr;
static  BusRoad *  bus_road_arr;


static int real_road_count ;
void bus_road_mathch_init()
{
    bus_road_node_arr = (struct roadnode *) malloc(sizeof(struct roadnode )* MAX_BUS_ROAD_NODE);

    if(bus_road_node_arr == NULL){
        printf("error\n");
        exit(-1);
    }

    bus_road_arr = (BusRoad *)malloc(sizeof(roadnode) * MAX_BUS_ROAD);

     if(bus_road_arr == NULL){
        printf("error\n");
        exit(-1);
    }


}

void bus_road_match_input()
{
    FILE * fin;
    fin = fopen(BUS_ROAD_FILE ,"r");
    if(fin == NULL){
        printf("打开文件%s失败\n", BUS_ROAD_FILE);
		exit(-1);
    }


    int roadseq;
    int roadid;
    int t1,t2;
    double len;
    real_road_count = 0;
    while(fscanf(fin,"%d%d%d%lf%d",&roadseq ,&t1,&t2,&len,&roadid) != EOF ){
        bus_road_arr[roadseq].roadseq = roadseq;
        bus_road_arr[roadseq].roadid = roadid;
        bus_road_arr[roadseq].road_node_slist = CSlistCreate();

        if(real_road_count < roadseq) real_road_count = roadseq;

    }

    fclose(fin);



    fin = fopen(BUS_ROADNODE_FILE,"r");

    int roadnodeid;
    double x;
    double y;//玮度
    double t3;

    while(fscanf(fin ,"%d%lf%lf%lf%d",&roadseq ,&x,&y,&t3,&roadnodeid ) != EOF){
        bus_road_node_arr[roadnodeid].id = roadnodeid;
        bus_road_node_arr[roadnodeid].x = x;
        bus_road_node_arr[roadnodeid].y = y;
        bus_road_node_arr[roadnodeid].roadid = roadseq;

        struct list_t * new_int = (struct list_t  *)malloc(sizeof(struct list_t));
        new_int->roadnode_id = roadnodeid;

        CSlistAddNodeTail ( bus_road_arr[roadseq].road_node_slist,new_int );

        //bus_road_arr[roadseq].road_node_vec.push_back(roadnodeid);


    }
}

void bus_road_match_work()
{
    int i;

    double d_x;
    double d_y;

    FILE * fout;
    fout = fopen("./data/result","w");
    if(fout == NULL){
        printf("file open error");
        exit(-1);
    }

    //fprintf(fout,"\t%d\t%d\t%lf\n" );
    for(i = 1 ; i <= real_road_count ;  i ++){

        if(bus_road_arr[i].road_node_slist->len != 0){
            //Print(bus_road_arr[i].road_node_slist);

            CSlistNode * list_node = bus_road_arr[i].road_node_slist->head;

            CSlistNode * pre_node = NULL;
            CSlistNode * next_node = NULL;
            int old_roadseq = 0;
            int roadseq = 0;
           // printf("%d---------------------------------\n",bus_road_arr[i].roadseq);

            int roadnode_count = bus_road_arr[i].road_node_slist->len ;
            int * roadseq_arr = (int *)malloc(sizeof(int)*roadnode_count);

            int roadseq_arr_pos = 0;
            while(list_node){

                //printf("%d\t",( (struct list_t *)(list_node->value) )->roadnode_id );
                roadseq = ( (struct list_t *)(list_node->value) )->roadnode_id;
                //在原来的图中的roadseq

                next_node = list_node->next;

                if(pre_node == NULL && next_node != NULL){ //第一个点
                    get_delta_x_y(list_node ,next_node , &d_x ,&d_y,1);
                }else if(next_node == NULL){//最后一个点
                    get_delta_x_y(pre_node ,list_node , &d_x ,&d_y,2);
                }else {// 中间点
                    //get_delta_x_y(pre_node ,list_node , &d_x ,&d_y,1);
                    d_x = 0.0;
                    d_y = 0.0;
                }

                old_roadseq = get_zone_road(bus_road_node_arr[roadseq].x + d_x ,bus_road_node_arr[roadseq].y + d_y);

                print_near_road2(3);

                roadseq_arr[roadseq_arr_pos++] = get_near_k_road(1);

                pre_node = list_node;
                list_node = list_node -> next;

            }
            int times;
            int max_times_roadseq = get_max_times(roadseq_arr,roadnode_count,&times);
            //printf("max_num is %d and %.4lf\n ", max_times_roadseq ,times*1.0/roadnode_count);

            //bus_road_arr[i].roadid =
            fprintf(fout,"%d\t%d\t%d\t%lf\n" ,
                bus_road_arr[i].roadseq ,bus_road_arr[i].roadid, max_times_roadseq  , times*1.0/roadnode_count);
            free(roadseq_arr);
            printf("\n");


        }



    }//end for

    fclose(fout);
}

void bus_road_match_show()
{
    int i;
    for(i = 1 ; i <= real_road_count ;  i ++){


        printf("%d---------------------------------\n",bus_road_arr[i].roadseq);
        if(bus_road_arr[i].road_node_slist->len != 0){
            Print(bus_road_arr[i].road_node_slist);

        }

        printf("\n");
//        if(bus_road_arr[i].road_node_vec.size()){
//            int j ;
//            int len = bus_road_arr[i].road_node_vec.size();
//            for(j = 0 ; j <len ; j++){
//                printf("%d\t",bus_road_arr[i].road_node_vec[j]);
//            }
//
//        }
//        printf("\n");


    }

}
void bus_road_match_testmain()
{
    bus_road_mathch_init();
    bus_road_match_input();

   // bus_road_match_show();

   bus_road_match_work();

}

static void Print(CSlist * l)
{
    CSlistNode *list_node = l->head;
    while(list_node){

        printf("%d\t",( (struct list_t *)(list_node->value) )->roadnode_id );

        list_node = list_node -> next;

    }
}

void bus_road_match_free()
{

}

static void get_delta_x_y(CSlistNode * first_node , CSlistNode * end_node ,double * dx ,double *dy ,int flag  )
{
    if(first_node== NULL || end_node == NULL  ){
        printf("ptr is null\n");
        exit(-1);
    }
    int first_node_id = ( (struct list_t *)(first_node->value) )->roadnode_id;
    int end_node_id = ( (struct list_t *)(end_node->value) )->roadnode_id ;


    double delta_x =  bus_road_node_arr[end_node_id].x - bus_road_node_arr[first_node_id].x;
    double delta_y =  bus_road_node_arr[end_node_id].y - bus_road_node_arr[first_node_id].y;


    //当处理的点不是最后一个点的时候
    if(flag == 1){
        (*dx) = delta_x/2;
        (*dy) = delta_y/2;
    }else {
        (*dx) = -1*delta_x/2;
        (*dy) = -1*delta_y/2;
    }

}
int  int_cmp(const void * a ,const void * b)
{
    return *(int *)(a) <  *(int*)(b);
}
static int get_max_times(int * arr ,int len ,int * times)
{

    int max_times = 0;
    int max_num = -1;

    qsort(arr,len,sizeof(int),int_cmp );

    for(int i = 0 ; i < len ; i ++){
        int j = i;
        while((i+1) < len && arr[i] ==  arr[i+1]){
            i ++;
        }

        if(i - j > max_times){
            max_times = i -j + 1;
            max_num = arr[j];
            //i ;
        }
    }

    (*times) =  max_times;
    return max_num;



}
