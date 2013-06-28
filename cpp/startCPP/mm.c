#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <mm.h>
int main(int argc, char* argv[])
{
// 创建 10KB 内存池 (最小小 8192),"abc" 是创建锁定标识文文件名。
    MM* pool = mm_create(1024 * 40, "abc");
// 锁定池,在当前⺫目目录下创建 abc.sem 文文件。
    mm_lock(pool, MM_LOCK_RW);
// 在池内分配内存块。
    int* x = mm_malloc(pool, sizeof(int));
    *x = 1234;
// 获取池内分配的某个块大大小小。
    printf("%p = %d\n", x, mm_sizeof(pool, x));
// 显式整个池状态信息。
    mm_display_info(pool);
    printf("max:%d, avail:%d\n", mm_maxsize(), mm_available(pool));
    getchar();
// 删除 abc.sem,解除锁定。
    mm_unlock(pool);
// 释放整个池。
    mm_destroy(pool);
    return EXIT_SUCCESS;
}
