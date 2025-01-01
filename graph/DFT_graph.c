/*
__DFTHelp: 깊이 우선 탐색(DFS) 보조 함수, 방문하지 않은 노드를 탐색하고 출력합니다.
DFT_recursive: 시작 노드를 지정하여 깊이 우선 탐색을 재귀적으로 수행합니다.
DFT_stack: 시작 노드가 주어진 경우 스택을 사용한 DFS를 수행합니다.

are_connected: 두 노드가 연결되어 있는지 확인하는 함수입니다.
areAllConnected: 그래프의 모든 노드가 연결되어 있는지 확인합니다.
countIslands: 연결된 컴포넌트(섬)의 개수를 세는 함수입니다.
hasCycle: 그래프에 사이클이 있는지 확인하는 함수입니다.
cycle_detect: 사이클을 감지하는 함수입니다.

is_connected: 그래프가 연결되어 있는지 확인하는 함수입니다.
shortest_path_bfs: BFS를 사용하여 두 노드 사이의 최단 경로를 찾는 함수입니다.
topological_sort: 방향 그래프에서 위상 정렬을 수행하는 함수입니다.
find_connected_components: 그래프의 연결 요소를 찾는 함수입니다.

detect_cycle_undirected: 무방향 그래프에서 사이클을 감지하는 함수입니다.
detect_cycle_directed: 방향 그래프에서 사이클을 감지하는 함수입니다
*/

//////// shortest_path_bfs를 위한 queue정의 ////
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100  // 큐의 최대 크기 설정

// 큐 구조체 정의
typedef struct {
    int items[MAX_QUEUE_SIZE];
    int front;
    int rear;
} queue_t;

// 큐 초기화 함수
void queue_init(queue_t* q) {
    q->front = -1;
    q->rear = -1;
}

// 큐가 비었는지 확인하는 함수
int queue_is_empty(queue_t* q) {
    return q->front == -1;
}

// 큐가 가득 찼는지 확인하는 함수
int queue_is_full(queue_t* q) {
    return q->rear == MAX_QUEUE_SIZE - 1;
}

