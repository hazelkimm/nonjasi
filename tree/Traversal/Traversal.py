from typing import List, Optional

"""
Classes
- TreeNode   : Binary tree node
- TreeNode_k : K-ary tree node (컴기 수업시간에 다룸)
- Tree_k     : K-ary tree node를 DFS (pre/in/post-order), BFS로 순회하는 함수들 모음 (컴기 수업시간에 다룸)
    - __DFT_preorderHelp(self, curNode)  : DFT_preorder 함수를 위한 헬퍼 함수
    - DFT_preorder(self)                 : K-ary tree를 받아서 DFS-Preorder 로 순회하며 각 value들을 print
    - __DFT_inorderHelp(self, curNode)   : DFT_inorder 함수를 위한 헬퍼 함수
    - DFT_inorder(self)                  : K-ary tree를 받아서 DFS-Inorder  로 순회하며 각 value들을 print
    - __DFT_postorderHelp(self, curNode) : DFT_postorder 함수를 위한 헬퍼 함수
    - DFT_postorder(self)                : K-ary tree를 받아서 DFS-Postorder로 순회하며 각 value들을 print
    - BFT                                : K-ary tree를 받아서 BFS          로 순회하며 각 value들을 print

Functions for Traversal
- preorder_dfs(root)  : Binary tree를 받아서 DFS-Preorder 로 순회하며 각 value들을 List 형태로 출력 (재귀 방식)
- preorder_stk(root)  : Binary tree를 받아서 DFS-Preorder 로 순회하며 각 value들을 List 형태로 출력 (스택을 이용한 반복 방식)
- inorder_dfs(root)   : Binary tree를 받아서 DFS-Inorder  로 순회하며 각 value들을 List 형태로 출력 (재귀 방식)
- inorder_stk(root)   : Binary tree를 받아서 DFS-Inorder  로 순회하며 각 value들을 List 형태로 출력 (스택을 이용한 반복 방식)
- postorder_dfs(root) : Binary tree를 받아서 DFS-Postorder로 순회하며 각 value들을 List 형태로 출력 (재귀 방식)
- postorder_stk(root) : Binary tree를 받아서 DFS-Postorder로 순회하며 각 value들을 List 형태로 출력 (스택을 이용한 반복 방식)
- bfs(root)           : Binary tree를 받아서 BFS          로 순회하며 각 value들을 List 형태로 출력 (큐를 이용한 반복 방식)

Functions for Test Cases
- list_to_tree(values) : List 받아서, Binary tree 형태로 출력
- tree_to_list(root)   : Binary tree를 받아서 List 형태로 출력
"""

#######################################
############### Classes ###############
#######################################

# binary tree node
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# K-ary tree node
class TreeNode_k:
    def __init__(self, x: int, k: int) -> None:
        self.val = x
        self.arity = k
        self.child = [None] * k

