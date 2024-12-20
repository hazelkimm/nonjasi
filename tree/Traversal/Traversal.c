#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Binary Tree Node
// - struct TreeNode
// - TreeNode* createTreeNode(int value)

// K-ary Tree Node
// - struct TreeNode_k
// - TreeNode_k* createTreeNode_k(int value, int k)

// Stack for DFS
// - struct StackNode
// - StackNode* createStackNode(TreeNode* treeNode)
// - void push(StackNode** top, TreeNode* treeNode)
// - TreeNode* pop(StackNode** top)
// - TreeNode* peek(StackNode* top)
// - int isStackEmpty(StackNode* top)

// Queue for BFS
// - struct QueueNode
// - struct Queue
// - Queue* createQueue()
// - int isQueueEmpty(Queue* q)
// - void enqueue(Queue* q, void* treeNode)
// - void* dequeue(Queue* q)

// K-ary Tree
// - struct Tree_k
// - Tree_k* createTree_k()
// - void visit(TreeNode_k* node)
// - void DFT_preorderHelper(TreeNode_k* curNode)   : DFT_preorder 함수를 위한 헬퍼 함수
// - void DFT_preorder(Tree_k* tree)                : K-ary tree를 받아서 DFS-Preorder 로 순회하며 각 value들을 print
// - void DFT_inorderHelper(TreeNode_k* curNode)    : DFT_inorder 함수를 위한 헬퍼 함수
// - void DFT_inorder(Tree_k* tree)                 : K-ary tree를 받아서 DFS-Inorder  로 순회하며 각 value들을 print
// - void DFT_postorderHelper(TreeNode_k* curNode)  : DFT_postorder 함수를 위한 헬퍼 함수
// - void DFT_postorder(Tree_k* tree)               : K-ary tree를 받아서 DFS-Postorder로 순회하며 각 value들을 print
// - void BFT(Tree_k* tree)                         : K-ary tree를 받아서 BFS          로 순회하며 각 value들을 print

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

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createTreeNode(int value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

////////////////////////////////////////////
/////////// K-ary Tree Node ////////////////
////////////////////////////////////////////

typedef struct TreeNode_k {
    int val;
    int arity;
    struct TreeNode_k** child;
} TreeNode_k;

TreeNode_k* createTreeNode_k(int value, int k) {
    TreeNode_k* node = (TreeNode_k*)malloc(sizeof(TreeNode_k));
    node->val = value;
    node->arity = k;
    node->child = (TreeNode_k**)malloc(k * sizeof(TreeNode_k*));
    for (int i = 0; i < k; ++i) {
        node->child[i] = NULL;
    }
    return node;
}

////////////////////////////////////////////
////////////// Stack for DFS ///////////////
////////////////////////////////////////////

// 스택의 노드를 정의하는 구조체
typedef struct StackNode {
    TreeNode* treeNode;
    struct StackNode* next;
} StackNode;

// 스택 노드 생성 함수
StackNode* createStackNode(TreeNode* treeNode) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->treeNode = treeNode;
    node->next = NULL;
    return node;
}

// 스택에 노드 추가
void push(StackNode** top, TreeNode* treeNode) {
    StackNode* newNode = createStackNode(treeNode);
    newNode->next = *top;
    *top = newNode;
}

// 스택에서 노드 제거
TreeNode* pop(StackNode** top) {
    if (*top == NULL) return NULL;
    StackNode* temp = *top;
    *top = (*top)->next;
    TreeNode* treeNode = temp->treeNode;
    free(temp);
    return treeNode;
}

// 스택의 top 노드 확인
TreeNode* peek(StackNode* top) {
    if (top == NULL) return NULL;
    return top->treeNode;
}

// 스택이 비어있는지 확인
int isStackEmpty(StackNode* top) {
    return top == NULL;
}

////////////////////////////////////////////
/////////// Queue for BFS //////////////////
////////////////////////////////////////////

