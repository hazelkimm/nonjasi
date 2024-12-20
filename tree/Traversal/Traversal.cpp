#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// Binary Tree Node
// - struct TreeNode

// K-ary Tree Node
// - struct TreeNode_k

// K-ary Tree
// - void visit(TreeNode_k* node)
// - void DFT_preorderHelper(TreeNode_k* curNode)   : DFT_preorder 함수를 위한 헬퍼 함수
// - void DFT_preorder()                            : K-ary tree를 받아서 DFS-Preorder 로 순회하며 각 value들을 print
// - void DFT_inorderHelper(TreeNode_k* curNode)    : DFT_inorder 함수를 위한 헬퍼 함수
// - void DFT_inorder()                             : K-ary tree를 받아서 DFS-Inorder  로 순회하며 각 value들을 print
// - void DFT_postorderHelper(TreeNode_k* curNode)  : DFT_postorder 함수를 위한 헬퍼 함수
// - void DFT_postorder()                           : K-ary tree를 받아서 DFS-Postorder로 순회하며 각 value들을 print
// - void BFT()                                     : K-ary tree를 받아서 BFS          로 순회하며 각 value들을 print

// Binary Tree Traversals
// - void preorder_dfs(TreeNode* root)  : Binary tree를 받아서 DFS-Preorder 로 순회하며 각 value들을 List 형태로 출력 (재귀 방식)
// - void preorder_stk(TreeNode* root)  : Binary tree를 받아서 DFS-Preorder 로 순회하며 각 value들을 List 형태로 출력 (스택을 이용한 반복 방식)
// - void inorder_dfs(TreeNode* root)   : Binary tree를 받아서 DFS-Inorder  로 순회하며 각 value들을 List 형태로 출력 (재귀 방식)
// - void inorder_stk(TreeNode* root)   : Binary tree를 받아서 DFS-Inorder  로 순회하며 각 value들을 List 형태로 출력 (스택을 이용한 반복 방식)
// - void postorder_dfs(TreeNode* root) : Binary tree를 받아서 DFS-Postorder로 순회하며 각 value들을 List 형태로 출력 (재귀 방식)
// - void postorder_stk(TreeNode* root) : Binary tree를 받아서 DFS-Postorder로 순회하며 각 value들을 List 형태로 출력 (스택을 이용한 반복 방식)
// - void bfs(TreeNode* root)           : Binary tree를 받아서 BFS          로 순회하며 각 value들을 List 형태로 출력 (큐를 이용한 반복 방식)

////////////////////////////////////////////
///////////// Binary Tree Node /////////////
////////////////////////////////////////////

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

////////////////////////////////////////////
/////////// K-ary Tree Node ////////////////
////////////////////////////////////////////

struct TreeNode_k {
    int val;
    int arity;
    vector<TreeNode_k*> child;

    TreeNode_k(int value, int k) : val(value), arity(k), child(k, nullptr) {}
};

////////////////////////////////////////////
////////////// K-ary Tree //////////////////
////////////////////////////////////////////

class Tree_k {
public:
    TreeNode_k* root;

    Tree_k() : root(nullptr) {}

    void visit(TreeNode_k* node) {
        if (node)
            cout << node->val << " ";
    }

    // DFS Preorder
    void DFT_preorderHelper(TreeNode_k* curNode) {
        if (!curNode) return;

        visit(curNode);
        for (auto childNode : curNode->child) {
            DFT_preorderHelper(childNode);
        }
    }

    void DFT_preorder() {
        DFT_preorderHelper(root);
        cout << endl;
    }

    // DFS Inorder
    void DFT_inorderHelper(TreeNode_k* curNode) {
        if (!curNode) return;

        int num_children = curNode->child.size();
        for (int i = 0; i < num_children; ++i) {
            DFT_inorderHelper(curNode->child[i]);
            if (i == num_children / 2 - 1) {
                visit(curNode);
            }
        }

        if (num_children == 0) {
            visit(curNode);
        }
    }

    void DFT_inorder() {
        DFT_inorderHelper(root);
        cout << endl;
    }

    // DFS Postorder
    void DFT_postorderHelper(TreeNode_k* curNode) {
        if (!curNode) return;

        for (auto childNode : curNode->child) {
            DFT_postorderHelper(childNode);
        }
        visit(curNode);
    }

    void DFT_postorder() {
        DFT_postorderHelper(root);
        cout << endl;
    }

    // BFS
    void BFT() {
        if (!root) return;

        queue<TreeNode_k*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode_k* curNode = q.front();
            q.pop();

            visit(curNode);

            for (auto childNode : curNode->child) {
                if (childNode) q.push(childNode);
            }
        }
        cout << endl;
    }
};

////////////////////////////////////////////
/////////// Binary Tree Traversals /////////
////////////////////////////////////////////

