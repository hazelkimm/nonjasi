# Graph 클래스: Graph 클래스는 정점의 개수와 인접 리스트를 사용하여 그래프를 나타냅니다.
# add_edge: 그래프에 간선을 추가합니다.
# dfs: 깊이 우선 탐색(DFS)을 구현합니다.
# bfs: 너비 우선 탐색(BFS)을 구현합니다.
# find_paths: 백트래킹을 이용하여 특정 경로를 찾습니다.
# level_order_traversal: 레벨 순서 탐색을 수행합니다.
# has_cycle: 그래프에 사이클이 있는지 확인합니다.
# topological_sort: 위상 정렬을 수행합니다.
# connected_components: 연결된 구성 요소를 찾습니다.
# dijkstra: 다익스트라 알고리즘을 이용하여 최단 경로를 찾습니다.
# prim_mst: 프림 알고리즘을 사용하여 최소 신장 트리를 찾습니다.
# floyd_warshall: 플로이드-워셜 알고리즘을 이용하여 모든 쌍 간의 최단 경로를 찾습니다.
# bellman_ford: 벨만-포드 알고리즘을 사용하여 단일 출발점에서의 최단 경로를 찾습니다.
# find_articulation_points: 단절점을 찾습니다.
# find_bridges: 브리지를 찾습니다.
# Eulerian Path and Circuit : 오일러 경로는 그래프의 모든 간선을 한 번씩만 통과하는 경로이고, 오일러 회로는 그런 경로 중 시작점과 끝점이 같은 경우입니다.
# Hamiltonian Path and Circuit : 해밀턴 경로는 그래프의 모든 정점을 한 번씩만 방문하는 경로이고, 해밀턴 회로는 그런 경로 중 시작점과 끝점이 같은 경우입니다.
# Coloring: 그래프 색칠하기는 인접한 정점들이 같은 색이 되지 않도록 최소한의 색을 사용해 그래프를 색칠하는 문제
# Shortest Path in Unweighted Graph: BFS를 사용하여 무가중치 그래프에서 출발점에서 다른 모든 정점까지의 최단 경로를 찾습니다.


