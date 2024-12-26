#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 1000000000

typedef struct {
    int node, weight;
} INFO;


void FloydWarshall(int **ArrayFY, int numNode) {
    for (int k = 1; k <= numNode; k++) {
        for (int i = 1; i <= numNode; i++) {
            for (int j = 1; j <= numNode; j++) {
                if (ArrayFY[i][j] > ArrayFY[i][k] + ArrayFY[k][j]) {
                    ArrayFY[i][j] = ArrayFY[i][k] + ArrayFY[k][j];
                }
            }
        }
    }
}


int detectNegativeCycle(int **ArrayFY, int numNode) {
    for (int i = 1; i <= numNode; i++) {
        if (ArrayFY[i][i] < 0) {
            return 1;  // Negative weight cycle detected
        }
    }
    return 0;  // No negative weight cycle detected
}


int main() {
    int numNode = 5;
    INFO **v;
    v = (INFO **)malloc((numNode + 1) * sizeof(INFO *));
    
    int edgesPerNode[] = {0, 3, 2, 3, 1, 3};  // 각 노드별 간선 개수

    for (int i = 1; i <= numNode; i++) {
        v[i] = (INFO *)malloc(edgesPerNode[i] * sizeof(INFO));
    }

    int **ArrayFY;
    ArrayFY = (int **)malloc((numNode + 1) * sizeof(int *));
    for (int i = 0; i <= numNode; i++) {
        ArrayFY[i] = (int *)malloc((numNode + 1) * sizeof(int));
    }

    // Make Graph
    v[1][0] = (INFO){2, 1};
    v[1][1] = (INFO){3, 5};
    v[1][2] = (INFO){5, 9};
    v[2][0] = (INFO){1, 1};
    v[2][1] = (INFO){3, 2};
    v[3][0] = (INFO){1, 5};
    v[3][1] = (INFO){2, 2};
    v[3][2] = (INFO){5, 2};
    v[4][0] = (INFO){5, 3};
    v[5][0] = (INFO){1, 9};
    v[5][1] = (INFO){3, 2};
    v[5][2] = (INFO){4, 3};

    // Initialize FY Array
    for (int i = 1; i <= numNode; i++) {
        for (int j = 1; j <= numNode; j++) {
            if (i == j)
                ArrayFY[i][j] = 0;
            else
                ArrayFY[i][j] = INF;
        }
    }
    
    // Graph에 있는 간선 정보를 FY Array에 복사
    for (int i = 1; i <= numNode; i++) {
        for (int j = 0; j < edgesPerNode[i]; j++) {  // 노드의 간선 수만큼 반복
            int nextNode = v[i][j].node;
            int weight = v[i][j].weight;
            ArrayFY[i][nextNode] = weight;
        }
    }

    // Floyd-Warshall Algorithm
    FloydWarshall(ArrayFY, numNode);


    // 음수 가중치 사이클 감지
    if (detectNegativeCycle(ArrayFY, numNode)) {
        printf("Negative weight cycle detected.\n");
    } else {
        printf("No negative weight cycle detected.\n");
    }
    

    // 결과 출력
    for (int i = 1; i <= numNode; i++) {
        for (int j = 1; j <= numNode; j++) {
            if (ArrayFY[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", ArrayFY[i][j]);
            }
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 1; i <= numNode; i++) {
        free(v[i]);
        free(ArrayFY[i]);
    }
    free(v);
    free(ArrayFY);

    return 0;
}
