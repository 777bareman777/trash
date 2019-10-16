#include <stdlib.h>
#include <stack.h>

// 스택 생성 함수
void stackCreate(ppStack stack, int size)
{
    // NULL 경우, 스택 메모리 생성
    if (!(*stack))
    {
        (*stack) = (pStack)malloc(sizeof(Stack));
        (*stack)->element =(pElement)calloc(size,sizeof(Element));
        (*stack)->top = -1;
        (*stack)->size = size;
    }
    // NULL 아닐 경우, 아무런 동작 하지 않음
    else
    {
        return;
    }
}

// 스택이 꽉 차있는지 확인하는 함수
boolean isStackFull(pStack stack)
{
    // NULL 경우, -1 반환
    if (!stack)
        return ERROR;

    // top이 size랑 값이 같을 경우 스택이 꽉참
    if (stack->top == stack->size-1)
        return TRUE;
    else
        return FALSE;
}

// 스택이 비어있는지 확인하는 함수
boolean isStackEmpty(pStack stack)
{
    // NULL 경우, -1 반환
    if (!stack)
        return ERROR;

    // top이 -1일 경우 스택이 비어 있음
    if (stack->top == -1)
        return TRUE;
    else
        return FALSE;
}

// 스택에 값 넣는 함수
boolean stackPush(pStack stack, Element element)
{
    // NULL 경우, -1 반환
    if(!stack)
        return ERROR;
    
    // 스택의 공간이 남아 있으면,
    // 스택의 맨 위에 값 push
    if(!isStackFull(stack))
    {
        stack->top+=1;
        stack->element[stack->top]=element;
    }

    // 스택의 공간이 남아 있지 않으면,
    // 0 반환
    return FALSE;
}

// 스택에서 값 가져오는 함수
boolean stackPop(pStack stack, pElement result)
{
    // NULL 경우, -1 반환
    if(!stack)
        return ERROR;

    // 스택안에 값이 있으면,
    // 스택의 맨 위에 값 pop
    if(!isStackEmpty(stack))
    {
        *result=stack->element[stack->top];
        stack->top-=1;
        return TRUE;
    }

    // 스택의 값이 없으면,
    // 0 반환
    return FALSE;
}

void stackFree(pStack stack)
{
	free(stack->element);
	free(stack);
}
