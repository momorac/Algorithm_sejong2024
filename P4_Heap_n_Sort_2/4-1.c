#include <stdio.h>

/*
    실습문제 4-1 : 유일 키 힙 정렬
        - 배열을 이용한 순차트리 힙
        - 키, 원소 쌍에서 원소는 생략
        - 최대 키 개수 < 100

    제자리 힙 정렬에서
        - Phase 1 : 초기 리스트에서 최대힙 생성
        - Phase 2 : 1단계에서 생성된 힙에 대해 오름차순 힙정렬 수행 -> O(log n) 시간에 수행

    인덱스 i 위치에 존재하는 노드에 대해
        - 왼쪽 자식은 2i 위치에 존재
        - 오른쪽 자식은 2i+1 위치에 존재
        - 부모는 첨자 i/2 위치에 존재
*/

int Heap[99];
int n;

int isInternal(int i);
void printHeap();
void insertItem(int key);
void upHeap(int i);
void downHeap(int i, int last);

// 무순배열의 힙 제자리 오름차순 정렬하는 함수
void inPlaceHeapSort()
{
    for (int i = n; i >= 2; i--)
    {
        int tmp = Heap[i];
        Heap[i] = Heap[1];
        Heap[1] = tmp;

        downHeap(1, i - 1);
    }
}

int main()
{
    // 최대 개수 입력받고 리스트 값 입력받기
    int count, tmp_k;
    scanf("%d", &count);

    for (int i = 0; i < count; i++)
    {
        scanf("%d", &tmp_k);
        insertItem(tmp_k);
    }

    // 힙 내림차순으로 정렬하기
    inPlaceHeapSort();

    printHeap();

    return 0;
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

// 힙에서 노드 삭제 시 힙순서 복구하는 함수
void downHeap(int i, int last)
{
    // 외부 노드 도착하면 정지
    if (2 * i > last)
        return;

    int maxChild = 2 * i; // 왼쪽 자식노드 인덱스 저장

    if (2 * i + 1 <= last)                    // 자식이 있을 때
        if (Heap[2 * i + 1] > Heap[maxChild]) // 오른쪽 자식이 더 크면 최대 자식 인덱스 갱신
            maxChild = 2 * i + 1;

    // 자식 노드의 키값이 자신보다 크거나 같으면 정지
    if (Heap[i] >= Heap[maxChild])
        return;

    // 자식 노드 키값이 자신보다 작으면 값 교환
    int tmp = Heap[maxChild];
    Heap[maxChild] = Heap[i];
    Heap[i] = tmp;

    // 재귀적 호출
    downHeap(maxChild, last);
}

int isInternal(int i)
{
    if (i * 2 <= n)
        return 1;
    else
        return 0;
}
