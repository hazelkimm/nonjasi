'''
insert(root, val): 이진 탐색 트리에서 값을 삽입하는 함수
search(root, val): 이진 탐색 트리에서 값을 검색하는 함수
*isValueInBST(root, val): 이진 탐색 트리에서 특정 값이 존재하는지 확인
findMin(root): 이진 탐색 트리에서 최솟값을 찾는 함수
findMax(root): 이진 탐색 트리에서 최댓값을 찾는 함수
delete(root, val): 이진 탐색 트리에서 값을 삭제하는 함수
inorder(root): 이진 탐색 트리의 중위 순회(좌->노드->우) 함수
preorder(root): 이진 탐색 트리의 전위 순회(노드->좌->우) 함수
postorder(root): 이진 탐색 트리의 후위 순회(좌->우->노드) 함수
*postorderTraversal(root): 이진 트리를 후위 순회하여 노드 값을 리스트로 반환
height(root): 이진 트리의 높이를 구하는 함수
isBalanced(root): 트리가 균형 잡혀 있는지 확인하는 함수 (왼쪽 서브트리와 오른쪽 서브트리의 높이 차이가 1 이하인 경우)
depth(root, val, level=0): 주어진 값이 이진 탐색 트리에서 몇 번째 깊이에 있는지 찾는 함수
*depth(root, val): 주어진 값이 이진 탐색 트리에서 몇 번째 깊이에 있는지 찾는 함수
lowestCommonAncestor(root, p, q): 두 노드 p와 q의 최저 공통 조상을 찾는 함수
pathToNode(root, val, path=[]): 특정 값으로 가는 경로를 찾는 함수
*pathToNode(root, val): 주어진 값까지의 경로를 반환하는 함수
allPaths(root): 모든 루트-리프 경로를 찾는 함수
kthSmallest(root, k): k번째로 작은 값을 찾는 함수
rangeSumBST(root, low, high): 주어진 범위 [low, high]의 합을 계산하는 함수
nodesAtDepth(root, depth): 특정 깊이에 있는 노드 값을 반환하는 함수
descendingOrderTraversal(root): 이진 트리를 내림차순으로 순회하여 노드 값을 리스트로 반환
mirrorTree(root): 이진 트리를 대칭으로 뒤집는 함수 (미러링)
*invertTree(root): 트리를 뒤집는 함수
distanceBetweenNodes(root, p, q): 두 노드 p와 q 사이의 거리를 계산하는 함수 (노드 간 edge 개수?)
isValidBST(root): 이진 트리가 유효한 BST인지 확인하는 함수
sumOfGreaterNodes(root): 각 노드의 값을 해당 노드보다 큰 노드들의 값의 합으로 갱신하는 함수
maxPathSum(root): 트리에서 최대 경로 합을 구하는 함수
nodesInRange(root, low, high): 주어진 범위에 속하는 노드들의 값을 찾는 함수
hasPathSum(root, sum): 경로의 합이 주어진 sum과 일치하는지 확인하는 함수
inorderSuccessor(root, p): 주어진 노드 p의 중위 순회 후속 노드를 찾는 함수
isChildSum(root): 트리가 자식 노드들의 합을 만족하는지 확인하는 함수 (트리에서 모든 노드가 그 자식들의 값의 합보다 크거나 같은지 확인하는 함수)
sortedArrayToBST(nums): 정렬된 배열을 이진 검색 트리로 변환하는 함수
isIdentical(root1, root2): 두 트리가 동일한지 확인하는 함수
diameterOfBinaryTree(root): 트리의 직경 (Diameter) 찾는 함수 (트리의 직경(Diameter)은 트리 내에서 두 노드 사이의 가장 긴 경로를 의미)
diameterAndPathOfBinaryTree(root): 이진 트리의 직경과 직경을 이루는 경로를 계산하여 반환하는 함수
'''

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


#########################################################################################################################################
# insert(root, val): 이진 탐색 트리에서 값을 삽입하는 함수
def insert(root, val):
    if not root:  # 루트가 비어있다면 새로운 노드를 반환
        return TreeNode(val)
    if val < root.val:  # 삽입할 값이 현재 노드 값보다 작으면 왼쪽 자식에 삽입
        root.left = insert(root.left, val)
    else:  # 삽입할 값이 현재 노드 값보다 크면 오른쪽 자식에 삽입
        root.right = insert(root.right, val)
    return root  # 변경된 트리의 루트 반환


