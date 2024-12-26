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
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>


// typedef struct Node {
//   int vertex;
//   struct Node* next;
// } Node;

// typedef struct Graph {
//   int totalVertices;
//   int* visited;
//   Node** adjLists;
// } Graph;

// Node* createNode(int v) {
//   Node* newNode = malloc(sizeof(Node));
//   newNode->vertex = v;
//   newNode->next = NULL;
//   return newNode;
// }

// void DFS(Graph* graph, int startVertex) {
//     Node* adjList = graph->adjLists[startVertex];
//     Node* temp = adjList;

//     graph->visited[startVertex] = 1;
//     printf("%d ", startVertex);

//     while (temp != NULL) {
//         int connectedVertex = temp->vertex;
//         if (graph->visited[connectedVertex] == 0) {
//             DFS(graph, connectedVertex);
//         }
//         temp = temp->next;
//     }
//     for (int i = 1; i < graph->totalVertices; ++i) {
//         if (!graph->visited[i]) {
//             DFS(graph, i);
//             // printf("\n"); // Uncomment if you want to distinguish between different connected components
//         }
//     }
// }

// Graph* createGraph(int v) {
//   Graph* graph = malloc(sizeof(Graph));
//   graph->totalVertices = v + 1; // Adjust for 1-based index
//   graph->adjLists = malloc((v + 1) * sizeof(Node*));
//   graph->visited = malloc((v + 1) * sizeof(int));

//   for (int i = 0; i <= v; i++) {
//     graph->adjLists[i] = NULL;
//     graph->visited[i] = 0;
//   }
//   return graph;
// }

// void addEdge(Graph* graph, int src, int dest) {
//     Node* newNode = createNode(dest);
//     if (graph->adjLists[src] == NULL || graph->adjLists[src]->vertex > dest) {
//         newNode->next = graph->adjLists[src];
//         graph->adjLists[src] = newNode;
//     } else {
//         Node* current = graph->adjLists[src];
//         while (current->next != NULL && current->next->vertex < dest) {
//             current = current->next;
//         }
//         newNode->next = current->next;
//         current->next = newNode;
//     }

//     // newNode = createNode(src);          //undirected graph일 경우 추가
//     // if (graph->adjLists[dest] == NULL || graph->adjLists[dest]->vertex > src) {
//     //     newNode->next = graph->adjLists[dest];
//     //     graph->adjLists[dest] = newNode;
//     // } else {
//     //     Node* current = graph->adjLists[dest];
//     //     while (current->next != NULL && current->next->vertex < src) {
//     //         current = current->next;
//     //     }
//     //     newNode->next = current->next;
//     //     current->next = newNode;
//     // }
// }



// // 스택을 사용한 반복적 DFS (연결되지 않은 노드도 순회)
// void DFSStack(Graph* graph, int startVertex) {
//     int* stack = malloc(graph->totalVertices * sizeof(int));
//     int top = -1;

//     stack[++top] = startVertex;

//     while (top != -1) {
//         int vertex = stack[top--];

//         if (graph->visited[vertex] == 0) {
//             printf("%d ", vertex);
//             graph->visited[vertex] = 1;
//         }

//         Node* adjList = graph->adjLists[vertex];
//         int neighbors[graph->totalVertices];
//         int count = 0;

//         while (adjList != NULL) {
//             if (graph->visited[adjList->vertex] == 0) {
//                 neighbors[count++] = adjList->vertex;
//             }
//             adjList = adjList->next;
//         }

//         // 인접 노드들을 오름차순으로 스택에 추가
//         for (int i = count - 1; i >= 0; i--) {
//             for (int j = 0; j < i; j++) {
//                 if (neighbors[j] > neighbors[j + 1]) {
//                     int temp = neighbors[j];
//                     neighbors[j] = neighbors[j + 1];
//                     neighbors[j + 1] = temp;
//                 }
//             }
//             stack[++top] = neighbors[i];
//         }
//     }

//     // 이어지지 않은 다른 컴포넌트도 탐색
//     for (int i = 1; i < graph->totalVertices; ++i) {
//         if (graph->visited[i] == 0) {
//             stack[++top] = i;

//             while (top != -1) {
//                 int vertex = stack[top--];

//                 if (graph->visited[vertex] == 0) {
//                     printf("%d ", vertex);
//                     graph->visited[vertex] = 1;
//                 }

//                 Node* adjList = graph->adjLists[vertex];
//                 int neighbors[graph->totalVertices];
//                 int count = 0;

//                 while (adjList != NULL) {
//                     if (graph->visited[adjList->vertex] == 0) {
//                         neighbors[count++] = adjList->vertex;
//                     }
//                     adjList = adjList->next;
//                 }

//                 for (int i = count - 1; i >= 0; i--) {
//                     for (int j = 0; j < i; j++) {
//                         if (neighbors[j] > neighbors[j + 1]) {
//                             int temp = neighbors[j];
//                             neighbors[j] = neighbors[j + 1];
//                             neighbors[j + 1] = temp;
//                         }
//                     }
//                     stack[++top] = neighbors[i];
//                 }
//             }
//         }
//     }

