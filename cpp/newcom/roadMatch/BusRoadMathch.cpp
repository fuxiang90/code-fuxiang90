
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
    for(i = 1 ; i <= real_road_count ;  i ++){


        if(bus_road_arr[i].road_node_slist->len != 0){
            //Print(bus_road_arr[i].road_node_slist);

            CSlistNode * list_node = bus_road_arr[i].road_node_slist->head;
            int old_roadseq = 0;
            int roadseq = 0;
            printf("%d---------------------------------\n",bus_road_arr[i].roadseq);
            while(list_node){

                //printf("%d\t",( (struct list_t *)(list_node->value) )->roadnode_id );
                roadseq = ( (struct list_t *)(list_node->value) )->roadnode_id;
                //在原来的图中的roadseq
                old_roadseq = get_zone_road(bus_road_node_arr[roadseq].x ,bus_road_node_arr[roadseq].y);

                //printf("%d\t",old_roadseq);
                print_near_road2(3);

//                for(int j = 0 ; j < 6 ; j++)
//                    printf("%d\t",arr_near_road[j]);
//                printf("\n");
                list_node = list_node -> next;

            }

            printf("\n");


        }



    }
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
