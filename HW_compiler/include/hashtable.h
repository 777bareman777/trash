/*
해시 함수는 임의의 길이의 문자열을 받아서
고정 문자열로 바꾸어주는 함수이다. 함수를
구현하는 방법에 따라서 서로 다른 임의의 문
자열이 같은 고정 문자열이 되기도 하며 이러
한 부분을 충돌이라고 한다.

해시 테이블을 구현할 때 해시 충돌이 일어나
게 되면, Chaining 혹은 Open Addressing 을 통
해서 해결해야 한다.

해시 테이블은 key와 value로 된 쌍을 저장하는
자료 구조이다. 성능이 좋을 때는 O(n) 에 접근
할 수 있기 때문에 공간을 소비해서 접근 속도를 
늘리고 싶을 때 사용한다.

*/
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <openssl/md5.h>

#define MAX_TABLE 1000 			// 테이블 크기
#define MAX_KEY 100 				// 키 크기

// key-value 값을 가지고 있는 node
// 해시 테이블을 구성하는 요소
typedef struct _Node Node;
struct _Node{
	char key[MAX_KEY]; // 토큰 이름
	int value;		   // 토큰 넘버
};

// 초기화 함수
void HTBinit(Node *tb[MAX_TABLE]);

//문자열 복사 및 비교 함수
void HTBStrCpy(char *dest, const char *src);
int HTBStrCmp(const char* dest, const char *src);

// 해시 함수
int HTBhash(const char* str);

// 추가하는 함수
void HTBadd(Node *tb[MAX_TABLE],const char *key, int value);

// 값 찾기 함수
Node *HTBsearch(Node *tb[MAX_TABLE],const char *key);

// 값 삭제 함수
bool HTBdelete(Node *tb[MAX_TABLE],const char *key);

// 출력 함수
void HTBprint_hash(Node *tb[MAX_TABLE]);

int unlink(const char *path);


#endif
