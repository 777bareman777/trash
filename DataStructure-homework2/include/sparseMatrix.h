#ifndef _SPARSEMATRIX_H_
#define _SPARSEMATRIX_H_

/*
Problem 3: 주어진 희소행열을 표현하기 위한 적합한 자료구조를 기술하고 행열 내 모든 값의 합을 구하는 독립된 함수를 작성하시오.
1. 정수값을 입력 받아 희소행렬의 크기를 결정
2. 주어진행렬내원소의약10%이하가0이아닌값으로임의수를생성
하여 대입
3. 계산결과의 비교
*/

/*
    cols[0] -> 행의 크기
    rows[0] -> 열의 크기
    value[0] -> 행렬 안에 있는 값의 개수
 */
typedef struct _sparseMatrix{
    int col;
    int row;
    int value;
} sparseMatrix, *psparseMatrix,**ppsparseMatrix;


// 희소 행렬 생성 함수
void 
createSparseMatrix(ppsparseMatrix matrix, int** arr,int rows, int cols);
// 희소 행렬 해제 함수
void
freeSparseMatrix(psparseMatrix matrix);


// 랜덤하게 값 생성하는 함수
// 10퍼센트만 값을 채움
void
generateRandomValue(int **arr , int rows, int cols);

// 이차원 배열 동적 할당 함수
void CreateTwoArray(int ***arr, int rows , int cols) ;
// 이차원 배열 동적 해제 함수
void freeTwoArray(int **arr,int rows);

// 희소 행렬 내 모든 합
long
sumSparseMatrix(psparseMatrix matrix);

// 행렬 내 모든 합
long
sumMatrix(int ** arr, int rows, int cols);


#endif
