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


def initializeSingleSource(vertices, source: int):
    for vertex in vertices:
        vertex.dist = sys.maxsize
        vertex.pi = -1
    vertices[source].dist = 0

def relax(vertices, edge):
    if vertices[edge.src].dist != sys.maxsize and vertices[edge.dst].dist > vertices[edge.src].dist + edge.weight:
        vertices[edge.dst].dist = vertices[edge.src].dist + edge.weight
        vertices[edge.dst].pi = edge.src

def bellmanFord(vertices, edges, source):
    initializeSingleSource(vertices, source)

    for i in range(1, len(vertices)+1):
        for edge in edges:
            relax(vertices, edge)
    
    for edge in edges:
        if vertices[edge.src].dist != sys.maxsize and vertices[edge.dst].dist > vertices[edge.src].dist + edge.weight:
            return False
    
    return True


def detectNegativeCycle(vertices, edges):
    for edge in edges:
        if vertices[edge.src].dist != sys.maxsize and vertices[edge.dst].dist > vertices[edge.src].dist + edge.weight:
            return True  # Negative weight cycle detected
    return False  # No negative weight cycle


def main():
    vertices = [Vertex() for i in range(5)]
    edges = [
        Edge(0,1,6), Edge(0,3,7),
        Edge(1,2,5), Edge(1,3,8), Edge(1,4,-4),
        Edge(2,1,-2),
        Edge(3,2,-3), Edge(3,4,9),
        Edge(4,0,2), Edge(4,2,7)
    ]

    source = 0

    if bellmanFord(vertices, edges, source):
        print("Shortest path from vertex", source, ':')
        for i in range(len(vertices)):
            print("Vertex", i, ": Distance =", vertices[i].dist, ", Predecessor =", vertices[i].pi)

    else:
        print("Negative weight cycle detected. Bellman-Ford algorithm failed.")

    detectNegativeCycle(vertices,edges)
if __name__ == '__main__':
    main()