#########################################################################################################################################
# search(root, val): 이진 탐색 트리에서 값을 검색하는 함수
def search(root, val):
    if not root or root.val == val:  # 루트가 비어있거나, 찾고자 하는 값과 같다면 그 노드를 반환
        return root
    if val < root.val:  # 찾고자 하는 값이 현재 노드 값보다 작으면 왼쪽 자식 노드로 이동
        return search(root.left, val)
    return search(root.right, val)  # 찾고자 하는 값이 현재 노드 값보다 크면 오른쪽 자식 노드로 이동


# isValueInBST(root, val): 이진 탐색 트리에서 특정 값이 존재하는지 확인
def isValueInBST(root, val):
    """
    이진 탐색 트리에서 특정 값이 존재하는지 확인합니다.
    root: 이진 트리의 루트 노드
    val: 탐색할 값
    반환값: 값이 존재하면 True, 아니면 False
    """
    if not root:  # 노드가 없으면 값이 존재하지 않음
        return False
    if root.val == val:  # 현재 노드 값이 찾는 값과 같으면 True 반환
        return True
    elif val < root.val:  # 찾는 값이 현재 노드 값보다 작으면 왼쪽으로 이동
        return isValueInBST(root.left, val)
    else:  # 찾는 값이 현재 노드 값보다 크면 오른쪽으로 이동
        return isValueInBST(root.right, val)
    

#########################################################################################################################################
# findMin(root): 이진 탐색 트리에서 최솟값을 찾는 함수
def findMin(root):
    while root.left:  # 왼쪽 자식이 있을 때까지 이동
        root = root.left
    return root  # 최솟값을 가진 노드 반환


#########################################################################################################################################
# findMax(root): 이진 탐색 트리에서 최댓값을 찾는 함수
def findMax(root):
    while root.right:  # 오른쪽 자식이 있을 때까지 이동
        root = root.right
    return root  # 최댓값을 가진 노드 반환


#########################################################################################################################################
# delete(root, val): 이진 탐색 트리에서 값을 삭제하는 함수
def delete(root, val):
    if not root:  # 트리가 비어있으면, 삭제할 값이 없으므로 루트 반환
        return root
    
    if val < root.val:  # 삭제할 값이 현재 노드 값보다 작으면 왼쪽 자식에서 삭제
        root.left = delete(root.left, val)
    elif val > root.val:  # 삭제할 값이 현재 노드 값보다 크면 오른쪽 자식에서 삭제
        root.right = delete(root.right, val)
    else:  # 현재 노드가 삭제할 노드일 경우
        if not root.left:  # 왼쪽 자식이 없으면 오른쪽 자식을 대체
            return root.right
        elif not root.right:  # 오른쪽 자식이 없으면 왼쪽 자식을 대체
            return root.left
        
        # 두 자식이 모두 있을 경우, 오른쪽 서브트리에서 최솟값을 찾아서 현재 노드에 대입
        minNode = findMin(root.right)
        root.val = minNode.val  # 최솟값을 현재 노드의 값으로 대체
        root.right = delete(root.right, minNode.val)  # 오른쪽 자식에서 최솟값 삭제
    
    return root  # 변경된 트리의 루트 반환


#########################################################################################################################################
# inorder(root): 이진 탐색 트리의 중위 순회(좌->노드->우) 함수
def inorder(root):
    if root:  # 루트가 비어있지 않으면
        inorder(root.left)  # 왼쪽 자식 탐색
        print(root.val, end=" ")  # 현재 노드 출력
        inorder(root.right)  # 오른쪽 자식 탐색


#########################################################################################################################################
# preorder(root): 이진 탐색 트리의 전위 순회(노드->좌->우) 함수
def preorder(root):
    if root:  # 루트가 비어있지 않으면
        print(root.val, end=" ")  # 현재 노드 출력
        preorder(root.left)  # 왼쪽 자식 탐색
        preorder(root.right)  # 오른쪽 자식 탐색


#########################################################################################################################################
# postorder(root): 이진 탐색 트리의 후위 순회(좌->우->노드) 함수
def postorder(root):
    if root:  # 루트가 비어있지 않으면
        postorder(root.left)  # 왼쪽 자식 탐색
        postorder(root.right)  # 오른쪽 자식 탐색
        print(root.val, end=" ")  # 현재 노드 출력


