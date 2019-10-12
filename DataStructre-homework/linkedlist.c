#include <stdio.h>
#include <stdlib.h>
#include <linkedlist.h>

// 링크드 리스트 초기화 함수
void createLinkedList(ppList list)
{
    *list=(pList)malloc(sizeof(list));
    (*list)->head=NULL;
    (*list)->tail=NULL;
    (*list)->size=0;
}

// 노드 생성 함수
void createNode(ppNode n, Element element)
{
    *n=(pNode)malloc(sizeof(node));
    (*n)->element=element;
    (*n)->link=NULL;
}

// 노드 메모리 해제
void freeNode(pNode n)
{
    free(n);
}

// 리스트 메모리 해제
void freeLinkedList(pList list)
{
    if(!list) return ; // 메모리가 제거된 상태

    pNode cur=list->head; // 현재 위치를 리스트의 첫 번째로 설정
    pNode tmp;
    while( cur != NULL)
    {
        tmp=cur->link; // 리스트의 다음 위치 저장
        freeNode(cur); // 사용한 노드 메모리 해제
        cur=tmp; // 리스트 다음 위치 백업
        list->size-=1; // 리스트 크기 감소
    }
    list->head=NULL; // 스택의 머리를 NULL로 설정
    list->tail=NULL; // 스택의 꼬리를 NULL로 설정
    list->size=0; // 스택의 크기를 0으로 설정. 제대로 코딩 됬으면 이미 0일 거임.
}

// 리스트 메모리 제거
void destoryLinkedList(pList list)
{
    freeLinkedList(list);
    if(!list) return ; // 메모리가 제거된 상태
    free(list);
    list=NULL;
}


// index를 가지고 노드 검색
pNode findNodeWithIndex(pNode n, int index)
{
    pNode cur=n;

    // index의 범위가 올바르지 않으면 NULL 반환
    if(index <0)
        return NULL;

    while(n->link != NULL && index > 0) // index를 감소 시키면서, 노드 검색
    {
        index--; // 인덱스 감소
        cur=cur->link; // 다음 노드로 변경
    }
    return cur;
}

// element를 가지고 노드 검색
pNode findNodeWithElement(pNode n, Element element)
{
    pNode cur=n;

    while(cur->link != NULL) // 값을 비교하면서, 노드 검색
    {
        if(cur->element == element)
            return cur; // 노드를 찾으면, 해당 노드를 반환
        cur=cur->link; // 다음 노드로 변경
    }
    return NULL; // 존재하지 않으면 NULl을 반환
}

// 맨 뒤에 노드 추가 함수
void appendNode(pList list, Element element)
{
    // 리스트가 NULL이면, 값을 넣지 않음.
    if(!list)   return ;

    // 노드 생성
    pNode n;
    createNode(&n,element);
    
    if(list->head == NULL && list->tail == NULL) // 맨 처음 노드 값 추가
        list->head=list->tail=n;
    else // 두 번째 부터 꼬리 부분에 노드 값 추가
    { 
        list->tail->link=n; // 맨 마지막의 노드가 추가된 노드를 가리킴
        list->tail=n; // 꼬리 부분을 추가된 노드로 변경
    }
    list->size+=1; // 리스트 크기 증가
}

// 선택 위치에 노트 추가 함수
void insertNode(pList list, Element element, int index)
{
    // 리스트가 NULL이면, 값을 넣지 않음.
    if(!list) 
        return ;

    // 리스트의 크기에 벗어나면 값을 넣지 않음.
    if(index>=list->size || index <0)
        return ;

    // 노드 생성
    pNode n;
    createNode(&n,element);

    pNode cur=findNodeWithIndex(list->head,index); // 해당하는 노드를 찾음
    n->link=cur->link; // 추가된 노드가 원래 있던 노드의 다음 번을 가리킴
    cur->link=n; // 원래있던 노드가 추가된 노드를 가리킴
    list->size+=1; // 리스크 크기 증가
}

// 맨 첫번째 노드 제거 함수
void deleteFirstNode(pList list)
{
    pNode cur=list->head;
    list->head=cur->link; // 머리 부분을 두 번째 노드로 바꿈
    freeNode(cur); // 머리 부분 메모리를 해제함.
    cur=NULL;
    list->size-=1; // 리스트 크기 감소
}

// 맨 마지막 번째 노드 제거 함수
void deleteLastNode(pList list)
{
    pNode cur=list->head; 
    while(cur->link->link != NULL ) // 맨 마지막 노드 검색
        cur=cur->link;
    freeNode(cur->link); // 맨 마지막 노드 메모리 해제
    cur->link=NULL; // 맨 마지막에서 두 번째 노드가 가리키는 값을 NULL로 변경
    list->tail=cur; // 꼬리 부분을 맨 마지막에서 두 번째 노드로 변경
    list->size-=1; // 리스트 크기 감소
}

// index를 가지고 노드 제거 함수
void deleteNodeWithIndex(pList list, int index)
{
    // 리스트가 NULL이면, 0을 반환
    if(!list) 
        return ;

    // 리스트의 크기에 벗어나면 값을 삭제 하지 않음
    if(index>=list->size || index <0)
        return ;

    pNode cur=findNodeWithIndex(list->head,index-1); // 삭제 대상 이전 노드 검색
    pNode tmp=cur->link; // 삭제 대상 노드를 임시 저장함
    cur->link=tmp->link; // 삭제 대상 노드가 가리키는 노드를 이전 노드가 가리키도록 변경
    freeNode(tmp); // 삭제 대상 노드 메모리 해제
    tmp=NULL; 
    list->size-=1; // 릭스트 크기 감소
}

// 링크드 리스트 값 모두 출력
void printLinkedList(pList list)
{
    pNode cur=list->head;
    while(cur != NULL)
    {
        printf("%d\n",cur->element);
        cur=cur->link;
    }
}
