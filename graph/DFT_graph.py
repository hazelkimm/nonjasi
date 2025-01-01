'''
__DFTHelp: 깊이 우선 탐색(DFS) 보조 함수, 방문하지 않은 노드를 탐색하고 출력합니다.
DFT_recursive: 시작 노드를 지정하여 깊이 우선 탐색을 재귀적으로 수행합니다.
DFT_stack: 시작 노드가 주어진 경우 스택을 사용한 DFS를 수행합니다.

are_connected: 두 노드가 연결되어 있는지 확인하는 함수입니다.
are_all_connected: 그래프의 모든 노드가 연결되어 있는지 확인합니다.
count_islands: 연결된 컴포넌트(섬)의 개수를 세는 함수입니다.
has_cycle: 그래프에 사이클이 있는지 확인하는 함수입니다.
cycle_detect: 사이클을 감지하는 함수입니다.

is_connected: 그래프가 연결되어 있는지 확인하는 함수입니다.
shortest_path_bfs: BFS를 사용하여 두 노드 사이의 최단 경로를 찾는 함수입니다.
topological_sort: 방향 그래프에서 위상 정렬을 수행하는 함수입니다.
find_connected_components: 그래프의 연결 요소를 찾는 함수입니다.

detect_cycle_undirected: 무방향 그래프에서 사이클을 감지하는 함수입니다.
detect_cycle_directed: 방향 그래프에서 사이클을 감지하는 함수입니다
'''
############ Vertex와 Edge가 주어진 경우 #################
class graph():
    def __init__(self, V:list, E:list) -> None:
        self.V = V[:]
        self.neighbor = {}
        for v in V:
            self.neighbor[v] = []
        for (v, w) in E:
            self.neighbor[v].append(w)
            # self.neighbor[w].append(v)   #directed라면 얘 제거
        self.count_island = 0

    # 만약 addEdge 형태라면
    # def __init__(self):
    #     self.neighbor = {}

    # def addVertex(self, v):
    #     if v not in self.neighbor:
    #         self.neighbor[v] = []

    # def addEdge(self, v, w):
    #     if v not in self.neighbor:
    #         self.addVertex(v)
    #     if w not in self.neighbor:
    #         self.addVertex(w)
    #     self.neighbor[v].append(w)
    #     self.neighbor[w].append(v)   #directed라면 얘 제거
        
    #preorder        
    def __DFTHelp(self, visited:list, v:int) ->None:
        if not visited[v]:
            visited[v] = True
            print(v, end = " ")

            for w in self.neighbor[v]:
                self.__DFTHelp(visited, w)
            
            ####### 얘 지워야할수도
            for w in self.V:
                if not visited[w]:
                    self.__DFTHelp(visited, w)



    
    # 시작 노드 지정 안할경우
    # def DFT(self) -> None:
    #     if self.V:
    #         visited = {}
    #         self.count_island = 0
    #         
    #         for v in self.V:
    #             visited[v] = False
    #
    #         for v in self.V:
    #             self.__DFTHelp(visited, v)
    #             self.count_island += 1



    # 시작 노드 지정해줄 경우
    def DFT_recursive(self, start_node: str) -> None:
        visited = {v: False for v in self.V}
        self.__DFTHelp(visited, start_node)
        self.count_island += 1
        print()


        
    # 스택을 사용한 DFS 구현 - 시작 노드 없는경우 (island 포함 모든 노드 출력)
    # def DFT_stack(self) -> None:
    #     visited = {v: False for v in self.V}
    #     stack = []
    #     self.count_island = 0

    #     for v in self.V:
    #         if not visited[v]:
    #             stack.append(v)

    #         while stack:
    #             v = stack.pop()
    #             if not visited[v]:
    #                 visited[v] = True
    #                 print(v, end=" ")

    #                 for w in reversed(self.neighbor[v]):        # 재귀함수와 같은 순서로 하기 위해
    #                     if not visited[w]:
    #                         stack.append(w)
            
    #         self.count_island += 1
    #     print()

    #스택을 사용한 DFS 구현 - 시작 노드가 주어진경우 (시작노드와 연결된 애들만 출력)
    def DFT_stack(self, start_node: int) -> None:
        visited = {v: False for v in self.V}  # 모든 노드를 미방문 상태로 초기화
        stack = [start_node]  # 시작 노드를 스택에 추가

        while stack:
            node = stack.pop()  # 스택의 최상단 노드를 꺼냄

            if not visited[node]:
                visited[node] = True  # 현재 노드를 방문 처리
                print(node, end=" ")  # 현재 노드를 출력

                # 인접 노드를 스택에 추가 (역순으로 추가하여 스택의 특성에 맞게 처리)
                for neighbor in reversed(self.neighbor[node]):
                    if not visited[neighbor]:
                        stack.append(neighbor)
        print()  # 탐색이 끝나면 줄바꿈



    def __DFTHelp2(self, visited:list, v:int) ->None:
        if not visited[v]:
            visited[v] = True
            # print(v, end = " ")
            for w in self.neighbor[v]:
                self.__DFTHelp2(visited, w)
            


    # 두 노드가 연결되어 있는지 확인
    def are_connected(self, start: int, end: int) -> bool:
        visited = {v: False for v in self.V}
        return self.__check_path(visited, start, end)
    


    def __check_path(self, visited, start, end) -> bool:
        if start == end:
            return True
        
        visited[start] = True

        for w in self.neighbor[start]:
            if not visited[w]:
                if self.__check_path(visited, w, end):
                    return True

        return False



    
    # 모든 노드가 연결되어 있는지 확인
    def are_all_connected(self) -> bool:
        if not self.V:  # 노드가 없는 경우
            return True

        visited = {v: False for v in self.V}
        self.__DFTHelp2(visited, self.V[0])  # 첫 번째 노드에서 시작하여 DFS 탐색

        return all(visited.values())  # 모든 노드가 방문되었는지 확인




    # 컴포넌트(섬)의 개수 세기
    def count_islands(self) -> int:
        visited = {v: False for v in self.V}
        island_count = 0

        for v in self.V:
            if not visited[v]:
                self.__DFTHelp2(visited, v)
                island_count += 1

        return island_count




    # 사이클 여부 확인
    def has_cycle(self) -> bool:
        visited = {v: False for v in self.V}
        rec_stack = {v: False for v in self.V}  #현재 재귀 호출이 진행중인 노드 추적

        for v in self.V:
            if not visited[v]:
                if self.__cycle_detect(v, visited, rec_stack):
                    return True
        return False


    def __cycle_detect(self, v, visited, rec_stack) -> bool:
        visited[v] = True
        rec_stack[v] = True

        for w in self.neighbor[v]:
            if not visited[w]:
                if self.__cycle_detect(w, visited, rec_stack):
                    return True
            elif rec_stack[w]:
                return True

        rec_stack[v] = False
      
    


