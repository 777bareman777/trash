#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stack.h>
#include <infixToPostfix.h>
#include <sparseMatrix.h>
#include <circleQueue.h>
#include <polynomial.h>

int main()
{
	// infixToPostfix 코드 테스트
	/*
	   printpostfix("(((a+b)*c+d-e)/(f+g)-(h+j)*(k-l))/(m-n)");
	   printpostfix("A-B*C");
	   printpostfix("A*B+C");
	   printpostfix("(a+b)*(c-d)/(e+f)");
	   printpostfix("(A+B)*C-D");
	   printpostfix("(A*(B-C/D)+E)/F+G");
	   printpostfix("(((A+B)*C)-D)");
	   */	

	// 희소 행렬 코드 테스트

	/*
	int r,c;
	for(r=10,c=10; r<=10000 && c<=10000;r+=10,c+=10)
	{
		psparseMatrix sm=NULL;
		int **arr=NULL;

		long sum1, sum2;
		struct timespec start,end,gap1,gap2;


		FILE *fp,*fp2;
		char *filename="sparsematrix.csv";
		char *filename2="matrix.csv";
		srand(time(NULL));

		CreateTwoArray(&arr,r,c);
		generateRandomValue(arr,r,c);
		createSparseMatrix(&sm,arr,r,c);

		// 희소 행렬 계산
		clock_gettime(CLOCK_REALTIME,&start);
		sum1=sumSparseMatrix(sm);
		clock_gettime(CLOCK_REALTIME,&end);
		gap1.tv_sec=end.tv_sec-start.tv_sec;
		gap1.tv_nsec=end.tv_nsec-start.tv_nsec;
		if(gap1.tv_nsec<0)
		{
			gap1.tv_sec=gap1.tv_sec-1;
			gap1.tv_nsec=gap1.tv_nsec+10e9;
		}

		// 행렬 계산
		clock_gettime(CLOCK_REALTIME,&start);
		sum2=sumMatrix(arr,r,c);
		clock_gettime(CLOCK_REALTIME,&end);
		gap2.tv_sec=end.tv_sec-start.tv_sec;
		gap2.tv_nsec=end.tv_nsec-start.tv_nsec;
		if(gap2.tv_nsec<0)
		{
			gap2.tv_sec=gap2.tv_sec-1;
			gap2.tv_nsec=gap2.tv_nsec+1000000000;
		}
		//printf("sum1: %ld\tsum2: %ld\n",sum1,sum2);
		printf("행렬 합 시간 : [%010ld.%010ld]\n",gap2.tv_sec,gap2.tv_nsec);
		printf("희소 행렬 합 시간 : [%010ld.%010ld]\n",gap1.tv_sec,gap1.tv_nsec);

		fp=fopen(filename,"a+");
		fp2=fopen(filename2,"a+");
		fprintf(fp,"%d,%010ld.%010ld\n",r*c,gap1.tv_sec,gap1.tv_nsec);
		fprintf(fp2,"%d,%010ld.%010ld\n",r*c,gap2.tv_sec,gap2.tv_nsec);
		fclose(fp); fclose(fp2);

		freeTwoArray(arr,r);
		freeSparseMatrix(sm);
	}
	*/



	// 원형 큐 테스트 20개
	/*	
		pQueue queue=NULL;
		createQueue(&queue,20);

		for(int i=1;i<=30;i++)
		enQueue(queue,i);
		for(int i=0;i<5;i++)
		{
		int result;
		deQueue(queue,&result);
		printf("dequeue: %d\n",result);
		}
		for(int i=11;i<=25;i++)
		enQueue(queue,i);
		for(int i=1;i<=10;i++)
		enQueue(queue,i);

		freeQueue(queue);
		*/

	// 선형 리스트로 구현한 다항식 테스트
	// f(x) = 6.7x^4 + 3.2x^3 - x^2 + x - 2

	/*	
	   poly_list pl=(poly_list)malloc(sizeof(struct _term_node));
	   pl->coef=-2; pl->expon=0; pl->link=NULL;
	   pl=polyAddItem(pl,1,1);
	   pl=polyAddItem(pl,-1,2);
	   pl=polyAddItem(pl,3.2,3);
	   pl=polyAddItem(pl,6.7,4);

	   WriteListItem(pl);

	   FILE *fp;
	   char *filename="poly.csv";
	   fp=fopen(filename,"w+");
	   for(float i=-10;i<=10;i+=0.001)
	   {
	   float result;
	   result=CalculatePolynomial(pl,i);
	   fprintf(fp,"%f,%f\n",i,result);
	   }
	   fclose(fp);

	   {
	   float result;
	   result=CalculatePolynomial(pl,-1.1);
	   printf("result: %f\n",result);
	   }
	*/



	return 0;
}
