#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Edge 구조체 정의
typedef struct Edge {
    int src;
    int dst;
    int weight;
    struct Edge* next;
} Edge;

// Vertex 구조체 정의
typedef struct {
    int dist;
    int pi;
} Vertex;

// 그래프 구조체 정의
typedef struct {
    Vertex* vertices;
    Edge** adj;
    int numVertex;
} Graph;

// 스택 구조체 정의
typedef struct {
    int* items;
    int top;
    int capacity;
} Stack;

// 스택 초기화
Stack* initializeStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    stack->items = (int*)malloc(capacity * sizeof(int));
    if (!stack->items) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

// 스택이 비어있는지 확인
int isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

// 스택에 요소 추가
void push(Stack* stack, int item) {
    if (stack->top == stack->capacity - 1) {
        fprintf(stderr, "Stack overflow.\n");
        exit(EXIT_FAILURE);
    }

    stack->items[++stack->top] = item;
}

// 스택에서 요소 제거
int pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Stack underflow.\n");
        exit(EXIT_FAILURE);
    }

    return stack->items[stack->top--];
}

// 스택의 가장 위의 요소 반환
int top(Stack* stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    return stack->items[stack->top];
}

// 그래프 초기화
Graph* initializeGraph(int numVertex) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    graph->vertices = (Vertex*)malloc(numVertex * sizeof(Vertex));
    if (!graph->vertices) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    graph->adj = (Edge**)malloc(numVertex * sizeof(Edge*));
    if (!graph->adj) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numVertex; i++) {
        graph->adj[i] = NULL;
    }

    graph->numVertex = numVertex;

    return graph;
}

// 간선 추가
void addEdge(Graph* graph, int src, int dst, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    if (!newEdge) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newEdge->src = src;
    newEdge->dst = dst;
    newEdge->weight = weight;

    newEdge->next = graph->adj[src];
    graph->adj[src] = newEdge;
}

// 단일 소스 초기화
void initializeSingleSource(Vertex vertices[], int size, int source) {
    for (int i = 0; i < size; i++) {
        vertices[i].dist = INT_MAX;
        vertices[i].pi = -1;
    }
    vertices[source].dist = 0;
}

// Relaxation 함수
void relax(Vertex vertices[], const Edge* edge) {
    if (vertices[edge->src].dist != INT_MAX && vertices[edge->dst].dist > vertices[edge->src].dist + edge->weight) {
        vertices[edge->dst].dist = vertices[edge->src].dist + edge->weight;
        vertices[edge->dst].pi = edge->src;
    }
}

// DFS_VISIT 함수
void DFS_VISIT(int u, int* visited, Stack* finishStack, Edge** adj) {
    visited[u] = 1;

    Edge* currentEdge = adj[u];
    while (currentEdge) {
        if (!visited[currentEdge->dst]) {
            DFS_VISIT(currentEdge->dst, visited, finishStack, adj);
        }
        currentEdge = currentEdge->next;
    }

    push(finishStack, u);
}

// 위상 정렬 함수
Stack* topologicalSort(Edge** adj, int numVertex) {
    Stack* finishStack = initializeStack(numVertex);
    int* visited = (int*)calloc(numVertex, sizeof(int));

    for (int i = 0; i < numVertex; i++) {
        if (!visited[i]) {
            DFS_VISIT(i, visited, finishStack, adj);
        }
    }

    free(visited);
    return finishStack;
}

// DAG 최단 경로 함수
void dagShortestPaths(Graph* graph, int source) {
    Stack* finishStack = topologicalSort(graph->adj, graph->numVertex);
    initializeSingleSource(graph->vertices, graph->numVertex, source);

    while (!isStackEmpty(finishStack)) {
        int u = pop(finishStack);

        Edge* currentEdge = graph->adj[u];
        while (currentEdge) {
            relax(graph->vertices, currentEdge);
            currentEdge = currentEdge->next;
        }
    }

    free(finishStack->items);
    free(finishStack);
}

// 메인 함수
int main() {
    Graph* graph = initializeGraph(6);

    addEdge(graph, 0, 1, 5);
    addEdge(graph, 0, 2, 3);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 1, 3, 6);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 4, 4);
    addEdge(graph, 2, 5, 2);
    addEdge(graph, 3, 4, -1);
    addEdge(graph, 3, 5, 1);
    addEdge(graph, 4, 5, -2);

    int source = 1;
    dagShortestPaths(graph, source);

    printf("Shortest path from vertex %d:\n", source);
    for (int i = 0; i < graph->numVertex; i++) {
        printf("Vertex %d: Distance=%d, Predecessor=%d\n", i, graph->vertices[i].dist, graph->vertices[i].pi);
    }

    // 메모리 해제
    free(graph->vertices);
    for (int i = 0; i < graph->numVertex; i++) {
        Edge* currentEdge = graph->adj[i];
        while (currentEdge) {
            Edge* temp = currentEdge;
            currentEdge = currentEdge->next;
            free(temp);
        }
    }
    free(graph->adj);
    free(graph);

    return 0;
}
