# Function Descriptions:
# - visit(node): 현재 노드의 값을 출력
# - BFT(): 트리에 대해 너비 우선 탐색(BFS) 수행
# - DFT_preorder(): 트리에 대해 전위 순회(DFS) 수행
# - DFT_inorder(): 트리에 대해 중위 순회(DFS) 수행
# - DFT_postorder(): 트리에 대해 후위 순회(DFS) 수행
# - visit_with_size(node, size): 서브트리 크기를 추가하여 노드 값을 업데이트
# - DFT_postorder_with_size(): 후위 순회를 통해 파일 크기를 계산 및 업데이트
# - calculate_height(): 트리의 높이를 계산
# - count_leaf_nodes(): 트리에서 리프 노드의 개수를 계산
# - find_max(): 트리에서 최댓값 찾기
# - find_min(): 트리에서 최솟값 찾기
# - search(value): 트리에서 특정 값이 존재하는지 확인
# - sum_of_nodes(): 트리에 있는 모든 노드들 값의 합
# - path_to_node(value): root부터 특정 노드까지의 path 찾기
# - is_balanced(): height-balanced인지 체크하기
# - diameter: 트리의 지름(노드 간 가장 긴 경로)을 계산합니다.
# - level_order_traversal: 트리를 레벨 순서로 순회하고, 각 레벨의 노드 값을 리스트로 반환합니다.
# - add_nodes: 주어진 값 리스트를 사용하여 트리에 레벨 순서로 노드를 추가합니다.
# - count_internal_nodes: 리프 노드를 제외한 내부 노드의 개수를 계산합니다.
# - left_most_nodes: 왼쪽 nodes들 반환
# - leaf_nodes: leaf nodes 출력하기
# - find_lca(node1, node2): 두 노드의 LCA(최소 공통 조상)를 반환
# - distance_between_nodes(node1, node2): 두 노드 간 거리 계산 (LCA 기반)
# - find_kth_ancestor(node_value, k): 특정 노드의 K번째 조상을 반환
# - are_nodes_in_same_subtree(node1, node2): 두 노드가 동일한 서브트리에 있는지 확인
# - find_predecessor : predecessor 찾기
# - find_successor: successor 찾기

#Preorder
#Directory listing
class TreeNode():
    def __init__(self, x:int, k:int) -> None:
        self.val = x
        self.arity = k
        self.child = [None]*k

class Tree():
    def __init__(self, root: TreeNode = None):
        self.root = root

    def visit(self, node:TreeNode):
        print(node.val)

    def BFT(self):
    #만약 deque를 쓰고싶다면 def BFT(self, x):    
        if self.root == None:
            return
        q = [self.root]
        # or, q = deque([self.root])
        while q:
            curNode = q.pop(0)
            #curNode = q.popleft()
            self.visit(curNode)
            # if curNode == x:   => 추가하기 for deque
            #     return curNode  => 추가하기 for deque
            for childNode in curNode.child:
                if childNode:
                    q.append(childNode)


    def __DFT_preorderHelp(self, curNode: TreeNode):
        if curNode == None:
            return
        self.visit(curNode)
        for childNode in curNode.child:
            self.__DFT_preorderHelp(childNode)
    
    def DFT_preorder(self):
        self.__DFT_preorderHelp(self.root)



#Inorder
#Flattening Tree
    def __DFT_inorderHelp(self, curNode: TreeNode):
        if curNode == None:
            return
        num_children = len(curNode.child)
        mid = num_children // 2
        for i in range(mid):
            self.__DFT_inorderHelp(curNode.child[i])
        self.visit(curNode)
        for i in range(mid, num_children):
            self.__DFT_inorderHelp(curNode.child[i])
    
    def DFT_inorder(self):
        self.__DFT_inorderHelp(self.root)
        print()



#Postorder
    def __DFT_postorderHelp(self, curNode: TreeNode):
        if curNode == None:
            return
        for i in range(len(curNode.child)):
            self.__DFT_postorderHelp(curNode.child[i])
        self.visit(curNode)


    def DFT_postorder(self):
        self.__DFT_postorderHelp(self.root)


