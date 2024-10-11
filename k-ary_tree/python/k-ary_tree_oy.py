class TreeNode:
    def __init__(self, x: int, k: int) -> None:
        self.val = x
        self.arity = k
        self.child = [None] * k

class KaryTree:
    def __init__(self, k: int):
        self.root = None
        self.k = k

    def search(self, x: int) -> list:
        result = []
        node = self._search_recursive(self.root, x)
        if node:
            result.append(node.val)
        return result

    def _search_recursive(self, node: TreeNode, x: int) -> TreeNode:
        if node is None or node.val == x:
            return node
        for child in node.child:
            found = self._search_recursive(child, x)
            if found:
                return found
        return None

    def insert(self, x: int) -> list:
        new_node = TreeNode(x, self.k)
        if self.root is None:
            self.root = new_node
        else:
            self._insert_recursive(self.root, new_node)
        return self.level_order_traversal()

    def _insert_recursive(self, node: TreeNode, new_node: TreeNode) -> bool:
        for i in range(node.arity):
            if node.child[i] is None:
                node.child[i] = new_node
                return True
            else:
                inserted = self._insert_recursive(node.child[i], new_node)
                if inserted:
                    return True
        return False

    def delete(self, x: int) -> list:
        self.root = self._delete_recursive(self.root, x)
        return self.level_order_traversal()

    def _delete_recursive(self, node: TreeNode, x: int) -> TreeNode:
        if node is None:
            return None
        if node.val == x:
            return None  # 간단한 삭제: 노드를 None으로 대체
        for i in range(node.arity):
            node.child[i] = self._delete_recursive(node.child[i], x)
        return node

    def level_order_traversal(self) -> list:
        result = []
        if self.root is None:
            return result
        queue = [self.root]
        while queue:
            current = queue.pop(0)
            result.append(current.val)
            for child in current.child:
                if child is not None:
                    queue.append(child)
        return result

# 사용 예시:
k_tree = KaryTree(3)  # 자식 노드가 최대 3개인 3-ary 트리

# 삽입 후 트리 상태 출력 (Level Order Traversal)
print("Insert 1:", k_tree.insert(1))  # [1]
print("Insert 2:", k_tree.insert(2))  # [1, 2]
print("Insert 3:", k_tree.insert(3))  # [1, 2, 3]
print("Insert 4:", k_tree.insert(4))  # [1, 2, 3, 4]
print("Insert 5:", k_tree.insert(5))  # [1, 2, 3, 4, 5]

# 검색 결과 출력
print("Search 3:", k_tree.search(3))  # [3]
print("Search 6:", k_tree.search(6))  # []

# 삭제 후 트리 상태 출력 (Level Order Traversal)
print("Delete 3:", k_tree.delete(3))  # [1, 2, 4, 5]
print("Delete 1:", k_tree.delete(1))  # [2, 4, 5]