# postorderTraversal(root): 이진 트리를 후위 순회하여 노드 값을 리스트로 반환
def postorderTraversal(root):
    """
    이진 트리를 후위 순회하여 노드 값을 리스트로 반환합니다.
    root: 이진 트리의 루트 노드
    반환값: 후위 순회 결과를 담은 리스트
    """
    result = []  # 결과를 저장할 리스트

    # 후위 순회를 수행하는 헬퍼 함수
    def postorder(node):
        if not node:  # 노드가 없으면 종료
            return
        postorder(node.left)  # 왼쪽 서브트리 순회
        postorder(node.right)  # 오른쪽 서브트리 순회
        result.append(node.val)  # 현재 노드의 값을 결과 리스트에 추가
    
    postorder(root)  # 후위 순회를 시작
    return result  # 결과 반환


#########################################################################################################################################
# height(root): 이진 트리의 높이를 구하는 함수
def height(root):
    if not root:  # 루트가 비어있으면 높이는 0
        return 0
    # 왼쪽과 오른쪽 서브트리의 높이를 구한 뒤, 더 큰 값을 선택하여 1을 더함
    left_height = height(root.left)
    right_height = height(root.right)
    return 1 + max(left_height, right_height)


#########################################################################################################################################
# isBalanced(root): 트리가 균형 잡혀 있는지 확인하는 함수 (왼쪽 서브트리와 오른쪽 서브트리의 높이 차이가 1 이하인 경우)
def isBalanced(root):
    if not root:
        return True
    
    def getHeight(node):
        if not node:
            return 0
        left_height = getHeight(node.left)
        right_height = getHeight(node.right)
        if left_height == -1 or right_height == -1 or abs(left_height - right_height) > 1:
            return -1
        return 1 + max(left_height, right_height)
    
    return getHeight(root) != -1


#########################################################################################################################################
# depth(root, val, level=0): 주어진 값이 이진 탐색 트리에서 몇 번째 깊이에 있는지 찾는 함수
def depth(root, val, level=0):
    if not root:  # 트리가 비어있으면 -1 반환
        return -1
    if root.val == val:  # 값이 현재 노드와 일치하면 깊이(level) 반환
        return level
    elif val < root.val:  # 찾고자 하는 값이 현재 노드 값보다 작으면 왼쪽 자식으로 탐색
        return depth(root.left, val, level + 1)
    else:  # 찾고자 하는 값이 현재 노드 값보다 크면 오른쪽 자식으로 탐색
        return depth(root.right, val, level + 1)
    
# depth(root, val): 주어진 값이 이진 탐색 트리에서 몇 번째 깊이에 있는지 찾는 함수
def depth(root, val):
    if not root:  # 트리가 비어있으면 -1 반환
        return -1
    if root.val == val:  # 값이 현재 노드와 일치하면 깊이 0 반환
        return 0
    elif val < root.val:  # 찾고자 하는 값이 현재 노드 값보다 작으면 왼쪽 자식으로 탐색
        left_depth = depth(root.left, val)
        if left_depth == -1:  # 값이 왼쪽 서브트리에서 없으면 -1 반환
            return -1
        return left_depth + 1  # 왼쪽 서브트리에서 찾았으면 깊이에 1을 더해서 반환
    else:  # 찾고자 하는 값이 현재 노드 값보다 크면 오른쪽 자식으로 탐색
        right_depth = depth(root.right, val)
        if right_depth == -1:  # 값이 오른쪽 서브트리에서 없으면 -1 반환
            return -1
        return right_depth + 1  # 오른쪽 서브트리에서 찾았으면 깊이에 1을 더해서 반환
    

#########################################################################################################################################
# lowestCommonAncestor(root, p, q): 두 노드 p와 q의 최저 공통 조상을 찾는 함수
def lowestCommonAncestor(root, p, q):
    if not root:  # 트리가 비어 있으면 None 반환
        return None
    
    if root.val > p.val and root.val > q.val:  # p와 q가 모두 root보다 작으면 왼쪽 서브트리로
        return lowestCommonAncestor(root.left, p, q)
    elif root.val < p.val and root.val < q.val:  # p와 q가 모두 root보다 크면 오른쪽 서브트리로
        return lowestCommonAncestor(root.right, p, q)
    else:  # root가 p와 q의 공통 조상이면 해당 root 반환
        return root
    

#########################################################################################################################################
# pathToNode(root, val, path=[]): 특정 값으로 가는 경로를 찾는 함수
def pathToNode(root, val, path=[]):
    if not root:  # 트리가 비어있으면 빈 리스트 반환
        return []
    
    path.append(root.val)  # 현재 노드 값을 경로에 추가
    
    if root.val == val:  # 값이 현재 노드와 일치하면 경로 반환
        return path
    elif val < root.val:  # 찾고자 하는 값이 현재 노드 값보다 작으면 왼쪽 자식으로 탐색
        return pathToNode(root.left, val, path)
    else:  # 찾고자 하는 값이 현재 노드 값보다 크면 오른쪽 자식으로 탐색
        return pathToNode(root.right, val, path)


