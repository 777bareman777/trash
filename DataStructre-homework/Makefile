TARGET=test
OBJS=main.o stack.o queue.o linkedlist.o
CC=gcc
CFLAGS=-I./include -c -Wall


$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) $<

clean :
	rm -rf $(OBJS) $(TARGET)
