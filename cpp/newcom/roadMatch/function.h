#ifndef FUNCTION_H
#define FUNCTION_H

extern int p2seg(double x, double y, const giroadnode *a, const giroadnode *b, double *out_x, double *out_y);
extern double dis(double x1, double y1, double x2, double y2);
extern double dis2(const giroadnode *u, const giroadnode *v);
extern double dis2seg(double x, double y, const giroadnode *u, const giroadnode *v);
extern double dis2line(double x, double y, const giroadnode *u, const giroadnode *v);
extern double get_dis(int start, int end, double x, double y);

extern int get_nearest_road(double x, double y);
extern int get_nearest_roadnode(int id, double x, double y);
extern double get_nearest_dis(int id, double x, double y);
extern double get_nearest_disp(int id, double x, double y, double *out_x, double out_y);
extern int test_nearest();

extern double coordnate2dist(double x1, double y1, double x2, double y2);
extern double sum_dist(int start, int end);
extern int calc_stop();

extern int get_bus_index(int seq);
extern int put_roadnode(FILE *fp, int start, int end);
extern int get_path2next(int index);
extern int calear_result_file();
extern int calear_result_file(char *filename);
extern int get_path(int stop1, int stop2);


// linux 下没有itoa 函数
void itoa(int temp ,char * str ,int jinzhi);

#endif