# pathToNode(root, val): 주어진 값까지의 경로를 반환하는 함수
def pathToNode(root, val):
    if not root:  # 트리가 비어있으면 빈 리스트 반환
        return []
    
    if root.val == val:  # 값이 현재 노드와 일치하면 현재 노드 값을 포함한 경로 반환
        return [root.val]
    
    # 왼쪽 자식에서 경로를 찾기
    if val < root.val:
        left_path = pathToNode(root.left, val)
        if left_path:  # 경로가 비어있지 않으면 (값을 찾은 경우)
            return [root.val] + left_path
    
    # 오른쪽 자식에서 경로를 찾기
    else:
        right_path = pathToNode(root.right, val)
        if right_path:  # 경로가 비어있지 않으면 (값을 찾은 경우)
            return [root.val] + right_path
    
    return []  # 값을 찾지 못하면 빈 리스트 반환


#########################################################################################################################################
# allPaths(root): 모든 루트-리프 경로를 찾는 함수
def allPaths(root):
    def findPaths(node, path, paths):
        if not node:  # 노드가 없으면 리턴
            return
        path.append(node.val)  # 현재 노드 값을 경로에 추가
        if not node.left and not node.right:  # 리프 노드에 도달한 경우
            paths.append(list(path))  # 현재 경로를 결과에 추가
        else:
            findPaths(node.left, path, paths)  # 왼쪽 자식으로 재귀 호출
            findPaths(node.right, path, paths)  # 오른쪽 자식으로 재귀 호출
        path.pop()  # 백트래킹을 위해 현재 노드 값을 제거

    paths = []  # 모든 경로를 저장할 리스트
    findPaths(root, [], paths)
    return paths


#########################################################################################################################################
# kthSmallest(root, k): k번째로 작은 값을 찾는 함수
def kthSmallest(root, k):
    def inorder(node):
        if node:  # 노드가 존재하면
            yield from inorder(node.left)  # 왼쪽 서브트리의 값 순회
            yield node.val  # 현재 노드 값 반환
            yield from inorder(node.right)  # 오른쪽 서브트리의 값 순회

    gen = inorder(root)  # 중위 순회 생성기 초기화
    for _ in range(k - 1):  # k-1번 생성기에서 값을 건너뜀
        next(gen)
    return next(gen)  # k번째 값 반환
#######################################
def kthSmallest_(root, k):
    # 중위 순회 함수 정의
    def inorder(node, elements):
        if node:  # 노드가 존재하면
            inorder(node.left, elements)  # 왼쪽 서브트리 순회
            elements.append(node.val)  # 현재 노드 값 추가
            inorder(node.right, elements)  # 오른쪽 서브트리 순회

    elements = []  # 중위 순회 결과를 저장할 리스트
    inorder(root, elements)  # 중위 순회 실행
    return elements[k - 1]  # k번째 값 반환 (0-based 인덱스)


#########################################################################################################################################
# rangeSumBST(root, low, high): 주어진 범위 [low, high]의 합을 계산하는 함수
def rangeSumBST(root, low, high):
    if not root:  # 노드가 없으면 0 반환
        return 0
    if root.val < low:  # 노드 값이 low보다 작으면 오른쪽 서브트리만 탐색
        return rangeSumBST(root.right, low, high)
    if root.val > high:  # 노드 값이 high보다 크면 왼쪽 서브트리만 탐색
        return rangeSumBST(root.left, low, high)
    # 노드 값이 범위 내에 있으면, 왼쪽/오른쪽 서브트리의 합과 현재 노드 값을 더함
    return root.val + rangeSumBST(root.left, low, high) + rangeSumBST(root.right, low, high)


#########################################################################################################################################
# nodesAtDepth(root, depth): 특정 깊이에 있는 노드 값을 반환하는 함수
def nodesAtDepth(root, depth):
    """
    이진 트리에서 특정 깊이에 위치한 노드 값을 리스트로 반환합니다.
    root: 이진 트리의 루트 노드
    depth: 탐색할 깊이 (0부터 시작)
    반환값: 해당 깊이에 있는 노드 값들의 리스트
    """
    if not root:  # 노드가 없으면 빈 리스트 반환
        return []
    if depth == 0:  # 깊이가 0이면 현재 노드의 값을 리스트로 반환
        return [root.val]
    # 왼쪽과 오른쪽 서브트리에서 깊이를 감소시키며 탐색
    return nodesAtDepth(root.left, depth - 1) + nodesAtDepth(root.right, depth - 1)


