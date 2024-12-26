# 1. Edge 정의
class Edge:
    src = 0
    dst = 0
    weight = 0

    def __init__(self, src: int, dst: int, weight: int):
        self.src = src
        self.dst = dst
        self.weight = weight




# 2. find-set
# v의 부모를 재귀적으로 찾아서 최종적 루트 노드 찾기
def Find(vertices, v: int):
    if v == vertices[v]:
        return v
    else:
        vertices[v] = Find(vertices, vertices[v])
        return vertices[v]




# 3. union 함수
def Union(vertices, a: int, b: int):
    a = Find(vertices, a)
    b = Find(vertices, b)

    # b로 통합
    if a != b:
        vertices[a] = b

# 랭크 기반병합: 트리의 높이를 최소화하기 위해 더 낮은 랭크의 트리를 더 높은 랭크의 트리에 병합
# def Union(vertices, rank, a: int, b: int):
#     a = Find(vertices, a)
#     b = Find(vertices, b)

#     if a != b:
#         if rank[a] < rank[b]:
#             vertices[a] = b
#         elif rank[a] > rank[b]:
#             vertices[b] = a
#         else:
#             vertices[b] = a
#             rank[a] += 1




def MSTKruskal(vertices, edges):
    mst = []

    # weight를 기준으로 edge오름차순으로 정렬
    edges.sort(key=lambda x: x.weight)

    # 랭크 활용시
    # rank = [0] * len(vertices)


    for edge in edges:
        set1 = Find(vertices, edge.src)
        set2 = Find(vertices, edge.dst)

        if set1 != set2:
            mst.append(edge)
            Union(vertices, set1, set2)
    
    return mst



def main():
    V = 9
    E = 14
    vertices = []
    edges = []

    for i in range(V):
        vertices.append(i)
    
    edges.append(Edge(0, 1, 4))
    edges.append(Edge(0, 7, 8))
    edges.append(Edge(1, 2, 8))
    edges.append(Edge(1, 7, 11))
    edges.append(Edge(2, 3, 7))
    edges.append(Edge(2, 5, 4))
    edges.append(Edge(2, 8, 2))
    edges.append(Edge(3, 4, 9))
    edges.append(Edge(3, 5, 14))
    edges.append(Edge(4, 5, 10))
    edges.append(Edge(5, 6, 2))
    edges.append(Edge(6, 7, 1))
    edges.append(Edge(6, 8, 6))
    edges.append(Edge(7, 8, 7))

    mst = MSTKruskal(vertices, edges)

    totalWeight = 0
    print("MST by Kruskal's Algorithm:")
    for edge in mst:
        print("Edge:", edge.src, "-", edge.dst, ", Weight:", edge.weight)
        totalWeight += edge.weight
    print("Total Weight of MST:", totalWeight)

if __name__ == '__main__':
    main()