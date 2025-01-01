# undi_graph 클래스:
#  - Undirected Graph (무방향 그래프)을 표현하는 클래스.
#  - add_edge: 그래프에 간선을 추가하는 함수.
#  - BFS: 주어진 root에서 시작하여 BFS 탐색을 수행하는 함수.
#  - bfs_shortest_path: BFS로 최단 경로를 찾는 함수.
#  - are_all_connected: 모든 노드가 연결되어 있는지 확인하는 함수.
#  - count_islands: 그래프에서 연결되지 않은 부분(섬)의 개수를 세는 함수.
#  - cycle_detection: 그래프에 사이클이 존재하는지 탐지하는 함수.

# dir_graph 클래스:
#  - Directed Graph (방향 그래프)을 표현하는 클래스.
#  - BFS: 주어진 root에서 시작하여 BFS 탐색을 수행하는 함수.
#  - bfs_shortest_path: BFS로 최단 경로를 찾는 함수.
#  - are_all_connected: 모든 노드가 연결되어 있는지 확인하는 함수.
#  - count_islands: 그래프에서 연결되지 않은 부분(섬)의 개수를 세는 함수.
#  - cycle_detection: 그래프에 사이클이 존재하는지 탐지하는 함수.


############ Vertex와 Edge가 주어진 경우 #################
##### Undirected Graph #########
from collections import deque

class undi_graph():
    def __init__(self, V:list, E:list) -> None:
        self.V = V[:]
        self.neighbor = {}
        for v in V:
            self.neighbor[v] = []
        for (v, w) in E:
            self.neighbor[v].append(w)
            self.neighbor[w].append(v)   # For undirected graph

    ### add edge형식인경우 앞부분만 밑처럼 바꾸기
    # graph.add_edge(0, 1)
    # graph.add_edge(0, 2)
    # graph.add_edge(1, 3)
    # graph.add_edge(2, 3)
    # graph.add_edge(3, 4)

# class UndiGraph:
#     def __init__(self, V):
#         self.V = V
#         self.neighbor = {v: [] for v in V}

