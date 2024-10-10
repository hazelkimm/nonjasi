# def createLinkedList(list):# list로 Linked List 생성
# def printLinkedList(head):# Linked List 를 프린트함
# def reverseLinkedList(head):    # 뒤집기
# def copyLinkedList(head):    # copy 하기
# def copyReverseLinkedList(head): # copy 후 뒤집어서 원본 훼손 안시키기
# def is_palindrome(head):  # palindrome 체크하기
# def removeElements(head: Optional[LinkedNode], val: int) -> Optional[LinkedNode]:    # 특정원소 제거하기
# def getIntersectionNode(headA: LinkedNode, headB: LinkedNode) -> Optional[LinkedNode]:# 두 리스트가 합쳐지는 부분 찾기
# def findMid(head: LinkedNode) -> LinkedNode:# 리스트의 중심부 찾기 
# def merge(head1: LinkedNode, head2: LinkedNode) -> LinkedNode:# 리스트 합치기
# def sortingLL(head: LinkedNode) -> LinkedNode:# 리스트 mergeSort
# def get_length(head):    # 리스트 길이 얻기
# def all_substrings(s: LinkedNode):    # 모든 substring을 리스트에 담아서 리턴
# def all_subsequences(s: LinkedNode):# 리스트에 담아서 리턴
    
    
from typing import Optional

class LinkedNode:
    def __init__(self, x):
        self.val = x
        self.next = None
# list로 Linked List 생성
def createLinkedList(list):
    if not list:
        return None
    
    head = LinkedNode(list[0])
    current = head
    
    for value in list[1:]:
        current.next = LinkedNode(value)
        current = current.next
    
    return head
# Linked List 를 프린트함
def printLinkedList(head):
    if not head:
        print('[]')        
    else:
        cursor = head
        print('[',end = '')
        while cursor:
            if cursor.next:
                print(cursor.val,',',end = '',sep = '')
            else :
                print(cursor.val,']',end = '\n',sep = '')
            cursor = cursor.next
# 뒤집기
def reverseLinkedList(head):
    prev = None
    curr = head
    
    while curr:
        next_node = curr.next
        curr.next = prev
        prev = curr
        curr = next_node
        
    return prev
# copy 하기
def copyLinkedList(head):
    if not head:
        return None
    
    new_head = LinkedNode(head.val)  # 첫 번째 노드 복사
    
    current_old = head.next
    current_new = new_head
    
    while current_old:
        current_new.next = LinkedNode(current_old.val)  # 현재 노드 복사
        current_old = current_old.next
        current_new = current_new.next
    
    return new_head
# copy 후 뒤집어서 원본 훼손 안시키기
def copyReverseLinkedList(head):
    copyed = copyLinkedList(head)
    reversed = reverseLinkedList(copyed)
    return reversed
# palindrome 체크하기
def is_palindrome(head):
    stack = []
    slow = head
    fast = head

    while fast and fast.next:
        stack.append(slow.val)
        slow = slow.next
        fast = fast.next.next

    if fast:
        slow = slow.next

    while slow:
        top = stack.pop()
        if top != slow.val:
            return False
        slow = slow.next

    return True
# 특정원소 제거하기
def removeElements(head: Optional[LinkedNode], val: int) -> Optional[LinkedNode]:

    sentinel = LinkedNode(None)
    sentinel.next = head
    p = sentinel 

    while p:
        if p.next and p.next.val == val:
            if p.next.next:
                p.next = p.next.next
            else :
                p.next = None

        else :
            p = p.next

    return sentinel.next
# 두 리스트가 합쳐지는 부분 찾기
def getIntersectionNode(headA: LinkedNode, headB: LinkedNode) -> Optional[LinkedNode]:
        
    p1 = headA
    p2 = headB

    while p1 != p2:
        p1 = p1.next if p1 else headB
        p2 = p2.next if p2 else headA
    
    return p1
# 리스트의 중심부 찾기 
def findMid(head: LinkedNode) -> LinkedNode:
    if not head:
        return head
    slow, fast = head, head.next
    while fast and fast.next:
        fast = fast.next.next
        slow = slow.next
    return slow
# 리스트 합치기
def merge(head1: LinkedNode, head2: LinkedNode) -> LinkedNode:
    sentinel = LinkedNode(None)
    cursor = sentinel

    while head1 and head2:
        if head1.val > head2.val:
            cursor.next = head1
            head1 = head1.next
        else:
            cursor.next = head2
            head2 = head2.next
        cursor = cursor.next
    
    cursor.next = head1 or head2
    
    return sentinel.next
# 리스트 mergeSort
def sortingLL(head: LinkedNode) -> LinkedNode:
    #len=1 or 2
    if not head or not head.next: 
        return head
    #[head~mid] [mid.next,end]
    mid = findMid(head)
    nextmid = mid.next
    mid.next = None

    left = sortingLL(head)
    right = sortingLL(nextmid)

    sortedList = merge(left, right)
    return sortedList
# 리스트 길이 얻기
def get_length(head):
    cursor = head
    output = 0
    while cursor:
        output += 1
        cursor = cursor.next
    return output
# t가 s의 서브리스트인가?
def substring(head1, head2):
    # Check if head2 is a sublist of head1
    curr1 = head1
    while curr1:
        curr2 = head2
        temp = curr1
        while curr2 and temp and curr2.val == temp.val:
            curr2 = curr2.next
            temp = temp.next
        if not curr2:
            return True
        curr1 = curr1.next
    
    return False

# 리스트에 담아서 리턴
def all_substrings(s: LinkedNode):
    substrings = []
    current = s

    while current:
        temp = current
        while temp:
            substring = []
            runner = current
            while runner != temp.next:
                substring.append(runner.val)
                runner = runner.next
            substrings.append(substring)
            temp = temp.next

        current = current.next

    return substrings

# 리스트에 담아서 리턴
def all_subsequences(s: LinkedNode):
    def backtrack(start, current_subsequence):
        if start is None:
            return

        # Include the current node in the subsequence
        current_subsequence.append(start.val)
        subsequences.append(current_subsequence.copy())

        # Recur with the current node excluded
        backtrack(start.next, current_subsequence)

        # Backtrack to exclude the current node for other combinations
        current_subsequence.pop()
        backtrack(start.next, current_subsequence)

    subsequences = []
    backtrack(s, [])

    return subsequences

   
if __name__ == '__main__':
    head = createLinkedList([1,2,3])
    rev = copyReverseLinkedList(head)
    printLinkedList(head)
    printLinkedList(rev)
