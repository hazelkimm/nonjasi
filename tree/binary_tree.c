#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

// Definition for a binary tree node
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Queue structure for level-order traversal
typedef struct QueueNode {
    TreeNode* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// (15) Create a binary tree from an array
TreeNode* create_bt_from_array(const int* values, int size) {
    if (size == 0) return NULL;

    TreeNode** nodes = (TreeNode**)malloc(size * sizeof(TreeNode*));
    for (int i = 0; i < size; i++) {
        nodes[i] = (TreeNode*)malloc(sizeof(TreeNode));
        nodes[i]->val = values[i];
        nodes[i]->left = nodes[i]->right = NULL;
    }

    for (int i = 0; i < size / 2; i++) {
        if (2 * i + 1 < size) nodes[i]->left = nodes[2 * i + 1];
        if (2 * i + 2 < size) nodes[i]->right = nodes[2 * i + 2];
    }

    TreeNode* root = nodes[0];
    free(nodes);
    return root;
}

// (1) Check if the tree is complete
bool is_complete(TreeNode* root) {
    if (!root) return true;

    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;

    QueueNode* enqueueNode = (QueueNode*)malloc(sizeof(QueueNode));
    enqueueNode->treeNode = root;
    enqueueNode->next = NULL;
    queue->front = queue->rear = enqueueNode;

    bool foundNull = false;

    while (queue->front != NULL) {
        TreeNode* current = queue->front->treeNode;
        QueueNode* temp = queue->front;
        queue->front = queue->front->next;
        if (queue->front == NULL) queue->rear = NULL;
        free(temp);

        if (!current) {
            foundNull = true;
        } else {
            if (foundNull) return false;

            QueueNode* leftNode = (QueueNode*)malloc(sizeof(QueueNode));
            leftNode->treeNode = current->left;
            leftNode->next = NULL;
            if (queue->rear) queue->rear->next = leftNode;
            queue->rear = leftNode;

            QueueNode* rightNode = (QueueNode*)malloc(sizeof(QueueNode));
            rightNode->treeNode = current->right;
            rightNode->next = NULL;
            if (queue->rear) queue->rear->next = rightNode;
            queue->rear = rightNode;
        }
    }

    free(queue);
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
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
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
void flatten(TreeNode* node, int* result, int* index, const char* order) {
    if (!node) return;
    if (strcmp(order, "pre-order") == 0) result[(*index)++] = node->val;
    flatten(node->left, result, index, order);
    if (strcmp(order, "in-order") == 0) result[(*index)++] = node->val;
    flatten(node->right, result, index, order);
    if (strcmp(order, "post-order") == 0) result[(*index)++] = node->val;
}

int* flatten_bt(TreeNode* root, const char* order, int* result_size) {
    *result_size = size(root);
    int* result = (int*)malloc((*result_size) * sizeof(int));
    int index = 0;
    flatten(root, result, &index, order);
    return result;
}

// (7) Mirror the tree
void mirror(TreeNode* node) {
    if (!node) return;
    TreeNode* temp = node->left;
    node->left = node->right;
    node->right = temp;
    mirror(node->left);
    mirror(node->right);
}

// (8) Diameter of the tree
int calculate_diameter(TreeNode* node, int* diameter) {
    if (!node) return 0;
    int leftHeight = calculate_diameter(node->left, diameter);
    int rightHeight = calculate_diameter(node->right, diameter);
    *diameter = (*diameter > leftHeight + rightHeight) ? *diameter : leftHeight + rightHeight;
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int diameter(TreeNode* root) {
    int dia = 0;
    calculate_diameter(root, &dia);
    return dia;
}

// (9) Find the path to a node
bool find_path(TreeNode* root, int value, int* path, int* pathLength) {
    if (!root) return false;

    path[(*pathLength)++] = root->val;
    if (root->val == value) return true;

    if (find_path(root->left, value, path, pathLength) ||
        find_path(root->right, value, path, pathLength))
        return true;

    (*pathLength)--;
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

// (11) Find the Lowest Common Ancestor (LCA)
TreeNode* find_lca(TreeNode* root, int p, int q) {
    if (!root || root->val == p || root->val == q) return root;

    TreeNode* left = find_lca(root->left, p, q);
    TreeNode* right = find_lca(root->right, p, q);

    if (left && right) return root;
    return left ? left : right;
}

// (12) Count Leaf Nodes
int count_leaves(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return count_leaves(root->left) + count_leaves(root->right);
}

// (13) Check if a Tree is a Subtree
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

// (14) Count Nodes per Level
void count_nodes_level(TreeNode* root, int level, int* counts) {
    if (!root) return;
    counts[level]++;
    count_nodes_level(root->left, level + 1, counts);
    count_nodes_level(root->right, level + 1, counts);
}

int* count_nodes_per_level(TreeNode* root, int* maxLevel) {
    *maxLevel = 0;

    int* counts = (int*)calloc(100, sizeof(int)); // Assume max depth 100
    count_nodes_level(root, 0, counts);

    for (int i = 0; i < 100; i++) {
        if (counts[i] > 0) *maxLevel = i;
    }

    return counts;
}


// Main function
int main() {
    int values[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(values) / sizeof(values[0]);

    // Create the binary tree
    TreeNode* root = create_bt_from_array(values, size);

    // Check properties
    printf("Is the tree complete? %s\n", is_complete(root) ? "Yes" : "No");
    printf("Is the tree balanced? %s\n", is_balanced(root) ? "Yes" : "No");
    printf("Is the tree perfect? %s\n", is_perfect(root) ? "Yes" : "No");
    printf("Is the tree full? %s\n", is_full(root) ? "Yes" : "No");

    // Flatten tree
    int result_size;
    int* result = flatten_bt(root, "pre-order", &result_size);
    printf("Flattened tree (pre-order): ");
    for (int i = 0; i < result_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}