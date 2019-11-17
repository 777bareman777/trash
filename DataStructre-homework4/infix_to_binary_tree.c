#include <stdio.h>
#include <stdlib.h>
#include <infix_to_binary_tree.h>

// infix expression 입력 받는 함수
char *strInput(void)
{
	char *str=(char*)calloc(100,sizeof(char));
	if(str==NULL)
	{
		fprintf(stderr,"메모리가 부족합니다\n");
		return NULL;
	}
	printf("Input infix expression(length 100): ");
	scanf("%100s",str);

	return str;
}

// 우선 순위 비교하는 함수
int priority(int op)
{
	int result;
	switch(op)
	{
		case MULTIPLY:
		case DIVIDE:
			result=2;
			break;
		case ADD:
		case SUBTRACT:
			result=1;
			break;
		case RIGHT_BRACKET:
		case LEFT_BRACKET:
			result=0;
			break;
		default:
			result=-1;
	}
	return result;
}

// 우선 순위 비교하는 함수
int compare(int op1, int op2)
{
	int result1, result2;
	result1=priority(op1);
	result2=priority(op2);

	return result1-result2;
}

// infix expression 을 연산자 우선순위를 고려해서
// binary tree로 만듬.
pTree createInfixToBinaryTree(void)
{
	pTree root=NULL;
	pStack operatorStack=NULL;
	pStack operandStack=NULL;

	operatorStack=STACKcreate(100);
	operandStack=STACKcreate(100);

	char *str=strInput();

	int i;
	pTree cur=NULL;
	for(i=0; str[i]!='\0';i++)
	{
		switch(str[i])
		{
			// '(' 일때
			case LEFT_BRACKET:
				{
					pTree tmp=BT_createNode();
					tmp->value=str[i];
					STACKpush(operatorStack,tmp);
				}
				break;
			// ')' 일때
			case RIGHT_BRACKET:
				{
					while( (cur=STACKpop(operatorStack)) != NULL )
					{
						if(cur->value == LEFT_BRACKET)
						{
							break;
						}

						pTree operand2=STACKpop(operandStack);
						pTree operand1=STACKpop(operandStack);

						cur->left=operand1;
						cur->right=operand2;
						STACKpush(operandStack,cur);

					}
				}
				break;
			// 산술 연산자 일때
			case MULTIPLY:
			case DIVIDE:
			case ADD:
			case SUBTRACT:
				{
					// 비어있을 때
					if(STACKisEmpty(operatorStack))
					{
						pTree tmp=BT_createNode();
						tmp->value=str[i];
						STACKpush(operatorStack,tmp);
					}
					// 스택에 있는 연산자보다 입력된 연산자 우선순위가 클 때,
					else if(compare(operatorStack->value[operatorStack->top]->value,str[i])<0)
					{
						pTree tmp=BT_createNode();
						tmp->value=str[i];
						STACKpush(operatorStack,tmp);
					}
					// 스택에 있는 연산자보다 입력된 연산자
					// 우선순위가  작을 때 또는 같을 때,
					else
					{
						pTree operand2=STACKpop(operandStack);
						pTree operand1=STACKpop(operandStack);
						pTree head=STACKpop(operatorStack);
						
						pTree tmp=BT_createNode();
						tmp->value=str[i];
						STACKpush(operatorStack,tmp);

						head->left=operand1;
						head->right=operand2;
						STACKpush(operandStack,head);
					}
				}
				break;
			default:
				{
					pTree tmp=BT_createNode();
					tmp->value=str[i];
					STACKpush(operandStack,tmp);
				}
		}
	}


	while( STACKisEmpty(operandStack) != true && STACKisEmpty(operatorStack) != true)
	{
		cur=STACKpop(operatorStack);
		if(cur->value == LEFT_BRACKET)
			continue;

		pTree operand2=STACKpop(operandStack);
		pTree operand1=STACKpop(operandStack);
		
		cur->left=operand1;
		cur->right=operand2;
		STACKpush(operandStack,cur);
	}
	root=cur;

	free(str);
	return root;
}

