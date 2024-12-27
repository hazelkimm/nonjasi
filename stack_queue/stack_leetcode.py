# 20. Valid Parentheses
# Easy

# Topics
# Companies

# Hint
# Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

# An input string is valid if:

# Open brackets must be closed by the same type of brackets.
# Open brackets must be closed in the correct order.
# Every close bracket has a corresponding open bracket of the same type.

class Solution:
  def isValid(self, s: str) -> bool:
    stack = []

    for c in s:
      if c == '(':
        stack.append(')')
      elif c == '{':
        stack.append('}')
      elif c == '[':
        stack.append(']')
      elif not stack or stack.pop() != c:
        return False

    return not stack

# 32. Longest Valid Parentheses
# Hard

# Topics
# Companies
# Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses 
# substring.

class Solution:
  def longestValidParentheses(self, s: str) -> int:
    s2 = ')' + s
    # dp[i] := the length of the longest valid parentheses in the substring
    # s2[1..i]
    dp = [0] * len(s2)

    for i in range(1, len(s2)):
      if s2[i] == ')' and s2[i - dp[i - 1] - 1] == '(':
        dp[i] = dp[i - 1] + dp[i - dp[i - 1] - 2] + 2

    return max(dp)

# 42. Trapping Rain Water
# Solved
# Hard

# Topics
# Companies
# Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

class Solution:
  def trap(self, height: list[int]) -> int:
    if not height:
      return 0

    ans = 0
    l = 0
    r = len(height) - 1
    maxL = height[l]
    maxR = height[r]

    while l < r:
      if maxL < maxR:
        ans += maxL - height[l]
        l += 1
        maxL = max(maxL, height[l])
      else:
        ans += maxR - height[r]
        r -= 1
        maxR = max(maxR, height[r])

    return ans

# 71. Simplify Path
# Medium

# Topics
# Companies
# You are given an absolute path for a Unix-style file system, which always begins with a slash '/'. Your task is to transform this absolute path into its simplified canonical path.

# The rules of a Unix-style file system are as follows:

# A single period '.' represents the current directory.
# A double period '..' represents the previous/parent directory.
# Multiple consecutive slashes such as '//' and '///' are treated as a single slash '/'.
# Any sequence of periods that does not match the rules above should be treated as a valid directory or file name. For example, '...' and '....' are valid directory or file names.
# The simplified canonical path should follow these rules:

# The path must start with a single slash '/'.
# Directories within the path must be separated by exactly one slash '/'.
# The path must not end with a slash '/', unless it is the root directory.
# The path must not have any single or double periods ('.' and '..') used to denote current or parent directories.
# Return the simplified canonical path.

class Solution:
  def simplifyPath(self, path: str) -> str:
    stack = []

    for str in path.split('/'):
      if str in ('', '.'):
        continue
      if str == '..':
        if stack:
          stack.pop()
      else:
        stack.append(str)

    return '/' + '/'.join(stack)

# 84. Largest Rectangle in Histogram
# Hard

# Topics
# Companies
# Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

class Solution:
  def largestRectangleArea(self, heights: list[int]) -> int:
    ans = 0
    stack = []

    for i in range(len(heights) + 1):
      while stack and (i == len(heights) or heights[stack[-1]] > heights[i]):
        h = heights[stack.pop()]
        w = i - stack[-1] - 1 if stack else i
        ans = max(ans, h * w)
      stack.append(i)

    return ans

# 85. Maximal Rectangle
# Solved
# Hard

# Topics
# Companies
# Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

class Solution:
  def maximalRectangle(self, matrix: list[list[str]]) -> int:
    if not matrix:
      return 0

    ans = 0
    hist = [0] * len(matrix[0])

    def largestRectangleArea(heights: list[int]) -> int:
      ans = 0
      stack = []

      for i in range(len(heights) + 1):
        while stack and (i == len(heights) or heights[stack[-1]] > heights[i]):
          h = heights[stack.pop()]
          w = i - stack[-1] - 1 if stack else i
          ans = max(ans, h * w)
        stack.append(i)

      return ans

    for row in matrix:
      for i, num in enumerate(row):
        hist[i] = 0 if num == '0' else hist[i] + 1
      ans = max(ans, largestRectangleArea(hist))

    return ans

