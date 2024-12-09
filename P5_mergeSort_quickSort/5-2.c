#include <stdio.h>
#include <stdlib.h>

void inPlaceQuickSort(int L[], int l, int r);
int findPivot(int L[], int l, int r);
int inPlacePartition(int L[], int l, int r, int k);
void swap(int *x, int *y);

int main(void)
{
    int *L;
    int n;
    int i;

    // n개의 정수 입력받아서 배열에 저장
    scanf("%d", &n);
    L = (int *)malloc(sizeof(int) * n);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &L[i]);
    }

    inPlaceQuickSort(L, 0, n - 1);

    for (i = 0; i < n; i++)
    {
        printf(" %d", L[i]);
    }

    free(L);

    return 0;
}

void inPlaceQuickSort(int L[], int l, int r)
{
    if (l >= r)
        return;

    int k = findPivot(L, l, r);
    int m = inPlacePartition(L, l, r, k);

    inPlaceQuickSort(L, l, m - 1);
    inPlaceQuickSort(L, m + 1, r);
}

int findPivot(int L[], int l, int r)
{

    int a = rand() % (r - l + 1) + l;
    int b = rand() % (r - l + 1) + l;
    int c = rand() % (r - l + 1) + l;

    if ((L[a] > L[b]) != (L[a] > L[c]))
        return a;
    else if ((L[b] > L[a]) != (L[b] > L[c]))
        return b;
    else
        return c;
}

int inPlacePartition(int L[], int l, int r, int k)
{
    int p = L[k];
    swap(&L[k], &L[r]);
    int i = l;
    int j = r - 1;

    while (i <= j)
    {
        while (i <= j && L[i] <= p)
        {
            i++;
        }
        while (i <= j && L[j] >= p)
        {
            j--;
        }
        if (i < j)
        {
            swap(&L[i], &L[j]);
        }
    }
    swap(&L[i], &L[r]);
    return i;
}

void swap(int *a, int *b)
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
}