#########################################################################################################################################
# descendingOrderTraversal(root): 이진 트리를 내림차순으로 순회하여 노드 값을 리스트로 반환
def descendingOrderTraversal(root):
    """
    이진 트리를 내림차순으로 순회하여 노드 값을 리스트로 반환합니다.
    root: 이진 트리의 루트 노드
    반환값: 내림차순 순회 결과를 담은 리스트
    """
    result = []  # 결과를 저장할 리스트

    # 내림차순 순회를 수행하는 헬퍼 함수
    def inorder(node):
        if node:  # 노드가 있으면
            inorder(node.right)  # 오른쪽 서브트리 순회
            result.append(node.val)  # 현재 노드 값을 결과 리스트에 추가
            inorder(node.left)  # 왼쪽 서브트리 순회
    
    inorder(root)  # 내림차순 순회를 시작
    return result  # 결과 반환


#########################################################################################################################################
# mirrorTree(root): 이진 트리를 대칭으로 뒤집는 함수 (미러링)
def mirrorTree(root):
    """
    이진 트리의 모든 노드를 대칭으로 뒤집어서 반환합니다.
    root: 이진 트리의 루트 노드
    반환값: 대칭으로 뒤집힌 트리의 루트 노드
    """
    if not root:  # 노드가 없으면 None 반환
        return None
    root.left, root.right = root.right, root.left  # 왼쪽과 오른쪽 자식 노드를 교환
    if root.left:  # 왼쪽 자식이 있으면 대칭적으로 뒤집기
        mirrorTree(root.left)
    if root.right:  # 오른쪽 자식이 있으면 대칭적으로 뒤집기
        mirrorTree(root.right)
    return root  # 대칭으로 바뀐 트리 반환


# invertTree(root): 트리를 뒤집는 함수
def invertTree(root):
    """
    이진 트리를 뒤집는 함수.
    각 노드에서 왼쪽 자식과 오른쪽 자식의 위치를 바꿈.
    
    root: 트리의 루트 노드
    반환값: 뒤집힌 트리의 루트 노드
    """
    if not root:
        return None  # 트리가 비어 있으면 None을 반환

    # 왼쪽 자식과 오른쪽 자식의 위치를 바꿈
    root.left, root.right = root.right, root.left

    # 왼쪽과 오른쪽 서브트리를 각각 재귀적으로 뒤집음
    invertTree(root.left)
    invertTree(root.right)

    return root  # 뒤집힌 트리의 루트 노드 반환


#########################################################################################################################################
# distanceBetweenNodes(root, p, q): 두 노드 p와 q 사이의 거리를 계산하는 함수 (노드 간 edge 개수?)
def distanceBetweenNodes(root, p, q):
    """
    주어진 두 노드 p와 q 사이의 거리를 계산합니다.
    root: 이진 트리의 루트 노드
    p, q: 거리 계산을 원하는 두 노드
    반환값: 두 노드 사이의 거리
    """
    
    # 최소 공통 조상 (LCA)을 찾는 함수
    def lowestCommonAncestor(root, p, q):
        if root is None or root == p or root == q:
            return root  # 루트가 None이거나 루트가 p나 q와 일치하면 그 노드를 반환
        left = lowestCommonAncestor(root.left, p, q)  # 왼쪽 서브트리에서 LCA를 찾음
        right = lowestCommonAncestor(root.right, p, q)  # 오른쪽 서브트리에서 LCA를 찾음
        
        # 왼쪽과 오른쪽 서브트리 모두에서 LCA가 발견되면, 현재 노드가 LCA임
        if left and right:
            return root
        # 왼쪽 서브트리에서만 LCA가 발견되면 왼쪽을 반환, 오른쪽 서브트리에서만 발견되면 오른쪽을 반환
        return left if left else right

    # LCA에서 주어진 노드까지의 거리를 계산하는 함수
    def distanceFromAncestor(node, target, distance=0):
        if not node:
            return -1  # 노드가 없으면 -1 반환
        if node == target:
            return distance  # 타겟 노드를 찾으면 현재 거리를 반환
        left_distance = distanceFromAncestor(node.left, target, distance + 1)  # 왼쪽 서브트리에서 거리 계산
        if left_distance != -1:
            return left_distance  # 왼쪽에서 타겟을 찾으면 거리를 반환
        return distanceFromAncestor(node.right, target, distance + 1)  # 오른쪽 서브트리에서 거리 계산

    # LCA를 찾고, LCA에서 p와 q까지의 거리를 각각 계산
    lca = lowestCommonAncestor(root, p, q)
    dist_p = distanceFromAncestor(lca, p)  # LCA에서 p까지의 거리
    dist_q = distanceFromAncestor(lca, q)  # LCA에서 q까지의 거리

    return dist_p + dist_q  # p와 q 사이의 거리 (LCA에서 각 노드까지의 거리 합산)


