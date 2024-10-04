#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    int elem;
    struct Node *next;
} typedef NODE;

struct Leaf
{
    int elem;
    struct Leaf *left;
    struct Leaf *right;
} typedef LEAF;

struct Heap
{
    LEAF root;
    LEAF *last;
} typedef HEAP;

NODE *getNode()
{
    NODE *new = (NODE *)malloc(sizeof(NODE));
    new->next = NULL;
    return new;
}

LEAF *setLeaf()
{
    LEAF *new = (LEAF *)malloc(sizeof(LEAF));
    new->left = NULL;
    new->right = NULL;
    return new;
}

NODE *buildList(int n, int min, int max)
{
    NODE *L = getNode();
    L->elem = rand() % (max - min) + min;

    NODE *p = L;
    for (int i = 1; i < n; i++)
    {
        NODE *new = getNode();
        new->elem = rand() % max + min;
        p->next = new;
        p = new;
    }

    return L;
}

void printList(NODE *L)
{
    NODE *p = L;
    while (p != NULL)
    {
        printf("%d ", p->elem);
        p = p->next;
    }
}

void findKthSmallest(NODE *L, int n, int k)
{
    // 리스트를 새로운 힙에 저장
    HEAP heap;
    heap.root.left = NULL;
    heap.root.right = NULL;
    heap.last = &(heap.root);
}

HEAP *buildHeap(HEAP *H, NODE *L)
{
    NODE *p = L;

    while (p != NULL)
    {
        H->last->elem = p->elem;
    }
}

int isExternal(LEAF *node)
{
    if (node->left == NULL && node->right == NULL)
        return 1;
    return 0;
}

void downHeap(LEAF *node)
{
    // 외부 노드이면 
    if ()
        return;

}

/*
    중복이 있을 수 있는 n개의 정수 원소들로 이루어진 리스트 L의 원소 가운데 k-번째로 작은 원소를 찾아라
*/
int main()
{
    srand(time(NULL));
    NODE *L = buildList(10, 1, 100);
    printList(L);

    for (int k = 1; k <= 3; k++)
    {
    }

    int n;
}