if __name__ == "__main__":
    vertices = [1, 2, 3, 4, 5, 6, 7, 8]
    edges = [
    (1, 2), (1, 3),
    (2, 8),
    (3, 4), (3, 5),
    (4, 5),
    (6, 7), (6, 8),
    (7, 8)
    ]
    # 1 2 8 3 4 5 6 7


    # Create the graph
    graph = graph(vertices, edges)

    # Perform BFS starting from vertex 'A'
    print("DFT starting from vertex 1:")
    graph.DFT_recursive(1)

    # Perform DFS starting from vertex 1
    print("DFT using stack starting from vertex 1:")
    graph.DFT_stack(1)

    # Check if two nodes are connected
    print("Are 1 and 5 connected?", graph.are_connected(1, 5))
    print("Are 1 and 7 connected?", graph.are_connected(1, 7))

    # # Check if all nodes are connected
    print("Are all nodes connected?", graph.are_all_connected())

    # # Count the number of islands (connected components)
    print("Number of islands:", graph.count_islands())

    # Check if the graph has a cycle
    print("Does the graph have a cycle?", graph.has_cycle())









############### 그래프 자체로 주어졌을 경우 #################
### Undirected graph, Directed graph 모두 표현 가능 ###########
from collections import deque

def dfs_recursive(graph, node, visited):
    # 현재 노드를 방문 처리
    visited[node] = True
    print(node, end=' ')

    # 현재 노드와 연결된 다른 노드를 재귀적으로 방문
    for neighbor in graph[node]:     
        if not visited[neighbor]:
            dfs_recursive(graph, neighbor, visited)

    for node in range(1, len(graph)):  # 인덱스 1부터 시작
        if not visited[node]:
            dfs_recursive(graph, node, visited)


