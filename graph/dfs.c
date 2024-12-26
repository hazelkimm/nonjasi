#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////
// DFS + Topological Sort + SCC (C Version) //
///////////////////////////////////////////////

// 1. Color 정의
typedef enum {
    WHITE,
    GRAY,
    BLACK
} Color;

// 2. Vertex 정의
typedef struct {
    Color color;
    int pi;
    int discover;       // timestamp for discover
    int finish;         // timestamp for finish
    int* adj;
    int adj_size;
} Vertex;

// 3. Graph 정의
typedef struct {
    Vertex* vertices;
    int numVertices; //vertices 배열의 크기
} Graph;

// 4. Stack 정의
typedef struct {
    int* array;
    int top;
    unsigned capacity;
} Stack;

Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(capacity * sizeof(int));
    return stack;
}

int isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

int pop(Stack* stack) {
    return stack->array[stack->top--];
}

void initializeVertex(Vertex* vertex) {
    vertex->color = WHITE;
    vertex->pi = -1;
}

void initializeGraph(Graph* graph, int numVertices) {
    graph->numVertices = numVertices;
    graph->vertices = (Vertex*)malloc(numVertices * sizeof(Vertex));

    for (int i = 0; i < numVertices; i++) {
        graph->vertices[i].adj = NULL;
        graph->vertices[i].adj_size = 0;
    }
}

void DFS_VISIT(Graph* graph, int u, int* time, Stack* finishStack) {
    *time = *time + 1;
    graph->vertices[u].discover = *time;
    graph->vertices[u].color = GRAY;

    for (int i = 0; i < graph->vertices[u].adj_size; i++) {
        int v = graph->vertices[u].adj[i];
        if (graph->vertices[v].color == WHITE) {
            graph->vertices[v].pi = u;
            DFS_VISIT(graph, v, time, finishStack);
        }
    }

    *time = *time + 1;
    graph->vertices[u].finish = *time;
    graph->vertices[u].color = BLACK;
    push(finishStack, u);
}

void DFS(Graph* graph, Stack* finishStack) {
    int time = 0;

    for (int i = 0; i < graph->numVertices; i++) {
        initializeVertex(&(graph->vertices[i]));
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].color == WHITE) {
            DFS_VISIT(graph, i, &time, finishStack);
        }
    }
}

void DFS_STACK(Graph* graph, Stack* finishStack) {
    int time = 0;

    for (int i = 0; i < graph->numVertices; i++) {
        initializeVertex(&(graph->vertices[i]));
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].color == WHITE) {
            Stack* s = createStack(graph->numVertices);
            push(s, i);

            while (!isStackEmpty(s)) {
                int u = s->array[s->top]; // 스택의 맨 위 원소를 확인 (pop하지 않음)
                
                if (graph->vertices[u].color == WHITE) {
                    time++;
                    graph->vertices[u].discover = time;
                    graph->vertices[u].color = GRAY;

                    // 인접 노드들을 처리 (작은 번호부터 처리하기 위해 역순으로 스택에 삽입)
                    for (int j = graph->vertices[u].adj_size - 1; j >= 0; j--) {
                        int v = graph->vertices[u].adj[j];
                        if (graph->vertices[v].color == WHITE) {
                            push(s, v);
                        }
                    }
                } else if (graph->vertices[u].color == GRAY) {
                    time++;
                    graph->vertices[u].finish = time;
                    graph->vertices[u].color = BLACK;
                    push(finishStack, u);
                    pop(s); // 처리 완료된 노드를 스택에서 제거
                }
            }

            free(s->array);
            free(s);
        }
    }
}


int CheckConnectivity(Graph* graph) {
    DFS(graph, NULL);

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].color == WHITE) {
            return 0;
        }
    }
    return 1;
}

int CountIslands(Graph* graph) {
    int island_count = 0;
    int time = 0;
    Stack* tempStack = createStack(graph->numVertices);

    for (int i = 0; i < graph->numVertices; i++) {
        initializeVertex(&(graph->vertices[i]));
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].color == WHITE) {
            DFS_VISIT(graph, i, &time, tempStack);
            island_count++;
        }
    }

    free(tempStack->array);
    free(tempStack);
    return island_count;
}

