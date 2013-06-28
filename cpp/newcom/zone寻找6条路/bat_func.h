#ifndef BAT_FUNC_H
#define BAT_FUNC_H

extern char * get_roadfile_name(int line, int direction);
extern char * get_stopfile_name(int line, int direction);
extern int put_roadnode_path(FILE *fp,int line, int direction, int index, int *count, int start, int end);
extern int put_stop_path(int line, int direction, int count_stop);
extern int save_one_line(int line, int direction, int stop_num);
extern int save_lines();


#endif
