import sys

class Vertex:
    name = 0
    key = 0
    pi = 0
    adj = []

    def __init__(self, i: int):
        self.name = i
        self.key = sys.maxsize
        self.pi = -1

class Graph:
    vertices = []
    weights = []

    def __init__(self, numVertex: int, initialWeights):
        self.vertices = [Vertex(i) for i in range(numVertex)]
        self.weights = initialWeights
        # initialize adjacency lists
        for i in range(numVertex):
            for j in range(numVertex):
                if (i != j) and (self.weights[i][j] != sys.maxsize):
                    self.vertices[i].adj.append(j)

class Heap:
    harr = []
    capacity = 0
    heap_size = 0

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.heap_size = 0
        self.harr = [sys.maxsize for i in range(capacity)]

    def parent(self, i: int):
        return (int)((i - 1) / 2)

    def left(self, i: int):
        return 2 * i + 1

    def right(self, i: int):
        return 2 * i + 2

    # 특정 이름(key)을 가진 정점의 index(위치) 찾기
    def idxHeap(self, name: int):
        for i in range(self.heap_size):
            if self.harr[i].name == name:
                return i
        return -1

    def minHeapify(self, i: int):
        l = self.left(i)
        r = self.right(i)
        smallest = i

        if l < self.heap_size and self.harr[l].key < self.harr[i].key:
            smallest = l
        if r < self.heap_size and self.harr[r].key < self.harr[smallest].key:
            smallest = r
        
        if smallest != i:
            tmp = self.harr[i]
            self.harr[i] = self.harr[smallest]
            self.harr[smallest] = tmp
            self.minHeapify(smallest)

    def minHeapMinimum(self):
        if self.heap_size < 1:
            print("Error: Heap underflow")
            return sys.maxsize
        return self.harr[0].name

    def minHeapExtractMin(self):
        #힙에서 가장 작은 키 값을 가진 노드의 이름 가져오기
        minVal = self.minHeapMinimum()

        #루트 노드를 마지막 노드로 대체(공간을 줄여야 하니)
        self.harr[0] = self.harr[self.heap_size - 1]
        self.heap_size -= 1

        #힙 속성을 유지하기 위해 루트노드에서부터 재정렬
        self.minHeapify(0)
        return minVal



    #주어진 정점의 키 값을 새로운 키 값으로 줄이기
    def minHeapDecreaseKey(self, i: int, key: int):
        if key > self.harr[i].key:
            print("Error: New key is smaller than the current key")
            return
        self.harr[i].key = key
        
        #현재 노드를 부모 노드와 비교하며 힙 속성 유지
        while (i > 0) and (self.harr[self.parent(i)].key > self.harr[i].key):
            tmp = self.harr[i]
            self.harr[i] = self.harr[self.parent(i)]
            self.harr[self.parent(i)] = tmp

            #인덱스를 부모 노드로 업데이트
            i = self.parent(i)


    # 새로운 요소 힙에 삽입
    def minHeapInsert(self, x):
        if self.heap_size == self.capacity:
            print("Error: Heap overflow")
            return
        
        # 힙 크기 증가
        self.heap_size += 1
        i = self.heap_size - 1
        self.harr[i] = x

        # 삽입한 요소의 키 값을 삽입할 요소로 업데이트
        self.minHeapDecreaseKey(i, x.key)


        # k = x.key
        # x.key = sys.maxsize

        # self.harr[self.heap_size - 1] = x
        # i = self.idxHeap(x.name)
        # self.minHeapDecreaseKey(i, k)


