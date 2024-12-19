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
//- diameter: 트리의 지름(노드 간 가장 긴 경로)을 계산합니다.
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

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

class TreeNode {
public:
    int val;
    int arity;
    vector<TreeNode*> child;

    TreeNode(int x, int k) : val(x), arity(k), child(k, nullptr) {}
};

class Tree {
private:
    TreeNode* root;

    void visit(TreeNode* node) {
        if (node)
            cout << node->val << " ";
    }
    
    void preorderHelper(TreeNode* curNode) {
        if (curNode == nullptr) return;
        visit(curNode);
        for (TreeNode* childNode : curNode->child) {
            preorderHelper(childNode);
        }
    }
    
    void inorderHelper(TreeNode* curNode) {
        if (curNode == nullptr) return;
        int num_children = curNode->child.size();
        int mid = num_children / 2;
        for (int i = 0; i < mid; ++i) {
            inorderHelper(curNode->child[i]);
        }
        visit(curNode);
        for (int i = mid; i < num_children; ++i) {
            inorderHelper(curNode->child[i]);
        }
    }


    void postorderHelper(TreeNode* curNode) {
        if (curNode == nullptr) return;
        for (TreeNode* childNode : curNode->child) {
            postorderHelper(childNode);
        }
        visit(curNode);
    }

    int calculateHeight(TreeNode* node) {
        if (!node) return 0;
        int maxHeight = 0;
        for (auto childNode : node->child) {
            maxHeight = max(maxHeight, calculateHeight(childNode));
        }
        return 1 + maxHeight;
    }

    int countLeaves(TreeNode* node) {
        if (!node) return 0;
        if (all_of(node->child.begin(), node->child.end(), [](TreeNode* child) { return child == nullptr; })) {
            return 1;
        }
        int leafCount = 0;
        for (auto childNode : node->child) {
            leafCount += countLeaves(childNode);
        }
        return leafCount;
    }

    int findMax(TreeNode* node) {
        if (!node) return INT_MIN;
        int maxValue = node->val;
        for (auto childNode : node->child) {
            maxValue = max(maxValue, findMax(childNode));
        }
        return maxValue;
    }

    int findMin(TreeNode* node) {
        if (!node) return INT_MAX;
        int minValue = node->val;
        for (auto childNode : node->child) {
            minValue = min(minValue, findMin(childNode));
        }
        return minValue;
    }

    int sumNodes(TreeNode* node) {
        if (!node) return 0;
        int total = node->val;
        for (auto childNode : node->child) {
            total += sumNodes(childNode);
        }
        return total;
    }

    void addNodes(TreeNode* node, queue<int>& values) {
        if (!node) return;
        for (int i = 0; i < node->arity && !values.empty(); i++) {
            if (!node->child[i]) {
                node->child[i] = new TreeNode(values.front(), node->arity);
                values.pop();
            }
            addNodes(node->child[i], values);
        }
    }

    vector<int> leftMostNodes(TreeNode* node) {
        vector<int> result;
        while (node) {
            result.push_back(node->val);
            node = node->child[0];
        }
        return result;
    }

    vector<int> collectLeafNodes(TreeNode* node) {
        vector<int> result;
        if (!node) return result;
        if (all_of(node->child.begin(), node->child.end(), [](TreeNode* child) { return child == nullptr; })) {
            result.push_back(node->val);
            return result;
        }
        for (auto childNode : node->child) {
            auto childLeaves = collectLeafNodes(childNode);
            result.insert(result.end(), childLeaves.begin(), childLeaves.end());
        }
        return result;
    }

    bool isBalancedHelper(TreeNode* node, int& height) {
        if (!node) {
            height = 0;
            return true;
        }
        int minHeight = INT_MAX, maxHeight = INT_MIN;
        for (auto childNode : node->child) {
            int childHeight = 0;
            if (!isBalancedHelper(childNode, childHeight)) return false;
            minHeight = min(minHeight, childHeight);
            maxHeight = max(maxHeight, childHeight);
        }
        height = maxHeight + 1;
        return (maxHeight - minHeight <= 1);
    }

    bool searchHelper(TreeNode* node, int value) {
        if (!node) return false;
        if (node->val == value) return true;
        for (auto childNode : node->child) {
            if (searchHelper(childNode, value)) return true;
        }
        return false;
    }

    bool pathToNodeHelper(TreeNode* node, int value, vector<int>& path) {
        if (!node) return false;
        path.push_back(node->val);
        if (node->val == value) return true;
        for (auto childNode : node->child) {
            if (pathToNodeHelper(childNode, value, path)) return true;
        }
        path.pop_back();
        return false;
    }

    void levelOrderTraversalHelper(TreeNode* node, vector<vector<int>>& levels, int depth) {
        if (!node) return;
        if (depth >= levels.size()) {
            levels.push_back({});
        }
        levels[depth].push_back(node->val);
        for (auto childNode : node->child) {
            levelOrderTraversalHelper(childNode, levels, depth + 1);
        }
    }

