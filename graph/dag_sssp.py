import sys

class Edge:
    src = 0
    dst = 0
    weight = 0

    def __init__(self, src: int, dst: int, weight: int):
        self.src = src
        self.dst = dst
        self.weight = weight


class Vertex:
    dist = 0
    pi = 0

    def __init__(self):
        self.dist = sys.maxsize
        self.pi = -1


class Graph:
    vertices = []
    adj = []

    def __init__(self, numVertex: int):
        self.vertices = [Vertex() for i in range(numVertex)]
        self.adj = [[] for i in range(numVertex)]

    def addEdge(self, src: int, dst: int, weight: int):
        edge = Edge(src, dst, weight)
        self.adj[src].append(edge)
    
    def initializeSingleSource(self, source: int):
        for vertex in self.vertices:
            vertex.dist = sys.maxsize
            vertex.pi = -1
        self.vertices[source].dist = 0
    
    def relax(self, edge):
        if self.vertices[edge.src].dist != sys.maxsize and self.vertices[edge.dst].dist > self.vertices[edge.src].dist + edge.weight:
            self.vertices[edge.dst].dist = self.vertices[edge.src].dist + edge.weight
            self.vertices[edge.dst].pi = edge.src

    def DFS_VISIT(self, u: int, visited, finishStack):
        visited[u] = True

        for edge in self.adj[u]:
            if visited[edge.dst] is False:
                self.DFS_VISIT(edge.dst, visited, finishStack)
        
        finishStack.append(u)


    def topologicalSort(self):
        finishStack = []
        visited = [False for i in range(len(self.vertices))]

        for i in range(len(self.vertices)):
            if visited[i] is False:
                self.DFS_VISIT(i, visited, finishStack)
        
        return finishStack
    
    # 동시에 사이클 
    
    def dagShortestPaths(self, source: int):
        finishStack = self.topologicalSort()

        self.initializeSingleSource(source)

        while len(finishStack) != 0:
            u = finishStack.pop()

            for edge in self.adj[u]:
                self.relax(edge)


def main():
    graph = Graph(6)

    graph.addEdge(0,1,5)
    graph.addEdge(0,2,3)
    graph.addEdge(1,2,2)
    graph.addEdge(1,3,6)
    graph.addEdge(2,3,7)
    graph.addEdge(2,4,4)
    graph.addEdge(2,5,2)
    graph.addEdge(3,4,-1)
    graph.addEdge(3,5,1)
    graph.addEdge(4,5,-2)

    source = 1
    graph.dagShortestPaths(source)

    print("Shortest path from vertex", source, ":")
    for i in range(len(graph.vertices)):
        print("Vertex", i, ": Distance =", graph.vertices[i].dist, ": Predecessor =", graph.vertices[i].pi)




if __name__ == '__main__':
    main()
