// DFS (깊이 우선 탐색)
// BFS (너비 우선 탐색)
// findCircleNum (서로 연결된 노드의 그룹 수 찾기)
// 최단 경로 탐색 (Dijkstra 알고리즘)
// 최소 신장 트리 (Kruskal 알고리즘)
// 사이클 존재 여부 확인 (DFS를 이용한 사이클 탐지)
// 위상 정렬 (Topological Sort)
// 이진 트리에서 가장 가까운 공통 조상 찾기 (LCA)
// 벨만-포드 알고리즘 (음수 가중치 포함 최단 경로)
// 최대 유량 문제 (Ford-Fulkerson 알고리즘)




// DFS (깊이 우선 탐색)
#include <iostream>
#include <vector>

using namespace std;

// 그래프를 표현하기 위한 구조체
class Graph {
public:
    int V; // 정점의 개수
    vector<vector<int>> adjList; // 인접 리스트

    Graph(int vertices) {
        V = vertices;
        adjList.resize(vertices);
    }

    // 간선을 추가하는 함수
    void addEdge(int src, int dst) {
        adjList[src].push_back(dst);
        adjList[dst].push_back(src); // 무방향 그래프이므로 양쪽에 간선을 추가
    }

    // DFS를 위한 재귀 함수
    void recursiveDFS(int current, vector<bool>& visited) {
        cout << current << " ";
        visited[current] = true;

        for (int neighbor : adjList[current]) {
            if (!visited[neighbor]) {
                recursiveDFS(neighbor, visited);
            }
        }
    }

    // DFS 함수
    void DFS(int startNode) {
        vector<bool> visited(V, false);
        cout << "DFS starting from node " << startNode << ": ";
        recursiveDFS(startNode, visited);
        cout << endl;
    }
};

int main() {
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 4}, {3, 4}};
    int numNodes = 5;

    Graph graph(numNodes);
    for (auto edge : edges) {
        graph.addEdge(edge.first, edge.second);
    }

    int startNode = 0;
    graph.DFS(startNode);

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BFS (너비 우선 탐색)
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
public:
    int V; // 정점의 개수
    vector<vector<int>> adjList; // 인접 리스트

    Graph(int vertices) {
        V = vertices;
        adjList.resize(vertices);
    }

    // 간선을 추가하는 함수
    void addEdge(int src, int dst) {
        adjList[src].push_back(dst);
        adjList[dst].push_back(src); // 무방향 그래프이므로 양쪽에 간선을 추가
    }

    // BFS 함수
    void BFS(int startNode) {
        vector<bool> visited(V, false);
        queue<int> q;

        cout << "BFS starting from node " << startNode << ": ";
        visited[startNode] = true;
        q.push(startNode);

        while (!q.empty()) {
            int currentNode = q.front();
            q.pop();
            cout << currentNode << " ";

            for (int neighbor : adjList[currentNode]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 4}, {3, 4}};
    int numNodes = 5;

    Graph graph(numNodes);
    for (auto edge : edges) {
        graph.addEdge(edge.first, edge.second);
    }

    int startNode = 0;
    graph.BFS(startNode);

    return 0;
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// findCircleNum (서로 연결된 노드의 그룹 수 찾기)
#include <iostream>
#include <vector>

using namespace std;

// DFS를 이용한 연결된 노드 방문
void dfs(vector<vector<int>>& isConnected, vector<bool>& visited, int i) {
    visited[i] = true;
    for (int j = 0; j < isConnected.size(); j++) {
        if (isConnected[i][j] == 1 && !visited[j]) {
            dfs(isConnected, visited, j);
        }
    }
}

// 연결된 그룹(서클)의 수를 찾는 함수
int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    vector<bool> visited(n, false);
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(isConnected, visited, i);
            count++;
        }
    }

    return count;
}

int main() {
    vector<vector<int>> isConnected1 = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };

    vector<vector<int>> isConnected2 = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    cout << "Number of circles (matrix 1): " << findCircleNum(isConnected1) << endl; // Output: 2
    cout << "Number of circles (matrix 2): " << findCircleNum(isConnected2) << endl; // Output: 3

    return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 최단 경로 탐색 (Dijkstra 알고리즘)
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

#define V 5

// 최단 거리 미방문 정점 찾기
int minDistance(vector<int>& dist, vector<bool>& sptSet) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// 최단 거리 결과 출력
void printSolution(vector<int>& dist) {
    cout << "Vertex \t Distance from Source\n";
    for (int i = 0; i < V; i++)
        cout << i << " \t\t " << dist[i] << endl;
}

// 다익스트라 알고리즘 구현
void dijkstra(int graph[V][V], int src) {
    vector<int> dist(V, INT_MAX); // 최단 거리 배열
    vector<bool> sptSet(V, false); // 방문 여부 배열
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist);
}

