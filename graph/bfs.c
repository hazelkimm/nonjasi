#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//////////////////
// BFS w/ queue //
//////////////////

// 1. Color 정의
typedef enum {
    WHITE,
    GRAY,
    BLACK
} Color;

// 2. Vertex 정의
typedef struct {
    Color color;
    int dist;
    int pi;
    int* adj;
    int adj_size;
} Vertex;

// 3. Graph 정의
typedef struct {
    Vertex* vertices;
    int numVertices;
} Graph;

// 큐 구현
typedef struct {
    int* array;
    int front;
    int rear;
    unsigned capacity;
} Queue;

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

int isEmpty(Queue* queue) {
    return queue->front == -1;
}

void enqueue(Queue* queue, int item) {
    if (isEmpty(queue))
        queue->front = 0;

    queue->rear++;
    queue->array[queue->rear] = item;
}

int dequeue(Queue* queue) {
    int item = queue->array[queue->front];

    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front++;

    return item;
}

// 모든 정점을 초기화하는 함수
void initializeVertices(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->vertices[i].color = WHITE;
        graph->vertices[i].dist = INT_MAX;
        graph->vertices[i].pi = -1;
    }
}

void BFS(Graph* graph, int s) {
    initializeVertices(graph); // 각 BFS 시작 시 초기화

    graph->vertices[s].color = GRAY;
    graph->vertices[s].dist = 0;
    graph->vertices[s].pi = -1;

    Queue* Q = createQueue(graph->numVertices);
    enqueue(Q, s);

    while (!isEmpty(Q)) {
        int u = dequeue(Q);

        for (int i = 0; i < graph->vertices[u].adj_size; i++) {
            int v = graph->vertices[u].adj[i];
            if (graph->vertices[v].color == WHITE) {
                graph->vertices[v].color = GRAY;
                graph->vertices[v].dist = graph->vertices[u].dist + 1;
                graph->vertices[v].pi = u;
                enqueue(Q, v);
            }
        }

        graph->vertices[u].color = BLACK;
    }

    free(Q->array);
    free(Q);
}

// Shortest Path
void printShortestPath(Graph* graph, int start, int goal) {
    BFS(graph, start);

    if (graph->vertices[goal].dist == INT_MAX) {
        printf("No path found from %d to %d\n", start, goal);
        return;
    }

    int path[graph->numVertices];
    int count = 0;
    for (int v = goal; v != -1; v = graph->vertices[v].pi) {
        path[count++] = v;
    }

    printf("Shortest path from %d to %d: ", start, goal);
    for (int i = count - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

// Check Connectivity
int areAllConnected(Graph* graph) {
    BFS(graph, 0);
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].color == WHITE) {
            return 0;
        }
    }
    return 1;
}

// Count Islands
// 통으로 연결되어있다면 1
int countIslands(Graph* graph) {
    int count = 0;

    initializeVertices(graph); // 모든 정점을 초기화

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].color == WHITE) {
            BFS(graph, i);
            count++;
        }
    }

    return count;
}

// Cycle Detection
int detectCycle(Graph* graph) {
    initializeVertices(graph); // 그래프 전체를 초기화

    for (int u = 0; u < graph->numVertices; u++) {
        if (graph->vertices[u].color == WHITE) {
            Queue* Q = createQueue(graph->numVertices);
            enqueue(Q, u);
            graph->vertices[u].pi = -1; // undirected라면 꼭 넣기, directed라면 불필요

            while (!isEmpty(Q)) {
                int v = dequeue(Q);

                for (int i = 0; i < graph->vertices[v].adj_size; i++) {
                    int w = graph->vertices[v].adj[i];
                    if (graph->vertices[w].color == WHITE) {
                        graph->vertices[w].color = GRAY;
                        graph->vertices[w].pi = v;
                        enqueue(Q, w);
                    } else if (graph->vertices[w].color == GRAY && graph->vertices[v].pi != w) { // undirected일 경우
                        free(Q->array);
                        free(Q);
                        return 1;  // Cycle found
                    }
                }

                graph->vertices[v].color = BLACK;
            }

            free(Q->array);
            free(Q);
        }
    }

    return 0;
}



//// 유방향 그래프의 사이클을 탐지하고 싶다면
// int detectCycle(Graph* graph) {
//     initializeVertices(graph); // 그래프 전체를 초기화

//     for (int u = 0; u < graph->numVertices; u++) {
//         if (graph->vertices[u].color == WHITE) {
//             Queue* Q = createQueue(graph->numVertices);
//             enqueue(Q, u);
//             graph->vertices[u].pi = -1; // 시작점의 부모 노드는 없음

//             while (!isEmpty(Q)) {
//                 int v = dequeue(Q);

//                 for (int i = 0; i < graph->vertices[v].adj_size; i++) {
//                     int w = graph->vertices[v].adj[i];
//                     if (graph->vertices[w].color == WHITE) {
//                         graph->vertices[w].color = GRAY;
//                         graph->vertices[w].pi = v;
//                         enqueue(Q, w);
//                     } else if (graph->vertices[w].color == GRAY) {
//                         // 유방향 그래프에서는 GRAY 노드를 다시 방문하면 사이클이 존재함을 의미
//                         free(Q->array);
//                         free(Q);
//                         return 1;  // Cycle found
//                     }
//                 }

//                 graph->vertices[v].color = BLACK;
//             }

//             free(Q->array);
//             free(Q);
//         }
//     }

//     return 0;
// }


int main() {
    int numVertex = 9;
    Graph graph;
    graph.numVertices = numVertex;
    graph.vertices = (Vertex*)malloc(numVertex * sizeof(Vertex));

    for (int i = 0; i < numVertex; i++) {
        graph.vertices[i].adj_size = 0;
    }

    graph.vertices[0].adj = (int[]){1, 2, 5};
    graph.vertices[0].adj_size = 3;
    graph.vertices[1].adj = (int[]){0, 3, 4};
    graph.vertices[1].adj_size = 3;
    graph.vertices[2].adj = (int[]){0, 3};
    graph.vertices[2].adj_size = 2;
    graph.vertices[3].adj = (int[]){1, 2, 7};
    graph.vertices[3].adj_size = 3;
    graph.vertices[4].adj = (int[]){1, 5, 7};
    graph.vertices[4].adj_size = 3;
    graph.vertices[5].adj = (int[]){0, 4, 6, 8};
    graph.vertices[5].adj_size = 4;
    graph.vertices[6].adj = (int[]){5, 7, 8};
    graph.vertices[6].adj_size = 3;
    graph.vertices[7].adj = (int[]){3, 4, 6};
    graph.vertices[7].adj_size = 3;
    graph.vertices[8].adj = (int[]){5, 6};
    graph.vertices[8].adj_size = 2;

    BFS(&graph, 1);

    for (int i = 0; i < numVertex; ++i) {
        printf("Vertex %d: Distance=%d, Parent=%d\n", i, graph.vertices[i].dist, graph.vertices[i].pi);
    }

    printf("\nShortest path from 0 to 8:");
    printShortestPath(&graph, 0, 8);

    printf("\nAre all nodes connected? %s", areAllConnected(&graph) ? "Yes" : "No");

    printf("\nNumber of islands: %d", countIslands(&graph));

    printf("\nDoes the graph have a cycle? %s", detectCycle(&graph) ? "Yes" : "No");

    free(graph.vertices);

    return 0;
}
