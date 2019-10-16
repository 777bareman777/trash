TARGET=test
OBJS=main.o stack.o infixToPostfix.o sparseMatrix.o circleQueue.o polynomial.o
CC=gcc
CFLAGS=-I./include -c -Wall -g


$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) $<

clean :
	rm -rf $(OBJS) $(TARGET)
