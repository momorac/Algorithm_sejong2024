#include <stdio.h>
#include <stdlib.h>

/*
    최소신장트리 생성 알고리즘
    n은 1과 100 사이
    m은 1과 1000 사이
    정점의 번호는 1부터 n까지의 정수
    모든 정점에 대해 간선이 존재하고, 무방향간선
*/
const int INFINITE = 99999;

// 정점 구조체: 정점 번호(elem), 거리(distance), 부모(parent) 저장
struct vertex {
    int name;
    int distance;
    int parent;
} typedef VERTEX;

// 간선 구조체: 가중치(weight), 시작(origin), 도착(destination) 저장
struct edge {
    int weight;
    int origin;
    int destination;
} typedef EDGE;

// 큐의 노드 구조체: 정점 번호(vertex), 거리 포인터(distance), 다음 노드 포인터(next) 저장
struct node {
    int vertex;
    int *distance;
    struct node *next;
} typedef NODE;

// 그래프의 정점 및 간선 개수
int n, m;
// 정점 및 간선 리스트 포인터
VERTEX *vertices;
EDGE *edges;
// 우선순위 큐(단일 연결 리스트로 구현)
NODE *queue;

// 그래프 정보를 입력받아 초기화하는 함수
void buildGraph() {
    scanf("%d", &n); // 정점 개수 입력
    vertices = (VERTEX *)malloc(sizeof(VERTEX) * (n + 1)); // n+1개의 정점 리스트 초기화
    for (int i = 1; i <= n; i++) {
        vertices[i].name = i; // 정점에 i의 정수 번호 저장하기
    }

    scanf("%d", &m); // 간선 개수 입력
    edges = (EDGE *)malloc(sizeof(EDGE) * m); // m개의 간선 리스트 초기화

    // m개의 간선 정보 입력받기
    int uName, vName, weight;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &uName, &vName, &weight);
        edges[i].origin = uName;
        edges[i].destination = vName;
        edges[i].weight = weight;
    }
}

// 우선순위 큐를 초기화하는 함수
void initQueue() {
    // 헤더가 있는 단일 연결 리스트로 구현된 큐 초기화
    queue = (NODE *)malloc(sizeof(NODE));
    queue->vertex = 0;
    queue->distance = NULL; // distance를 NULL로 초기화
    queue->next = NULL;

    NODE *prev = queue;

    for (int i = 1; i <= n; i++) {
        NODE *new = (NODE *)malloc(sizeof(NODE));
        new->vertex = i;
        new->distance = &vertices[i].distance; // 정점의 distance 값을 참조
        new->next = NULL;

        prev->next = new; // 새 노드를 연결
        prev = new;
    }
}

// 우선순위 큐를 거리 기준으로 오름차순 정렬하는 함수
void reOrderQueue() {
    if (queue == NULL || queue->next == NULL) return;

    NODE *sorted = (NODE *)malloc(sizeof(NODE));
    sorted->next = NULL;

    NODE *current = queue->next;

    while (current != NULL) {
        NODE *nextNode = current->next; // 현재 노드의 다음 노드를 저장
        NODE *tmp = sorted;

        // 정렬된 위치를 탐색하여 삽입
        while (tmp->next != NULL && *(tmp->next->distance) < *(current->distance)) {
            tmp = tmp->next;
        }
        current->next = tmp->next; // 삽입
        tmp->next = current;

        current = nextNode; // 다음 노드로 이동
    }

    queue->next = sorted->next; // 정렬된 리스트로 갱신
    free(sorted); // 임시 헤더 메모리 해제
}

// 우선순위 큐에서 최소 거리의 정점을 제거하고 반환하는 함수
int removeMin() {
    NODE *min = queue->next; // 큐의 첫 번째 노드
    int result = min->vertex;

    queue->next = min->next; // 노드를 큐에서 제거
    free(min); // 제거된 노드 메모리 해제

    return result; // 제거된 정점 번호 반환
}

// 큐에 특정 정점이 포함되어 있는지 확인하는 함수
int isIncluded(int z) {
    NODE *p = queue->next;

    while (p != NULL) {
        if (p->vertex == z)
            return 1; // 정점이 포함되어 있으면 true 반환
        p = p->next;
    }
    return 0; // 정점이 없으면 false 반환
}

// 두 정점 간의 가중치를 반환하는 함수
int weight(int u, int z) {
    for (int i = 0; i < m; i++) {
        if ((edges[i].origin == u && edges[i].destination == z) || 
            (edges[i].origin == z && edges[i].destination == u))
            return edges[i].weight; // 가중치 반환
    }
    return -1; // 간선이 없으면 -1 반환
}

// 우선순위 큐에서 정점의 키 값을 교체하고 정렬을 유지하는 함수
void replaceKey(int node, int key) {
    NODE *p = queue;
    while (p != NULL) {
        if (p->vertex == node) {
            *(p->distance) = key; // 키 값 교체
            reOrderQueue(); // 정렬 재조정
            return;
        }
        p = p->next;
    }
}

// Prim-Jarnik 알고리즘을 통해 최소신장트리(MST) 생성
void primJarnikMST(int *mstWeight) {
    // 정점 초기화
    for (int i = 1; i <= n; i++) {
        vertices[i].distance = INFINITE; // 초기 거리를 무한대로 설정
        vertices[i].parent = 0; // 초기 부모를 0으로 설정
    }

    vertices[1].distance = 0; // 시작 정점의 거리 0으로 설정
    initQueue(); // 우선순위 큐 초기화

    while (queue->next != NULL) {
        int u = removeMin(); // 최소 거리의 정점을 제거
        printf(" %d", vertices[u].name); // MST에 추가된 정점 출력
        *mstWeight += vertices[u].distance; // MST 가중치 합산

        for (int e = 0; e < m; e++) {
            if (edges[e].origin == u || edges[e].destination == u) {
                int z = edges[e].origin == u ? edges[e].destination : edges[e].origin;
                int w = weight(u, z);

                if (isIncluded(z) && w < vertices[z].distance) {
                    vertices[z].distance = w; // 거리 갱신
                    vertices[z].parent = u; // 부모 설정
                    replaceKey(z, w); // 우선순위 큐에서 키 값 교체
                }
            }
        }
    }
}

int main() {
    int mstWeight = 0; // MST 가중치 초기값
    buildGraph(); // 그래프 생성
    primJarnikMST(&mstWeight); // MST 생성

    printf("\n%d", mstWeight); // MST 가중치 출력

    // 동적 메모리 해제
    free(vertices);
    free(edges);
    free(queue);

    return 0;
}
