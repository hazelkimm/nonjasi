#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 20

// Define Vertex structure
typedef struct {
    int name;
    int key;
    int pi;
    int adj[MAX_VERTICES];  // Assuming a maximum number of adjacent vertices
} Vertex;

// Define Graph structure
typedef struct {
    Vertex vertices[MAX_VERTICES];
    int weights[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

// Define Heap structure
typedef struct {
    Vertex harr[MAX_VERTICES];
    int capacity;
    int heap_size;
} Heap;

// Function prototypes
void initializeVertex(Vertex *v, int i);
Graph* createGraph(int numVertex, int initialWeights[MAX_VERTICES][MAX_VERTICES]);
void minHeapify(Heap *h, int i);
int minHeapMinimum(Heap *h);
int minHeapExtractMin(Heap *h);
void minHeapDecreaseKey(Heap *h, int i, int key);
void minHeapInsert(Heap *h, Vertex x);
void MSTPrim(Graph *graph, int r);
void printMST(Graph *graph);

// Function to initialize a Vertex
void initializeVertex(Vertex *v, int i) {
    v->name = i;
    v->key = INT_MAX;
    v->pi = -1;
}

// Function to create a Graph
Graph* createGraph(int numVertex, int initialWeights[MAX_VERTICES][MAX_VERTICES]) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertex;

    // Initialize vertices
    for (int i = 0; i < numVertex; i++) {
        initializeVertex(&(graph->vertices[i]), i);
        for (int j = 0; j < numVertex; j++) {
            graph->weights[i][j] = initialWeights[i][j];
        }
    }

    return graph;
}

int idxHeap(Heap *h, int name) {
    for (int i=0; i<h->heap_size; i++) {
        if (h->harr[i].name == name) {
            return i;
        }
    }
    return -1;
}

// Function to perform min-heapify operation
void minHeapify(Heap *h, int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest = i;

    if (l < h->heap_size && h->harr[l].key < h->harr[i].key) {
        smallest = l;
    }
    if (r < h->heap_size && h->harr[r].key < h->harr[smallest].key) {
        smallest = r;
    }

    if (smallest != i) {
        Vertex tmp = h->harr[i];
        h->harr[i] = h->harr[smallest];
        h->harr[smallest] = tmp;

        minHeapify(h, smallest);
    }
}

// Function to get the minimum key from the heap
int minHeapMinimum(Heap *h) {
    if (h->heap_size < 1) {
        fprintf(stderr, "Error: Heap underflow\n");
        return INT_MAX;
    }

    return h->harr[0].name;
}

// Function to extract the minimum element from the heap
int minHeapExtractMin(Heap *h) {
    int minVertex = minHeapMinimum(h);

    h->harr[0] = h->harr[h->heap_size - 1];
    h->heap_size--;
    minHeapify(h, 0);

    return minVertex;
}

// Function to decrease the key of a vertex in the heap
void minHeapDecreaseKey(Heap *h, int i, int key) {
    if (key > h->harr[i].key) {
        fprintf(stderr, "Error: New key is larger than the current key\n");
        return;
    }

    h->harr[i].key = key;

    //현재 노드를 부모 노드와 비교하며 힙 속성 유지
    while (i > 0 && h->harr[(i - 1) / 2].key > h->harr[i].key) {
        Vertex tmp = h->harr[i];
        h->harr[i] = h->harr[(i - 1) / 2];
        h->harr[(i - 1) / 2] = tmp;

        // 인덱스를 부모 노드로 업데이트
        i = (i - 1) / 2;
    }
}

// 새로운 요소를 힙에 삽입
void minHeapInsert(Heap *h, Vertex x) {
    if (h->heap_size == h->capacity) {
        fprintf(stderr, "Error: Heap overflow\n");
        return;
    }

    h->heap_size++;
    int i = h->heap_size-1;
    h->harr[i] = x;

    minHeapDecreaseKey(h, i, x.key);
    // int k = x.key;
    // x.key = INT_MAX;

    // h->harr[h->heap_size - 1] = x;
    // int i = 0;
    // while (i < h->heap_size && h->harr[i].name != x.name) {
    //     i++;
    // }
    // minHeapDecreaseKey(h, i, k);

    // int i = idxHeap(h, x.name);
    // minHeapDecreaseKey(h, i, k);

}

// Function to perform Prim's algorithm for Minimum Spanning Tree
void MSTPrim(Graph *graph, int r) {
    // 모든 정점 초기화
    for (int i = 0; i < graph->numVertices; i++) {
        initializeVertex(&(graph->vertices[i]), i);
    }

    // 시작 정점의 키 값을 0으로 설정
    graph->vertices[r].key = 0;
    Heap Q;
    Q.capacity = MAX_VERTICES;
    Q.heap_size = 0;

    // 모든 정점을 힙에 삽입
    for (int i = 0; i < graph->numVertices; i++) {
        minHeapInsert(&Q, graph->vertices[i]);
    }

    // 힙이 비어있지 않은 동안 반복
    while (Q.heap_size != 0) {
        // 키 값이 가장 작은 정점 힙에서 제거
        int u = minHeapExtractMin(&Q);

        // 제거된 정점과 인접한 모든 정점 탐색
        for (int v = 0; v < graph->numVertices; v++) {
            //정점이 힙에 있고, 새 경로의 비용이 현재 키 값보다 작으면 키 값을 갱신
            if (graph->weights[u][v] != 0 && graph->weights[u][v] != INT_MAX && idxHeap(&Q, v) != -1 && graph->weights[u][v] < graph->vertices[v].key) {
                graph->vertices[v].pi = u;
                graph->vertices[v].key = graph->weights[u][v];
                minHeapDecreaseKey(&Q, idxHeap(&Q, v), graph->weights[u][v]);
            }
        }
    }
}

// Function to print the Minimum Spanning Tree
void printMST(Graph *graph) {
    int totalWeight = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].pi != -1) {
            // Edge from 'vertices[i].pi -> i' in the MST
            printf("Edge: %d - %d, Weight: %d\n", graph->vertices[i].pi, i, graph->weights[graph->vertices[i].pi][i]);
            totalWeight += graph->weights[graph->vertices[i].pi][i];
        }
    }

    printf("Total Weight of MST: %d\n", totalWeight);
}

int main() {
    // [#14] p.28 graph example
    int numVertex = 9;
    int initialWeights[MAX_VERTICES][MAX_VERTICES] = {
        {0, 4, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 8, INT_MAX},
        {4, 0, 8, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 11, INT_MAX},
        {INT_MAX, 8, 0, 7, INT_MAX, 4, INT_MAX, INT_MAX, 2},
        {INT_MAX, INT_MAX, 7, 0, 9, 14, INT_MAX, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, 9, 0, 10, INT_MAX, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, 4, 14, 10, 0, 2, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 2, 0, 1, 6},
        {8, 11, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1, 0, 7},
        {INT_MAX, INT_MAX, 2, INT_MAX, INT_MAX, INT_MAX, 6, 7, 0}
    };

    Graph *graph = createGraph(numVertex, initialWeights);
    
    MSTPrim(graph, 0);
    printMST(graph);

    free(graph);

    return 0;
}
