#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 그래프의 간선 인접 리스트 구현 구조체
struct link
{
    struct edge *edge;
    struct link *next;
} typedef LINK;

// 그래프의 정점 구조체
struct vertex
{
    char name;
    LINK *adjacent;
    int distance; // dijkstra 알고리즘을 수행할 때, 출발점으로부터의 최단거리
    int count;    // dijkstra 알고리즘을 수행할 때, 최단거리의 개수
} typedef VERTEX;

// 그래프의 간선 구조체
struct edge
{
    VERTEX *origin;
    VERTEX *destination;
    int weight;
} typedef EDGE;

struct graph
{
    VERTEX *vertices;
    EDGE *edges;
} typedef GRAPH;

// 큐를 구현할 노드 구조체
struct node
{
    VERTEX *vertex;
    struct node *next;
} typedef NODE;

const int INFINITE = 99999;
int n, m; // n:그래프 내 정점의 개수 / m:그래프 내 간선의 개수
GRAPH G;
NODE *Q;

VERTEX *getVertex(char name);
void addAdjacent(char v, int e);
void buildSampleGraph();
void printSampleGraph();
void initQueue();
void reOrderQueue();
NODE *removeFirst();
void freeMemory();

// 다익스트라 알고리즘을 활용하여 최단거리 및 최단경로의 개수를 계산하는 함수
void findShortestPath(char source, char target)
{
    for (int i = 0; i < n; i++)
    {
        G.vertices[i].distance = INFINITE;
        G.vertices[i].count = 0;
    }

    VERTEX *start = getVertex(source);
    start->distance = 0;
    start->count = 1;

    initQueue();
    reOrderQueue();

    while (Q->next != NULL)
    {
        VERTEX *u = removeFirst()->vertex;

        LINK *adj = u->adjacent;
        while (adj != NULL)
        {
            VERTEX *z = adj->edge->origin == u ? adj->edge->destination : adj->edge->origin;

            int dist = u->distance + adj->edge->weight;
            if (z->distance > dist)
            {
                z->distance = dist;
                z->count = u->count; // 최단거리 수 업데이트
                reOrderQueue();      // 큐에서 키로 작용하는 distance값이 바뀌었으므로 우선순위 큐로 재정렬
            }
            else if (z->distance == dist)
            {
                z->count += u->count; // 동일한 최단 거리 경로 추가
            }

            adj = adj->next;
        }
    }
}

int main()
{
    char source, target, str[20];

    buildSampleGraph();
    // printSampleGraph();

    while (1)
    {
        // 입력받기 (공백 입력 시 프로그램 종료)
        printf("시작 정점 : ");
        fgets(str, 20, stdin);
        if (str[0] == ' ' || str[0] == '\n')
            break;
        else
            source = str[0];

        printf("목표 정점 : ");
        fgets(str, 20, stdin);

        if (str[0] == ' ' || str[0] == '\n')
            break;
        else
            target = str[0];

        // 다익스트라 알고리즘으로 최단거리 계산하기
        findShortestPath(source, target);

        // 출력하기
        printf("source   target   최단거리   최단경로 수\n");
        printf("%c        %c        %d          %d\n", source, target, getVertex(target)->distance, getVertex(target)->count);
    }

    // 동적할당된 메모리 해제
    freeMemory();

    return 0;
}

// 큐 초기화하는 함수 (n:그래프 내 정점의 개수)
void initQueue()
{
    // 헤더가 존재하는 단일 연결리스트로 큐 규현
    Q = (NODE *)malloc(sizeof(NODE));
    Q->vertex = NULL;
    Q->next = NULL;

    NODE *prev = Q;
    for (int i = 0; i < n; i++)
    {
        NODE *new = (NODE *)malloc(sizeof(NODE));
        new->vertex = &(G.vertices[i]);
        new->next = NULL;

        prev->next = new;
        prev = new;
    }
}

