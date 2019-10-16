#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>
#include <infixToPostfix.h>


// 연산자 우선 순위 고려 하지 않은 함수
void postfix1(char* dest, char* src,pStack stack)
{
	int i, index, p;
	for(i=0, index=0; src[i] != '\0';i++)
	{
		switch(src[i])
		{
			case '(':
				break;
			case ')':
				stackPop(stack,&p);
				dest[index]=p; index++;
				break;
			case multiply:
			case divide:
			case add:
			case subtract:
				stackPush(stack,src[i]);
				break;
			default:
				dest[index]=src[i]; index++;
		}
	}
}

// 연산자 우선 순위 고려한 함수
void postfix2(char* dest, char* src,pStack stack)
{
	int i, index, p;
	for(i=0,index=0;src[i]!='\0';i++)
	{
		switch(src[i])
		{
			case '(':
				{
					stackPush(stack,src[i]);

				}
				break;
			case ')':
				{
					while(stackPop(stack,&p))
					{
						if(p == '(')
						{
							break;
						}
						dest[index]=p; index++;
					}
				}
				break;
			case multiply:
			case divide:
			case add:
			case subtract:
				{
					if(stack->top==-1)
						stackPush(stack,src[i]);
					else if(priority(stack->element[stack->top])<priority(src[i]))
						stackPush(stack,src[i]);
					else if (priority(stack->element[stack->top])>=priority(src[i]))
					{
						stackPop(stack,&p);
						dest[index]=p; index++;
						stackPush(stack,src[i]);
					}
				}
				break;
			default:
				{
					dest[index]=src[i]; index++;
				}
				break;        
		}

		// infixToPostfix 코드 테스트
		/*
		for(int j=stack->top;j>-1;j--){
			printf("%c ",stack->element[j]);
		}
		printf("\t->");
		for(int j=0;j<index;j++){
			printf("%c ",dest[j]);
		}
		printf("\n");
		*/
	}

	while( (stack->top) >-1 )
	{
		if(stack->element[stack->top]=='(')
		{
			stackPop(stack,&p);
			continue;
		}
		stackPop(stack,&p);
		dest[index]=p; index++;
	}
}

// 연산자 우선 순위 비교하는 함수
int priority(int operation)
{
	int result;
	switch(operation)
	{
		case '*':
		case '/':
			result=2;
			break;
		case '+':
		case '-':
			result=1;
			break;
		case '(':
			result=0;
			break;
		default:
			result=-1;
	}
	return result;
}

// postfix 출력 값
void printpostfix(const char *str)
{
	char *dest=(char*)calloc(100,sizeof(char));
	char *src=(char*)calloc(100,sizeof(char));
	pStack stack=NULL;

	stackCreate(&stack,100);
	strncpy(src,str,100);
	postfix2(dest,src,stack);
	printf("infix: %s\n",src);
	printf("postfix: %s\n",dest);

	free(dest);
	free(src);
	stackFree(stack);
}