#     def add_edge(self, v, w):
#         self.neighbor[v].append(w)
#         self.neighbor[w].append(v)  # For undirected graph


    def BFS(self, root):
        if root is None:
            return
        visited = {v: False for v in self.V}
        q = [root]
        visited[root] = True

        while q:
            curNode = q.pop(0)
            print(curNode, end=' ')
            for v in self.neighbor[curNode]:
                if not visited[v]:
                    q.append(v)
                    visited[v] = True

        for k in self.V:
            if not visited[k]:
                q.append(k)
                visited[k] = True
                while q:
                    curNode = q.pop(0)
                    print(curNode, end=' ')
                    for v in self.neighbor[curNode]:
                        if not visited[v]:
                            q.append(v)
                            visited[v] = True


     #1. shortest path in undirected unweighted graph
    def bfs_shortest_path(self, start, goal)-> list:
        '''
        bfs로 진행하면서 경로 내에 goal이 있다면 가장 먼저 goal에 도달한 path가 shortest path임을 보장한다.
        '''
        if start== goal:
            return [start]
        
        visited = {v: False for v in self.V}
        q = deque([[start]])


        while q: 
            path = q.popleft()
            node = path[-1] ## 가장 최근 node로부터 더 확장해나가는 느낌.

            # 방문을 하지 않았다면
            if not visited[node]:
                visited[node] = True

                for w in self.neighbor[node]:
                    new_path = list(path)
                    new_path.append(w)
                    q.append(new_path)

                    if w == goal:
                        return new_path ## 순환하다 goal이 나타난다면
        return []



    #2.check connectivity
    def are_all_connected(self) -> bool:
        '''
        BFS를 진행하면서 새롭게 visit할 때마다 counting
        그 counting이 vertex와 모두 같다면 모두 connected
        
        '''

        if not self.V :
            return False
        
        visited = {v : False for v in self.V}
        count = 0
        
        # for v in self.V:
        #     q = deque()
        #     q.append(v) # 여기서 연결되지 않아도 모든 node 추가 되게끔.() : 그래서 이 방법은 안됨. 그냥 하나만 가지고 해야함.

        #     ##v와 연결된 모든 vertex를 순회할 것임.
        #     while q:
        #         node = q.popleft()

        #         #traversal 진행여부 여기서 판단.
        #         if not visited[node] : 
        #             visited[node] = True
        #             count +=1
        #             for w in self.neighbors[node]:
        #                 if not visited[w]:
        #                     q.append(w)

        q = deque()
        q.append(self.V[0]) # 하나만 가지고 BFS 일단 진행, 그래야 다 연결된 것만 보니까, 연결 안된 것은 for문으로 해결했음.
        while q:
            node = q.popleft()

            #traversal 진행여부 여기서 판단.
            if not visited[node] : 
                visited[node] = True
                count +=1
                for w in self.neighbor[node]:
                    if not visited[w]:
                        q.append(w)
        
        return count == len(self.V)

    #3. count island
    
    def count_islands(self) -> int:
        if self.V:
            visited ={v: False for v in self.V}

            island_count = 0
        else:
            return 0 
        
        for v in self.V:
            # q = deque()
            # q.append(v) # 모든 것이 한번씩 queue에 들어갔다 나오는 것이 아님.
            
            if not visited[v]: #그 다음 for문 iteration에 대해 연결이 되지 않은 것만 queue를 형성.
                # 대표자 한명에 대해서 새롭게 dequeu 재정의
                q = deque([v])
                island_count +=1 #그때 count


            while q:
                v = q.popleft() # First in, First out

                #check visited
                if not visited[v]:
                    visited[v] = True
                    print(v, end = " ")

                for w in self.neighbor[v]:
                    if not visited[w]:
                        q.append(w)

        return island_count
    
    #4. cycle detection
    

    def cycle_detection(self)-> bool:
        if self.V:
            visited ={v: False for v in self.V}
            parent = {v: None for v in self.V} # 경로 내 바로 직전 parent를 추적

        else:
            return False

        for v in self.V:
            
            #모든 vertex가 아닌 각 island별로 돌리기 위해서.
            if not visited[v]:
                q = deque([v])


            #각 node에 대해 bfs를 진행하는 부분.
            while q:

                v = q.popleft() # First in, First out

                #check visited
                if not visited[v]:
                    visited[v] = True
                    

                    for w in self.neighbor[v]:
                        if not visited[w]:
                            q.append(w)
                            parent[w] = v
                        
                        elif parent[v] !=w: 
                            '''
                            ## v-> w 왔는데, 이미 재방문이고, 
                            w->v가 아니라면!(즉 bidirected가 아니라면)
                            '''
                            
                            return True


if __name__ == "__main__":
    vertices = [1, 2, 3, 4, 5, 6, 7, 8]
    edges = [
    (1, 2), (1, 3), 
    (2, 1), (2, 8),
    (3, 1), (3, 4), (3, 5),
    (4, 3), (4, 5),
    (5, 3), (5, 4),
    (6, 7),
    (7, 6),
    (8, 2)
    ]

    # Create the graph
    graph = undi_graph(vertices, edges)

    # Perform BFS starting from vertex 1
    print("BFS starting from vertex 1:")
    graph.BFS(1)
    
    print("\n")

    print("Shortest Path from 1 to 8:", graph.bfs_shortest_path(1, 8))

    print("Are all nodes connected?", graph.are_all_connected())

    print("Number of islands:", graph.count_islands())

    print("Does the graph have a cycle?", graph.cycle_detection())