int main() {
    int graph[V][V] = {
        {0, 10, 0, 0, 5},
        {0, 0, 1, 0, 2},
        {0, 0, 0, 4, 0},
        {7, 0, 6, 0, 0},
        {0, 3, 9, 2, 0}
    };

    dijkstra(graph, 0);
    return 0;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 최소 신장 트리 (Kruskal 알고리즘)
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define V 4
#define E 5

// 간선 구조체 정의
struct Edge {
    int src, dest, weight;
};

// 부분 집합 구조체 정의
struct Subset {
    int parent, rank;
};

// 부모를 찾는 함수 (경로 압축)
int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// 두 집합을 합치는 함수 (랭크에 따른 합치기)
void Union(vector<Subset>& subsets, int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// 간선을 오름차순으로 정렬하기 위한 비교 함수
bool cmp(Edge a, Edge b) {
    return a.weight < b.weight;
}

// 크루스칼 알고리즘 구현
void Kruskal(vector<Edge>& edges, int V, int E) {
    sort(edges.begin(), edges.end(), cmp);

    vector<Subset> subsets(V);
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    cout << "Edges in the MST:\n";
    int e = 0, i = 0;
    while (e < V - 1 && i < E) {
        Edge next_edge = edges[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            cout << next_edge.src << " -- " << next_edge.dest << " == " << next_edge.weight << endl;
            Union(subsets, x, y);
            e++;
        }
    }
}

int main() {
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    Kruskal(edges, V, E);
    return 0;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 사이클 존재 여부 확인 (DFS를 이용한 사이클 탐지)


#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    int V; // 정점의 개수
    vector<vector<int>> adjList; // 인접 리스트

    Graph(int vertices) {
        V = vertices;
        adjList.resize(vertices);
    }

    // 간선을 추가하는 함수
    void addEdge(int src, int dst) {
        adjList[src].push_back(dst);
        adjList[dst].push_back(src); // 무방향 그래프이므로 양쪽에 간선을 추가
    }

    // DFS를 이용한 사이클 탐지 함수
    bool isCyclicUtil(int v, vector<bool>& visited, int parent) {
        visited[v] = true;

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                if (isCyclicUtil(neighbor, visited, v))
                    return true;
            } else if (neighbor != parent) {
                return true;
            }
        }
        return false;
    }

    // 그래프에서 사이클이 있는지 확인하는 함수
    bool isCyclic() {
        vector<bool> visited(V, false);

        for (int u = 0; u < V; u++) {
            if (!visited[u]) {
                if (isCyclicUtil(u, visited, -1))
                    return true;
            }
        }
        return false;
    }
};

int main() {
    Graph graph(4);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);

    if (graph.isCyclic())
        cout << "Graph contains cycle\n";
    else
        cout << "Graph doesn't contain cycle\n";

    return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 위상 정렬 (Topological Sort)

#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    int V; // 정점의 개수
    vector<vector<int>> adjList; // 인접 리스트

    Graph(int vertices) {
        V = vertices;
        adjList.resize(vertices);
    }

    // 간선을 추가하는 함수
    void addEdge(int src, int dst) {
        adjList[src].push_back(dst);
    }

    // 위상 정렬을 위한 재귀 함수
    void topologicalSortUtil(int v, vector<bool>& visited, vector<int>& stack) {
        visited[v] = true;

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                topologicalSortUtil(neighbor, visited, stack);
            }
        }

        stack.push_back(v);
    }

    // 위상 정렬 함수
    void topologicalSort() {
        vector<bool> visited(V, false);
        vector<int> stack;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, stack);
            }
        }

        cout << "Topological Sort: ";
        for (int i = stack.size() - 1; i >= 0; i--) {
            cout << stack[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Graph graph(6);
    graph.addEdge(5, 2);
    graph.addEdge(5, 0);
    graph.addEdge(4, 0);
    graph.addEdge(4, 1);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    graph.topologicalSort();

    return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 이진 트리에서 가장 가까운 공통 조상 찾기 (LCA)

#include <iostream>

using namespace std;

// 이진 트리 노드 구조체
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// LCA를 찾는 함수
Node* findLCA(Node* root, int n1, int n2) {
    if (root == nullptr)
        return nullptr;

    if (root->data == n1 || root->data == n2)
        return root;

    Node* left_lca = findLCA(root->left, n1, n2);
    Node* right_lca = findLCA(root->right, n1, n2);

    if (left_lca && right_lca)
        return root;

    return (left_lca != nullptr) ? left_lca : right_lca;
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    Node* lca = findLCA(root, 4, 5);
    if (lca != nullptr)
        cout << "LCA of 4 and 5 is " << lca->data << endl;
    else
        cout << "LCA does not exist\n";

    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 벨만-포드 알고리즘 (음수 가중치 포함 최단 경로)

#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

#define V 5
#define E 8

// 간선 구조체 정의
struct Edge {
    int src, dest, weight;
};

// 벨만-포드 알고리즘 구현
void bellmanFord(vector<Edge>& edges, int V, int E, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative weight cycle\n";
            return;
        }
    }

    cout << "Vertex Distance from Source\n";
    for (int i = 0; i < V; i++) {
        cout << i << " \t\t " << dist[i] << endl;
    }
}

int main() {
    vector<Edge> edges = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };

    bellmanFord(edges, V, E, 0);

    return 0;
}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 최대 유량 문제 (Ford-Fulkerson 알고리즘)
#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>

using namespace std;

#define V 6 // 정점의 개수

// BFS를 이용하여 증가 경로를 찾는 함수
bool bfs(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}

// 포드-풀커슨 알고리즘을 이용한 최대 유량 계산
int fordFulkerson(vector<vector<int>>& graph, int s, int t) {
    vector<vector<int>> rGraph = graph;
    vector<int> parent(V);
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    vector<vector<int>> graph = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 5) << endl;

    return 0;
}
