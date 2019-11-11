TARGET = program
OBJS = main.o hashtable.o scanner.o
CC = gcc
CFLAGS = -I./include -I/usr/local/opt/openssl/include -c -Wall -g
LDFLAGS = -L/usr/local/opt/openssl/lib -lcrypto

$(TARGET) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) $<

clean :
	rm -f $(OBJS) $(TARGET)
