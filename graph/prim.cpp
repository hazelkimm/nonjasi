#include <iostream>
#include <cmath>
#include <climits>
#include <vector>

////////////////////////////////////////////
// Prim's Algorithm w/ min-priority queue //
////////////////////////////////////////////

using namespace std;

class Vertex {
public:
    int name;  //정점의 고유 식별자
    int key;   //현재 정점이 MST에 포함된 정점들로부터 접근할 수 있는 최소 간선 비용
    int pi;    //MST 내에서 정점의 부모
    vector<int> adj;

    // 기본 생성자
    Vertex() : key(INT_MAX), pi(-1) {}
    /*
    혹은,
    Vertex() {
        key = INT_MAX;
        pi = -1;
    }
    */

    void initialize(int i) {  //key, pi 초기화하기
        name = i;
        key = INT_MAX;
        pi = -1;
    }
};

class Graph {
public:
    vector<Vertex> vertices;   //Vertex 객체들로 이루어진 벡터 {Vertex, Vertex, Vertex, Vertex, ...}
    vector<vector<int>> weights; //{{int, int, int...}, {int, int, int, ...}, {int, int, int,...}}

    // vertices 벡터를 numVertex 크기로 초기화. numVertex 개수만큼 Vertex 개체 생성
    // weights 벡터를 initialWeights 벡터로 초기화
    Graph(int numVertex, const vector<vector<int>>& initialWeights) : vertices(numVertex), weights(initialWeights) {
        // Initialize adjacency lists
        for (int i=0; i<numVertex; i++) {
            for (int j=0; j<numVertex; j++) {
                if (i != j && weights[i][j] != INT_MAX) {
                    vertices[i].adj.push_back(j);
                }
            }
        }
    }
};

class Heap {
public:
    Vertex *harr;
    int capacity;
    int heap_size;

    Heap(int capacity);

    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }

    int idxHeap(int name);

    void minHeapify(int i);

    int minHeapMinimum();
    int minHeapExtractMin();
    void minHeapDecreaseKey(int i, int key);
    void minHeapInsert(Vertex& key);
};

Heap::Heap(int capacity) {
    this->capacity = capacity;
    heap_size = 0;
    harr = new Vertex[capacity];
}

// 특정 이름(key)을 가진 정점의 index(위치) 찾기
int Heap::idxHeap(int name) {
    for (int i=0; i<heap_size; i++) {
        if (harr[i].name == name) {
            return i;
        }
    }
    return -1;
}

void Heap::minHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l < heap_size && harr[l].key < harr[i].key) {
        smallest = l;
    }
    if (r < heap_size && harr[r].key < harr[smallest].key) {
        smallest = r;
    }

    if (smallest != i) {
        // swap(harr[i], harr[smallest]);
        Vertex tmp = harr[i];
        harr[i] = harr[smallest];
        harr[smallest] = tmp;
        
        minHeapify(smallest);
    }
}

int Heap::minHeapMinimum() {
    if (heap_size < 1) {
        cerr << "Error: Heap underflow\n";
        return INT_MAX;
    }

    return harr[0].name;
}

int Heap::minHeapExtractMin() {
    //힙에서 가장 작은 키 값을 가진 노드의 이름 가져오기
    int minVertex = minHeapMinimum();

    //루트 노드를 마지막 노드로 대체(공간을 줄여야 하니깐)
    harr[0] = harr[heap_size - 1];
    heap_size--;
    //힙 속성을 유지하기 위해 루트노드에서부터 재정렬
    minHeapify(0);

    return minVertex;
}

// 주어진 정점의 키 값을 새로운 키 값으로 줄이기
void Heap::minHeapDecreaseKey(int i, int key) {
    if (key > harr[i].key) {
        cerr << "Error: New key is larger than the current key\n";
        return;
    }

    harr[i].key = key;

    // 현재 노드를 부모 노드와 비교하며 힙 속성 유지
    while (i > 0 && harr[parent(i)].key > harr[i].key) {
        // swap(harr[i], harr[parent(i)]);
        Vertex tmp = harr[i];
        harr[i] = harr[parent(i)];
        harr[parent(i)] = tmp;
        
        // 인덱스를 부모 노드로 업데이트
        i = parent(i);
    }
}

// 새로운 요소를 힙에 삽입
void Heap::minHeapInsert(Vertex& x) {
    if (heap_size == capacity) {
        cerr << "Error: Heap overflow\n";
        return;
    }

    // 힙 크기 증가
    heap_size++;
    // 새로운 요소를 힙의 마지막 위치에 삽입
    int i = heap_size - 1;
    harr[i] = x;

    // 삽입한 요소의 키 값을 삽입할 키 값으로 업데이트
    minHeapDecreaseKey(i, x.key);
}



void MSTPrim(Graph& graph, int r) {
    //모든 정점 초기화
    for (int i=0; i<graph.vertices.size(); i++) {
        graph.vertices[i].initialize(i);
    }

    //시작 정점의 키 값을 0으로 설정
    graph.vertices[r].key = 0;
    Heap Q(20);

    // 모든 정점을 힙에 삽임
    for (int i=0; i<graph.vertices.size(); i++) {
        Q.minHeapInsert(graph.vertices[i]);
    }

    //힙이 비어있지 않은 동안 반복
    while (Q.heap_size != 0) {
        // 키 값이 가장 작은 정점을 힙에서 제거
        int u = Q.minHeapExtractMin();
        
        // 제거된 정점과 인접한 모든 정점 탐색
        for (int v : graph.vertices[u].adj) {
            //정점이 힙에 있고, 새 경로의 비용이 현재 키 값보다 작으면 키 값을 갱신
            if (Q.idxHeap(v) != -1 && graph.weights[u][v] < graph.vertices[v].key) {
                graph.vertices[v].pi = u;
                graph.vertices[v].key = graph.weights[u][v];
                Q.minHeapDecreaseKey(Q.idxHeap(v), graph.weights[u][v]);
            }
        }
    }
}


int main() {
    // [#14] p.28 graphe example
    int numVertex = 9;
    vector<vector<int>> initialWeights = {
        {0, 4, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 8, INT_MAX},
        {4, 0, 8, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 11, INT_MAX},
        {INT_MAX, 8, 0, 7, INT_MAX, 4, INT_MAX, INT_MAX, 2},
        {INT_MAX, INT_MAX, 7, 0, 9, 14, INT_MAX, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, 9, 0, 10, INT_MAX, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, 4, 14, 10, 0, 2, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 2, 0, 1, 6},
        {8, 11, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1, 0, 7},
        {INT_MAX, INT_MAX, 2, INT_MAX, INT_MAX, INT_MAX, 6, 7, 0}
    };

    Graph graph(numVertex, initialWeights);
    
    MSTPrim(graph, 0);

    int totalWeight = 0;
    for (int i=0; i<numVertex; i++) {
        if (graph.vertices[i].pi != -1) {
            // Edge from 'vertices[i].pi -> i' in the MST
            cout << "Edge: " << graph.vertices[i].pi << " - " << i << ", Weight: " << graph.weights[graph.vertices[i].pi][i] << endl;
            totalWeight += graph.weights[graph.vertices[i].pi][i];
        }
    }
    /*
    혹은,
    for (int i = 0; i < numVertex; i++) {
        totalWeight += graph.vertices[i].key;
    }
    */

    cout << "Total Weight of MST: " << totalWeight << endl;

    return 0;
}