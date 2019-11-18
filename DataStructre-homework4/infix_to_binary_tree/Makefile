TARGET=program
OBJS=main.o binary_tree.o stack.o circle_queue.o infix_to_binary_tree.o 
CC=gcc
CFLAGS=-I./include -c -Wall -g


$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) $<

clean :
	rm -rf $(OBJS) $(TARGET)
