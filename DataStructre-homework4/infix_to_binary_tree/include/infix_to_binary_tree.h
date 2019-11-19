#ifndef _INFIX_TO_BINARY_TREE_H_
#define _INFIX_TO_BINARY_TREE_H_

#include <binary_tree.h>
#include <stack.h>


// 연산자 상수 정의
#define MULTIPLY '*'
#define DIVIDE '/'
#define ADD '+'
#define SUBTRACT '-'
#define LEFT_BRACKET '('
#define RIGHT_BRACKET ')'

// 우선 순위 값 반환하는 함수
int priority(int op);
// 우선 순위 비교하는 함수
int compare(int op1, int op2);

// infix expression 입력 받는 함수
char *strInput(void);

// infix expression 을 연산자 우선순위 고려해서
// binary tree로 만듬.
pTree createInfixToBinaryTree(void);

void test1();


#endif
