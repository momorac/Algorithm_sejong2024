
#include <stdio.h>
#include <stdlib.h>

struct incidence
{
    int edge;
    struct incidence *next;
} typedef INCIDENCE;

struct vertices
{
    INCIDENCE *incidence;
    int elem;
    int label;
} typedef VERTICES;

struct edge
{
    int vertex1;
    int vertex2;
    int label;
} typedef EDGE;

struct graph
{
    VERTICES *vertices;
    EDGE *edges;
    int edgeSize;
    int size;
} typedef GRAPH;

INCIDENCE *getIncidence(int edge)
{
    INCIDENCE *node = (INCIDENCE *)malloc(sizeof(INCIDENCE));

    node->next = NULL;
    node->edge = edge;

    return node;
}

void initGraph(GRAPH *graph, int n, int m);
void insertIncidence(int v1, int v2, INCIDENCE *incidence, GRAPH *graph);
void insertEdge(int v1, int v2, GRAPH *graph);
void DFS(GRAPH *graph, int s);
void rDFS(GRAPH *graph, int s);

int main()
{
    GRAPH graph;
    int n, m, s;
    int u, v;

    scanf("%d %d %d", &n, &m, &s);

    initGraph(&graph, n, m);

    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);

        insertEdge(u, v, &graph);
    }

    DFS(&graph, s);

    return 0;
}

void initGraph(GRAPH *graph, int n, int m)
{
    graph->size = n;
    graph->edgeSize = 0;

    graph->vertices = (VERTICES *)malloc(sizeof(VERTICES) * (n + 1));
    graph->edges = (EDGE *)malloc(sizeof(EDGE) * m);

    for (int i = 1; i <= graph->size; i++)
    {
        graph->vertices[i].incidence = NULL;
        graph->vertices[i].elem = i;
    }
}


void insertIncidence(int v1, int v2, INCIDENCE *incidence, GRAPH *graph)
{
    EDGE *edges = graph->edges;
    VERTICES *vertices = graph->vertices;
    INCIDENCE *current = vertices[v1].incidence;
    INCIDENCE *previous = NULL;

    while (current != NULL)
    {
        int other = (edges[current->edge].vertex1 == v1) ? edges[current->edge].vertex2 : edges[current->edge].vertex1;

        // v2보다 큰 정점이 나오면 종료
        if (other > v2)
            break;

        previous = current;
        current = current->next;
    }

    // 새 incidence를 삽입
    incidence->next = current;
    if (previous == NULL)
        vertices[v1].incidence = incidence; // 리스트의 첫 번째에 삽입
    else
        previous->next = incidence; // 중간 또는 끝에 삽입
}

void insertEdge(int v1, int v2, GRAPH *graph)
{
    EDGE *edges = graph->edges;
    INCIDENCE *incidence1, *incidence2;
    int index = -1;

    for (int i = 0; i < graph->edgeSize; i++)
    {
        if ((edges[i].vertex1 == v1 && edges[i].vertex2 == v2) ||
            (edges[i].vertex1 == v2 && edges[i].vertex2 == v1))
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        index = graph->edgeSize;
        edges[index].vertex1 = v1;
        edges[index].vertex2 = v2;
        graph->edgeSize++;
    }

    incidence1 = getIncidence(index);
    insertIncidence(v1, v2, incidence1, graph);

    if (v1 != v2)
    {
        incidence2 = getIncidence(index);
        insertIncidence(v2, v1, incidence2, graph);
    }
}

void DFS(GRAPH *graph, int s)
{
    for (int i = 1; i <= graph->size; i++)
    {
        graph->vertices[i].label = 0;
    }
    for (int i = 0; i < graph->edgeSize; i++)
    {
        graph->edges[i].label = 0;
    }

    rDFS(graph, s);
}

void rDFS(GRAPH *graph, int s)
{
    EDGE *edges = graph->edges;
    VERTICES *vertices = graph->vertices;
    INCIDENCE *current = vertices[s].incidence;
    printf("%d\n", s);
    vertices[s].label = -1;

    while (current != NULL)
    {
        if (edges[current->edge].label == 0)
        {
            // 다른 정점을 계산
            int other = (edges[current->edge].vertex1 == vertices[s].elem)
                            ? edges[current->edge].vertex2
                            : edges[current->edge].vertex1;

            if (vertices[other].label == 0)
            {
                edges[current->edge].label = -1;
                rDFS(graph, other);
            }
        }
        current = current->next;
    }
}
