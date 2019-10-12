#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

// 데이터 구조체 정의
typedef char boolean; /* 논리 데이터 타입*/
typedef int Element; /* 노드의 데이터 타입 */
typedef struct _node *pNode; /* struct node 포인터 */
typedef pNode *ppNode; /* struct node 이중 포인터 */
typedef struct _list *pList; /* struct list 포인터 */
typedef pList *ppList; /* struct list 이중 포인터 */

typedef struct _node{ /* 노드 구조체 */
    Element element;
    pNode link;
} node;

typedef struct _list{ /* 리스트 구조체 */
    pNode head;
    pNode tail;
    int size;
} list;

// 프로토 타입 함수 정의
void createLinkedList(ppList list); // 링크드 리스트 초기화 함수
void createNode(ppNode n, Element element); // 노드 생성 함수
void freeNode(pNode n); // 노드 메모리 해제
void freeLinkedList(pList list); // 리스트 메모리 해제
void destoryLinkedList(pList list); // 리스트 메모리 제거
pNode findNodeWithIndex(pNode n, int index); // index를 가지고 노드 검색
pNode findNodeWithElement(pNode n, Element element); // element를 가지고 노드 검색
void appendNode(pList list, Element element); // 맨 뒤에 노드 추가 함수
void insertNode(pList list, Element element, int index); // 선택 위치에 노드 추가 함수
void deleteFirstNode(pList list); // 맨 첫 번째 노드 제거 함수
void deleteLastNode(pList list); // 맨 마지막 번째 노드 제거 함수
void deleteNodeWithIndex(pList list, int index); // index를 가지고 노드 제거 함수
void printLinkedList(pList list); // 링크드 리스트 값 모두 출력

#endif
