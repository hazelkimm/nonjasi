class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class DoubleListNode:
    def __init__(self, x):
        self.val = x
        self.prev = None
        self.next = None

# 1. Array Palindrome Check and Conversion
def is_palindrome_array(arr):
    left, right = 0, len(arr) - 1
    while left < right:
        if arr[left] != arr[right]:
            return False
        left += 1
        right -= 1
    return True

def make_palindrome_array(arr):
    left, right = 0, len(arr) - 1
    while left < right:
        if arr[left] != arr[right]:
            arr[right] = arr[left]
        left += 1
        right -= 1
    return arr

def palindrome_array(s):
    return s == s[::-1]

def is_substring(s, t):
    return t in s


def max_palindromes_array(s: str):
    result = []
    
    for i in range(len(s)):
        for length in range(1, len(s) + 1 - i):
            substring = s[i:i + length]
            if palindrome_array(substring) and substring not in result:
                result.append(substring)
    
    sub = []
    for t in result:
        for ss in result:
            if t != ss and is_substring(ss, t):
                sub.append(t)
    sub = set(sub)

    for w in sub:
        result.remove(w)

    return result




# 2. LinkedList Palindrome Check and Conversion
def is_palindrome_linked_list(head):
    stack = []
    node = head
    while node:
        stack.append(node.val)
        node = node.next

    node = head
    while node:
        if node.val != stack.pop():
            return False
        node = node.next
    return True

def reverse_list(head):
    prev = None
    current = head
    while current:
        next_node = current.next
        current.next = prev
        prev = current
        current = next_node
    return prev



def palindrome(s: ListNode):
    chars = []
    curr = s
    while curr is not None:
        chars.append(curr.val)
        curr = curr.next

    for alpha in chars:
        if alpha != chars.pop():
            return False
    return True

def substring(s, t):
    if t in s:
        return True
    return False


def max_palindromes(s: ListNode):
    chars = []
    curr = s
    while curr is not None:
        chars.append(str(curr.val))  # 정수를 문자열로 변환하여 리스트에 추가
        curr = curr.next
    ss = ''.join(chars)  # 문자열 리스트를 결합하여 단일 문자열로 만듦

    result = []
    for i in range(len(ss)):
        for length in range(1, len(ss) + 1 - i):
            curr = s
            idx = 0
            while idx < i:
                curr = curr.next
                idx += 1
            
            s_copy = ListNode(curr.val)
            curr_copy = s_copy
            idx = 1
            while idx < length:
                curr = curr.next
                node = ListNode(curr.val)
                curr_copy.next = node
                curr_copy = curr_copy.next
                idx += 1

            if palindrome(s_copy) and ss[i:i+length] not in result:
                result.append(ss[i:i+length])

    sub = []
    for t in result:
        for ss in result:
            if t != ss and is_substring(ss, t):
                sub.append(t)
    sub = set(sub)

    for w in sub:
        result.remove(w)
    
    return result






# 3. Double LinkedList Palindrome Check and Conversion
def is_palindrome_double_linked_list(head):
    if not head:
        return True

    tail = head
    while tail.next:
        tail = tail.next

    while head != tail:
        if head.val != tail.val:
            return False
        if head.next == tail:
            break
        head = head.next
        tail = tail.prev

    return True

def make_palindrome_double_linked_list(head):
    if not head:
        return None

    tail = head
    while tail.next:
        tail = tail.next

    start = head
    while start != tail and start.prev != tail:
        if start.val != tail.val:
            tail.val = start.val
        start = start.next
        tail = tail.prev

    return head


def palindrome_dlist(head: DoubleListNode, length: int):
    start = head
    end = head
    
    for _ in range(length - 1):
        end = end.next
    
    while start and end and start != end and start.prev != end:
        if start.val != end.val:
            return False
        start = start.next
        end = end.prev
    
    return True

