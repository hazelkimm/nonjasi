/*
struct TreeNode* insert(struct TreeNode* root, int val): 이진 탐색 트리에 값을 삽입하는 함수
struct TreeNode* search(struct TreeNode* root, int val): 이진 탐색 트리에서 값을 검색하는 함수
-bool isValueInBST(struct TreeNode* root, int val): 이진 탐색 트리에서 특정 값이 존재하는지 확인하는 함수
struct TreeNode* findMin(struct TreeNode* root): 이진 탐색 트리에서 최솟값을 찾는 함수
struct TreeNode* findMax(struct TreeNode* root): 이진 탐색 트리에서 최댓값을 찾는 함수
struct TreeNode* delete(struct TreeNode* root, int val): 트리에서 값을 삭제하는 함수
void inorder(struct TreeNode* root): 트리의 중위 순회로 값을 출력하는 함수 (좌 -> 노드 -> 우)
void preorder(struct TreeNode* root): 트리의 전위 순회로 값을 출력하는 함수 (노드 -> 좌 -> 우)
void postorder(struct TreeNode* root): 트리의 후위 순회로 값을 출력하는 함수 (좌 -> 우 -> 노드)
-int* postorderTraversal(struct TreeNode* root, int* returnSize): 후위 순회로 값을 리스트에 저장하는 함수
int height(struct TreeNode* root): 트리의 높이를 계산하는 함수
int isBalanced(struct TreeNode* root): 트리가 균형 잡혀 있는지 확인하는 함수
int depth(struct TreeNode* root, int val, int level): 주어진 값이 트리에서 몇 번째 깊이에 있는지 찾는 함수
-int depth(struct TreeNode* root, int val): 주어진 값이 트리에서 몇 번째 깊이에 있는지 찾는 함수
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q): 두 노드 p와 q의 최저 공통 조상을 찾는 함수
int* pathToNode(struct TreeNode* root, int val, int* path, int* pathIndex): 특정 값으로 가는 경로를 찾는 함수
-int* pathToNode(struct TreeNode* root, int val, int* path, int* pathLen): 특정 값까지의 경로를 찾아 반환하는 함수
int** allPaths(struct TreeNode* root, int* returnSize, int** returnColumnSizes): 모든 루트-리프 경로를 찾는 함수
int kthSmallest(struct TreeNode* root, int k): 이진 검색 트리에서 k번째로 작은 값을 반환
int rangeSumBST(struct TreeNode* root, int low, int high): 주어진 범위 [low, high]에 속하는 값들의 합을 계산
void nodesAtDepth(struct TreeNode* root, int depth, int* result, int* returnSize): 특정 깊이에 위치한 노드들의 값을 배열로 반환 (void 반환형) -> result에 값이 채워짐
-int* nodesAtDepth(struct TreeNode* root, int depth, int* returnSize): 특정 깊이에 위치한 노드들의 값을 배열로 반환
int* descendingOrderTraversal(struct TreeNode* root, int* returnSize): 이진 트리를 내림차순으로 순회하여 노드 값을 반환
struct TreeNode* mirrorTree(struct TreeNode* root): 이진 트리를 대칭으로 뒤집는 함수
struct TreeNode* invertTree(struct TreeNode* root): 이진 트리를 뒤집는 함수
int distanceBetweenNodes(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q): 두 노드 사이의 거리를 계산하는 함수
int isValidBST(struct TreeNode* root): 트리가 유효한 BST인지 확인하는 함수
struct TreeNode* sumOfGreaterNodes(struct TreeNode* root): 트리의 각 노드를 해당 노드보다 큰 노드들의 값의 합으로 갱신
int maxPathSum(struct TreeNode* root): 트리에서 가장 큰 경로 합을 구하는 함수
int* nodesInRange(struct TreeNode* root, int low, int high, int* returnSize): 주어진 범위 [low, high]에 속하는 노드들의 값을 반환하는 함수
bool hasPathSum(struct TreeNode* root, int sum): 경로 합이 sum과 일치하는지 확인하는 함수
struct TreeNode* inorderSuccessor(struct TreeNode* root, struct TreeNode* p): p 노드의 중위 순회 후속 노드를 찾는 함수
int isChildSum(struct TreeNode* root): 트리가 자식 노드들의 합 규칙을 만족하는지 확인하는 함수
struct TreeNode* sortedArrayToBST(int* nums, int start, int end): 정렬된 배열을 이진 검색 트리(BST)로 변환하는 함수
int isIdentical(struct TreeNode* root1, struct TreeNode* root2): 두 트리가 동일한지 확인하는 함수
int diameterOfBinaryTree(struct TreeNode* root): 트리의 직경을 구하는 함수 (트리의 직경(Diameter)은 트리 내에서 두 노드 사이의 가장 긴 경로를 의미

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// struct TreeNode* insert(struct TreeNode* root, int val): 이진 탐색 트리에 값을 삽입하는 함수
// 주어진 트리에서 val 값을 적절한 위치에 삽입
struct TreeNode* insert(struct TreeNode* root, int val) {
    // 루트가 비어있으면 새로운 노드를 반환
    if (root == NULL) {
        struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    // 삽입할 값이 현재 노드의 값보다 작으면 왼쪽 서브트리에 삽입
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else {  // 삽입할 값이 현재 노드의 값보다 크면 오른쪽 서브트리에 삽입
        root->right = insert(root->right, val);
    }

    // 변경된 트리의 루트를 반환
    return root;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// struct TreeNode* search(struct TreeNode* root, int val): 이진 탐색 트리에서 값을 검색하는 함수
// 주어진 트리에서 val 값이 있는 노드를 찾으면 그 노드를 반환, 없으면 NULL 반환
struct TreeNode* search(struct TreeNode* root, int val) {
    // 루트가 NULL이거나, 현재 노드 값이 val와 같으면 해당 노드 반환
    if (root == NULL || root->val == val) {
        return root;
    }
    
    // 찾고자 하는 값이 현재 노드의 값보다 작으면 왼쪽 서브트리로 이동
    if (val < root->val) {
        return search(root->left, val);
    }

    // 찾고자 하는 값이 현재 노드의 값보다 크면 오른쪽 서브트리로 이동
    return search(root->right, val);
}


// bool isValueInBST(struct TreeNode* root, int val): 이진 탐색 트리에서 특정 값이 존재하는지 확인하는 함수
// 주어진 트리에서 val 값이 존재하면 true, 아니면 false를 반환
bool isValueInBST(struct TreeNode* root, int val) {
    // 노드가 NULL이면 값이 존재하지 않음
    if (root == NULL) {
        return false;
    }

    // 현재 노드 값이 val과 같으면 true 반환
    if (root->val == val) {
        return true;
    }
    
    // val이 현재 노드 값보다 작으면 왼쪽 서브트리로 이동하여 검색
    if (val < root->val) {
        return isValueInBST(root->left, val);
    }
    
    // val이 현재 노드 값보다 크면 오른쪽 서브트리로 이동하여 검색
    return isValueInBST(root->right, val);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// struct TreeNode* findMin(struct TreeNode* root): 이진 탐색 트리에서 최솟값을 찾는 함수
// 주어진 트리에서 최솟값을 가지는 노드를 반환
struct TreeNode* findMin(struct TreeNode* root) {
    // 왼쪽 자식 노드가 있을 때까지 왼쪽으로 이동
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    // 최솟값을 가진 노드를 반환
    return root;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// struct TreeNode* findMax(struct TreeNode* root): 이진 탐색 트리에서 최댓값을 찾는 함수
// 주어진 트리에서 최댓값을 가지는 노드를 반환
struct TreeNode* findMax(struct TreeNode* root) {
    // 오른쪽 자식 노드가 있을 때까지 오른쪽으로 이동
    while (root != NULL && root->right != NULL) {
        root = root->right;
    }
    // 최댓값을 가진 노드를 반환
    return root;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// struct TreeNode* delete(struct TreeNode* root, int val): 트리에서 값을 삭제하는 함수
struct TreeNode* delete(struct TreeNode* root, int val) {
    if (root == NULL) {  // 트리가 비어있으면, 삭제할 값이 없으므로 루트 반환
        return root;
    }

    if (val < root->val) {  // 삭제할 값이 현재 노드 값보다 작으면 왼쪽 자식에서 삭제
        root->left = delete(root->left, val);
    } else if (val > root->val) {  // 삭제할 값이 현재 노드 값보다 크면 오른쪽 자식에서 삭제
        root->right = delete(root->right, val);
    } else {  // 현재 노드가 삭제할 노드일 경우
        if (root->left == NULL) {  // 왼쪽 자식이 없으면 오른쪽 자식을 대체
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {  // 오른쪽 자식이 없으면 왼쪽 자식을 대체
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // 두 자식이 모두 있을 경우, 오른쪽 서브트리에서 최솟값을 찾아서 현재 노드에 대입
        struct TreeNode* minNode = findMin(root->right);
        root->val = minNode->val;  // 최솟값을 현재 노드의 값으로 대체
        root->right = delete(root->right, minNode->val);  // 오른쪽 자식에서 최솟값 삭제
    }

    return root;  // 변경된 트리의 루트 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void inorder(struct TreeNode* root): 트리의 중위 순회로 값을 출력하는 함수 (좌 -> 노드 -> 우)
void inorder(struct TreeNode* root) {
    if (root != NULL) {  // 루트가 비어있지 않으면
        inorder(root->left);  // 왼쪽 자식 탐색
        printf("%d ", root->val);  // 현재 노드 출력
        inorder(root->right);  // 오른쪽 자식 탐색
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void preorder(struct TreeNode* root): 트리의 전위 순회로 값을 출력하는 함수 (노드 -> 좌 -> 우)
void preorder(struct TreeNode* root) {
    if (root != NULL) {  // 루트가 비어있지 않으면
        printf("%d ", root->val);  // 현재 노드 출력
        preorder(root->left);  // 왼쪽 자식 탐색
        preorder(root->right);  // 오른쪽 자식 탐색
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void postorder(struct TreeNode* root): 트리의 후위 순회로 값을 출력하는 함수 (좌 -> 우 -> 노드)
void postorder(struct TreeNode* root) {
    if (root != NULL) {  // 루트가 비어있지 않으면
        postorder(root->left);  // 왼쪽 자식 탐색
        postorder(root->right);  // 오른쪽 자식 탐색
        printf("%d ", root->val);  // 현재 노드 출력
    }
}


///////////////////////////////////////////////
// 후위 순회를 수행하는 헬퍼 함수
void postorder2(struct TreeNode* node, int* result, int* returnSize) {
    if (node == NULL) {
        return;
    }

    postorder2(node->left, result, returnSize);  // 왼쪽 서브트리 순회
    postorder2(node->right, result, returnSize);  // 오른쪽 서브트리 순회
    result[*returnSize] = node->val;  // 노드 값을 배열에 저장
    (*returnSize)++;  // 저장한 값의 크기 증가
}

// int* postorderTraversal(struct TreeNode* root, int* returnSize): 후위 순회로 값을 리스트에 저장하는 함수
int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    int* result = (int*)malloc(100 * sizeof(int));  // 결과를 저장할 배열 (크기 100으로 초기화)
    *returnSize = 0;  // 결과 크기 초기화

    postorder2(root, result, returnSize);  // 후위 순회 시작

    return result;  // 결과 배열 반환
}
///////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int height(struct TreeNode* root): 트리의 높이를 계산하는 함수
int height(struct TreeNode* root) {
    if (root == NULL) {
        return 0;  // 노드가 없으면 높이는 0
    }

    // 왼쪽과 오른쪽 서브트리의 높이를 구한 후, 더 큰 값을 선택하고 1을 더함
    int left_height = height(root->left);
    int right_height = height(root->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 트리의 높이를 계산하고 균형을 확인하는 함수
int getHeight(struct TreeNode* root) {
    if (root == NULL) {
        return 0;  // 빈 노드의 경우 높이는 0
    }

    // 왼쪽과 오른쪽 서브트리의 높이를 계산
    int left_height = getHeight(root->left);
    int right_height = getHeight(root->right);

    // 만약 서브트리 높이 차이가 2 이상이면 균형이 맞지 않음
    if (left_height == -1 || right_height == -1 || abs(left_height - right_height) > 1) {
        return -1;  // 균형이 맞지 않으면 -1 반환
    }

    return 1 + (left_height > right_height ? left_height : right_height);  // 균형이 맞으면 높이 반환
}

// int isBalanced(struct TreeNode* root): 트리가 균형 잡혀 있는지 확인하는 함수
int isBalanced(struct TreeNode* root) {
    return getHeight(root) != -1;  // 트리 높이가 -1이면 불균형, 아니면 균형
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int depth(struct TreeNode* root, int val, int level): 주어진 값이 트리에서 몇 번째 깊이에 있는지 찾는 함수
int depth(struct TreeNode* root, int val, int level) {
    if (root == NULL) {
        return -1;  // 트리가 비어있으면 -1 반환
    }
    if (root->val == val) {
        return level;  // 값이 현재 노드와 일치하면 깊이(level) 반환
    }
    if (val < root->val) {
        return depth(root->left, val, level + 1);  // 왼쪽 서브트리 탐색
    } else {
        return depth(root->right, val, level + 1);  // 오른쪽 서브트리 탐색
    }
}


// int depth(struct TreeNode* root, int val): 주어진 값이 트리에서 몇 번째 깊이에 있는지 찾는 함수
int depth2(struct TreeNode* root, int val) {
    if (root == NULL) {
        return -1;  // 트리가 비어있으면 -1 반환
    }
    if (root->val == val) {
        return 0;  // 값이 현재 노드와 일치하면 깊이 0 반환
    }

    // 값이 현재 노드보다 작으면 왼쪽 서브트리 탐색
    if (val < root->val) {
        int left_depth = depth2(root->left, val);
        if (left_depth == -1) {
            return -1;  // 왼쪽 서브트리에서 값을 찾지 못했으면 -1 반환
        }
        return left_depth + 1;  // 왼쪽 서브트리에서 값을 찾았으면 깊이에 1을 더해서 반환
    } 
    // 값이 현재 노드보다 크면 오른쪽 서브트리 탐색
    else {
        int right_depth = depth2(root->right, val);
        if (right_depth == -1) {
            return -1;  // 오른쪽 서브트리에서 값을 찾지 못했으면 -1 반환
        }
        return right_depth + 1;  // 오른쪽 서브트리에서 값을 찾았으면 깊이에 1을 더해서 반환
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q): 두 노드 p와 q의 최저 공통 조상을 찾는 함수
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (root == NULL) {
        return NULL;  // 트리가 비어있으면 NULL 반환
    }

    // root가 p와 q를 분리하는 경우
    if (root->val > p->val && root->val > q->val) {
        return lowestCommonAncestor(root->left, p, q);  // 왼쪽 서브트리로 탐색
    } else if (root->val < p->val && root->val < q->val) {
        return lowestCommonAncestor(root->right, p, q);  // 오른쪽 서브트리로 탐색
    }

    // root가 p와 q의 공통 조상이면 해당 root 반환
    return root;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int* pathToNode(struct TreeNode* root, int val, int* path, int* pathIndex): 특정 값으로 가는 경로를 찾는 함수
int* pathToNode(struct TreeNode* root, int val, int* path, int* pathIndex) {
    if (root == NULL) {
        return NULL;  // 트리가 비어있으면 NULL 반환
    }

    // 현재 노드 값을 경로에 추가
    path[*pathIndex] = root->val;
    (*pathIndex)++;

    // 찾는 값이 현재 노드 값과 같으면 경로 반환
    if (root->val == val) {
        return path;
    }

    // 값이 현재 노드보다 작으면 왼쪽 서브트리 탐색
    if (val < root->val) {
        return pathToNode(root->left, val, path, pathIndex);
    } else {  // 값이 현재 노드보다 크면 오른쪽 서브트리 탐색
        return pathToNode(root->right, val, path, pathIndex);
    }
}


// int* pathToNode(struct TreeNode* root, int val, int* path, int* pathLen): 특정 값까지의 경로를 찾아 반환하는 함수
int* pathToNode(struct TreeNode* root, int val, int* path, int* pathLen) {
    if (!root) { // 트리가 비어있는 경우
        return NULL; // NULL 반환
    }

    // 현재 노드 값을 경로에 추가
    path[*pathLen] = root->val;
    (*pathLen)++;

    if (root->val == val) { // 현재 노드의 값이 찾는 값인 경우
        return path; // 경로 반환
    }

    // 왼쪽 자식에서 경로를 찾기
    if (val < root->val) {
        if (root->left) {
            return pathToNode(root->left, val, path, pathLen);
        }
    } else { // 오른쪽 자식에서 경로를 찾기
        if (root->right) {
            return pathToNode(root->right, val, path, pathLen);
        }
    }

    // 경로에서 현재 노드 제거 (백트래킹)
    (*pathLen)--;
    return NULL; // 값을 찾지 못한 경우 NULL 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// findPaths 함수 선언
void findPaths(struct TreeNode* node, int* path, int pathLen, int** paths, int* pathsCount, int* pathSizes);

// int** allPaths(struct TreeNode* root, int* returnSize, int** returnColumnSizes): 모든 루트-리프 경로를 찾는 함수
int** allPaths(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    int** paths = (int**)malloc(100 * sizeof(int*)); // 최대 100개의 경로 저장 가능 (확장 가능)
    int* path = (int*)malloc(100 * sizeof(int));    // 임시 경로 저장 (최대 100 노드 깊이)
    int* pathSizes = (int*)malloc(100 * sizeof(int)); // 각 경로의 길이 저장
    int pathsCount = 0; // 발견된 경로 수

    findPaths(root, path, 0, paths, &pathsCount, pathSizes);

    *returnSize = pathsCount; // 경로 수 반환
    *returnColumnSizes = pathSizes; // 각 경로의 길이 반환
    free(path); // 임시 경로 메모리 해제

    return paths;
}

// findPaths 함수: 경로를 탐색하고 저장
void findPaths(struct TreeNode* node, int* path, int pathLen, int** paths, int* pathsCount, int* pathSizes) {
    if (!node) {
        return; // 노드가 NULL이면 종료
    }

    path[pathLen] = node->val; // 현재 노드 값을 경로에 추가
    pathLen++;

    if (!node->left && !node->right) { // 리프 노드에 도달한 경우
        paths[*pathsCount] = (int*)malloc(pathLen * sizeof(int)); // 경로를 저장할 메모리 할당
        for (int i = 0; i < pathLen; i++) {
            paths[*pathsCount][i] = path[i];
        }
        pathSizes[*pathsCount] = pathLen; // 현재 경로의 길이 저장
        (*pathsCount)++; // 경로 수 증가
    } else {
        findPaths(node->left, path, pathLen, paths, pathsCount, pathSizes); // 왼쪽 자식으로 재귀 호출
        findPaths(node->right, path, pathLen, paths, pathsCount, pathSizes); // 오른쪽 자식으로 재귀 호출
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 중위 순회로 k번째로 작은 값을 찾는 함수
int kthSmallest(struct TreeNode* root, int k);
void inorder_(struct TreeNode* node, int* count, int* result, int k);

// int kthSmallest(struct TreeNode* root, int k): 이진 검색 트리에서 k번째로 작은 값을 반환
int kthSmallest(struct TreeNode* root, int k) {
    int count = 0; // 현재 방문한 노드 수
    int result = -1; // 결과 값
    inorder_(root, &count, &result, k); // 중위 순회 시작
    return result;
}

// 중위 순회 함수: k번째로 작은 값을 찾음
void inorder_(struct TreeNode* node, int* count, int* result, int k) {
    if (!node || *result != -1) {
        return; // 노드가 NULL이거나 결과를 이미 찾은 경우 종료
    }

    inorder_(node->left, count, result, k); // 왼쪽 서브트리 탐색

    (*count)++; // 현재 노드 방문
    if (*count == k) { // k번째 노드에 도달한 경우
        *result = node->val;
        return;
    }

    inorder_(node->right, count, result, k); // 오른쪽 서브트리 탐색
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int rangeSumBST(struct TreeNode* root, int low, int high): 주어진 범위 [low, high]에 속하는 값들의 합을 계산
int rangeSumBST(struct TreeNode* root, int low, int high) {
    // 1. 트리가 비었으면 0 반환
    if (root == NULL) {
        return 0;
    }
    
    // 2. 현재 노드의 값이 low보다 작으면 왼쪽 서브트리만 탐색 (오른쪽 서브트리는 고려할 필요 없음)
    if (root->val < low) {
        return rangeSumBST(root->right, low, high);
    }
    
    // 3. 현재 노드의 값이 high보다 크면 오른쪽 서브트리만 탐색 (왼쪽 서브트리는 고려할 필요 없음)
    if (root->val > high) {
        return rangeSumBST(root->left, low, high);
    }
    
    // 4. 현재 노드의 값이 범위 내에 있으면, 현재 노드의 값과 왼쪽/오른쪽 서브트리의 값을 더함
    return root->val + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void nodesAtDepth(struct TreeNode* root, int depth, int* result, int* returnSize): 특정 깊이에 위치한 노드들의 값을 배열로 반환 (void 반환형) -> result에 값이 채워짐
void nodesAtDepth(struct TreeNode* root, int depth, int* result, int* returnSize) {
    // 1. 트리가 비었으면 반환
    if (root == NULL) {
        return;
    }
    
    // 2. 깊이가 0이면 현재 노드의 값을 결과 배열에 추가
    if (depth == 0) {
        result[*returnSize] = root->val;
        (*returnSize)++;
        return;
    }
    
    // 3. 왼쪽과 오른쪽 서브트리에서 깊이를 감소시키며 탐색
    nodesAtDepth(root->left, depth - 1, result, returnSize);
    nodesAtDepth(root->right, depth - 1, result, returnSize);
}


// int* nodesAtDepth(struct TreeNode* root, int depth, int* returnSize): 특정 깊이에 위치한 노드들의 값을 배열로 반환
int* nodesAtDepth_(struct TreeNode* root, int depth, int* returnSize) {
    // 1. 트리가 비었으면 빈 배열과 크기 0 반환
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    
    // 2. 재귀적으로 서브트리에서 특정 깊이의 노드 값들을 찾음
    if (depth == 0) {
        int* result = (int*)malloc(sizeof(int));
        result[0] = root->val;
        *returnSize = 1;
        return result;
    }
    
    // 3. 왼쪽과 오른쪽 서브트리에서 깊이를 감소시키며 탐색
    int* leftResult = nodesAtDepth_(root->left, depth - 1, returnSize);
    int leftSize = *returnSize;
    
    int* rightResult = nodesAtDepth_(root->right, depth - 1, returnSize);
    int rightSize = *returnSize;
    
    // 4. 왼쪽과 오른쪽 결과 배열을 합침
    int* result = (int*)malloc((leftSize + rightSize) * sizeof(int));
    
    // 왼쪽 결과 복사
    for (int i = 0; i < leftSize; i++) {
        result[i] = leftResult[i];
    }
    
    // 오른쪽 결과 복사
    for (int i = 0; i < rightSize; i++) {
        result[leftSize + i] = rightResult[i];
    }
    
    // 메모리 해제
    free(leftResult);
    free(rightResult);
    
    *returnSize = leftSize + rightSize;
    
    return result;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 내림차순 순회를 수행하는 헬퍼 함수
void descendingOrderTraversalHelper(struct TreeNode* root, int* result, int* returnSize) {
    if (root == NULL) {
        return;
    }
    
    // 오른쪽 서브트리 순회
    descendingOrderTraversalHelper(root->right, result, returnSize);
    
    // 현재 노드 값을 결과 배열에 추가
    result[*returnSize] = root->val;
    (*returnSize)++;
    
    // 왼쪽 서브트리 순회
    descendingOrderTraversalHelper(root->left, result, returnSize);
}

// int* descendingOrderTraversal(struct TreeNode* root, int* returnSize): 이진 트리를 내림차순으로 순회하여 노드 값을 반환
int* descendingOrderTraversal(struct TreeNode* root, int* returnSize) {
    // 최대 크기를 설정 (예: 트리의 노드 수가 100개 이하일 경우)
    int maxSize = 100;
    int* result = (int*)malloc(maxSize * sizeof(int));  // 결과 배열을 동적으로 할당
    
    *returnSize = 0;  // 결과 배열의 크기 초기화
    
    // 내림차순 순회를 수행
    descendingOrderTraversalHelper(root, result, returnSize);
    
    return result;  // 결과 배열 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// struct TreeNode* mirrorTree(struct TreeNode* root): 이진 트리를 대칭으로 뒤집는 함수
struct TreeNode* mirrorTree(struct TreeNode* root) {
    // 1. 트리가 비었으면 NULL 반환
    if (root == NULL) {
        return NULL;
    }

    // 2. 왼쪽과 오른쪽 자식 노드를 교환
    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // 3. 왼쪽과 오른쪽 서브트리도 재귀적으로 뒤집기
    mirrorTree(root->left);
    mirrorTree(root->right);

    return root;  // 대칭으로 바뀐 트리 반환
}


// struct TreeNode* invertTree(struct TreeNode* root): 이진 트리를 뒤집는 함수
struct TreeNode* invertTree(struct TreeNode* root) {
    // 1. 트리가 비었으면 NULL 반환
    if (root == NULL) {
        return NULL;
    }

    // 2. 왼쪽과 오른쪽 자식의 위치를 바꿈
    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // 3. 왼쪽과 오른쪽 서브트리도 재귀적으로 뒤집기
    invertTree(root->left);
    invertTree(root->right);

    return root;  // 뒤집힌 트리의 루트 노드 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 최소 공통 조상(LCA)을 찾는 함수
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (root == NULL || root == p || root == q) {
        return root;
    }

    // 왼쪽 서브트리에서 LCA를 찾음
    struct TreeNode* left = lowestCommonAncestor(root->left, p, q);
    // 오른쪽 서브트리에서 LCA를 찾음
    struct TreeNode* right = lowestCommonAncestor(root->right, p, q);

    // 왼쪽과 오른쪽에서 모두 LCA가 발견되면 현재 노드가 LCA
    if (left != NULL && right != NULL) {
        return root;
    }

    // 왼쪽 또는 오른쪽에서만 LCA가 발견되면 그 서브트리의 LCA 반환
    return (left != NULL) ? left : right;
}

// LCA에서 target까지의 거리를 계산하는 함수
int distanceFromAncestor(struct TreeNode* node, struct TreeNode* target, int distance) {
    if (node == NULL) {
        return -1;  // 노드가 없으면 -1 반환
    }
    if (node == target) {
        return distance;  // 타겟 노드를 찾으면 현재 거리 반환
    }

    // 왼쪽 서브트리에서 찾기
    int left_distance = distanceFromAncestor(node->left, target, distance + 1);
    if (left_distance != -1) {
        return left_distance;
    }

    // 오른쪽 서브트리에서 찾기
    return distanceFromAncestor(node->right, target, distance + 1);
}

// int distanceBetweenNodes(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q): 두 노드 사이의 거리를 계산하는 함수
int distanceBetweenNodes(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    // LCA 찾기
    struct TreeNode* lca = lowestCommonAncestor(root, p, q);

    // LCA에서 p와 q까지의 거리 계산
    int dist_p = distanceFromAncestor(lca, p, 0);
    int dist_q = distanceFromAncestor(lca, q, 0);

    // 두 거리의 합이 p와 q 사이의 거리
    return dist_p + dist_q;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// helper 함수: 트리가 유효한 BST인지 확인하는 함수 (재귀적 검사)
int isValidBSTHelper(struct TreeNode* node, long long lower, long long upper) {
    if (node == NULL) {
        return 1;  // 노드가 NULL이면 유효한 BST로 간주
    }
    
    if (node->val <= lower || node->val >= upper) {
        return 0;  // 노드 값이 범위 밖에 있으면 유효하지 않음
    }
    
    // 왼쪽 서브트리는 upper를 현재 노드 값으로, 오른쪽 서브트리는 lower를 현재 노드 값으로 설정하여 재귀적으로 검사
    return isValidBSTHelper(node->left, lower, node->val) && isValidBSTHelper(node->right, node->val, upper);
}

// int isValidBST(struct TreeNode* root): 트리가 유효한 BST인지 확인하는 함수
int isValidBST(struct TreeNode* root) {
    return isValidBSTHelper(root, LONG_MIN, LONG_MAX);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 후위 순회 방식으로 오른쪽 서브트리부터 탐색하여 더 큰 값들의 합을 갱신하는 DFS 함수
int dfs(struct TreeNode* node, int sum_greater) {
    if (node == NULL) {
        return sum_greater;  // 노드가 NULL이면 합을 그대로 반환
    }
    
    // 오른쪽 서브트리부터 탐색
    sum_greater = dfs(node->right, sum_greater);

    // 현재 노드의 값에 더 큰 값들의 합을 더함
    node->val += sum_greater;

    // 왼쪽 서브트리로 진행, sum_greater는 현재 노드의 값
    return dfs(node->left, node->val);
}

// struct TreeNode* sumOfGreaterNodes(struct TreeNode* root): 트리의 각 노드를 해당 노드보다 큰 노드들의 값의 합으로 갱신
struct TreeNode* sumOfGreaterNodes(struct TreeNode* root) {
    dfs(root, 0);  // DFS 탐색을 시작
    return root;  // 갱신된 트리 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// helper 함수: 현재 노드에서 시작하는 경로 합과, 전체 트리에서 가능한 최대 경로 합을 구함
int dfs(struct TreeNode* node, int* max_sum) {
    if (node == NULL) {
        return 0;  // 노드가 없으면 경로 합은 0
    }
    
    // 왼쪽과 오른쪽 서브트리에서 최대 경로 합을 구함
    int left_single = dfs(node->left, max_sum);
    int right_single = dfs(node->right, max_sum);
    
    // 현재 노드를 포함하는 경로에서 단일 경로 합 계산
    int single_path = (left_single > 0 ? left_single : 0) + node->val;
    int max_single = (right_single > 0 ? right_single : 0) + node->val;
    
    // 현재 노드를 포함한 최대 경로 합 계산
    int current_max_path = left_single + node->val + right_single;
    if (current_max_path > *max_sum) {
        *max_sum = current_max_path;  // 최대 경로 합을 갱신
    }
    
    // return the maximum single path sum, which can be used for the parent path
    return (single_path > max_single) ? single_path : max_single;
}

// int maxPathSum(struct TreeNode* root): 트리에서 가장 큰 경로 합을 구하는 함수
int maxPathSum(struct TreeNode* root) {
    int max_sum = INT_MIN;  // 초기 최대 경로 합을 음의 무한대 값으로 설정
    dfs(root, &max_sum);  // DFS 탐색을 시작하고, max_sum을 갱신
    return max_sum;  // 최종적으로 계산된 최대 경로 합 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 범위 내에 있는 노드들의 값을 저장하는 배열 크기를 추적하기 위한 변수
int size = 0;

// DFS로 트리를 탐색하면서 주어진 범위 [low, high]에 포함되는 값들을 배열에 저장
void dfs__(struct TreeNode* node, int low, int high, int* result) {
    if (node == NULL) {
        return;  // 노드가 없다면 종료
    }
    
    // 현재 노드 값이 범위 내에 있으면 결과 배열에 추가
    if (low <= node->val && node->val <= high) {
        result[size++] = node->val;  // 배열에 추가하고 크기 증가
    }
    
    // 왼쪽 서브트리 탐색 (현재 노드 값이 low보다 크면 왼쪽으로 가야함)
    if (node->val > low) {
        dfs__(node->left, low, high, result);
    }
    
    // 오른쪽 서브트리 탐색 (현재 노드 값이 high보다 작으면 오른쪽으로 가야함)
    if (node->val < high) {
        dfs__(node->right, low, high, result);
    }
}

// int* nodesInRange(struct TreeNode* root, int low, int high, int* returnSize): 주어진 범위 [low, high]에 속하는 노드들의 값을 반환하는 함수
int* nodesInRange(struct TreeNode* root, int low, int high, int* returnSize) {
    // 결과를 저장할 배열 할당 (임시로 1000개로 크기 설정)
    int* result = (int*)malloc(1000 * sizeof(int));
    size = 0;  // 배열 크기 초기화
    
    // DFS 탐색 시작
    dfs__(root, low, high, result);
    
    // 반환할 크기 설정
    *returnSize = size;
    
    return result;  // 범위 내의 값들 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// bool hasPathSum(struct TreeNode* root, int sum): 경로 합이 sum과 일치하는지 확인하는 함수
bool hasPathSum(struct TreeNode* root, int sum) {
    if (root == NULL) {
        return false;  // 트리가 비어 있으면 False 반환
    }

    // 리프 노드에 도달한 경우, 현재 노드 값이 sum과 일치하는지 확인
    if (root->left == NULL && root->right == NULL) {
        return root->val == sum;
    }

    // 리프 노드가 아니라면, sum에서 현재 노드의 값을 빼고 왼쪽, 오른쪽 자식으로 재귀 호출
    sum -= root->val;
    return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// struct TreeNode* inorderSuccessor(struct TreeNode* root, struct TreeNode* p): p 노드의 중위 순회 후속 노드를 찾는 함수
struct TreeNode* inorderSuccessor(struct TreeNode* root, struct TreeNode* p) {
    if (root == NULL) {
        return NULL;  // 트리가 비어 있으면 NULL 반환
    }
    
    struct TreeNode* successor = NULL;  // 후속 노드를 저장할 변수
    
    // 트리를 탐색하여 p 노드의 후속 노드를 찾음
    while (root != NULL) {
        if (p->val < root->val) {
            successor = root;  // 현재 노드를 후속 후보로 설정
            root = root->left;  // 왼쪽 서브트리로 이동하여 더 작은 값을 찾음
        } else {
            root = root->right;  // p 노드의 값이 현재 노드보다 크면 오른쪽 서브트리로 이동
        }
    }

    return successor;  // p의 중위 순회 후속 노드 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int isChildSum(struct TreeNode* root): 트리가 자식 노드들의 합 규칙을 만족하는지 확인하는 함수
int isChildSum(struct TreeNode* root) {
    // 트리가 비어 있거나 리프 노드일 경우 True 반환
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return 1;  // 1은 True
    }

    // 왼쪽 자식과 오른쪽 자식의 값을 구합니다. 자식이 없으면 0으로 처리.
    int left_val = (root->left != NULL) ? root->left->val : 0;
    int right_val = (root->right != NULL) ? root->right->val : 0;

    // 현재 노드의 값이 왼쪽 + 오른쪽 자식 값보다 크거나 같은지 확인하고,
    // 왼쪽과 오른쪽 자식 노드들에 대해서도 재귀적으로 검사
    if (root->val >= left_val + right_val &&
        isChildSum(root->left) && isChildSum(root->right)) {
        return 1;  // 1은 True
    }

    return 0;  // 0은 False
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// struct TreeNode* sortedArrayToBST(int* nums, int start, int end): 정렬된 배열을 이진 검색 트리(BST)로 변환하는 함수
struct TreeNode* sortedArrayToBST(int* nums, int start, int end) {
    if (start > end) {
        return NULL;  // 배열이 비어 있으면 NULL 반환
    }

    // 배열의 중간값을 선택하여 루트 노드를 생성
    int mid = (start + end) / 2;
    struct TreeNode* root = newNode(nums[mid]);

    // 중간값을 제외한 왼쪽 절반과 오른쪽 절반을 재귀적으로 BST로 변환
    root->left = sortedArrayToBST(nums, start, mid - 1);  // 왼쪽 절반
    root->right = sortedArrayToBST(nums, mid + 1, end);   // 오른쪽 절반

    return root;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int isIdentical(struct TreeNode* root1, struct TreeNode* root2): 두 트리가 동일한지 확인하는 함수
int isIdentical(struct TreeNode* root1, struct TreeNode* root2) {
    // 두 트리가 모두 NULL이면 동일한 트리이므로 TRUE 반환
    if (!root1 && !root2) {
        return 1; // TRUE
    }

    // 두 트리 중 하나만 NULL이면 동일하지 않으므로 FALSE 반환
    if (!root1 || !root2) {
        return 0; // FALSE
    }

    // 현재 노드의 값이 같고, 왼쪽과 오른쪽 서브트리가 동일한지 재귀적으로 확인
    return (root1->val == root2->val) && isIdentical(root1->left, root2->left) && isIdentical(root1->right, root2->right);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 트리의 직경을 구하는 함수 (DFS를 사용)
int diameter = 0;  // 직경을 계산할 변수

// 트리의 깊이를 구하는 함수 (DFS)
int dfs___(struct TreeNode* node) {
    if (!node) {
        return 0;  // 노드가 NULL이면 깊이는 0
    }

    // 왼쪽과 오른쪽 서브트리의 깊이를 구함
    int left_depth = dfs___(node->left);
    int right_depth = dfs___(node->right);

    // 트리의 직경은 왼쪽 서브트리 깊이 + 오른쪽 서브트리 깊이
    diameter = (diameter > left_depth + right_depth) ? diameter : (left_depth + right_depth);

    // 현재 노드에서 가장 큰 깊이를 반환 (1 + 왼쪽/오른쪽 서브트리 깊이)
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
}

// int diameterOfBinaryTree(struct TreeNode* root): 트리의 직경을 구하는 함수
int diameterOfBinaryTree(struct TreeNode* root) {
    diameter = 0;  // 직경 초기화
    dfs___(root);  // DFS를 시작하여 트리의 직경을 계산
    return diameter;  // 계산된 직경 반환
}