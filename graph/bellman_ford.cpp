/*
Single-destination shortest-paths problem: find a shortest path to a given destination vertex t from each vertex v
Single-pair shortest-path problem: find a shortest path from u  to v for given vertices u and v (한 노드에서 다른 노드까지의 최단 기록 거리)
=> bellman-ford(edge 가중치가 음수인 경우에도 사용 가능, 다만 dijkstra보다 시간복잡도가 크다), dijkstra(모든 가중치가 양수인 경우에만 사용)
All-pairs shortest paths problem: find a shortest path from u to v for every pair of vertices u and v
*/

#include <iostream>
#include <vector>

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

void initializeSingleSource(vector<Vertex>& vertices, int source) {
    for (Vertex& vertex : vertices) {
        vertex.dist = INT_MAX;
        vertex.pi = -1;
    }
    vertices[source].dist = 0;
}

void relax(vector<Vertex>& vertices, const Edge& edge) {
    if (vertices[edge.src].dist != INT_MAX && vertices[edge.dst].dist > vertices[edge.src].dist + edge.weight) {
        vertices[edge.dst].dist = vertices[edge.src].dist + edge.weight;
        vertices[edge.dst].pi = edge.src;
    }
}

bool detectNegativeCycle(const vector<Vertex>& vertices, const vector<Edge>& edges) {
    for (const Edge& edge : edges) {
        if (vertices[edge.src].dist != INT_MAX && vertices[edge.dst].dist > vertices[edge.src].dist + edge.weight) {
            return true;  // Negative weight cycle detected
        }
    }
    return false;  // No negative weight cycle detected
}


bool bellmanFord(vector<Vertex>& vertices, const vector<Edge>& edges, int source) {
    initializeSingleSource(vertices, source);
    
    for (int i=1; i<vertices.size(); i++) {
        for (const Edge& edge : edges) {
            relax(vertices, edge);
        }
    }

    for (const Edge& edge : edges) {
        if (vertices[edge.src].dist != INT_MAX && vertices[edge.dst].dist > vertices[edge.src].dist + edge.weight) {
            return false;
        }
    }

    return true;
}

int main() {
    vector<Vertex> vertices(5);
    vector<Edge> edges = {
        {0,1,6}, {0,3,7},
        {1,2,5}, {1,3,8}, {1,4,-4},
        {2,1,-2},
        {3,2,-3}, {3,4,9},
        {4,0,2}, {4,2,7}
    };

    int source = 0;

    if (bellmanFord(vertices, edges, source)) {
        cout << "Shortest path from vertex " << source << ":\n";
        for (int i=0; i<vertices.size(); i++) {
            cout << "Vertex " << i << ": Distance=" << vertices[i].dist << ", Predecessor=" << vertices[i].pi << "\n";
        }
    } else {
        cout << "Negative weight cycle detected. Bellman-Ford algorithm failed.\n";
    }

    return 0;
}