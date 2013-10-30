CC=gcc
CFLAGS=-c
LD=ld
LIB=libadd.so

main: main.o  
	$(CC)  main.o -L./lib -ladd -o main


#add.o:
#	$(CC) $(CFLAGS) add.c -o add.o 

main.o:
	$(CC) $(CFLAGS) main.c  -o main.o
	#$(CC) $(CFLAGS) main.c  -L$(LIB) -ladd -o main.o

lib:
	$(LD) -share -o $(LIB) add.o 

