#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef struct {
    int node;   // 연결된 다음 노드 번호
    int weight; // 간선의 가중치
} Data;

struct cmp {
    bool operator()(Data a, Data b) {
        return a.weight > b.weight;     // 가중치 오름차순 (priority queue가 가중치가 작은 순서대로 나오게)
    }
};

void Dijkstra(vector<vector<Data>>& v, int* Dijk, priority_queue<Data, vector<Data>, cmp>& pq) {
    while (!pq.empty()) {
        // priority_queue의 맨 앞 노드(가장 가중치가 적은 노드) 가져오기
        Data nowNode = pq.top();
        pq.pop(); 

        int node = nowNode.node;
        int weightSum = nowNode.weight;

        // 이미 이전에 더 적은 가중치로 Dijk[node]를 갱신함
        // 현재 노드까지의 최단 거리가 더 작은 경우, 이 경로는 무시하고 다음으로 넘어가기
        if (Dijk[node] < weightSum) {
            continue;
        }

        // nowNode와 연결되어 있는 다른 모든 노드 탐색
        for (int i = 0; i < v[node].size(); i++) {
            int nextNode = v[node][i].node;
            int weight = v[node][i].weight;

            // (다음 노드에 저장된 값 > 다음 노드로 방문하면서 소비할 가중치의 합) 일 때만 값 갱신, 그리고 pq 삽입
            if (Dijk[nextNode] > weight + weightSum) {
                Dijk[nextNode] = weight + weightSum;
                pq.push({nextNode, Dijk[nextNode]});
            }
        }
    }
}
 
int main() {
    int numNode = 5;
    vector<vector<Data>> v(numNode + 1);  // v[x] : x번 노드에 연결된 다음 노드와 가중치의 정보
    int Dijk[numNode + 1];        // Dijk[x] : x번 노드까지의 최단경로 값

    priority_queue<Data, vector<Data>, cmp> pq;

    // Make Graph
    /* ex)
    v[1] -> [ {node: 2, weight: 8}, {node: 3, weight: 2} ]
    v[2] -> [ {node: 4, weight: 10} ]
    v[3] -> [ {node: 4, weight: 1}, {node: 5, weight: 7} ]
    v[4] -> [ {node: 5, weight: 9} ]
    v[5] -> []

    */
    v[1].push_back({2, 8});
    v[1].push_back({3, 2});
    v[2].push_back({1, 8});
    v[2].push_back({4, 10});
    v[3].push_back({1, 2});
    v[3].push_back({4, 1});
    v[3].push_back({5, 7});
    v[4].push_back({2, 10});
    v[4].push_back({5, 9});
    v[5].push_back({3, 7});
    v[5].push_back({4, 9});

    // Initialize Dijk Array
    for (int i = 1; i <= numNode; i++) {
        Dijk[i] = INT_MAX;
    }

    // Initialize Queue
    int start = 1;
    pq.push({start, 0});
    Dijk[start] = 0;

    // Dijkstra Algorithm
    Dijkstra(v, Dijk, pq);

    for (int i = 1; i <= numNode; i++) {
        cout << "Dijk[" << i << "] = " << Dijk[i] << endl;
    }

    return 0;
}