# 스택을 사용한 DFS 구현 - 시작 노드 없는경우 (island 포함 모든 노드 출력)
def DFT_stack(self) -> None:
    visited = [False] * len(graph)
    stack = []

    for v in range(1, len(graph)):  # 노드 1부터 시작 (0번 인덱스는 사용 안 함)
        if not visited[v]:
            stack.append(v)

        while stack:
            node = stack.pop()
            if not visited[node]:
                visited[node] = True
                print(node, end=" ")

                for neighbor in reversed(graph[node]):
                    if not visited[neighbor]:
                        stack.append(neighbor)
        
    print()


#스택을 사용한 DFS 구현 - 시작 노드가 주어진경우 (시작노드와 연결된 애들만 출력)
def dfs_stack(graph, start_node):
    visited = [False] * len(graph)
    stack = [start_node]
    
    while stack:
        node = stack.pop()
        
        if not visited[node]:
            visited[node] = True
            print(node, end=' ')
            
            for neighbor in reversed(graph[node]):
                if not visited[neighbor]:
                    stack.append(neighbor)
    print()



def dfs_recursive2(graph, node, visited):
    # 현재 노드를 방문 처리
    visited[node] = True

    # 현재 노드와 연결된 다른 노드를 재귀적으로 방문
    for neighbor in graph[node]:     
        if not visited[neighbor]:
            dfs_recursive2(graph, neighbor, visited)

 

# Check Connectivity (Are all nodes connected?)
def are_all_connected(graph):
    visited = [False] * len(graph)
    dfs_recursive2(graph, 1, visited)  # 노드 1부터 시작하여 DFS 수행
    
    # 모든 노드가 방문되었는지 확인
    return all(visited[1:])  # 노드 0은 사용하지 않으므로 [1:]부터 확인



# Count the Number of Islands (Connected Components)
def count_islands(graph):
    visited = [False] * len(graph)
    island_count = 0
    
    for node in range(1, len(graph)):
        if not visited[node]:
            dfs_recursive2(graph, node, visited)
            island_count += 1
    
    return island_count

# Check for Cycle in Undirected Graph
def has_cycle(graph):
    def cycle_detect(node, visited, rec_stack):
        visited[node] = True
        rec_stack[node] = True
        
        for neighbor in graph[node]:
            if not visited[neighbor]:
                if cycle_detect(neighbor, visited, rec_stack):
                    return True
            elif rec_stack[neighbor]:
                return True
        
        rec_stack[node] = False
        return False
    
    visited = [False] * len(graph)
    rec_stack = [False] * len(graph)  # 현재 탐색 중인 노드를 추적하기 위한 스택

    for node in range(1, len(graph)):
        if not visited[node]:
            if cycle_detect(node, visited, rec_stack):
                return True
    return False



#Directed
# graph = [
#     [],
#     [2,3],
#     [8],
#     [4,5],
#     [5],
#     [],
#     [7,8],
#     [8],
#     []
# ]
# 1 2 8 3 4 5 6 7

#Undirected
graph = [
    [],
    [2, 3],
    [1, 8],
    [1, 4, 5],
    [3, 5],
    [3, 4],
    [7,8],
    [6,8],
    [2,6,7]
]
# 1 2 8 3 4 5 6 7
visited = [False]*9

# DFS Recursive로 모든 컴포넌트 탐색 및 출력
print("DFS (Recursive) for all islands:")
dfs_recursive(graph, 1, visited)
print()

# DFS using Stack으로 모든 컴포넌트 탐색 및 출력
print("DFS (Stack) for all islands:")
DFT_stack(graph)
print("DFS (Stack) for connected islands: ")
dfs_stack(graph, 1)

# 그래프가 모든 노드가 연결되어 있는지 확인
print("Are all nodes connected?", are_all_connected(graph))

# 섬의 개수(연결된 컴포넌트 수) 계산
print("Number of islands:", count_islands(graph))

# 그래프에 사이클이 있는지 확인
print("Does the graph have a cycle?", has_cycle(graph))






####################### grid로 주어질경우 ###########
from collections import deque