def max_palindromes_dlist(head: DoubleListNode):
    chars = []
    curr = head
    while curr is not None:
        chars.append(str(curr.val))  # 정수를 문자열로 변환하여 리스트에 추가
        curr = curr.next
    ss = ''.join(chars)  # 리스트를 문자열로 변환

    result = []
    for i in range(len(ss)):
        for length in range(1, len(ss)+1-i):
            curr = head
            idx = 0
            while idx < i:
                curr = curr.next
                idx += 1

            if palindrome_dlist(curr, length) and ss[i:i+length] not in result:
                result.append(ss[i:i+length])

    sub = []
    for t in result:
        for s in result:
            if t != s and is_substring(s, t):
                sub.append(t)
    sub = set(sub)

    for w in sub:
        result.remove(w)

    return result


def build_dlist_from_string(s: str) -> DoubleListNode:
    head = DoubleListNode(s[0])
    curr = head
    for char in s[1:]:
        new_node = DoubleListNode(char)
        curr.next = new_node
        new_node.prev = curr
        curr = new_node
    return head





# 4. Stack Palindrome Check and Conversion
def is_palindrome_stack(head):
    stack = []
    node = head
    while node:
        stack.append(node.val)
        node = node.next

    node = head
    while node:
        if node.val != stack.pop():
            return False
        node = node.next
    return True

def make_palindrome_stack(head):
    if not head:
        return None

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
        if stack:
            slow.val = stack.pop()
        slow = slow.next

    return head


def palindrome_stack(s):
    return s == s[::-1]

def max_palindromes_stack(s: str):
    result = []
    stack = []

    # 모든 부분 문자열을 스택을 사용하여 생성
    for i in range(len(s)):
        for j in range(i + 1, len(s) + 1):
            substring = s[i:j]
            stack.append(substring)

    # 스택에서 모든 부분 문자열을 꺼내면서 회문을 확인
    while stack:
        substring = stack.pop()
        if palindrome_stack(substring) and substring not in result:
            result.append(substring)

    # 부분 문자열 중 중복되는 회문을 제거
    sub = []
    for t in result:
        for ss in result:
            if t != ss and is_substring(ss, t):  # 여기에서 is_substring을 사용합니다.
                sub.append(t)
    sub = set(sub)

    for w in sub:
        result.remove(w)

    return result







# 6. Deque Palindrome Check and Conversion
from collections import deque

def is_palindrome_deque(head):
    dq = deque()
    node = head
    while node:
        dq.append(node.val)
        node = node.next

    while len(dq) > 1:
        if dq.popleft() != dq.pop():
            return False
    return True

def palindrome_deque(s):
    return s == s[::-1]

def is_substring(s, t):
    return t in s

def max_palindromes_deque(s: str):
    result = []
    q = deque()

    # 모든 부분 문자열을 덱에 저장
    for i in range(len(s)):
        for j in range(i + 1, len(s) + 1):
            substring = s[i:j]
            q.append(substring)

    # 덱에서 부분 문자열을 추출하면서 회문을 확인
    while q:
        substring = q.pop()
        if palindrome_deque(substring) and substring not in result:
            result.append(substring)

    # 부분 문자열 중 중복되는 회문을 제거
    sub = []
    for t in result:
        for ss in result:
            if t != ss and is_substring(ss, t):  # 여기서 is_substring을 사용합니다.
                sub.append(t)
    sub = set(sub)

    for w in sub:
        result.remove(w)

    return result



