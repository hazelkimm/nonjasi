#include <iostream>
#include <vector>
#include <algorithm>

///////////////////////////////////////////
// Kruskal's Algorithm w/ set operations //
///////////////////////////////////////////


using namespace std;

// 1. Edge 정의
class Edge {
public:
    int src, dst, weight;

    //src, dst, weight라는 세 개의 멤버 변수를 초기화
    Edge(int src, int dst, int weight) : src(src), dst(dst), weight(weight) {}

    /*혹은
    Edge(int src, int dst, int weight) {
        this->src = src;     // this->src는 멤버 변수, src는 매개변수
        this->dst = dst;     // this->dst는 멤버 변수, dst는 매개변수
        this->weight = weight; // this->weight는 멤버 변수, weight는 매개변수
    }
    */
};


//2. find-set
//v가 속한 집합의 대표 요소 찾기
// vertices 벡터는 각 정점의 부모 저장하는 배열
//v의 부모를 재귀적으로 찾아서 최종적 루트 노드 찾기. 그리고 찾은 루트노드를 v의 부모로 설정
int Find(vector<int>& vertices, int v) {
    if (v == vertices[v]) {
        return v;
    } else {
        return vertices[v] = Find(vertices, vertices[v]);
    }
}

// 3. Union 함수
void Union(vector<int>& vertices, int a, int b) {
    a = Find(vertices, a);
    b = Find(vertices, b);

    // b로 통합
    if (a != b) {
        vertices[a] = b;
    }
}


//랭크 기반병합: 트리의 높이를 최소화하기 위해 더 낮은 랭크의 트리를 더 높은 랭크의 트리에 병합
// void Union(vector<int>& parent, vector<int>& rank, int u, int v) {
//     int rootU = Find(parent, u);
//     int rootV = Find(parent, v);
//     if (rootU != rootV) {
//         if (rank[rootU] < rank[rootV]) {
//             parent[rootU] = rootV;
//         } else if (rank[rootU] > rank[rootV]) {
//             parent[rootV] = rootU;
//         } else {
//             parent[rootV] = rootU;
//             rank[rootU]++;
//         }
//     }
// }

vector<Edge> MSTKruskal(vector<int>& vertices, vector<Edge>& edges) {
    vector<Edge> mst;

    //edge를 가중치로 오름차순 정렬
    //a와 b를 받아서, a의 weight이 b의 weight보다 작으면 true임을 기준으로 edges의 처음부터 끝까지 오름차순 정렬
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });
    
    //랭크 활용시
    // vector<int> rank(vertices.size(), 0);

    // edge를 하나씩 확인하기
    for (const Edge& edge : edges) {
        int set1 = Find(vertices, edge.src);
        int set2 = Find(vertices, edge.dst);

        // 두 정점이 다른 집합에 속하면 MST에 추가하고 집합 병합
        if (set1 != set2) {
            mst.push_back(edge);
            Union(vertices, set1, set2);
        }
    }

    return mst;
}


int main() {
    int V = 9, E = 14;
    vector<int> vertices;
    vector<Edge> edges;
    
    for (int i=0; i<V; i++) {
        vertices.push_back(i);
    }
    /*혹은,
    vector<int> vertices(V);  
    for (int i = 0; i < V; i++) {
        vertices[i] = i;
    }
    */
    // 0 1 2 3 4 5 6 7 8

    edges.push_back(Edge(0, 1, 4));
    edges.push_back(Edge(0, 7, 8));
    edges.push_back(Edge(1, 2, 8));
    edges.push_back(Edge(1, 7, 11));
    edges.push_back(Edge(2, 3, 7));
    edges.push_back(Edge(2, 5, 4));
    edges.push_back(Edge(2, 8, 2));
    edges.push_back(Edge(3, 4, 9));
    edges.push_back(Edge(3, 5, 14));
    edges.push_back(Edge(4, 5, 10));
    edges.push_back(Edge(5, 6, 2));
    edges.push_back(Edge(6, 7, 1));
    edges.push_back(Edge(6, 8, 6));
    edges.push_back(Edge(7, 8, 7));

    vector<Edge> mst = MSTKruskal(vertices, edges);

    int totalWeight = 0;
    cout << "MST by Kruskal's Algorithm:" << endl;
    for (const Edge& edge : mst) {
        cout << "Edge: " << edge.src << " - " << edge.dst << ", Weight: " << edge.weight << endl;
        totalWeight += edge.weight;
    }

    cout << "Total Weight of MST: " << totalWeight << endl;

    return 0;
}

//혹은, 


