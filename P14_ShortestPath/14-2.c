#include <stdio.h>
#include <stdlib.h>

struct link
{
    int edge;
    struct link *next;
} typedef LINK;

struct edge
{
    int origin;
    int dest;
    int weight;
} typedef EDGE;

struct vertex
{
    int name;
    int distance;
    LINK *adjacent;
} typedef VERTEX;

struct graph
{
    VERTEX *vertices;
    EDGE *edges;
} typedef GRAPH;

void initGraph();
void addAdjacent(int vertex, int edge);

const int INFINITE = 99999;
GRAPH G;
int n, m, s;

int weight(int u, int v)
{
    for (int i = 0; i < m; i++)
    {
        if (G.edges[i].origin == u && G.edges[i].dest == v)
            return G.edges[i].weight;
    }
    return 0;
}

void bellmanFordShortestPaths()
{
    for (int i = 1; i < n + 1; i++)
        G.vertices[i].distance = INFINITE;
    G.vertices[s].distance = 0;

    for (int i = 0; i < n - 1; i++) // n-1번 반복
    {
        for (int e = 0; e < m; e++) // 모든 간선에 대해 relaxation
        {
            int u = G.edges[e].origin;
            int z = G.edges[e].dest;
            int weight = G.edges[e].weight;

            if (G.vertices[u].distance != INFINITE && G.vertices[u].distance + weight < G.vertices[z].distance)
            {
                G.vertices[z].distance = G.vertices[u].distance + weight;
            }
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

        G.edges[i].origin = uName;
        G.edges[i].dest = vName;
        G.edges[i].weight = weight;

        addAdjacent(uName, i);
    }

    bellmanFordShortestPaths();

    for (int i = 1; i < n + 1; i++)
    {
        if (i == s)
            continue;
        else if (G.vertices[i].distance > 20000)
            continue;
        
        printf("%d %d\n", G.vertices[i].name, G.vertices[i].distance);
    }
}

// 그래프 초기화
void initGraph()
{
    G.vertices = (VERTEX *)malloc(sizeof(VERTEX) * n + 1);
    G.edges = (EDGE *)malloc(sizeof(EDGE) * m);

    for (int i = 1; i < n + 1; i++)
    {
        G.vertices[i].name = i;
        G.vertices[i].adjacent = NULL;
    }
}

void addAdjacent(int vertex, int edge)
{

    LINK *new = (LINK *)malloc(sizeof(LINK));
    new->edge = edge;
    new->next = NULL;

    LINK *header = G.vertices[vertex].adjacent;
    if (header == NULL)
    {
        G.vertices[vertex].adjacent = new;
    }
    else
    {
        while (header->next != NULL)
            header = header->next;
        header->next = new;
    }
}