def count_islands_from_graph(graph):
    visited = set()
    num_islands = 0

    def dfs(node):
        stack = [node]
        while stack:
            current = stack.pop()
            if current not in visited:
                visited.add(current)
                for neighbor in graph[current]:
                    if neighbor not in visited:
                        stack.append(neighbor)

    for node in graph:
        if node not in visited:
            dfs(node)  # 새로운 섬 발견 -> DFS 수행
            num_islands += 1

    return num_islands


def count_islands(grid):
    """
    2D 그리드에서 섬(연결된 1의 집합)의 개수를 세는 함수.
    :param grid: 2D 리스트 (0과 1로 구성)
    :return: 섬의 개수 (int)
    """
    def bfs(x, y):
        queue = deque([(x, y)])
        visited[x][y] = True
        while queue:
            cx, cy = queue.popleft()
            for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nx, ny = cx + dx, cy + dy
                if 0 <= nx < len(grid) and 0 <= ny < len(grid[0]) and not visited[nx][ny] and grid[nx][ny] == 1:
                    visited[nx][ny] = True
                    queue.append((nx, ny))

    if not grid:
        return 0

    visited = [[False for _ in range(len(grid[0]))] for _ in range(len(grid))]
    islands = 0

    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == 1 and not visited[i][j]:
                bfs(i, j)
                islands += 1

    return islands


def is_connected(graph):
    """
    그래프가 연결되어 있는지 확인하는 함수.
    :param graph: 인접 리스트로 표현된 그래프 (dict 형태)
    :return: 연결 여부 (True/False)
    """
    def dfs(node):
        visited.add(node)
        for neighbor in graph[node]:
            if neighbor not in visited:
                dfs(neighbor)

    if not graph:
        return True  # 빈 그래프는 연결되어 있다고 간주

    visited = set()
    start_node = next(iter(graph))
    dfs(start_node)

    return len(visited) == len(graph)


def shortest_path_bfs(graph, start, end):
    """
    BFS를 이용해 두 노드 사이의 최단 경로를 찾는 함수.
    :param graph: 인접 리스트로 표현된 그래프
    :param start: 시작 노드
    :param end: 끝 노드
    :return: 최단 경로 길이 (없으면 -1)
    """
    queue = deque([(start, 0)])
    visited = set([start])

    while queue:
        current, distance = queue.popleft()
        if current == end:
            return distance
        for neighbor in graph[current]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append((neighbor, distance + 1))

    return -1  # 경로가 없는 경우


def topological_sort(graph):
    """
    위상 정렬을 수행하는 함수.
    :param graph: 방향성 있는 비순환 그래프 (DAG) 인접 리스트
    :return: 위상 정렬 순서 (리스트)
    """
    in_degree = {node: 0 for node in graph}
    for neighbors in graph.values():
        for neighbor in neighbors:
            in_degree[neighbor] += 1

    queue = deque([node for node in graph if in_degree[node] == 0])
    topo_order = []

    while queue:
        current = queue.popleft()
        topo_order.append(current)
        for neighbor in graph[current]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    if len(topo_order) == len(graph):
        return topo_order
    else:
        return []  # 그래프에 사이클이 있는 경우



def dfs_recursive(graph, start, visited=None):
    """
    DFS(깊이 우선 탐색)를 재귀적으로 구현한 함수.
    :param graph: 인접 리스트
    :param start: 탐색 시작 노드
    :param visited: 방문 여부를 저장하는 집합
    :return: 방문 순서 리스트
    """
    if visited is None:
        visited = set()
    visited.add(start)
    result = [start]
    for neighbor in graph[start]:
        if neighbor not in visited:
            result.extend(dfs_recursive(graph, neighbor, visited))
    return result


def bfs(graph, start):
    """
    BFS(너비 우선 탐색)를 구현한 함수.
    :param graph: 인접 리스트
    :param start: 탐색 시작 노드
    :return: 방문 순서 리스트
    """
    visited = set()
    queue = deque([start])
    visited.add(start)
    result = []

    while queue:
        node = queue.popleft()
        result.append(node)
        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)

    return result

### 그래프 유틸리티

def find_connected_components(graph):
    """
    그래프의 연결 요소(connected components)를 찾는 함수.
    :param graph: 인접 리스트
    :return: 연결 요소 리스트
    """
    visited = set()
    components = []

    def dfs(node):
        component = []
        stack = [node]
        while stack:
            current = stack.pop()
            if current not in visited:
                visited.add(current)
                component.append(current)
                stack.extend(graph[current])
        return component

    for node in graph:
        if node not in visited:
            components.append(dfs(node))
    return components


