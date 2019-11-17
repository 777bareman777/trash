#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>
#include <binary_tree.h>

typedef struct _STACK *pStack;
typedef struct _STACK
{
	pTree *value;
	int top;
	int size;
} Stack;

// 스택 생성 함수
pStack STACKcreate(int size);
// 스택이 가득 차있는지 확인하는 함수
bool STACKisFull(pStack stack);
// 스택이 비어있는지 확인하는 함수
bool STACKisEmpty(pStack stack);
// 스택에 값 넣는 함수
void STACKpush(pStack stack,pTree value);
// 스택에서 값 가져오는 함수
pTree STACKpop(pStack stack);
// 스택 해제 함수
void STACKfree(pStack stack);

#endif
