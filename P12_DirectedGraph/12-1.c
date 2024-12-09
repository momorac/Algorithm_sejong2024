#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct incident
{
    int elem;
    struct incident *next;
} typedef INCIDENT;

struct edge
{
    int origin;
    int destination;
} typedef EDGE;

struct vertex
{
    char name;
    int inDegree;
    INCIDENT *inEdges;
    INCIDENT *outEdges;
} typedef VERTEX;

struct graph
{
    VERTEX *vertices;
    EDGE *edges;
} typedef GRAPH;

GRAPH graph;
int n, m; // n < 100, m < 1000
int topOrder[100];
int queue[100];
int front, rear;

void buildGraph();
void insertVertex(char vName, int i);
void insertDirectedEdge(char uName, char wName, int i);
int index_(char vName);
void addFirst(INCIDENT *H, int i);
void topologicalSort();
bool isEmpty();
void enqueue(int v);
int dequeue();
void freeGraph();

int main()
{
    buildGraph(); // 입력으로부터 그래프 구축

    topologicalSort(); // 그래프 위상정렬

    if (topOrder[0] == 0)
    {
        printf("0\n");
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            printf("%c ", graph.vertices[topOrder[i]].name);
        }
    }

    freeGraph();

    return 0;
}

void buildGraph()
{
    scanf("%d", &n);
    graph.vertices = (VERTEX *)malloc(sizeof(VERTEX) * n);

    char vName;
    for (int i = 0; i < n; i++)
    {
        getchar();
        scanf("%c", &vName);
        insertVertex(vName, i);
    }

    scanf("%d", &m);
    graph.edges = (EDGE *)malloc(sizeof(EDGE) * m);

    char uName, wName;
    for (int i = 0; i < m; i++)
    {
        getchar();
        scanf("%c %c", &uName, &wName);
        insertDirectedEdge(uName, wName, i);
    }
}

void insertVertex(char vName, int i)
{
    graph.vertices[i].name = vName;
    graph.vertices[i].outEdges = (INCIDENT *)malloc(sizeof(INCIDENT));
    graph.vertices[i].outEdges->next = NULL;

    graph.vertices[i].inEdges = (INCIDENT *)malloc(sizeof(INCIDENT));
    graph.vertices[i].inEdges->next = NULL;
    graph.vertices[i].inDegree = 0;
}

void insertDirectedEdge(char uName, char wName, int i)
{
    int u = index_(uName);
    int w = index_(wName);

    graph.edges[i].origin = u;
    graph.edges[i].destination = w;

    addFirst(graph.vertices[u].outEdges, i);
    addFirst(graph.vertices[u].inEdges, i);

    graph.vertices[w].inDegree++; // 정점 w의 진입차수 갱신
}

int index_(char vName)
{
    for (int i = 0; i < n; i++)
    {
        if (graph.vertices[i].name == vName)
            return i;
    }
    return 0;
}

void addFirst(INCIDENT *H, int i)
{
    INCIDENT *new = (INCIDENT *)malloc(sizeof(INCIDENT));
    new->elem = i;
    new->next = H->next;
    H->next = new;
}

void topologicalSort()
{
    // in[i] = 정점 i의 진입차수
    int in[100];

    INCIDENT *e;

    // 큐 초기화
    front = 0, rear = 0;
    for (int i = 0; i < 100; i++)
        queue[i] = 0;

    for (int i = 0; i < n; i++)
    {
        in[i] = graph.vertices[i].inDegree;
        if (in[i] == 0)
            enqueue(i);
    }

    int t = 1; // t = 위상순위
    int u, w;
    while (!isEmpty())
    {
        u = dequeue();
        topOrder[t] = u;
        t++;

        e = graph.vertices[u].outEdges;
        e = e->next;
        while (e != NULL)
        {
            w = graph.edges[e->elem].destination;
            in[w] -= 1;
            if (in[w] == 0)
                enqueue(w);

            e = e->next;
        }

        if (t <= n)
            topOrder[0] = 0;
        else
            topOrder[0] = 1;
    }
}

void enqueue(int v)
{
    queue[rear] = v;
    rear = (rear + 1) % 100;
}

int dequeue()
{
    int result = queue[front];
    queue[front] = 0;
    front = (front + 1) % 100;
    return result;
}

bool isEmpty()
{
    if (front == rear)
        return true;
    else
        return false;
}

void freeGraph()
{
    // 모든 정점의 inEdges와 outEdges의 INCIDENT 리스트 해제
    for (int i = 0; i < n; i++)
    {
        INCIDENT *current, *temp;

        // inEdges 해제
        current = graph.vertices[i].inEdges;
        while (current != NULL)
        {
            temp = current;
            current = current->next;
            free(temp);
        }

        // outEdges 해제
        current = graph.vertices[i].outEdges;
        while (current != NULL)
        {
            temp = current;
            current = current->next;
            free(temp);
        }
    }

    // 정점 배열 해제
    free(graph.vertices);

    // 간선 배열 해제
    free(graph.edges);
}
