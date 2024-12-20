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
// (11) lowest_common_ancestor: return the lca of node1 and node2 (char)
// (12) count_leaves: count all leaves (int)
// (13) is_subtree: Given a TreeNode, check if the treenode is a subtree of the current tree (bool)
// (14) count_nodes_per_level: Return a dictionary showing the count of nodes at each level (dict)
// (15) create_bt_from_array: Given a list of ints (or a string), make a complete binary tree (left to right)
// (16) to_complete_bt: Given a binary tree, convert it into a complete binary tree (in-place)
// (17) to_complete_bst: Given a binary tree, convert it into a complete BST (in-place) 

// Definition for a binary tree node
typedef struct TreeNode {
    char val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Queue implementation for level-order traversal
typedef struct QueueNode {
    TreeNode* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Queue helper functions
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, TreeNode* node) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = node;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

TreeNode* dequeue(Queue* queue) {
    if (queue->front == NULL) return NULL;
    QueueNode* temp = queue->front;
    TreeNode* node = temp->treeNode;
    queue->front = queue->front->next;
    if (queue->front == NULL) queue->rear = NULL;
    free(temp);
    return node;
}

bool isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

// (1) Check if the tree is complete
bool is_complete(TreeNode* root) {
    if (!root) return true;
    Queue* queue = createQueue();
    enqueue(queue, root);
    bool foundNull = false;

    while (!isQueueEmpty(queue)) {
        TreeNode* current = dequeue(queue);
        if (!current) {
            foundNull = true;
        } else {
            if (foundNull) return false;
            enqueue(queue, current->left);
            enqueue(queue, current->right);
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
int count_nodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

// (6) Flatten the binary tree into a list
void flatten_char(TreeNode* node, char* result, int* index, const char* order) {
    if (!node) return;
    if (strcmp(order, "pre-order") == 0) result[(*index)++] = node->val;
    flatten_char(node->left, result, index, order);
    if (strcmp(order, "in-order") == 0) result[(*index)++] = node->val;
    flatten_char(node->right, result, index, order);
    if (strcmp(order, "post-order") == 0) result[(*index)++] = node->val;
}

char* flatten_bt(TreeNode* root, const char* order, int* result_size) {
    *result_size = count_nodes(root);
    char* result = (char*)malloc((*result_size) * sizeof(char));
    int index = 0;
    flatten_char(root, result, &index, order);
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
bool find_path(TreeNode* root, char value, char* path, int* pathLength) {
    if (!root) return false;
    path[(*pathLength)++] = root->val;
    if (root->val == value) return true;
    if (find_path(root->left, value, path, pathLength) ||
        find_path(root->right, value, path, pathLength)) return true;
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
TreeNode* find_lca(TreeNode* root, char p, char q) {
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
void count_nodes_per_level_helper(TreeNode* root, int level, int* levels) {
    if (!root) return;
    levels[level]++;
    count_nodes_per_level_helper(root->left, level + 1, levels);
    count_nodes_per_level_helper(root->right, level + 1, levels);
}

int* count_nodes_per_level(TreeNode* root, int* maxLevel) {
    *maxLevel = 0;
    int* levels = (int*)calloc(100, sizeof(int)); // Assume max depth is 100
    count_nodes_per_level_helper(root, 0, levels);

    for (int i = 0; i < 100; i++) {
        if (levels[i] > 0) *maxLevel = i;
    }

    return levels;
}

// (15) Create a binary tree from an array
TreeNode* create_bt_from_array(const char* values, int size) {
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

// helper for (16)
void collect_nodes(TreeNode* root, TreeNode** nodes, int* count) {
    if (!root) return;
    Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        TreeNode* current = dequeue(queue);
        nodes[(*count)++] = current;
        if (current->left) enqueue(queue, current->left);
        if (current->right) enqueue(queue, current->right);
    }

    free(queue);
}

// (16) BT -> complete BT
TreeNode* to_complete_bt(TreeNode* root) {
    if (!root) return NULL;

    // Collect all nodes in level order
    TreeNode* nodes[1000]; // Assume max nodes is 1000 for simplicity
    int count = 0;
    collect_nodes(root, nodes, &count);

    // Rebuild the tree as a complete binary tree
    for (int i = 0; i < count; i++) {
        nodes[i]->left = (2 * i + 1 < count) ? nodes[2 * i + 1] : NULL;
        nodes[i]->right = (2 * i + 2 < count) ? nodes[2 * i + 2] : NULL;
    }

    return nodes[0];
}

// helper for (17)

void collect_values_inorder(TreeNode* root, char* values, int* count) {
    if (!root) return;
    collect_values_inorder(root->left, values, count);
    values[(*count)++] = root->val;
    collect_values_inorder(root->right, values, count);
}

void rebuild_complete_bst(TreeNode* root, char* values, int* index) {
    if (!root) return;
    rebuild_complete_bst(root->left, values, index);
    root->val = values[(*index)++];
    rebuild_complete_bst(root->right, values, index);
}

// (17) BT -> complete BST
TreeNode* to_complete_bst(TreeNode* root) {
    if (!root) return NULL;

    // Collect all values using in-order traversal
    char values[1000]; // Assume max nodes is 1000 for simplicity
    int count = 0;
    collect_values_inorder(root, values, &count);

    // Sort the values to satisfy BST property
    qsort(values, count, sizeof(char), (int (*)(const void*, const void*))strcmp);

    // Rebuild the tree as a complete binary tree
    TreeNode* nodes[1000];
    int nodeCount = 0;
    collect_nodes(root, nodes, &nodeCount);
    for (int i = 0; i < nodeCount; i++) {
        nodes[i]->left = (2 * i + 1 < nodeCount) ? nodes[2 * i + 1] : NULL;
        nodes[i]->right = (2 * i + 2 < nodeCount) ? nodes[2 * i + 2] : NULL;
    }

    // Populate values into the complete binary tree
    int index = 0;
    rebuild_complete_bst(nodes[0], values, &index);

    return nodes[0];
}

// Free the entire tree
void free_tree(TreeNode* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// Main function to demonstrate the implementation
int main() {
    const char values[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    int size = sizeof(values) / sizeof(values[0]);

    // Create the binary tree
    TreeNode* root = create_bt_from_array(values, size);

    // Check tree properties
    printf("Is the tree complete? %s\n", is_complete(root) ? "Yes" : "No");
    printf("Is the tree balanced? %s\n", is_balanced(root) ? "Yes" : "No");
    printf("Is the tree perfect? %s\n", is_perfect(root) ? "Yes" : "No");
    printf("Is the tree full? %s\n", is_full(root) ? "Yes" : "No");

    // Flatten the tree in pre-order
    int result_size = 0;
    char* result = flatten_bt(root, "pre-order", &result_size);
    printf("Flattened tree (pre-order): ");
    for (int i = 0; i < result_size; i++) {
        printf("%c ", result[i]);
    }
    printf("\n");

    // Free memory
    free(result);
    free_tree(root);

    return 0;
}