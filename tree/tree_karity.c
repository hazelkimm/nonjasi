// Function Descriptions:
//- visit(node): 현재 노드의 값을 출력
//- BFT(): 트리에 대해 너비 우선 탐색(BFS) 수행
//- DFT_preorder(): 트리에 대해 전위 순회(DFS) 수행
//- DFT_inorder(): 트리에 대해 중위 순회(DFS) 수행
//- DFT_postorder(): 트리에 대해 후위 순회(DFS) 수행
//- visit_with_size(node, size): 서브트리 크기를 추가하여 노드 값을 업데이트
//- DFT_postorder_with_size(): 후위 순회를 통해 파일 크기를 계산 및 업데이트
//- calculateHeight(): 트리의 높이를 계산
//- countLeaves(): 트리에서 리프 노드의 개수를 계산
//- findMax(): 트리에서 최댓값 찾기
//- findMin(): 트리에서 최솟값 찾기
//- search(value): 트리에서 특정 값이 존재하는지 확인
//- sumOfNodes(): 트리에 있는 모든 노드들 값의 합
//- pathToNode(value): root부터 특정 노드까지의 path 찾기
//- isBalanced(): height-balanced인지 체크하기
//- calculateDiameter: 트리의 지름(노드 간 가장 긴 경로)을 계산합니다.
//- levelOrderTraversal: 트리를 레벨 순서로 순회하고, 각 레벨의 노드 값을 리스트로 반환합니다.
//- addNodes: 주어진 값 리스트를 사용하여 트리에 레벨 순서로 노드를 추가합니다.
//- count_internal_nodes: 리프 노드를 제외한 내부 노드의 개수를 계산합니다.
//- getLeftMostNodes: 왼쪽 nodes들 반환
//- getLeafNodes: leaf nodes 출력하기
//- findLCA(node1, node2): 두 노드의 LCA(최소 공통 조상)를 반환
//- distanceBetweenNodes(node1, node2): 두 노드 간 거리 계산 (LCA 기반)
//- findKthAncestor(node_value, k): 특정 노드의 K번째 조상을 반환
//- areNodesInSameSubtree(node1, node2): 두 노드가 동일한 서브트리에 있는지 확인
//- findPredecessor : predecessor 찾기
//- findSuccessor: successor 찾기

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

// 노드 구조체 정의
typedef struct TreeNode {
    int val;                      // 노드의 값
    int arity;                    // 자식의 최대 개수
    struct TreeNode** children;   // 자식 노드 배열
    struct TreeNode* parent;      // 부모 노드
} TreeNode;

// 트리 구조체 정의
typedef struct Tree {
    TreeNode* root;
    int arity;
} Tree;

// 노드 생성 함수
TreeNode* createNode(int value, int arity) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = value;
    node->arity = arity;
    node->children = (TreeNode**)calloc(arity, sizeof(TreeNode*));
    node->parent = NULL;
    return node;
}

// 트리 생성 함수
Tree* createTree(int rootValue, int arity) {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = createNode(rootValue, arity);
    tree->arity = arity;
    return tree;
}

// 노드 방문
void visit(TreeNode* node) {
    if (node) printf("%d ", node->val);
}

// BFS로 노드 추가
void addNodes(Tree* tree, int* values, int size) {
    if (!tree->root || size <= 0) return;

    TreeNode** queue = (TreeNode**)malloc(size * sizeof(TreeNode*));
    int front = 0, rear = 0;

    queue[rear++] = tree->root;
    int index = 0;

    while (front < rear && index < size) {
        TreeNode* current = queue[front++];
        for (int i = 0; i < current->arity && index < size; ++i) {
            if (!current->children[i]) {
                current->children[i] = createNode(values[index++], tree->arity);
                current->children[i]->parent = current;
                queue[rear++] = current->children[i];
            }
        }
    }
    free(queue);
}

// BFS (Breadth-First Traversal)
void BFT(Tree* tree) {
    if (!tree->root) return;

    TreeNode** queue = (TreeNode**)malloc(1000 * sizeof(TreeNode*));
    int front = 0, rear = 0;

    queue[rear++] = tree->root;

    while (front < rear) {
        TreeNode* current = queue[front++];
        visit(current);

        for (int i = 0; i < current->arity; ++i) {
            if (current->children[i]) {
                queue[rear++] = current->children[i];
            }
        }
    }
    printf("\n");
    free(queue);
}

