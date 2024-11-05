#include <stdio.h>
#include <stdlib.h>

int HashFunction(int key, int m);
void initBucketArray(int *buckets, int m)
{
    for (int i = 0; i < m; i++)
    {
        buckets[i] = 0;
    }
}

void insertItem(int *buckets, int key, int m)
{
    int v = HashFunction(key, m);

    if (buckets[v] == 0)
    {
        buckets[v] = key;
        printf("%d\n", v);
        return;
    }
    else
    {
        printf("C");
        for (int i = (v + 1) % m; i != v; i = (i + 1) % m)
        {
            if (buckets[i] == 0)
            {
                buckets[i] = key;
                printf("%d\n", i);
                break;
            }
            else
            {
                printf("C");
            }
        }
    }
}

void findElement(int *buckets, int m, int key)
{
    int v = HashFunction(key, m);

    if (buckets[v] == key)
    {
        printf("%d %d\n", v, buckets[v]);
        return;
    }

    for (int i = v + 1; i < m; i++)
    {
        if (buckets[i] == key)
        {
            printf("%d %d\n", i, buckets[i]);
            return;
        }
    }

    printf("-1\n");
}

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);

    int *buckets = (int *)malloc(sizeof(int) * m);
    initBucketArray(buckets, m);

    char command;
    int tmp, searchCount = 0;

    while (1)
    {
        getchar();
        scanf("%c", &command);

        if (command == 'i')
        {
            scanf("%d", &tmp);
            insertItem(buckets, tmp, m);

            searchCount++;
        }
        else if (command == 's')
        {
            scanf("%d", &tmp);
            findElement(buckets, m, tmp);
        }
        else if (command == 'e')
        {
            break;
        }
    }

    return 0;
}

int HashFunction(int key, int m)
{
    return key % m;
}
