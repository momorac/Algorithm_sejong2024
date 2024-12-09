#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int elem;
    struct Node *next;
} typedef NODE;

NODE *getNode(int elem);
void printList(NODE *L);
NODE *mergeSort(NODE *L, int n);
void partition(NODE *L, int k, NODE **L1, NODE **L2);
NODE *merge(NODE *L1, NODE *L2);

int main()
{
    // n개의 정수 입력받아서 연결리스트에 할당하기
    int n, tmp;
    scanf("%d", &n);
    scanf("%d", &tmp);

    NODE *L = getNode(tmp);

    NODE *p = L;
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &tmp);
        NODE *new = getNode(tmp);

        p->next = new;
        p = new;
    }

    L = mergeSort(L, n);  

    printList(L);

    return 0;
}

NODE *getNode(int elem)
{
    NODE *new = (NODE *)malloc(sizeof(NODE));
    new->elem = elem;
    new->next = NULL;

    return new;
}

void printList(NODE *L)
{
    NODE *p = L;
    while (p != NULL)
    {
        printf(" %d", p->elem);
        p = p->next;
    }
    printf("\n");
}

NODE *mergeSort(NODE *L, int n)
{
    if (L == NULL || L->next == NULL) 
        return L;

    NODE *L1 = NULL;
    NODE *L2 = NULL;

    partition(L, n / 2, &L1, &L2);

    L1 = mergeSort(L1, n / 2);
    L2 = mergeSort(L2, n - n / 2);

    return merge(L1, L2);
}

// L을 k를 기준으로 두 개로 분할
void partition(NODE *L, int k, NODE **L1, NODE **L2)
{
    NODE *p = L;
    *L1 = p;

    for (int i = 0; i < k - 1; i++)
    {
        p = p->next;
    }

    *L2 = p->next;
    p->next = NULL;
}

NODE *merge(NODE *L1, NODE *L2)
{
    NODE *L = NULL;  
    NODE **pL = &L;  

    NODE *p1 = L1;
    NODE *p2 = L2;

    // 최초 초기화
    if (p1->elem <= p2->elem)
    {
        *pL = p1;
        p1 = p1->next;
    }
    else
    {
        *pL = p2;
        p2 = p2->next;
    }

    NODE *current = *pL;

    // 리스트 병합
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->elem <= p2->elem)
        {
            current->next = p1;
            p1 = p1->next;
        }
        else
        {
            current->next = p2;
            p2 = p2->next;
        }
        current = current->next;
    }

    // 나머지 리스트 연결
    if (p1 != NULL)
    {
        current->next = p1;
    }
    else if (p2 != NULL)
    {
        current->next = p2;
    }

    return L;
}