# 94. Binary Tree Inorder Traversal
# Easy

# Topics
# Companies
# Given the root of a binary tree, return the inorder traversal of its nodes' values.

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
        
class Solution:
  def inorderTraversal(self, root: TreeNode | None) -> list[int]:
    ans = []
    stack = []

    while root or stack:
      while root:
        stack.append(root)
        root = root.left
      root = stack.pop()
      ans.append(root.val)
      root = root.right

    return ans

# 114. Flatten Binary Tree to Linked List
# Solved
# Medium

# Topics
# Companies

# Hint
# Given the root of a binary tree, flatten the tree into a "linked list":

# The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
# The "linked list" should be in the same order as a pre-order traversal of the binary tree.

class Solution:
  def flatten(self, root: TreeNode | None) -> None:
    if not root:
      return

    while root:
      if root.left:
        # Find the rightmost root
        rightmost = root.left
        while rightmost.right:
          rightmost = rightmost.right
        # Rewire the connections
        rightmost.right = root.right
        root.right = root.left
        root.left = None
      # Move on to the right side of the tree
      root = root.right
      
# 143. Reorder List
# Medium

# Topics
# Companies
# You are given the head of a singly linked-list. The list can be represented as:

# L0 → L1 → … → Ln - 1 → Ln
# Reorder the list to be on the following form:

# L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
# You may not modify the values in the list's nodes. Only nodes themselves may be changed.

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
  def reorderList(self, head: ListNode) -> None:
    def findMid(head: ListNode):
      prev = None
      slow = head
      fast = head

      while fast and fast.next:
        prev = slow
        slow = slow.next
        fast = fast.next.next
      prev.next = None

      return slow

    def reverse(head: ListNode) -> ListNode:
      prev = None
      curr = head

      while curr:
        next = curr.next
        curr.next = prev
        prev = curr
        curr = next

      return prev

    def merge(l1: ListNode, l2: ListNode) -> None:
      while l2:
        next = l1.next
        l1.next = l2
        l1 = l2
        l2 = next

    if not head or not head.next:
      return

    mid = findMid(head)
    reversed = reverse(mid)
    merge(head, reversed)
    
# 144. Binary Tree Preorder Traversal
# Easy

# Topics
# Companies
# Given the root of a binary tree, return the preorder traversal of its nodes' values.

class Solution:
  def preorderTraversal(self, root: TreeNode | None) -> list[int]:
    if not root:
      return []

    ans = []
    stack = [root]

    while stack:
      node = stack.pop()
      ans.append(node.val)
      if node.right:
        stack.append(node.right)
      if node.left:
        stack.append(node.left)

    return ans

# 145. Binary Tree Postorder Traversal
# Easy

# Topics
# Companies
# Given the root of a binary tree, return the postorder traversal of its nodes' values.

class Solution:
  def postorderTraversal(self, root: TreeNode | None) -> list[int]:
    if not root:
      return []

    ans = []
    stack = [root]

    while stack:
      node = stack.pop()
      ans.append(node.val)
      if node.left:
        stack.append(node.left)
      if node.right:
        stack.append(node.right)

    return ans[::-1]

# 150. Evaluate Reverse Polish Notation
# Medium

# Topics
# Companies
# You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.

# Evaluate the expression. Return an integer that represents the value of the expression.

# Note that:

# The valid operators are '+', '-', '*', and '/'.
# Each operand may be an integer or another expression.
# The division between two integers always truncates toward zero.
# There will not be any division by zero.
# The input represents a valid arithmetic expression in a reverse polish notation.
# The answer and all the intermediate calculations can be represented in a 32-bit integer.

class Solution:
  def evalRPN(self, tokens: list[str]) -> int:
    stack = []
    op = {
        '+': lambda a, b: a + b,
        '-': lambda a, b: a - b,
        '*': lambda a, b: a * b,
        '/': lambda a, b: int(a / b),
    }

    for token in tokens:
      if token in op:
        b = stack.pop()
        a = stack.pop()
        stack.append(op[token](a, b))
      else:
        stack.append(int(token))

    return stack.pop()

