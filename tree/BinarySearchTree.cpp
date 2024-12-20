/*
TreeNode* insert(TreeNode* root, int val): 이진 탐색 트리에 값을 삽입하는 함수
TreeNode* search(TreeNode* root, int val): 이진 탐색 트리에서 값을 검색하는 함수
-bool isValueInBST(TreeNode* root, int val): 이진 탐색 트리에서 특정 값이 존재하는지 확인하는 함수
TreeNode* findMin(TreeNode* root): 이진 탐색 트리에서 최솟값을 찾는 함수
TreeNode* findMax(TreeNode* root): 이진 탐색 트리에서 최댓값을 찾는 함수
TreeNode* deleteNode(TreeNode* root, int val): 트리에서 값을 삭제하는 함수
void inorder(TreeNode* root): 중위 순회를 수행하는 함수 (좌 -> 노드 -> 우)
void preorder(TreeNode* root): 전위 순회를 수행하는 함수 (노드 -> 좌 -> 우)
void postorder(TreeNode* root): 후위 순회를 수행하는 함수 (좌 -> 우 -> 노드)
-vector<int> postorderTraversal(TreeNode* root): 후위 순회로 트리의 값을 리스트에 저장하는 함수
int height(TreeNode* root): 트리의 높이를 계산하는 함수
bool isBalanced(TreeNode* root): 트리가 균형 잡혀 있는지 확인하는 함수
int depth(TreeNode* root, int val, int level): 주어진 값이 트리에서 몇 번째 깊이에 있는지 찾는 함수
-int depth2(TreeNode* root, int val): 주어진 값이 트리에서 몇 번째 깊이에 있는지 찾는 함수
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q): 두 노드 p와 q의 최저 공통 조상을 찾는 함수
vector<int> pathToNode(TreeNode* root, int val): 특정 값으로 가는 경로를 찾는 함수
-vector<int> pathToNode2(TreeNode* root, int val, vector<int>& path): 특정 값까지의 경로를 찾아 반환하는 함수
vector<vector<int>> allPaths(TreeNode* root): 이진 트리의 모든 루트-리프 경로를 반환
int kthSmallest(TreeNode* root, int k): 이진 검색 트리에서 k번째로 작은 값을 반환
int rangeSumBST(TreeNode* root, int low, int high): 이진 검색 트리에서 주어진 범위 [low, high]에 속하는 값들의 합을 계산
void nodesAtDepth(TreeNode* root, int depth, int* result, int* returnSize): 특정 깊이에 위치한 노드들의 값을 배열로 반환
int* nodesAtDepth(TreeNode* root, int depth, int* returnSize): 특정 깊이에 위치한 노드들의 값을 동적 배열로 반환
vector<int> descendingOrderTraversal(TreeNode* root): 이진 트리를 내림차순으로 순회하여 노드 값을 반환
TreeNode* mirrorTree(TreeNode* root): 이진 트리를 대칭으로 뒤집는 함수
TreeNode* invertTree(TreeNode* root): 이진 트리를 뒤집는 함수
int distanceBetweenNodes(TreeNode* root, TreeNode* p, TreeNode* q): 두 노드 사이의 거리를 계산하는 함수
int isValidBST(TreeNode* root): 트리가 유효한 이진 검색 트리(BST)인지 확인하는 함수
TreeNode* sumOfGreaterNodes(TreeNode* root): 트리의 각 노드를 해당 노드보다 큰 노드들의 값의 합으로 갱신하는 함수
int maxPathSum(TreeNode* root): 트리에서 가장 큰 경로 합을 구하는 함수
int* nodesInRange(TreeNode* root, int low, int high, int* returnSize): 주어진 범위 [low, high]에 속하는 노드들의 값을 반환하는 함수
bool hasPathSum(TreeNode* root, int sum): 경로 합이 주어진 값과 일치하는지 확인하는 함수
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p): p 노드의 중위 순회 후속 노드를 찾는 함수
int isChildSum(TreeNode* root): 트리가 자식 노드들의 합 규칙을 만족하는지 확인하는 함수
TreeNode* sortedArrayToBST(int* nums, int start, int end): 정렬된 배열을 이진 검색 트리(BST)로 변환하는 함수
int isIdentical(TreeNode* root1, TreeNode* root2): 두 트리가 동일한지 확인하는 함수
diameterOfBinaryTree(TreeNode* root): 트리의 직경을 구하는 함수
*/


#include <iostream>
#include <vector>

