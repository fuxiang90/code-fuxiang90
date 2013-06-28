#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
struct LocRoad_t
{

    int locid;
    int pre_locid; //他的上一个locid
    double  history_road[7][360]; //这条道路 7天历史时刻，每个时间段的平均速度
    double  weights_arr[7][5]; //每个对应一个权值

    std::vector< int > road_seq_vec; // nav road seq


};
struct node_t
{
    int a;
};

struct LocRoad2_t
{

    int locid;
    int pre_locid; //他的上一个locid
    double  ** history_road; //这条道路 7天历史时刻，每个时间段的平均速度
    double  ** weights_arr; //每个对应一个权值

    //std::vector< int > road_seq_vec; // nav road seq


};



void malloc1()
{
    struct LocRoad_t * loc_road_arr = (struct LocRoad_t * )malloc(sizeof(struct LocRoad_t ) * 50000);

    //loc_road_arr[2].road_seq_vec.push_back(2);

    //free(loc_road_arr);

    printf("%d\n",sizeof(struct LocRoad_t));
    printf("debug\n");

}
struct LocRoad2_t * LocRoad2_creat()
{
    struct LocRoad2_t * road =  (struct LocRoad2_t * )malloc(sizeof(struct LocRoad2_t *));

    road->history_road = (double ** )malloc(sizeof(double *) * 7);
    for(int i = 0 ; i < 7 ; i ++){
        road->history_road[i] = (double *) malloc(sizeof( double ) * 720);
    }

     road->weights_arr = (double ** )malloc(sizeof(double *) * 7);

     for(int i = 0 ; i < 7 ; i ++){
        road->history_road[i] = (double *) malloc(sizeof( double ) * 5);
    }

    return road;
}
void malloc2()
{
    struct LocRoad2_t * * loc_road_arr = (struct LocRoad2_t * * )malloc(sizeof(struct LocRoad2_t *) * 50000);

    for(int i = 0 ; i < 50000 ; i ++){
        (loc_road_arr)[i] = LocRoad2_creat();
    }


    printf("debug\n");

}


void vector_malloc()
{
     vector<int> vec;

     for(int i=1;i<=10000;i++)
     {
         vec.push_back(i);
         //cout<<vec.size()<<"  "<<vec.capacity()<<"  "<<vec.max_size()<<endl;
     }
     cout<<endl;


//     cout<<endl;
//     if(true)
//     {
//         vector<int> temp;
//         vec.swap(temp);
//     }
//     cout<<vec.size()<<"  "<<vec.capacity()<<endl;
}

void malloc3()
{
    struct node_t * node_arr = (struct node_t *)malloc(sizeof(struct node_t ) * 3);

    memset(node_arr ,0 ,sizeof(struct node_t) * 3);

    node_arr[2].a = 1;

    printf("%d\n",node_arr[2].a);

    struct node_t * node_arr_2 = (struct node_t *) realloc(node_arr , sizeof(struct node_t ) * 1024 * 130);

    printf("%d\n",node_arr_2[2].a);

    if(node_arr == node_arr_2){
        printf("equl\n");
    }

}
int main()
{

//    for(int i = 0 ; i < 100 ; i ++)
//        vector_malloc();
//    vector < vector <double > > train_data[7];
//    vector<double > data ;
//    vector<double > label[7];
//    data.resize(4);
//
//    data[0] = 1;
//    train_data[0].push_back(data);
//
//
//    malloc1();
//    malloc2();
    fprintf(stderr,"hello\n" );
    malloc3();
	return 0;
}
