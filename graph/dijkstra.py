import sys

class Data:
    node = 0
    weight = 0

    def __init__(self, node=0, weight=0):
        self.node = node
        self.weight = weight


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

    def idxHeap(self, node: int):
        for i in range(self.heap_size):
            if self.harr[i].node == node:
                return i
        return -1

    def minHeapify(self, i: int):
        l = self.left(i)
        r = self.right(i)
        smallest = i

        if l < self.heap_size and self.harr[l].weight < self.harr[i].weight:
            smallest = l
        if r < self.heap_size and self.harr[r].weight < self.harr[smallest].weight:
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
        return self.harr[0]

    def minHeapExtractMin(self):
        minVal = self.minHeapMinimum()
        self.harr[0] = self.harr[self.heap_size - 1]
        self.heap_size -= 1
        self.minHeapify(0)
        return minVal

    def minHeapDecreaseKey(self, i: int, weight: int):
        if weight > self.harr[i].weight:
            print("Error: New key is smaller than the current key")
            return
        self.harr[i].weight = weight
        while (i > 0) and (self.harr[self.parent(i)].weight > self.harr[i].weight):
            tmp = self.harr[i]
            self.harr[i] = self.harr[self.parent(i)]
            self.harr[self.parent(i)] = tmp
            i = self.parent(i)

    def minHeapInsert(self, x):
        if self.heap_size == self.capacity:
            print("Error: Heap overflow")
            return
        self.heap_size += 1
        k = x.weight
        x.weight = sys.maxsize

        self.harr[self.heap_size - 1] = x
        i = self.idxHeap(x.node)
        self.minHeapDecreaseKey(i, k)

def Dijkstra(v, Dijk, pq: Heap):
    while pq.heap_size != 0:
        # priority queue의 맨 앞 노드 가져오기
        nowNode = pq.minHeapExtractMin()

        node = nowNode.node
        weightSum = nowNode.weight

        # 이미 이전에 더 적은 가중치로 Dijk[node]를 갱신함
        if Dijk[node] < weightSum:
            continue
        
        # nowNode와 연결되어 있는 다른 모든 노드 탐색
        for i in range(len(v[node])):
            nextNode = v[node][i].node
            weight = v[node][i].weight

            # (다음 노드에 저장된 값 > 다음 노드로 방문하면서 소비할 가중치의 합) 일 때만 값 갱신, 그리고 pq 삽입
            if Dijk[nextNode] > weight + weightSum:
                Dijk[nextNode] = weight + weightSum
                pq.minHeapInsert(Data(nextNode, Dijk[nextNode]))



def main():
    numNode = 5
    v = [[] for i in range(numNode+1)]  # v[x]: x번 노드에 연결된 다음 노드와 가중치의 정보
    Dijk = [sys.maxsize for i in range(numNode+1)]  # Dijk[x]: x번 노드까지의 최단경로 값

    pq = Heap(20)

    # Make Graph
    v[1].append(Data(2,8))
    v[1].append(Data(3,2))
    v[2].append(Data(1,8))
    v[2].append(Data(4,10))
    v[3].append(Data(1,2))
    v[3].append(Data(4,1))
    v[3].append(Data(5,7))
    v[4].append(Data(2,10))
    v[4].append(Data(5,9))
    v[5].append(Data(3,7))
    v[5].append(Data(4,9))
    
    # Initialize Queue
    start = 1
    pq.minHeapInsert(Data(start, 0))
    Dijk[start] = 0

    # Dijkstra Algorithm
    Dijkstra(v, Dijk, pq)

    for i in range(1, numNode+1):
        print(i, Dijk[i])

if __name__ == "__main__":
    main()






############### 혹은, library 활용하기
import heapq
import sys

class Data:
    def __init__(self, node=0, weight=0):
        self.node = node
        self.weight = weight

    # heapq가 사용하는 비교 연산을 위해 less-than 메서드를 정의합니다.
    def __lt__(self, other):
        return self.weight < other.weight

def Dijkstra(v, Dijk):
    pq = []
    heapq.heappush(pq, Data(1, 0))  # 시작 노드 추가
    Dijk[1] = 0

    while pq:
        nowNode = heapq.heappop(pq)  # 최소 가중치 노드 추출
        node = nowNode.node
        weightSum = nowNode.weight

        # 이미 처리된 노드라면 무시
        if Dijk[node] < weightSum:
            continue
        
        # nowNode와 연결된 다른 모든 노드 탐색
        for nextNodeData in v[node]:
            nextNode = nextNodeData.node
            weight = nextNodeData.weight

            # (다음 노드에 저장된 값 > 다음 노드로 방문하면서 소비할 가중치의 합)일 때만 값 갱신, 그리고 pq에 삽입
            if Dijk[nextNode] > weight + weightSum:
                Dijk[nextNode] = weight + weightSum
                heapq.heappush(pq, Data(nextNode, Dijk[nextNode]))

def main():
    numNode = 5
    v = [[] for _ in range(numNode + 1)]  # v[x]: x번 노드에 연결된 다음 노드와 가중치의 정보
    Dijk = [sys.maxsize for _ in range(numNode + 1)]  # Dijk[x]: x번 노드까지의 최단경로 값

    # 그래프 생성
    v[1].append(Data(2, 8))
    v[1].append(Data(3, 2))
    v[2].append(Data(1, 8))
    v[2].append(Data(4, 10))
    v[3].append(Data(1, 2))
    v[3].append(Data(4, 1))
    v[3].append(Data(5, 7))
    v[4].append(Data(2, 10))
    v[4].append(Data(5, 9))
    v[5].append(Data(3, 7))
    v[5].append(Data(4, 9))

    # Dijkstra 알고리즘 실행
    Dijkstra(v, Dijk)

    # 결과 출력
    for i in range(1, numNode + 1):
        print(f"Dijk[{i}] = {Dijk[i]}")

if __name__ == "__main__":
    main()