// Preorder DFS (Recursive)
void preorder_dfs(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder_dfs(root->left);
    preorder_dfs(root->right);
}

// Preorder DFS (Stack)
void preorder_stk(TreeNode* root) {
    if (!root) return;

    stack<TreeNode*> stk;
    stk.push(root);

    while (!stk.empty()) {
        TreeNode* curr = stk.top();
        stk.pop();

        cout << curr->val << " ";

        if (curr->right) stk.push(curr->right);
        if (curr->left) stk.push(curr->left);
    }
    cout << endl;
}

// Inorder DFS (Recursive)
void inorder_dfs(TreeNode* root) {
    if (!root) return;
    inorder_dfs(root->left);
    cout << root->val << " ";
    inorder_dfs(root->right);
}

// Inorder DFS (Stack)
void inorder_stk(TreeNode* root) {
    stack<TreeNode*> stk;
    TreeNode* curr = root;

    while (curr || !stk.empty()) {
        while (curr) {
            stk.push(curr);
            curr = curr->left;
        }

        curr = stk.top();
        stk.pop();

        cout << curr->val << " ";
        curr = curr->right;
    }
    cout << endl;
}

// Postorder DFS (Recursive)
void postorder_dfs(TreeNode* root) {
    if (!root) return;
    postorder_dfs(root->left);
    postorder_dfs(root->right);
    cout << root->val << " ";
}

// Postorder DFS (Stack)
void postorder_stk(TreeNode* root) {
    if (!root) return;

    stack<TreeNode*> stk;
    stack<int> out;
    stk.push(root);

    while (!stk.empty()) {
        TreeNode* curr = stk.top();
        stk.pop();

        out.push(curr->val);

        if (curr->left) stk.push(curr->left);
        if (curr->right) stk.push(curr->right);
    }

    while (!out.empty()) {
        cout << out.top() << " ";
        out.pop();
    }
    cout << endl;
}

// BFS (Level Order)
void bfs(TreeNode* root) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curNode = q.front();
        q.pop();
        cout << curNode->val << " ";

        if (curNode->left) q.push(curNode->left);
        if (curNode->right) q.push(curNode->right);
    }
    cout << endl;
}

////////////////////////////////////////////
////////////// Test Cases //////////////////
////////////////////////////////////////////

int main() {
    cout << "--- Binary Tree Traversal Tests ---\n";

    // Binary Tree Example
    //        1
    //       / \
    //      2   3
    //       \  / \
    //       5 6  7
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    // Preorder
    cout << "preorder_dfs:       ";
    preorder_dfs(root);             // 예상 출력: 1 2 5 3 6 7
    cout << "preorder_stk:       ";
    preorder_stk(root);             // 예상 출력: 1 2 5 3 6 7
    cout << endl;

    // Inorder
    cout << "inorder_dfs:        ";
    inorder_dfs(root);              // 예상 출력: 2 5 1 6 3 7
    cout << "inorder_stk:        ";
    inorder_stk(root);              // 예상 출력: 2 5 1 6 3 7
    cout << endl;

    // Postorder
    cout << "postorder_dfs:      ";
    postorder_dfs(root);            // 예상 출력: 5 2 6 7 3 1
    cout << "postorder_stk:      ";
    postorder_stk(root);            // 예상 출력: 5 2 6 7 3 1
    cout << endl;

    // BFS
    cout << "bfs:                ";
    bfs(root);                      // 예상 출력: 1 2 3 5 6 7

    cout << "\n--- K-ary Tree Traversal Tests ---\n";

    // K-ary Tree Example
    //        1
    //      / | \
    //     2  3  4
    //    / \    / \
    //   5   6  7   8
    TreeNode_k* k_root = new TreeNode_k(1, 3);
    k_root->child[0] = new TreeNode_k(2, 2);
    k_root->child[1] = new TreeNode_k(3, 0);
    k_root->child[2] = new TreeNode_k(4, 2);
    k_root->child[0]->child[0] = new TreeNode_k(5, 0);
    k_root->child[0]->child[1] = new TreeNode_k(6, 0);
    k_root->child[2]->child[0] = new TreeNode_k(7, 0);
    k_root->child[2]->child[1] = new TreeNode_k(8, 0);

    Tree_k tree_k;
    tree_k.root = k_root;

    // Preorder
    cout << "DFT_preorder:       ";
    tree_k.DFT_preorder();           // 예상 출력: 1 2 5 6 3 4 7 8

    // Inorder
    cout << "DFT_inorder:        ";
    tree_k.DFT_inorder();            // 예상 출력: 5 2 6 1 3 7 4 8

    // Postorder
    cout << "DFT_postorder:      ";
    tree_k.DFT_postorder();          // 예상 출력: 5 6 2 3 7 8 4 1

    // BFS
    cout << "BFT:                ";
    tree_k.BFT();                    // 예상 출력: 1 2 3 4 5 6 7 8

    return 0;
}
