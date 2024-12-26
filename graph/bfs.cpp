#include <iostream>
#include <vector>
#include <queue>

//////////////////
// BFS w/ queue //
//////////////////


using namespace std;

// 1. Color 정의
enum Color { WHITE, GRAY, BLACK };

// 2. Vertex 정의
class Vertex {
public:
    Color color;
    int dist;
    int pi;
    vector<int> adj;

    Vertex() : color(WHITE), dist(INT_MAX), pi(-1) {}

    void initialize() {
        color = WHITE;
        dist = INT_MAX;
        pi = -1;
    }
};

// 3. Graph 정의
class Graph {
public:
    vector<Vertex> vertices;

    Graph(int numVertex) : vertices(numVertex) {}

    void BFS(int s) {
        for (int i=0; i<vertices.size(); i++) {
            if (i != s) {
                vertices[i].initialize();
            }
        }

        vertices[s].color = GRAY;
        vertices[s].dist = 0;
        vertices[s].pi = -1;

        queue<int> Q;
        Q.push(s);

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();

            for (int v : vertices[u].adj) {
                if (vertices[v].color == WHITE) {
                    vertices[v].color = GRAY;
                    vertices[v].dist = vertices[u].dist + 1;
                    vertices[v].pi = u;
                    Q.push(v);
                }
            }

            vertices[u].color = BLACK;
        }
    }


    // 1. Shortest Path
    vector<int> bfs_shortest_path(int start, int goal) {
        if (start == goal) return {start};

        BFS(start); // BFS 수행으로 모든 최단경로 갱신

        vector<int> path;
        int current = goal;

        while (current != -1) {
            path.insert(path.begin(), current);      //path의 맨 앞에 current 삽입하기
            current = vertices[current].pi;
        }

        if (path[0] == start) {
            return path;
        } else {
            return {}; // 경로가 없는 경우
        }
    }



    // 2. Check Connectivity
    bool are_all_connected() {
        BFS(0); // 임의의 정점에서 BFS 시작

        for (const auto& vertex : vertices) {
            if (vertex.color == WHITE) {
                return false; // 연결되지 않은 정점이 있음
            }
        }

        return true; // 모든 정점이 연결됨
    }



    // 3. Count Islands
    // 통으로 연결되어있다면 1
    int count_islands() {
        int count = 0;

        for (auto& vertex : vertices) {
            vertex.initialize(); // 모든 정점 초기화
        }

        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i].color == WHITE) {
                BFS(i); // 새로운 섬을 탐색
                count++;
            }
        }

        return count;
    }



    // 4. Cycle Detection
    bool cycle_detection() {
        for (auto& vertex : vertices) {
            vertex.initialize(); // 모든 정점 초기화
        }

        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i].color == WHITE) {
                if (bfs_cycle_detection(i)) {
                    return true;
                }
            }
        }

        return false;
    }




private:
    bool bfs_cycle_detection(int s) {
        queue<int> Q;
        vertices[s].color = GRAY;
        vertices[s].pi = -1;  //directed에서는 제거 가능, but undirected에서는 꼭 써야함
        Q.push(s);

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();

            for (int v : vertices[u].adj) {
                if (vertices[v].color == WHITE) {
                    vertices[v].color = GRAY;
                    vertices[v].pi = u;
                    Q.push(v);
                } else if (vertices[v].color == GRAY && vertices[u].pi != v) {  //for undirected graph
                //for directed graph: else if(vertices[v].color == GRAY)
                    return true; // 사이클이 발견됨
                }
            }

            vertices[u].color = BLACK;
        }

        return false;
    }


    //// 유방향 그래프로 탐지하고 싶다면 bfs_cycle_detection을 아래 함수로 대체해야함
    // bool bfs_cycle_detection(int s) {
    //     queue<int> Q;
    //     vertices[s].color = GRAY;
    //     Q.push(s);

    //     while (!Q.empty()) {
    //         int u = Q.front();
    //         Q.pop();

    //         for (int v : vertices[u].adj) {
    //             if (vertices[v].color == WHITE) {
    //                 vertices[v].color = GRAY;
    //                 Q.push(v);
    //             } else if (vertices[v].color == GRAY) {  // 유방향 그래프의 경우, 다시 방문한 노드가 GRAY 상태면 사이클이 존재
    //                 return true; // 사이클이 발견됨
    //             }
    //         }

    //         vertices[u].color = BLACK;
    //     }

    //     return false;
    // }

};


int main() {
    // [#11] p.9 graph example
    int numVertex = 9;
    Graph graph(numVertex);

    graph.vertices[0].adj = {1, 2, 5};
    graph.vertices[1].adj = {0, 3, 4};
    graph.vertices[2].adj = {0, 3};
    graph.vertices[3].adj = {1, 2, 7};
    graph.vertices[4].adj = {1, 5, 7};
    graph.vertices[5].adj = {0, 4, 6, 8};
    graph.vertices[6].adj = {5, 7, 8};
    graph.vertices[7].adj = {3, 4, 6};
    graph.vertices[8].adj = {5, 6};

    graph.BFS(1);


    for (int i=0; i<numVertex; ++i) {
        cout << "Vertex " << i << ": Distance=" << graph.vertices[i].dist << ", Parent=" << graph.vertices[i].pi << endl;
    }

    cout << "Shortest Path from 0 to 8: ";

    vector<int> path = graph.bfs_shortest_path(0, 8);
    if (!path.empty()) {
        for (int v : path) {
            cout << v << " ";
        }
    } else {
        cout << "No path found";
    }
    cout << endl;



    

    cout << "Are all nodes connected? " << (graph.are_all_connected() ? "Yes" : "No") << endl;
    cout << "Number of islands: " << graph.count_islands() << endl;
    cout << "Does the graph have a cycle? " << (graph.cycle_detection() ? "Yes" : "No") << endl;

    return 0;
}