// 큐에 아이템을 넣는 함수
void queue_enqueue(queue_t* q, int value) {
    if (queue_is_full(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (q->front == -1) {  // 큐가 비어 있으면
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

// 큐에서 아이템을 꺼내는 함수
int queue_dequeue(queue_t* q) {
    if (queue_is_empty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {  // 큐가 비어 있으면
        q->front = q->rear = -1;
    }
    return item;
}

// 큐의 첫 번째 아이템을 확인하는 함수
int queue_front(queue_t* q) {
    if (queue_is_empty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->items[q->front];
}

// 큐의 크기를 반환하는 함수
int queue_size(queue_t* q) {
    if (queue_is_empty(q)) {
        return 0;
    }
    return q->rear - q->front + 1;
}

// 큐의 상태를 출력하는 함수
void queue_print(queue_t* q) {
    if (queue_is_empty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
  int vertex;
  struct Node* next;
} Node;


typedef struct Graph {
  int totalVertices;
  int* visited;
  Node** adjLists;
} Graph;

/*
adjlist 예시
0: 1 -> 2
1: 0 -> 2 -> 3
2: 0 -> 1 -> 4
3: 1
4: 2
*/

Node* createNode(int v) {
  Node* newNode = malloc(sizeof(Node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}



void DFS(Graph* graph, int startVertex) {
    Node* adjList = graph->adjLists[startVertex];
    Node* temp = adjList;

    graph->visited[startVertex] = 1;
    printf("%d ", startVertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
    for (int i = 1; i < graph->totalVertices; ++i) {
        if (!graph->visited[i]) {
            DFS(graph, i);
            printf("\n"); // Uncomment if you want to distinguish between different connected components
        }
    }
}


Graph* createGraph(int v) {
  Graph* graph = malloc(sizeof(Graph));
  graph->totalVertices = v;
  graph->adjLists = malloc(v * sizeof(Node*));
  graph->visited = malloc(v * sizeof(int));

  for (int i = 0; i < v; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}



void addEdge(Graph* graph, int src, int dest) {
    // dest를 src의 인접 리스트에 정렬된 상태로 추가
    Node* newNode = createNode(dest);
    if (graph->adjLists[src] == NULL || graph->adjLists[src]->vertex > dest) {
        newNode->next = graph->adjLists[src];
        graph->adjLists[src] = newNode;
    } else {
        Node* current = graph->adjLists[src];
        while (current->next != NULL && current->next->vertex < dest) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    // src를 dest의 인접 리스트에 정렬된 상태로 추가 (무방향 그래프의 경우 추가하기)
    // newNode = createNode(src);
    // if (graph->adjLists[dest] == NULL || graph->adjLists[dest]->vertex > src) {
    //     newNode->next = graph->adjLists[dest];
    //     graph->adjLists[dest] = newNode;
    // } else {
    //     Node* current = graph->adjLists[dest];
    //     while (current->next != NULL && current->next->vertex < src) {
    //         current = current->next;
    //     }
    //     newNode->next = current->next;
    //     current->next = newNode;
    // }
}

/////혹은,
// void addEdge(Graph* graph, int src, int dest) {
//     // Add edge from src to dest
//     Node* newNode = createNode(dest);
//     newNode->next = graph->adjLists[src];
//     graph->adjLists[src] = newNode;

//     // Add edge from dest to src (for undirected graph)
//     newNode = createNode(src);
//     newNode->next = graph->adjLists[dest];
//     graph->adjLists[dest] = newNode;
// }



// 스택을 사용한 반복적 DFS (숫자가 낮은 노드가 우선순위를 가지도록 수정)
void DFSStack(Graph* graph, int startVertex) {
    int* stack = malloc(graph->totalVertices * sizeof(int));
    int top = -1;

    stack[++top] = startVertex;

    while (top != -1) {
        int vertex = stack[top--];

        if (graph->visited[vertex] == 0) {
            printf("%d ", vertex);
            graph->visited[vertex] = 1;
        }

        // 인접 리스트를 오름차순으로 스택에 푸시
        int neighbors[graph->totalVertices];
        int count = 0;

        Node* adjList = graph->adjLists[vertex];
        while (adjList != NULL) {
            if (graph->visited[adjList->vertex] == 0) {
                neighbors[count++] = adjList->vertex;
            }
            adjList = adjList->next;
        }

        // 인접 노드들을 오름차순으로 정렬하여 스택에 추가
        for (int i = count - 1; i >= 0; i--) {
            for (int j = 0; j < i; j++) {
                if (neighbors[j] > neighbors[j + 1]) {
                    int temp = neighbors[j];
                    neighbors[j] = neighbors[j + 1];
                    neighbors[j + 1] = temp;
                }
            }
            stack[++top] = neighbors[i];
        }
    }

    // 이어지지 않은 다른 컴포넌트(섬)도 탐색
    for (int i = 1; i < graph->totalVertices; ++i) {
        if (graph->visited[i] == 0) {
            stack[++top] = i;

            while (top != -1) {
                int vertex = stack[top--];

                if (graph->visited[vertex] == 0) {
                    printf("%d ", vertex);
                    graph->visited[vertex] = 1;
                }

                // 인접 리스트를 오름차순으로 스택에 푸시
                int neighbors[graph->totalVertices];
                int count = 0;

                Node* adjList = graph->adjLists[vertex];
                while (adjList != NULL) {
                    if (graph->visited[adjList->vertex] == 0) {
                        neighbors[count++] = adjList->vertex;
                    }
                    adjList = adjList->next;
                }

                // 인접 노드들을 오름차순으로 정렬하여 스택에 추가
                for (int i = count - 1; i >= 0; i--) {
                    for (int j = 0; j < i; j++) {
                        if (neighbors[j] > neighbors[j + 1]) {
                            int temp = neighbors[j];
                            neighbors[j] = neighbors[j + 1];
                            neighbors[j + 1] = temp;
                        }
                    }
                    stack[++top] = neighbors[i];
                }
            }
        }
    }

    free(stack);
}



void DFS2(Graph* graph, int startVertex) {
    Node* adjList = graph->adjLists[startVertex];
    Node* temp = adjList;

    graph->visited[startVertex] = 1;

    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (graph->visited[connectedVertex] == 0) {
            DFS2(graph, connectedVertex);
        }
        temp = temp->next;
    }
    // for (int i = 1; i < graph->totalVertices; ++i) {
    //     if (!graph->visited[i]) {
    //         DFS2(graph, i);
    //         // printf("\n"); // Uncomment if you want to distinguish between different connected components
    //     }
    // }
}

// 두 노드가 연결되어 있는지 확인하는 함수
int are_connected(Graph* graph, int src, int dest) {
    // 초기화
    for (int i = 0; i < graph->totalVertices; ++i) {
        graph->visited[i] = 0;
    }
    
    // DFS로 연결 여부 확인
    DFS2(graph, src);  // DFS를 사용하여 연결된 노드를 모두 방문
    
    return graph->visited[dest];
}


// 모든 노드가 연결되어 있는지 확인
int areAllConnected(Graph* graph) {
    for (int i = 1; i < graph->totalVertices; ++i) {
        if (graph->visited[i] == 0) {
            return 0;
        }
    }
    return 1;
}

// 방문 상태 초기화
void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->totalVertices; i++) {
        graph->visited[i] = 0;
    }
}

// 섬의 개수 세기
int countIslands(Graph* graph) {
    // resetVisited(graph);  // 방문 상태 초기화

    int islandCount = 0;
    for (int i = 1; i < graph->totalVertices; ++i) {
        if (graph->visited[i] == 0) {
            DFS2(graph, i);  // 또는 DFSStack(graph, i) 사용
            islandCount++;
        }
    }
    return islandCount;
}

// 사이클 여부 확인 (방향 그래프용)
int hasCycleHelper(Graph* graph, int vertex, int* recStack) {
    if (!graph->visited[vertex]) {
        graph->visited[vertex] = 1;
        recStack[vertex] = 1;

        Node* adjList = graph->adjLists[vertex];
        while (adjList != NULL) {
            int connectedVertex = adjList->vertex;
            if (!graph->visited[connectedVertex] && hasCycleHelper(graph, connectedVertex, recStack)) {
                return 1;
            } else if (recStack[connectedVertex]) {
                return 1;
            }
            adjList = adjList->next;
        }
    }
    recStack[vertex] = 0;
    return 0;
}

int hasCycle(Graph* graph) {
    int* recStack = malloc(graph->totalVertices * sizeof(int));
    for (int i = 0; i < graph->totalVertices; i++) {
        recStack[i] = 0;
    }

    for (int i = 1; i < graph->totalVertices; i++) {
        if (hasCycleHelper(graph, i, recStack)) {
            free(recStack);
            return 1;
        }
    }

    free(recStack);
    return 0;
}


// BFS를 사용하여 두 노드 사이의 최단 경로를 찾는 함수
int shortest_path_bfs(Graph* graph, int start, int end) {
    int* distance = malloc(graph->totalVertices * sizeof(int));
    int* parent = malloc(graph->totalVertices * sizeof(int));
    for (int i = 0; i < graph->totalVertices; ++i) {
        distance[i] = -1;  // 거리 초기화
        parent[i] = -1;    // 부모 노드 초기화
    }

    distance[start] = 0;
    parent[start] = -1;
    
    // 큐 초기화
    queue_t* q = queue_create();
    queue_enqueue(q, start);
    
    while (!queue_is_empty(q)) {
        int current = queue_dequeue(q);
        Node* adjList = graph->adjLists[current];
        while (adjList != NULL) {
            int neighbor = adjList->vertex;
            if (distance[neighbor] == -1) {  // 아직 방문하지 않았다면
                distance[neighbor] = distance[current] + 1;
                parent[neighbor] = current;
                queue_enqueue(q, neighbor);
                if (neighbor == end) {
                    queue_destroy(q);
                    free(distance);
                    free(parent);
                    return distance[end];  // 최단 거리 반환
                }
            }
            adjList = adjList->next;
        }
    }

    queue_destroy(q);
    free(distance);
    free(parent);
    return -1;  // 경로가 없다면 -1 반환
}

// 방향 그래프에서 위상 정렬을 수행하는 함수
int topological_sort_helper(Graph* graph, int vertex, int* visited, int* stack, int* stackIndex) {
    visited[vertex] = 1;
    Node* adjList = graph->adjLists[vertex];
    while (adjList != NULL) {
        int connectedVertex = adjList->vertex;
        if (!visited[connectedVertex]) {
            if (topological_sort_helper(graph, connectedVertex, visited, stack, stackIndex)) {
                return 1;  // 사이클이 존재하면 에러 반환
            }
        } else if (visited[connectedVertex] == 1) {
            return 1;  // 사이클 발견
        }
        adjList = adjList->next;
    }
    
    visited[vertex] = 2;  // 방문 완료 표시
    stack[*stackIndex] = vertex;
    (*stackIndex)--;
    return 0;
}

void topological_sort(Graph* graph) {
    int* visited = malloc(graph->totalVertices * sizeof(int));
    int* stack = malloc(graph->totalVertices * sizeof(int));
    int stackIndex = graph->totalVertices - 1;

    for (int i = 0; i < graph->totalVertices; ++i) {
        visited[i] = 0;  // 0: 방문하지 않음, 1: 방문 중, 2: 방문 완료
    }

    for (int i = 0; i < graph->totalVertices; ++i) {
        if (visited[i] == 0) {
            if (topological_sort_helper(graph, i, visited, stack, &stackIndex)) {
                printf("The graph has a cycle, cannot perform topological sort.\n");
                free(visited);
                free(stack);
                return;
            }
        }
    }

    printf("Topological sort: ");
    for (int i = 0; i < graph->totalVertices; ++i) {
        printf("%d ", stack[i]);
    }
    printf("\n");

    free(visited);
    free(stack);
}

// 그래프의 연결 요소를 찾는 함수
void find_connected_components(Graph* graph) {
    resetVisited(graph);
    int componentCount = 0;
    for (int i = 0; i < graph->totalVertices; ++i) {
        if (graph->visited[i] == 0) {
            componentCount++;
            printf("Component %d: ", componentCount);
            DFS(graph, i);
            printf("\n");
        }
    }
}

// 무방향 그래프에서 사이클을 감지하는 함수
int detect_cycle_undirected_helper(Graph* graph, int vertex, int parent, int* visited) {
    visited[vertex] = 1;
    Node* adjList = graph->adjLists[vertex];
    while (adjList != NULL) {
        int connectedVertex = adjList->vertex;
        if (visited[connectedVertex] == 0) {
            if (detect_cycle_undirected_helper(graph, connectedVertex, vertex, visited)) {
                return 1;
            }
        } else if (connectedVertex != parent) {
            return 1;  // 사이클 발견
        }
        adjList = adjList->next;
    }
    return 0;
}

int detect_cycle_undirected(Graph* graph) {
    int* visited = malloc(graph->totalVertices * sizeof(int));
    for (int i = 0; i < graph->totalVertices; ++i) {
        visited[i] = 0;
    }

    for (int i = 0; i < graph->totalVertices; ++i) {
        if (visited[i] == 0) {
            if (detect_cycle_undirected_helper(graph, i, -1, visited)) {
                free(visited);
                return 1;  // 사이클 존재
            }
        }
    }

    free(visited);
    return 0;  // 사이클 없음
}

// 방향 그래프에서 사이클을 감지하는 함수
int detect_cycle_directed_helper(Graph* graph, int vertex, int* visited, int* recStack) {
    if (!visited[vertex]) {
        visited[vertex] = 1;
        recStack[vertex] = 1;

        Node* adjList = graph->adjLists[vertex];
        while (adjList != NULL) {
            int connectedVertex = adjList->vertex;
            if (!visited[connectedVertex] && detect_cycle_directed_helper(graph, connectedVertex, visited, recStack)) {
                return 1;
            } else if (recStack[connectedVertex]) {
                return 1;  // 사이클 발견
            }
            adjList = adjList->next;
        }
    }
    recStack[vertex] = 0;
    return 0;
}

int detect_cycle_directed(Graph* graph) {
    int* visited = malloc(graph->totalVertices * sizeof(int));
    int* recStack = malloc(graph->totalVertices * sizeof(int));
    
    for (int i = 0; i < graph->totalVertices; ++i) {
        visited[i] = 0;
        recStack[i] = 0;
    }

    for (int i = 0; i < graph->totalVertices; ++i) {
        if (detect_cycle_directed_helper(graph, i, visited, recStack)) {
            free(visited);
            free(recStack);
            return 1;  // 사이클 존재
        }
    }

    free(visited);
    free(recStack);
    return 0;  // 사이클 없음
}


void displayGraph(Graph* graph) {
  int v;
  for (v = 1; v < graph->totalVertices; v++) {
    Node* temp = graph->adjLists[v];
    printf("%d ", v);
    while (temp) {
      printf("%d ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
  printf("\n");
}



int main() {
    int vertices = 9;
    Graph* graph = createGraph(vertices);

    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 8);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);
    addEdge(graph, 6, 7);
    addEdge(graph, 6, 8);
    addEdge(graph, 7, 8);

    // printf("\nThe Adjacency List of the Graph is:");
    // displayGraph(graph);
    printf("DFS traversal of the graph: \n");
    DFS(graph, 1);


    resetVisited(graph);

    printf("DFS Stack traversal starting from vertex 1: \n");
    DFSStack(graph, 1);
    printf("\n");

    resetVisited(graph);

    printf("Are all nodes connected? %s\n", areAllConnected(graph) ? "Yes" : "No");

    resetVisited(graph);

    printf("Number of islands: %d\n", countIslands(graph));

    resetVisited(graph);

    printf("Does the graph have a cycle? %s\n", hasCycle(graph) ? "Yes" : "No");

    // Cleanup
    for (int i = 0; i < vertices; i++) {
        Node* adjList = graph->adjLists[i];
        while (adjList != NULL) {
            Node* temp = adjList;
            adjList = adjList->next;
            free(temp);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);

    return 0;
}

// 만약 add, vertex 따로 준다면
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node {
  int vertex;
  struct Node* next;
} Node;

typedef struct Graph {
  int totalVertices;
  int* visited;
  Node** adjLists;
} Graph;

Node* createNode(int v) {
  Node* newNode = malloc(sizeof(Node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

void DFS(Graph* graph, int startVertex) {
    Node* adjList = graph->adjLists[startVertex];
    Node* temp = adjList;

    graph->visited[startVertex] = 1;
    printf("%d ", startVertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
    for (int i = 1; i < graph->totalVertices; ++i) {
        if (!graph->visited[i]) {
            DFS(graph, i);
            // printf("\n"); // Uncomment if you want to distinguish between different connected components
        }
    }
}

Graph* createGraph(int v) {
  Graph* graph = malloc(sizeof(Graph));
  graph->totalVertices = v + 1; // Adjust for 1-based index
  graph->adjLists = malloc((v + 1) * sizeof(Node*));
  graph->visited = malloc((v + 1) * sizeof(int));

  for (int i = 0; i <= v; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    if (graph->adjLists[src] == NULL || graph->adjLists[src]->vertex > dest) {
        newNode->next = graph->adjLists[src];
        graph->adjLists[src] = newNode;
    } else {
        Node* current = graph->adjLists[src];
        while (current->next != NULL && current->next->vertex < dest) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    // newNode = createNode(src);          //undirected graph일 경우 추가
    // if (graph->adjLists[dest] == NULL || graph->adjLists[dest]->vertex > src) {
    //     newNode->next = graph->adjLists[dest];
    //     graph->adjLists[dest] = newNode;
    // } else {
    //     Node* current = graph->adjLists[dest];
    //     while (current->next != NULL && current->next->vertex < src) {
    //         current = current->next;
    //     }
    //     newNode->next = current->next;
    //     current->next = newNode;
    // }
}



// 스택을 사용한 반복적 DFS (연결되지 않은 노드도 순회)
void DFSStack(Graph* graph, int startVertex) {
    int* stack = malloc(graph->totalVertices * sizeof(int));
    int top = -1;

    stack[++top] = startVertex;

    while (top != -1) {
        int vertex = stack[top--];

        if (graph->visited[vertex] == 0) {
            printf("%d ", vertex);
            graph->visited[vertex] = 1;
        }

        Node* adjList = graph->adjLists[vertex];
        int neighbors[graph->totalVertices];
        int count = 0;

        while (adjList != NULL) {
            if (graph->visited[adjList->vertex] == 0) {
                neighbors[count++] = adjList->vertex;
            }
            adjList = adjList->next;
        }

        // 인접 노드들을 오름차순으로 스택에 추가
        for (int i = count - 1; i >= 0; i--) {
            for (int j = 0; j < i; j++) {
                if (neighbors[j] > neighbors[j + 1]) {
                    int temp = neighbors[j];
                    neighbors[j] = neighbors[j + 1];
                    neighbors[j + 1] = temp;
                }
            }
            stack[++top] = neighbors[i];
        }
    }

    // 이어지지 않은 다른 컴포넌트도 탐색
    for (int i = 1; i < graph->totalVertices; ++i) {
        if (graph->visited[i] == 0) {
            stack[++top] = i;

            while (top != -1) {
                int vertex = stack[top--];

                if (graph->visited[vertex] == 0) {
                    printf("%d ", vertex);
                    graph->visited[vertex] = 1;
                }

                Node* adjList = graph->adjLists[vertex];
                int neighbors[graph->totalVertices];
                int count = 0;

                while (adjList != NULL) {
                    if (graph->visited[adjList->vertex] == 0) {
                        neighbors[count++] = adjList->vertex;
                    }
                    adjList = adjList->next;
                }

                for (int i = count - 1; i >= 0; i--) {
                    for (int j = 0; j < i; j++) {
                        if (neighbors[j] > neighbors[j + 1]) {
                            int temp = neighbors[j];
                            neighbors[j] = neighbors[j + 1];
                            neighbors[j + 1] = temp;
                        }
                    }
                    stack[++top] = neighbors[i];
                }
            }
        }
    }

    free(stack);
}

// 방문 상태 초기화
void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->totalVertices; i++) {
        graph->visited[i] = 0;
    }
}


void DFS2(Graph* graph, int startVertex) {
    Node* adjList = graph->adjLists[startVertex];
    Node* temp = adjList;

    graph->visited[startVertex] = 1;

    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (graph->visited[connectedVertex] == 0) {
            DFS2(graph, connectedVertex);
        }
        temp = temp->next;
    }
    // for (int i = 1; i < graph->totalVertices; ++i) {
    //     if (!graph->visited[i]) {
    //         DFS(graph, i);
    //         // printf("\n"); // Uncomment if you want to distinguish between different connected components
    //     }
    // }
}


// 두 노드가 연결되어 있는지 확인하는 함수
bool are_connected(Graph* graph, int src, int dest) {
    resetVisited(graph);
    DFS(graph, src);
    return graph->visited[dest] == 1;
}

// 모든 노드가 연결되어 있는지 확인
bool areAllConnected(Graph* graph) {
    resetVisited(graph);
    DFS2(graph, 1);

    for (int i = 1; i < graph->totalVertices; i++) {
        if (graph->visited[i] == 0) {
            return false;
        }
    }
    return true;
}

// 섬의 개수 세기
int countIslands(Graph* graph) {
    resetVisited(graph);

    int islandCount = 0;
    for (int i = 1; i < graph->totalVertices; ++i) {
        if (graph->visited[i] == 0) {
            DFS2(graph, i);
            islandCount++;
        }
    }
    return islandCount;
}

// 사이클 여부 확인 (방향 그래프용)
bool hasCycleHelper(Graph* graph, int vertex, bool* recStack) {
    if (graph->visited[vertex] == 0) {
        graph->visited[vertex] = 1;
        recStack[vertex] = 1;

        Node* adjList = graph->adjLists[vertex];
        while (adjList != NULL) {
            int connectedVertex = adjList->vertex;
            if (graph->visited[connectedVertex] == 0 && hasCycleHelper(graph, connectedVertex, recStack)) {
                return true;
            } else if (recStack[connectedVertex]) {
                return true;
            }
            adjList = adjList->next;
        }
    }
    recStack[vertex] = 0;
    return false;
}

bool hasCycle(Graph* graph) {
    resetVisited(graph);
    bool* recStack = malloc(graph->totalVertices * sizeof(bool));
    for (int i = 0; i < graph->totalVertices; i++) {
        recStack[i] = 0;
    }

    for (int i = 1; i < graph->totalVertices; i++) {
        if (hasCycleHelper(graph, i, recStack)) {
            free(recStack);
            return true;
        }
    }

    free(recStack);
    return false;
}


// BFS로 최단 경로 찾기
void shortest_path_bfs(Graph* graph, int start, int end) {
    int* parent = malloc(graph->totalVertices * sizeof(int));
    int* dist = malloc(graph->totalVertices * sizeof(int));
    for (int i = 0; i < graph->totalVertices; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    dist[start] = 0;
    Node* queue = NULL;
    Node* adjList = graph->adjLists[start];
    int current = start;

    while (current != NULL) {
        for (Node* neighbor = graph->adjLists[current]; neighbor != NULL; neighbor = neighbor->next) {
            if (dist[neighbor->vertex] == INT_MAX) {
                dist[neighbor->vertex] = dist[current] + 1;
                parent[neighbor->vertex] = current;
                queue = neighbor;
            }
        }
        current = queue;
    }
}

// 위상 정렬 함수
void topological_sort(Graph* graph) {
    int* inDegree = malloc(graph->totalVertices * sizeof(int));
    for (int i = 0; i < graph->totalVertices; i++) {
        inDegree[i] = 0;
    }

    for (int i = 1; i < graph->totalVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp != NULL) {
            inDegree[temp->vertex]++;
            temp = temp->next;
        }
    }

    Node* queue = NULL;
    for (int i = 1; i < graph->totalVertices; i++) {
        if (inDegree[i] == 0) {
            queue = i;
        }
    }

    while (queue != NULL) {
        int vertex = queue;
        printf("%d ", vertex);

        for (Node* adjList = graph->adjLists[vertex]; adjList != NULL; adjList = adjList->next) {
            if (--inDegree[adjList->vertex] == 0) {
                queue = adjList->vertex;
            }
        }
    }
}

// 연결된 컴포넌트 찾기
void find_connected_components(Graph* graph) {
    resetVisited(graph);
    for (int i = 1; i < graph->totalVertices; i++) {
        if (!graph->visited[i]) {
            DFS(graph, i);
            printf("\n");
        }
    }
}

// 무방향 그래프에서 사이클 감지
bool detect_cycle_undirected_helper(Graph* graph, int vertex, bool* visited, int parent) {
    visited[vertex] = true;
    for (Node* adjList = graph->adjLists[vertex]; adjList != NULL; adjList = adjList->next) {
        if (!visited[adjList->vertex]) {
            if (detect_cycle_undirected_helper(graph, adjList->vertex, visited, vertex)) {
                return true;
            }
        } else if (adjList->vertex != parent) {
            return true;
        }
    }
    return false;
}

bool detect_cycle_undirected(Graph* graph) {
    bool* visited = malloc(graph->totalVertices * sizeof(bool));
    for (int i = 0; i < graph->totalVertices; i++) {
        visited[i] = false;
    }

    for (int i = 1; i < graph->totalVertices; i++) {
        if (!visited[i]) {
            if (detect_cycle_undirected_helper(graph, i, visited, -1)) {
                return true;
            }
        }
    }

    return false;
}

// 방향 그래프에서 사이클 감지
bool detect_cycle_directed_helper(Graph* graph, int vertex, bool* visited, bool* recStack) {
    if (recStack[vertex]) {
        return true;
    }
    if (visited[vertex]) {
        return false;
    }

    visited[vertex] = true;
    recStack[vertex] = true;

    for (Node* adjList = graph->adjLists[vertex]; adjList != NULL; adjList = adjList->next) {
        if (detect_cycle_directed_helper(graph, adjList->vertex, visited, recStack)) {
            return true;
        }
    }

    recStack[vertex] = false;
    return false;
}

bool detect_cycle_directed(Graph* graph) {
    bool* visited = malloc(graph->totalVertices * sizeof(bool));
    bool* recStack = malloc(graph->totalVertices * sizeof(bool));
    for (int i = 0; i < graph->totalVertices; i++) {
        visited[i] = false;
        recStack[i] = false;
    }

    for (int i = 1; i < graph->totalVertices; i++) {
        if (!visited[i]) {
            if (detect_cycle_directed_helper(graph, i, visited, recStack)) {
                return true;
            }
        }
    }

    return false;
}

void displayGraph(Graph* graph) {
    int v;
    for (v = 1; v < graph->totalVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("%d ", v);
        while (temp) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}



void displayGraph(Graph* graph) {
  int v;
  for (v = 1; v < graph->totalVertices; v++) {
    Node* temp = graph->adjLists[v];
    printf("%d ", v);
    while (temp) {
      printf("%d ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
  printf("\n");
}

int main() {
    int vertices[] = {1, 2, 3, 4, 5, 6, 7, 8}; // 정점
    int edges[][2] = {
        {1, 2}, {1, 3}, {2, 8}, {3, 4}, {3, 5}, {4, 5}, {6, 7}, {6, 8}, {7, 8}
    }; // 간선
    int numVertices = sizeof(vertices) / sizeof(vertices[0]);
    int numEdges = sizeof(edges) / sizeof(edges[0]);

    Graph* graph = createGraph(numVertices);

    for (int i = 0; i < numEdges; i++) {
        addEdge(graph, edges[i][0], edges[i][1]);
    }

    // printf("\nThe Adjacency List of the Graph is:");
    // displayGraph(graph);
    printf("DFS traversal of the graph: \n");
    DFS(graph, 1);
    printf("\n");
    resetVisited(graph);

    printf("DFS Stack traversal of the graph starting from vertex 1: \n");
    DFSStack(graph, 1);
    printf("\n");

    printf("Are all nodes connected? %s\n", areAllConnected(graph) ? "Yes" : "No");

    printf("Number of islands: %d\n", countIslands(graph));

    printf("Does the graph have a cycle? %s\n", hasCycle(graph) ? "Yes" : "No");

    // Cleanup
    // for (int i = 0; i <= vertices; i++) {
    //     Node* adjList = graph->adjLists[i];
    //     while (adjList != NULL) {
    //         Node* temp = adjList;
    //         adjList = adjList->next;
    //         free(temp);
    //     }
    // }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);

    return 0;
}