class Vertex:
    color = 'WHITE'
    pi = -1
    discover = 0
    finish = 0
    adj = []

    def __init__(self):
        self.color = 'WHITE'
        self.pi = -1
        self.discover = 0
        self.finish = 0
        self.adj = []

class Graph:
    vertices = []

    def __init__(self, numVertex: int):
        self.vertices = [Vertex() for i in range(numVertex)]


    def DFS_VISIT(self, u: int, time: int, finishStack):
        time = time + 1
        self.vertices[u].discover = time
        self.vertices[u].color = 'GRAY'

        for v in self.vertices[u].adj:
            if self.vertices[v].color == 'WHITE':
                self.vertices[v].pi = u
                time = self.DFS_VISIT(v, time, finishStack)
        
        time = time + 1
        self.vertices[u].finish = time
        self.vertices[u].color = 'BLACK'
        finishStack.append(u)

        return time



    def DFS(self):
        time = 0
        finishStack = []

        for i in range(len(self.vertices)):
            if self.vertices[i].color == 'WHITE':
                time = self.DFS_VISIT(i, time, finishStack)
        
        return finishStack




    def DFS_STACK(self):
        time = 0
        finishStack = []
        for i in range(len(self.vertices)):
            if self.vertices[i].color == 'WHITE':
                stack = [i]
                while stack:
                    u = stack.pop()
                    if self.vertices[u].color == 'WHITE':
                        time += 1
                        self.vertices[u].discover = time
                        self.vertices[u].color = 'GRAY'
                        stack.append(u)  # Push the node back to the stack to handle finishing time
                        for v in reversed(self.vertices[u].adj):  # reversed to maintain the same order as recursive DFS
                            if self.vertices[v].color == 'WHITE':
                                self.vertices[v].pi = u
                                stack.append(v)
                    elif self.vertices[u].color == 'GRAY':
                        time += 1
                        self.vertices[u].finish = time
                        self.vertices[u].color = 'BLACK'
                        finishStack.append(u)

        return finishStack

    def CheckConnectivity(self):
        self.DFS()  # Perform DFS to mark all reachable vertices
        for vertex in self.vertices:
            if vertex.color == 'WHITE':  # If any vertex is still WHITE, graph is not fully connected
                return False
        return True

    def CountIslands(self):
        island_count = 0
        for vertex in self.vertices:
            vertex.color = 'WHITE'  # Reset vertex colors for counting islands

        for i in range(len(self.vertices)):
            if self.vertices[i].color == 'WHITE':
                self.DFS_VISIT(i, 0, [])
                island_count += 1

        return island_count

    def DetectCycleUtil(self, u):
        self.vertices[u].color = 'GRAY'  # Mark the current node as being processed (GRAY)
        
        for v in self.vertices[u].adj:
            if self.vertices[v].color == 'WHITE':  # If the adjacent node is WHITE, explore it
                if self.DetectCycleUtil(v):
                    return True
            elif self.vertices[v].color == 'GRAY':  # If the adjacent node is GRAY, a cycle is found
                return True
        
        self.vertices[u].color = 'BLACK'  # Mark the node as fully processed (BLACK)
        return False

    def DetectCycle(self):
        for vertex in self.vertices:
            vertex.color = 'WHITE'  # Reset vertex colors for cycle detection

        for i in range(len(self.vertices)):
            if self.vertices[i].color == 'WHITE':
                if self.DetectCycleUtil(i):
                    return True
        return False


    def TopologicalSort(self):
        result = []
        finishStack = []

        finishStack = self.DFS()

        while len(finishStack) != 0:
            result.append(finishStack.pop())
        
        return result


def main():
    # [#11] p.21 graph example
    numVertex = 6
    graph = Graph(numVertex)

    graph.vertices[0].adj = [1, 3]
    graph.vertices[1].adj = [4]
    graph.vertices[2].adj = [4, 5]
    graph.vertices[3].adj = [1]
    graph.vertices[4].adj = [3]
    graph.vertices[5].adj = [5]

    graph.DFS()
 
    for i in range(numVertex):
        print('Vertex', i, ': Discover =', graph.vertices[i].discover, ', Finish =', graph.vertices[i].finish)


    # [#11] p.30 graph example
    # numVertex = 9
    # graph = Graph(numVertex)

    # graph.vertices[0].adj = [1, 7]
    # graph.vertices[1].adj = [2, 7]
    # graph.vertices[2].adj = [5]
    # graph.vertices[3].adj = [2, 4]
    # graph.vertices[4].adj = [5]
    # graph.vertices[5].adj = []
    # graph.vertices[6].adj = [7]
    # graph.vertices[7].adj = []
    # graph.vertices[8].adj = []

    # sortedVertices = graph.TopologicalSort()

    # for i in range(numVertex):
    #     print('Vertex', i, ': Discover =', graph.vertices[i].discover, ', Finish =', graph.vertices[i].finish)

    # print('Topological Sort:', end=' ')
    # for vertex in sortedVertices:
    #     print(vertex, end=' ')
    # print()

     # DFS using stack
    graph.DFS_STACK()
    print("\nDFS (Stack-based):")
    for i in range(numVertex):
        print(f'Vertex {i}: Discover = {graph.vertices[i].discover}, Finish = {graph.vertices[i].finish}')

    # Check Connectivity
    is_connected = graph.CheckConnectivity()
    print(f"\nCheck Connectivity: {'Connected' if is_connected else 'Not Connected'}")

    # Count Islands
    islands = graph.CountIslands()
    print(f"Number of Islands: {islands}")

    # Detect Cycle
    has_cycle = graph.DetectCycle()
    print(f"Cycle Detection: {'Cycle exists' if has_cycle else 'No cycle'}")

    # Topological Sort
    sortedVertices = graph.TopologicalSort()
    print(f"Topological Sort: {sortedVertices}")




if __name__ == '__main__':
    main()