    int countInternalNodesHelper(TreeNode* node) {
        if (!node) return 0;
        if (all_of(node->child.begin(), node->child.end(), [](TreeNode* child) { return child == nullptr; })) {
            return 0;
        }
        int count = 1;
        for (auto childNode : node->child) {
            count += countInternalNodesHelper(childNode);
        }
        return count;
    }

    TreeNode* lcaHelper(TreeNode* node, int value1, int value2) {
        if (!node) return nullptr;
        if (node->val == value1 || node->val == value2) return node;

        TreeNode* lca = nullptr;
        int count = 0;
        for (auto childNode : node->child) {
            TreeNode* res = lcaHelper(childNode, value1, value2);
            if (res) {
                count++;
                lca = res;
            }
        }

        if (count > 1) return node;
        return lca;
    }

public:
    Tree(int rootValue, int k) {
        root = new TreeNode(rootValue, k);
    }

    void addNodes(vector<int> values) {
    if (!root || values.empty()) return;

    queue<TreeNode*> nodeQueue;
    queue<int> valueQueue;

    // 값을 큐에 삽입
    for (int val : values) {
        valueQueue.push(val);
    }

    // 루트 노드를 큐에 삽입
    nodeQueue.push(root);

    while (!nodeQueue.empty() && !valueQueue.empty()) {
        TreeNode* current = nodeQueue.front();
        nodeQueue.pop();

        // 현재 노드에 자식을 추가
        for (int i = 0; i < current->arity && !valueQueue.empty(); ++i) {
            if (!current->child[i]) {
                // 값에서 새로운 노드 생성
                current->child[i] = new TreeNode(valueQueue.front(), current->arity);
                valueQueue.pop();

                // 새로 추가된 자식을 큐에 삽입
                nodeQueue.push(current->child[i]);
            }
        }
    }
}


    void BFT() {
        if (!root) return;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* curNode = q.front();
            q.pop();
            visit(curNode);
            for (auto childNode : curNode->child) {
                if (childNode) q.push(childNode);
            }
        }
        cout << endl;
    }

    void DFT_preorder() {
        preorderHelper(root);
        cout << endl;
    }

    void DFT_inorder() {
        inorderHelper(root);
        cout << endl;
    }

    void DFT_postorder() {
        postorderHelper(root);
        cout << endl;
    }

    int calculateHeight() {
        return calculateHeight(root);
    }

    int countLeafNodes() {
        return countLeaves(root);
    }

    int findMaxValue() {
        return findMax(root);
    }

    int findMinValue() {
        return findMin(root);
    }

    int sumOfNodes() {
        return sumNodes(root);
    }

    vector<int> getLeftMostNodes() {
        return leftMostNodes(root);
    }

    vector<int> getLeafNodes() {
        return collectLeafNodes(root);
    }

    bool isBalanced() {
        int height = 0;
        return isBalancedHelper(root, height);
    }

        bool search(int value) {
        return searchHelper(root, value);
    }

    vector<int> pathToNode(int value) {
        vector<int> path;
        pathToNodeHelper(root, value, path);
        return path;
    }

    vector<vector<int>> levelOrderTraversal() {
        vector<vector<int>> levels;
        levelOrderTraversalHelper(root, levels, 0);
        return levels;
    }

    int countInternalNodes() {
        return countInternalNodesHelper(root);
    }

    int findLCA(int value1, int value2) {
        TreeNode* lcaNode = lcaHelper(root, value1, value2);
        return lcaNode ? lcaNode->val : -1;
    }


    int depth(TreeNode* node, int value, int level) {
        if (!node) return -1;
        if (node->val == value) return level;
        for (auto child : node->child) {
            int d = depth(child, value, level + 1);
            if (d != -1) return d;
        }
        return -1;
    }

    int distanceBetweenNodes(int value1, int value2) {
        TreeNode* lcaNode = lcaHelper(root, value1, value2);
        if (!lcaNode) return -1;

        int d1 = depth(lcaNode, value1, 0);
        int d2 = depth(lcaNode, value2, 0);
        return (d1 != -1 && d2 != -1) ? d1 + d2 : -1;
    }


    int findKthAncestor(int value, int k) {
        vector<int> path = pathToNode(value);
        int n = path.size();
        return (k < n) ? path[n - k - 1] : -1;
    }

    bool areNodesInSameSubtree(int value1, int value2) {
        TreeNode* lcaNode = lcaHelper(root, value1, value2);
        return lcaNode && lcaNode != root;
    }

    int findPredecessor(TreeNode* node, int value, TreeNode*& predecessor) {
        if (!node) return -1;

        for (auto child : node->child) {
            if (child && child->val == value) {
                return node->val;
            }
            int res = findPredecessor(child, value, predecessor);
            if (res != -1) {
                predecessor = node;
                return res;
            }
        }

        return -1;
    }

    int findSuccessor(TreeNode* node, int value, bool& foundValue) {
        if (!node) return -1;

        if (foundValue) return node->val;
        if (node->val == value) foundValue = true;

        for (auto child : node->child) {
            int res = findSuccessor(child, value, foundValue);
            if (res != -1) return res;
        }

        return -1;
    }

    int findPredecessor(int value) {
        TreeNode* predecessor = nullptr;
        findPredecessor(root, value, predecessor);
        return predecessor ? predecessor->val : -1;
    }

    int findSuccessor(int value) {
        bool foundValue = false;
        return findSuccessor(root, value, foundValue);
    }
};