# 7. Dynamic Programming Palindrome Check and Conversion
def is_palindrome_dp(s):
    n = len(s)
    dp = [[False] * n for _ in range(n)]

    for i in range(n):
        dp[i][i] = True

    for length in range(2, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            if length == 2:
                dp[i][j] = (s[i] == s[j])
            else:
                dp[i][j] = (s[i] == s[j]) and dp[i + 1][j - 1]

    return dp[0][n - 1]

def make_palindrome_dp(s):
    n = len(s)
    dp = [[False] * n for _ in range(n)]
    changes = [[0] * n for _ in range(n)]

    for i in range(n):
        dp[i][i] = True

    for length in range(2, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            if s[i] == s[j]:
                dp[i][j] = True
                changes[i][j] = changes[i + 1][j - 1]
            else:
                if changes[i + 1][j] < changes[i][j - 1]:
                    changes[i][j] = changes[i + 1][j] + 1
                else:
                    changes[i][j] = changes[i][j - 1] + 1

    result = [''] * (len(s) + changes[0][n - 1])
    left, right = 0, len(result) - 1
    i, j = 0, n - 1

    while i <= j:
        if s[i] == s[j]:
            result[left] = s[i]
            result[right] = s[j]
            left += 1
            right -= 1
            i += 1
            j -= 1
        elif changes[i + 1][j] < changes[i][j - 1]:
            result[left] = s[i]
            result[right] = s[i]
            left += 1
            right -= 1
            i += 1
        else:
            result[left] = s[j]
            result[right] = s[j]
            left += 1
            right -= 1
            j -= 1

    return ''.join(result)


def max_palindromes_dp2(s: str):
    n = len(s)
    dp = [[False] * n for _ in range(n)]
    result = []

    # 길이가 1인 모든 부분 문자열은 회문이다.
    for i in range(n):
        dp[i][i] = True
        result.append(s[i])

    # 길이가 2인 부분 문자열에 대해 회문 여부 확인
    for i in range(n-1):
        if s[i] == s[i+1]:
            dp[i][i+1] = True
            result.append(s[i:i+2])

    # 길이가 3 이상인 부분 문자열에 대해 회문 여부 확인
    for length in range(3, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            if s[i] == s[j] and dp[i+1][j-1]:
                dp[i][j] = True
                result.append(s[i:j+1])

    # 결과 리스트에서 중복된 부분 문자열 제거
    sub = []
    for t in result:
        for ss in result:
            if t != ss and substring(ss, t):
                sub.append(t)
    sub = set(sub)

    for w in sub:
        result.remove(w)

    return result




def main():
    # Array example
    print("=== Array Example ===")
    arr = [1, 2, 3, 2, 1]
    print("Array:", arr)
    print("Array is Palindrome:", is_palindrome_array(arr))

    non_palindrome_arr = [1, 2, 3, 4, 5]
    print("\nNon-Palindrome Array:", non_palindrome_arr)
    print("Array is Palindrome:", is_palindrome_array(non_palindrome_arr))
    palindrome_arr = make_palindrome_array(non_palindrome_arr)
    print("Converted Palindrome Array:", palindrome_arr)
    print("Max Palindromes in Array:", max_palindromes_array("".join(map(str, non_palindrome_arr))))
    print()

    # LinkedList example
    print("=== LinkedList Example ===")
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(2)
    head.next.next.next.next = ListNode(1)
    print("LinkedList is Palindrome:", is_palindrome_linked_list(head))

    non_palindrome_head = ListNode(1)
    non_palindrome_head.next = ListNode(2)
    non_palindrome_head.next.next = ListNode(3)
    non_palindrome_head.next.next.next = ListNode(4)
    non_palindrome_head.next.next.next.next = ListNode(3)

    print("\nNon-Palindrome LinkedList is Palindrome:", is_palindrome_linked_list(non_palindrome_head))
    print("\nMax Palindromes in LinkedList:", max_palindromes(non_palindrome_head))
    print()

    # Double LinkedList example
    print("=== Double LinkedList Example ===")
    double_head = DoubleListNode(1)
    double_head.next = DoubleListNode(2)
    double_head.next.prev = double_head
    double_head.next.next = DoubleListNode(3)
    double_head.next.next.prev = double_head.next
    double_head.next.next.next = DoubleListNode(2)
    double_head.next.next.next.prev = double_head.next.next
    double_head.next.next.next.next = DoubleListNode(1)
    double_head.next.next.next.next.prev = double_head.next.next.next
    print("Double LinkedList is Palindrome:", is_palindrome_double_linked_list(double_head))

    non_palindrome_double_head = DoubleListNode(1)
    non_palindrome_double_head.next = DoubleListNode(2)
    non_palindrome_double_head.next.prev = non_palindrome_double_head
    non_palindrome_double_head.next.next = DoubleListNode(3)
    non_palindrome_double_head.next.next.prev = non_palindrome_double_head.next
    non_palindrome_double_head.next.next.next = DoubleListNode(4)
    non_palindrome_double_head.next.next.next.next = DoubleListNode(3)
    non_palindrome_double_head.next.next.next.prev = non_palindrome_double_head.next.next
    non_palindrome_double_head.next.next.next.next.prev = non_palindrome_double_head.next.next.next

    print("\nNon-Palindrome Double LinkedList is Palindrome:", is_palindrome_double_linked_list(non_palindrome_double_head))
    # palindrome_double_linked_list = make_palindrome_double_linked_list(non_palindrome_double_head)
    # print("Converted Palindrome Double LinkedList: ", end="")
    # node = palindrome_double_linked_list
    # while node:
    #     print(node.val, end=" ")
    #     node = node.next
    print("\nMax Palindromes in Double LinkedList:", max_palindromes_dlist(non_palindrome_double_head))
    print()

    # Stack example
    print("=== Stack Example ===")
    stack_head = ListNode(1)
    stack_head.next = ListNode(2)
    stack_head.next.next = ListNode(3)
    stack_head.next.next.next = ListNode(2)
    stack_head.next.next.next.next = ListNode(1)
    print("Stack is Palindrome:", is_palindrome_stack(stack_head))

    non_palindrome_stack_head = ListNode(1)
    non_palindrome_stack_head.next = ListNode(2)
    non_palindrome_stack_head.next.next = ListNode(3)
    non_palindrome_stack_head.next.next.next = ListNode(4)

    print("\nNon-Palindrome Stack is Palindrome:", is_palindrome_stack(non_palindrome_stack_head))
    palindrome_stack = make_palindrome_stack(non_palindrome_stack_head)
    print("Converted Palindrome Stack: ", end="")
    node = palindrome_stack
    while node:
        print(node.val, end=" ")
        node = node.next
    print("\nMax Palindromes in Stack:", max_palindromes_stack("".join(map(str, [1, 2, 3, 4]))))
    print()

    # Deque example
    print("=== Deque Example ===")
    deque_head = ListNode(1)
    deque_head.next = ListNode(2)
    deque_head.next.next = ListNode(3)
    deque_head.next.next.next = ListNode(2)
    deque_head.next.next.next.next = ListNode(1)
    print("Deque is Palindrome:", is_palindrome_deque(deque_head))

    non_palindrome_deque_head = ListNode(1)
    non_palindrome_deque_head.next = ListNode(2)
    non_palindrome_deque_head.next.next = ListNode(3)
    non_palindrome_deque_head.next.next.next = ListNode(4)
    non_palindrome_deque_head.next.next.next.next = ListNode(3)

    print("\nNon-Palindrome Deque is Palindrome:", is_palindrome_deque(non_palindrome_deque_head))
    print("\nMax Palindromes in Deque:", max_palindromes_deque("".join(map(str, [1, 2, 3, 4]))))
    print()

    # Dynamic Programming example
    print("=== Dynamic Programming Example ===")
    s = "abcba"
    print("String is Palindrome:", is_palindrome_dp(s))

    non_palindrome_str = "abcde"
    print("\nString is Palindrome:", is_palindrome_dp(non_palindrome_str))
    palindrome_str = make_palindrome_dp(non_palindrome_str)
    print("Converted Palindrome String:", palindrome_str)
    print("Max Palindromes in String:", max_palindromes_dp2("edcbabcde"))

if __name__ == "__main__":
    main()