// DFS 전위 순회 (Preorder)
void preorder(TreeNode* node) {
    if (!node) return;
    visit(node);
    for (int i = 0; i < node->arity; ++i) {
        preorder(node->children[i]);
    }
}

// DFS 중위 순회 (Inorder)
void inorder(TreeNode* node) {
    if (!node) return;
    int mid = node->arity / 2;
    for (int i = 0; i < mid; ++i) {
        inorder(node->children[i]);
    }
    visit(node);
    for (int i = mid; i < node->arity; ++i) {
        inorder(node->children[i]);
    }
}

// DFS 후위 순회 (Postorder)
void postorder(TreeNode* node) {
    if (!node) return;
    for (int i = 0; i < node->arity; ++i) {
        postorder(node->children[i]);
    }
    visit(node);
}

// 트리 높이 계산
int calculateHeight(TreeNode* node) {
    if (!node) return 0;
    int maxHeight = 0;
    for (int i = 0; i < node->arity; ++i) {
        int height = calculateHeight(node->children[i]);
        if (height > maxHeight) maxHeight = height;
    }
    return maxHeight + 1;
}

// 리프 노드 개수 계산
int countLeaves(TreeNode* node) {
    if (!node) return 0;
    bool isLeaf = true;
    int leafCount = 0;
    for (int i = 0; i < node->arity; ++i) {
        if (node->children[i]) {
            isLeaf = false;
            leafCount += countLeaves(node->children[i]);
        }
    }
    return isLeaf ? 1 : leafCount;
}

int findMax(TreeNode* node) {
    if (!node) return INT_MIN; // 노드가 없으면 최소값 반환

    int maxValue = node->val; // 현재 노드의 값
    for (int i = 0; i < node->arity; ++i) {
        int childMax = findMax(node->children[i]); // 자식 노드에서 최댓값 찾기
        if (childMax > maxValue) {
            maxValue = childMax;
        }
    }
    return maxValue;
}

int findMin(TreeNode* node) {
    if (!node) return INT_MAX; // 노드가 없으면 최대값 반환

    int minValue = node->val; // 현재 노드의 값
    for (int i = 0; i < node->arity; ++i) {
        int childMin = findMin(node->children[i]); // 자식 노드에서 최솟값 찾기
        if (childMin < minValue) {
            minValue = childMin;
        }
    }
    return minValue;
}


// 특정 값 검색
bool search(TreeNode* node, int value) {
    if (!node) return false;
    if (node->val == value) return true;
    for (int i = 0; i < node->arity; ++i) {
        if (search(node->children[i], value)) {
            return true;
        }
    }
    return false;
}


// 트리 노드 값 합계
int sumOfNodes(TreeNode* node) {
    if (!node) return 0;
    int sum = node->val;
    for (int i = 0; i < node->arity; ++i) {
        sum += sumOfNodes(node->children[i]);
    }
    return sum;
}



// 특정 노드의 경로 반환
bool pathToNode(TreeNode* node, int value, int* path, int* pathIndex) {
    if (!node) return false;
    path[(*pathIndex)++] = node->val;

    if (node->val == value) return true;

    for (int i = 0; i < node->arity; ++i) {
        if (pathToNode(node->children[i], value, path, pathIndex)) return true;
    }
    (*pathIndex)--;

    return false;
}

bool isBalancedHelper(TreeNode* node, int* height) {
    if (!node) {
        *height = 0;
        return true;
    }

    int leftHeight = 0, rightHeight = 0;
    bool balanced = true;

    for (int i = 0; i < node->arity; ++i) {
        int childHeight = 0;
        balanced &= isBalancedHelper(node->children[i], &childHeight);
        if (childHeight > leftHeight) {
            rightHeight = leftHeight;
            leftHeight = childHeight;
        } else if (childHeight > rightHeight) {
            rightHeight = childHeight;
        }
    }

    *height = leftHeight + 1;
    return balanced && (leftHeight - rightHeight <= 1);
}

bool isBalanced(Tree* tree) {
    int height = 0;
    return isBalancedHelper(tree->root, &height);
}


