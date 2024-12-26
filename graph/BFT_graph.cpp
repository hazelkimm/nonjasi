#include <iostream>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;
// class UndiGraph {
// public:
//     // Constructor to initialize the graph with vertices and edges
//     UndiGraph(const vector<int>& V, const vector<pair<int, int>>& E) {
//         this->V = V;
//         for (const auto& v : V) {
//             neighbors[v] = vector<int>();
//         }
//         for (const auto& edge : E) {
//             neighbors[edge.first].push_back(edge.second);
//             neighbors[edge.second].push_back(edge.first);
//         }
//     }


//     /*
//     만약 main함수가 이런식으로 주어진다면 undigraph만 undigraph + addedge로 쪼개면 됨!
//     graph.addEdge(0, 1);
//     graph.addEdge(0, 2);
//     graph.addEdge(1, 3);
//     graph.addEdge(2, 3);
//     graph.addEdge(3, 4);
//     */

//     /*
//     UndiGraph(const vector<int>& V) {
//         this->V = V;
//         for (const auto& v : V) {
//             neighbors[v] = vector<int>();
//         }
//     }

//     // Function to insert an edge
//     void addEdge(int v, int w) {
//         neighbors[v].push_back(w);
//         neighbors[w].push_back(v); // For undirected graph
//     }
//     */



//     // BFS function to traverse the graph starting from a root node
//     void BFS(const int& root) {
//         if (root == NULL) return;

//         queue<int> q;
//         unordered_map<int, bool> visited;

//         for (const auto& v : V) {
//             visited[v] = false;
//         }

//         q.push(root);
//         visited[root] = true;

//         while (!q.empty()) {
//             int curNode = q.front();
//             q.pop();
//             cout << curNode << " ";

//             for (const auto& neighbor : neighbors[curNode]) {
//                 if (!visited[neighbor]) {
//                     q.push(neighbor);
//                     visited[neighbor] = true;
//                 }
//             }
//         }

//         for (int k: V) {
//             if (!visited[k]) {
//                 q.push(k);
//                 visited[k] = true;
//                 while (!q.empty()) {
//                     int curNode = q.front();
//                     q.pop();
//                     cout << curNode << ' ';
//                     for (int v : neighbors[curNode]) {
//                         if (!visited[v]) {
//                             q.push(v);
//                             visited[v] = true;
//                         }
//                     }

//                 }
//             }
//         } 
//     }


  


//     // Shortest path in undirected, unweighted graph
//     vector<int> shortestPath(int start, int goal) {
//         if (start == goal) {
//             return {start};
//         }

//         unordered_map<int, bool> visited;
//         unordered_map<int, int> parent;
//         queue<int> q;

//         q.push(start);
//         visited[start] = true;
//         parent[start] = -1;

//         while (!q.empty()) {
//             int node = q.front();
//             q.pop();

//             for (const auto& neighbor : neighbors[node]) {
//                 if (!visited[neighbor]) {
//                     visited[neighbor] = true;
//                     parent[neighbor] = node;
//                     q.push(neighbor);

//                     if (neighbor == goal) {
//                         vector<int> path;
//                         for (int at = goal; at != -1; at = parent[at]) {
//                             path.push_back(at);
//                         }
//                         reverse(path.begin(), path.end());
//                         return path;
//                     }
//                 }
//             }
//         }
//         return {}; // No path found
//     }

//     // Check if all nodes are connected
//     bool areAllConnected() {
//         if (V.empty()) return false;

//         unordered_map<int, bool> visited;
//         for (const auto& v : V) {
//             visited[v] = false;
//         }

//         int count = 0;
//         queue<int> q;
//         q.push(V[0]);

//         while (!q.empty()) {
//             int node = q.front();
//             q.pop();

//             if (!visited[node]) {
//                 visited[node] = true;
//                 count++;
//                 for (const auto& neighbor : neighbors[node]) {
//                     if (!visited[neighbor]) {
//                         q.push(neighbor);
//                     }
//                 }
//             }
//         }

//         return count == V.size();
//     }

