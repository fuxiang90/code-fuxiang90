#ifndef STOP_H
#define STOP_H

extern int create_stop_arr();
extern int init_stop(int *pn, char *filename);
extern int clear_stop(int num);
extern int del_stop(int num);

extern int show_stop();
extern int check_stop();

#endif