####### directed graph #########
class dir_graph():
    def __init__(self, V:list, E:list) -> None:
        self.V = V[:]
        self.neighbor = {v: [] for v in V}
        for (v, w) in E:
            self.neighbor[v].append(w)


    def BFS(self, root):
        if root is None:
            return
        
        visited = {v: False for v in self.V}
        q = [root]
        visited[root] = True

        while q:
            curNode = q.pop(0)
            print(curNode, end=' ')
            for v in self.neighbor[curNode]:
                if not visited[v]:
                    q.append(v)
                    visited[v] = True

        for k in self.V:
            if not visited[k]:
                q.append(k)
                visited[k] = True
                while q:
                    curNode = q.pop(0)
                    print(curNode, end=' ')
                    for v in self.neighbor[curNode]:
                        if not visited[v]:
                            q.append(v)
                            visited[v] = True

     #1. shortest path in undirected unweighted graph
    def bfs_shortest_path(self, start, goal)-> list:
        '''
        bfs로 진행하면서 경로 내에 goal이 있다면 가장 먼저 goal에 도달한 path가 shortest path임을 보장한다.
        '''
        if start== goal:
            return [start]
        
        visited = {v: False for v in self.V}
        q = deque([[start]])


        while q: 
            path = q.popleft()
            node = path[-1] ## 가장 최근 node로부터 더 확장해나가는 느낌.

            # 방문을 하지 않았다면
            if not visited[node]:
                visited[node] = True

                for w in self.neighbor[node]:
                    new_path = list(path)
                    new_path.append(w)
                    q.append(new_path)

                    if w == goal:
                        return new_path ## 순환하다 goal이 나타난다면
        return []



    #2.check connectivity
    def are_all_connected(self) -> bool:
        '''
        BFS를 진행하면서 새롭게 visit할 때마다 counting
        그 counting이 vertex와 모두 같다면 모두 connected
        
        '''

        if not self.V :
            return False
        
        visited = {v : False for v in self.V}
        count = 0
        
        # for v in self.V:
        #     q = deque()
        #     q.append(v) # 여기서 연결되지 않아도 모든 node 추가 되게끔.() : 그래서 이 방법은 안됨. 그냥 하나만 가지고 해야함.

        #     ##v와 연결된 모든 vertex를 순회할 것임.
        #     while q:
        #         node = q.popleft()

        #         #traversal 진행여부 여기서 판단.
        #         if not visited[node] : 
        #             visited[node] = True
        #             count +=1
        #             for w in self.neighbors[node]:
        #                 if not visited[w]:
        #                     q.append(w)

        q = deque()
        q.append(self.V[0]) # 하나만 가지고 BFS 일단 진행, 그래야 다 연결된 것만 보니까, 연결 안된 것은 for문으로 해결했음.
        while q:
            node = q.popleft()

            #traversal 진행여부 여기서 판단.
            if not visited[node] : 
                visited[node] = True
                count +=1
                for w in self.neighbor[node]:
                    if not visited[w]:
                        q.append(w)
        
        return count == len(self.V)

    #3. count island
    
    def count_islands(self) -> int:
        if self.V:
            visited ={v: False for v in self.V}

            island_count = 0
        else:
            return 0 
        
        for v in self.V:
            # q = deque()
            # q.append(v) # 모든 것이 한번씩 queue에 들어갔다 나오는 것이 아님.
            
            if not visited[v]: #그 다음 for문 iteration에 대해 연결이 되지 않은 것만 queue를 형성.
                # 대표자 한명에 대해서 새롭게 dequeu 재정의
                q = deque([v])
                island_count +=1 #그때 count


            while q:
                v = q.popleft() # First in, First out

                #check visited
                if not visited[v]:
                    visited[v] = True
                    print(v, end = " ")

                for w in self.neighbor[v]:
                    if not visited[w]:
                        q.append(w)

        return island_count
    
    #4. cycle detection
    

    def cycle_detection(self) -> bool:
        def dfs(v, visited, recursion_stack):
            visited[v] = True
            recursion_stack[v] = True

            for neighbor in self.neighbor[v]:
                if not visited[neighbor]:
                    if dfs(neighbor, visited, recursion_stack):
                        return True
                elif recursion_stack[neighbor]:
                    return True

            recursion_stack[v] = False
            return False
        
        visited = {v: False for v in self.V}
        recursion_stack = {v: False for v in self.V}

        for v in self.V:
            if not visited[v]:
                if dfs(v, visited, recursion_stack):
                    return True
        
        return False


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

    # Create the graph
    graph = dir_graph(vertices, edges)

    # Perform BFS starting from vertex 1
    print("BFS starting from vertex 1:")
    graph.BFS(1)

    print("\n")

    print("Shortest Path from 1 to 8:", graph.bfs_shortest_path(1, 8))

    print("Are all nodes connected?", graph.are_all_connected())

    print("Number of islands:", graph.count_islands())

    print("Does the graph have a cycle?", graph.cycle_detection())




