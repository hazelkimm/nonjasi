#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 1000000000

typedef struct {
    int node, weight;
} INFO;

void FloydWarshall(int **ArrayFY, int numNode) {
    for (int k=1; k<=numNode; k++) {
        for (int i=1; i<=numNode; i++) {
            for (int j=1; j<=numNode; j++) {
                ArrayFY[i][j] = min(ArrayFY[i][j], ArrayFY[i][k]+ArrayFY[k][j]);
            }
        }
    }
}

bool detectNegativeCycle(int **ArrayFY, int numNode) {
    for (int i = 1; i <= numNode; i++) {
        if (ArrayFY[i][i] < 0) {
            return true;  // Negative cycle detected
        }
    }
    return false;  // No negative cycle
}

void printPath(int **Path, int i, int j) {
    if (i == j) {
        cout << i << " ";
    } else if (Path[i][j] == -1) {
        cout << "No path exists from " << i << " to " << j << endl;
    } else {
        printPath(Path, i, Path[i][j]);
        cout << j << " ";
    }
}


/*
ArrayFY의 형태 예시
   1  2  3  4  5
1 [0, 1, 5, INF, 9]
2 [1, 0, 2, INF, INF]
3 [5, 2, 0, INF, 2]
4 [INF, INF, INF, 0, 3]
5 [9, INF, 2, 3, 0]

*/


int main() {
    int numNode = 5;
    vector<vector<INFO>> v(numNode+1, vector<INFO>());
    int **ArrayFY;
    ArrayFY = new int *[numNode+1];
    for (int i=0; i<numNode+1; i++) {
        ArrayFY[i] = new int[numNode+1];
    }

    // 혹은 int **arrayFY부터 for문까지 아래 한문장으로 대체 가능:
    // vector<vector<int>> ArrayFY(numNode + 1, vector<int>(numNode + 1, INF));
    // 이 경우 위에 function의 인자는 int **ArrayFY가 아니라 vector<vector<int>>&ArrayFY가 된다


    // Make Graph
    v[1].push_back({2, 1});
    v[1].push_back({3, 5});
    v[1].push_back({5, 9});
    v[2].push_back({1, 1});
    v[2].push_back({3, 2});
    v[3].push_back({1, 5});
    v[3].push_back({2, 2});
    v[3].push_back({5, 2});
    v[4].push_back({5, 3});
    v[5].push_back({1, 9});
    v[5].push_back({3, 2});
    v[5].push_back({4, 3});

    // Initialize FY Array
    // 1. 모든 값을 0 혹은 INF로 초기화
    //void initializeArrayFY(int **ArrayFY, int numNode) {  로 함수 따로 밖에서 빼도 됨; 그 경우 initializeArrayFY(ArrayFY, nmNode) 호출
    for (int i=1; i<=numNode; i++) {
        for (int j=1; j<=numNode; j++) {
            if (i == j) ArrayFY[i][j] = 0;
            else ArrayFY[i][j] = INF;
        }
    }


    // 2. 그래프에 그려진 간선 정보 넣기
    // void insertEdgeInfo(int **ArrayFY, const vector<vector<INFO>>& v, int numNode) { 로 함수 밖에서 따로 빼도 됨    ; 그 경우 insertEdgeInfo(ArrayFY, v, numNode) 로 호출
    for (int i=1; i<=numNode; i++) {
        for (int j=0; j<v[i].size(); j++) {
            int nextNode = v[i][j].node;
            int weight = v[i][j].weight;

            ArrayFY[i][nextNode] = weight;
        }
    }

    // Floyd-Warshall Algorithm
    FloydWarshall(ArrayFY, numNode);


    // Detect Negative Cycle
    if (detectNegativeCycle(ArrayFY, numNode)) {
        cout << "Negative cycle detected." << endl;
    } else {
        cout << "No negative cycle detected." << endl;
    }


//void printArrayFY(int **ArrayFY, int numNode) {  로 함수 밖에서 따로 빼도 됨
    for (int i=1; i<=numNode; i++) {
        for (int j=1; j<=numNode; j++) {
            if (ArrayFY[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << ArrayFY[i][j] << " ";
            }
        }
        cout << endl;
    }

}