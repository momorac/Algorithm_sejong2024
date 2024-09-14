#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char elem;
    struct Node *next;
    struct Node *prev;
} typedef NODE;

// 헤더와 트레일러 노드가 존재하는 이중연결리스트 구조체
struct LinkedList
{
    struct Node *head;
    struct Node *tail;
} typedef LinkedList;

NODE *getNode()
{
    NODE *new = (NODE *)malloc(sizeof(NODE));
    new->elem = 0;
    new->next = NULL;
    new->prev = NULL;

    return new;
}

void add(LinkedList list, int r, char e)
{
    NODE *p = list.head;

    for (int i = 0; i < r; i++)
    {
        p = p->next;
        // p는 삽입할 위치의 다음 노드를 가리킴

        if (p == NULL)
        {
            printf("invalid position");
            return;
        }

        NODE *new = getNode();
        new->elem = 0;
        new->next = p;
        new->prev = p->prev;
        p->prev->next = new;
        p->prev = new;
    }
}

void print(LinkedList list)
{
    // p는 linkedlist의 헤드 다음 첫 노드부터 시작
    NODE *p = list.head->next;

    while (p != list.tail)
    {
        printf("%c ", p->elem);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    // 이중연결리스트 선언 및 초기화 - O(n)
    LinkedList list;
    list.head = getNode();
    list.head->next = list.tail;
    list.tail = getNode();
    list.tail->prev = list.head;

    return 0;
}