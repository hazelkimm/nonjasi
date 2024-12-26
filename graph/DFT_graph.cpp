#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

class Graph {
public:
    Graph(int vertices) {
        V = vertices+1; //index가 1번부터 시작해서! 0부터라면 V = vertices
        adj.resize(V);
        visited.resize(V, false);
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        // adj[w].push_back(v); // For undirected graph
    }

    //만약 vertex, edge 따로준다면
    /*
    vector<int> vertices = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<pair<int, int>> edges = {
        {1, 2}, {1, 3},
        {2, 1}, {2, 8},
        {3, 1}, {3, 4}, {3, 5},
        {4, 3}, {4, 5},
        {5, 3}, {5, 4},
        {6, 7},
        {7, 6},
        {8, 2}
    };
    */ 
    // Graph를 constructor 이렇게 바꾸기 
    // Graph(const vector<int>& vertices, const vector<pair<int, int>>& edges) {
    //     V = vertices.size();
    //     adj.resize(V + 1); // Assuming vertices are 1-indexed
    //     visited.resize(V + 1, false);

    //     for (const auto& edge : edges) {
    //         addEdge(edge.first, edge.second);
    //     }
    // }

    void DFS(int v) {
        fill(visited.begin(), visited.end(), false);
        DFSUtil(v);
        for (auto k = adj[v].begin(); k != adj[v].end(); ++k) {
            if (!visited[*k]) {
                DFSUtil(*k);
            }
        }
        for (int i = 1; i < V; ++i) {       //index가 1부터 시작이라..
            if (!visited[i]) {
                DFSUtil(i);
            }
        }
        cout << endl;
    }

    void DFSAll() {
        fill(visited.begin(), visited.end(), false);
        for (int i = 1; i < V; ++i) {    //index가 1부터 시작이라
            if (!visited[i]) {
                DFSUtil(i);
            }
        }
        cout << endl;
    }


    // 스택을 사용하는 반복 방식의 DFS
    void DFSStack(int v) {
        fill(visited.begin(), visited.end(), false);
        stack<int> stack;
        stack.push(v);

        while (!stack.empty()) {
            int node = stack.top();
            stack.pop();

            if (!visited[node]) {
                cout << node << " ";
                visited[node] = true;
            }

            for (auto i = adj[node].rbegin(); i != adj[node].rend(); ++i) {
                if (!visited[*i]) {
                    stack.push(*i);
                }
            }
        }

        // 방문되지 않은 다른 컴포넌트 탐색
        for (int i = 1; i < V; ++i) {   //index가 0부터 시작이라면 i = 0
            if (!visited[i]) {
                stack.push(i);
                while (!stack.empty()) {
                    int node = stack.top();
                    stack.pop();

                    if (!visited[node]) {
                        cout << node << " ";
                        visited[node] = true;
                    }

                    for (auto i = adj[node].rbegin(); i != adj[node].rend(); ++i) {
                        if (!visited[*i]) {
                            stack.push(*i);
                        }
                    }
                }
            }
        }
        cout<<endl;
    }

     // 모든 노드가 연결되어 있는지 확인
    bool areAllConnected() {
        fill(visited.begin(), visited.end(), false);
        DFSUtil2(1); //index가 0부터 시작이라면 DFSUtil2(0)

        for (int i = 1; i < V; ++i) {   //index가 0부터 시작이라면 i = 0
            if (!visited[i]) {
                return false;
            }
        }
        return true;
    }

    // 섬의 개수 세기
    int countIslands() {
        fill(visited.begin(), visited.end(), false);
        int islandCount = 0;

        for (int i = 1; i < V; ++i) {    //index가 0부터 시작이라면 i = 0
            if (!visited[i]) {
                DFSUtil2(i);
                islandCount++;
            }
        }
        return islandCount;
    }

    // 사이클 여부 확인 (방향 그래프용)
    bool hasCycle() {
        fill(visited.begin(), visited.end(), false);
        vector<bool> recStack(V, false);

        for (int i = 1; i < V; ++i) {     //index가 0부터 시작이라면 i = 0
            if (!visited[i]) {
                if (cycleDetect(i, recStack)) {
                    return true;
                }
            }
        }
        return false;
    }


private:
    int V; // Number of vertices
    vector<list<int>> adj; // Adjacency lists
    vector<bool> visited; // Visited vertices

    void DFSUtil(int v) {
        visited[v] = true;
        cout << v << " ";

        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!visited[*i]) {
                DFSUtil(*i);
            }
        }
    }

    void DFSUtil2(int v) {
        visited[v] = true;

        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!visited[*i]) {
                DFSUtil2(*i);
            }
        }
    }


    // 사이클 감지 유틸리티 함수 (방향 그래프용)
    bool cycleDetect(int v, vector<bool>& recStack) {
        visited[v] = true;
        recStack[v] = true;

        for (int neighbor : adj[v]) {
            if (!visited[neighbor] && cycleDetect(neighbor, recStack)) {
                return true;
            } else if (recStack[neighbor]) {
                return true;
            }
        }

        recStack[v] = false;
        return false;
    }

};

