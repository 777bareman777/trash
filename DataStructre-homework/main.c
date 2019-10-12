#include <stdio.h>
#include <stdlib.h>
#include <stack.h>
#include <queue.h>
#include <linkedlist.h>

int main()
{

    pStack stack=NULL;
    pQueue queue=NULL;
    pList list=NULL;

    // 스택
    printf("\n\n스택\n\n");
    createStack(&stack);
    for(int i=1;i<=10;i++)
        pushStack(stack,i);
    for(int i=0;i<10;i++)
        printf("%d\n",popStack(stack));
    freeStack(stack);
    destroyStack(stack);

    // 큐
    printf("\n\n큐\n\n");
    createQueue(&queue);
    for(int i=1;i<=10;i++)
        enQueue(queue,i);
    for(int i=0;i<10;i++)
        printf("%d\n",deQueue(queue));
    freeQueue(queue);
    destroyQueue(queue);

    // 링크드 리스트
    printf("\n\n링크드 리스트\n\n");
    createLinkedList(&list);
    for(int i=1;i<=10;i++)
        appendNode(list,i);
    printLinkedList(list);
    freeLinkedList(list);
    destoryLinkedList(list);

    exit(0);
}
