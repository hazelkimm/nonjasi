#include <stdio.h>
#include <limits.h>

// Edge 정의
typedef struct {
    int src;
    int dst;
    int weight;
} Edge;

// Vertex 정의
typedef struct {
    int dist;
    int pi;
} Vertex;

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


// 음수 가중치 사이클 감지 함수
int detectNegativeCycle(const Vertex vertices[], const Edge edges[], int numEdges) {
    for (int i = 0; i < numEdges; i++) {
        if (vertices[edges[i].src].dist != INT_MAX && vertices[edges[i].dst].dist > vertices[edges[i].src].dist + edges[i].weight) {
            return 1; // Negative weight cycle detected
        }
    }
    return 0; // No negative weight cycle
}


// Bellman-Ford 알고리즘
int bellmanFord(Vertex vertices[], const Edge edges[], int numVertices, int numEdges, int source) {
    initializeSingleSource(vertices, numVertices, source);

    for (int i = 1; i < numVertices; i++) {
        for (int j = 0; j < numEdges; j++) {
            relax(vertices, &edges[j]);
        }
    }

    for (int i = 0; i < numEdges; i++) {
        if (vertices[edges[i].src].dist != INT_MAX && vertices[edges[i].dst].dist > vertices[edges[i].src].dist + edges[i].weight) {
            return 0; // Negative weight cycle detected
        }
    }

    return 1; // Success
}

int main() {
    Vertex vertices[5];
    Edge edges[] = {
        {0, 1, 6}, {0, 3, 7},
        {1, 2, 5}, {1, 3, 8}, {1, 4, -4},
        {2, 1, -2},
        {3, 2, -3}, {3, 4, 9},
        {4, 0, 2}, {4, 2, 7}
    };

    int numVertices = 5;
    int numEdges = sizeof(edges) / sizeof(edges[0]);
    int source = 0;

    if (bellmanFord(vertices, edges, numVertices, numEdges, source)) {
        printf("Shortest path from vertex %d:\n", source);
        for (int i = 0; i < numVertices; i++) {
            printf("Vertex %d: Distance=%d, Predecessor=%d\n", i, vertices[i].dist, vertices[i].pi);
        }
    } else {
        printf("Negative weight cycle detected. Bellman-Ford algorithm failed.\n");
    }

    return 0;
}
