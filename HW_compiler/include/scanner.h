#ifndef _SCANNER_H_
#define _SCANNER_H_
#include <hashtable.h>


typedef enum _clangKeywordIndex
{
	_ASM=1, 	// => 인라인 어셈블리 코드를 나타내는 키워드
	_AUTO=2, 		// => 기본적인 변수의 저장 방식을 지정하는 키워드
	_BREAK=3,		// => 반복문을 조건 없이 마치는 명령어
	_CASE=4,		// => swtich 문 내에서 사용되는 명령어
	_CHAR=5, 		// => 가장 간단한 데티어형
	_CONST=6,		// => 변수가 변경되지 않도록 방지하는 데이터 지정자
	_CONTINUE=7, 	// => 반복문을 다음 반복 동작을 진행시키는 명령어
	_DEFAULT=8,	// => case 문에 일치하지 않는 경우를 처리하기 위해 switch 문에서 사용되는 명령어
	_DO=9,		// => while문과 함께 사용되는 순환 명령어.
	_DOUBLE=10,	// => 배정도 부동 소수형 값을 저장할 수 있는 데이터형
	_ELSE=11,		// => if문이 FALSE로 평가될 때 실행되는 선택적인 문장을 나타내는 명령어
	_EXTERN=12,	// => 변수가 프로그램의 다른 부분에서 선언되었다는 것을 알려주는 데이터 지정자
	_FLOAT=13, 	// => 부동소수형 숫자 값을 저장하기 위해 사용되는 데이터형
	_FOR=14,		// => 초기화, 증가, 조건 부분을 가지는 순환 명령어
	_GOTO=15,		// => 정의되어 있는 레이블로 이동시키는 명령어
	_IF=16,		// => TRUE/FALSE의 결과에 따라 프로그램의 제어를 변경하는데 사용되는 명령어
	_INT=17,		// => 정수형 값을 저장하는데 사용되는 데이터형
	_LONG=18,		// => int형보다 큰 정수형 값을 저장하는데 사용되는 데이터형
	_REGISTER=19, 	// => 가능하다면 변수를 레지스터에 저장하도록 지정하는 저장형태 지정자
	_RETURN=20,	// => 현재의 함수를 마치고 호출한 함수로 프로그램의 제어를 돌려주는 함수, 함수 값을 돌려주기위해 사용됨.
	_SHORT=21,		// => 정수형 값을 저장하는데 사용되는 데이터형.
	_SIGNED=22,	// => 변수가 양수와 음수값을 모두 저장할 수 있다는 지정자
	_SIZEOF=23,	// => 항목의 크기를 바이트 단위로 알려주는 연산자
	_STATIC=24,	// => 컴파일러가 변수의 값을 보존해야 한다는 것을 지정한느데 사용되는 지정자
	_STRUCT=25,	// => C에서 어떤 데이터형의 변수를 함께 결합시키는데 사용되는 키워드
	_SWITCH=26,	// => 여러가지 조건을 통해서 프로그램의 흐름을 변경하는데 사용되는 명령, case문과 함께 사용됨.
	_TYPEDEF=27,	// => 이미 존재하는 변수와 함수의 형태를 새로운 이름으로 변경하ㅡㄴ데 사용되는 지정자
	_UNION=28,		// => 여러 개의 변수가 동일한 메모리 영역을 공유하도록 해주는데 사용되는 키워드
	_UNSIGNED=29,	// => 변수가 양수 값만을 저장할수 있다는 것을 지정하는데 사용되는 지정자
	_VOID=30,		// => 함수가 어떤 값을 돌려주지 않거나 또는 사용되는 포인터가 범용포인터 이거나, 모든 데이터형을 지적할 수 있다는 것을 지정하는데 사용되는 키워드
	_VOLATILE=31,	// => 변수가 변경될 수 있다는 것을 나타내는 지정자
	_WHILE=32,		// => 지정된 조건이 TRUE로 평가되는 한 계속해서 포함된 문장을 실행하는 순환문
	_ENUM=33,
	_ENUM_COUNT_KEYWORD=34 // => enum 타입의 갯수

} ClangKeywordIndex;