int main() {
    Tree tree(1, 3);
    tree.addNodes({2, 3, 4, 5, 6, 7, 8, 9});

    cout << "Breadth-First Traversal:" << endl;
    tree.BFT();
    // Expected output: 1 2 3 4 5 6 7 8 9

    cout << "\nPreorder Traversal:" << endl;
    tree.DFT_preorder();
    // Expected output: 1 2 5 6 7 3 8 4 9

    cout << "\nInorder Traversal:" << endl;
    tree.DFT_inorder();
    // Expected output: 5 2 6 7 1 8 3 9 4

    cout << "\nPostorder Traversal:" << endl;
    tree.DFT_postorder();
    // Expected output: 5 6 7 2 8 3 9 4 1

    cout << "\nTree Height: " << tree.calculateHeight() << endl;
    // Expected output: 3

    cout << "\nLeaf Nodes: ";
    for (int leaf : tree.getLeafNodes()) {
        cout << leaf << " ";
    }
    cout << endl;
    // Expected output: 5 6 7 8 9

    cout << "\nMax Value: " << tree.findMaxValue() << endl;
    // Expected output: 9
    cout << "\nMin Value: " << tree.findMinValue() << endl;
    // Expected output: 1
    cout << "\nSum of All Nodes: " << tree.sumOfNodes() << endl;
    // Expected output: 45

    cout << "\nLeft Most Nodes: ";
    for (int left : tree.getLeftMostNodes()) {
        cout << left << " ";
    }
    cout << endl;
    // Expected output: 1 2 5

    cout << "\nIs Balanced: " << (tree.isBalanced() ? "True" : "False") << endl;
    // Expected output: True

    cout << "\nLevel Order Traversal:" << endl;
    vector<vector<int>> levels = tree.levelOrderTraversal();
    for (int i = 0; i < levels.size(); ++i) {
        cout << "Level " << i << ": ";
        for (int val : levels[i]) {
            cout << val << " ";
        }
        cout << endl;
    }
    // Expected output:
    // Level 0: 1
    // Level 1: 2 3 4
    // Level 2: 5 6 7 8 9

    cout << "\nSearch for Value 8: " << (tree.search(8) ? "Found" : "Not Found") << endl;
    // Expected output: Found
    cout << "Search for Value 10: " << (tree.search(10) ? "Found" : "Not Found") << endl;
    // Expected output: Not Found

    cout << "\nPath to Node with Value 7: ";
    vector<int> path = tree.pathToNode(7);
    for (int val : path) {
        cout << val << " ";
    }
    cout << endl;
    // Expected output: 1 2 7

    cout << "\nInternal Nodes Count: " << tree.countInternalNodes() << endl;
    // Expected output: 3

    cout << "\nLowest Common Ancestor of 5 and 6: " << tree.findLCA(5, 6) << endl;
    // Expected output: 2
    cout << "Lowest Common Ancestor of 5 and 8: " << tree.findLCA(5, 8) << endl;
    // Expected output: 1

    cout << "\nDistance Between Nodes 5 and 6: " << tree.distanceBetweenNodes(5, 6) << endl;
    // Expected output: 2
    cout << "Distance Between Nodes 5 and 8: " << tree.distanceBetweenNodes(5, 8) << endl;
    // Expected output: 4

    cout << "\n3rd Ancestor of Node 8: " << tree.findKthAncestor(8, 3) << endl;
    // Expected output: 1
    cout << "3rd Ancestor of Node 5: " << tree.findKthAncestor(5, 3) << endl;
    // Expected output: -1

    cout << "\nAre Nodes 5 and 6 in the Same Subtree: " << (tree.areNodesInSameSubtree(5, 6) ? "Yes" : "No") << endl;
    // Expected output: Yes
    cout << "Are Nodes 5 and 4 in the Same Subtree: " << (tree.areNodesInSameSubtree(5, 4) ? "Yes" : "No") << endl;
    // Expected output: No

    cout << "\nPredecessor of Node 6: " << tree.findPredecessor(6) << endl;
    // Expected output: 2
    cout << "Successor of Node 6: " << tree.findSuccessor(6) << endl;
    // Expected output: 7

    return 0;
}