def MSTPrim(graph, r: int):
    #시작 정점의 키 값을 0으로 업데이트
    graph.vertices[r].key = 0
    Q = Heap(20)

    # 모든 정점을 힙에 삽입
    for i in range(len(graph.vertices)):
        Q.minHeapInsert(graph.vertices[i])
    
    # 힙이 비어있지 않은 동안 반복
    while Q.heap_size != 0:
        # 키 값이 가장 작은 정점을 힙에서 제거
        u = Q.minHeapExtractMin()

        #제거된 정점과 인접한 모든 정점 탐색
        for v in graph.vertices[u].adj:
            #정점이 힙에 있고, 새 경로의 비용이 현재 키 값보다 작으면 키 값을 갱신
            if Q.idxHeap(v) != -1 and graph.weights[u][v] < graph.vertices[v].key:
                graph.vertices[v].pi = u
                graph.vertices[v].key = graph.weights[u][v]
                Q.minHeapDecreaseKey(Q.idxHeap(v), graph.weights[u][v])
                
# def tree_to_array(graph):
#     result = []
#     def dfs(u):
#         result.append(u)
#         for v in graph.vertices[u].adj:
#             if v != graph.vertices[u].pi:
#                 dfs(v)
#     dfs(0)
#     return result

def tree_to_array(graph):
    result = []
    visited = [False] * len(graph.vertices)
    
    def dfs(u):
        visited[u] = True
        result.append(u)
        for v in graph.vertices[u].adj:
            if graph.vertices[v].pi == u and not visited[v]:
                dfs(v)
            elif graph.vertices[u].pi == v and not visited[v]:
                dfs(v)
    
    dfs(0)  # Start DFS from the root of MST (vertex 0)
    return result


def edges_to_array(graph):
    mst_edges = []
    for i in range(len(graph.vertices)):
        if graph.vertices[i].pi != -1:
            mst_edges.append((graph.vertices[i].pi, i, graph.weights[graph.vertices[i].pi][i]))
    return mst_edges
# MST as array: [(0, 1, 4), (5, 2, 4), (2, 3, 7), (3, 4, 9), (6, 5, 2), (7, 6, 1), (0, 7, 8), (2, 8, 2)]



def main():
    # [#14] p.28 graphe example
    numVertex = 9
    initialWeights = [
        [0, 4, sys.maxsize, sys.maxsize, sys.maxsize, sys.maxsize, sys.maxsize, 8, sys.maxsize],
        [4, 0, 8, sys.maxsize, sys.maxsize, sys.maxsize, sys.maxsize, 11, sys.maxsize],
        [sys.maxsize, 8, 0, 7, sys.maxsize, 4, sys.maxsize, sys.maxsize, 2],
        [sys.maxsize, sys.maxsize, 7, 0, 9, 14, sys.maxsize, sys.maxsize, sys.maxsize],
        [sys.maxsize, sys.maxsize, sys.maxsize, 9, 0, 10, sys.maxsize, sys.maxsize, sys.maxsize],
        [sys.maxsize, sys.maxsize, 4, 14, 10, 0, 2, sys.maxsize, sys.maxsize],
        [sys.maxsize, sys.maxsize, sys.maxsize, sys.maxsize, sys.maxsize, 2, 0, 1, 6],
        [8, 11, sys.maxsize, sys.maxsize, sys.maxsize, sys.maxsize, 1, 0, 7],
        [sys.maxsize, sys.maxsize, 2, sys.maxsize, sys.maxsize, sys.maxsize, 6, 7, 0]
    ]

    graph = Graph(numVertex, initialWeights)

    MSTPrim(graph, 0)

    totalWeight = 0
    # for i in range(numVertex):
    #     if graph.vertices[i].pi != -1:
    #         # Edge from 'vertices[i].pi -> i' in the MST
    #         print("Edge:", graph.vertices[i].pi, "-", i, ", Weight:", graph.weights[graph.vertices[i].pi][i])
    #         totalWeight += graph.weights[graph.vertices[i].pi][i]
    # print("Total Weight of MST:", totalWeight)

    for i in range(numVertex):
        if graph.vertices[i].pi != -1:
            print("Edge:", graph.vertices[i].pi, "-", i, ", Weight:", graph.weights[graph.vertices[i].pi][i])
        totalWeight += graph.vertices[i].key
    print("Total Weight of MST: ", totalWeight)

     # Convert the MST to an array
    mst_array = tree_to_array(graph)
    print("MST as array:", mst_array)


if __name__ == '__main__':
    main()