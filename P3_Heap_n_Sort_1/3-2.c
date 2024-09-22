#include <stdio.h>

/*
    실습문제 3-2 : 상향식 힙 생성
    - 배열을 이용한 최대힙 구현 문제
        인덱스 i 위치에 존재하는 노드에 대해
        - 왼쪽 자식은 2i 위치에 존재
        - 오른쪽 자식은 2i+1 위치에 존재
        - 부모는 첨자 i/2 위치에 존재
    - 배열에 미리 저장된 키들을 상향식으로 재배치하여 힙 생성
*/

int Heap[99];
int n;

// 힙에서 노드 삭제 시 힙순서 복구하는 함수
void downHeap(int i)
{
    // 외부 노드 도착하면 정지
    if (i * 2 > n)
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

void buildHeap()
{
    for (int i = n / 2; i >= 1; i--)
    {
        downHeap(i);
    }
}

int main()
{
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &Heap[i]);
    }

    buildHeap();
    printHeap();

    return 0;
}