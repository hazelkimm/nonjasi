#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define UNKNOWN INT_MAX

typedef struct {
    int src;
    int dst;
    int weight;
} Edge;

int has_negative_cycle(Edge* edges, int* distance, int edge_count) {
    for (int i = 0; i < edge_count; i++) {
        Edge e = edges[i];
        if (distance[e.src] == UNKNOWN) {
            continue;
        }
        if (distance[e.src] + e.weight < distance[e.dst]) {
            return 1; // Negative cycle exists
        }
    }
    return 0;
}

int* bellman_ford(Edge* edges, int V, int edge_count) {
    int* distance = (int*)malloc((V + 1) * sizeof(int));
    for (int i = 0; i <= V; i++) {
        distance[i] = UNKNOWN;
    }

    // 더미 정점 s 추가 후 모든 정점에서 s로 가는 edge 0 추가
    int s = V;
    Edge* new_edges = (Edge*)malloc((edge_count + V) * sizeof(Edge));
    for (int i = 0; i < edge_count; i++) {
        new_edges[i] = edges[i];
    }
    for (int i = 0; i < V; i++) {
        new_edges[edge_count + i].src = s;
        new_edges[edge_count + i].dst = i;
        new_edges[edge_count + i].weight = 0;
    }
    distance[s] = 0;

    // 정점 개수가 V+1개이므로 V번 반복
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < edge_count + V; j++) {
            Edge e = new_edges[j];
            if (distance[e.src] == UNKNOWN) {
                continue;
            }
            if (distance[e.dst] > distance[e.src] + e.weight) {
                distance[e.dst] = distance[e.src] + e.weight;
            }
        }
    }

    // 음수 사이클이 존재하면 종료
    if (has_negative_cycle(new_edges, distance, edge_count + V)) {
        printf("Negative Cycle exists\n");
        free(distance);
        free(new_edges);
        return NULL;
    }

    free(new_edges);
    // 각 정점의 최단거리 반환
    return distance;
}

int get_min_distance(int* distance, int* visited, int V) {
    int min_distance = UNKNOWN;
    int min_index = -1;

    for (int i = 0; i < V; i++) {
        if (!visited[i] && distance[i] <= min_distance) {
            min_distance = distance[i];
            min_index = i;
        }
    }

    // 가장 작은 거리를 가진 정점의 인덱스 반환. 다음에 방문할 정점이 됨!
    return min_index;
}

int* dijkstra(Edge* edges, int V, int start, int edge_count) {
    int* distance = (int*)malloc(V * sizeof(int));
    int* visited = (int*)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        distance[i] = UNKNOWN;
        visited[i] = 0;
    }

    distance[start] = 0;

    for (int i = 0; i < V - 1; i++) {
        int curr = get_min_distance(distance, visited, V);

        visited[curr] = 1;

        for (int j = 0; j < edge_count; j++) {
            Edge e = edges[j];
            if (e.src != curr) {
                continue;
            }

            if (visited[e.dst]) {
                continue;
            }

            if (distance[curr] != UNKNOWN && distance[e.dst] > distance[curr] + e.weight) {
                distance[e.dst] = distance[curr] + e.weight;
            }
        }
    }

    free(visited);
    return distance;
}

void johnson(Edge* edges, int V, int edge_count) {
    // 더미 정점을 기준으로 각 정점까지의 잠재치 h 계산
    int* h = bellman_ford(edges, V, edge_count);

    if (h == NULL) {
        return;
    }

    // edge의 가중치 재설정
    for (int i = 0; i < edge_count; i++) {
        edges[i].weight += (h[edges[i].src] - h[edges[i].dst]);
    }

    // 모든 정점들 사이의 최단 거리 저장
    int** shortest = (int**)malloc(V * sizeof(int*));

    for (int i = 0; i < V; i++) {
        shortest[i] = dijkstra(edges, V, i, edge_count);
    }

    // 가중치 변환 수식을 역으로 적용하여 최단 거리 출력
    for (int i = 0; i < V; i++) {
        printf("%d:\n", i);

        for (int j = 0; j < V; j++) {
            if (shortest[i][j] != UNKNOWN) {
                shortest[i][j] += h[j] - h[i];
                printf("\t%d: %d\n", j, shortest[i][j]);
            }
        }

        free(shortest[i]);
    }

    free(shortest);
    free(h);
}

int main() {
    int V = 5;
    int edge_count = 6;
    Edge edges[6] = {
        {0, 1, -7},
        {1, 2, -2},
        {2, 0, 10},
        {0, 3, -5},
        {0, 4, 2},
        {3, 4, 4}
    };

    johnson(edges, V, edge_count);

    return 0;
}
