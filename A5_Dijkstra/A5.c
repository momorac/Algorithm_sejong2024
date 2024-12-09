#include <stdio.h>
#include <stdlib.h>

struct edge
{
    int origin;
    int destination;
    int weight;
} typedef EDGE;

struct link
{
    EDGE *edge;
    struct link *next;
} typedef LINK;

struct vertex
{
    char name;
    int distance;
    LINK *adjacent;
} typedef VERTEX;

struct graph
{
    VERTEX *vertices;
    EDGE *edges;
} typedef GRAPH;

int n, m; // n:그래프 내 정점의 개수 / m:그래프 내 간선의 개수
GRAPH G;

// 샘플 그래프를 생성 및 초기화하는 함수
void buildSampleGraph()
{
    n = 6, m = 9;
    G.vertices = (VERTEX *)malloc(sizeof(VERTEX) * n);
    G.edges = (EDGE *)malloc(sizeof(EDGE) * m);

    for (int i = 0; i < n; i++)
    {
        G.vertices[i].name = (char)i + 'A';
    }

    G.edges[0].origin = 'A', G.edges[0].destination = 'B', G.edges[0].weight = 8;
    G.edges[1].origin = 'A', G.edges[1].destination = 'C', G.edges[1].weight = 1;
    G.edges[2].origin = 'A', G.edges[2].destination = 'D', G.edges[2].weight = 4;
    G.edges[3].origin = 'B', G.edges[3].destination = 'C', G.edges[3].weight = 7;
    G.edges[4].origin = 'B', G.edges[4].destination = 'E', G.edges[4].weight = 4;
    G.edges[5].origin = 'C', G.edges[5].destination = 'D', G.edges[5].weight = 5;
    G.edges[6].origin = 'C', G.edges[6].destination = 'E', G.edges[6].weight = 3;
    G.edges[7].origin = 'C', G.edges[7].destination = 'F', G.edges[7].weight = 9;
    G.edges[8].origin = 'D', G.edges[8].destination = 'F', G.edges[8].weight = 4;

    
}

    void printSampleGraph()
{
    for (int i = 0; i < n; i++)
    {
        printf("%c\n", G.vertices[i].name);
    }
}

int main()
{
    buildSampleGraph();
    printSampleGraph();
    return 0;
}