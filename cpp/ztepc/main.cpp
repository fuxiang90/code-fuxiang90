#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "road.h"
#include "dijkstra.h"

#include "dijkstra_heap.h"
using namespace std;



int main(int argc, char* argv[] )
{
    int src;
    int dest ;
    char * file_in;
    char * file_out ;
    int flag = 0;
    for (int i = 1 ; i < argc ; i ++){
        if(argv[i][1] == 's' ){
            src = atoi(argv[i] + 2 );
        }else if(argv[i][1] == 'd' ){
            dest = atoi(argv[i] + 2 );
        }else if(argv[i][1] == 'f' ){
            file_in = &(argv[i][2]);
        }else if(argv[i][1] == 'o' ){
            file_out = &(argv[i][2]);
        }else if(argv[i][1] == 'c' ){
            flag = atoi(argv[i] + 2 );
        }
    }

    //printf("%d %d %d %s %s",src ,dest,flag ,file_in ,file_out);

    //

    // src = 20;
    // dest = 32;
    // flag = 2;
    // file_in = "in" ;
    // file_out = "out";
   dijkstra_main(src,dest,flag,file_in,file_out);
//    dijkstra_main(src,dest,flag,"in","out");
//    dijkstra_heap_main(src,dest,flag,file_in,file_out);
    // dijkstra_heap_test();
    cout << "Hello world!" << endl;
    return 0;
}


