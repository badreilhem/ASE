CC = gcc
CFLAGS = -m32 

all : switchto.o pingpong

pingpong : 
	$(CC) $(CFLAGS) switchto.o pingpong.c -o pingpong

switchto.o : 
	$(CC) $(CFLAGS) switchto.h -c switchto.c 

clean :
	rm pingpong *.o *~ 
	