#########################################################################################################################################
# isValidBST(root): 이진 트리가 유효한 BST인지 확인하는 함수
def isValidBST(root):
    """
    주어진 이진 트리가 유효한 이진 탐색 트리(BST)인지 확인합니다.
    root: 이진 트리의 루트 노드
    반환값: 트리가 유효한 BST이면 True, 아니면 False
    """
    
    # helper 함수는 재귀적으로 트리를 순회하면서 값이 유효한 범위 내에 있는지 확인
    def helper(node, lower=float('-inf'), upper=float('inf')):
        if not node:
            return True  # 노드가 None이면 유효한 트리로 간주
        if node.val <= lower or node.val >= upper:
            return False  # 노드 값이 유효한 범위에 없으면 False 반환
        # 왼쪽 서브트리에는 'upper'를 현재 노드 값으로, 오른쪽 서브트리에는 'lower'를 현재 노드 값으로 설정
        return helper(node.left, lower, node.val) and helper(node.right, node.val, upper)
    
    return helper(root)


#########################################################################################################################################
# sumOfGreaterNodes(root): 각 노드의 값을 해당 노드보다 큰 노드들의 값의 합으로 갱신하는 함수
def sumOfGreaterNodes(root):
    """
    트리의 각 노드를 해당 노드보다 큰 노드들의 값의 합으로 갱신합니다.
    오른쪽 서브트리부터 처리하여 더 큰 값들을 먼저 합산합니다.
    root: 트리의 루트 노드
    반환값: 갱신된 트리
    """
    def dfs(node, sum_greater):
        # 트리가 비어 있으면 더 이상 진행할 필요가 없으므로 현재까지의 합 반환
        if not node:
            return sum_greater
        
        # 오른쪽 서브트리로 먼저 가서 더 큰 값들부터 처리
        sum_greater = dfs(node.right, sum_greater)
        
        # 현재 노드의 값에 더 큰 값들의 합을 더함
        node.val += sum_greater
        
        # 왼쪽 서브트리로 진행, 새로운 sum_greater는 현재 노드의 값
        return dfs(node.left, node.val)
    
    # 루트 노드부터 DFS 탐색 시작
    dfs(root, 0)
    
    # 갱신된 트리를 반환
    return root


#########################################################################################################################################
# maxPathSum(root): 트리에서 최대 경로 합을 구하는 함수
def maxPathSum(root):
    """
    트리에서 가장 큰 경로 합을 구하는 함수입니다.
    경로는 트리의 노드를 따라 이어지는 경로로, 반드시 루트에서 시작하거나 루트에서 끝나지 않아도 됩니다.
    root: 트리의 루트 노드
    반환값: 가장 큰 경로 합
    """
    
    def helper(node):
        # 현재 노드가 없다면, 경로 합은 0이고, 최대 경로 합은 음의 무한대
        if not node:
            return 0, float('-inf')
        
        # 왼쪽 서브트리와 오른쪽 서브트리에서 최대 경로 합을 구함
        left_single, left_max = helper(node.left)
        right_single, right_max = helper(node.right)
        
        # 현재 노드를 포함하는 경로에서 단일 경로 합을 계산
        # 왼쪽 서브트리에서 이어진 경로, 오른쪽 서브트리에서 이어진 경로, 현재 노드 자체를 고려
        single_path = max(left_single + node.val, right_single + node.val, node.val)
        
        # 현재 노드를 포함한 최대 경로 합을 계산
        max_path = max(left_max, right_max, left_single + node.val + right_single, single_path)
        
        # 이 함수는 두 값을 반환: 현재 노드를 포함한 경로의 합, 현재 노드를 포함한 최대 경로 합
        return single_path, max_path
    
    # 루트 노드부터 DFS 탐색을 시작하고, 최대 경로 합을 반환
    _, max_sum = helper(root)
    return max_sum


