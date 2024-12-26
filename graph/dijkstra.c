#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int node;   // 연결된 다음 노드 번호
    int weight; // 간선의 가중치
} Data;

typedef struct {
    Data* array;
    int size;
    int capacity;
} PriorityQueue;

typedef struct {
    int dist;
    int pi;
} Vertex;

void initializePriorityQueue(PriorityQueue* pq, int capacity) {
    pq->array = (Data*)malloc(capacity * sizeof(Data));
    if (!pq->array) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    pq->size = 0;
    pq->capacity = capacity;
}

void enqueue(PriorityQueue* pq, Data item) {
    if (pq->size == pq->capacity) {
        fprintf(stderr, "Priority queue overflow.\n");
        exit(EXIT_FAILURE);
    }

    // if (pq->size == pq->capacity) {
    //     pq->capacity *= 2;
    //     pq->array = realloc(pq->array, pq->capacity * sizeof(Data));
    // }   

    int i = pq->size++;
    while (i > 0 && item.weight < pq->array[(i - 1) / 2].weight) {
        pq->array[i] = pq->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    pq->array[i] = item;
}

Data dequeue(PriorityQueue* pq) {
    if (pq->size == 0) {
        fprintf(stderr, "Priority queue underflow.\n");
        exit(EXIT_FAILURE);
    }

    Data minItem = pq->array[0];
    Data lastItem = pq->array[--pq->size];

    int i = 0;
    int child;

    while (2 * i + 1 < pq->size) {
        child = 2 * i + 1;

        if (child + 1 < pq->size && pq->array[child + 1].weight < pq->array[child].weight) {
            child++;
        }

        if (lastItem.weight > pq->array[child].weight) {
            pq->array[i] = pq->array[child];
        } else {
            break;
        }

        i = child;
    }

    pq->array[i] = lastItem;

    return minItem;
}

void Dijkstra(int numNode, int start, int* Dijk, PriorityQueue* pq, Data** v) {
    while (pq->size > 0) {
        // priority_queue의 맨 앞 노드 가져오기
        Data nowNode = dequeue(pq);

        int node = nowNode.node;
        int weightSum = nowNode.weight;

        // 이미 이전에 더 적은 가중치로 Dijk[node]를 갱신함
        if (Dijk[node] < weightSum) {
            continue;
        }

        // nowNode와 연결되어 있는 다른 모든 노드 탐색
        for (int i = 0; i < numNode + 1; i++) {
            if (v[node][i].node != -1) {
                int nextNode = v[node][i].node;
                int weight = v[node][i].weight;

                // (다음 노드에 저장된 값 > 다음 노드로 방문하면서 소비할 가중치의 합) 일 때만 값 갱신, 그리고 pq 삽입
                if (Dijk[nextNode] > weight + weightSum) {
                    Dijk[nextNode] = weight + weightSum;
                    enqueue(pq, (Data){nextNode, Dijk[nextNode]});
                }
            }
        }
    }
}

int main() {
    int numNode = 5;
    Data** v = (Data**)malloc((numNode + 1) * sizeof(Data*));
    for (int i = 0; i < numNode + 1; i++) {
        v[i] = (Data*)malloc((numNode + 1) * sizeof(Data));
    }

    int Dijk[numNode + 1]; // Dijk[x] : x번 노드까지의 최단경로 값

    PriorityQueue pq;
    initializePriorityQueue(&pq, numNode);

    // Make Graph
    for (int i = 0; i < numNode + 1; i++) {
        for (int j = 0; j < numNode + 1; j++) {
            v[i][j].node = -1;
            v[i][j].weight = -1;
        }
    }

    v[1][0] = (Data){2, 8};
    v[1][1] = (Data){3, 2};
    v[2][0] = (Data){1, 8};
    v[2][1] = (Data){4, 10};
    v[3][0] = (Data){1, 2};
    v[3][1] = (Data){4, 1};
    v[3][2] = (Data){5, 7};
    v[4][0] = (Data){2, 10};
    v[4][1] = (Data){5, 9};
    v[5][0] = (Data){3, 7};
    v[5][1] = (Data){4, 9};

    // Initialize Dijk Array
    for (int i = 1; i <= numNode; i++) {
        Dijk[i] = INT_MAX;
    }

    // Initialize Queue
    int start = 1;
    enqueue(&pq, (Data){start, 0});
    Dijk[start] = 0;

    // Dijkstra Algorithm
    Dijkstra(numNode, start, Dijk, &pq, v);

    for (int i = 1; i <= numNode; i++) {
        printf("Dijk[%d] = %d\n", i, Dijk[i]);
    }

    // 메모리 해제
    for (int i = 0; i < numNode + 1; i++) {
        free(v[i]);
    }
    free(v);
    free(pq.array);

    return 0;
}
