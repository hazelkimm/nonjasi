#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

// [Functions]
// (1) is_complete: check if the tree is complete (bool)
// (2) is_balanced: check if the tree is balanced (bool)
// (3) is_perfect: check if the tree is perfect (bool)
// (4) is_full: check if the tree is full (bool)
// (5) size: count all number of nodes (int)
// (6) flatten_bt: flatten a binary tree to a list. An argument will be given whether to do it in pre-order, in-order, or post-order (list)
// (7) mirror: invert the tree: left->right and right->left (void)
// (8) diameter: return size of longest path between two nodes (int)
// (9) find_path: find and return the path from the root to a specific node (list)
// (10) is_symmetric: check if the tree is symmetric around the center (bool)
// (11) lowest_common_ancestor: return the lca of node1 and node2 (int)
// (12) count_leaves: count all leaves (int)
// (13) is_subtree: Given a TreeNode, check if the treenode is a subtree of the current tree (bool)
// (14) count_nodes_per_level: Return a dictionary showing the count of nodes at each level (dict)
// (15) create_bt_from_array: Given a list of ints (or a string), make a complete binary tree (left to right)
// (16) to_complete_bt: Given a binary tree, convert it into a complete binary tree (in-place)
// (17) to_complete_bst: Given a binary tree, convert it into a complete BST (in-place) 

// Definition of a binary tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// (1) Check if the tree is complete
bool is_complete(TreeNode* root) {
    if (!root) return true;
    queue<TreeNode*> q;
    q.push(root);
    bool foundNull = false;

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        if (!current) {
            foundNull = true;
        } else {
            if (foundNull) return false;
            q.push(current->left);
            q.push(current->right);
        }
    }
    return true;
}

// (2) Check if the tree is balanced
int check_height(TreeNode* node) {
    if (!node) return 0;
    int leftHeight = check_height(node->left);
    if (leftHeight == -1) return -1;
    int rightHeight = check_height(node->right);
    if (rightHeight == -1) return -1;
    if (abs(leftHeight - rightHeight) > 1) return -1;
    return 1 + max(leftHeight, rightHeight);
}

bool is_balanced(TreeNode* root) {
    return check_height(root) != -1;
}

// (3) Check if the tree is perfect
int calculate_depth(TreeNode* node) {
    int depth = 0;
    while (node) {
        depth++;
        node = node->left;
    }
    return depth;
}

bool is_perfect_recursive(TreeNode* node, int depth, int level) {
    if (!node) return true;
    if (!node->left && !node->right) return depth == level + 1;
    if (!node->left || !node->right) return false;
    return is_perfect_recursive(node->left, depth, level + 1) &&
           is_perfect_recursive(node->right, depth, level + 1);
}

bool is_perfect(TreeNode* root) {
    int depth = calculate_depth(root);
    return is_perfect_recursive(root, depth, 0);
}

// (4) Check if the tree is full
bool is_full(TreeNode* root) {
    if (!root) return true;
    if ((root->left && !root->right) || (!root->left && root->right)) return false;
    return is_full(root->left) && is_full(root->right);
}

// (5) Count the total number of nodes
int size(TreeNode* root) {
    if (!root) return 0;
    return 1 + size(root->left) + size(root->right);
}

// (6) Flatten the binary tree into a list
void flatten(TreeNode* node, vector<int>& result, const string& order) {
    if (!node) return;
    if (order == "pre-order") result.push_back(node->val);
    flatten(node->left, result, order);
    if (order == "in-order") result.push_back(node->val);
    flatten(node->right, result, order);
    if (order == "post-order") result.push_back(node->val);
}

vector<int> flatten_bt(TreeNode* root, const string& order) {
    vector<int> result;
    flatten(root, result, order);
    return result;
}

// (7) Mirror the tree
void mirror(TreeNode* node) {
    if (!node) return;
    swap(node->left, node->right);
    mirror(node->left);
    mirror(node->right);
}

// (8) Diameter of the tree
int calculate_diameter(TreeNode* node, int& diameter) {
    if (!node) return 0;
    int leftHeight = calculate_diameter(node->left, diameter);
    int rightHeight = calculate_diameter(node->right, diameter);
    diameter = max(diameter, leftHeight + rightHeight);
    return 1 + max(leftHeight, rightHeight);
}

int diameter(TreeNode* root) {
    int dia = 0;
    calculate_diameter(root, dia);
    return dia;
}

// (9) Find the path to a node
bool find_path(TreeNode* root, int value, vector<int>& path) {
    if (!root) return false;
    path.push_back(root->val);
    if (root->val == value) return true;
    if (find_path(root->left, value, path) || find_path(root->right, value, path)) return true;
    path.pop_back();
    return false;
}

// (10) Check if the tree is symmetric
bool is_mirror(TreeNode* t1, TreeNode* t2) {
    if (!t1 && !t2) return true;
    if (!t1 || !t2) return false;
    return (t1->val == t2->val &&
            is_mirror(t1->left, t2->right) &&
            is_mirror(t1->right, t2->left));
}

