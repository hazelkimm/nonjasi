// bellman과 dijkstra를 결합한 apsp
/*
그래프에 새로운 더미 정점 추가 후, 더미 정점과 나머지 모든 정점 사이에 가중치가 0인 edge 연결
이후 벨만-포드로 더미 정점과 나머지 정점 사이의 최단 경로를 찾고, 기록
가중치 변환 수식으로 다익스트라 알고리즘으로 모든 정점 쌍 사이의 최단 거리 구하기
*/


#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int src;
    int dst;
    int weight;
};

const int UNKNOWN = INT_MAX;

bool HasNegativeCycle(const vector<Edge> & edges, vector<int> distance) {
    for (auto& e: edges) {
        if (distance[e.src] == UNKNOWN) {
            continue;
        }
        if (distance[e.src] + e.weight < distance[e.dst]) {
            return true;
        }
    }
    return false;
}


vector<int> BellmanFord(vector<Edge> edges, int V) {
    vector<int> distance(V+1, UNKNOWN);

    // 더미 정점 s 추가 후 모든 정점에서 s로 가는 edge 0 추가
    int s = V;
    for (int i = 0; i < V; i++) {
        edges.push_back(Edge{s,i,0});
    }
    distance[s] = 0;

    //정점 개수가 V+1개이므로 V번 반복
    for (int i = 0; i < V; i++) {
        for (auto& e: edges) {
            // edge의 시작 정점의 거리 값이 unknown이면 스킵
            if (distance[e.src] == UNKNOWN) {
                continue;
            }

            // 인접한 정점의 거리 값이 새로운 경로에 의한 거리값보다 크면 거리 값 업데이트
            if (distance[e.dst] > distance[e.src] + e.weight) {
                distance[e.dst] = distance[e.src] + e.weight;
            }
        }
    }

    // 음수 사이클이 존재하면 종료
    if (HasNegativeCycle(edges, distance)) {
        cout << "Negative Cycle exists" << endl;
        return {};
    }

    // 각 정점의 최단거리 반환
    return distance;
}



int GetMinDistance(vector<int>& distance, vector<bool> & visited) {
    int minDistance = UNKNOWN;
    int minIndex = -1;

    for (int i = 0; i < distance.size(); i++) {
        if (!visited[i] && distance[i] <= minDistance) {
            minDistance = distance[i];
            minIndex = i;
        }
    }

    // 가장 작은 거리를 가진 정점의 인덱스 반환. 다음에 방문할 정점이 됨!
    return minIndex;
}


vector<int> Dijkstra(vector<Edge> edges, int V, int start) {
    vector<int> distance(V, UNKNOWN);
    vector<bool> visited(V, false);

    distance[start] = 0;

    for (int i = 0; i < V-1; i++) {
        // 방문하지 않은 정점 중에서 최소 거리 정점 찾기
        int curr = GetMinDistance(distance, visited);

        visited[curr] = true;

        for (auto& e:edges) {
            // 간선의 출발 정점이 현재 정점이 아니면 무시
            if (e.src != curr) {
                continue;
            }

            // 이미 방문했으면 무시
            if (visited[e.dst]) {
                continue;
            }
            if (distance[curr] != UNKNOWN && distance[e.dst] > distance[curr] + e.weight) {
                distance[e.dst] = distance[curr] + e.weight;
            }
        }
    }
    return distance;
}


void Johnson(vector<Edge> edges, int V) {
    // 더미 정점을 기준으로 각 정점까지의 잠재치 h 계산
    vector<int> h = BellmanFord(edges, V);

    if (h.empty()) {
        return;
    }

    // edge의 가중치 재설정
    for (auto&e: edges) {
        e.weight += (h[e.src] - h[e.dst]);
    }

    // 모든 정점들 사이의 최단 거리 저장
    vector<vector<int>> shortest(V);

    for (int i = 0; i < V; i++) {
        shortest[i] = Dijkstra(edges, V, i);
    }


    // 가중치 변환 수식을 역으로 적용하여 최단 거리 출력
    for (int i = 0; i < V; i++) {
        cout << i << ":\n";

        for (int j = 0; j < V; j++) {
            if (shortest[i][j] != UNKNOWN) {
                shortest[i][j] += h[j] - h[i];

                cout << "\t" << j << ": " << shortest[i][j] << endl;
            }
        }
    }
}


int main() {
    int V = 5;
    vector<Edge> edges;

    vector<vector<int>> edge_map {
        {0,1,-7},
        {1, 2, -2},
        {2, 0, 10},
        {0, 3, -5},
        {0, 4, 2},
        {3, 4, 4}
    };

    for (auto& e: edge_map) {
        edges.emplace_back(Edge {e[0], e[1], e[2]});
    }

    Johnson(edges, V);

    return 0;
}
