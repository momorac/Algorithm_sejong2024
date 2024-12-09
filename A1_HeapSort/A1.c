#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    int name;
    struct Node *next;
} typedef NODE;

struct Leaf
{
    int name;
    struct Leaf *left;
    struct Leaf *right;
} typedef LEAF;

struct Heap
{
    LEAF *root;
    LEAF *last;
    int size;
} typedef HEAP;

NODE *getNode()
{
    NODE *new = (NODE *)malloc(sizeof(NODE));
    new->next = NULL;
    return new;
}

LEAF *setLeaf(int name)
{
    LEAF *new = (LEAF *)malloc(sizeof(LEAF));
    new->name = name;
    new->left = NULL;
    new->right = NULL;
    return new;
}

NODE *buildList(int n, int min, int max)
{
    NODE *L = getNode();
    L->name = rand() % (max - min + 1) + min;

    NODE *p = L;
    for (int i = 1; i < n; i++)
    {
        NODE *new = getNode();
        new->name = rand() % (max - min + 1) + min;
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
        printf("%d ", p->name);
        p = p->next;
    }
    printf("\n");
}

// 힙의 최대 노드를 루트로 유지 (Max-Heap)
void heapify(LEAF *node)
{
    if (node == NULL)
        return;

    LEAF *largest = node;
    if (node->left && node->left->name > largest->name)
        largest = node->left;
    if (node->right && node->right->name > largest->name)
        largest = node->right;

    if (largest != node)
    {
        int temp = node->name;
        node->name = largest->name;
        largest->name = temp;
        heapify(largest);
    }
}

HEAP *buildHeapFromList(NODE *L)
{
    HEAP *heap = (HEAP *)malloc(sizeof(HEAP));
    heap->root = setLeaf(L->name); // 첫 노드를 힙 루트로 설정
    heap->last = heap->root;
    heap->size = 1;

    NODE *p = L->next;
    while (p != NULL)
    {
        LEAF *newLeaf = setLeaf(p->name);

        // 힙에 새로운 리프를 추가 (완전이진트리 유지)
        if (heap->size % 2 == 0)
            heap->last->left = newLeaf;
        else
            heap->last->right = newLeaf;

        heap->last = newLeaf;
        heap->size++;

        // 힙 성질을 유지
        heapify(heap->root);
        p = p->next;
    }

    return heap;
}

// 힙에서 k번째 작은 원소를 찾음 (최대 힙 사용)
int findKthSmallest(NODE *L, int n, int k)
{
    HEAP *heap = buildHeapFromList(L);

    // 힙에서 k번째 작은 원소를 찾기 위해 루트에서부터 삭제하며 찾아감
    for (int i = 0; i < k - 1; i++)
    {
        // 루트에 가장 큰 값이 있으므로, 루트를 삭제하고 힙 성질 유지
        if (heap->root == NULL)
            return -1;

        LEAF *lastLeaf = heap->last;
        heap->root->name = lastLeaf->name;

        // 힙 크기를 줄이고 마지막 노드 갱신
        if (heap->size % 2 == 0)
            heap->last = heap->last->left;
        else
            heap->last = heap->last->right;

        heap->size--;
        heapify(heap->root);
    }

    return heap->root->name; // 루트는 k번째 작은 원소
}

int main()
{
    srand(time(NULL));

    // 리스트 L 생성
    NODE *L = buildList(10, 1, 100);
    printList(L);

    // k = 1, 2, 3에 대해 k번째 작은 원소를 찾고 출력
    for (int k = 1; k <= 3; k++)
    {
        int kthSmallest = findKthSmallest(L, 10, k);
        printf("%d번째 작은 원소: %d\n", k, kthSmallest);
    }

    return 0;
}
