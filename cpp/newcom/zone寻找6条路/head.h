#ifndef HEAD_H
#define HEAD_H


//地图
extern giroad **arr_proad;                        //动态数组的指针，arr_proad[1]指向road_id为1的giroad
extern gikeynode **arr_pkeynode;                  //动态数组的指针，arr_pkeynode[1]指向keynode_id为1的gikeynode
extern giroadnode **arr_proadnode;                //roadnode数组的指针
extern gizone *arr_pzone[ZONE_NUM];
//目标路段
extern gzroad **arr_pzroad;
extern gznode **arr_pznode; 
//公交站点
extern busstop **arr_pstop;


#endif