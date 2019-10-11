# 컴파일러
CC=gcc
# 컴파일 옵션
CFLAGS=-g -Wall
# 링크 옵션
#LDFLAGS=
# 링크 라이브러리 목록
#LDLIBS=
# Object 파일 목록
OBJS=main.o myfat32.o myparsing.o
# 빌드 대상 이름
TARGET=a.out

all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
