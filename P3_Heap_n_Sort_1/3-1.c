#include <stdio.h>

/*
    배열을 이용한 순차힙 구현하기
        인덱스 i 위치에 존재하는 노드에 대해
        - 왼쪽 자식은 2i 위치에 존재
        - 오른쪽 자식은 2i+1 위치에 존재
        - 부모는 첨자 i/2 위치에 존재

    - 배열 0번째 위치는 사용하지 않음
    - 마지막 노드의 인덱스는 항상 n
    - 최대힙으로 구현. 최대값부터 삭제
*/

void insertItem(int key);
void upHeap(int i);
int removeMax();
void downHeap(int i);
void printHeap();
int isInternal(int i);

int Heap[99];
int n = 0;

int main()
{
    char command;
    int tmp_k;

    while (1)
    {
        scanf("%c", &command);

        if (command == 'i')
        {
            scanf("%d", &tmp_k);
            insertItem(tmp_k);
            printf("0\n");
        }
        else if (command == 'd')
        {
            printf("%d\n", removeMax());
        }
        else if (command == 'p')
        {
            printHeap();
        }
        else if (command == 'q')
        {
            break;
        }
    }

    return 0;
}

// 힙에 새 노드 추가하는 함수
void insertItem(int key)
{
    n++;
    Heap[n] = key;
    upHeap(n);
}

// 힙에 새 노드 삽입 시 하향 순서로 힙 재정렬하는 함수
void upHeap(int i)
{
    // 루트에 도달하거나 부모 노드의 자신보다 크거나 같으면 정지
    if (i == 1)
        return;
    if (Heap[i] <= Heap[i / 2])
        return;

    // 위 조건 만족할때까지 부모와 키값 바꾸기
    int tmp = Heap[i];
    Heap[i] = Heap[i / 2];
    Heap[i / 2] = tmp;

    // 재귀적 호출
    upHeap(i / 2);
}

// 힙에서 최대 값(루트노드) 삭제 후 반환하는 함수
int removeMax()
{
    int key = Heap[1];
    Heap[1] = Heap[n];
    n--;
    downHeap(1);

    return key;
}

// 힙에서 노드 삭제 시 힙순서 복구하는 함수
void downHeap(int i)
{
    // 외부 노드 도착하면 정지
    if (!isInternal(i))
        return;

    int maxChild = 2 * i; // 왼쪽 자식노드 인덱스 저장

    if (2 * i + 1 <= n)
        if (Heap[2 * i + 1] > Heap[maxChild]) // 오른쪽 자식이 더 크면 최대 자식 인덱스 갱신
            maxChild = 2 * i + 1;

    // 자식 노드의 키값이 자신보다 작거나 같으면 정지
    if (Heap[maxChild] <= Heap[i])
        return;

    // 자식 노드 키값이 자신보다 크면 값 교환
    int tmp = Heap[maxChild];
    Heap[maxChild] = Heap[i];
    Heap[i] = tmp;

    // 재귀적 호출
    downHeap(maxChild);
}

// 힙에 저장된 값들 레벨 순서대로 출력하는 함수
void printHeap()
{
    for (int i = 1; i <= n; i++)
    {
        printf(" %d", Heap[i]);
    }
    printf("\n");
}

int isInternal(int i)
{
    if (i * 2 <= n)
        return 1;
    else
        return 0;
}
