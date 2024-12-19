class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class BinaryTree:
    def __init__(self, root=None):
        self.root = root

    # (1) Check if the tree is complete
    def is_complete(self):
        if not self.root:
            return True
        queue = [self.root]
        found_null = False
        while queue:
            node = queue.pop(0)
            if not node:
                found_null = True
            else:
                if found_null:
                    return False
                queue.append(node.left)
                queue.append(node.right)
        return True

    # (2) Check if the tree is balanced
    def is_balanced(self):
        def check_height(node):
            if not node:
                return 0
            left_height = check_height(node.left)
            if left_height == -1:
                return -1
            right_height = check_height(node.right)
            if right_height == -1:
                return -1
            if abs(left_height - right_height) > 1:
                return -1
            return max(left_height, right_height) + 1

        return check_height(self.root) != -1

    # (3) Check if the tree is perfect
    def is_perfect(self):
        if not self.root:
            return True

        def depth(node):
            d = 0
            while node:
                node = node.left
                d += 1
            return d

        def is_perfect_recursive(node, level, max_depth):
            if not node:
                return True
            if not node.left and not node.right:
                return level + 1 == max_depth
            if not node.left or not node.right:
                return False
            return is_perfect_recursive(node.left, level + 1, max_depth) and \
                   is_perfect_recursive(node.right, level + 1, max_depth)

        max_depth = depth(self.root)
        return is_perfect_recursive(self.root, 0, max_depth)

    # (4) Check if the tree is full
    def is_full(self):
        def is_full_recursive(node):
            if not node:
                return True
            if (node.left and not node.right) or (not node.left and node.right):
                return False
            return is_full_recursive(node.left) and is_full_recursive(node.right)

        return is_full_recursive(self.root)

    # (5) Count the total number of nodes
    def size(self):
        def count_nodes(node):
            if not node:
                return 0
            return 1 + count_nodes(node.left) + count_nodes(node.right)

        return count_nodes(self.root)

    # (6) Flatten a binary tree to a list
    def flatten_bt(self, order="in-order"):
        def traverse(node, order):
            if not node:
                return []
            if order == "pre-order":
                return [node.val] + traverse(node.left, order) + traverse(node.right, order)
            elif order == "in-order":
                return traverse(node.left, order) + [node.val] + traverse(node.right, order)
            elif order == "post-order":
                return traverse(node.left, order) + traverse(node.right, order) + [node.val]
            else:
                raise ValueError("Invalid order. Choose from 'pre-order', 'in-order', or 'post-order'.")

        return traverse(self.root, order)

    # (7) Mirror the tree
    def mirror(self):
        def mirror_tree(node):
            if not node:
                return
            node.left, node.right = node.right, node.left
            mirror_tree(node.left)
            mirror_tree(node.right)

        mirror_tree(self.root)

    # (8) Diameter of the tree
    def diameter(self):
        self.diameter_length = 0

        def calculate_diameter(node):
            if not node:
                return 0
            left_height = calculate_diameter(node.left)
            right_height = calculate_diameter(node.right)
            self.diameter_length = max(self.diameter_length, left_height + right_height)
            return 1 + max(left_height, right_height)

        calculate_diameter(self.root)
        return self.diameter_length

    # (9) Find path to a node
    def find_path(self, value):
        def dfs(node, path):
            if not node:
                return False
            path.append(node.val)
            if node.val == value:
                return True
            if dfs(node.left, path) or dfs(node.right, path):
                return True
            path.pop()
            return False

        path = []
        dfs(self.root, path)
        return path

    # (10) Check if the tree is symmetric
    def is_symmetric(self):
        def is_mirror(t1, t2):
            if not t1 and not t2:
                return True
            if not t1 or not t2:
                return False
            return (t1.val == t2.val) and is_mirror(t1.left, t2.right) and is_mirror(t1.right, t2.left)

        return is_mirror(self.root, self.root)

    # (11) Lowest Common Ancestor
    def lowest_common_ancestor(self, p, q):
        def find_lca(node):
            if not node or node.val == p or node.val == q:
                return node
            left = find_lca(node.left)
            right = find_lca(node.right)
            if left and right:
                return node
            return left if left else right

        lca = find_lca(self.root)
        return lca.val if lca else None

    # (12) Count leaf nodes
    def count_leaves(self):
        def count(node):
            if not node:
                return 0
            if not node.left and not node.right:
                return 1
            return count(node.left) + count(node.right)

        return count(self.root)

    # (13) Check if a tree is a subtree
    def is_subtree(self, sub_root):
        def are_identical(tree1, tree2):
            if not tree1 and not tree2:
                return True
            if not tree1 or not tree2:
                return False
            return (tree1.val == tree2.val and
                    are_identical(tree1.left, tree2.left) and
                    are_identical(tree1.right, tree2.right))

        def check_subtree(node, sub_root):
            if not node:
                return False
            if are_identical(node, sub_root):
                return True
            return check_subtree(node.left, sub_root) or check_subtree(node.right, sub_root)

        return check_subtree(self.root, sub_root)

    # (14) Count nodes per level
    def count_nodes_per_level(self):
        if not self.root:
            return {}
        level_count = {}
        queue = [(self.root, 0)]
        while queue:
            node, level = queue.pop(0)
            level_count[level] = level_count.get(level, 0) + 1
            if node.left:
                queue.append((node.left, level + 1))
            if node.right:
                queue.append((node.right, level + 1))
        return level_count

    # (15) Create a binary tree from an array
    @staticmethod
    def create_bt_from_array(arr):
        if not arr:
            return None
        nodes = [TreeNode(val) if val is not None else None for val in arr]
        for i in range(len(arr)):
            if nodes[i]:
                if 2 * i + 1 < len(arr):
                    nodes[i].left = nodes[2 * i + 1]
                if 2 * i + 2 < len(arr):
                    nodes[i].right = nodes[2 * i + 2]
        return BinaryTree(nodes[0])
    