int DetectCycleUtil(Graph* graph, int u) {
    graph->vertices[u].color = GRAY;

    for (int i = 0; i < graph->vertices[u].adj_size; i++) {
        int v = graph->vertices[u].adj[i];
        if (graph->vertices[v].color == WHITE) {
            if (DetectCycleUtil(graph, v)) {
                return 1;
            }
        } else if (graph->vertices[v].color == GRAY) {
            return 1;
        }
    }

    graph->vertices[u].color = BLACK;
    return 0;
}

int DetectCycle(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        initializeVertex(&(graph->vertices[i]));
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].color == WHITE) {
            if (DetectCycleUtil(graph, i)) {
                return 1;
            }
        }
    }
    return 0;
}



void TopologicalSort(Graph* graph, Stack* finishStack) {
    DFS(graph, finishStack);

    printf("Topological Sort: ");
    while (!isStackEmpty(finishStack)) {
        printf("%d ", pop(finishStack));
    }
    printf("\n");
}

int main() {
    // [#11] p.21 graph example
    int numVertex = 6;
    Graph graph;
    Stack finishStack;

    initializeGraph(&graph, numVertex);
    finishStack = *createStack(numVertex);

    graph.vertices[0].adj = (int[]){1, 3};
    graph.vertices[0].adj_size = 2;
    graph.vertices[1].adj = (int[]){4};
    graph.vertices[1].adj_size = 1;
    graph.vertices[2].adj = (int[]){4, 5};
    graph.vertices[2].adj_size = 2;
    graph.vertices[3].adj = (int[]){1};
    graph.vertices[3].adj_size = 1;
    graph.vertices[4].adj = (int[]){3};
    graph.vertices[4].adj_size = 1;
    graph.vertices[5].adj = (int[]){5};
    graph.vertices[5].adj_size = 1;

    DFS(&graph, &finishStack);

    for (int i = 0; i < numVertex; i++) {
        printf("Vertex %d: Discover=%d, Finish=%d\n", i, graph.vertices[i].discover, graph.vertices[i].finish);
    }

    // [#11] p.30 graph example
    // int numVertex = 9;
    // Graph graph;
    // Stack finishStack;

    // initializeGraph(&graph, numVertex);
    // finishStack = *createStack(numVertex);

    // graph.vertices[0].adj = (int[]){1, 7};
    // graph.vertices[0].adj_size = 2;
    // graph.vertices[1].adj = (int[]){2, 7};
    // graph.vertices[1].adj_size = 2;
    // graph.vertices[2].adj = (int[]){5};
    // graph.vertices[2].adj_size = 1;
    // graph.vertices[3].adj = (int[]){2, 4};
    // graph.vertices[3].adj_size = 2;
    // graph.vertices[4].adj = (int[]){5};
    // graph.vertices[4].adj_size = 1;
    // graph.vertices[5].adj_size = 0;
    // graph.vertices[6].adj = (int[]){7};
    // graph.vertices[6].adj_size = 1;
    // graph.vertices[7].adj_size = 0;
    // graph.vertices[8].adj_size = 0;

    // DFS(&graph, &finishStack);

    // for (int i = 0; i < numVertex; i++) {
    //     printf("Vertex %d: Discover=%d, Finish=%d\n", i, graph.vertices[i].discover, graph.vertices[i].finish);
    // }

    // printf("Topological Sort: ");
    // while (!isStackEmpty(&finishStack)) {
    //     printf("%d ", pop(&finishStack));
    // }
    // printf("\n");

    // printf("\nDFS (Stack-based):\n");
    // DFS_STACK(&graph, &finishStack);
    // for (int i = 0; i < numVertex; i++) {
    //     printf("Vertex %d: Discover=%d, Finish=%d\n", i, graph.vertices[i].discover, graph.vertices[i].finish);
    // }

    printf("\nCheck Connectivity: %s\n", CheckConnectivity(&graph) ? "Connected" : "Not Connected");
    printf("Number of Islands: %d\n", CountIslands(&graph));
    printf("Cycle Detection: %s\n", DetectCycle(&graph) ? "Cycle exists" : "No cycle");

    TopologicalSort(&graph, &finishStack);

    free(graph.vertices);
    free(finishStack.array);

    return 0;
}