# K-ary tree
class Tree_k:
    def __init__(self) -> None:
        self.root = None

    def visit(self, node: TreeNode_k) -> None:
        print(node.val)
    

    # DFS Preorder (루트 -> 왼쪽 -> 오른쪽)
    def __DFT_preorderHelp(self, curNode: TreeNode_k) -> None:
        if curNode == None:
            return
        
        self.visit(curNode)
        for childNode in curNode.child:
            self.__DFT_preorderHelp(childNode)

    def DFT_preorder(self) -> None:
        self.__DFT_preorderHelp(self.root)


    # DFS Inorder (왼쪽 -> 루트 -> 오른쪽)
    def __DFT_inorderHelp(self, curNode: TreeNode_k) -> None:
        if curNode == None:
            return
        
        # K-ary Tree일 경우
        num_children = len(curNode.child)
        for i in range(num_children):
            self.__DFT_inorderHelp(curNode.child[i])
            if i == (num_children // 2) - 1:
                self.visit(curNode)

        if num_children == 0:
            self.visit(curNode)

        # Binary Tree일 경우
        # for i in range(len(curNode.child)):
        #     if i == 1:
        #         self.visit(curNode)
        #     self.__DFT_inorderHelp(curNode.child[i])

    def DFT_inorder(self) -> None:
        self.__DFT_inorderHelp(self.root)

    
    # DFS Postorder (왼쪽 -> 오른쪽 -> 루트)
    def __DFT_postorderHelp(self, curNode: TreeNode_k) -> None:
        if curNode == None:
            return
        
        for i in range(len(curNode.child)):
            self.__DFT_postorderHelp(curNode.child[i])
        self.visit(curNode)

    def DFT_postorder(self) -> None:
        self.__DFT_postorderHelp(self.root)


    # BFS
    def BFT(self) -> None:
        if self.root == None:
            return
        
        q = [self.root]
        while q:
            curNode = q.pop(0)
            self.visit(curNode)

            for childNode in curNode.child:
                if childNode:
                    q.append(childNode)

#######################################
####### Functions for Traversal #######
#######################################

# DFS Preorder (루트 -> 왼쪽 -> 오른쪽)를 재귀로 구현
def preorder_dfs(root: Optional[TreeNode]) -> List[int]:
    """
    - Base case: curr가 비어있으면, 아무것도 하지 않고 출력
    - Recursion: curr가 정상 노드면, curr.val을 res에 추가한 뒤 왼쪽, 오른쪽 순으로 재귀 호출
    """
    res = []

    def dfs(curr):
        if not curr:
            return
        
        res.append(curr.val)
        dfs(curr.left)
        dfs(curr.right)
    
    dfs(root)
    return res

# DFS Preorder (루트 -> 왼쪽 -> 오른쪽)를 스택을 이용한 반복으로 구현
def preorder_stk(root: Optional[TreeNode]) -> List[int]:
    """
    - curr.val을 res에 추가한 뒤,
    - 오른쪽 자식을 먼저 스택에 넣고 (나중에 방문해야 하므로),
    - 왼쪽 자식을 스택에 넣음 (왼쪽이 오른쪽보다 먼저 나와서 처리됨)
    """
    if not root:
        return []
    
    res = []
    stk = [root]

    while stk:
        curr = stk.pop()
        res.append(curr.val)

        if curr.right:
            stk.append(curr.right)
        if curr.left:
            stk.append(curr.left)

    return res

# DFS Inorder (왼쪽 -> 루트 -> 오른쪽)를 재귀로 구현
def inorder_dfs(root: Optional[TreeNode]) -> List[int]:
    """
    - 함수 preorder_dfs와 비슷한데, 왼쪽 재귀 호출 -> curr.val 추가 -> 오른쪽 재귀 호출 순
    """
    res = []

    def dfs(curr):
        if not curr:
            return
        
        dfs(curr.left)
        res.append(curr.val)
        dfs(curr.right)
    
    dfs(root)
    return res

# DFS Inorder (왼쪽 -> 루트 -> 오른쪽)를 스택을 이용한 반복으로 구현
def inorder_stk(root: Optional[TreeNode]) -> List[int]:
    """
    - 왼쪽 서브트리의 끝까지 이동하며 왼쪽 자식 노드를 스택에 추가하고,
    - 스택에서 노드를 꺼내 방문한 후,
    - 오른쪽 자식 노드로 이동
    """
    res = []
    stk = []
    curr = root

    while curr or stk:
        while curr:
            stk.append(curr)
            curr = curr.left

        curr = stk.pop()
        res.append(curr.val)

        curr = curr.right

    return res

# DFS Postorder (왼쪽 -> 오른쪽 -> 루트)를 재귀로 구현
def postorder_dfs(root: Optional[TreeNode]) -> List[int]:
    """
    - 함수 preorder_dfs와 비슷한데, 왼쪽 재귀 호출 -> 오른쪽 재귀 호출 -> curr.val 추가 순
    """
    res = []

    def dfs(curr):
        if not curr:
            return
        
        dfs(curr.left)
        dfs(curr.right)
        res.append(curr.val)
    
    dfs(root)
    return res

# DFS Postorder (왼쪽 -> 오른쪽 -> 루트)를 스택을 이용한 반복으로 구현
def postorder_stk(root: Optional[TreeNode]) -> List[int]:
    """
    - postorder의 역순은 루트 -> 오른쪽 -> 왼쪽이므로,
      함수 preorder_stk와 비슷하게 (왼쪽, 오른쪽 순서만 바꿔서) 이를 구현한 후,
      최종 결과를 뒤집음
    """
    if not root:
        return []
    
    res = []
    stk = [root]

    while stk:
        curr = stk.pop()
        res.append(curr.val)

        if curr.left:
            stk.append(curr.left)
        if curr.right:
            stk.append(curr.right)

    return res[::-1]

# BFS를 큐를 이용한 반복으로 구현
def bfs(root: Optional[TreeNode]) -> List[int]:
    """
    - 함수 preorder_stk와 비슷한데, 큐 (스택 x), pop(0) (pop x), 왼쪽부터 (오른쪽부터 x)만 다름
    """
    if not root:
        return []

    res = []
    q = [root]

    while q:
        curr = q.pop(0)
        res.append(curr.val)

        if curr.left:
            q.append(curr.left)
        if curr.right:
            q.append(curr.right)

    return res

#######################################
####### Functions for Test Cases ######
#######################################

# 리스트를 받아서, binary tree 형태로 출력
def list_to_tree(values: List[Optional[int]]) -> Optional[TreeNode]:
    """
    - values의 각 원소마다, 그걸 값으로 하는 노드들을 생성해서, 리스트 nodes에 저장
    - nodes를 역순으로 복제한 새로운 리스트 kids 생성 (nodes와 달리 계속 pop할 예정)
      (pop(0) 말고 pop()을 활용하기 위해 뒤집었을 뿐, nodes와 마찬가지로 root부터 순회 예정)
    - nodes를 순회하면서, node가 None이 아닐 경우,
        kids에 정상 노드가 남아있으면 pop해서 node.left로 저장하고,
        kids에 정상 노드가 남아있으면 pop해서 node.right로 저장
    - 순회가 끝나고, kids에서 처음으로 pop했던 root를 출력
    """
    if not values:
        return None

    nodes = [TreeNode(val) if val is not None else None for val in values]
    kids = nodes[::-1]
    root = kids.pop()

    for node in nodes:
        if node:
            if kids:
                node.left = kids.pop()
            if kids:
                node.right = kids.pop()
    
    return root

# binary tree를 받아서, 리스트 형태로 출력
def tree_to_list(root: Optional[TreeNode]) -> List[Optional[int]]:
    """
    - 출력할 리스트 res 생성
    - BFS로 순회하면서, q에서 pop(0)한 curr가
        정상 노드면,
          res에 curr의 값을 추가하고,
          curr.left와 curr.right를 추가 (None일 수 있음)
        None이면, res에 None을 추가
    - res의 뒷부분에 추가된 불필요한 None 값들 제거한 뒤 출력
    """
    if not root:
        return []
    
    res = []
    q = [root]
    
    while q:
        curr = q.pop(0)

        if curr:
            res.append(curr.val)
            q.append(curr.left)
            q.append(curr.right)
        else:
            res.append(None)
    
    while res and res[-1] is None:
        res.pop()
    
    return res

#######################################
############## Test Cases #############
#######################################

if __name__ == "__main__":

    #############################
    #### Binary Tree Tests ######
    #############################
    print("\n--- Binary Tree Traversal Tests ---")

    # Binary Tree 생성 (예제: [1, 2, 3, None, 5, 6, 7])
    #        1
    #       / \
    #      2   3
    #       \  / \
    #       5 6  7
    values = [1, 2, 3, None, 5, 6, 7]
    root = list_to_tree(values)
    
    # Preorder DFS (재귀)
    print("preorder_dfs:       ", preorder_dfs(root))       # 예상 출력: [1, 2, 5, 3, 6, 7]
    
    # Preorder DFS (스택)
    print("preorder_stk:       ", preorder_stk(root))       # 예상 출력: [1, 2, 5, 3, 6, 7]
    
    # Inorder DFS (재귀)
    print("inorder_dfs:        ", inorder_dfs(root))        # 예상 출력: [2, 5, 1, 6, 3, 7]
    
    # Inorder DFS (스택)
    print("inorder_stk:        ", inorder_stk(root))        # 예상 출력: [2, 5, 1, 6, 3, 7]
    
    # Postorder DFS (재귀)
    print("postorder_dfs:      ", postorder_dfs(root))      # 예상 출력: [5, 2, 6, 7, 3, 1]
    
    # Postorder DFS (스택)
    print("postorder_stk:      ", postorder_stk(root))      # 예상 출력: [5, 2, 6, 7, 3, 1]
    
    # BFS
    print("bfs:                ", bfs(root))                # 예상 출력: [1, 2, 3, 5, 6, 7]

    # Binary Tree -> List로 변환
    print("tree_to_list:       ", tree_to_list(root))       # 예상 출력: [1, 2, 3, None, 5, 6, 7]

    #############################
    ##### K-ary Tree Tests ######
    #############################
    print("\n--- K-ary Tree Traversal Tests ---")

    # K-ary Tree 생성 (k=3)
    #        1
    #      / | \
    #     2  3  4
    #    / \    / \
    #   5   6  7   8
    root_k = TreeNode_k(1, 3)
    root_k.child[0] = TreeNode_k(2, 2)
    root_k.child[1] = TreeNode_k(3, 0)
    root_k.child[2] = TreeNode_k(4, 2)
    root_k.child[0].child[0] = TreeNode_k(5, 0)
    root_k.child[0].child[1] = TreeNode_k(6, 0)
    root_k.child[2].child[0] = TreeNode_k(7, 0)
    root_k.child[2].child[1] = TreeNode_k(8, 0)
    
    tree_k = Tree_k()
    tree_k.root = root_k

    # DFS Preorder
    print("DFT_preorder:")
    tree_k.DFT_preorder()  # 예상 출력: 1, 2, 5, 6, 3, 4, 7, 8

    # DFS Inorder
    print("\nDFT_inorder:")
    tree_k.DFT_inorder()   # 예상 출력: 5, 2, 6, 1, 3, 7, 4, 8

    # DFS Postorder
    print("\nDFT_postorder:")
    tree_k.DFT_postorder() # 예상 출력: 5, 6, 2, 3, 7, 8, 4, 1

    # BFS
    print("\nBFT:")
    tree_k.BFT()           # 예상 출력: 1, 2, 3, 4, 5, 6, 7, 8