//     // Count the number of islands (connected components)
//     int countIslands() {
//         if (V.empty()) return 0;

//         unordered_map<int, bool> visited;
//         for (const auto& v : V) {
//             visited[v] = false;
//         }

//         int island_count = 0;

//         for (const auto& v : V) {
//             if (!visited[v]) {
//                 queue<int> q;
//                 q.push(v);
//                 island_count++;

//                 while (!q.empty()) {
//                     int node = q.front();
//                     q.pop();

//                     if (!visited[node]) {
//                         visited[node] = true;
//                         for (const auto& neighbor : neighbors[node]) {
//                             if (!visited[neighbor]) {
//                                 q.push(neighbor);
//                             }
//                         }
//                     }
//                 }
//             }
//         }

//         return island_count;
//     }

//     // Cycle detection in undirected graph
//     bool hasCycleUtil(int v, unordered_map<int, bool>& visited, unordered_map<int, bool>& recursionStack) {
//         visited[v] = true;
//         recursionStack[v] = true;

//         for (int neighbor : neighbors[v]) {
//             if (!visited[neighbor] && hasCycleUtil(neighbor, visited, recursionStack))
//                 return true;
//             else if (recursionStack[neighbor])
//                 return true;
//         }

//         recursionStack[v] = false;
//         return false;
//     }

//     bool hasCycle() {
//         unordered_map<int, bool> visited;
//         unordered_map<int, bool> recursionStack;

//         for (const auto& v : V) {
//             if (!visited[v]) {
//                 if (hasCycleUtil(v, visited, recursionStack))
//                     return true;
//             }
//         }
//         return false;
//     }


// private:
//     vector<int> V;
//     unordered_map<int, vector<int>> neighbors; // Adjacency list representation


// };

// int main() {
//     vector<int> vertices = {1,2,3,4,5,6,7,8};
//     vector<pair<int, int>> edges = {{1,2}, {1,3}, {2, 8}, {3, 4}, {3, 5}, {4, 5}, {6, 7}, {6, 8}, {7, 8}};

//     // Create the graph
//     UndiGraph graph(vertices, edges);

//     cout << "BFS starting from vertex 1:" << endl;
//     graph.BFS(1);
//     // 1 2 3 8 4 5 6 7
//     cout << endl;

//     cout << "Shortest Path from 1 to 5: ";
//     vector<int> path = graph.shortestPath(1, 5);
//     if (!path.empty()) {
//         for (int node : path) {
//             cout << node << " ";
//         }
//         cout << endl;
//     } else {
//         cout << "No path found" << endl;
//     }

//     cout << "Are all nodes connected? " << (graph.areAllConnected() ? "Yes" : "No") << endl;
//     cout << "Number of islands: " << graph.countIslands() << endl;
//     cout << "Does the graph have a cycle? " << (graph.hasCycle() ? "Yes" : "No") << endl;

//     return 0;
// }






// //혹은, 그래프 자체로 주어졌을 경우
// //include queue하기
#include <queue>