int calculateDiameter(TreeNode* node, int* height) {
    if (!node) {
        *height = 0;
        return 0;
    }

    int max1 = 0, max2 = 0;
    int diameter = 0;

    for (int i = 0; i < node->arity; ++i) {
        int childHeight = 0;
        diameter = calculateDiameter(node->children[i], &childHeight);
        if (childHeight > max1) {
            max2 = max1;
            max1 = childHeight;
        } else if (childHeight > max2) {
            max2 = childHeight;
        }
    }

    *height = max1 + 1;
    return (max1 + max2 > diameter) ? max1 + max2 : diameter;
}

void levelOrderTraversal(Tree* tree) {
    if (!tree->root) return;

    TreeNode** queue = (TreeNode**)malloc(1000 * sizeof(TreeNode*));
    int front = 0, rear = 0;

    queue[rear++] = tree->root;

    int currentLevel = 0, nextLevelCount = 1, currentLevelCount = 0;

    while (front < rear) {
        currentLevelCount = nextLevelCount;
        nextLevelCount = 0;
        printf("Level %d: ", currentLevel++);

        for (int i = 0; i < currentLevelCount; ++i) {
            TreeNode* current = queue[front++];
            visit(current);

            for (int j = 0; j < current->arity; ++j) {
                if (current->children[j]) {
                    queue[rear++] = current->children[j];
                    nextLevelCount++;
                }
            }
        }
        printf("\n");
    }
    free(queue);
}




int countInternalNodes(TreeNode* node) {
    if (!node) return 0;
    bool isLeaf = true;
    int count = 0;

    for (int i = 0; i < node->arity; ++i) {
        if (node->children[i]) {
            isLeaf = false;
            count += countInternalNodes(node->children[i]);
        }
    }

    return isLeaf ? 0 : 1 + count;
}

void getLeftMostNodes(TreeNode* node) {
    while (node) {
        printf("%d ", node->val);
        node = node->children[0];
    }
    printf("\n");
}


void getLeafNodes(TreeNode* node) {
    if (!node) return;

    bool isLeaf = true;
    for (int i = 0; i < node->arity; ++i) {
        if (node->children[i]) {
            isLeaf = false;
            getLeafNodes(node->children[i]);
        }
    }

    if (isLeaf) {
        printf("%d ", node->val);
    }
}


// 최소 공통 조상 (LCA)
TreeNode* findLCA(TreeNode* root, int value1, int value2) {
    if (!root) return NULL;
    if (root->val == value1 || root->val == value2) return root;

    TreeNode* lca = NULL;
    int count = 0;

    for (int i = 0; i < root->arity; ++i) {
        TreeNode* res = findLCA(root->children[i], value1, value2);
        if (res) {
            count++;
            lca = res;
        }
    }
    return (count > 1) ? root : lca;
}

int depth(TreeNode* node, int value, int level) {
    if (!node) return -1;
    if (node->val == value) return level;

    for (int i = 0; i < node->arity; ++i) {
        int d = depth(node->children[i], value, level + 1);
        if (d != -1) return d;
    }
    return -1;
}

int distanceBetweenNodes(TreeNode* root, int value1, int value2) {
    TreeNode* lca = findLCA(root, value1, value2);
    if (!lca) return -1;

    int d1 = depth(lca, value1, 0);
    int d2 = depth(lca, value2, 0);

    return d1 + d2;
}

TreeNode* findKthAncestor(TreeNode* node, int k) {
    while (node && k > 0) {
        node = node->parent;
        k--;
    }
    return node;
}

bool areNodesInSameSubtree(TreeNode* root, int value1, int value2) {
    TreeNode* lca = findLCA(root, value1, value2);
    return lca && lca != root;
}

TreeNode* findPredecessor(TreeNode* root, int value, TreeNode** predecessor) {
    if (!root) return NULL;

    for (int i = 0; i < root->arity; ++i) {
        if (root->children[i] && root->children[i]->val == value) {
            *predecessor = root;
            return root->children[i];
        }
        TreeNode* result = findPredecessor(root->children[i], value, predecessor);
        if (result) return result;
    }
    return NULL;
}

