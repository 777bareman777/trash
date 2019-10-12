#include <linkedlist.h>

#ifndef _STACK_H_
#define _STACK_H_

// 데이터 구조체 정의
typedef int Element; /* 노드의 데이터 타입 */
typedef char boolean; /* 논리 데이터 타입*/
typedef struct _Stack *pStack; /* struct _Stack 포인터 */
typedef pStack *ppStack; /* struct _Stack 이중 포인터 */

typedef struct _Stack{ /* 스택 구조체 */
    pNode top;
    int size;
} Stack;

// 프로토 타입 함수 정의
void createStack(ppStack stack); // 스택 초기화
void freeStack(pStack stack); // 스택 메모리 해제
void destroyStack(pStack stack); // 스택 메모리 제거
boolean isStackEmpty(pStack stack); // 스택이 비어있는지 확인
void pushStack(pStack stack, Element element); // 스택 값 push
Element popStack(pStack stack); // 스택 값 pop

#endif