# 155. Min Stack
# Solved
# Medium

# Topics
# Companies

# Hint
# Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

# Implement the MinStack class:

# MinStack() initializes the stack object.
# void push(int val) pushes the element val onto the stack.
# void pop() removes the element on the top of the stack.
# int top() gets the top element of the stack.
# int getMin() retrieves the minimum element in the stack.
# You must implement a solution with O(1) time complexity for each function.

class MinStack:
  def __init__(self):
    self.stack = []

  def push(self, x: int) -> None:
    mn = x if not self.stack else min(self.stack[-1][1], x)
    self.stack.append([x, mn])

  def pop(self) -> None:
    self.stack.pop()

  def top(self) -> int:
    return self.stack[-1][0]

  def getMin(self) -> int:
    return self.stack[-1][1]

# 173. Binary Search Tree Iterator
# Solved
# Medium

# Topics
# Companies
# Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):

# BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
# boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
# int next() Moves the pointer to the right, then returns the number at the pointer.
# Notice that by initializing the pointer to a non-existent smallest number, the first call to next() will return the smallest element in the BST.

# You may assume that next() calls will always be valid. That is, there will be at least a next number in the in-order traversal when next() is called.

class BSTIterator:
  def __init__(self, root: TreeNode | None):
    self.stack = []
    self._pushLeftsUntilNull(root)

  def next(self) -> int:
    root = self.stack.pop()
    self._pushLeftsUntilNull(root.right)
    return root.val

  def hasNext(self) -> bool:
    return self.stack

  def _pushLeftsUntilNull(self, root: TreeNode | None) -> None:
    while root:
      self.stack.append(root)
      root = root.left
      
# 224. Basic Calculator
# Hard

# Topics
# Companies
# Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.

# Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

# Example 1:

# Input: s = "1 + 1"
# Output: 2
# Example 2:

# Input: s = " 2-1 + 2 "
# Output: 3
# Example 3:

# Input: s = "(1+(4+5+2)-3)+(6+8)"
# Output: 23

class Solution:
  def calculate(self, s: str) -> int:
    ans = 0
    num = 0
    sign = 1
    stack = [sign]  # stack[-1]: the current environment's sign

    for c in s:
      if c.isdigit():
        num = num * 10 + int(c)
      elif c == '(':
        stack.append(sign)
      elif c == ')':
        stack.pop()
      elif c == '+' or c == '-':
        ans += sign * num
        sign = (1 if c == '+' else -1) * stack[-1]
        num = 0

    return ans + sign * num

# 225. Implement Stack using Queues
# Easy

# Topics
# Companies
# Implement a last-in-first-out (LIFO) stack using only two queues. The implemented stack should support all the functions of a normal stack (push, top, pop, and empty).

# Implement the MyStack class:

# void push(int x) Pushes element x to the top of the stack.
# int pop() Removes the element on the top of the stack and returns it.
# int top() Returns the element on the top of the stack.
# boolean empty() Returns true if the stack is empty, false otherwise.
# Notes:

# You must use only standard operations of a queue, which means that only push to back, peek/pop from front, size and is empty operations are valid.
# Depending on your language, the queue may not be supported natively. You may simulate a queue using a list or deque (double-ended queue) as long as you use only a queue's standard operations.

import collections

class MyStack:
  def __init__(self):
    self.q = collections.deque()

  def push(self, x: int) -> None:
    self.q.append(x)
    for _ in range(len(self.q) - 1):
      self.q.append(self.q.popleft())

  def pop(self) -> int:
    return self.q.popleft()

  def top(self) -> int:
    return self.q[0]

  def empty(self) -> bool:
    return not self.q

# 227. Basic Calculator II
# Medium

# Topics
# Companies
# Given a string s which represents an expression, evaluate this expression and return its value. 

# The integer division should truncate toward zero.

# You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

# Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