class Graph:
    def __init__(self, num_vertices):
        self.graph = [[] for _ in range(num_vertices)]
        self.num_vertices = num_vertices
    
    # 무방향 그래프일 경우
    def add_edge(self, u, v, weight=1):
        self.graph[u].append((v, weight))
        self.graph[v].append((u, weight))  # 무방향 그래프인 경우

    def dfs(self, start):
        visited = [False] * self.num_vertices
        result = []
        self._dfs_util(start, visited, result)
        return result

    def _dfs_util(self, v, visited, result):
        visited[v] = True
        result.append(v)
        for neighbor, _ in self.graph[v]:
            if not visited[neighbor]:
                self._dfs_util(neighbor, visited, result)

    def find_paths(self, start, end):
        visited = [False] * self.num_vertices
        path = []
        all_paths = []
        self._backtrack(start, end, visited, path, all_paths)
        return all_paths

    def _backtrack(self, current, end, visited, path, all_paths):
        visited[current] = True
        path.append(current)

        if current == end:
            all_paths.append(list(path))
        else:
            for neighbor, _ in self.graph[current]:
                if not visited[neighbor]:
                    self._backtrack(neighbor, end, visited, path, all_paths)

        path.pop()
        visited[current] = False

    def bfs(self, start):
        visited = [False] * self.num_vertices
        queue = []
        result = []

        queue.append(start)
        visited[start] = True

        while queue:
            v = queue.pop(0)
            result.append(v)

            for neighbor, _ in self.graph[v]:
                if not visited[neighbor]:
                    queue.append(neighbor)
                    visited[neighbor] = True

        return result
    
    def level_order_traversal(self, start):
        visited = [False] * self.num_vertices
        queue = []
        result = []

        queue.append((start, 0))  # (노드, 레벨)
        visited[start] = True

        while queue:
            v, level = queue.pop(0)
            if len(result) <= level:
                result.append([])
            result[level].append(v)

            for neighbor, _ in self.graph[v]:
                if not visited[neighbor]:
                    queue.append((neighbor, level + 1))
                    visited[neighbor] = True

        return result

    def has_cycle(self):
        visited = [False] * self.num_vertices
        for v in range(self.num_vertices):
            if not visited[v]:
                if self._has_cycle_util(v, visited, -1):
                    return True
        return False

    def _has_cycle_util(self, v, visited, parent):
        visited[v] = True
        for neighbor, _ in self.graph[v]:
            if not visited[neighbor]:
                if self._has_cycle_util(neighbor, visited, v):
                    return True
            elif parent != neighbor:
                return True
        return False
    
    def topological_sort(self):
        visited = [False] * self.num_vertices
        stack = []

        for i in range(self.num_vertices):
            if not visited[i]:
                self._topological_sort_util(i, visited, stack)

        return stack[::-1]

    def _topological_sort_util(self, v, visited, stack):
        visited[v] = True

        for neighbor, _ in self.graph[v]:
            if not visited[neighbor]:
                self._topological_sort_util(neighbor, visited, stack)

        stack.append(v)
    
    def connected_components(self):
        visited = [False] * self.num_vertices
        components = []

        for v in range(self.num_vertices):
            if not visited[v]:
                component = []
                self._dfs_util(v, visited, component)
                components.append(component)

        return components

    def dijkstra(self, start):
        distances = [float('inf')] * self.num_vertices
        distances[start] = 0
        priority_queue = [(start, 0)]

        while priority_queue:
            current_vertex, current_distance = priority_queue.pop(0)

            if current_distance > distances[current_vertex]:
                continue

            for neighbor, weight in self.graph[current_vertex]:
                distance = current_distance + weight
                if distance < distances[neighbor]:
                    distances[neighbor] = distance
                    priority_queue.append((neighbor, distance))
                    priority_queue.sort(key=lambda x: x[1])  # 우선순위 큐를 정렬

        return distances

    def prim_mst(self):
        key = [float('inf')] * self.num_vertices
        parent = [-1] * self.num_vertices
        key[0] = 0
        mst_set = [False] * self.num_vertices

        for _ in range(self.num_vertices):
            u = self._min_key(key, mst_set)
            mst_set[u] = True

            for neighbor, weight in self.graph[u]:
                if not mst_set[neighbor] and weight < key[neighbor]:
                    key[neighbor] = weight
                    parent[neighbor] = u

        return parent

    def _min_key(self, key, mst_set):
        min_val = float('inf')
        min_index = -1

        for v in range(self.num_vertices):
            if key[v] < min_val and not mst_set[v]:
                min_val = key[v]
                min_index = v

        return min_index

    def floyd_warshall(self):
        dist = [[float('inf')] * self.num_vertices for _ in range(self.num_vertices)]
        
        for u in range(self.num_vertices):
            dist[u][u] = 0
            for v, w in self.graph[u]:
                dist[u][v] = w
        
        for k in range(self.num_vertices):
            for i in range(self.num_vertices):
                for j in range(self.num_vertices):
                    if dist[i][j] > dist[i][k] + dist[k][j]:
                        dist[i][j] = dist[i][k] + dist[k][j]
        
        return dist

    def bellman_ford(self, start):
        distances = [float('inf')] * self.num_vertices
        distances[start] = 0

        for _ in range(self.num_vertices - 1):
            for u in range(self.num_vertices):
                for v, weight in self.graph[u]:
                    if distances[u] != float('inf') and distances[u] + weight < distances[v]:
                        distances[v] = distances[u] + weight

        for u in range(self.num_vertices):
            for v, weight in self.graph[u]:
                if distances[u] != float('inf') and distances[u] + weight < distances[v]:
                    print("Graph contains negative weight cycle")
                    return None

        return distances
    
    def find_articulation_points(self):
        visited = [False] * self.num_vertices
        disc = [float('inf')] * self.num_vertices
        low = [float('inf')] * self.num_vertices
        parent = [-1] * self.num_vertices
        articulation_points = set()

        for i in range(self.num_vertices):
            if not visited[i]:
                self._articulation_point_dfs(i, visited, disc, low, parent, articulation_points)

        return list(articulation_points)

    def _articulation_point_dfs(self, u, visited, disc, low, parent, ap):
        static_time = [0]
        visited[u] = True
        disc[u] = low[u] = static_time[0]
        static_time[0] += 1
        children = 0

        for v, _ in self.graph[u]:
            if not visited[v]:
                parent[v] = u
                children += 1
                self._articulation_point_dfs(v, visited, disc, low, parent, ap)
                low[u] = min(low[u], low[v])

                if parent[u] == -1 and children > 1:
                    ap.add(u)

                if parent[u] != -1 and low[v] >= disc[u]:
                    ap.add(u)

            elif v != parent[u]:
                low[u] = min(low[u], disc[v])
    
    def find_bridges(self):
        visited = [False] * self.num_vertices
        disc = [float('inf')] * self.num_vertices
        low = [float('inf')] * self.num_vertices
        parent = [-1] * self.num_vertices
        bridges = []

        for i in range(self.num_vertices):
            if not visited[i]:
                self._bridge_dfs(i, visited, disc, low, parent, bridges)

        return bridges

    def _bridge_dfs(self, u, visited, disc, low, parent, bridges):
        static_time = [0]
        visited[u] = True
        disc[u] = low[u] = static_time[0]
        static_time[0] += 1

        for v, _ in self.graph[u]:
            if not visited[v]:
                parent[v] = u
                self._bridge_dfs(v, visited, disc, low, parent, bridges)
                low[u] = min(low[u], low[v])

                if low[v] > disc[u]:
                    bridges.append((u, v))

            elif v != parent[u]:
                low[u] = min(low[u], disc[v])
                
                
                
    def is_eulerian(self):
        # 모든 정점의 차수를 계산
        odd_degree_count = 0
        for vertex in range(self.num_vertices):
            if len(self.graph[vertex]) % 2 != 0:
                odd_degree_count += 1

        if odd_degree_count == 0:
            return "Eulerian Circuit"
        elif odd_degree_count == 2:
            return "Eulerian Path"
        else:
            return "Not Eulerian"


    def hamiltonian_path(self):
        path = []
        visited = [False] * self.num_vertices
        if self._hamiltonian_util(0, path, visited):
            return path
        return None

    def _hamiltonian_util(self, vertex, path, visited):
        visited[vertex] = True
        path.append(vertex)

        if len(path) == self.num_vertices:
            return True

        for neighbor, _ in self.graph[vertex]:
            if not visited[neighbor]:
                if self._hamiltonian_util(neighbor, path, visited):
                    return True

        visited[vertex] = False
        path.pop()
        return False
