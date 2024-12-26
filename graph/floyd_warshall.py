INF = 1e+9

class INFO:
    node = 0
    weight = 0

    def __init__(self, node=0, weight=0):
        self.node = node
        self.weight = weight



def FloydWarshall(ArrayFY, numNode: int):
    for k in range(1, numNode+1):
        for i in range(1, numNode+1):
            for j in range(1, numNode+1):
                ArrayFY[i][j] = min(ArrayFY[i][j], ArrayFY[i][k]+ArrayFY[k][j])



def detectNegativeCycle(ArrayFY, numNode: int) -> bool:
    for i in range(1, numNode+1):
        if ArrayFY[i][i] < 0:
            return True  # Negative weight cycle detected
    return False  # No negative weight cycle



def main():
    numNode = 5
    v = [[] for i in range(numNode+1)]
    ArrayFY = [[0]*(numNode+1) for i in range(numNode+1)]

    # Make Graph
    v[1].append(INFO(2,1))
    v[1].append(INFO(3,5))
    v[1].append(INFO(5,9))
    v[2].append(INFO(1,1))
    v[2].append(INFO(3,2))
    v[3].append(INFO(5,1))
    v[3].append(INFO(2,2))
    v[3].append(INFO(5,2))
    v[4].append(INFO(5,3))
    v[5].append(INFO(1,9))
    v[5].append(INFO(3,2))
    v[5].append(INFO(4,3))
    
    # Initialize FY Array
    # 1. 모든 값을 0 혹은 INF로 초기화
    for i in range(1, numNode+1):
        for j in range(1, numNode+1):
            if i == j:
                ArrayFY[i][j] = 0
            else:
                ArrayFY[i][j] = INF  
    # 2. 그래프에 그려진 간선 정보 넣기
    for i in range(1, numNode+1):
        for j in range(len(v[i])):
            nextNode = v[i][j].node
            weight = v[i][j].weight

            ArrayFY[i][nextNode] = weight
    
    # Floyd-Warshall Algorithm
    FloydWarshall(ArrayFY, numNode)


    # Detect negative cycle
    if detectNegativeCycle(ArrayFY, numNode):
        print("Negative weight cycle detected.")
    else:
        print("No negative weight cycle detected.")


    # Print results
    for i in range(1, numNode+1):
        for j in range(1, numNode+1):
            if ArrayFY[i][j] == INF:
                print("INF ")
            else:
                print(ArrayFY[i][j], end=' ')
        print()



if __name__ == "__main__":
    main()