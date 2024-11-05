#include <stdio.h>
#include <stdlib.h>

struct node
{
    int elem;
    struct node *next;
} typedef NODE;

NODE *getnode(int key);
int HashFunction(int key, int m);
void initBucketArray(NODE **buckets, int m);
void insertItem(NODE **buckets, int m, int key);
int findElement(NODE **buckets, int m, int key);
void deleteItem(NODE **buckets, int m, int key);
void printBucketArray(NODE **buckets, int m);

int main()
{
    int m;
    scanf("%d", &m);

    NODE **buckets = (NODE **)malloc(m * sizeof(NODE *));

    char command;
    int tmp;

    while (1)
    {
        getchar();
        scanf("%c", &command);

        if (command == 'i')
        {
            scanf("%d", &tmp);
            insertItem(buckets, m, tmp);
        }
        else if (command == 's')
        {
            scanf("%d", &tmp);
            findElement(buckets, m, tmp);
        }
        else if (command == 'd')
        {
            scanf("%d", &tmp);
            deleteItem(buckets, m, tmp);
        }
        else if (command == 'p')
        {
            printBucketArray(buckets, m);
        }
        else if (command == 'e')
            break;
    }

    return 0;
}

NODE *getnode(int key)
{
    NODE *new = (NODE *)malloc(sizeof(NODE));
    new->elem = key;
    new->next = NULL;

    return new;
}

int HashFunction(int key, int m)
{
    return key % m;
}

void initBucketArray(NODE **buckets, int m)
{
    for (int i = 0; i < m; i++)
    {
        buckets[i] = NULL;
    }
}

void insertItem(NODE **buckets, int m, int key)
{
    int v = HashFunction(key, m);
    NODE *new = getnode(key);

    if (buckets[v] == NULL)
    {
        buckets[v] = new;
    }
    else
    {
        NODE *tmp = buckets[v];
        buckets[v] = new;
        new->next = tmp;
    }
}

int findElement(NODE **buckets, int m, int key)
{
    int v = HashFunction(key, m);
    NODE *tmp = buckets[v];

    if (tmp == NULL)
    {
        printf("0\n");
        return 0;
    }

    int i = 1;
    while (tmp != NULL)
    {
        if (tmp->elem == key)
        {
            printf("%d\n", i);
            return 1;
        }
        tmp = tmp->next;
        i++;
    }

    printf("0\n");
    return 0;
}

void deleteItem(NODE **buckets, int m, int key)
{
    int v = HashFunction(key, m);

    if (findElement(buckets, m, key) == 0) // 키가 테이블에 없을 때
        return;
    else // 키가 테이블에 있을 때
    {

        if (buckets[v]->elem == key)
        {
            NODE *tmp = buckets[v];
            buckets[v] = tmp->next;
            free(tmp);
            return;
        }
        else
        {
            NODE *pre = buckets[v];
            NODE *target = pre->next;

            while (target->elem != key)
            {
                pre = pre->next;
                target = target->next;
            }

            pre->next = target->next;
            free(target);
        }
    }
}

void printBucketArray(NODE **buckets, int m)
{
    NODE *tmp;
    for (int i = 0; i < m; i++)
    {
        tmp = buckets[i];
        while (tmp != NULL)
        {
            printf(" %d", tmp->elem);
            tmp = tmp->next;
        }
    }
    printf("\n");
}
