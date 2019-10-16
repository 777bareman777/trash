#ifndef _STACK_H_
#define _STACK_H_

#define TRUE 1
#define FALSE 0
#define ERROR -1

typedef int Element;
typedef char boolean;
typedef Element *pElement;
typedef struct _Stack *pStack;
typedef pStack *ppStack;

typedef struct _Stack{
    pElement element;
    int top;
    int size;
} Stack;

// 스택 생성 함수
void stackCreate(ppStack stack, int size);
// 스택이 꽉 차있는지 확인하는 함수
boolean isStackFull(pStack stack);
// 스택이 비어있는지 확인하는 함수
boolean isStackEmpty(pStack stack);
// 스택에 값 넣는 함수
boolean stackPush(pStack stack, Element element);
// 스택에서 값 가져오는 함수
boolean stackPop(pStack stack, pElement result);
// 스택 해제 함수
void stackFree(pStack stack);

#endif
