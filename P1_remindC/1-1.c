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

void add(LinkedList *list, int r, char e)
{
    NODE *p = list->head;

    for (int i = 0; i < r; i++)
    {
        p = p->next;
        // p는 삽입할 위치의 다음 노드를 가리킴

        if (p == NULL)
        {
            printf("invalid position\n");
            return;
        }
    }

    NODE *new = getNode();
    new->elem = e;
    new->next = p;
    new->prev = p->prev;
    new->prev->next = new;
    p->prev = new;
}

void delete(LinkedList *list, int r)
{
    NODE *p = list->head;

    for (int i = 0; i < r; i++)
    {
        p = p->next;
        // p는 삭제할 대상 노드를 가리킴

        if (p == list->tail || p == NULL)
        {
            printf("invalid position\n");
            return;
        }
    }

    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
}

char get(LinkedList *list, int r)
{
    NODE *p = list->head;

    for (int i = 0; i < r; i++)
    {
        p = p->next;
        if (p == list->tail || p == NULL)
        {
            printf("invalid position\n");
            return 0;
        }
    }
    return p->elem;
}

void print(LinkedList *list)
{
    // p는 linkedlist의 헤드 다음 첫 노드부터 시작
    NODE *p = list->head->next;

    while (p != list->tail)
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
    list.tail = getNode();
    list.head->next = list.tail;
    list.tail->prev = list.head;

    int n, tmp_int;
    char command, tmp_char;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        getchar();
        scanf("%c", &command);
        switch (command)
        {
        case 'A':
            scanf("%d %c", &tmp_int, &tmp_char);
            add(&list, tmp_int, tmp_char);
            break;

        case 'D':
            scanf("%d", &tmp_int);
            delete (&list, tmp_int);
            break;

        case 'G':
            scanf("%d", &tmp_int);
            printf("%c\n", get(&list, tmp_int));
            break;
        case 'P':
            print(&list);
        }
    }

    int n, tmp_int;
    char command, tmp_char;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        getchar();
        scanf("%c", &command);
        switch (command)
        {
        case 'A':
            scanf("%d %c", &tmp_int, &tmp_char);
            add(&list, tmp_int, tmp_char);
            break;

        case 'D':
            scanf("%d", &tmp_int);
            delete (&list, tmp_int);
            break;

        case 'G':
            scanf("%d", &tmp_int);
            printf("%c\n", get(&list, tmp_int));
            break;
        case 'P':
            print(&list);
        }
    }

    // 동적할당 해제
    NODE *p = list.head;
    while (p != NULL)
    {
        NODE *next = p->next;
        free(p);
        p = next;
    }

    return 0;
}