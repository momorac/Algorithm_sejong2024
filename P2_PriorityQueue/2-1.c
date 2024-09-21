#include <stdio.h>
#include <stdlib.h>

// 배열 뒤에서부터 ***선택정렬***하는 문제

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

    for (int *p = list + n - 1; p >= list; p--)
    {
        int *max = p;
        for (int *pp = p - 1; pp >= list; pp--)
        {
            if (*pp > *max)
            {
                max = pp;
            }
        }

        int tmp = *p;
        *p = *max;
        *max = tmp;
    }

    for (int *p = list; p < list + n; p++)
    {
        printf(" %d", *p);
    }

    return 0;
}