//     free(stack);
// }

// // 방문 상태 초기화
// void resetVisited(Graph* graph) {
//     for (int i = 0; i < graph->totalVertices; i++) {
//         graph->visited[i] = 0;
//     }
// }


// void DFS2(Graph* graph, int startVertex) {
//     Node* adjList = graph->adjLists[startVertex];
//     Node* temp = adjList;

//     graph->visited[startVertex] = 1;

//     while (temp != NULL) {
//         int connectedVertex = temp->vertex;
//         if (graph->visited[connectedVertex] == 0) {
//             DFS2(graph, connectedVertex);
//         }
//         temp = temp->next;
//     }
//     // for (int i = 1; i < graph->totalVertices; ++i) {
//     //     if (!graph->visited[i]) {
//     //         DFS(graph, i);
//     //         // printf("\n"); // Uncomment if you want to distinguish between different connected components
//     //     }
//     // }
// }

// // 모든 노드가 연결되어 있는지 확인
// bool areAllConnected(Graph* graph) {
//     resetVisited(graph);
//     DFS2(graph, 1);

//     for (int i = 1; i < graph->totalVertices; i++) {
//         if (graph->visited[i] == 0) {
//             return false;
//         }
//     }
//     return true;
// }

// // 섬의 개수 세기
// int countIslands(Graph* graph) {
//     resetVisited(graph);

//     int islandCount = 0;
//     for (int i = 1; i < graph->totalVertices; ++i) {
//         if (graph->visited[i] == 0) {
//             DFS2(graph, i);
//             islandCount++;
//         }
//     }
//     return islandCount;
// }

// // 사이클 여부 확인 (방향 그래프용)
// bool hasCycleHelper(Graph* graph, int vertex, bool* recStack) {
//     if (graph->visited[vertex] == 0) {
//         graph->visited[vertex] = 1;
//         recStack[vertex] = 1;

//         Node* adjList = graph->adjLists[vertex];
//         while (adjList != NULL) {
//             int connectedVertex = adjList->vertex;
//             if (graph->visited[connectedVertex] == 0 && hasCycleHelper(graph, connectedVertex, recStack)) {
//                 return true;
//             } else if (recStack[connectedVertex]) {
//                 return true;
//             }
//             adjList = adjList->next;
//         }
//     }
//     recStack[vertex] = 0;
//     return false;
// }

// bool hasCycle(Graph* graph) {
//     resetVisited(graph);
//     bool* recStack = malloc(graph->totalVertices * sizeof(bool));
//     for (int i = 0; i < graph->totalVertices; i++) {
//         recStack[i] = 0;
//     }

//     for (int i = 1; i < graph->totalVertices; i++) {
//         if (hasCycleHelper(graph, i, recStack)) {
//             free(recStack);
//             return true;
//         }
//     }

//     free(recStack);
//     return false;
// }



// void displayGraph(Graph* graph) {
//   int v;
//   for (v = 1; v < graph->totalVertices; v++) {
//     Node* temp = graph->adjLists[v];
//     printf("%d ", v);
//     while (temp) {
//       printf("%d ", temp->vertex);
//       temp = temp->next;
//     }
//     printf("\n");
//   }
//   printf("\n");
// }

// int main() {
//     int vertices[] = {1, 2, 3, 4, 5, 6, 7, 8}; // 정점
//     int edges[][2] = {
//         {1, 2}, {1, 3}, {2, 8}, {3, 4}, {3, 5}, {4, 5}, {6, 7}, {6, 8}, {7, 8}
//     }; // 간선
//     int numVertices = sizeof(vertices) / sizeof(vertices[0]);
//     int numEdges = sizeof(edges) / sizeof(edges[0]);

//     Graph* graph = createGraph(numVertices);

//     for (int i = 0; i < numEdges; i++) {
//         addEdge(graph, edges[i][0], edges[i][1]);
//     }

//     // printf("\nThe Adjacency List of the Graph is:");
//     // displayGraph(graph);
//     printf("DFS traversal of the graph: \n");
//     DFS(graph, 1);
//     printf("\n");
//     resetVisited(graph);

//     printf("DFS Stack traversal of the graph starting from vertex 1: \n");
//     DFSStack(graph, 1);
//     printf("\n");

//     printf("Are all nodes connected? %s\n", areAllConnected(graph) ? "Yes" : "No");

//     printf("Number of islands: %d\n", countIslands(graph));

//     printf("Does the graph have a cycle? %s\n", hasCycle(graph) ? "Yes" : "No");

//     // Cleanup
//     // for (int i = 0; i <= vertices; i++) {
//     //     Node* adjList = graph->adjLists[i];
//     //     while (adjList != NULL) {
//     //         Node* temp = adjList;
//     //         adjList = adjList->next;
//     //         free(temp);
//     //     }
//     // }
//     free(graph->adjLists);
//     free(graph->visited);
//     free(graph);

//     return 0;
// }