// 큐 구조체 정의
typedef struct QueueNode {
    void* treeNode;  // void*로 일반화
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// 큐 초기화 함수
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// 큐가 비어있는지 확인
int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

// 큐에 노드 추가
void enqueue(Queue* q, void* treeNode) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

// 큐에서 노드 제거
void* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    QueueNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    void* treeNode = temp->treeNode;
    free(temp);
    return treeNode;
}

////////////////////////////////////////////
////////////// K-ary Tree //////////////////
////////////////////////////////////////////

typedef struct {
    TreeNode_k* root;
} Tree_k;

Tree_k* createTree_k() {
    Tree_k* tree = (Tree_k*)malloc(sizeof(Tree_k));
    tree->root = NULL;
    return tree;
}

void visit(TreeNode_k* node) {
    if (node)
        printf("%d ", node->val);
}

// DFS Preorder
void DFT_preorderHelper(TreeNode_k* curNode) {
    if (!curNode) return;

    visit(curNode);
    for (int i = 0; i < curNode->arity; i++) {
        if (curNode->child[i]) {
            DFT_preorderHelper(curNode->child[i]);
        }
    }
}

void DFT_preorder(Tree_k* tree) {
    DFT_preorderHelper(tree->root);
    printf("\n");
}

// DFS Inorder
void DFT_inorderHelper(TreeNode_k* curNode) {
    if (!curNode) return;

    int num_children = curNode->arity;
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

void DFT_inorder(Tree_k* tree) {
    DFT_inorderHelper(tree->root);
    printf("\n");
}

// DFS Postorder
void DFT_postorderHelper(TreeNode_k* curNode) {
    if (!curNode) return;

    for (int i = 0; i < curNode->arity; i++) {
        if (curNode->child[i]) {
            DFT_postorderHelper(curNode->child[i]);
        }
    }
    visit(curNode);
}

void DFT_postorder(Tree_k* tree) {
    DFT_postorderHelper(tree->root);
    printf("\n");
}

// BFS
void BFT(Tree_k* tree) {
    if (!tree->root) return;

    Queue* q = createQueue();
    enqueue(q, (void*)tree->root);

    while (!isQueueEmpty(q)) {
        TreeNode_k* curNode = (TreeNode_k*)dequeue(q);
        visit(curNode);

        for (int i = 0; i < curNode->arity; i++) {
            if (curNode->child[i]) {
                enqueue(q, (void*)curNode->child[i]);
            }
        }
    }
    printf("\n");
}

////////////////////////////////////////////
/////////// Binary Tree Traversals /////////
////////////////////////////////////////////

// Preorder DFS (Recursive)
void preorder_dfs(TreeNode* root) {
    if (!root) return;
    printf("%d ", root->val);
    preorder_dfs(root->left);
    preorder_dfs(root->right);
}

// Preorder DFS (Stack)
void preorder_stk(TreeNode* root) {
    if (!root) return;

    StackNode* stack = NULL;
    push(&stack, root);

    while (!isStackEmpty(stack)) {
        TreeNode* curr = pop(&stack);
        printf("%d ", curr->val);

        if (curr->right) push(&stack, curr->right);
        if (curr->left) push(&stack, curr->left);
    }
    printf("\n");
}

// Inorder DFS (Recursive)
void inorder_dfs(TreeNode* root) {
    if (!root) return;
    inorder_dfs(root->left);
    printf("%d ", root->val);
    inorder_dfs(root->right);
}

// Inorder DFS (Stack)
void inorder_stk(TreeNode* root) {
    StackNode* stack = NULL;
    TreeNode* curr = root;

    while (curr || !isStackEmpty(stack)) {
        while (curr) {
            push(&stack, curr);
            curr = curr->left;
        }

        curr = pop(&stack);
        printf("%d ", curr->val);
        curr = curr->right;
    }
    printf("\n");
}

// Postorder DFS (Recursive)
void postorder_dfs(TreeNode* root) {
    if (!root) return;
    postorder_dfs(root->left);
    postorder_dfs(root->right);
    printf("%d ", root->val);
}

// Postorder DFS (Stack)
void postorder_stk(TreeNode* root) {
    if (!root) return;

    StackNode* stack = NULL;
    StackNode* outStack = NULL;

    push(&stack, root);

    while (!isStackEmpty(stack)) {
        TreeNode* curr = pop(&stack);
        push(&outStack, curr);

        if (curr->left) push(&stack, curr->left);
        if (curr->right) push(&stack, curr->right);
    }

    while (!isStackEmpty(outStack)) {
        TreeNode* curr = pop(&outStack);
        printf("%d ", curr->val);
    }
    printf("\n");
}

// BFS (Level Order)
void bfs(TreeNode* root) {
    if (!root) return;
    Queue* q = createQueue();
    enqueue(q, (void*)root);
    while (!isQueueEmpty(q)) {
        TreeNode* curNode = (TreeNode*)dequeue(q);
        printf("%d ", curNode->val);
        if (curNode->left) enqueue(q, (void*)curNode->left);
        if (curNode->right) enqueue(q, (void*)curNode->right);
    }
    free(q);
    printf("\n");
}

////////////////////////////////////////////
////////////// Test Cases //////////////////
////////////////////////////////////////////

int main() {
    
    // Binary Tree Example
    //        1
    //       / \
    //      2   3
    //       \  / \
    //       5 6  7
    printf("--- Binary Tree Traversal Tests ---\n");

    TreeNode* root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->right = createTreeNode(5);
    root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(7);

    // Preorder
    printf("preorder_dfs:       ");
    preorder_dfs(root);                // 예상 출력: 1 2 5 3 6 7
    printf("\npreorder_stk:       ");
    preorder_stk(root);                // 예상 출력: 1 2 5 3 6 7

    // Inorder
    printf("\ninorder_dfs:        ");
    inorder_dfs(root);                 // 예상 출력: 2 5 1 6 3 7
    printf("\ninorder_stk:        ");
    inorder_stk(root);                 // 예상 출력: 2 5 1 6 3 7

    // Postorder
    printf("\npostorder_dfs:      ");
    postorder_dfs(root);               // 예상 출력: 5 2 6 7 3 1
    printf("\npostorder_stk:      ");
    postorder_stk(root);               // 예상 출력: 5 2 6 7 3 1

    // BFS
    printf("\nbfs:                ");
    bfs(root);                         // 예상 출력: 1 2 3 5 6 7

    // K-ary Tree Example
    //        1
    //      / | \
    //     2  3  4
    //    / \    / \
    //   5   6  7   8
    printf("--- Binary Tree Traversal Tests ---\n");

    TreeNode_k* k_root = createTreeNode_k(1, 3);
    k_root->child[0] = createTreeNode_k(2, 2);
    k_root->child[1] = createTreeNode_k(3, 0);
    k_root->child[2] = createTreeNode_k(4, 2);
    k_root->child[0]->child[0] = createTreeNode_k(5, 0);
    k_root->child[0]->child[1] = createTreeNode_k(6, 0);
    k_root->child[2]->child[0] = createTreeNode_k(7, 0);
    k_root->child[2]->child[1] = createTreeNode_k(8, 0);
    
    Tree_k* tree = createTree_k();
    tree->root = k_root;

    printf("DFT_preorder:       ");
    DFT_preorder(tree);            // 예상 출력: 1 2 5 6 3 4 7 8

    printf("DFT_inorder:        ");
    DFT_inorder(tree);             // 예상 출력: 5 2 6 1 3 7 4 8

    printf("DFT_postorder:      ");
    DFT_postorder(tree);           // 예상 출력: 5 6 2 3 7 8 4 1

    printf("BFT:                ");
    BFT(tree);                     // 예상 출력: 1 2 3 4 5 6 7 8

    return 0;
}
