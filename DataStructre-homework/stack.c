#include <stdlib.h>
#include <stack.h>


// 스택 초기화 함수
void createStack(ppStack stack)
{
    *stack = (pStack)malloc(sizeof(stack));
    (*stack)->top = NULL;
    (*stack)->size=0;
}

// 스택 값 push
void pushStack(pStack stack, Element element)
{
    // 스택이 NULL 이면, 값을 push 하지 않음.
    if (!stack)
        return ;

    // 노드 생성
    pNode n;
    createNode(&n,element);
    
    // 스택에 값 push
    n->link = stack->top; // 이전 node를 가리키도록 설정
    stack->top = n; // 스택의 탑 새로 생성한 node를 가리키도록 설정
    stack->size+=1; // 스택 크기 증가
}

// 스택 값 pop
Element popStack(pStack stack)
{
    pNode n;
    Element element;

    // 스택이 비어있는지 확인
    // 비어있다면, 0의 값을 꺼냄
    if(isStackEmpty(stack))
    {
        return 0;
    }

    n=stack->top; // n을 top 으로 설정
    element=n->element; // n의 element를 꺼냄
    stack->top=n->link; // top을 n의 이전 node로 설정
    freeNode(n); // 사용한 node 메모리 해제
    stack->size-=1; // 스택 크기 감소
    return element; 
}

// 스택이 비어있는지 확인
boolean isStackEmpty(pStack stack)
{
    return stack->top == NULL; // 스택이 비어있을 경우 1을 반환, 아닐 경우 0을 반환
}

// 스택 메모리 해제
void freeStack(pStack stack)
{
    if(!stack) return; // 메모리가 제거된 상태

    while(stack->size != 0)
    {
        pNode n=stack->top; // 스택의 탑의 현재 위치 저장
        stack->top=n->link; // 스택의 탑을 이전 node로 변경
        stack->size-=1; // 스택 크기 감소
        freeNode(n); // 사용한 노드 메모리 해제
    }
    stack->top=NULL; // 스택의 탑을 NULL로 설정
}

// 스택 메모리 제거
void destroyStack(pStack stack)
{
    freeStack(stack);
    if(!stack) return ; // 메모리가 제거된 상태
    free(stack);
    stack=NULL; 
}
