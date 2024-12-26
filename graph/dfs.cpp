#include <iostream>
#include <vector>
#include <stack>

////////////////////////////////////////////////////////////
// DFS + Topological Sort + Strongly Connected Components //
////////////////////////////////////////////////////////////

using namespace std;

// 1. Color 정의
enum Color { WHITE, GRAY, BLACK };

// 2. Vertex 정의
class Vertex {
public:
    Color color;
    int pi;
    int discover;       // timestamp for discover (White-> gray 순간의 timestamp)
    int finish;         // timestamp for finish   (gray -> black 순간의 timestamp)
    vector<int> adj;    // Assuming an adjacency list representation

    Vertex() : color(WHITE), pi(-1) {}

    void initialize() {
        color = WHITE;
        pi = -1;
    }
};


// 3. Graph 정의
class Graph {
public:
    vector<Vertex> vertices;

    Graph(int numVertex) : vertices(numVertex) {}
    
    stack<int> DFS() {
        int time = 0; 
        stack<int> finishStack;  

        for (int i=0; i<vertices.size(); i++) {
            vertices[i].initialize();
        }


        for (int i=0; i<vertices.size(); i++) {
            if (vertices[i].color == WHITE) {           // 방문하지 않은 vertex를 기준으로 
                DFS_VISIT(i, time, finishStack);        // DFS 들어가기
            }
        }

        return finishStack;
    }

    void DFS_VISIT(int u, int& time, stack<int>& finishStack) {
        time = time + 1;               // time 증가시키고
        vertices[u].discover = time;   // discover time update하고
        vertices[u].color = GRAY;      // gray로 변경

        for (int v : vertices[u].adj) {
            if (vertices[v].color == WHITE) {
                vertices[v].pi = u;
                DFS_VISIT(v, time, finishStack);     //visit 안된거 깊게 들어가기
            }
        }

        time = time + 1;
        vertices[u].finish = time;    
        vertices[u].color = BLACK;
        finishStack.push(u);
    }


    stack<int> DFS_STACK() {
        int time = 0;
        stack<int> finishStack;

        for (int i = 0; i < vertices.size(); i++) {
            vertices[i].initialize();
        }

        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i].color == WHITE) {
                stack<int> s;
                s.push(i);

                while (!s.empty()) {
                    int u = s.top();
                    s.pop();

                    if (vertices[u].color == WHITE) {
                        time++;
                        vertices[u].discover = time;
                        vertices[u].color = GRAY;
                        s.push(u);

                        for (auto it = vertices[u].adj.rbegin(); it != vertices[u].adj.rend(); ++it) {
                            if (vertices[*it].color == WHITE) {
                                vertices[*it].pi = u;
                                s.push(*it);
                            }
                        }
                    } else if (vertices[u].color == GRAY) {
                        time++;
                        vertices[u].finish = time;
                        vertices[u].color = BLACK;
                        finishStack.push(u);
                    }
                }
            }
        }

        return finishStack;
    }

    bool CheckConnectivity() {
        DFS();
        for (const auto& vertex : vertices) {
            if (vertex.color == WHITE) {
                return false;
            }
        }
        return true;
    }

    int CountIslands() {
        int island_count = 0;
        for (auto& vertex : vertices) {
            vertex.initialize();
        }

        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i].color == WHITE) {
                int time = 0;              // time 변수를 여기서 선언
                stack<int> tempStack;      // stack<int> 변수를 선언
                DFS_VISIT(i, time, tempStack);  // time과 tempStack 변수를 전달
                island_count++;
            }
        }

        return island_count;
    }


    bool DetectCycleUtil(int u) {
        vertices[u].color = GRAY;

        for (int v : vertices[u].adj) {
            if (vertices[v].color == WHITE) {
                if (DetectCycleUtil(v)) {
                    return true;
                }
            } else if (vertices[v].color == GRAY) {
                return true;
            }
        }

        vertices[u].color = BLACK;
        return false;
    }

    bool DetectCycle() {
        for (auto& vertex : vertices) {
            vertex.initialize();
        }

        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i].color == WHITE) {
                if (DetectCycleUtil(i)) {
                    return true;
                }
            }
        }
        return false;
    }

    vector<int> TopologicalSort() {
        vector<int> result;
        stack<int> finishStack;

        finishStack = DFS();      // Compute finish times

        while (!finishStack.empty()) {
            result.push_back(finishStack.top());
            finishStack.pop();
        }

        return result;
    }    
};



int main() {
    // [#11] p.21 graph example
    int numVertex = 6;
    Graph graph(numVertex);

    graph.vertices[0].adj = {1, 3};
    graph.vertices[1].adj = {4};
    graph.vertices[2].adj = {4, 5};
    graph.vertices[3].adj = {1};
    graph.vertices[4].adj = {3};
    graph.vertices[5].adj = {5};

    graph.DFS();

    for (int i=0; i<numVertex; i++) {
        cout << "Vertex " << i << ": Discover=" << graph.vertices[i].discover << ", Finish=" << graph.vertices[i].finish << endl;
    }


    // [#11] p.30 graph example
    // int numVertex = 9;
    // Graph graph(numVertex);

    // graph.vertices[0].adj = {1, 7};
    // graph.vertices[1].adj = {2, 7};
    // graph.vertices[2].adj = {5};
    // graph.vertices[3].adj = {2, 4};
    // graph.vertices[4].adj = {5};
    // graph.vertices[5].adj = {};
    // graph.vertices[6].adj = {7};
    // graph.vertices[7].adj = {};
    // graph.vertices[8].adj = {};

    // vector<int> sortedVertices = graph.TopologicalSort();

    // for (int i=0; i<numVertex; i++) {
    //     cout << "Vertex " << i << ": Discover=" << graph.vertices[i].discover << ", Finish=" << graph.vertices[i].finish << endl;
    // }

    // cout << "Topological Sort: ";
    // for (int vertex : sortedVertices) {
    //     cout << vertex << " ";
    // }
    // cout << endl;

    // DFS using stack-based approach
    graph.DFS_STACK();
    cout << "\nDFS (Stack-based):\n";
    for (int i = 0; i < numVertex; i++) {
        cout << "Vertex " << i << ": Discover=" << graph.vertices[i].discover << ", Finish=" << graph.vertices[i].finish << endl;
    }

    // Check Connectivity
    bool is_connected = graph.CheckConnectivity();
    cout << "\nCheck Connectivity: " << (is_connected ? "Connected" : "Not Connected") << endl;

    // Count Islands
    int islands = graph.CountIslands();
    cout << "Number of Islands: " << islands << endl;

    // Detect Cycle
    bool has_cycle = graph.DetectCycle();
    cout << "Cycle Detection: " << (has_cycle ? "Cycle exists" : "No cycle") << endl;

    // Topological Sort
    vector<int> sortedVertices = graph.TopologicalSort();
    cout << "Topological Sort: ";
    for (int vertex : sortedVertices) {
        cout << vertex << " ";
    }
    cout << endl;

    return 0;
}