############### 그래프 자체로 주어졌을 경우 #################
### Undirected graph, Directed graph 모두 표현 가능 ###########
#queue 쓰기
from collections import deque


num_nodes = 8 
def bfs_helper(graph, node, visited):
    queue = deque([node])
    visited[node] = True

    while queue:
        v = queue.popleft()  # 데크에 삽입된 순서대로 노드 하나 꺼내기
        print(v, end=' ')
        for i in graph[v]:
            if not visited[i]:
                queue.append(i)
                visited[i] = True



# 시작 노드 안넣어두기
# def bfs(graph, num_nodes):
#     visited = [False] * (num_nodes + 1)
    
#     for node in range(1, num_nodes + 1):
#         if not visited[node]:
#             bfs_helper(graph, node, visited)


# 시작 위치 지명하기
def bfs(graph, num_nodes, start_node):
    visited = [False] * (num_nodes + 1)
    bfs_helper(graph, start_node, visited)

    for node in range(1, num_nodes + 1):
        if not visited[node]:
            bfs_helper(graph, node, visited)


def bfs_shortest_path(graph, start, goal):
    if start == goal:
        return [start]

    visited = [False] * (len(graph))
    q = deque([[start]])

    while q:
        path = q.popleft()
        node = path[-1]

        if not visited[node]:
            visited[node] = True
            for neighbor in graph[node]:
                new_path = list(path)
                new_path.append(neighbor)
                q.append(new_path)

                if neighbor == goal:
                    return new_path
    return []



def are_all_connected(graph, num_nodes):
    visited = [False] * (num_nodes + 1)
    q = deque([1])  # 첫 번째 노드에서 시작 (노드 번호 1부터 시작)

    count = 0
    while q:
        node = q.popleft()

        if not visited[node]:
            visited[node] = True
            count += 1
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    q.append(neighbor)

    # 모든 노드가 방문되었는지 확인
    return count == num_nodes



def count_islands(graph, num_nodes):
    visited = [False] * (num_nodes + 1)
    island_count = 0

    for node in range(1, num_nodes + 1):
        if not visited[node]:
            q = deque([node])
            island_count += 1

            while q:
                v = q.popleft()

                if not visited[v]:
                    visited[v] = True
                    for neighbor in graph[v]:
                        if not visited[neighbor]:
                            q.append(neighbor)

    return island_count


def cycle_detection(graph, num_nodes):
    def dfs(v, visited, recursion_stack):
        visited[v] = True
        recursion_stack[v] = True

        for neighbor in graph[v]:
            if not visited[neighbor]:
                if dfs(neighbor, visited, recursion_stack):
                    return True
            elif recursion_stack[neighbor]:
                return True

        recursion_stack[v] = False
        return False
    
    visited = [False] * (num_nodes + 1)
    recursion_stack = [False] * (num_nodes + 1)

    for node in range(1, num_nodes + 1):
        if not visited[node]:
            if dfs(node, visited, recursion_stack):
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
# 1 2 3 8 4 5 6 7

#Undirected
graph = [
    [],
    [2, 3],
    [1, 8],
    [1, 4, 5],
    [3, 5],
    [3, 4],
    [7],
    [6],
    [2]
]
# 1 2 3 8 4 5 6 7



print("BFS starting from vertex 1:")
# bfs(graph, num_nodes)
bfs(graph, num_nodes, 1)
print("\n")

print("Shortest Path from 1 to 8:", bfs_shortest_path(graph, 1, 8))

print("Are all nodes connected?", are_all_connected(graph, num_nodes))

print("Number of islands:", count_islands(graph, num_nodes))

print("Does the graph have a cycle?", cycle_detection(graph, num_nodes))