#########################################################################################################################################
# nodesInRange(root, low, high): 주어진 범위에 속하는 노드들의 값을 찾는 함수
def nodesInRange(root, low, high):
    """
    트리에서 주어진 범위 [low, high]에 포함되는 노드들의 값을 찾는 함수.
    범위 내의 값을 가진 노드를 DFS 방식으로 탐색하고, 해당 값을 결과에 추가함.
    
    root: 트리의 루트 노드
    low: 범위의 하한 값
    high: 범위의 상한 값
    반환값: 범위 내에 있는 노드들의 값이 담긴 리스트
    """
    result = []  # 결과를 저장할 리스트

    # DFS로 트리를 탐색하는 내부 함수
    def dfs(node):
        if not node:
            return  # 노드가 없으면 종료
        # 노드 값이 범위 내에 있으면 결과 리스트에 추가
        if low <= node.val <= high:
            result.append(node.val)
        # 왼쪽 서브트리 탐색 (현재 노드 값이 low보다 크면 왼쪽으로 가야함)
        if node.val > low:
            dfs(node.left)
        # 오른쪽 서브트리 탐색 (현재 노드 값이 high보다 작으면 오른쪽으로 가야함)
        if node.val < high:
            dfs(node.right)

    # DFS 탐색 시작
    dfs(root)
    
    return result  # 범위 내의 값들 반환


#########################################################################################################################################
# hasPathSum(root, sum): 경로의 합이 주어진 sum과 일치하는지 확인하는 함수
def hasPathSum(root, sum):
    """
    주어진 sum을 만들 수 있는 경로가 트리 안에 존재하는지 확인하는 함수.
    루트에서 리프 노드까지의 경로의 합이 sum과 같으면 True를 반환.
    
    root: 트리의 루트 노드
    sum: 찾고자 하는 경로 합
    반환값: 경로 합이 sum과 일치하는 경로가 있으면 True, 그렇지 않으면 False
    """
    if not root:
        return False  # 트리가 비어 있으면 False 반환

    # 리프 노드에 도달한 경우, 리프 노드의 값이 sum과 일치하는지 확인
    if not root.left and not root.right:
        return root.val == sum

    # 리프 노드가 아니라면, sum에서 현재 노드의 값을 빼고 왼쪽, 오른쪽 자식으로 재귀 호출
    sum -= root.val
    return hasPathSum(root.left, sum) or hasPathSum(root.right, sum)


#########################################################################################################################################
# inorderSuccessor(root, p): 주어진 노드 p의 중위 순회 후속 노드를 찾는 함수
def inorderSuccessor(root, p):
    """
    주어진 트리에서 p 노드의 중위 순회 후속 노드를 찾는 함수.
    BST에서 p 노드의 후속 노드는, p보다 큰 값들 중에서 중위 순회로 가장 먼저 나오는 노드이다.
    
    root: 트리의 루트 노드
    p: 중위 순회 후속 노드를 찾고자 하는 노드
    반환값: p의 중위 순회 후속 노드 또는 없으면 None
    """
    if not root:
        return None  # 트리가 비어 있으면 None 반환
    
    successor = None  # 후속 노드를 저장할 변수
    
    while root:
        # p 노드의 값이 현재 노드의 값보다 작으면, 후속 노드는 현재 노드일 수 있음
        if p.val < root.val:
            successor = root  # 현재 노드를 후속 후보로 설정
            root = root.left  # 왼쪽 서브트리에서 더 작은 값을 찾기 위해 이동
        else:
            root = root.right  # 현재 노드가 p보다 작으면, 오른쪽 서브트리로 이동
    
    return successor  # p의 중위 순회 후속 노드 반환


#########################################################################################################################################
# isChildSum(root): 트리가 자식 노드들의 합을 만족하는지 확인하는 함수
def isChildSum(root):
    """
    트리에서 모든 노드가 그 자식들의 값의 합보다 크거나 같은지 확인하는 함수.
    
    root: 트리의 루트 노드
    반환값: 트리가 자식 합 규칙을 만족하면 True, 아니면 False
    """
    # 트리가 비어 있거나 리프 노드일 경우 (자식이 없는 노드는 자동으로 True)
    if not root or (not root.left and not root.right):
        return True
    
    # 왼쪽 자식과 오른쪽 자식의 값을 구합니다. 자식이 없으면 0으로 처리.
    left_val = root.left.val if root.left else 0
    right_val = root.right.val if root.right else 0
    
    # 현재 노드의 값이 왼쪽 + 오른쪽 자식 값보다 크거나 같은지 확인하고,
    # 왼쪽과 오른쪽 자식 노드들에 대해서도 재귀적으로 검사
    return (root.val >= left_val + right_val) and isChildSum(root.left) and isChildSum(root.right)


