#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sparseMatrix.h>

// 희소 행렬 생성 함수
void createSparseMatrix(ppsparseMatrix matrix,int **arr,int rows, int cols)
{
    // NULL 아닐 경우, 아무런 동작 하지 않음.
    if((*matrix))
        return ;

    int r,c,index=1,size=0;
    
    for(r=0;r<rows;r++)
    {
        for(int c=0;c<cols;c++)
            {
                if( arr[r][c] != 0)
                    size++;
            }
    }

    *matrix=(psparseMatrix)calloc(size+1,sizeof(sparseMatrix));
    (*matrix+0)->row=rows;
    (*matrix+0)->col=cols;
    (*matrix+0)->value=size;

    for(r=0;r<rows;r++)
    {
        for(c=0;c<cols;c++)
        {
            if(arr[r][c]!=0)
                {
                    (*matrix+index)->row=r;
                    (*matrix+index)->col=c;
                    (*matrix+index)->value=(*(*(arr+r)+c));
                    index++;
                }
        }
    }
}

//희소 행렬 해제 함수
void
freeSparseMatrix(psparseMatrix matrix)
{
    if(!matrix)
        return ;
    
    free(matrix);
}


// 랜덤하게 값 생성하는 함수
// 10퍼센트만 값을 채움
void
generateRandomValue(int **arr, int rows, int cols)
{
    int r,c,k=0;
    int count=(float)rows*cols*0.1;

    for(r=0;r<rows;r++){
        for(c=0;c<cols;c++)
        {
            if(rand()%10==0 && (k < count ))
            {
                *(*(arr+r)+c)=rand()%10000;
                k++;
            }
            else
            {
                *(*(arr+r)+c)=0;
            }
        }
    }
}

// 이차원 배열 동적 할당 함수
void
CreateTwoArray(int ***arr, int rows, int cols)
{
    // NULL 아닐 경우, 아무런 동작 하지 않음
    if ((*arr))
        return ;

    int i;
    *arr=(int **)malloc(sizeof(int *)*rows);
    for(i=0;i<rows;i++)
        *(*arr+i)=(int*)calloc(cols,sizeof(int));
}

// 이차원 배열 동적 해제 함수
void
freeTwoArray(int **arr, int rows)
{
    //  NULL 일 경우 아무런 동작 하지 않음
    if (!arr)
        return ;

    int i;
    for(i=0;i<rows;i++)
        free(*(arr+i));
    free(arr);
}

// 희소 행렬 내 모든 합
long
sumSparseMatrix(psparseMatrix matrix)
{
	int i;
	long sum=0;
	int size=(matrix+0)->value;	

	for(i=1;i<=size;i++)
		sum+=(matrix+i)->value;

	return sum;
}

// 행렬 내 모든 합
long
sumMatrix(int **arr,int rows,int cols)
{
	int r,c;
	long sum=0;

	for(r=0;r<rows;r++)
	{
		for(c=0;c<cols;c++)
		{
			sum+=arr[r][c];
		}
	}
	
	return sum;
}