##############################################################################
# Create binary tree from array
arr = [1, 2, 3, 4, 5, 6, 7]
print("Current array: ", arr)
bt = BinaryTree.create_bt_from_array(arr)

# Check tree properties
print("Is complete:", bt.is_complete())
print("Is balanced:", bt.is_balanced())
print("Is perfect:", bt.is_perfect())
print("Is full:", bt.is_full())

# Flatten the tree
print("Flattened tree (pre-order):", bt.flatten_bt(order="pre-order"))

# Mirror the tree
bt.mirror()
print("Flattened tree (in-order, mirrored):", bt.flatten_bt(order="in-order"))

# Diameter of the tree
print("Diameter of the tree:", bt.diameter())

# Find path
print("Path to 5:", bt.find_path(5))

# Symmetry
print("Is symmetric:", bt.is_symmetric())

# Lowest Common Ancestor
print("Lowest Common Ancestor of 4 and 5:", bt.lowest_common_ancestor(4, 5))

# Count leaves
print("Number of leaves:", bt.count_leaves())

# Check if subtree
sub_tree = BinaryTree.create_bt_from_array([2, 4, 5])
print("Is subtree:", bt.is_subtree(sub_tree.root))

# Count nodes per level
print("Nodes per level:", bt.count_nodes_per_level())
    
##############################################################################

# Create a binary tree from a list of characters
arr = ['A', 'B', 'C', 'D', 'E', 'F', 'G']
print("\nCurrent array: ", arr)
bt = BinaryTree.create_bt_from_array(arr)

# Check tree properties
print("Is complete:", bt.is_complete())
print("Is balanced:", bt.is_balanced())
print("Is perfect:", bt.is_perfect())
print("Is full:", bt.is_full())

# Flatten the tree
print("Flattened tree (pre-order):", bt.flatten_bt(order="pre-order"))

# Mirror the tree
bt.mirror()
print("Flattened tree (in-order, mirrored):", bt.flatten_bt(order="in-order"))

# Diameter of the tree
print("Diameter of the tree:", bt.diameter())

# Find path
print("Path to 'E':", bt.find_path('E'))

# Symmetry
print("Is symmetric:", bt.is_symmetric())

# Lowest Common Ancestor
print("Lowest Common Ancestor of 'D' and 'E':", bt.lowest_common_ancestor('D', 'E'))

# Count leaves
print("Number of leaves:", bt.count_leaves())

# Check if subtree
sub_tree = BinaryTree.create_bt_from_array(['B', 'D', 'E'])
print("Is subtree:", bt.is_subtree(sub_tree.root))

# Count nodes per level
print("Nodes per level:", bt.count_nodes_per_level())