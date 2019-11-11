#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <linkedlist_polynomial.h>
#include <array_polynomial1.h>
#include <array_polynomial2.h>

// 선형 리스트를 이용한 두 다항식의 가감 테스트
void test1();
// 첫 번째 배열 자료구조를 이용한 두 다항식 가감 테스트
void test2();
// 두 번째 배열 자료구조를 이용한 두 다항식 가감 테스트
void test3();

// 선형 리스트를 이용한 두 다항식의 가감 테스트 -> 입력해서
void input_test1();
// 첫 번째 배열 자료구조를 이용한 두 다항식 가감 테스트 -> 입력해서
void input_test2();
// 두 번째 배열 자료구조를 이용한 두 다항식 가감 테스트 -> 입력해서
void input_test3();

int main()
{
	srand(time(NULL));

	printf(" 자료 구조를 이용한 두 다항식의 가감 테스트 프로그램\n");
	while(1)
	{
		int index;

		printf("1. 선형 리스트를 이용한 두 다항식의 가감 테스트\n");
		printf("2. 첫 번째 배열 자료구조를 이용한 두 다항식의 가감 테스트\n");
		printf("3. 두 번째 배열 자료구조를 이용한 두 다항식의 가감 테스트\n");
		printf("4. 임의의 값을 집어 넣어서 모든 자료구조에 대한 두 다항식의 가감 테스트\n");
		printf("5. 프로그램 종료\n");
		printf("번호를 입력해주세요 ( 5를 입력시 프로그램 종료): ");
		scanf("%d",&index); getchar();

		switch(index)
		{
			case 1:
				input_test1();
				break;
			case 2:
				input_test2();
				break;
			case 3:
				input_test3();
				break;
			case 4:
				test1();
				test2();
				test3();
				break;
			case 5:
				printf("프로그램 종료\n");
				exit(0);
		}
	}
}

// 선형 리스트를 이용한 두 다항식의 가감 테스트 -> 입력해서
void input_test1()
{
	printf("선형 리스트를 이용한 두 다항식의 가감 테스트\n\n");

	poly_ptr a=NULL;
	poly_ptr b=NULL;
	a=getNode(); b=getNode();


	float coef; int expon;
	printf("a 다항식 입력\n");
	while(1)
	{
		printf("계수, 지수 형태로 입력 ( -1을 입력하기 전까지 ): ");
		scanf("%f %d",&coef,&expon);
		if( (coef == -1 || expon == -1))
			break;
		a=polyAddItem(a,coef,expon);
	}

	printf("b 다항식 입력\n");
	while(1)
	{
		printf("계수, 지수 형태로 입력 ( -1을 입력하기 전까지 ): ");
		scanf("%f %d",&coef,&expon);
		if( (coef == -1 || expon == -1) )
			break;
		b=polyAddItem(b,coef,expon);
	}
	printf("a 다항식 \n");
	WriteListItem(a);
	printf("b 다항식 \n");
	WriteListItem(b);

	poly_ptr result=NULL;

	printf("덧셈결과\n");
	result=poly_add(a,b);
	WriteListItem(result);
	
	printf("뺄셈결과\n");
	result=poly_sub(a,b);
	WriteListItem(result);
	
	printf("\n");
	a=MakeListEmpty(a);
	b=MakeListEmpty(b);
	result=MakeListEmpty(result);
}

