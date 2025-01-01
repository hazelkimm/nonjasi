// undi_graph 클래스:
//  - Undirected Graph (무방향 그래프)을 표현하는 클래스.
//  - add_edge: 그래프에 간선을 추가하는 함수.
//  - BFS: 주어진 root에서 시작하여 BFS 탐색을 수행하는 함수.
//  - shortestPath: BFS로 최단 경로를 찾는 함수.
//  - allConnected: 모든 노드가 연결되어 있는지 확인하는 함수.
//  - countIslands: 그래프에서 연결되지 않은 부분(섬)의 개수를 세는 함수.
//  - hasCycle: 그래프에 사이클이 존재하는지 탐지하는 함수

// dir_graph 클래스:
//  - Directed Graph (방향 그래프)을 표현하는 클래스.
//  - BFS: 주어진 root에서 시작하여 BFS 탐색을 수행하는 함수.
//  - shortestPath: BFS로 최단 경로를 찾는 함수.
//  - allConnected: 모든 노드가 연결되어 있는지 확인하는 함수.
//  - countIslands: 그래프에서 연결되지 않은 부분(섬)의 개수를 세는 함수.
//  - hasCycle: 그래프에 사이클이 존재하는지 탐지하는 함수.



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct {
    int vertices[MAX_VERTICES];
    int adjacencyList[MAX_VERTICES][MAX_VERTICES];
    int vertexCount;
    int edgeCount[MAX_VERTICES];
} Graph;

typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

void initializeGraph(Graph* g, int vertexCount) {
    g->vertexCount = vertexCount;
    for (int i = 0; i < vertexCount; i++) {
        g->vertices[i] = i;
        g->edgeCount[i] = 0;
    }
}

void addEdge(Graph* g, int v, int w) {
    g->adjacencyList[v][g->edgeCount[v]++] = w;
    // g->adjacencyList[w][g->edgeCount[w]++] = v; // For undirected graph
}

void initializeQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isQueueEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        printf("Queue is full\n");
        return;
    }
    if (isQueueEmpty(q)) {
        q->front = 0;
    }
    q->items[++q->rear] = value;
}

int dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front >= q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}


void BFS_Helper(Graph* g, int startVertex, bool* visited) {
    Queue q;
    initializeQueue(&q);

    visited[startVertex] = true;
    enqueue(&q, startVertex);

    while (!isQueueEmpty(&q)) {
        int currentVertex = dequeue(&q);
        printf("%d ", currentVertex);

        for (int i = 0; i < g->edgeCount[currentVertex]; i++) {
            int adjVertex = g->adjacencyList[currentVertex][i];
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(&q, adjVertex);
            }
        }
    }
}

void BFS_Helper2(Graph* g, int startVertex, bool* visited) {
    Queue q;
    initializeQueue(&q);

    visited[startVertex] = true;
    enqueue(&q, startVertex);

    while (!isQueueEmpty(&q)) {
        int currentVertex = dequeue(&q);
        // printf("%d ", currentVertex);

        for (int i = 0; i < g->edgeCount[currentVertex]; i++) {
            int adjVertex = g->adjacencyList[currentVertex][i];
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(&q, adjVertex);
            }
        }
    }
}

void BFS(Graph* g, int startNode) {
    bool visited[MAX_VERTICES] = {false};
    BFS_Helper(g, startNode, visited);
    for (int i = 0; i < g->vertexCount; i++) {
        if (!visited[i] && g->edgeCount[i] > 0) { // 실제로 연결된 노드만 탐색
            BFS_Helper(g, i, visited);
        }
    }
    printf("\n");
}


bool allConnected(Graph* g) {
    bool visited[MAX_VERTICES] = {false};
    int start_node = -1;

    for (int i = 0; i < g->vertexCount; i++) {
        if (g->edgeCount[i] > 0) {
            start_node = i;
            break;
        }
    }

    if (start_node == -1) return false; // 그래프에 간선이 없는 경우

    BFS_Helper2(g, start_node, visited);

    for (int i = 0; i < g->vertexCount; i++) {
        if (g->edgeCount[i] > 0 && !visited[i]) {
            return false; // 연결되지 않은 노드가 존재하면 False
        }
    }

    return true;
}

int countIslands(Graph* g) {
    bool visited[MAX_VERTICES] = {false};
    int island_count = 0;

    for (int i = 0; i < g->vertexCount; i++) {
        if (!visited[i] && g->edgeCount[i] > 0) {
            BFS_Helper2(g, i, visited);
            island_count++;
        }
    }

    return island_count;
}

