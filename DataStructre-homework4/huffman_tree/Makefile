TARGET=program
OBJS=main.o huffman_tree.o
CC=gcc
CFLAGS=-I./include -c -Wall -g


$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) $<

clean :
	rm -rf $(OBJS) $(TARGET)
