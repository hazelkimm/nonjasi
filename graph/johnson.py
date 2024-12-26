class Edge:
    def __init__(self, src, dst, weight):
        self.src = src
        self.dst = dst
        self.weight = weight

UNKNOWN = float('inf')

def has_negative_cycle(edges, distance):
    for e in edges:
        if distance[e.src] == UNKNOWN:
            continue
        if distance[e.src] + e.weight < distance[e.dst]:
            return True
    return False

def bellman_ford(edges, V):
    distance = [UNKNOWN] * (V + 1)

    # 더미 정점 s 추가 후 모든 정점에서 s로 가는 edge 0 추가
    s = V
    for i in range(V):
        edges.append(Edge(s, i, 0))
    distance[s] = 0

    # 정점 개수가 V+1개이므로 V번 반복
    for i in range(V):
        for e in edges:
            # edge의 시작 정점의 거리 값이 unknown이면 스킵
            if distance[e.src] == UNKNOWN:
                continue

            # 인접한 정점의 거리 값이 새로운 경로에 의한 거리값보다 크면 거리 값 업데이트
            if distance[e.dst] > distance[e.src] + e.weight:
                distance[e.dst] = distance[e.src] + e.weight

    # 음수 사이클이 존재하면 종료
    if has_negative_cycle(edges, distance):
        print("Negative Cycle exists")
        return []

    # 각 정점의 최단거리 반환
    return distance

def get_min_distance(distance, visited):
    min_distance = UNKNOWN
    min_index = -1

    for i in range(len(distance)):
        if not visited[i] and distance[i] <= min_distance:
            min_distance = distance[i]
            min_index = i

    # 가장 작은 거리를 가진 정점의 인덱스 반환. 다음에 방문할 정점이 됨!
    return min_index

def dijkstra(edges, V, start):
    distance = [UNKNOWN] * V
    visited = [False] * V

    distance[start] = 0

    for _ in range(V - 1):
        # 방문하지 않은 정점 중에서 최소 거리 정점 찾기
        curr = get_min_distance(distance, visited)

        visited[curr] = True

        for e in edges:
            # 간선의 출발 정점이 현재 정점이 아니면 무시
            if e.src != curr:
                continue

            # 이미 방문했으면 무시
            if visited[e.dst]:
                continue

            if distance[curr] != UNKNOWN and distance[e.dst] > distance[curr] + e.weight:
                distance[e.dst] = distance[curr] + e.weight

    return distance

def johnson(edges, V):
    # 더미 정점을 기준으로 각 정점까지의 잠재치 h 계산
    h = bellman_ford(edges, V)

    if not h:
        return

    # edge의 가중치 재설정
    for e in edges:
        e.weight += (h[e.src] - h[e.dst])

    # 모든 정점들 사이의 최단 거리 저장
    shortest = []

    for i in range(V):
        shortest.append(dijkstra(edges, V, i))

    # 가중치 변환 수식을 역으로 적용하여 최단 거리 출력
    for i in range(V):
        print(f"{i}:")
        for j in range(V):
            if shortest[i][j] != UNKNOWN:
                shortest[i][j] += h[j] - h[i]
                print(f"\t{j}: {shortest[i][j]}")

def main():
    V = 5
    edges = []

    edge_map = [
        [0, 1, -7],
        [1, 2, -2],
        [2, 0, 10],
        [0, 3, -5],
        [0, 4, 2],
        [3, 4, 4]
    ]

    for e in edge_map:
        edges.append(Edge(e[0], e[1], e[2]))

    johnson(edges, V)

if __name__ == "__main__":
    main()
