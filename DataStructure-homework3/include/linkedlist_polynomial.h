#ifndef _LINKEDLIST_POLYNOMIAL_H_
#define _LINKEDLIST_POLYNOMIAL_H_

typedef struct _poly *poly_ptr;
typedef struct _poly {
    float coef;
    int expon;
    poly_ptr link;
} poly;

/////////////////////////////////////////////////////

// 맨 앞에 값 추가
poly_ptr polyAddItem(poly_ptr pl,float coef,int expon);
// expon 값을 가지고 노드 찾기
poly_ptr FindItem(poly_ptr pl, int expon);
// 맨 앞에 값 제거
poly_ptr DeleteFirstItem(poly_ptr pl);
// expon  값을 가지고 제거
poly_ptr DeleteItem(poly_ptr pl, int expon);
// 메모리 제거
poly_ptr MakeListEmpty(poly_ptr pl);
// 리스트 내용 출력
void WriteListItem(poly_ptr pl);

// 다항식 계산
float CalculatePolynomial(poly_ptr pl,float x);

///////////////////////////////////////////////////


//두 다항식의 가감(덧셈, 뺄셈) ADT

// 노드 생성
poly_ptr getNode();

// 노드 추가
void append(float coef,int expon, poly_ptr *pptr);

// 노드 삭제
void erase(poly_ptr *pptr);

// 다항식 덧셈 함수
poly_ptr poly_add(poly_ptr, poly_ptr b);

// 다항식 뺄셈 함수
poly_ptr poly_sub(poly_ptr a, poly_ptr b);

// 지수 비교 함수
int compare(int a,int b);

#endif