// C++ program for Kruskal's algorithm to find Minimum 
// Spanning Tree of a given connected, undirected and 
// // weighted graph 
// #include<bits/stdc++.h> 
// using namespace std; 
  
// // Creating shortcut for an integer pair 
// typedef pair<int, int> iPair; 
  
// // Structure to represent a graph 
// struct Graph 
// { 
//     int V, E; 
//     vector< pair<int, iPair> > edges; 
  
//     // Constructor 
//     Graph(int V, int E) 
//     { 
//         this->V = V; 
//         this->E = E; 
//     } 
  
//     // Utility function to add an edge 
//     void addEdge(int u, int v, int w) 
//     { 
//         edges.push_back({w, {u, v}}); 
//     } 
  
//     // Function to find MST using Kruskal's 
//     // MST algorithm 
//     int kruskalMST(); 
// }; 
  
// // To represent Disjoint Sets 
// struct DisjointSets 
// { 
//     int *parent, *rnk; 
//     int n; 
  
//     // Constructor. 
//     DisjointSets(int n) 
//     { 
//         // Allocate memory 
//         this->n = n; 
//         parent = new int[n+1]; 
//         rnk = new int[n+1]; 
  
//         // Initially, all vertices are in 
//         // different sets and have rank 0. 
//         for (int i = 0; i <= n; i++) 
//         { 
//             rnk[i] = 0; 
  
//             //every element is parent of itself 
//             parent[i] = i; 
//         } 
//     } 
  
//     // Find the parent of a node 'u' 
//     // Path Compression 
//     int find(int u) 
//     { 
//         /* Make the parent of the nodes in the path 
//         from u--> parent[u] point to parent[u] */
//         if (u != parent[u]) 
//             parent[u] = find(parent[u]); 
//         return parent[u]; 
//     } 
  
//     // Union by rank 
//     void merge(int x, int y) 
//     { 
//         x = find(x), y = find(y); 
  
//         /* Make tree with smaller height 
//         a subtree of the other tree */
//         if (rnk[x] > rnk[y]) 
//             parent[y] = x; 
//         else // If rnk[x] <= rnk[y] 
//             parent[x] = y; 
  
//         if (rnk[x] == rnk[y]) 
//             rnk[y]++; 
//     } 
// }; 
  
// /* Functions returns weight of the MST*/
  
// int Graph::kruskalMST() 
// { 
//     int mst_wt = 0; // Initialize result 
  
//     // Sort edges in increasing order on basis of cost 
//     sort(edges.begin(), edges.end()); 
  
//     // Create disjoint sets 
//     DisjointSets ds(V); 
  
//     // Iterate through all sorted edges 
//     vector< pair<int, iPair> >::iterator it; 
//     for (it=edges.begin(); it!=edges.end(); it++) 
//     { 
//         int u = it->second.first; 
//         int v = it->second.second; 
  
//         int set_u = ds.find(u); 
//         int set_v = ds.find(v); 
  
//         // Check if the selected edge is creating 
//         // a cycle or not (Cycle is created if u 
//         // and v belong to same set) 
//         if (set_u != set_v) 
//         { 
//             // Current edge will be in the MST 
//             // so print it 
//             cout << u << " - " << v << endl; 
  
//             // Update MST weight 
//             mst_wt += it->first; 
  
//             // Merge two sets 
//             ds.merge(set_u, set_v); 
//         } 
//     } 
  
//     return mst_wt; 
// } 
  
// // Driver program to test above functions 
// int main() 
// { 
//     /* Let us create above shown weighted 
//     and undirected graph */
//     int V = 9, E = 14; 
//     Graph g(V, E); 
  
//     // making above shown graph 
//     g.addEdge(0, 1, 4); 
//     g.addEdge(0, 7, 8); 
//     g.addEdge(1, 2, 8); 
//     g.addEdge(1, 7, 11); 
//     g.addEdge(2, 3, 7); 
//     g.addEdge(2, 8, 2); 
//     g.addEdge(2, 5, 4); 
//     g.addEdge(3, 4, 9); 
//     g.addEdge(3, 5, 14); 
//     g.addEdge(4, 5, 10); 
//     g.addEdge(5, 6, 2); 
//     g.addEdge(6, 7, 1); 
//     g.addEdge(6, 8, 6); 
//     g.addEdge(7, 8, 7); 
  
//     cout << "Edges of MST are \n"; 
//     int mst_wt = g.kruskalMST(); 
  
//     cout << "\nWeight of MST is " << mst_wt; 
  
//     return 0; 
// } 