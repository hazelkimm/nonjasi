/*
__DFTHelp: 깊이 우선 탐색(DFS) 보조 함수, 방문하지 않은 노드를 탐색하고 출력합니다.
DFT_recursive: 시작 노드를 지정하여 깊이 우선 탐색을 재귀적으로 수행합니다.
DFT_stack: 시작 노드가 주어진 경우 스택을 사용한 DFS를 수행합니다.

are_connected: 두 노드가 연결되어 있는지 확인하는 함수입니다.
areAllConnected: 그래프의 모든 노드가 연결되어 있는지 확인합니다.
countIslands: 연결된 컴포넌트(섬)의 개수를 세는 함수입니다.
hasCycle: 그래프에 사이클이 있는지 확인하는 함수입니다.
cycleDetect: 사이클을 감지 utility 함수입니다.

shortest_path_bfs: BFS를 사용하여 두 노드 사이의 최단 경로를 찾는 함수입니다.
topological_sort: 방향 그래프에서 위상 정렬을 수행하는 함수입니다.
find_connected_components: 그래프의 연결 요소를 찾는 함수입니다.

detect_cycle_undirected: 무방향 그래프에서 사이클을 감지하는 함수입니다.
detect_cycle_directed: 방향 그래프에서 사이클을 감지하는 함수입니다
*/
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>

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

    // 시작 노드 지정
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

    // 시작 노드 지정 안함함
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

    // 특정 두 노드가 연결되었는지 확인인
    bool are_connected(int u, int v) {
        fill(visited.begin(), visited.end(), false);
        DFSUtil(u);
        return visited[v];
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

    // 두 노드 간의 shortest path 프린트
    vector<int> shortest_path_bfs(int start, int end) {
        vector<int> parent(V, -1); // Track the parent of each node
        queue<int> q;
        fill(visited.begin(), visited.end(), false);

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            if (node == end) break;

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = node;
                }
            }
        }

        vector<int> path;
        for (int at = end; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        if (path.front() != start) path.clear(); // No path found
        return path;
    }

    vector<int> topological_sort() {
        vector<int> indegree(V, 0), result;
        queue<int> q;

        for (int i = 1; i < V; ++i) {
            for (int neighbor : adj[i]) {
                indegree[neighbor]++;
            }
        }

        for (int i = 1; i < V; ++i) {
            if (indegree[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            result.push_back(node);

            for (int neighbor : adj[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) q.push(neighbor);
            }
        }

        if (result.size() != V - 1) result.clear(); // Cycle detected
        return result;
    }

    vector<vector<int>> find_connected_components() {
        fill(visited.begin(), visited.end(), false);
        vector<vector<int>> components;

        for (int i = 1; i < V; ++i) {
            if (!visited[i]) {
                vector<int> component;
                DFSUtilCollect(i, component);
                components.push_back(component);
            }
        }
        return components;
    }

    bool detect_cycle_undirected() {
        fill(visited.begin(), visited.end(), false);
        for (int i = 1; i < V; ++i) {
            if (!visited[i]) {
                if (cycleDetectUndirected(i, -1)) return true;
            }
        }
        return false;
    }

    bool detect_cycle_directed() {
        return hasCycle();
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

    void DFSUtilCollect(int v, vector<int>& component) {
        visited[v] = true;
        component.push_back(v);
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!visited[*i]) DFSUtilCollect(*i, component);
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

    bool cycleDetectUndirected(int v, int parent) {
        visited[v] = true;
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                if (cycleDetectUndirected(neighbor, v)) return true;
            } else if (neighbor != parent) return true;
        }
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
#include <iostream>
#include <vector>
#include <stack>

using namespace std;


class Graph {
public:
    Graph(const vector<vector<int>>& graph) {
        adj = graph;
        V = graph.size();
        visited.resize(V, false);
    }

    void DFS(int v) {
        // 시작 정점에서 DFS 수행
        DFSUtil(v);

        // 방문되지 않은 다른 섬들 탐색
        for (int i = 1; i < V; ++i) { // 인덱스 1부터 시작
            if (!visited[i]) {
                DFSUtil(i);
            }
        }
    }

    // DFS using Stack (Iterative)
    void DFSStack(int v) {
        fill(visited.begin(), visited.end(), false); // 방문 배열 초기화
        stack<int> s;
        s.push(v);

        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) {
                visited[node] = true;
                cout << node << " ";

                // 인접 노드를 스택에 추가 (역순으로 추가하여 스택의 특성에 맞게 처리)
                for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
                    if (!visited[*it]) {
                        s.push(*it);
                    }
                }
            }
        }

        // 방문되지 않은 다른 섬들 탐색
        for (int i = 1; i < V; ++i) {
            if (!visited[i]) {
                s.push(i);
                while (!s.empty()) {
                    int node = s.top();
                    s.pop();

                    if (!visited[node]) {
                        visited[node] = true;
                        cout << node << " ";

                        for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
                            if (!visited[*it]) {
                                s.push(*it);
                            }
                        }
                    }
                }
            }
        }
    }


    bool areAllConnected() {
        fill(visited.begin(), visited.end(), false);  // 방문 배열 초기화
        DFSUtil2(1);  // 첫 번째 노드부터 시작 (1번 노드)

        for (int i = 1; i < V; ++i) {
            if (!visited[i]) {
                return false;  // 연결되지 않은 노드가 있으면 false 반환
            }
        }
        return true;
    }

    int countIslands() {
        fill(visited.begin(), visited.end(), false);  // 방문 배열 초기화
        int islandCount = 0;

        for (int i = 1; i < V; ++i) {
            if (!visited[i]) {
                DFSUtil2(i);
                islandCount++;
            }
        }
        return islandCount;
    }

    bool hasCycle() {
        fill(visited.begin(), visited.end(), false);  // 방문 배열 초기화
        vector<bool> recStack(V, false);  // 재귀 스택을 사용하여 사이클을 감지

        for (int i = 1; i < V; ++i) {
            if (!visited[i]) {
                if (cycleDetect(i, recStack)) {
                    return true;
                }
            }
        }
        return false;
    }

    // Find shortest path between two nodes using BFS
    vector<int> shortest_path_bfs(int start, int end) {
        fill(visited.begin(), visited.end(), false);
        vector<int> parent(V, -1);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            if (node == end) {
                break;
            }

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = node;
                    q.push(neighbor);
                }
            }
        }

        vector<int> path;
        if (!visited[end]) {
            return path; // No path found
        }

        for (int v = end; v != -1; v = parent[v]) {
            path.push_back(v);
        }

        reverse(path.begin(), path.end());
        return path;
    }

    // Topological Sort for a Directed Acyclic Graph (DAG)
    vector<int> topological_sort() {
        vector<int> in_degree(V, 0);
        for (int i = 1; i < V; ++i) {
            for (int neighbor : adj[i]) {
                in_degree[neighbor]++;
            }
        }

        queue<int> q;
        for (int i = 1; i < V; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topo_order;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topo_order.push_back(node);

            for (int neighbor : adj[node]) {
                if (--in_degree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        return topo_order;
    }

    // Find all connected components
    vector<vector<int>> find_connected_components() {
        fill(visited.begin(), visited.end(), false);
        vector<vector<int>> components;

        for (int i = 1; i < V; ++i) {
            if (!visited[i]) {
                vector<int> component;
                DFSUtil3(i, component);
                components.push_back(component);
            }
        }

        return components;
    }

    // Detect cycle in an undirected graph
    bool detect_cycle_undirected() {
        fill(visited.begin(), visited.end(), false);
        vector<bool> parent(V, false);

        for (int i = 1; i < V; ++i) {
            if (!visited[i]) {
                if (cycleDetectUndirected(i, parent)) {
                    return true;
                }
            }
        }
        return false;
    }

    // Detect cycle in a directed graph
    bool detect_cycle_directed() {
        return hasCycle();
    }


private:
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency lists
    vector<bool> visited; // Visited vertices

    void DFSUtil(int v) {
        visited[v] = true;
        cout << v << " ";

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor);
            }
        }
    }

    void DFSUtil2(int v) {
        visited[v] = true;

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFSUtil2(neighbor);
            }
        }
    }

    void DFSUtil3(int v, vector<int>& component) {
        visited[v] = true;
        component.push_back(v);
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFSUtil3(neighbor, component);
            }
        }
    }


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

    bool cycleDetectUndirected(int v, vector<bool>& parent) {
        visited[v] = true;

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                parent[neighbor] = v;
                if (cycleDetectUndirected(neighbor, parent)) {
                    return true;
                }
            } else if (parent[v] != neighbor) {
                return true; // Cycle found
            }
        }

        return false;
    }

};



int main() {
    vector<vector<int>> graph = {
        {},
        {2, 3},
        {8},
        {4, 5},
        {5},
        {},
        {7},
        {},
        {}
    };

    //1 2 8 3 4 5 6 7

    cout << "Graph size: " << graph.size() << endl;

    Graph g(graph);
    cout << "DFS starting from vertex 1:\n";
    g.DFS(1);
    printf("\n");
    g.DFSStack(1);

    cout << "\nAre all nodes connected? " << (g.areAllConnected() ? "Yes" : "No") << endl;

    cout << "Number of islands: " << g.countIslands() << endl;

    cout << "Does the graph have a cycle? " << (g.hasCycle() ? "Yes" : "No") << endl;

    return 0;
}