def detect_cycle_undirected(graph):
    """
    무방향 그래프에서 사이클을 감지하는 함수.
    :param graph: 인접 리스트
    :return: 사이클 존재 여부 (True/False)
    """
    visited = set()

    def dfs(node, parent):
        visited.add(node)
        for neighbor in graph[node]:
            if neighbor not in visited:
                if dfs(neighbor, node):
                    return True
            elif neighbor != parent:
                return True
        return False

    for node in graph:
        if node not in visited:
            if dfs(node, None):
                return True
    return False


def detect_cycle_directed(graph):
    """
    방향 그래프에서 사이클을 감지하는 함수.
    :param graph: 인접 리스트
    :return: 사이클 존재 여부 (True/False)
    """
    visited = set()
    stack = set()

    def dfs(node):
        visited.add(node)
        stack.add(node)
        for neighbor in graph[node]:
            if neighbor not in visited:
                if dfs(neighbor):
                    return True
            elif neighbor in stack:
                return True
        stack.remove(node)
        return False

    for node in graph:
        if node not in visited:
            if dfs(node):
                return True
    return False

# 사용 예시:
grid = [
    [1, 1, 0, 0],
    [1, 0, 0, 1],
    [0, 0, 1, 1],
    [0, 0, 0, 0]
]
print("Number of islands:", count_islands(grid))  # Output: 3


# from typing import List

# def is_safe(M: List[List[str]], r: int, c: int, Row: int, Col: int):
#     return (0 <= r < Row) and (0 <= c < Col) and (M[r][c] == '1')


# def convert_matrix_to_graph(M: List[List[str]]) -> List[List[int]]:
#     n_row = len(M)
#     n_col = len(M[0])
#     adj = [[] for _ in range(n_row * n_col)]

#     directions = [[-1, -1], [-1, 0], [-1, 1],
#                   [0, -1],          [ 0, 1],
#                   [1, -1],  [1, 0], [1, 1]]
    
#     for r in range(n_row):
#         for c in range(n_col):
#             if M[r][c] == '1':
#                 idx = r * n_col + c
#                 adj[idx].append(idx)
#                 for dr, dc in directions:
#                     nr = r + dr
#                     nc = c + dc
#                     if is_safe(M, nr, nc, n_row, n_col):
#                         n_idx = nr * n_col + nc
#                         adj[idx].append(n_idx)
#     return adj


# ## count_island함수임 사실상!
# def dfs(adj: list[list[int]]) -> int:
#     cnt = 0
    
#     n = len(adj)
#     visited = [False] * n

#     def dfs_util(v: int):
#         visited[v] = True
#         for neighbor in adj[v]:
#             if not visited[neighbor]:
#                 dfs_util(neighbor)
    
#     for i in range(n):
#         if not visited[i] and len(adj[i]):
#             dfs_util(i)
#             cnt += 1
    
#     return cnt


# def count_islands(M: List[List[str]]) -> int:
#     adj = convert_matrix_to_graph(M)
#     print(adj)
#     return dfs(adj)

'''
adj: [[0, 1, 6], [1, 0, 6], [], [], [], [], [6, 0, 1, 10], [], [], [9, 13, 14], [10, 6], [], [], [13, 9, 14], [14, 9, 13], [], [], [], [], [], [20], [], [22, 23], [23, 22], []]
'''

if __name__ == "__main__":
    # Example Usage (Same as previous)
    M = [['1', '1', '0', '0', '0'],
         ['0', '1', '0', '0', '1'],
         ['1', '0', '0', '1', '1'],
         ['0', '0', '0', '0', '0'],
         ['1', '0', '1', '1', '0']]
    print("Number of Islands in M using BFS:", count_islands(M))
    # Expected Output: 4

    # Other test cases can be reused from the previous example


graph = {
    0: [1, 2],
    1: [2],
    2: [3],
    3: []
}
print("Is graph connected?", is_connected(graph))  # Output: False
print("Shortest path from 0 to 3:", shortest_path_bfs(graph, 0, 3))  # Output: 2
print("Topological order:", topological_sort(graph))  # Output: [0, 1, 2, 3]
