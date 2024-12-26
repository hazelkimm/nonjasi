import sys

class Vertex:
    color = 'WHITE'
    dist = sys.maxsize
    pi = -1
    adj = []

    def __init__(self):
        self.color = 'WHITE'
        self.dist = sys.maxsize
        self.pi = -1
        self.adj = []

class Graph:
    vertices = []

    def __init__(self, numVertex: int):
        self.vertices = [Vertex() for i in range(numVertex)]
    
    def BFS(self, s: int):
        self.vertices[s].color = 'GRAY'
        self.vertices[s].dist = 0
        self.vertices[s].pi = -1

        Q = []
        Q.append(s)

        while len(Q) != 0:
            u = Q.pop(0)

            for v in self.vertices[u].adj:
                if self.vertices[v].color == 'WHITE':
                    self.vertices[v].color = 'GRAY'
                    self.vertices[v].dist = self.vertices[u].dist + 1
                    self.vertices[v].pi = u
                    Q.append(v)
            
            self.vertices[u].color = 'BLACK'

    # Shortest Path
    def bfs_shortest_path(self, start: int, goal: int):
        self.BFS(start)

        path = []
        current = goal
        while current != -1:
            path.insert(0, current)  # Insert at the beginning
            current = self.vertices[current].pi

        if path[0] == start:
            return path
        else:
            return []

    # Check Connectivity
    def are_all_connected(self):
        self.BFS(0)

        for vertex in self.vertices:
            if vertex.color == 'WHITE':
                return False
        return True

    # Count Islands
    # 통으로 연결되어있으면 1
    def count_islands(self):
        count = 0

        for vertex in self.vertices:
            vertex.color = 'WHITE'
            vertex.dist = sys.maxsize
            vertex.pi = -1

        for i in range(len(self.vertices)):
            if self.vertices[i].color == 'WHITE':
                self.BFS(i)
                count += 1

        return count

    # Cycle Detection
    def cycle_detection(self):
        for vertex in self.vertices:
            vertex.color = 'WHITE'
            vertex.pi = -1

        for i in range(len(self.vertices)):
            if self.vertices[i].color == 'WHITE':
                if self.bfs_cycle_detection(i):
                    return True

        return False

    def bfs_cycle_detection(self, s: int):
        Q = []
        self.vertices[s].color = 'GRAY'
        Q.append(s)

        while len(Q) != 0:
            u = Q.pop(0)

            for v in self.vertices[u].adj:
                if self.vertices[v].color == 'WHITE':
                    self.vertices[v].color = 'GRAY'
                    self.vertices[v].pi = u
                    Q.append(v)
                elif self.vertices[v].color == 'GRAY' and self.vertices[u].pi != v:
                    #만약 directed라면 self.vertices[v].color == 'GRAY'
                    return True
            
            self.vertices[u].color = 'BLACK'
        
        return False

    ## 유방향 그래프의 사이클을 탐지하고 싶다면
    # def bfs_cycle_detection(self, s: int):
    #     Q = []
    #     self.vertices[s].color = 'GRAY'
    #     Q.append(s)

    #     while len(Q) != 0:
    #         u = Q.pop(0)

    #         for v in self.vertices[u].adj:
    #             if self.vertices[v].color == 'WHITE':
    #                 self.vertices[v].color = 'GRAY'
    #                 self.vertices[v].pi = u
    #                 Q.append(v)
    #             elif self.vertices[v].color == 'GRAY':
    #                 # 유방향 그래프에서는 GRAY인 노드를 다시 방문하면 사이클이 존재함을 의미
    #                 return True
                
    #         self.vertices[u].color = 'BLACK'
        
    #     return False



def main():
    # [#11] p.9 graph example
    numVertex = 9
    graph = Graph(numVertex)

    graph.vertices[0].adj = [1, 2, 5]
    graph.vertices[1].adj = [0, 3, 4]
    graph.vertices[2].adj = [0, 3]
    graph.vertices[3].adj = [1, 2, 7]
    graph.vertices[4].adj = [1, 5, 7]
    graph.vertices[5].adj = [0, 4, 6, 8]
    graph.vertices[6].adj = [5, 7, 8]
    graph.vertices[7].adj = [3, 4, 6]
    graph.vertices[8].adj = [5, 6]

    graph.BFS(1)

    for i in range(numVertex):
        print('Vertex', i, ': Distance =', graph.vertices[i].dist, ', Parent =', graph.vertices[i].pi)

    print("\nShortest Path from 0 to 8:", graph.bfs_shortest_path(0, 8))
    print("Are all nodes connected?", "Yes" if graph.are_all_connected() else "No")
    print("Number of islands:", graph.count_islands())
    print("Does the graph have a cycle?", "Yes" if graph.cycle_detection() else "No")

if __name__ == '__main__':
    main()