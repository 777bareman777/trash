#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

typedef struct _poly *poly_ptr;
typedef struct _poly {
    float coef;
    int expon;
    poly_ptr link;
} poly;

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

#endif