# #Postorder - file size calculation
    def visit_with_size(self, node:TreeNode, size:float) -> None:
        node.val += size

    def __DFT_postorderWithSizeHelp(self, curNode: TreeNode) -> float:
        if not curNode:
            return 0
        subSize = 0
        for i in range(len(curNode.child)):
            subSize += self.__DFT_postorderWithSizeHelp(curNode.child[i])
        self.visit_with_size(curNode, subSize)
        return curNode.val

    def DFT_postorder_with_size(self) -> float:
        return self.__DFT_postorderWithSizeHelp(self.root)
    


    def calculate_height(self, curNode: TreeNode = None):
        if curNode is None:
            curNode = self.root
        if not curNode:
            return 0
        return 1 + max((self.calculate_height(child) for child in curNode.child if child), default=0)



    def count_leaf_nodes(self, curNode: TreeNode = None):
        if curNode is None:
            curNode = self.root
        if not curNode:
            return 0
        if all(child is None for child in curNode.child):
            return 1
        return sum(self.count_leaf_nodes(child) for child in curNode.child if child)



    def find_max(self, curNode: TreeNode = None):
        if curNode is None:
            curNode = self.root
        if not curNode:
            return float('-inf')
        max_value = curNode.val
        for child in curNode.child:
            if child:
                max_value = max(max_value, self.find_max(child))
        return max_value



    def find_min(self, curNode: TreeNode = None):
        if curNode is None:
            curNode = self.root
        if not curNode:
            return float('inf')
        min_value = curNode.val
        for child in curNode.child:
            if child:
                min_value = min(min_value, self.find_min(child))
        return min_value



    def search(self, value: int, curNode: TreeNode = None):
        if curNode is None:
            curNode = self.root
        if not curNode:
            return False
        if curNode.val == value:
            return True
        return any(self.search(value, child) for child in curNode.child if child)


    def sum_of_nodes(self, curNode: TreeNode = None):
        if curNode is None:
            curNode = self.root
        if not curNode:
            return 0
        return curNode.val + sum(self.sum_of_nodes(child) for child in curNode.child if child)

    def path_to_node(self, value: int, curNode: TreeNode = None, path=None):
        if path is None:
            path = []
        if curNode is None:
            curNode = self.root
        if not curNode:
            return None
        path.append(curNode.val)
        if curNode.val == value:
            return path
        for child in curNode.child:
            if child:
                result = self.path_to_node(value, child, path.copy())
                if result:
                    return result
        return None

    def is_balanced(self, curNode: TreeNode = None):
        if curNode is None:
            curNode = self.root
        def height_and_balance(node):
            if not node:
                return 0, True
            heights = []
            balanced = True
            for child in node.child:
                h, b = height_and_balance(child)
                heights.append(h)
                balanced = balanced and b
            if heights and max(heights) - min(heights) > 1:
                balanced = False
            return 1 + max(heights, default=0), balanced
        _, balanced = height_and_balance(curNode)
        return balanced

    def diameter(self, curNode: TreeNode = None) -> int:
        """
        Calculate the diameter of the tree (longest path between two nodes).
        """
        if curNode is None:
            curNode = self.root

        def helper(node):
            if not node:
                return 0, 0  # (height, diameter)
            heights = [helper(child)[0] for child in node.child if child]
            if len(heights) == 0:
                return 1, 0  # leaf node
            heights.sort(reverse=True)
            height = 1 + heights[0]
            diameter = max(heights[0] + (heights[1] if len(heights) > 1 else 0), max(helper(child)[1] for child in node.child if child))
            return height, diameter

        _, dia = helper(curNode)
        return dia

    def level_order_traversal(self) -> list:
        """
        Perform level-order traversal (BFS) and return values as a list of lists for each level.
        """
        if self.root is None:
            return []
        q = [self.root]
        result = []
        while q:
            level_size = len(q)
            current_level = []
            for _ in range(level_size):
                curNode = q.pop(0)
                current_level.append(curNode.val)
                for childNode in curNode.child:
                    if childNode:
                        q.append(childNode)
            result.append(current_level)
        return result

    def add_nodes(self, values: list):
        """
        Add nodes to the tree in level order using a list of values.
        """
        if not values:
            return
        if self.root is None:
            self.root = TreeNode(values.pop(0), len(values))
        q = [self.root]
        while q and values:
            curNode = q.pop(0)
            for i in range(curNode.arity):
                if not values:
                    break
                if curNode.child[i] is None:
                    curNode.child[i] = TreeNode(values.pop(0), curNode.arity)
                q.append(curNode.child[i])

    def count_internal_nodes(self, curNode: TreeNode = None) -> int:
        """
        Count the number of internal (non-leaf) nodes in the tree.
        """
        if curNode is None:
            curNode = self.root
        if not curNode or all(child is None for child in curNode.child):
            return 0
        return 1 + sum(self.count_internal_nodes(child) for child in curNode.child if child)

    def left_most_nodes(self, curNode: TreeNode = None) -> list:
        """
        Retrieve all left-most nodes from the tree.
        """
        if curNode is None:
            curNode = self.root
        result = []
        while curNode:
            result.append(curNode.val)
            curNode = curNode.child[0] if curNode.child else None
        return result

    def leaf_nodes(self, curNode: TreeNode = None) -> list:
        """
        Retrieve all leaf nodes from the tree.
        """
        if curNode is None:
            curNode = self.root
        if not curNode:
            return []
        if all(child is None for child in curNode.child):
            return [curNode.val]
        result = []
        for child in curNode.child:
            if child:
                result.extend(self.leaf_nodes(child))
        return result
    
    def find_lca(self, node1: int, node2: int) -> int:
        """
        Find the Lowest Common Ancestor (LCA) of two nodes in the tree.
        Args:
            node1 (int): Value of the first node.
            node2 (int): Value of the second node.
        Returns:
            int: Value of the LCA node, or None if either node does not exist.
        """
        def lca_helper(curNode, n1, n2):
            if not curNode:
                return None

            # If current node matches any of the two nodes, it's an LCA candidate
            if curNode.val == n1 or curNode.val == n2:
                return curNode

            # Check all children for LCA
            found_children = []
            for child in curNode.child:
                if child:
                    found = lca_helper(child, n1, n2)
                    if found:
                        found_children.append(found)

            # If more than one child subtree contains one of the nodes, current node is LCA
            if len(found_children) > 1:
                return curNode

            # Otherwise, return the single found node or None
            return found_children[0] if found_children else None

        # Start searching from the root
        lca_node = lca_helper(self.root, node1, node2)
        return lca_node.val if lca_node else None

    def find_successor(self, value: int):
        """
        Find the successor of a node (next node in inorder traversal).
        """
        inorder_list = []

        # Perform inorder traversal and store values
        def inorder(curNode):
            if not curNode:
                return
            for child in curNode.child[:len(curNode.child)//2]:
                inorder(child)
            inorder_list.append(curNode.val)
            for child in curNode.child[len(curNode.child)//2:]:
                inorder(child)

        inorder(self.root)
        
        # Find successor in the list
        if value in inorder_list:
            idx = inorder_list.index(value)
            return inorder_list[idx + 1] if idx + 1 < len(inorder_list) else None
        return None

    def find_predecessor(self, value: int):
        """
        Find the predecessor of a node (previous node in inorder traversal).
        """
        inorder_list = []

        # Perform inorder traversal and store values
        def inorder(curNode):
            if not curNode:
                return
            for child in curNode.child[:len(curNode.child)//2]:
                inorder(child)
            inorder_list.append(curNode.val)
            for child in curNode.child[len(curNode.child)//2:]:
                inorder(child)

        inorder(self.root)
        
        # Find predecessor in the list
        if value in inorder_list:
            idx = inorder_list.index(value)
            return inorder_list[idx - 1] if idx > 0 else None
        return None
    
    def distance_between_nodes(self, node1: int, node2: int):
        
        def path_length_to_node(value, curNode=None, depth=0):
            if curNode is None:
                curNode = self.root
            if not curNode:
                return float('inf')
            if curNode.val == value:
                return depth
            for child in curNode.child:
                if child:
                    length = path_length_to_node(value, child, depth + 1)
                    if length != float('inf'):
                        return length
            return float('inf')

        lca_value = self.find_lca(node1, node2)
        if lca_value is None:
            return -1  # Nodes not found

        distance = (
            path_length_to_node(node1) +
            path_length_to_node(node2) -
            2 * path_length_to_node(lca_value)
        )
        return distance
    
    
    def find_kth_ancestor(self, node_value: int, k: int):
        """
        Find the k-th ancestor of a node.
        """
        path = self.path_to_node(node_value)
        if not path or k >= len(path):
            return None
        return path[-(k + 1)]
    
    def are_nodes_in_same_subtree(self, node1: int, node2: int):
        """
        Check if two nodes belong to the same subtree.
        """
        lca_value = self.find_lca(node1, node2)
        return lca_value != self.root.val



if __name__ == "__main__":
    # Tree structure: root = 1, arity = 3
    tree = Tree(TreeNode(1, 3))
    tree.add_nodes([2, 3, 4, 5, 6, 7, 8, 9])

    print("Breadth-First Traversal:")
    tree.BFT()
    # Expected output: 1 2 3 4 5 6 7 8 9

    print("\nPreorder Traversal:")
    tree.DFT_preorder()
    # Expected output: 1 2 5 6 7 3 8 4 9

    print("\nInorder Traversal:")
    tree.DFT_inorder()
    # Expected output: 5 2 6 7 1 8 3 9 4

    print("\nPostorder Traversal:")
    tree.DFT_postorder()
    # Expected output: 5 6 7 2 8 3 9 4 1

    print("\nTree Height:")
    print(tree.calculate_height())
    # Expected output: 3

    print("\nLeaf Nodes:")
    print(tree.leaf_nodes())
    # Expected output: [5, 6, 7, 8, 9, 4]

    print("\nInternal Nodes Count:")
    print(tree.count_internal_nodes())
    # Expected output: 3

    print("\nLeft-Most Nodes:")
    print(tree.left_most_nodes())
    # Expected output: [1, 2, 5]

    print("\nTree Diameter:")
    print(tree.diameter())
    # Expected output: 4

    print("\nLevel Order Traversal:")
    print(tree.level_order_traversal())
    # Expected output: [[1], [2, 3, 4], [5, 6, 7, 8, 9]]

    print("\nSum of All Nodes:")
    print(tree.sum_of_nodes())
    # Expected output: 45

    print("\nFind Max Value:")
    print(tree.find_max())
    # Expected output: 9

    print("\nFind Min Value:")
    print(tree.find_min())
    # Expected output: 1

    print("\nSearch for Value 8:")
    print(tree.search(8))
    # Expected output: True

    print("\nSearch for Value 10:")
    print(tree.search(10))
    # Expected output: False

    print("\nPath to Node with Value 7:")
    print(tree.path_to_node(7))
    # Expected output: [1, 2, 7]

    print("\nIs Tree Balanced:")
    print(tree.is_balanced())
    # Expected output: True

    # LCA Testing
    print("\nFind LCA of 7 and 9:")
    print(tree.find_lca(7, 9))
    # Expected output: 1

    print("\nFind LCA of 5 and 7:")
    print(tree.find_lca(5, 7))
    # Expected output: 2

    print("\nDistance Between 7 and 9:")
    print(tree.distance_between_nodes(7, 9))
    # Expected output: 3 (7 -> 2 -> 1 -> 3 -> 9)

    print("\nFind K-th Ancestor of 7 (K=1):")
    print(tree.find_kth_ancestor(7, 1))
    # Expected output: 2

    print("\nFind K-th Ancestor of 7 (K=2):")
    print(tree.find_kth_ancestor(7, 2))
    # Expected output: 1

    print("\nCheck if 7 and 9 are in Same Subtree:")
    print(tree.are_nodes_in_same_subtree(7, 9))
    # Expected output: False (7 in subtree of 2, 9 in subtree of 4)

    # Successor and Predecessor Testing
    print("\nFind Successor of 7:")
    print(tree.find_successor(7))
    # Expected output: 1 (Inorder: 5 -> 2 -> 6 -> 7 -> 1 -> ...)

    print("\nFind Predecessor of 7:")
    print(tree.find_predecessor(7))
    # Expected output: 6

    print("\nFind Successor of 9:")
    print(tree.find_successor(9))
    # Expected output: None (9 is the last node)

    print("\nFind Predecessor of 5:")
    print(tree.find_predecessor(5))
    # Expected output: None (5 is the first node)