using namespace std;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TreeNode* insert(TreeNode* root, int val): 이진 탐색 트리에 값을 삽입하는 함수
// 주어진 트리에서 val 값을 적절한 위치에 삽입
TreeNode* insert(TreeNode* root, int val) {
    // 루트가 비어있으면 새로운 노드를 생성하여 반환
    if (root == nullptr) {
        return new TreeNode(val);
    }

    // 삽입할 값이 현재 노드의 값보다 작으면 왼쪽 서브트리에 삽입
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else {  // 삽입할 값이 현재 노드의 값보다 크면 오른쪽 서브트리에 삽입
        root->right = insert(root->right, val);
    }

    // 삽입이 완료된 후, 변경된 트리의 루트를 반환
    return root;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TreeNode* search(TreeNode* root, int val): 이진 탐색 트리에서 값을 검색하는 함수
// 주어진 트리에서 val 값이 있는 노드를 찾으면 그 노드를 반환, 없으면 NULL 반환
TreeNode* search(TreeNode* root, int val) {
    // 루트가 NULL이거나, 현재 노드의 값이 val와 같으면 해당 노드 반환
    if (root == nullptr || root->val == val) {
        return root;
    }

    // 찾고자 하는 값이 현재 노드의 값보다 작으면 왼쪽 서브트리로 이동
    if (val < root->val) {
        return search(root->left, val);
    }

    // 찾고자 하는 값이 현재 노드의 값보다 크면 오른쪽 서브트리로 이동
    return search(root->right, val);
}


// bool isValueInBST(TreeNode* root, int val): 이진 탐색 트리에서 특정 값이 존재하는지 확인하는 함수
// 주어진 트리에서 val 값이 존재하면 true, 아니면 false를 반환
bool isValueInBST(TreeNode* root, int val) {
    // 노드가 NULL이면 값이 존재하지 않음
    if (root == nullptr) {
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
// TreeNode* findMin(TreeNode* root): 이진 탐색 트리에서 최솟값을 찾는 함수
// 주어진 트리에서 최솟값을 가지는 노드를 반환
TreeNode* findMin(TreeNode* root) {
    // 왼쪽 자식 노드가 있을 때까지 왼쪽으로 이동
    while (root != nullptr && root->left != nullptr) {
        root = root->left;
    }
    // 최솟값을 가진 노드를 반환
    return root;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TreeNode* findMax(TreeNode* root): 이진 탐색 트리에서 최댓값을 찾는 함수
// 주어진 트리에서 최댓값을 가지는 노드를 반환
TreeNode* findMax(TreeNode* root) {
    // 오른쪽 자식 노드가 있을 때까지 오른쪽으로 이동
    while (root != nullptr && root->right != nullptr) {
        root = root->right;
    }
    // 최댓값을 가진 노드를 반환
    return root;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TreeNode* deleteNode(TreeNode* root, int val): 트리에서 값을 삭제하는 함수
// 주어진 트리에서 val 값을 가진 노드를 삭제하고, 변경된 트리의 루트를 반환
TreeNode* deleteNode(TreeNode* root, int val) {
    // 트리가 비어있으면 값을 삭제할 수 없으므로 그대로 반환
    if (root == nullptr) {
        return root;
    }

    // 삭제할 값이 현재 노드 값보다 작으면 왼쪽 서브트리에서 삭제
    if (val < root->val) {
        root->left = deleteNode(root->left, val);
    } 
    // 삭제할 값이 현재 노드 값보다 크면 오른쪽 서브트리에서 삭제
    else if (val > root->val) {
        root->right = deleteNode(root->right, val);
    }
    // 현재 노드가 삭제할 노드일 경우
    else {
        // 왼쪽 자식이 없으면 오른쪽 자식을 대체
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;  // 현재 노드 메모리 해제
            return temp;
        }
        // 오른쪽 자식이 없으면 왼쪽 자식을 대체
        else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;  // 현재 노드 메모리 해제
            return temp;
        }

        // 두 자식이 모두 있을 경우
        // 오른쪽 서브트리에서 최솟값을 찾아 현재 노드의 값으로 대체
        TreeNode* minNode = findMin(root->right);
        root->val = minNode->val;
        // 오른쪽 서브트리에서 최솟값을 삭제
        root->right = deleteNode(root->right, minNode->val);
    }

    return root;  // 변경된 트리의 루트를 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void inorder(TreeNode* root): 중위 순회를 수행하는 함수 (좌 -> 노드 -> 우)
void inorder(TreeNode* root) {
    if (root != nullptr) {  // 루트가 비어있지 않으면
        inorder(root->left);  // 왼쪽 자식 탐색
        cout << root->val << " ";  // 현재 노드 출력
        inorder(root->right);  // 오른쪽 자식 탐색
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void preorder(TreeNode* root): 전위 순회를 수행하는 함수 (노드 -> 좌 -> 우)
void preorder(TreeNode* root) {
    if (root != nullptr) {  // 루트가 비어있지 않으면
        cout << root->val << " ";  // 현재 노드 출력
        preorder(root->left);  // 왼쪽 자식 탐색
        preorder(root->right);  // 오른쪽 자식 탐색
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void postorder(TreeNode* root): 후위 순회를 수행하는 함수 (좌 -> 우 -> 노드)
void postorder(TreeNode* root) {
    if (root != nullptr) {  // 루트가 NULL이 아니면
        postorder(root->left);  // 왼쪽 자식부터 탐색
        postorder(root->right);  // 오른쪽 자식 탐색
        cout << root->val << " ";  // 현재 노드 출력
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 후위 순회 (좌 -> 우 -> 노드)로 트리 값을 배열에 저장하는 헬퍼 함수
void postorder2(TreeNode* node, vector<int>& result) {
    if (node == nullptr) {  // 노드가 비어 있으면 종료
        return;
    }

    postorder2(node->left, result);  // 왼쪽 서브트리 순회
    postorder2(node->right, result);  // 오른쪽 서브트리 순회
    result.push_back(node->val);  // 현재 노드 값을 결과 배열에 저장
}

// vector<int> postorderTraversal(TreeNode* root): 후위 순회로 트리의 값을 리스트에 저장하는 함수
// 후위 순회 (좌 -> 우 -> 노드)로 트리의 값을 리스트에 저장하고, 결과 배열을 반환
vector<int> postorderTraversal(TreeNode* root) {
    vector<int> result;  // 결과를 저장할 벡터
    postorder2(root, result);  // 후위 순회 시작
    return result;  // 후위 순회 결과 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int height(TreeNode* root): 트리의 높이를 계산하는 함수
int height(TreeNode* root) {
    if (root == nullptr) {  // 노드가 비어 있으면 높이는 0
        return 0;
    }

    // 왼쪽과 오른쪽 서브트리의 높이를 계산하고, 더 큰 값을 선택하여 1을 더한 후 반환
    int left_height = height(root->left);  // 왼쪽 서브트리 높이
    int right_height = height(root->right);  // 오른쪽 서브트리 높이

    return 1 + max(left_height, right_height);  // 더 큰 높이에 1을 더한 값 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 트리의 높이를 계산하고 균형을 확인하는 함수
int getHeight(TreeNode* root) {
    if (root == nullptr) {  // 노드가 NULL이면 높이는 0
        return 0;
    }

    // 왼쪽과 오른쪽 서브트리의 높이를 계산
    int left_height = getHeight(root->left);
    int right_height = getHeight(root->right);

    // 서브트리 높이 차이가 2 이상이면 균형이 맞지 않음
    if (left_height == -1 || right_height == -1 || abs(left_height - right_height) > 1) {
        return -1;  // 균형이 맞지 않으면 -1 반환
    }

    // 균형이 맞으면 더 큰 서브트리 높이에 1을 더한 값 반환
    return 1 + max(left_height, right_height);
}

// bool isBalanced(TreeNode* root): 트리가 균형 잡혀 있는지 확인하는 함수
bool isBalanced(TreeNode* root) {
    return getHeight(root) != -1;  // 트리 높이가 -1이면 불균형, 아니면 균형
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int depth(TreeNode* root, int val, int level): 주어진 값이 트리에서 몇 번째 깊이에 있는지 찾는 함수
// 주어진 값이 트리에서 몇 번째 깊이에 있는지 반환. 값이 없으면 -1을 반환
int depth(TreeNode* root, int val, int level) {
    if (root == nullptr) {  // 트리가 비어있으면 -1 반환
        return -1;
    }
    if (root->val == val) {  // 값이 현재 노드와 일치하면 깊이(level) 반환
        return level;
    }
    if (val < root->val) {  // 값이 현재 노드보다 작으면 왼쪽 서브트리로 탐색
        return depth(root->left, val, level + 1);
    } else {  // 값이 현재 노드보다 크면 오른쪽 서브트리로 탐색
        return depth(root->right, val, level + 1);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int depth2(TreeNode* root, int val): 주어진 값이 트리에서 몇 번째 깊이에 있는지 찾는 함수
// 주어진 값이 트리에서 몇 번째 깊이에 있는지 반환. 값이 없으면 -1을 반환
int depth2(TreeNode* root, int val) {
    if (root == nullptr) {  // 트리가 비어있으면 -1 반환
        return -1;
    }
    if (root->val == val) {  // 값이 현재 노드와 일치하면 깊이 0 반환
        return 0;
    }

    // 값이 현재 노드보다 작으면 왼쪽 서브트리 탐색
    if (val < root->val) {
        int left_depth = depth2(root->left, val);
        if (left_depth == -1) {  // 왼쪽 서브트리에서 값을 찾지 못했으면 -1 반환
            return -1;
        }
        return left_depth + 1;  // 왼쪽 서브트리에서 값을 찾았으면 깊이에 1을 더해서 반환
    } 
    // 값이 현재 노드보다 크면 오른쪽 서브트리 탐색
    else {
        int right_depth = depth2(root->right, val);
        if (right_depth == -1) {  // 오른쪽 서브트리에서 값을 찾지 못했으면 -1 반환
            return -1;
        }
        return right_depth + 1;  // 오른쪽 서브트리에서 값을 찾았으면 깊이에 1을 더해서 반환
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q): 두 노드 p와 q의 최저 공통 조상을 찾는 함수
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr) {
        return nullptr;  // 트리가 비어있으면 NULL 반환
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
// vector<int> pathToNode(TreeNode* root, int val): 특정 값으로 가는 경로를 찾는 함수
// 주어진 트리에서 특정 값으로 가는 경로를 찾고, 그 경로를 반환하는 함수
vector<int> pathToNode(TreeNode* root, int val) {
    vector<int> path;  // 경로를 저장할 벡터 선언

    // 현재 트리가 비어있으면 빈 경로 반환
    if (root == nullptr) {
        return path;  // 트리가 비었으므로 빈 벡터 반환
    }

    // 현재 노드 값을 경로에 추가
    path.push_back(root->val);  // 현재 노드 값을 경로에 추가

    // 찾고자 하는 값이 현재 노드와 일치하는지 확인
    if (root->val == val) {
        return path;  // 값이 일치하면 경로 반환
    }

    // 찾고자 하는 값이 현재 노드의 값보다 작은 경우 왼쪽 서브트리로 탐색
    if (val < root->val) {
        // 왼쪽 서브트리에서 경로를 찾음
        vector<int> leftPath = pathToNode(root->left, val);  // 왼쪽 서브트리 탐색

        // 왼쪽 서브트리에서 값을 찾았다면, 그 경로를 이어서 반환
        if (!leftPath.empty()) {  // 값이 존재하면 경로가 비지 않음
            path.insert(path.end(), leftPath.begin(), leftPath.end());  // 경로를 이어서 반환
            return path;
        }
    } else {  // 찾고자 하는 값이 현재 노드보다 큰 경우 오른쪽 서브트리로 탐색
        // 오른쪽 서브트리에서 경로를 찾음
        vector<int> rightPath = pathToNode(root->right, val);  // 오른쪽 서브트리 탐색

        // 오른쪽 서브트리에서 값을 찾았다면, 그 경로를 이어서 반환
        if (!rightPath.empty()) {  // 값이 존재하면 경로가 비지 않음
            path.insert(path.end(), rightPath.begin(), rightPath.end());  // 경로를 이어서 반환
            return path;
        }
    }

    // 값이 없는 경우 빈 벡터를 반환
    return {};  // 값이 없으면 빈 벡터 반환
}


// vector<int> pathToNode2(TreeNode* root, int val, vector<int>& path): 특정 값까지의 경로를 찾아 반환하는 함수
vector<int> pathToNode2(TreeNode* root, int val, vector<int>& path) {
    if (!root) {  // 트리가 비어있는 경우
        return {};  // 빈 벡터 반환
    }

    // 현재 노드 값을 경로에 추가
    path.push_back(root->val);  // 현재 노드의 값 추가

    if (root->val == val) {  // 현재 노드의 값이 찾는 값인 경우
        return path;  // 경로 반환
    }

    // 왼쪽 자식에서 경로를 찾기
    if (val < root->val) {
        if (root->left) {
            vector<int> leftPath = pathToNode2(root->left, val, path);  // 왼쪽 서브트리에서 경로 찾기
            if (!leftPath.empty()) {
                return leftPath;  // 경로를 찾으면 반환
            }
        }
    } else {  // 오른쪽 자식에서 경로를 찾기
        if (root->right) {
            vector<int> rightPath = pathToNode2(root->right, val, path);  // 오른쪽 서브트리에서 경로 찾기
            if (!rightPath.empty()) {
                return rightPath;  // 경로를 찾으면 반환
            }
        }
    }

    // 경로에서 현재 노드 제거 (백트래킹)
    path.pop_back();  // 경로에서 마지막 노드 제거
    return {};  // 값을 찾지 못한 경우 빈 벡터 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// findPaths 함수: 이진 트리의 모든 루트-리프 경로를 탐색하여 저장
void findPaths(TreeNode* node, vector<int>& path, vector<vector<int>>& paths) {
    if (!node) return; // 노드가 NULL이면 종료

    path.push_back(node->val); // 현재 노드 값을 경로에 추가

    if (!node->left && !node->right) {
        paths.push_back(path); // 리프 노드일 경우 경로를 저장
    } else {
        findPaths(node->left, path, paths);  // 왼쪽 자식으로 재귀 호출
        findPaths(node->right, path, paths); // 오른쪽 자식으로 재귀 호출
    }

    path.pop_back(); // 재귀 호출에서 돌아오면 경로에서 현재 노드 제거
}

// vector<vector<int>> allPaths(TreeNode* root): 이진 트리의 모든 루트-리프 경로를 반환
vector<vector<int>> allPaths(TreeNode* root) {
    vector<vector<int>> paths; // 모든 경로를 저장할 벡터
    vector<int> path;          // 임시 경로를 저장할 벡터
    findPaths(root, path, paths);
    return paths;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 중위 순회를 수행하여 k번째로 작은 값을 찾는 헬퍼 함수
void inorderTraversal(TreeNode* node, int& count, int& result, int k) {
    if (!node || result != -1) {
        return; // 노드가 NULL이거나 이미 결과를 찾은 경우 종료
    }

    // 왼쪽 서브트리 방문
    inorderTraversal(node->left, count, result, k);

    // 현재 노드 방문
    count++;
    if (count == k) { // k번째 노드에 도달한 경우
        result = node->val;
        return;
    }

    // 오른쪽 서브트리 방문
    inorderTraversal(node->right, count, result, k);
}

// int kthSmallest(TreeNode* root, int k): 이진 검색 트리에서 k번째로 작은 값을 반환
int kthSmallest(TreeNode* root, int k) {
    int count = 0;   // 현재 방문한 노드 수
    int result = -1; // 결과 값 초기화
    inorderTraversal(root, count, result, k); // 중위 순회 수행
    return result;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int rangeSumBST(TreeNode* root, int low, int high): 이진 검색 트리에서 주어진 범위 [low, high]에 속하는 값들의 합을 계산
int rangeSumBST(TreeNode* root, int low, int high) {
    // 1. 트리가 비었으면 0 반환
    if (root == nullptr) {
        return 0;
    }
    
    // 2. 현재 노드의 값이 low보다 작으면 오른쪽 서브트리만 탐색
    if (root->val < low) {
        return rangeSumBST(root->right, low, high);
    }
    
    // 3. 현재 노드의 값이 high보다 크면 왼쪽 서브트리만 탐색
    if (root->val > high) {
        return rangeSumBST(root->left, low, high);
    }
    
    // 4. 현재 노드의 값이 범위 내에 있으면, 현재 노드의 값과 왼쪽/오른쪽 서브트리의 값을 더함
    return root->val + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void nodesAtDepth(TreeNode* root, int depth, int* result, int* returnSize): 특정 깊이에 위치한 노드들의 값을 배열로 반환
void nodesAtDepth(TreeNode* root, int depth, int* result, int* returnSize) {
    // 1. 트리가 비었으면 반환
    if (root == nullptr) {
        return;
    }

    // 2. 깊이가 0이면 현재 노드의 값을 결과 배열에 추가
    if (depth == 0) {
        result[*returnSize] = root->val; // 결과 배열에 값 추가
        (*returnSize)++;                 // 결과 크기 증가
        return;
    }

    // 3. 왼쪽과 오른쪽 서브트리에서 깊이를 감소시키며 탐색
    nodesAtDepth(root->left, depth - 1, result, returnSize);
    nodesAtDepth(root->right, depth - 1, result, returnSize);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int* nodesAtDepth(TreeNode* root, int depth, int* returnSize): 특정 깊이에 위치한 노드들의 값을 동적 배열로 반환
int* nodesAtDepth(TreeNode* root, int depth, int* returnSize) {
    // 1. 트리가 비었으면 빈 배열과 크기 0 반환
    if (root == nullptr) {
        *returnSize = 0;
        return nullptr;
    }

    // 2. 재귀적으로 서브트리에서 특정 깊이의 노드 값들을 찾음
    if (depth == 0) {
        int* result = new int[1]; // 결과를 저장할 배열 할당
        result[0] = root->val;    // 현재 노드 값을 추가
        *returnSize = 1;          // 결과 크기를 1로 설정
        return result;
    }

    // 3. 왼쪽과 오른쪽 서브트리에서 깊이를 감소시키며 탐색
    int leftSize = 0, rightSize = 0; 
    int* leftResult = nodesAtDepth(root->left, depth - 1, &leftSize);
    int* rightResult = nodesAtDepth(root->right, depth - 1, &rightSize);

    // 4. 왼쪽과 오른쪽 결과 배열을 합침
    int* result = new int[leftSize + rightSize]; // 결과 배열 할당

    // 왼쪽 결과 복사
    for (int i = 0; i < leftSize; i++) {
        result[i] = leftResult[i];
    }

    // 오른쪽 결과 복사
    for (int i = 0; i < rightSize; i++) {
        result[leftSize + i] = rightResult[i];
    }

    // 메모리 해제
    delete[] leftResult;
    delete[] rightResult;

    *returnSize = leftSize + rightSize; // 전체 결과 크기 설정

    return result; // 결과 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 내림차순 순회를 수행하는 헬퍼 함수
void descendingOrderTraversalHelper(TreeNode* root, vector<int>& result) {
    if (root == nullptr) {
        return; // 트리가 비어 있으면 종료
    }

    // 오른쪽 서브트리 순회
    descendingOrderTraversalHelper(root->right, result);

    // 현재 노드 값을 결과 벡터에 추가
    result.push_back(root->val);

    // 왼쪽 서브트리 순회
    descendingOrderTraversalHelper(root->left, result);
}

// vector<int> descendingOrderTraversal(TreeNode* root): 이진 트리를 내림차순으로 순회하여 노드 값을 반환
vector<int> descendingOrderTraversal(TreeNode* root) {
    vector<int> result; // 결과 값을 저장할 벡터
    descendingOrderTraversalHelper(root, result); // 내림차순 순회 시작
    return result; // 결과 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TreeNode* mirrorTree(TreeNode* root): 이진 트리를 대칭으로 뒤집는 함수
TreeNode* mirrorTree(TreeNode* root) {
    // 1. 트리가 비었으면 NULL 반환
    if (root == nullptr) {
        return nullptr;
    }

    // 2. 왼쪽과 오른쪽 자식 노드를 교환
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // 3. 왼쪽과 오른쪽 서브트리도 재귀적으로 뒤집기
    mirrorTree(root->left);
    mirrorTree(root->right);

    return root;  // 대칭으로 바뀐 트리 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TreeNode* invertTree(TreeNode* root): 이진 트리를 뒤집는 함수
TreeNode* invertTree(TreeNode* root) {
    // 1. 트리가 비었으면 NULL 반환
    if (root == nullptr) {
        return nullptr;
    }

    // 2. 왼쪽과 오른쪽 자식의 위치를 바꿈
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // 3. 왼쪽과 오른쪽 서브트리도 재귀적으로 뒤집기
    invertTree(root->left);
    invertTree(root->right);

    return root;  // 뒤집힌 트리의 루트 노드 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// lowestCommonAncestor 함수: 두 노드 p와 q의 최소 공통 조상(LCA)을 찾는 함수
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // 1. root가 NULL이거나 root가 p 또는 q라면 root를 반환
    if (root == nullptr || root == p || root == q) {
        return root;
    }

    // 2. 왼쪽 서브트리에서 LCA 찾기
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    // 3. 오른쪽 서브트리에서 LCA 찾기
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    // 4. 왼쪽과 오른쪽 서브트리에서 모두 LCA가 발견되면 root가 LCA
    if (left != nullptr && right != nullptr) {
        return root;
    }

    // 5. 왼쪽 또는 오른쪽에서만 LCA가 발견되면 그 서브트리의 LCA 반환
    return (left != nullptr) ? left : right;
}

// distanceFromAncestor 함수: LCA에서 target까지의 거리를 계산하는 함수
int distanceFromAncestor(TreeNode* node, TreeNode* target, int distance) {
    // 1. 노드가 NULL이면 -1 반환
    if (node == nullptr) {
        return -1;
    }

    // 2. 타겟 노드를 찾으면 현재 거리 반환
    if (node == target) {
        return distance;
    }

    // 3. 왼쪽 서브트리에서 target 찾기
    int left_distance = distanceFromAncestor(node->left, target, distance + 1);
    if (left_distance != -1) {
        return left_distance;  // 왼쪽에서 찾으면 그 거리 반환
    }

    // 4. 오른쪽 서브트리에서 target 찾기
    return distanceFromAncestor(node->right, target, distance + 1);
}

// int distanceBetweenNodes(TreeNode* root, TreeNode* p, TreeNode* q): 두 노드 사이의 거리를 계산하는 함수
int distanceBetweenNodes(TreeNode* root, TreeNode* p, TreeNode* q) {
    // 1. LCA 찾기
    TreeNode* lca = lowestCommonAncestor(root, p, q);

    // 2. LCA에서 p와 q까지의 거리 계산
    int dist_p = distanceFromAncestor(lca, p, 0);
    int dist_q = distanceFromAncestor(lca, q, 0);

    // 3. 두 거리의 합이 p와 q 사이의 거리
    return dist_p + dist_q;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// helper 함수: 트리가 유효한 BST인지 확인하는 함수 (재귀적 검사)
int isValidBSTHelper(TreeNode* node, long long lower, long long upper) {
    // 1. 노드가 NULL이면 유효한 BST로 간주
    if (node == nullptr) {
        return 1;
    }
    
    // 2. 현재 노드의 값이 유효한 범위 내에 있는지 확인
    if (node->val <= lower || node->val >= upper) {
        return 0;  // 노드 값이 범위 밖에 있으면 유효하지 않음
    }
    
    // 3. 왼쪽 서브트리는 upper를 현재 노드 값으로, 오른쪽 서브트리는 lower를 현재 노드 값으로 설정하여 재귀적으로 검사
    return isValidBSTHelper(node->left, lower, node->val) && isValidBSTHelper(node->right, node->val, upper);
}

// int isValidBST(TreeNode* root): 트리가 유효한 이진 검색 트리(BST)인지 확인하는 함수
int isValidBST(TreeNode* root) {
    // 1. 초기 범위는 LONG_MIN부터 LONG_MAX까지 설정하여 BST 규칙을 확인
    return isValidBSTHelper(root, LONG_MIN, LONG_MAX);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 후위 순회 방식으로 오른쪽 서브트리부터 탐색하여 더 큰 값들의 합을 갱신하는 DFS 함수
int dfs(TreeNode* node, int sum_greater) {
    if (node == nullptr) {
        return sum_greater;  // 노드가 NULL이면 합을 그대로 반환
    }

    // 1. 오른쪽 서브트리부터 탐색 (더 큰 값들이 먼저 처리되므로)
    sum_greater = dfs(node->right, sum_greater);

    // 2. 현재 노드의 값에 더 큰 값들의 합을 더함
    node->val += sum_greater;

    // 3. 왼쪽 서브트리로 진행, sum_greater는 현재 노드의 값
    return dfs(node->left, node->val);
}

// TreeNode* sumOfGreaterNodes(TreeNode* root): 트리의 각 노드를 해당 노드보다 큰 노드들의 값의 합으로 갱신하는 함수
TreeNode* sumOfGreaterNodes(TreeNode* root) {
    dfs(root, 0);  // DFS 탐색을 시작
    return root;   // 갱신된 트리 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// helper 함수: 현재 노드에서 시작하는 경로 합과, 전체 트리에서 가능한 최대 경로 합을 구함
int dfs(TreeNode* node, int* max_sum) {
    if (node == nullptr) {
        return 0;  // 노드가 없으면 경로 합은 0
    }

    // 1. 왼쪽과 오른쪽 서브트리에서 최대 경로 합을 구함
    int left_single = dfs(node->left, max_sum);
    int right_single = dfs(node->right, max_sum);

    // 2. 현재 노드를 포함하는 경로에서 단일 경로 합 계산
    int single_path = max(left_single, 0) + node->val;  // 왼쪽 서브트리의 합이 음수라면 0으로 처리
    int max_single = max(right_single, 0) + node->val; // 오른쪽 서브트리의 합이 음수라면 0으로 처리

    // 3. 현재 노드를 포함한 최대 경로 합 계산
    int current_max_path = left_single + node->val + right_single;
    if (current_max_path > *max_sum) {
        *max_sum = current_max_path;  // 최대 경로 합을 갱신
    }

    // 4. 현재 노드를 포함한 경로의 최대값을 반환 (부모로 전달될 수 있는 경로 합)
    return max(single_path, max_single);
}

// int maxPathSum(TreeNode* root): 트리에서 가장 큰 경로 합을 구하는 함수
int maxPathSum(TreeNode* root) {
    int max_sum = INT_MIN;  // 초기 최대 경로 합을 음의 무한대 값으로 설정
    dfs(root, &max_sum);  // DFS 탐색을 시작하고, max_sum을 갱신
    return max_sum;  // 최종적으로 계산된 최대 경로 합 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 범위 내에 있는 노드들의 값을 저장하는 배열 크기를 추적하기 위한 변수
int size = 0;

// DFS로 트리를 탐색하면서 주어진 범위 [low, high]에 포함되는 값들을 배열에 저장
void dfs__(TreeNode* node, int low, int high, int* result) {
    if (node == nullptr) {
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

// int* nodesInRange(TreeNode* root, int low, int high, int* returnSize): 주어진 범위 [low, high]에 속하는 노드들의 값을 반환하는 함수
int* nodesInRange(TreeNode* root, int low, int high, int* returnSize) {
    // 결과를 저장할 배열 할당 (임시로 1000개로 크기 설정)
    int* result = (int*)malloc(1000 * sizeof(int));  // 메모리 동적 할당
    size = 0;  // 배열 크기 초기화

    // DFS 탐색 시작
    dfs__(root, low, high, result);

    // 반환할 크기 설정
    *returnSize = size;

    return result;  // 범위 내의 값들 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// bool hasPathSum(TreeNode* root, int sum): 경로 합이 주어진 값과 일치하는지 확인하는 함수
// 주어진 이진 트리에서 루트부터 리프 노드까지의 경로 중 합이 sum과 일치하는 경로가 있는지 확인
bool hasPathSum(TreeNode* root, int sum) {
    // 트리가 비어 있으면, 경로가 없으므로 false 반환
    if (root == nullptr) {
        return false;
    }

    // 리프 노드에 도달한 경우 (왼쪽, 오른쪽 자식이 모두 NULL)
    if (root->left == nullptr && root->right == nullptr) {
        // 리프 노드의 값이 남은 합과 일치하면 true 반환
        return root->val == sum;
    }

    // 리프 노드가 아니라면, sum에서 현재 노드 값을 빼고 왼쪽과 오른쪽 자식으로 재귀 호출
    sum -= root->val;
    return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p): p 노드의 중위 순회 후속 노드를 찾는 함수
// p 노드를 기준으로 중위 순회 후에 오는 노드를 반환
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    if (root == nullptr) {
        return nullptr;  // 트리가 비어 있으면 NULL 반환
    }

    TreeNode* successor = nullptr;  // 후속 노드를 저장할 변수

    // 트리를 탐색하여 p 노드의 후속 노드를 찾음
    while (root != nullptr) {
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
// int isChildSum(TreeNode* root): 트리가 자식 노드들의 합 규칙을 만족하는지 확인하는 함수
// 각 노드가 자식 노드들의 합보다 크거나 같은지 확인
int isChildSum(TreeNode* root) {
    // 트리가 비어 있거나 리프 노드일 경우 True 반환
    if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
        return 1;  // 1은 True
    }

    // 왼쪽 자식과 오른쪽 자식의 값을 구합니다. 자식이 없으면 0으로 처리.
    int left_val = (root->left != nullptr) ? root->left->val : 0;
    int right_val = (root->right != nullptr) ? root->right->val : 0;

    // 현재 노드의 값이 왼쪽 + 오른쪽 자식 값보다 크거나 같은지 확인하고,
    // 왼쪽과 오른쪽 자식 노드들에 대해서도 재귀적으로 검사
    if (root->val >= left_val + right_val &&
        isChildSum(root->left) && isChildSum(root->right)) {
        return 1;  // 1은 True
    }

    return 0;  // 0은 False
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 새 노드를 생성하는 함수
TreeNode* newNode(int val) {
    return new TreeNode(val);  // 주어진 값을 가진 새로운 노드를 생성
}

// TreeNode* sortedArrayToBST(int* nums, int start, int end): 정렬된 배열을 이진 검색 트리(BST)로 변환하는 함수
// 배열의 중간값을 루트로 하고, 왼쪽과 오른쪽 절반을 재귀적으로 트리로 변환
TreeNode* sortedArrayToBST(int* nums, int start, int end) {
    if (start > end) {
        return nullptr;  // 배열이 비어 있으면 NULL 반환
    }

    // 배열의 중간값을 선택하여 루트 노드를 생성
    int mid = (start + end) / 2;
    TreeNode* root = newNode(nums[mid]);

    // 중간값을 제외한 왼쪽 절반과 오른쪽 절반을 재귀적으로 BST로 변환
    root->left = sortedArrayToBST(nums, start, mid - 1);  // 왼쪽 절반
    root->right = sortedArrayToBST(nums, mid + 1, end);   // 오른쪽 절반

    return root;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int isIdentical(TreeNode* root1, TreeNode* root2): 두 트리가 동일한지 확인하는 함수
int isIdentical(TreeNode* root1, TreeNode* root2) {
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
// 전역 변수로 트리의 직경을 저장
int diameter = 0;  // 트리의 직경을 계산할 변수

// 트리의 깊이를 구하는 함수 (DFS)
int dfs(TreeNode* node) {
    if (!node) {
        return 0;  // 노드가 NULL이면 깊이는 0
    }

    // 왼쪽과 오른쪽 서브트리의 깊이를 구함
    int left_depth = dfs(node->left);
    int right_depth = dfs(node->right);

    // 트리의 직경은 왼쪽 서브트리 깊이 + 오른쪽 서브트리 깊이
    diameter = std::max(diameter, left_depth + right_depth);

    // 현재 노드에서 가장 큰 깊이를 반환 (1 + 왼쪽/오른쪽 서브트리 깊이)
    return 1 + std::max(left_depth, right_depth);
}

// diameterOfBinaryTree(TreeNode* root): 트리의 직경을 구하는 함수
int diameterOfBinaryTree(TreeNode* root) {
    diameter = 0;  // 직경 초기화
    dfs(root);  // DFS를 시작하여 트리의 직경을 계산
    return diameter;  // 계산된 직경 반환
}