int shortestPath(Graph* g, int start, int goal) {
    bool visited[MAX_VERTICES] = {false};
    int distance[MAX_VERTICES];
    int parent[MAX_VERTICES];
    Queue q;

    for (int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = -1;
        parent[i] = -1;
    }

    initializeQueue(&q);
    visited[start] = true;
    distance[start] = 0;
    enqueue(&q, start);

    while (!isQueueEmpty(&q)) {
        int v = dequeue(&q);
        for (int i = 0; i < g->edgeCount[v]; i++) {
            int w = g->adjacencyList[v][i];
            if (!visited[w]) {
                visited[w] = true;
                distance[w] = distance[v] + 1;
                parent[w] = v;
                enqueue(&q, w);

                if (w == goal) {
                    // 경로를 역순으로 추적하여 저장
                    int path[MAX_VERTICES];
                    int pathIndex = 0;
                    for (int current = w; current != -1; current = parent[current]) {
                        path[pathIndex++] = current;
                    }

                    // 저장된 경로를 역순으로 출력하여 start부터 goal까지 출력
                    printf("Shortest path from %d to %d: ", start, goal);
                    for (int j = pathIndex - 1; j >= 0; j--) {
                        printf("%d ", path[j]);
                    }
                    printf("\n");

                    return distance[goal];
                }
            }
        }
    }
    return -1;
}


bool hasCycleUtil(Graph* g, int v, bool visited[], bool recStack[]) {
    visited[v] = true;
    recStack[v] = true;

    for (int i = 0; i < g->edgeCount[v]; i++) {
        int w = g->adjacencyList[v][i];
        if (!visited[w] && hasCycleUtil(g, w, visited, recStack)) {
            return true;
        } else if (recStack[w]) {
            return true;
        }
    }

    recStack[v] = false;
    return false;
}

