// topologically sort the vertices of G

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Edge {
public:
    int src;
    int dst;
    int weight;

    Edge(int src, int dst, int weight) : src(src), dst(dst), weight(weight) {}
};

class Vertex {
public:
    int dist;
    int pi;

    Vertex() : dist(INT_MAX), pi(-1) {}
};

class Graph {
public:
    vector<Vertex> vertices;
    vector<vector<Edge>> adj;

    Graph(int numVertex) : vertices(numVertex), adj(numVertex) {}

    void addEdge(int src, int dst, int weight) {
        adj[src].emplace_back(src, dst, weight);
    }

    void initializeSingleSource(int source) {
        for (Vertex& vertex : vertices) {
            vertex.dist = INT_MAX;
            vertex.pi = -1;
        }
        vertices[source].dist = 0;
    }

    void relax(const Edge& edge) {
        if (vertices[edge.src].dist != INT_MAX && vertices[edge.dst].dist > vertices[edge.src].dist + edge.weight) {
            vertices[edge.dst].dist = vertices[edge.src].dist + edge.weight;
            vertices[edge.dst].pi = edge.src;
        }
    }

    void DFS_VISIT(int u, vector<bool>& visited, stack<int>& finishStack) {
        visited[u] = true;

        for (const Edge& edge : adj[u]) {
            if (!visited[edge.dst]) {
                DFS_VISIT(edge.dst, visited, finishStack);
            }
        }

        finishStack.push(u);
    }

    stack<int> topologicalSort() {
        stack<int> finishStack;
        vector<bool> visited(vertices.size(), false);

        for (int i=0; i<vertices.size(); i++) {
            if (!visited[i]) {
                DFS_VISIT(i, visited, finishStack);
            }
        }

        return finishStack;
    }

    void dagShortestPaths(int source) {
        stack<int> finishStack = topologicalSort();

        initializeSingleSource(source);

        while (!finishStack.empty()) {
            int u = finishStack.top();
            finishStack.pop();

            for (const Edge& edge : adj[u]) {
                relax(edge);
            }
        }

        
    }
};

int main() {
    Graph graph(6);

    graph.addEdge(0,1,5);
    graph.addEdge(0,2,3);
    graph.addEdge(1,2,2);
    graph.addEdge(1,3,6);
    graph.addEdge(2,3,7);
    graph.addEdge(2,4,4);
    graph.addEdge(2,5,2);
    graph.addEdge(3,4,-1);
    graph.addEdge(3,5,1);
    graph.addEdge(4,5,-2);

    int source = 1;
    graph.dagShortestPaths(source);

    cout << "Shortest path from vertex " << source << ":\n";
    for (int i=source; i<graph.vertices.size(); i++) {
        cout << "Vertex " << i << ": Distance=" << graph.vertices[i].dist << ", Predecessor=" << graph.vertices[i].pi << "\n";
    }

    return 0;
}