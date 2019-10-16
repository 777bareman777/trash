#ifndef _INFIXTOPOSTFIX_H_
#define _INFIXTOPOSTFIX_H_

/*
Problem 4: Infix 표현을 Postfix로 변환시키는 프로그램을 설계하고 구현하시 오.
1
• 스택의 함수 구현
• 5개 이상의 Infix 표현을 Postfix로 변환한 결과
*/

// 연산자 상수 정의
#define multiply '*'
#define divide '/'
#define add '+'
#define subtract '-'

// 연산자 우선 순위 고려 하지 않은 함수
void postfix1(char* dest, char* src,pStack stack);
// 연산자 우선 순위 고려한 함수
void postfix2(char* dest, char* src,pStack stack);
// 연산자 우선 순위 비교하는 함수
int priority(int operation);

// postfix 출력
void printpostfix(const char* str);


#endif
