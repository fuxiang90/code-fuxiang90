#ifndef AIM_H
#define AIM_H


extern int create_aimroad_arr();
extern int init_aimroad(int *pn, char *filename);
extern int del_aimroad(int num);
extern int create_zroad_arr();
extern int create_znode_arr();
extern int clear_zroad(int num);
extern int clear_znode();
extern int del_zroad(int num);
extern int del_znode();
extern int get_road_startnode();
extern int show_aimroad();
extern int show_aimroad2();
extern int sort_aimroad();

#endif