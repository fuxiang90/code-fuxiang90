/*
 * echoserveri.c - An iterative echo server
 */
/* $begin echoserverimain */
#include "csapp.h"
#include "echo.c"
void echo(int connfd);

int main(int argc, char **argv)
{
    int listenfd, connfd, port, clientlen;
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    static char * post_str = "5555";
    char *haddrp;
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        argv[1] = post_str;
        //exit(0);
    }
    port = atoi(argv[1]);
//    port = 5555;

    listenfd = Open_listenfd(port);
    while (1) {


        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

        int child_id = fork();

        if(child_id == -1){
             fprintf(stderr, "fork error\n");
             exit(0);
        }else if(child_id == 0) {  /*child process */
             /* determine the domain name and IP address of the client */
            hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                           sizeof(clientaddr.sin_addr.s_addr), AF_INET);
            haddrp = inet_ntoa(clientaddr.sin_addr);
            printf("server connected to %s (%s)\n", hp->h_name, haddrp);

            echo(connfd);
            Close(connfd);
            exit(0);

        }else {
            Close(connfd);
        }


    }
    exit(0);
}
/* $end echoserverimain */