// 큐를 오름차순으로 재정렬하는 함수
void reOrderQueue()
{
    if (Q == NULL || Q->next == NULL)
        return;

    NODE *sorted = (NODE *)malloc(sizeof(NODE));
    sorted->next = NULL;

    while (Q->next != NULL)
    {
        // 현재 노드를 정렬된 리스트에 삽입
        NODE *current = Q->next;
        Q->next = current->next; // 큐에서 current 분리

        NODE *tmp = sorted;

        int currentDistance = current->vertex->distance;
        while (tmp->next != NULL && tmp->next->vertex->distance < currentDistance)
        {
            tmp = tmp->next;
        }

        current->next = tmp->next;
        tmp->next = current;
    }

    Q->next = sorted->next;
    free(sorted);
}

// 큐의 첫 번째 노드 반환하는 함수
NODE *removeFirst()
{
    NODE *result = Q->next;
    Q->next = result->next;
    return result;
}

// 문자 전달받아 정점 반환하는 함수
VERTEX *getVertex(char name)
{
    return &(G.vertices[name - 'A']);
}

// 그래프 정점에 인접 간선 추가하는 함수
void addAdjacent(char v, int e)
{
    LINK *new = (LINK *)malloc(sizeof(LINK));
    new->edge = &(G.edges[e]);
    new->next = NULL;

    LINK *header = getVertex(v)->adjacent;

    if (header == NULL)
        getVertex(v)->adjacent = new;
    else
    {
        while (header->next != NULL)
            header = header->next;
        header->next = new;
    }
}

// 샘플 그래프를 생성 및 초기화하는 함수
void buildSampleGraph()
{
    n = 6, m = 9;
    G.vertices = (VERTEX *)malloc(sizeof(VERTEX) * n);
    G.edges = (EDGE *)malloc(sizeof(EDGE) * m);

    for (int i = 0; i < n; i++)
    {
        G.vertices[i].name = (char)i + 'A';
        G.vertices[i].adjacent = NULL;
    }

    // 샘플 데이터 초기화
    G.edges[0].origin = getVertex('A'), G.edges[0].destination = getVertex('B'), G.edges[0].weight = 8;
    addAdjacent('A', 0), addAdjacent('B', 0);

    G.edges[1].origin = getVertex('A'), G.edges[1].destination = getVertex('C'), G.edges[1].weight = 1;
    addAdjacent('A', 1), addAdjacent('C', 1);

    G.edges[2].origin = getVertex('A'), G.edges[2].destination = getVertex('D'), G.edges[2].weight = 4;
    addAdjacent('A', 2), addAdjacent('D', 2);

    G.edges[3].origin = getVertex('B'), G.edges[3].destination = getVertex('C'), G.edges[3].weight = 7;
    addAdjacent('B', 3), addAdjacent('C', 3);

    G.edges[4].origin = getVertex('B'), G.edges[4].destination = getVertex('E'), G.edges[4].weight = 4;
    addAdjacent('B', 4), addAdjacent('E', 4);

    G.edges[5].origin = getVertex('C'), G.edges[5].destination = getVertex('D'), G.edges[5].weight = 5;
    addAdjacent('C', 5), addAdjacent('D', 5);

    G.edges[6].origin = getVertex('C'), G.edges[6].destination = getVertex('E'), G.edges[6].weight = 3;
    addAdjacent('C', 6), addAdjacent('E', 6);

    G.edges[7].origin = getVertex('C'), G.edges[7].destination = getVertex('F'), G.edges[7].weight = 9;
    addAdjacent('C', 7), addAdjacent('F', 7);

    G.edges[8].origin = getVertex('D'), G.edges[8].destination = getVertex('F'), G.edges[8].weight = 4;
    addAdjacent('D', 8), addAdjacent('F', 8);
}

void printSampleGraph()
{
    for (int i = 0; i < n; i++)
    {
        printf("%c\n", G.vertices[i].name);
    }
}

// 동적할당된 메모리를 해제하는 함수
void freeMemory()
{
    // 모든 정점의 인접 리스트 링크를 해제
    for (int i = 0; i < n; i++)
    {
        LINK *current = G.vertices[i].adjacent;
        while (current != NULL)
        {
            LINK *next = current->next;
            free(current);
            current = next;
        }
    }

    // 정점 배열과 간선 배열 해제
    free(G.vertices);
    free(G.edges);

    // 큐의 모든 노드를 해제
    while (Q != NULL)
    {
        NODE *next = Q->next;
        free(Q);
        Q = next;
    }
}