void bfs_helper(const vector<vector<int>>& graph, int node, vector<bool>& visited) {
    queue<int> q;
    visited[node] = true;
    q.push(node);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << v << " ";

        for (int i : graph[v]) {
            if (!visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}


void bfs_helper2(const vector<vector<int>>& graph, int node, vector<bool>& visited) {
    queue<int> q;
    visited[node] = true;
    q.push(node);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        // cout << v << " ";

        for (int i : graph[v]) {
            if (!visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

void bfs(const vector<vector<int>>& graph, int num_nodes, int start_node) {
    vector<bool> visited(num_nodes + 1, false);
    bfs_helper(graph, start_node, visited);

    for (int node = 1; node <= num_nodes; ++node) {
        if (!visited[node]) {
            bfs_helper(graph, node, visited);
        }
    }
    cout << endl;
}


//deque 직접 구현한 버전

// vector<int> bfs_helper(const vector<vector<int>>& graph, int node, vector<bool>& visited) {
//     Deque queue(graph.size());
//     queue.add_rear(node);
//     visited[node] = true;

//     vector<int> result;

//     while (!queue.is_empty()) {
//         int v = queue.delete_front();
//         result.push_back(v);
//         cout << v << " ";

//         for (int neighbor : graph[v]) {
//             if (!visited[neighbor]) {
//                 queue.add_rear(neighbor);
//                 visited[neighbor] = true;
//             }
//         }
//     }
//     return result;
// }

// void bfs(const vector<vector<int>>& graph, int num_nodes, int start_node) {
//     vector<bool> visited(num_nodes + 1, false);
//     bfs_helper(graph, start_node, visited);

//     for (int node = 1; node <= num_nodes; ++node) {
//         if (!visited[node]) {
//             bfs_helper(graph, node, visited);
//         }
//     }
//     cout << endl;
// }
// Function to find the shortest path between two nodes using BFS
vector<int> shortestPath(const vector<vector<int>>& graph, int start, int goal) {
    if (start == goal) {
        return {start};
    }

    vector<bool> visited(graph.size(), false);
    vector<int> parent(graph.size(), -1);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = node;
                q.push(neighbor);

                if (neighbor == goal) {
                    vector<int> path;
                    for (int at = goal; at != -1; at = parent[at]) {
                        path.push_back(at);
                    }
                    reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
    }
    return {}; // No path found
}

// Function to check if all nodes are connected (single connected component)
bool areAllConnected(const vector<vector<int>>& graph) {
    vector<bool> visited(graph.size(), false);
    int count = 0;

    bfs_helper2(graph, 1, visited);
    
    for (bool node_visited : visited) {
        if (node_visited) count++;
    }

    return count == graph.size() - 1;
}

// Function to count the number of islands (connected components)
int countIslands(const vector<vector<int>>& graph) {
    vector<bool> visited(graph.size(), false);
    int island_count = 0;

    for (int i = 1; i < graph.size(); ++i) {
        if (!visited[i]) {
            bfs_helper2(graph, i, visited);
            island_count++;
        }
    }

    return island_count;
}

// Function to detect cycle in an undirected graph
bool hasCycleUtil(int node, const vector<vector<int>>& graph, vector<bool>& visited, vector<bool>& recStack) {
    visited[node] = true;
    recStack[node] = true;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor] && hasCycleUtil(neighbor, graph, visited, recStack)) {
            return true;
        } else if (recStack[neighbor]) {
            return true;
        }
    }

    recStack[node] = false;  // 스택에서 현재 노드 제거
    return false;
}

bool hasCycle(const vector<vector<int>>& graph) {
    vector<bool> visited(graph.size(), false);
    vector<bool> recStack(graph.size(), false);  // 재귀 스택

    for (int i = 1; i < graph.size(); ++i) {
        if (!visited[i]) {
            if (hasCycleUtil(i, graph, visited, recStack)) {
                return true;
            }
        }
    }
    return false;
}


int main() {
    vector<vector<int>> graph = {
        {},
        {2, 3, 8},    // Node 1 connects to Node 2 and 3
        {},       
        {4, 5},    // Node 3 connects to Node 4 and 5
        {5},       // Node 4 connects to Node 5
        {},        // Node 5 has no outgoing connections
        {7, 8},    // Node 6 connects to Node 7 and 8
        {8},       // Node 7 connects to Node 8
        {}         // Node 8 has no outgoing connections
    };

    cout << "Graph size: " << graph.size() << endl;

    cout << "BFS starting from vertex 1:\n";
    bfs(graph, graph.size() - 1, 1);
    cout << endl;

    cout << "Shortest Path from 1 to 5: ";
    vector<int> path = shortestPath(graph, 1, 5);
    if (!path.empty()) {
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found" << endl;
    }

    cout << "Are all nodes connected? " << (areAllConnected(graph) ? "Yes" : "No") << endl;
    cout << "Number of islands: " << countIslands(graph) << endl;
    cout << "Does the graph have a cycle? " << (hasCycle(graph) ? "Yes" : "No") << endl;

    return 0;
}