bool hasCycle(Graph* g) {
    bool visited[MAX_VERTICES] = {false};
    bool recStack[MAX_VERTICES] = {false};

    for (int i = 0; i < g->vertexCount; i++) {
        if (!visited[i]) {
            if (hasCycleUtil(g, i, visited, recStack)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    Graph graph;
    initializeGraph(&graph, 9); // 9 vertices labeled 0 to 8

    addEdge(&graph, 1, 2);
    addEdge(&graph, 1, 3);
    addEdge(&graph, 2, 8);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 3, 5);
    addEdge(&graph, 4, 5);
    addEdge(&graph, 6, 7);
    addEdge(&graph, 6, 8);
    addEdge(&graph, 7, 8);

    printf("BFS starting from vertex 1:\n");
    BFS(&graph, 1);

    printf("Are all nodes connected? %s\n", allConnected(&graph) ? "Yes" : "No");
    printf("Number of islands: %d\n", countIslands(&graph));

    int distance = shortestPath(&graph, 1, 5);
    if (distance != -1) {
        printf("Shortest distance from 1 to 5: %d\n", distance);
    } else {
        printf("No path from 1 to 5\n");
    }

    printf("Does the graph have a cycle? %s\n", hasCycle(&graph) ? "Yes" : "No");

    return 0;
}





#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10
#define MAX_VERTICES 50

typedef int element;
typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void error(const char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void queue_init(QueueType* q) {
    q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

int is_full(QueueType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
    if (is_full(q)) {
        error("Queue overflow");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (is_empty(q)) {
        error("Queue underflow");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}





typedef struct {
    int n;  // Number of vertices
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;



int visited[MAX_VERTICES];


void graph_init(GraphType* g) {
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++) {
        for (c = 0; c < MAX_VERTICES; c++) {
            g->adj_mat[r][c] = 0;
        }
    }
}

void insert_vertex(GraphType* g, int v) {
    if (v > MAX_VERTICES) {
        fprintf(stderr, "Graph overflow\n");
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "Graph index error\n");
        return;
    }
    g->adj_mat[start][end] = 1;
    // g->adj_mat[end][start] = 1; // Remove this line for directed graph
}

void BFS_Helper(GraphType* g, int v, bool* visited) {
    int w;
    QueueType q;

    queue_init(&q);
    visited[v] = TRUE;
    printf("%d ", v);
    enqueue(&q, v);
    while (!is_empty(&q)) {
        v = dequeue(&q);
        for (w = 1; w < g->n; w++) {
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = TRUE;
                printf("%d ", w);
                enqueue(&q, w);
            }
        }
    }
}


void BFS_Helper2(GraphType* g, int v, bool* visited) {
    int w;
    QueueType q;

    queue_init(&q);
    visited[v] = TRUE;
    // printf("%d ", v);
    enqueue(&q, v);
    while (!is_empty(&q)) {
        v = dequeue(&q);
        for (w = 0; w < g->n; w++) {
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = TRUE;
                // printf("%d ", w);
                enqueue(&q, w);
            }
        }
    }
}

void BFS(GraphType* g, int startNode) {
    bool visited[MAX_VERTICES] = {FALSE};
    BFS_Helper(g, startNode, visited);
    for (int i = 0; i < g->n; i++) {
        if (!visited[i]) {
            BFS_Helper(g, i, visited);
        }
    }
}



bool allConnected(GraphType* g) {
    bool visited[MAX_VERTICES] = {FALSE};
    int count = 0;

    BFS_Helper2(g, 0, visited);
    for (int i = 0; i < g->n+1; i++) {
        if (visited[i]) count++;
    }
    printf("count: %d\n", count);
    printf("vertex: %d\n", g->n);

    return count == g->n;
}

int countIslands(GraphType* g) {
    bool visited[MAX_VERTICES] = {FALSE};
    int island_count = 0;

    for (int i = 0; i < g->n; i++) {
        if (!visited[i]) {
            BFS_Helper2(g, i, visited);
            island_count++;
        }
    }

    return island_count;
}

void printPath(int parent[], int v) {
    if (parent[v] == -1) {
        printf("%d ", v);
        return;
    }
    printPath(parent, parent[v]);
    printf("%d ", v);
}

int shortestPath(GraphType* g, int start, int goal) {
    bool visited[MAX_VERTICES] = {FALSE};
    int distance[MAX_VERTICES];
    int parent[MAX_VERTICES];  // 배열 추가: 각 노드의 부모 노드를 추적
    QueueType q;

    queue_init(&q);
    for (int i = 0; i < g->n; i++) {
        distance[i] = -1;
        parent[i] = -1;  // 초기화
    }

    visited[start] = TRUE;
    distance[start] = 0;
    enqueue(&q, start);

    while (!is_empty(&q)) {
        int v = dequeue(&q);
        for (int w = 0; w < g->n; w++) {
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = TRUE;
                distance[w] = distance[v] + 1;
                parent[w] = v;  // 부모 노드를 기록
                enqueue(&q, w);
                if (w == goal) {
                    printf("Shortest path from %d to %d: ", start, goal);
                    printPath(parent, w);  // 경로를 출력
                    printf("\n");
                    return distance[w];
                }
            }
        }
    }
    return -1;  // 경로를 찾지 못한 경우
}



bool hasCycleUtil(GraphType* g, int v, bool visited[], bool recStack[]) {
    visited[v] = TRUE;
    recStack[v] = TRUE;

    for (int w = 0; w < g->n; w++) {
        if (g->adj_mat[v][w]) {  // 간선이 존재하는 경우
            if (!visited[w] && hasCycleUtil(g, w, visited, recStack)) {
                return TRUE;
            } else if (recStack[w]) {
                return TRUE;
            }
        }
    }

    recStack[v] = FALSE;  // 재귀 호출 스택에서 제거
    return FALSE;
}

bool hasCycle(GraphType* g) {
    bool visited[MAX_VERTICES] = {FALSE};
    bool recStack[MAX_VERTICES] = {FALSE};  // 재귀 호출 스택

    for (int i = 0; i < g->n; i++) {
        if (!visited[i]) {
            if (hasCycleUtil(g, i, visited, recStack)) {
                return TRUE;
            }
        }
    }
    return FALSE;
}


int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    for (int i = 0; i < 9; i++) {
        insert_vertex(g, i);
    }
    
    insert_edge(g, 0, 1);
    insert_edge(g, 1, 2);
    insert_edge(g, 1, 3);
    insert_edge(g, 2, 8);
    insert_edge(g, 3, 4);
    insert_edge(g, 3, 5);
    insert_edge(g, 4, 5);
    insert_edge(g, 6, 7);
    insert_edge(g, 6, 8);
    insert_edge(g, 7, 8);

    printf("BFS starting from vertex 0:\n");
    BFS(g, 0);
    //0 1 2 3 4 5 6 7 8
    printf("\n");

    printf("Are all nodes connected? %s\n", allConnected(g) ? "Yes" : "No");
    printf("Number of islands: %d\n", countIslands(g));
    
    int distance = shortestPath(g, 1, 5);

    printf("Shortest distance from 1 to 5: %d\n", distance);
    

    printf("Does the graph have a cycle? %s\n", hasCycle(g) ? "Yes" : "No");

    free(g);
    return 0;
}







// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// #define TRUE 1
// #define FALSE 0
// #define MAX_QUEUE_SIZE 50
// #define MAX_VERTICES 50

// typedef int element;
// typedef struct {
//     element queue[MAX_QUEUE_SIZE];
//     int front, rear;
// } QueueType;

// void error(const char* message) {
//     fprintf(stderr, "%s\n", message);
//     exit(1);
// }

// void queue_init(QueueType* q) {
//     q->front = q->rear = 0;
// }

// int is_empty(QueueType* q) {
//     return (q->front == q->rear);
// }

// int is_full(QueueType* q) {
//     return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
// }

// void enqueue(QueueType* q, element item) {
//     if (is_full(q)) {
//         error("Queue overflow");
//     }
//     q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
//     q->queue[q->rear] = item;
// }

// element dequeue(QueueType* q) {
//     if (is_empty(q)) {
//         error("Queue underflow");
//     }
//     q->front = (q->front + 1) % MAX_QUEUE_SIZE;
//     return q->queue[q->front];
// }

// typedef struct {
//     int n;  // Number of vertices
//     int adj_mat[MAX_VERTICES][MAX_VERTICES];
// } GraphType;

// void graph_init(GraphType* g) {
//     int r, c;
//     g->n = 0;
//     for (r = 0; r < MAX_VERTICES; r++) {
//         for (c = 0; c < MAX_VERTICES; c++) {
//             g->adj_mat[r][c] = 0;
//         }
//     }
// }

// void insert_vertex(GraphType* g, int v) {
//     if (v >= MAX_VERTICES) {
//         fprintf(stderr, "Graph overflow\n");
//         return;
//     }
//     g->n++;
// }


// void insert_edge(GraphType* g, int start, int end) {
//     if (start >= MAX_VERTICES || end >= MAX_VERTICES) {
//         fprintf(stderr, "Graph index error\n");
//         return;
//     }
//     g->adj_mat[start][end] = 1;
//     g->adj_mat[end][start] = 1; // Remove this line for directed graph
// }

// void BFS_Helper(GraphType* g, int v, bool* visited) {
//     int w;
//     QueueType q;

//     queue_init(&q);
//     visited[v] = TRUE;
//     printf("%d ", v);
//     enqueue(&q, v);
//     while (!is_empty(&q)) {
//         v = dequeue(&q);
//         for (w = 1; w < g->n; w++) {
//             if (g->adj_mat[v][w] && !visited[w]) {
//                 visited[w] = TRUE;
//                 printf("%d ", w);
//                 enqueue(&q, w);
//             }
//         }
//     }
// }


// void BFS_Helper2(GraphType* g, int v, bool* visited) {
//     int w;
//     QueueType q;

//     queue_init(&q);
//     visited[v] = TRUE;
//     // printf("%d ", v);
//     enqueue(&q, v);
//     while (!is_empty(&q)) {
//         v = dequeue(&q);
//         for (w = 1; w < g->n; w++) {
//             if (g->adj_mat[v][w] && !visited[w]) {
//                 visited[w] = TRUE;
//                 // printf("%d ", w);
//                 enqueue(&q, w);
//             }
//         }
//     }
// }

// void BFS(GraphType* g, int startNode) {
//     bool visited[MAX_VERTICES] = {FALSE};
//     BFS_Helper(g, startNode, visited);
//     for (int i = 1; i < g->n; i++) {
//         if (!visited[i]) {
//             BFS_Helper(g, i, visited);
//         }
//     }
// }



// bool allConnected(GraphType* g) {
//     bool visited[MAX_VERTICES] = {FALSE};
//     int count = 0;

//     BFS_Helper2(g, 1, visited);  // BFS를 시작하는 첫 번째 노드
//     for (int i = 1; i < g->n; i++) {
//         if (visited[i]) count++;
//     }
//     printf("count: %d\n", count);
//     printf("vetex: %d\n",g->n -1); 
//     return count == g->n - 1;  // 모든 노드가 연결되어 있는지 확인
// }

// int countIslands(GraphType* g) {
//     bool visited[MAX_VERTICES] = {FALSE};
//     int island_count = 0;

//     for (int i = 1; i < g->n; i++) {
//         if (!visited[i]) {
//             BFS_Helper2(g, i, visited);
//             island_count++;
//         }
//     }

//     return island_count;
// }

// void printPath(int parent[], int v) {
//     if (parent[v] == -1) {
//         printf("%d ", v);
//         return;
//     }
//     printPath(parent, parent[v]);
//     printf("%d ", v);
// }

// int shortestPath(GraphType* g, int start, int goal) {
//     bool visited[MAX_VERTICES] = {FALSE};
//     int distance[MAX_VERTICES];
//     int parent[MAX_VERTICES];
//     QueueType q;

//     queue_init(&q);
//     for (int i = 0; i < MAX_VERTICES; i++) {
//         distance[i] = -1;
//         parent[i] = -1;  // 초기화
//     }

//     visited[start] = TRUE;
//     distance[start] = 0;
//     enqueue(&q, start);

//     while (!is_empty(&q)) {
//         int v = dequeue(&q);
//         for (int w = 0; w < g->n; w++) {
//             if (g->adj_mat[v][w] && !visited[w]) {
//                 visited[w] = TRUE;
//                 distance[w] = distance[v] + 1;
//                 parent[w] = v;  // 부모 노드 기록
//                 enqueue(&q, w);
//                 if (w == goal) {
//                     printf("Shortest path from %d to %d: ", start, goal);
//                     printPath(parent, w);
//                     printf("\n");
//                     return distance[w];
//                 }
//             }
//         }
//     }
//     return -1;
// }

// bool DFS_cycle_detect(GraphType* g, int v, bool visited[], bool recStack[]) {
//     visited[v] = true;
//     recStack[v] = true;

//     for (int w = 0; w < g->n; w++) {
//         if (g->adj_mat[v][w]) {  // 인접한 경우
//             if (!visited[w] && DFS_cycle_detect(g, w, visited, recStack)) {
//                 return true;
//             } else if (recStack[w]) {  // 재귀 스택에 있는 노드가 다시 발견되면 사이클 존재
//                 return true;
//             }
//         }
//     }

//     recStack[v] = false;  // 함수 호출이 끝나면 재귀 스택에서 제거
//     return false;
// }

// bool hasCycle(GraphType* g) {
//     bool visited[MAX_VERTICES] = {false};
//     bool recStack[MAX_VERTICES] = {false};  // 재귀 호출 스택

//     for (int i = 0; i < g->n; i++) {
//         if (!visited[i]) {
//             if (DFS_cycle_detect(g, i, visited, recStack)) {
//                 return true;
//             }
//         }
//     }
//     return false;
// }

// int main(void) {
//     int vertices[] = {1, 2, 3, 4, 5, 6, 7, 8}; // 정점 번호를 0부터 시작하도록 조정
//     int edges[][2] = {
//         {1, 2}, {1, 3}, {2, 8}, {3, 4}, {3, 5}, {4, 5}, {6, 7}, {6, 8}, {7, 8}
//     }; // 간선
//     int numVertices = sizeof(vertices) / sizeof(vertices[0]);
//     int numEdges = sizeof(edges) / sizeof(edges[0]);
   
//     GraphType* g = (GraphType*)malloc(sizeof(GraphType));
//     graph_init(g);

//     for (int i = 0; i < numVertices+1; i++) {
//         insert_vertex(g, vertices[i]);
//     }

//     for (int i = 0; i < numEdges; i++) {
//         insert_edge(g, edges[i][0], edges[i][1]);
//     }

//     printf("BFS starting from vertex 1:\n");
//     BFS(g, 1);
//     // 1 2 3 8 4 5 6 7
//     printf("\n");

//     printf("Are all nodes connected? %s\n", allConnected(g) ? "Yes" : "No");
//     printf("Number of islands: %d\n", countIslands(g));
    
//     int distance = shortestPath(g, 1, 5);
//     if (distance != -1) {
//         printf("Shortest distance from 1 to 5: %d\n", distance);
//     } else {
//         printf("No path from 1 to 5\n");
//     }

//     printf("Does the graph have a cycle? %s\n", hasCycle(g) ? "Yes" : "No");

//     free(g);
//     return 0;
// }