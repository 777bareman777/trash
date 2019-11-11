TARGET=test
OBJS=main.o polynomial.o array_polynomial1.o array_polynomial2.o
CC=gcc
CFLAGS=-I./include -c -Wall -g


$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) $<

clean :
	rm -rf $(OBJS) $(TARGET)

