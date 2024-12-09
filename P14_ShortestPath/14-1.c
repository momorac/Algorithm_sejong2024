#include <stdio.h>
#include <stdlib.h>

struct node
{
    int vertex;
    int *distance;
    struct node *next;
} typedef NODE;

struct link
{
    int edge;
    struct link *next;
} typedef LINK;

struct edge
{
    int weight;
    int start;
    int dest;
} typedef EDGE;

struct vertex
{
    int name;
    int distance;
    LINK *adjacent;
    NODE *locator;
} typedef VERTEX;

struct graph
{
    VERTEX *vertices;
    EDGE *edges;
} typedef GRAPH;

void initGraph();
void addAdjacent(int vertex, int edge);
void initQueue();
void reOrderQueue();
int removeMin();
void replaceKey(int node, int key);
int isIncluded(int v);
int weight(int u, int v);

const int INFINITE = 20000;
GRAPH G;
int n, m, s;
NODE *queue;

void dijkstraShortestPaths(int s)
{
    for (int i = 0; i < n; i++)
        G.vertices[i].distance = INFINITE;

    G.vertices[s - 1].distance = 0;

    initQueue(queue);

    while (queue->next != NULL)
    {
        int u = removeMin(queue);

        LINK *adj = G.vertices[u - 1].adjacent;
        while (adj != NULL)
        {
            int z = G.edges[adj->edge].start == u ? G.edges[adj->edge].dest : G.edges[adj->edge].start;
            if (isIncluded(z))
            {
                if (G.vertices[u - 1].distance + weight(u, z) < G.vertices[z - 1].distance)
                {
                    G.vertices[z - 1].distance = G.vertices[u - 1].distance + weight(u, z);
                    replaceKey(z, G.vertices[z - 1].distance);
                }
            }
            adj = adj->next;
        }
    }
}

int main()
{
    scanf("%d %d %d", &n, &m, &s);

    initGraph(G, n, m);

    // 간선 정보 입력받고 그래프 생성하기
    int uName, vName, weight;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &uName, &vName, &weight);

        G.edges[i].start = uName;
        G.edges[i].dest = vName;
        G.edges[i].weight = weight;

        addAdjacent(uName, i);
        addAdjacent(vName, i);
    }

    dijkstraShortestPaths(s);

    for (int i = 0; i < n; i++)
    {
        if (i + 1 == s)
            continue;
        else if (G.vertices[i].distance > 20)
            continue;
        printf("%d %d\n", G.vertices[i].name, G.vertices[i].distance);
    }
}

// 그래프 초기화
void initGraph()
{
    G.vertices = (VERTEX *)malloc(sizeof(VERTEX) * n);
    G.edges = (EDGE *)malloc(sizeof(EDGE) * m);

    for (int i = 0; i < n; i++)
    {
        G.vertices[i].name = i + 1;
        G.vertices[i].adjacent = NULL;
    }
}

void addAdjacent(int vertex, int edge)
{

    LINK *new = (LINK *)malloc(sizeof(LINK));
    new->edge = edge;
    new->next = NULL;

    LINK *header = G.vertices[vertex - 1].adjacent;
    if (header == NULL)
    {
        G.vertices[vertex - 1].adjacent = new;
    }
    else
    {
        while (header->next != NULL)
            header = header->next;
        header->next = new;
    }
}

void initQueue()
{
    // 헤더가 있는 단일 연결 리스트로 구현된 큐 초기화
    queue = (NODE *)malloc(sizeof(NODE));
    queue->vertex = 0;
    queue->distance = NULL;
    queue->next = NULL;

    NODE *prev = queue;

    for (int i = 0; i < n; i++)
    {
        NODE *new = (NODE *)malloc(sizeof(NODE));
        new->vertex = i + 1;
        new->distance = &(G.vertices[i].distance);
        new->next = NULL;

        prev->next = new;
        prev = new;
    }
    reOrderQueue(queue);
}

// 우선순위 큐를 거리 기준으로 오름차순 정렬하는 함수
void reOrderQueue()
{
    if (queue == NULL || queue->next == NULL)
        return;

    NODE *sorted = (NODE *)malloc(sizeof(NODE));
    sorted->next = NULL;

    NODE *current = queue->next;

    while (current != NULL)
    {
        NODE *nextNode = current->next; // 현재 노드의 다음 노드를 저장
        NODE *tmp = sorted;

        // 정렬된 위치를 탐색하여 삽입
        while (tmp->next != NULL && *(tmp->next->distance) < *(current->distance))
        {
            tmp = tmp->next;
        }
        current->next = tmp->next;
        tmp->next = current;

        current = nextNode;
    }

    queue->next = sorted->next;
    free(sorted);
}

// 우선순위 큐에서 최소 거리의 정점을 제거하고 반환하는 함수
int removeMin()
{
    NODE *min = queue->next;
    int result = min->vertex;

    queue->next = min->next;
    free(min);

    return result;
}

void replaceKey(int node, int key)
{
    NODE *p = queue;
    while (p != NULL)
    {
        if (p->vertex == node)
        {
            *(p->distance) = key;
            reOrderQueue(queue);
            return;
        }
        p = p->next;
    }
}

int isIncluded(int v)
{
    for (NODE *p = queue; p != NULL; p = p->next)
    {
        if (p->vertex == v)
            return 1;
    }
    return 0;
}

int weight(int u, int v)
{
    for (int i = 0; i < m; i++)
    {
        if ((G.edges[i].start == u && G.edges[i].dest == v) || (G.edges[i].start == v && G.edges[i].dest == u))
            return G.edges[i].weight;
    }
    return -1;
}