// 첫 번째 배열 자료구조를 이용한 두 다항식 가감 테스트 -> 입력해서
void input_test2()
{
	int i;

	printf("첫 번째 배열 자료구조를 이용한 두 다항식 가감 테스트\n\n");

	array_polynomial1 a={0,};
	array_polynomial1 b={0,};
	array_polynomial1 result={0,};

	printf("a 다항식의 최고 차항 값 입력: ");
	scanf("%d",&a.degree);

	printf("b 다항식의 최고 차항 값 입력: ");
	scanf("%d",&b.degree);

	printf("a 다항식의 계수 설정\n");
	for(i=0;i<=a.degree;i++)
	{
		printf("%d 지수에 대한 계수 입력: ",a.degree-i);
		scanf("%f",&a.coef[i]);
	}
	
	printf("b 다항식의 계수 설정\n");
	for(i=0;i<=b.degree;i++)
	{
		printf("%d 지수에 대한 계수 입력: ",b.degree-i);
		scanf("%f",&b.coef[i]);
	}

	printf("a 다항식\n");
	array_polynomial_print1(a);
	printf("b 다항식\n");
	array_polynomial_print1(b);
	printf("덧셈결과\n");
	result=array_poly_add1(a,b);
	array_polynomial_print1(result);
	printf("뺄셈결과\n");
	result=array_poly_sub1(a,b);
	array_polynomial_print1(result);

	printf("\n");
}

// 두 번째 배열 자료구조를 이용한 두 다항식 가감 테스트 -> 입력해서
void input_test3()
{
	printf("두 번째 배열 자료구조를 이용한 두 다항식 가감 테스트\n\n");

	int sp, fp;
	int sq, fq;
	int sr, fr;

	float coef;
	int expon;

	int index;
	index=sp=0;
	array_polynomial2 a[SIZE]={{0,}};

	printf("a 다항식 입력\n");
	while(1)
	{
		printf("계수, 지수 형태로 입력 ( 지수에 0 입력시 종료 ): ");
		scanf("%f %d",&coef, &expon);
		
		a[index].coef=coef;
		a[index].expon=expon;
		index++;

		if(expon == 0)
		{
			fp=index-1;
			sq=index;
			break;
		}
	}

	printf("b 다항식 입력\n");
	while(1)
	{
		printf("계수, 지수 형태로 입력 ( 지수에 0 입력시 종료 ): ");
		scanf("%f %d",&coef,&expon);

		a[index].coef=coef;
		a[index].expon=expon;
		index++;

		if(expon==0)
		{
			fq=index-1;
			break;
		}
	}

	int j;
	printf("a 다항식\n");
	for(j=sp;j<=fp;j++)
	{
		printf("%+.2fx^%d \t",a[j].coef,a[j].expon);
	}
	printf("\n");

	printf("b 다항식\n");
	for(j=sq;j<=fq;j++)
	{
		printf("%+.2fx^%d \t",a[j].coef,a[j].expon);
	}
	printf("\n");

	array_poly_add2(a,sp,fp,sq,fq,&sr,&fr);
	printf("덧셈 결과\n");
	for(j=sr;j<=fr;j++)
	{
		printf("%+.2fx^%d \t",a[j].coef,a[j].expon);
	}
	printf("\n");

	array_poly_sub2(a,sp,fp,sq,fq,&sr,&fr);
	printf("뺄셈 결과\n");
	for(j=sr;j<=fr;j++)
	{
		printf("%+.2fx^%d \t",a[j].coef,a[j].expon);
	}
	printf("\n");
}



// 선형 리스트를 이용한 두 다항식의 가감 테스트
void test1()
{
	printf("\n\n 선형 리스트를 이용한 두 다항식 가감 테스트 시작 \n\n");
	int i;
	for(i=0;i<10;i++)
	{
		poly_ptr a=NULL;
		poly_ptr b=NULL;
		a=getNode(); b=getNode();

		int j;
		int a_expon=0;
		int b_expon=0;
		int tmp1, tmp2;

		a->coef=rand()%100+1;a->expon=a_expon;a->link=NULL;
		b->coef=rand()%100+1;b->expon=b_expon;b->link=NULL;
		for(j=1;j<10;j++)
		{
			tmp1=a_expon;
			tmp2=b_expon;
			do
			{
				a_expon=j*(rand()%4+1);
				b_expon=j*(rand()%4+1);
			} while( tmp1>=a_expon || tmp2>=b_expon );
			a=polyAddItem(a,rand()%100+1,a_expon);
			b=polyAddItem(b,rand()%100+1,b_expon);
		}

		poly_ptr result=NULL;
		result=poly_add(a,b);
		printf("%d 번째 선형 리스트를 이용한 두 두항식의 가감 테스트\n",i+1);
		printf("a 다항식\n");
		WriteListItem(a);
		printf("b 다항식\n");
		WriteListItem(b);
		printf("덧셈 결과\n");
		WriteListItem(result);
		MakeListEmpty(result);
		result=poly_sub(a,b);
		printf("뺄셈 결과\n");
		WriteListItem(result);
		a=MakeListEmpty(a);
		b=MakeListEmpty(b);
		result=MakeListEmpty(result);
		printf("\n");
	}
	printf("\n\n 선형 리스트를 이용한 두 다항식 가감 테스트 끝 \n\n");
}