class Solution:
  def calculate(self, s: str) -> int:
    ans = 0
    prevNum = 0
    currNum = 0
    op = '+'

    for i, c in enumerate(s):
      if c.isdigit():
        currNum = currNum * 10 + int(c)
      if not c.isdigit() and c != ' ' or i == len(s) - 1:
        if op == '+' or op == '-':
          ans += prevNum
          prevNum = (currNum if op == '+' else -currNum)
        elif op == '*':
          prevNum *= currNum
        elif op == '/':
          prevNum = int(prevNum / currNum)
        op = c
        currNum = 0

    return ans + prevNum

# 232. Implement Queue using Stacks
# Easy

# Topics
# Companies
# Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

# Implement the MyQueue class:

# void push(int x) Pushes element x to the back of the queue.
# int pop() Removes the element from the front of the queue and returns it.
# int peek() Returns the element at the front of the queue.
# boolean empty() Returns true if the queue is empty, false otherwise.
# Notes:

# You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
# Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.

class MyQueue:
  def __init__(self):
    self.input = []
    self.output = []

  def push(self, x: int) -> None:
    self.input.append(x)

  def pop(self) -> int:
    self.peek()
    return self.output.pop()

  def peek(self) -> int:
    if not self.output:
      while self.input:
        self.output.append(self.input.pop())
    return self.output[-1]

  def empty(self) -> bool:
    return not self.input and not self.output

# 234. Palindrome Linked List
# Easy

# Topics
# Companies
# Given the head of a singly linked list, return true if it is a 
# palindrome
#  or false otherwise.

class Solution:
  def isPalindrome(self, head: ListNode) -> bool:
    def reverseList(head: ListNode) -> ListNode:
      prev = None
      curr = head
      while curr:
        next = curr.next
        curr.next = prev
        prev = curr
        curr = next
      return prev

    slow = head
    fast = head

    while fast and fast.next:
      slow = slow.next
      fast = fast.next.next

    if fast:
      slow = slow.next
    slow = reverseList(slow)

    while slow:
      if slow.val != head.val:
        return False
      slow = slow.next
      head = head.next

    return True

# 255. Verify Preorder sequence in Binary Search (Locked)

import math

class Solution:
  def verifyPreorder(self, preorder: list[int]) -> list[int]:
    low = -math.inf
    stack = []

    for p in preorder:
      if p < low:
        return False
      while stack and stack[-1] < p:
        low = stack.pop()
      stack.append(p)

    return True

# 272. Closest Binary Search Tree II (Locked)
class Solution:
  def closestKValues(
      self,
      root: TreeNode | None,
      target: float,
      k: int,
  ) -> list[int]:
    dq = collections.deque()

    def inorder(root: TreeNode | None) -> None:
      if not root:
        return

      inorder(root.left)
      dq.append(root.val)
      inorder(root.right)

    inorder(root)

    while len(dq) > k:
      if abs(dq[0] - target) > abs(dq[-1] - target):
        dq.popleft()
      else:
        dq.pop()

    return list(dq)

# 316. Remove Duplicate Letters
# Medium

# Topics
# Companies

# Hint
# Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is 
# the smallest in lexicographical order
# among all possible results.

import string

class Solution:
  def removeDuplicateLetters(self, s: str) -> str:
    ans = []
    count = collections.Counter(s)
    used = [False] * 26

    for c in s:
      count[c] -= 1
      if used[string.ascii_lowercase.index(c)]:
        continue
      while ans and ans[-1] > c and count[ans[-1]] > 0:
        used[ord(ans[-1]) - ord('a')] = False
        ans.pop()
      ans.append(c)
      used[ord(ans[-1]) - ord('a')] = True

    return ''.join(ans)

# 321. Create Maximum Number
# Hard

# Topics
# Companies
# You are given two integer arrays nums1 and nums2 of lengths m and n respectively. nums1 and nums2 represent the digits of two numbers. You are also given an integer k.

# Create the maximum number of length k <= m + n from digits of the two numbers. The relative order of the digits from the same array must be preserved.

# Return an array of the k digits representing the answer.