int main() {
    Graph graph(8);

    // Add edges
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 8);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);
    graph.addEdge(6, 7);
    graph.addEdge(6, 8);
    graph.addEdge(7, 8);

    cout << "DFS starting from vertex 1:" << endl;
    graph.DFS(1);

    cout << "DFS for all vertices:" << endl;
    graph.DFSAll();

    cout << "DFS Stack starting from vertex 1:" << endl;
    graph.DFSStack(1);

    cout << "Are all nodes connected? " << (graph.areAllConnected() ? "Yes" : "No") << endl;
    cout << "Number of islands: " << graph.countIslands() << endl;
    cout << "Does the graph have a cycle? " << (graph.hasCycle() ? "Yes" : "No") << endl;


    return 0;
}



/////////// vector 형태 /////////////////
/////////// undirected, directed 모두 표현 가능 ////////
// #include <iostream>
// #include <vector>
// #include <stack>

// using namespace std;


// class Graph {
// public:
//     Graph(const vector<vector<int>>& graph) {
//         adj = graph;
//         V = graph.size();
//         visited.resize(V, false);
//     }

//     void DFS(int v) {
//         // 시작 정점에서 DFS 수행
//         DFSUtil(v);

//         // 방문되지 않은 다른 섬들 탐색
//         for (int i = 1; i < V; ++i) { // 인덱스 1부터 시작
//             if (!visited[i]) {
//                 DFSUtil(i);
//             }
//         }
//     }

//     // DFS using Stack (Iterative)
//     void DFSStack(int v) {
//         fill(visited.begin(), visited.end(), false); // 방문 배열 초기화
//         stack<int> s;
//         s.push(v);

//         while (!s.empty()) {
//             int node = s.top();
//             s.pop();

//             if (!visited[node]) {
//                 visited[node] = true;
//                 cout << node << " ";

//                 // 인접 노드를 스택에 추가 (역순으로 추가하여 스택의 특성에 맞게 처리)
//                 for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
//                     if (!visited[*it]) {
//                         s.push(*it);
//                     }
//                 }
//             }
//         }

//         // 방문되지 않은 다른 섬들 탐색
//         for (int i = 1; i < V; ++i) {
//             if (!visited[i]) {
//                 s.push(i);
//                 while (!s.empty()) {
//                     int node = s.top();
//                     s.pop();

//                     if (!visited[node]) {
//                         visited[node] = true;
//                         cout << node << " ";

//                         for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
//                             if (!visited[*it]) {
//                                 s.push(*it);
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }


//     bool areAllConnected() {
//         fill(visited.begin(), visited.end(), false);  // 방문 배열 초기화
//         DFSUtil2(1);  // 첫 번째 노드부터 시작 (1번 노드)

//         for (int i = 1; i < V; ++i) {
//             if (!visited[i]) {
//                 return false;  // 연결되지 않은 노드가 있으면 false 반환
//             }
//         }
//         return true;
//     }

//     int countIslands() {
//         fill(visited.begin(), visited.end(), false);  // 방문 배열 초기화
//         int islandCount = 0;

//         for (int i = 1; i < V; ++i) {
//             if (!visited[i]) {
//                 DFSUtil2(i);
//                 islandCount++;
//             }
//         }
//         return islandCount;
//     }

//     bool hasCycle() {
//         fill(visited.begin(), visited.end(), false);  // 방문 배열 초기화
//         vector<bool> recStack(V, false);  // 재귀 스택을 사용하여 사이클을 감지

//         for (int i = 1; i < V; ++i) {
//             if (!visited[i]) {
//                 if (cycleDetect(i, recStack)) {
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }

// private:
//     int V; // Number of vertices
//     vector<vector<int>> adj; // Adjacency lists
//     vector<bool> visited; // Visited vertices

//     void DFSUtil(int v) {
//         visited[v] = true;
//         cout << v << " ";

//         for (int neighbor : adj[v]) {
//             if (!visited[neighbor]) {
//                 DFSUtil(neighbor);
//             }
//         }
//     }

//     void DFSUtil2(int v) {
//         visited[v] = true;

//         for (int neighbor : adj[v]) {
//             if (!visited[neighbor]) {
//                 DFSUtil2(neighbor);
//             }
//         }
//     }


//     bool cycleDetect(int v, vector<bool>& recStack) {
//         visited[v] = true;
//         recStack[v] = true;

//         for (int neighbor : adj[v]) {
//             if (!visited[neighbor] && cycleDetect(neighbor, recStack)) {
//                 return true;
//             } else if (recStack[neighbor]) {
//                 return true;
//             }
//         }

//         recStack[v] = false;
//         return false;
//     }

// };



// int main() {
//     vector<vector<int>> graph = {
//         {},
//         {2, 3},
//         {8},
//         {4, 5},
//         {5},
//         {},
//         {7},
//         {},
//         {}
//     };

//     //1 2 8 3 4 5 6 7

//     cout << "Graph size: " << graph.size() << endl;

//     Graph g(graph);
//     cout << "DFS starting from vertex 1:\n";
//     g.DFS(1);
//     printf("\n");
//     g.DFSStack(1);

//     cout << "\nAre all nodes connected? " << (g.areAllConnected() ? "Yes" : "No") << endl;

//     cout << "Number of islands: " << g.countIslands() << endl;

//     cout << "Does the graph have a cycle? " << (g.hasCycle() ? "Yes" : "No") << endl;

//     return 0;
// }