typedef enum _clangOperationIndex
{
	// 우선순위 1 , 왼쪽에서 오른쪽
	_POSTFIX_INCREMENT=50, 	// 후위 증가
	_POSTFIX_DECREMENT=51,		// 후위 감소
	_FUNCTION_CALL=52,			// 함수 호출
	_ARRAY_SUBSCRIPTING=53,		// 배열 첨자
	_DOT=54,					// 구조체/유니온 접근자
	_ARROW=55,					// 구조체/유니온 포인터 접근자
	_COMPOUND_LITERAL=56,		// 복합 리터럴

	// 우선순위 2, 오른쪽에서 왼쪽
	_PREFIX_INCREMENT=57,		// 전위 증가
	_PREFIX_DECREMENT=58,		// 전위 감소
	_UNARY_PLUS=59,			// 단항 덧셈(양의 부호)
	_UNARY_MINUS=60,			// 단항 뺄셈(음의 부호)
	_LOGICAL_NOT=61,			// 논리 NOT
	_BITWISE_NOT=62,			// 비트 NOT
	_TYPE_CAST=63,				// 타입 캐스팅
	_INDIRECTION=64,			// 포인터 역참조
	_ADDRESS_OF=65,			// 주소 연산자
	_SIZE_OF=66,				// 자료형의 크기
	_ALIGNO_OF=67,				// Aligment requirement

	// 우선순위 3, 왼쪽에서 오른쪽
	_MULTIPLICATION=68,		// 곱하기
	_DIVISION=69,				// 나눗셈
	_REMAINDER=70,				// 나머지연산자

	// 우선순위 4, 왼쪽에서 오른쪽
	_ADDITION=71,				// 덧셈	
	_SUBTRACTION=72,			// 뺄셈

	// 우선순위 5, 왼쪽에서 오른쪽
	_BITWISE_LEFT_SHIFT=73,	// 비트를 왼쪽으로 시프트
	_BITWISE_RIGHT_SHIFT=74,	// 비트를 오른쪽으로 시프트
	
	// 우선순위 6, 왼쪽에서 오른쪽
	_LESS=75,					// 작음, <
	_LSEE_EQUAL=76,			// 작거나 같음, <=
	_GREATER=77,				// 큼, >
	_GREATER_EQUAL=78,			// 크거나 같음,	 >=

	// 우선순위 7, 왼쪽에서 오른쪽
	_EQUAL_EQUAL=79,			// 같음, ==
	_EXCLAM_EQUAL=80,			// 다름, !=

	// 우선순위 8, 왼쪽에서 오른쪽
	_BITWISE_AND=81,			// 비트 AND
	
	// 우선순위 9, 왼쪽에서 오른쪽
	_BITWISE_XOR=82,			// 비트 XOR

	// 우선순위 10, 왼쪽에서 오른쪽
	_BITWISE_OR=83,			// 비트 OR

	// 우선순위 11, 왼쪽에서 오른쪽
	_LOGICAL_AND=84,			// 논리 AND

	// 우선순위 12, 왼쪽에서 오른쪽
	_LOGICAL_OR=85,			// 논리 OR

	// 우선순위 13, 오른쪽에서 왼쪽
	_TERNARY_CONDITIONAL=86,	// 삼항 연산자, ?:
	
	// 우선순위 14, 오른쪽에서 왼쪽
	_SIMPLE_ASSIGNMENT=87,					// 할당,대입
	_ASSIGNMENT_BY_SUN=88,					// 덧셈 후 할당
	_ASSIGNMENT_BY_DIFFERENCE=89,			// 뺼셈 후 할당
	_ASSIGNMENT_BY_PRODUCT=90,				// 곱셈 후 할당
	_ASSIGNMENT_BY_QUOTIENT=91,			// 나눗셈 후 할당
	_ASSIGNMENT_BY_REMAINDER=92,			// 나머지 연산 후 할당
	_ASSIGNMENT_BY_BITWISE_LEFT_SHIFT=93, 	// 비트를 왼쪽으로 시프트한 후 할당
	_ASSIGNMENT_BY_BITWISE_RIGHT_SHIFT=94,	// 비트를 오른쪽으로 시프트한 후 할당
	_ASSIGNMENT_BY_BITWISE_AND=95,			// 비트 AND 연산 후 할당
	_ASSIGNMENT_BY_BITWISE_XOR=96,			// 비트 XOR 연산 후 할당
	_ASSIGNMENT_BY_BITWISE_OR=97,			// 비트 OR 연산 후 할당

	// 우선순위 15, 왼쪽에서 오른쪽
	_COMMA=98,								// 쉼표(콤마) 연산자
	
	_ENUM_COUNT_OPERATION=99				//	enum 타입의 갯수 : ENUMCOUNT-50
} ClangOperationIndex;


typedef enum _ClangDelimiterIndex
{
	_LEFT_PAREN=100, 			// -> (
	_RIGHT_PAREN=101, 			// -> )
	_LEFT_BRACE=102, 			// -> {
	_RIGHT_BRACE=103, 			// -> }
	_LEFT_BRACKET=104, 			// -> [
	_RIGHT_BRACKET=105, 		// -> ]
	_SEMICOLON=106, 			// -> ;

	_ENUM_COUNT_DELIMITER=107		// enum 타입의 갯수 : ENUMCOUNT - 100
} ClangDelimiterIndex;

typedef enum _ClangSymbolIndex
{
	_IDENTIFIER=120,			// -> 변수 이름, 함수 이름 등...
								// ex) ([a-zA-Z][a-zA-Z0-9]*)
	_DIGIT=121,					// -> 숫자([0-9]+(.[0-9]*)?)

	_ENUM_COUNT_SYMBOL=122		// enum 타입의 갯수 : ENUMCOUNT - 120



} ClangSymbolIndex;

typedef enum _ClangEtcIndex
{
	_SHARP=140,				// #
	_INCLUDE=141,			// include
	_HEADER_FILE=142,		// 헤더 파일

	_ENUM_COUNT_ETC=143
} ClangEtcIndex;

void init();

bool scanner();

void printOpTableWithFile();
void printSymbolTableWithFile();
void destroyFile();
void print();



#endif 