#########################################################################################################################################
# sortedArrayToBST(nums): 정렬된 배열을 이진 검색 트리로 변환하는 함수
def sortedArrayToBST(nums):
    """
    정렬된 배열을 이진 검색 트리(BST)로 변환하는 함수.
    
    nums: 정렬된 배열 (리스트 형태)
    반환값: 이진 검색 트리의 루트 노드
    """
    if not nums:  # 배열이 비어 있으면 None을 반환
        return None
    
    # 배열의 중간값을 선택하여 루트 노드 생성
    mid = len(nums) // 2
    root = TreeNode(nums[mid])
    
    # 중간값을 제외한 왼쪽 절반과 오른쪽 절반을 재귀적으로 BST로 변환
    root.left = sortedArrayToBST(nums[:mid])  # 왼쪽 절반
    root.right = sortedArrayToBST(nums[mid + 1:])  # 오른쪽 절반
    
    return root


#########################################################################################################################################
# isIdentical(root1, root2): 두 트리가 동일한지 확인하는 함수
def isIdentical(root1, root2):
    """
    두 이진 트리가 동일한지 확인하는 함수.
    
    root1: 첫 번째 트리의 루트 노드
    root2: 두 번째 트리의 루트 노드
    반환값: 두 트리가 동일하면 True, 아니면 False
    """
    # 두 트리가 모두 None이면 동일한 트리이므로 True 반환
    if not root1 and not root2:
        return True
    
    # 두 트리 중 하나가 None이면 동일하지 않으므로 False 반환
    if not root1 or not root2:
        return False
    
    # 현재 노드의 값이 같고, 왼쪽과 오른쪽 서브트리가 동일한지 확인
    return (root1.val == root2.val) and isIdentical(root1.left, root2.left) and isIdentical(root1.right, root2.right)


#########################################################################################################################################
# diameterOfBinaryTree(root): 트리의 직경 (Diameter) 찾는 함수
def diameterOfBinaryTree(root):
    diameter = 0  # 직경을 계산할 변수
    
    # 트리의 직경을 구하는 함수 (DFS를 사용)
    def dfs(node):
        nonlocal diameter  # outer scope에서 diameter를 사용할 수 있도록 지정
        
        if not node:
            return 0  # 노드가 없으면 0을 반환 (깊이가 없으므로)

        # 왼쪽과 오른쪽 서브트리의 깊이를 구함
        left_depth = dfs(node.left)
        right_depth = dfs(node.right)
        
        # 트리의 직경은 왼쪽 깊이 + 오른쪽 깊이로 갱신
        diameter = max(diameter, left_depth + right_depth)
        
        # 현재 노드에서 가장 큰 깊이를 반환 (1 + 왼쪽/오른쪽 서브트리 깊이)
        return 1 + max(left_depth, right_depth)
    
    dfs(root)  # DFS를 시작하여 트리의 직경을 계산
    return diameter  # 계산된 직경 반환


#########################################################################################################################################
# diameterAndPathOfBinaryTree(root): 이진 트리의 직경과 직경을 이루는 경로를 계산하여 반환하는 함수
def diameterAndPathOfBinaryTree(root):
    diameter = 0  # 트리의 지름
    diameter_path = []  # 트리의 지름을 이루는 경로
    
    # 트리의 직경과 경로를 구하는 함수 (DFS를 사용)
    def dfs(node):
        nonlocal diameter, diameter_path  # 바깥 함수의 변수들에 접근
        
        if not node:
            return 0, []  # 노드가 없으면 깊이는 0, 경로는 빈 리스트
        
        left_depth, left_path = dfs(node.left)
        right_depth, right_path = dfs(node.right)
        
        # 현재 지름의 경로 구하기
        if left_depth + right_depth > diameter:
            diameter = left_depth + right_depth
            # 지름을 이루는 경로 구하기 (왼쪽 경로 + 현재 노드 + 오른쪽 경로)
            diameter_path = left_path[::-1] + [node.val] + right_path
        
        # 현재 노드에서 가장 큰 깊이와 경로 반환
        if left_depth >= right_depth:
            return 1 + left_depth, left_path + [node.val]
        else:
            return 1 + right_depth, right_path + [node.val]
    
    dfs(root)  # DFS를 시작하여 트리의 지름과 경로를 계산
    return diameter, diameter_path  # 계산된 지름과 경로 반환