TreeNode* findSuccessor(TreeNode* node, int value, bool* foundValue) {
    if (!node) return NULL;

    if (*foundValue) return node;
    if (node->val == value) *foundValue = true;

    for (int i = 0; i < node->arity; ++i) {
        TreeNode* result = findSuccessor(node->children[i], value, foundValue);
        if (result) return result;
    }
    return NULL;
}



int main() {
    // 1. 트리 생성 및 노드 추가
    int values[] = {2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(values) / sizeof(values[0]);

    Tree* tree = createTree(1, 3); // 루트 값: 1, 자식 최대 3개
    addNodes(tree, values, size);

    // 트리 구조
    //        1
    //     /  |  \
    //    2   3   4
    //   /|\  /\
    //  5 6 7 8 9

    printf("Breadth-First Traversal:\n");
    BFT(tree); // Expected: 1 2 3 4 5 6 7 8 9

    printf("\nPreorder Traversal:\n");
    preorder(tree->root); // Expected: 1 2 5 6 7 3 8 9 4
    printf("\n");

    printf("\nInorder Traversal:\n");
    inorder(tree->root); // Expected: 5 2 6 7 1 8 3 9 4
    printf("\n");

    printf("\nPostorder Traversal:\n");
    postorder(tree->root); // Expected: 5 6 7 2 8 9 3 4 1
    printf("\n");

    printf("\nTree Height: %d\n", calculateHeight(tree->root)); // Expected: 3

    printf("Leaf Node Count: %d\n", countLeaves(tree->root)); // Expected: 5 (5, 6, 7, 8, 9)

    printf("Sum of All Nodes: %d\n", sumOfNodes(tree->root)); // Expected: 45

    printf("Maximum Value in Tree: %d\n", findMax(tree->root)); // Expected: 9
    printf("Minimum Value in Tree: %d\n", findMin(tree->root)); // Expected: 1

    printf("Is Balanced: %s\n", isBalanced(tree) ? "True" : "False"); // Expected: True

    printf("\nTree Diameter: %d\n", calculateDiameter(tree->root, &(int){0})); // Expected: 4

    printf("\nLevel Order Traversal:\n");
    levelOrderTraversal(tree); 
    // Expected:
    // Level 0: 1
    // Level 1: 2 3 4
    // Level 2: 5 6 7 8 9

    printf("\nInternal Node Count: %d\n", countInternalNodes(tree->root)); // Expected: 4 (1, 2, 3, 4)

    printf("\nLeft-Most Nodes:\n");
    getLeftMostNodes(tree->root); // Expected: 1 2 5

    printf("\nLeaf Nodes:\n");
    getLeafNodes(tree->root); // Expected: 5 6 7 8 9

    printf("\nPath to Node 7: ");
    int path[100], pathIndex = 0;
    if (pathToNode(tree->root, 7, path, &pathIndex)) {
        for (int i = 0; i < pathIndex; ++i) printf("%d ", path[i]);
    }
    // Expected: 1 2 7
    printf("\n");

    TreeNode* lca = findLCA(tree->root, 5, 6);
    if (lca) printf("Lowest Common Ancestor of 5 and 6: %d\n", lca->val); // Expected: 2

    printf("Distance Between Nodes 5 and 6: %d\n", distanceBetweenNodes(tree->root, 5, 6)); // Expected: 2
    printf("Distance Between Nodes 5 and 8: %d\n", distanceBetweenNodes(tree->root, 5, 8)); // Expected: 4

    TreeNode* ancestor = findKthAncestor(tree->root->children[0]->children[2], 2); // Node 7, K=2
    if (ancestor) printf("2nd Ancestor of Node 7: %d\n", ancestor->val); // Expected: 1

    printf("Are Nodes 5 and 6 in Same Subtree: %s\n", areNodesInSameSubtree(tree->root, 5, 6) ? "Yes" : "No");
    // Expected: Yes

    TreeNode* predecessor = NULL;
    findPredecessor(tree->root, 6, &predecessor);
    if (predecessor) printf("Predecessor of Node 6: %d\n", predecessor->val); // Expected: 2

    bool foundValue = false;
    TreeNode* successor = findSuccessor(tree->root, 6, &foundValue);
    if (successor) printf("Successor of Node 6: %d\n", successor->val); // Expected: 7

    return 0;
}