// 첫 번째 배열 자료구조를 이용한 두 다항식 가감 테스트
void test2()
{
	printf("\n\n 첫 번째 배열 자료구조를 이용한 두 다항식 가감 테스트 시작 \n\n");
	int i;
	for(i=0;i<10;i++)
	{
		array_polynomial1 a={0,};
		array_polynomial1 b={0,};
		array_polynomial1 result;

		a.degree=rand()%MAX_DEGREE;
		b.degree=rand()%MAX_DEGREE;

		int j;
		for(j=0;j<a.degree;j++)
		{
			a.coef[j]=rand()%100;
		}
		for(j=0;j<b.degree;j++)
		{
			b.coef[j]=rand()%100;
		}

		printf("%d 번째 첫 번째 배열 자료구조를 이용한 두 다항식의 가감 테스트\n",i+1);
		printf("a 다항식\n");
		array_polynomial_print1(a);
		printf("b 다항식\n");
		array_polynomial_print1(b);
		printf("덧셈 결과\n");
		result=array_poly_add1(a,b);
		array_polynomial_print1(result);
		printf("뺄셈 결과\n");
		result=array_poly_sub1(a,b);
		array_polynomial_print1(result);

		printf("\n");
	}	
	printf("\n\n 첫 번째 배열 자료구조를 이용한 두 다항식 가감 테스트 끝 \n\n");
}

// 두 번째 배열 자료구조를 이용한 두 다항식 가감 테스트
void test3()
{
	printf("\n\n 두 번째 배열 자료구조를 이용한 두 다항식 가감 테스트 시작 \n\n");
	int i;
	for(i=0;i<10;i++)
	{
		int sp=0, fp=5;
		int sq=fp+1, fq=sq+5;
		int sr, fr;
		array_polynomial2 a[SIZE]={{0,}};

		int j;
		int expon=rand()%100+30;
		for(j=sp; j<=fp;j++)
		{
			a[j].coef=rand()%100;
			a[j].expon=expon;
			expon-=rand()%3+1;
		}
		expon=rand()%100+29;
		for(j=sq;j<=fq;j++)
		{
			a[j].coef=rand()%100;
			a[j].expon=expon;
			expon-=rand()%3+1;

		}

		printf("%d 번째 두 번째 배열 자료구조를 이용한 두 다항식의 가감 테스트\n",i+1);
		printf("a 다항식\n");
		for(j=sp;j<=fp;j++)
		{
			printf("%+.2fx^%d \t",a[j].coef,a[j].expon);
		}
		printf("\n");

		printf("b 다항식\n");
		for(j=sq;j<=fq;j++)
		{
			printf("%+.2fx^%d \t",a[j].coef,a[j].expon);
		}
		printf("\n");

		array_poly_add2(a,sp,fp,sq,fq,&sr,&fr);
		printf("덧셈 결과\n");
		for(j=sr;j<=fr;j++)
		{
			printf("%+.2fx^%d \t",a[j].coef,a[j].expon);
		}
		printf("\n");

		array_poly_sub2(a,sp,fp,sq,fq,&sr,&fr);
		printf("뺄셈 결과\n");
		for(j=sr;j<=fr;j++)
		{
			printf("%+.2fx^%d \t",a[j].coef,a[j].expon);
		}
		printf("\n");

	}

	printf("\n\n 두 번째 배열 자료구조를 이용한 두 다항식 가감 테스트 끝 \n\n");
}
