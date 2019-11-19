TARGET=program
OBJS=main.o priority_queue.o huffman_tree.o queue.o
CC=gcc
CFLAGS=-I./include -c -Wall -g


$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) $<

clean :
	rm -rf $(OBJS) $(TARGET)
