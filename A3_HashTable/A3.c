#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int M = 23; // 해시테이블의 최대 저장 원소 개수

int hashFunction(int key);
int hashFunction_(int key);

bool isHashTableFull(int *buckets);
void initBucketArray(int *buckets);
void findElement(int *buckets, int key);
void insertItem(int *buckets, int key);
void removeElement(int *buckets, int key);
void printHashTable(int *buckets);

int main()
{
    int *buckets = (int *)malloc(sizeof(int) * M); // 크기가 M인 해시테이블 포인터배열에 동적할당받기
    initBucketArray(buckets);

    char command;
    int tmp_key;

    while (true)
    {
        scanf("%c", &command);

        if (command == 'f')
        {
            printf("enter the key to find :");
            scanf("%d", &tmp_key);
            findElement(buckets, tmp_key);
            getchar();
        }
        else if (command == 'i')
        {
            printf("enter the key to insert :");
            scanf("%d", &tmp_key);
            insertItem(buckets, tmp_key);
            getchar();
        }
        else if (command == 'r')
        {
            printf("enter the key to remove :");
            scanf("%d", &tmp_key);
            removeElement(buckets, tmp_key);
            getchar();
        }
        else if (command == 'p')
        {
            printHashTable(buckets);
            getchar();
        }
        else if (command == 'q')
        {
            break;
        }
    }

    free(buckets); // 동적할당된 메모리 해제

    return 0;
}

// 해시 함수
int hashFunction(int key)
{
    return key % M;
}

// 이중 해싱을 위한 해시 함수
int hashFunction_(int key)
{
    return 1 + (key % (M - 1));
}

// 해시테이블이 꽉 찼는지 확인하는 함수
bool isHashTableFull(int *buckets)
{
    for (int i = 0; i < M; i++)
    {
        if (buckets[i] == -1)
            return false;
    }
    return true;
}

// 해시테이블 초기화 함수
void initBucketArray(int *buckets)
{
    for (int i = 0; i < M; i++)
    {
        buckets[i] = -1; // 셀의 기본 값은 -1로 한다. 즉 해시테이블에 저장된 값이 0보다 -1이면 비활성화 된 것이다.
    }
}
// 주어진 키를 통해 해시테이블에 저장된 원소를 출력하는 함수
void findElement(int *buckets, int key)
{
    // 초기 키 위치에 존재한다면 출력 후 종료
    int v = hashFunction(key);
    
    if (buckets[v] == key)
    {
        printf("element for key %d exists on index %d.\n", key, v);
        return;
    }

    // 충돌 발생 시 탐색 후 출력, 종료
    for (int i = 0; i < M; i++)
    {
        if (buckets[i] == key)
        {
            printf("element for key %d exists on index %d.\n", key, i);
            return;
        }
    }

    // 해당하는 키가 없다면 Nosuchkey 반환
    printf("NoSuchKey\n");
}

// 키를 통해 해시테이블에 원소를 삽입하는 함수
void insertItem(int *buckets, int key)
{
    // 해시테이블이 가득 찬 경우 출력 후 종료
    if (isHashTableFull(buckets))
    {
        printf("Cannot Insert Item! Table is full.\n");
        return;
    }
    int v = hashFunction(key);
    int v_ = hashFunction_(key);

    // 초기 위치가 비어있는 경우 바로 삽입
    if (buckets[v] == -1)
    {
        buckets[v] = key;
        return;
    }

    // 이중 해싱을 이용한 충돌 처리
    int idx = v;
    int count = 0; // count변수를 통해 무한루프 방지
    while (buckets[idx] >= 0 && count < M)
    {
        idx = (idx + v_) % M;
        count++;
    }

    if (count == M)
    { // 키값이 유효하지 않은 경우
        printf("Cannot Insert Item! No valid position available.\n");
    }
    else
    {
        buckets[idx] = key;
    }
}

void removeElement(int *buckets, int key)
{
    int v = hashFunction(key);

    // 초기 해시 자리에 해당 키가 존재하면 삭제(비활성화)
    if (buckets[v] == key)
    {
        buckets[v] = -1;
        return;
    }
    // 충돌 발생 시 탐색 후 키 삭제(비활성화))
    else
    {
        for (int i = 0; i < M; i++)
        {
            if (buckets[i] == key)
            {
                buckets[v] = -1;
                return;
            }
        }
    }

    // 삭제할 키가 존재하지 않으면 NoSuchKey 반환
    printf("NoSuchKey\n");
}

// 인덱스 번호와 함께 해시테이블에 저장된 원소들을 출력하는 함수
void printHashTable(int *buckets)
{
    for (int i = 0; i < M; i++)
        printf("% 3d ", i);

    printf("\n");

    for (int i = 0; i < M; i++)
    {
        if (buckets[i] >= 0)
            printf("% 3d ", buckets[i]);
        else
            printf("  . ");
    }
    printf("\n");
}
