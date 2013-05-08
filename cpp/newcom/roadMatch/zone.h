#ifndef ZONE_H
#define ZONE_H

extern int init_zone(int num);
extern int del_zone();
extern int show_zone_con();
extern int get_zone_road(double x, double y);
extern int test_zone();

// add by fuxiang
extern void  count_dx_dy();

extern int print_near_road2(int n);


int get_zone_road(double x, double y ,double * min_dist);
//得到第K个最匹配的路
int get_near_k_road(int kth = 1);

#endif
