#include <stdio.h>
#include <stdlib.h>

// 배열 삽입정렬하는 문제

int main()
{

    // 크기가 n인 배열 동적할당하고 입력받기
    int n;
    scanf("%d", &n);

    int *list = (int *)malloc(n * sizeof(int));

    for (int *p = list; p < list + n; p++)
    {
        scanf("%d", p);
    }

    // 삽입정렬 알고리즘
    for (int *p = list + 1; p < list + n; p++)
    {
        int this = *p;

        int *pp;
        for (pp = p - 1; (pp >= list) && (*pp > this); pp--)
        {
            *(pp + 1) = *pp;
        }
        *(pp + 1) = this;
    }

    // 정렬된 리스트 출력
    for (int *p = list; p < list + n; p++)
    {
        printf(" %d", *p);
    }

    // 동적할당 해제
    free(list);

    return 0;
}