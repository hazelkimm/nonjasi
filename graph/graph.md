Prim's Algorithm:
목적: MST
시간 복잡도: 우선순위 큐를 사용한 구현에서 O(E log V)입니다.
음수 가중치: 사용 가능
특징: 시작점을 내가 정하고 나서 MST!


Kruskal's Algorithm: 
목적: MST
시간 복잡도: 간선을 정렬하는데 O(E log E), 간선을 하나씩 추가하면서 MST를 구성하는 데 O(E log V)
음수 가중치: 사용 가능
특징: 간선을 가중치에 따라 정렬한 후, 최소 가중치 간선을 하나씩 추가하며 MST를 구성합니다. MST를 구할 때 사용하는 Disjoint Set 구조를 사용하여 사이클을 감지하고 피합니다.
시작점을 내가 정의하지 않음. edge의 min이 시작점이고, edge의 weight가 작은 순서대로 tree를 만들어나감.







Dijkstra's Algorithm:
목적: SSSP
시간 복잡도: 간단한 구현에서 O(V^2), 우선순위 큐를 사용한 구현에서 O(E log V)
음수 가중치: 음수 가중치 X
특징: 음수 간선이 없는 그래프에서 사용되며, 단일 출발점에서 다른 모든 정점까지의 최단 경로를 찾는 데 효율적입니다.


Bellman-Ford Algorithm:
목적: SSSP
시간 복잡도: O(VE)
음수 가중치: 음수 가중치 O, 음수 사이클 X


Dag_sssp:
목적: SSSP
시간 복잡도: O(V + E)
음수 가중치: 음수 가중치 O, 사이클 존재 안함
특징: 음수 가중치를 포함한 directed graph에서 매우 효율적. dag라 사이클이 없음. 이 그래프에서는 topological order 존재







Floyd-Warshall Algorithm:
목적: APSP
시간 복잡도: O(V^3)
음수 가중치: 음수 가중치 O, 음수 사이클 X


Johnson's Algorithm:
목적: APSP
시간 복잡도: O(V^2 log V + VE)
음수 가중치: 음수 가중치 O, 음수 사이클 X
특징: 벨만-포드 알고리즘을 사용하여 그래프를 변환하고, 변환된 그래프에 대해 다익스트라 알고리즘을 사용합니다. floyd-warshall보다 빠르다