bool is_symmetric(TreeNode* root) {
    return is_mirror(root, root);
}

// (11) Lowest common ancestor
TreeNode* find_lca(TreeNode* root, int p, int q) {
    if (!root || root->val == p || root->val == q) return root;
    TreeNode* left = find_lca(root->left, p, q);
    TreeNode* right = find_lca(root->right, p, q);
    if (left && right) return root;
    return left ? left : right;
}

// (12) Count leaf nodes
int count_leaves(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return count_leaves(root->left) + count_leaves(root->right);
}

// (13) Check if a tree is a subtree
bool are_identical(TreeNode* t1, TreeNode* t2) {
    if (!t1 && !t2) return true;
    if (!t1 || !t2) return false;
    return (t1->val == t2->val &&
            are_identical(t1->left, t2->left) &&
            are_identical(t1->right, t2->right));
}

bool is_subtree(TreeNode* root, TreeNode* subRoot) {
    if (!root) return false;
    if (are_identical(root, subRoot)) return true;
    return is_subtree(root->left, subRoot) || is_subtree(root->right, subRoot);
}

// (14) Count nodes per level
void count_nodes_per_level(TreeNode* root, unordered_map<int, int>& counts, int level) {
    if (!root) return;
    counts[level]++;
    count_nodes_per_level(root->left, counts, level + 1);
    count_nodes_per_level(root->right, counts, level + 1);
}

unordered_map<int, int> count_nodes_per_level(TreeNode* root) {
    unordered_map<int, int> counts;
    count_nodes_per_level(root, counts, 0);
    return counts;
}

// (15) Function to create a binary tree from an array
TreeNode* create_bt_from_array(const vector<int>& values) {
    if (values.empty()) return nullptr;

    vector<TreeNode*> nodes(values.size(), nullptr);
    for (size_t i = 0; i < values.size(); i++) {
        nodes[i] = new TreeNode(values[i]);
    }

    for (size_t i = 0; i < values.size() / 2; i++) {
        if (2 * i + 1 < values.size()) nodes[i]->left = nodes[2 * i + 1];
        if (2 * i + 2 < values.size()) nodes[i]->right = nodes[2 * i + 2];
    }

    return nodes[0];
}

// Helper for (16)
void collect_nodes(TreeNode* root, vector<TreeNode*>& nodes) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        nodes.push_back(current);

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

// (16) BT -> complete BT
TreeNode* to_complete_bt(TreeNode* root) {
    if (!root) return nullptr;

    vector<TreeNode*> nodes;
    collect_nodes(root, nodes);

    // Rebuild the tree as a complete binary tree
    for (size_t i = 0; i < nodes.size(); ++i) {
        nodes[i]->left = (2 * i + 1 < nodes.size()) ? nodes[2 * i + 1] : nullptr;
        nodes[i]->right = (2 * i + 2 < nodes.size()) ? nodes[2 * i + 2] : nullptr;
    }

    return nodes[0];
}

// Helper for (17)
void collect_values_inorder(TreeNode* root, vector<int>& values) {
    if (!root) return;
    collect_values_inorder(root->left, values);
    values.push_back(root->val);
    collect_values_inorder(root->right, values);
}

void assign_values_inorder(TreeNode* root, vector<int>& values, size_t& index) {
    if (!root) return;
    assign_values_inorder(root->left, values, index);
    root->val = values[index++];
    assign_values_inorder(root->right, values, index);
}

// (17) BT -> complete BST
TreeNode* to_complete_bst(TreeNode* root) {
    if (!root) return nullptr;

    // Step 1: Collect all values using in-order traversal
    vector<int> values;
    collect_values_inorder(root, values);

    // Step 2: Sort the values to satisfy BST property
    sort(values.begin(), values.end());

    // Step 3: Convert the tree to a complete binary tree
    root = to_complete_bt(root);

    // Step 4: Assign sorted values back to the tree in in-order traversal
    size_t index = 0;
    assign_values_inorder(root, values, index);

    return root;
}

// Main function to demonstrate the implementation
int main() {
    vector<int> values = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* root = create_bt_from_array(values);

    // Test each function
    cout << "Is the tree complete? " << (is_complete(root) ? "Yes" : "No") << endl;
    cout << "Is the tree balanced? " << (is_balanced(root) ? "Yes" : "No") << endl;
    cout << "Is the tree perfect? " << (is_perfect(root) ? "Yes" : "No") << endl;
    cout << "Is the tree full? " << (is_full(root) ? "Yes" : "No") << endl;

    vector<int> flattened = flatten_bt(root, "pre-order");
    cout << "Flattened tree (pre-order): ";
    for (int val : flattened) cout << val << " ";
    cout << endl;

    cout << "Tree diameter: " << diameter(root) << endl;

    return 0;
}