class Solution:
  def maxNumber(self, nums1: list[int], nums2: list[int], k: int) -> list[int]:
    def maxArray(nums: list[int], k: int) -> list[int]:
      res = []
      toTop = len(nums) - k
      for num in nums:
        while res and res[-1] < num and toTop > 0:
          res.pop()
          toTop -= 1
        res.append(num)
      return res[:k]

    def merge(nums1: list[int], nums2: list[int]) -> list[int]:
      return [max(nums1, nums2).pop(0) for _ in nums1 + nums2]

    return max(merge(maxArray(nums1, i), maxArray(nums2, k - i))
               for i in range(k + 1)
               if i <= len(nums1) and k - i <= len(nums2))
    
# 331. Verify Preorder Serialization of a Binary Tree
# Medium

# Topics
# Companies
# One way to serialize a binary tree is to use preorder traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as '#'.


# For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where '#' represents a null node.

# Given a string of comma-separated values preorder, return true if it is a correct preorder traversal serialization of a binary tree.

# It is guaranteed that each comma-separated value in the string must be either an integer or a character '#' representing null pointer.

# You may assume that the input format is always valid.

# For example, it could never contain two consecutive commas, such as "1,,3".
# Note: You are not allowed to reconstruct the tree.

class Solution:
  def isValidSerialization(self, preorder: str) -> bool:
    degree = 1  # out-degree (children) - in-degree (parent)

    for node in preorder.split(','):
      degree -= 1
      if degree < 0:
        return False
      if node != '#':
        degree += 2

    return degree == 0

# 341. Flatten Nested List Iterator
# Medium

# Topics
# Companies
# You are given a nested list of integers nestedList. Each element is either an integer or a list whose elements may also be integers or other lists. Implement an iterator to flatten it.

# Implement the NestedIterator class:

# NestedIterator(List<NestedInteger> nestedList) Initializes the iterator with the nested list nestedList.
# int next() Returns the next integer in the nested list.
# boolean hasNext() Returns true if there are still some integers in the nested list and false otherwise.
# Your code will be tested with the following pseudocode:

# initialize iterator with nestedList
# res = []
# while iterator.hasNext()
#     append iterator.next() to the end of res
# return res
# If res matches the expected flattened list, then your code will be judged as correct.

# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """
#class NestedInteger:
#    def isInteger(self) -> bool:
#        """
#        @return True if this NestedInteger holds a single integer, rather than a nested list.
#        """
#
#    def getInteger(self) -> int:
#        """
#        @return the single integer that this NestedInteger holds, if it holds a single integer
#        Return None if this NestedInteger holds a nested list
#        """
#
#    def getList(self) -> [NestedInteger]:
#        """
#        @return the nested list that this NestedInteger holds, if it holds a nested list
#        Return None if this NestedInteger holds a single integer
#        """

# class NestedIterator:
#   def __init__(self, nestedList: list[NestedInteger]):
#     self.stack: list[NestedInteger] = []
#     self.addInteger(nestedList)

#   def next(self) -> int:
#     return self.stack.pop().getInteger()

#   def hasNext(self) -> bool:
#     while self.stack and not self.stack[-1].isInteger():
#       self.addInteger(self.stack.pop().getList())
#     return self.stack

#   # addInteger([1, [4, [6]]]) . stack = [[4, [6]], 1]
#   # addInteger([4, [6]]) . stack = [[6], 4]
#   # addInteger([6]) . stack = [6]
#   def addInteger(self, nestedList: list[NestedInteger]) -> None:
#     for n in reversed(nestedList):
#       self.stack.append(n)

# 364. Nested List Weight Sum II (Locked)

# class Solution:
#   def depthSumInverse(self, nestedList: list[NestedInteger]) -> int:
#     ans = 0
#     prevSum = 0
#     q = collections.deque(nestedList)

#     while q:
#       for _ in range(len(q)):
#         ni = q.popleft()
#         if ni.isInteger():
#           prevSum += ni.getInteger()
#         else:
#           for nextNi in ni.getList():
#             q.append(nextNi)
#       ans += prevSum

#     return ans

