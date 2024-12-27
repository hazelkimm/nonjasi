from typing import List

def is_safe(M: List[List[str]], r: int, c: int, Row: int, Col: int):
    return (0 <= r < Row) and (0 <= c < Col) and (M[r][c] == '1')


def convert_matrix_to_graph(M: List[List[str]]) -> List[List[int]]:
    n_row = len(M)
    n_col = len(M[0])
    adj = [[] for _ in range(n_row * n_col)]

    directions = [[-1, -1], [-1, 0], [-1, 1],
                  [0, -1],          [ 0, 1],
                  [1, -1],  [1, 0], [1, 1]]
    
    for r in range(n_row):
        for c in range(n_col):
            if M[r][c] == '1':
                idx = r * n_col + c
                adj[idx].append(idx)
                for dr, dc in directions:
                    nr = r + dr
                    nc = c + dc
                    if is_safe(M, nr, nc, n_row, n_col):
                        n_idx = nr * n_col + nc
                        adj[idx].append(n_idx)
    return adj


def dfs(adj: list[list[int]]) -> int:
    cnt = 0
    
    n = len(adj)
    visited = [False] * n

    def dfs_util(v: int):
        visited[v] = True
        for neighbor in adj[v]:
            if not visited[neighbor]:
                dfs_util(neighbor)
    
    for i in range(n):
        if not visited[i] and len(adj[i]):
            dfs_util(i)
            cnt += 1
    
    return cnt


def count_islands(M: List[List[str]]) -> int:
    adj = convert_matrix_to_graph(M)
    print(adj)
    return dfs(adj)


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