#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
int main(int argc, char* argv[])
{
    
    getchar();
    char * p = (char *) malloc(sizeof(char)*10*1024); 
    printf("%d\n",sizeof(p) );
    getchar();
    return EXIT_SUCCESS;
}

