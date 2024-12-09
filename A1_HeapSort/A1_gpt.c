#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 노드 구조체 정의
struct Node
{
    int elem;
    struct Node *next;
} typedef NODE;

// 노드 생성 함수
NODE *getNode()
{
    NODE *new = (NODE *)malloc(sizeof(NODE));
    new->next = NULL;
    return new;
}

// 리스트 생성 함수
NODE *buildList(int n, int min, int max)
{
    NODE *L = getNode();
    L->elem = rand() % (max - min + 1) + min;

    NODE *p = L;
    for (int i = 1; i < n; i++)
    {
        NODE *new = getNode();
        new->elem = rand() % (max - min + 1) + min;
        p->next = new;
        p = new;
    }

    return L;
}

// 리스트 출력 함수
void printList(NODE *L)
{
    NODE *p = L;
    while (p != NULL)
    {
        printf("%d ", p->elem);
        p = p->next;
    }
    printf("\n");
}

// 힙 정렬을 위한 힙 구성 함수
void minHeapify(int arr[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i)
    {
        int temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;

        minHeapify(arr, n, smallest);
    }
}

// k번째 작은 원소를 찾는 함수
int findKthSmallest(NODE *L, int n, int k)
{
    // 배열에 리스트 복사
    int *arr = (int *)malloc(n * sizeof(int));
    NODE *p = L;
    for (int i = 0; i < n; i++)
    {
        arr[i] = p->elem;
        p = p->next;
    }

    // 배열을 힙으로 변환
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);

    // k번째 작은 원소를 찾기 위해 하나씩 추출
    for (int i = 0; i < k - 1; i++)
    {
        arr[0] = arr[n - 1]; // 루트 교체
        n--;                 // 힙 크기 줄이기
        minHeapify(arr, n, 0); // 힙 정렬
    }

    int kthSmallest = arr[0];
    free(arr);
    return kthSmallest;
}

// main 함수
int main()
{
    srand(time(NULL));

    // 첫 번째 리스트 L 생성
    NODE *L = buildList(10, 1, 100);
    printf("List L: ");
    printList(L);

    // k = 1, 2, 3에 대해 k번째 작은 원소를 찾고 출력
    int output[3];
    for (int k = 1; k <= 3; k++)
    {
        output[k - 1] = findKthSmallest(L, 10, k);
    }
    printf("%d %d %d\n", output[0], output[1], output[2]);

    // 두 번째 리스트 L 생성 (100,000개의 정수)
    L = buildList(100000, 1, 1000000);

    // k값 설정
    int karray[] = {1, 100, 99900, 99999};

    // 각 k에 대해 k번째 작은 원소를 찾고 실행 시간을 측정하여 출력
    for (int i = 0; i < 4; i++)
    {
        clock_t start = clock(); // 시간 측정 시작
        int result = findKthSmallest(L, 100000, karray[i]);
        clock_t end = clock(); // 시간 측정 종료
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%d번째 작은 원소: %d, 실행 시간: %f초\n", karray[i], result, time_spent);
    }

    return 0;
}
