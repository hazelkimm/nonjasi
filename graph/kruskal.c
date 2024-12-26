#include <stdio.h>
#include <stdlib.h>

// Edge 구조체 정의
typedef struct {
    int src, dst, weight;
} Edge;

// Find 함수
int Find(int vertices[], int v) {
    if (v == vertices[v]) {
        return v;
    } else {
        return vertices[v] = Find(vertices, vertices[v]);
    }
}

// Union 함수
void Union(int vertices[], int a, int b) {
    a = Find(vertices, a);
    b = Find(vertices, b);

    if (a != b) {
        vertices[a] = b;
    }
}

// Union 함수 (랭크 기반 병합)
// void Union(int vertices[], int rank[], int a, int b) {
//     a = Find(vertices, a);
//     b = Find(vertices, b);

//     if (a != b) {
//         if (rank[a] < rank[b]) {
//             vertices[a] = b;
//         } else if (rank[a] > rank[b]) {
//             vertices[b] = a;
//         } else {
//             vertices[b] = a;
//             rank[a]++;
//         }
//     }
// }



// MSTKruskal 함수
Edge* MSTKruskal(int vertices[], Edge edges[], int numVertices, int numEdges, int* numMSTEdges) {
    Edge* mst = (Edge*)malloc((numVertices - 1) * sizeof(Edge));
    *numMSTEdges = 0;

    // 랭크 배열 초기화
    // int* rank = (int*)calloc(numVertices, sizeof(int));


    // 간선을 가중치 순으로 정렬
    for (int i = 0; i < numEdges - 1; i++) {
        for (int j = 0; j < numEdges - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < numEdges; i++) {
        int set1 = Find(vertices, edges[i].src);
        int set2 = Find(vertices, edges[i].dst);

        if (set1 != set2) {
            mst[*numMSTEdges] = edges[i];
            (*numMSTEdges)++;
            Union(vertices, set1, set2);
        }
    }

    return mst;
}

int main() {
    int V = 9, E = 14;
    int vertices[V];
    Edge edges[E];

    for (int i = 0; i < V; i++) {
        vertices[i] = i;
    }

    edges[0] = (Edge){0, 1, 4};
    edges[1] = (Edge){0, 7, 8};
    edges[2] = (Edge){1, 2, 8};
    edges[3] = (Edge){1, 7, 11};
    edges[4] = (Edge){2, 3, 7};
    edges[5] = (Edge){2, 5, 4};
    edges[6] = (Edge){2, 8, 2};
    edges[7] = (Edge){3, 4, 9};
    edges[8] = (Edge){3, 5, 14};
    edges[9] = (Edge){4, 5, 10};
    edges[10] = (Edge){5, 6, 2};
    edges[11] = (Edge){6, 7, 1};
    edges[12] = (Edge){6, 8, 6};
    edges[13] = (Edge){7, 8, 7};

    int numMSTEdges;
    Edge* mst = MSTKruskal(vertices, edges, V, E, &numMSTEdges);

    int totalWeight = 0;
    printf("MST by Kruskal's Algorithm:\n");
    for (int i = 0; i < numMSTEdges; i++) {
        printf("Edge: %d - %d, Weight: %d\n", mst[i].src, mst[i].dst, mst[i].weight);
        totalWeight += mst[i].weight;
    }

    printf("Total Weight of MST: %d\n", totalWeight);

    free(mst);

    return 0;
}
