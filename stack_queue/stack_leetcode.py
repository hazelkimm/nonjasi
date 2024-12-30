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

# 385. Mini Parser
# Medium

# Topics
# Companies
# Given a string s represents the serialization of a nested list, implement a parser to deserialize it and return the deserialized NestedInteger.

# Each element is either an integer or a list whose elements may also be integers or other lists.

# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """
#class NestedInteger:
#    def __init__(self, value=None):
#        """
#        If value is not specified, initializes an empty list.
#        Otherwise initializes a single integer equal to value.
#        """
#
#    def isInteger(self):
#        """
#        @return True if this NestedInteger holds a single integer, rather than a nested list.
#        :rtype bool
#        """
#
#    def add(self, elem):
#        """
#        Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
#        :rtype void
#        """
#
#    def setInteger(self, value):
#        """
#        Set this NestedInteger to hold a single integer equal to value.
#        :rtype void
#        """
#
#    def getInteger(self):
#        """
#        @return the single integer that this NestedInteger holds, if it holds a single integer
#        Return None if this NestedInteger holds a nested list
#        :rtype int
#        """
#
#    def getList(self):
#        """
#        @return the nested list that this NestedInteger holds, if it holds a nested list
#        Return None if this NestedInteger holds a single integer
#        :rtype List[NestedInteger]
#        """

# class Solution:
#   def deserialize(self, s: str) -> NestedInteger:
#     if s[0] != '[':
#       return NestedInteger(int(s))

#     stack = []

#     for i, c in enumerate(s):
#       if c == '[':
#         stack.append(NestedInteger())
#         start = i + 1
#       elif c == ',':
#         if i > start:
#           num = int(s[start:i])
#           stack[-1].add(NestedInteger(num))
#         start = i + 1
#       elif c == ']':
#         popped = stack.pop()
#         if i > start:
#           num = int(s[start:i])
#           popped.add(NestedInteger(num))
#         if stack:
#           stack[-1].add(popped)
#         else:
#           return popped
#         start = i + 1

# 388. Longest Absolute File Path
# Medium

# Topics
# Companies
# Suppose we have a file system that stores both files and directories. An example of one system is represented in the following picture:



# Here, we have dir as the only directory in the root. dir contains two subdirectories, subdir1 and subdir2. subdir1 contains a file file1.ext and subdirectory subsubdir1. subdir2 contains a subdirectory subsubdir2, which contains a file file2.ext.

# In text form, it looks like this (with ⟶ representing the tab character):

# dir
# ⟶ subdir1
# ⟶ ⟶ file1.ext
# ⟶ ⟶ subsubdir1
# ⟶ subdir2
# ⟶ ⟶ subsubdir2
# ⟶ ⟶ ⟶ file2.ext
# If we were to write this representation in code, it will look like this: "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext". Note that the '\n' and '\t' are the new-line and tab characters.

# Every file and directory has a unique absolute path in the file system, which is the order of directories that must be opened to reach the file/directory itself, all concatenated by '/'s. Using the above example, the absolute path to file2.ext is "dir/subdir2/subsubdir2/file2.ext". Each directory name consists of letters, digits, and/or spaces. Each file name is of the form name.extension, where name and extension consist of letters, digits, and/or spaces.

# Given a string input representing the file system in the explained format, return the length of the longest absolute path to a file in the abstracted file system. If there is no file in the system, return 0.

# Note that the testcases are generated such that the file system is valid and no file or directory name has length 0.

 

# Example 1:


# Input: input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
# Output: 20
# Explanation: We have only one file, and the absolute path is "dir/subdir2/file.ext" of length 20.
# Example 2:


# Input: input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
# Output: 32
# Explanation: We have two files:
# "dir/subdir1/file1.ext" of length 21
# "dir/subdir2/subsubdir2/file2.ext" of length 32.
# We return 32 since it is the longest absolute path to a file.
# Example 3:

# Input: input = "a"
# Output: 0
# Explanation: We do not have any files, just a single directory named "a".

class Solution:
  def lengthLongestPath(self, input: str) -> int:
    ans = 0
    stack = [(-1, 0)]  # placeholder

    for token in input.split('\n'):
      depth = token.count('\t')
      token = token.replace('\t', '')
      while depth <= stack[-1][0]:
        stack.pop()
      if '.' in token:  # `token` is file.
        ans = max(ans, stack[-1][1] + len(token))
      else:  # directory + '/'
        stack.append((depth, stack[-1][1] + len(token) + 1))

    return ans

# 394. Decode String
# Medium

# Topics
# Companies
# Given an encoded string, return its decoded string.

# The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

# You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].

# The test cases are generated so that the length of the output will never exceed 105.

class Solution:
  def decodeString(self, s: str) -> str:
    stack = []  # (prevStr, repeatCount)
    currStr = ''
    currNum = 0

    for c in s:
      if c.isdigit():
        currNum = currNum * 10 + int(c)
      else:
        if c == '[':
          stack.append((currStr, currNum))
          currStr = ''
          currNum = 0
        elif c == ']':
          prevStr, num = stack.pop()
          currStr = prevStr + num * currStr
        else:
          currStr += c

    return currStr

# 402. Remove K Digits
# Medium

# Topics
# Companies
# Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num.

 

# Example 1:

# Input: num = "1432219", k = 3
# Output: "1219"
# Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
# Example 2:

# Input: num = "10200", k = 1
# Output: "200"
# Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
# Example 3:

# Input: num = "10", k = 2
# Output: "0"
# Explanation: Remove all the digits from the number and it is left with nothing which is 0.

class Solution:
  def removeKdigits(self, num: str, k: int) -> str:
    if len(num) == k:
      return '0'

    ans = []
    stack = []

    for i, digit in enumerate(num):
      while k > 0 and stack and stack[-1] > digit:
        stack.pop()
        k -= 1
      stack.append(digit)

    for _ in range(k):
      stack.pop()

    for c in stack:
      if c == '0' and not ans:
        continue
      ans.append(c)

    return ''.join(ans) if ans else '0'

# 445. Add Two Numbers II
# Medium

# Topics
# Companies
# You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

# You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 

# Example 1:


# Input: l1 = [7,2,4,3], l2 = [5,6,4]
# Output: [7,8,0,7]
# Example 2:

# Input: l1 = [2,4,3], l2 = [5,6,4]
# Output: [8,0,7]
# Example 3:

# Input: l1 = [0], l2 = [0]
# Output: [0]

class Solution:
  def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
    stack1 = []
    stack2 = []

    while l1:
      stack1.append(l1)
      l1 = l1.next

    while l2:
      stack2.append(l2)
      l2 = l2.next

    head = None
    carry = 0

    while carry or stack1 or stack2:
      if stack1:
        carry += stack1.pop().val
      if stack2:
        carry += stack2.pop().val
      node = ListNode(carry % 10)
      node.next = head
      head = node
      carry //= 10

    return head

# 456. 132 Pattern
# Medium

# Topics
# Companies
# Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].

# Return true if there is a 132 pattern in nums, otherwise, return false.

 

# Example 1:

# Input: nums = [1,2,3,4]
# Output: false
# Explanation: There is no 132 pattern in the sequence.
# Example 2:

# Input: nums = [3,1,4,2]
# Output: true
# Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
# Example 3:

# Input: nums = [-1,3,2,0]
# Output: true
# Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].

class Solution:
  def find132pattern(self, nums: list[int]) -> bool:
    stack = []  # a decreasing stack
    ak = -math.inf  # Find a seq, where ai < ak < aj.

    for num in reversed(nums):
      # If ai < ak, done because ai must < aj.
      if num < ak:
        return True
      while stack and stack[-1] < num:
        ak = stack[-1]
        stack.pop()
      stack.append(num)  # `nums[i]` is a candidate of aj.

    return False

# 484. Find Permutation (Locked)

class Solution:
  def findPermutation(self, s: str) -> list[int]:
    ans = []
    stack = []

    for i, c in enumerate(s):
      stack.append(i + 1)
      if c == 'I':
        while stack:  # Consume all decreasings
          ans.append(stack.pop())
    stack.append(len(s) + 1)

    while stack:
      ans.append(stack.pop())

    return ans

# 488. Zuma Game
# Hard

# Topics
# Companies
# You are playing a variation of the game Zuma.

# In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or white 'W'. You also have several colored balls in your hand.

# Your goal is to clear all of the balls from the board. On each turn:

# Pick any ball from your hand and insert it in between two balls in the row or on either end of the row.
# If there is a group of three or more consecutive balls of the same color, remove the group of balls from the board.
# If this removal causes more groups of three or more of the same color to form, then continue removing each group until there are none left.
# If there are no more balls on the board, then you win the game.
# Repeat this process until you either win or do not have any more balls in your hand.
# Given a string board, representing the row of balls on the board, and a string hand, representing the balls in your hand, return the minimum number of balls you have to insert to clear all the balls from the board. If you cannot clear all the balls from the board using the balls in your hand, return -1.

 

# Example 1:

# Input: board = "WRRBBW", hand = "RB"
# Output: -1
# Explanation: It is impossible to clear all the balls. The best you can do is:
# - Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
# - Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
# There are still balls remaining on the board, and you are out of balls to insert.
# Example 2:

# Input: board = "WWRRBBWW", hand = "WRBRW"
# Output: 2
# Explanation: To make the board empty:
# - Insert 'R' so the board becomes WWRRRBBWW. WWRRRBBWW -> WWBBWW.
# - Insert 'B' so the board becomes WWBBBWW. WWBBBWW -> WWWW -> empty.
# 2 balls from your hand were needed to clear the board.
# Example 3:

# Input: board = "G", hand = "GGGGG"
# Output: 2
# Explanation: To make the board empty:
# - Insert 'G' so the board becomes GG.
# - Insert 'G' so the board becomes GGG. GGG -> empty.
# 2 balls from your hand were needed to clear the board.

class Solution:
  def findMinStep(self, board: str, hand: str) -> int:
    def deDup(board):
      start = 0  # the start index of a color sequenece
      for i, c in enumerate(board):
        if c != board[start]:
          if i - start >= 3:
            return deDup(board[:start] + board[i:])
          start = i  # Meet a new sequence.
      return board

    @functools.lru_cache(None)
    def dfs(board: str, hand: str):
      board = deDup(board)
      if board == '#':
        return 0

      boardSet = set(board)
      # hand that is in board
      hand = ''.join(h for h in hand if h in boardSet)
      if not hand:  # infeasible
        return math.inf

      ans = math.inf

      for i in range(len(board)):
        for j, h in enumerate(hand):
          # Place hs[j] in board[i].
          newHand = hand[:j] + hand[j + 1:]
          newBoard = board[:i] + h + board[i:]
          ans = min(ans, 1 + dfs(newBoard, newHand))

      return ans

    ans = dfs(board + '#', hand)
    return -1 if ans == math.inf else ans

# 496. Next Greater Element I
# Solved
# Easy

# Topics
# Companies
# The next greater element of some element x in an array is the first greater element that is to the right of x in the same array.

# You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of nums2.

# For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and determine the next greater element of nums2[j] in nums2. If there is no next greater element, then the answer for this query is -1.

# Return an array ans of length nums1.length such that ans[i] is the next greater element as described above.

 

# Example 1:

# Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
# Output: [-1,3,-1]
# Explanation: The next greater element for each value of nums1 is as follows:
# - 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
# - 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
# - 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
# Example 2:

# Input: nums1 = [2,4], nums2 = [1,2,3,4]
# Output: [3,-1]
# Explanation: The next greater element for each value of nums1 is as follows:
# - 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
# - 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so the answer is -1.

class Solution:
  def nextGreaterElement(self, nums1: list[int], nums2: list[int]) -> list[int]:
    numToNextGreater = {}
    stack = []  # a decreasing stack

    for num in nums2:
      while stack and stack[-1] < num:
        numToNextGreater[stack.pop()] = num
      stack.append(num)

    return [numToNextGreater.get(num, -1) for num in nums1]

# 503. Next Greater Element II
# Medium

# Topics
# Companies
# Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]), return the next greater number for every element in nums.

# The next greater number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return -1 for this number.

 

# Example 1:

# Input: nums = [1,2,1]
# Output: [2,-1,2]
# Explanation: The first 1's next greater number is 2; 
# The number 2 can't find next greater number. 
# The second 1's next greater number needs to search circularly, which is also 2.
# Example 2:

# Input: nums = [1,2,3,4,3]
# Output: [2,3,4,-1,4]

class Solution:
  def nextGreaterElements(self, nums: list[int]) -> list[int]:
    n = len(nums)
    ans = [-1] * n
    stack = []  # a decreasing stack storing indices

    for i in range(n * 2):
      num = nums[i % n]
      while stack and nums[stack[-1]] < num:
        ans[stack.pop()] = num
      if i < n:
        stack.append(i)

    return ans
  
# 581. Shortest Unsorted Continuous Subarray
# Medium

# Topics
# Companies
# Given an integer array nums, you need to find one continuous subarray such that if you only sort this subarray in non-decreasing order, then the whole array will be sorted in non-decreasing order.

# Return the shortest such subarray and output its length.

 

# Example 1:

# Input: nums = [2,6,4,8,10,9,15]
# Output: 5
# Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
# Example 2:

# Input: nums = [1,2,3,4]
# Output: 0
# Example 3:

# Input: nums = [1]
# Output: 0

class Solution:
  def findUnsortedSubarray(self, nums: list[int]) -> int:
    mn = math.inf
    mx = -math.inf
    flag = False

    for i in range(1, len(nums)):
      if nums[i] < nums[i - 1]:
        flag = True
      if flag:
        mn = min(mn, nums[i])

    flag = False

    for i in reversed(range(len(nums) - 1)):
      if nums[i] > nums[i + 1]:
        flag = True
      if flag:
        mx = max(mx, nums[i])

    for l in range(len(nums)):
      if nums[l] > mn:
        break

    for r, num in reversed(list(enumerate(nums))):
      if num < mx:
        break

    return 0 if l >= r else r - l + 1
  
# 589. N-ary Tree Preorder Traversal
# Easy

# Topics
# Companies
# Given the root of an n-ary tree, return the preorder traversal of its nodes' values.

# Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)

 

# Example 1:



# Input: root = [1,null,3,2,4,null,5,6]
# Output: [1,3,5,6,2,4]
# Example 2:



# Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
# Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]

"""
# Definition for a Node.
"""
class Node:
    def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        self.val = val
        self.children = children
        
class Solution:
    def preorder(self, root: 'Node') -> List[int]:
        if not root:
            return []
        
        stack = [root]
        result = []
        
        while stack:
            node = stack.pop()
            result.append(node.val)  # Visit the root
            # Push children in reverse order to maintain left-to-right traversal
            if node.children:
                stack.extend(node.children[::-1])
        
        return result
      
# 636. Exclusive Time of Functions
# Medium

# Topics
# Companies
# On a single-threaded CPU, we execute a program containing n functions. Each function has a unique ID between 0 and n-1.

# Function calls are stored in a call stack: when a function call starts, its ID is pushed onto the stack, and when a function call ends, its ID is popped off the stack. The function whose ID is at the top of the stack is the current function being executed. Each time a function starts or ends, we write a log with the ID, whether it started or ended, and the timestamp.

# You are given a list logs, where logs[i] represents the ith log message formatted as a string "{function_id}:{"start" | "end"}:{timestamp}". For example, "0:start:3" means a function call with function ID 0 started at the beginning of timestamp 3, and "1:end:2" means a function call with function ID 1 ended at the end of timestamp 2. Note that a function can be called multiple times, possibly recursively.

# A function's exclusive time is the sum of execution times for all function calls in the program. For example, if a function is called twice, one call executing for 2 time units and another call executing for 1 time unit, the exclusive time is 2 + 1 = 3.

# Return the exclusive time of each function in an array, where the value at the ith index represents the exclusive time for the function with ID i.

 

# Example 1:


# Input: n = 2, logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
# Output: [3,4]
# Explanation:
# Function 0 starts at the beginning of time 0, then it executes 2 for units of time and reaches the end of time 1.
# Function 1 starts at the beginning of time 2, executes for 4 units of time, and ends at the end of time 5.
# Function 0 resumes execution at the beginning of time 6 and executes for 1 unit of time.
# So function 0 spends 2 + 1 = 3 units of total time executing, and function 1 spends 4 units of total time executing.
# Example 2:

# Input: n = 1, logs = ["0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"]
# Output: [8]
# Explanation:
# Function 0 starts at the beginning of time 0, executes for 2 units of time, and recursively calls itself.
# Function 0 (recursive call) starts at the beginning of time 2 and executes for 4 units of time.
# Function 0 (initial call) resumes execution then immediately calls itself again.
# Function 0 (2nd recursive call) starts at the beginning of time 6 and executes for 1 unit of time.
# Function 0 (initial call) resumes execution at the beginning of time 7 and executes for 1 unit of time.
# So function 0 spends 2 + 4 + 1 + 1 = 8 units of total time executing.
# Example 3:

# Input: n = 2, logs = ["0:start:0","0:start:2","0:end:5","1:start:6","1:end:6","0:end:7"]
# Output: [7,1]
# Explanation:
# Function 0 starts at the beginning of time 0, executes for 2 units of time, and recursively calls itself.
# Function 0 (recursive call) starts at the beginning of time 2 and executes for 4 units of time.
# Function 0 (initial call) resumes execution then immediately calls function 1.
# Function 1 starts at the beginning of time 6, executes 1 unit of time, and ends at the end of time 6.
# Function 0 resumes execution at the beginning of time 6 and executes for 2 units of time.
# So function 0 spends 2 + 4 + 1 = 7 units of total time executing, and function 1 spends 1 unit of total time executing.

class Solution:
    def exclusiveTime(self, n: int, logs: List[str]) -> List[int]:
        result = [0] * n
        stack = []  # To track currently active functions
        prev_time = 0  # The last processed timestamp

        for log in logs:
            func_id, action, timestamp = log.split(":")
            func_id = int(func_id)
            timestamp = int(timestamp)

            if action == "start":
                if stack:
                    # Update the exclusive time of the current function
                    result[stack[-1]] += timestamp - prev_time
                stack.append(func_id)
                prev_time = timestamp  # Update the previous timestamp
            else:  # action == "end"
                # Add the duration of the function to the result
                result[stack.pop()] += timestamp - prev_time + 1
                prev_time = timestamp + 1  # Move to the next timestamp

        return result
      
# 654. Maximum Binary Tree
# Medium

# Topics
# Companies
# You are given an integer array nums with no duplicates. A maximum binary tree can be built recursively from nums using the following algorithm:

# Create a root node whose value is the maximum value in nums.
# Recursively build the left subtree on the subarray prefix to the left of the maximum value.
# Recursively build the right subtree on the subarray suffix to the right of the maximum value.
# Return the maximum binary tree built from nums.

 

# Example 1:


# Input: nums = [3,2,1,6,0,5]
# Output: [6,3,5,null,2,0,null,null,1]
# Explanation: The recursive calls are as follow:
# - The largest value in [3,2,1,6,0,5] is 6. Left prefix is [3,2,1] and right suffix is [0,5].
#     - The largest value in [3,2,1] is 3. Left prefix is [] and right suffix is [2,1].
#         - Empty array, so no child.
#         - The largest value in [2,1] is 2. Left prefix is [] and right suffix is [1].
#             - Empty array, so no child.
#             - Only one element, so child is a node with value 1.
#     - The largest value in [0,5] is 5. Left prefix is [0] and right suffix is [].
#         - Only one element, so child is a node with value 0.
#         - Empty array, so no child.
# Example 2:


# Input: nums = [3,2,1]
# Output: [3,null,2,null,1]

class Solution:
  def constructMaximumBinaryTree(self, nums: list[int]) -> TreeNode | None:
    def build(i: int, j: int) -> TreeNode | None:
      if i > j:
        return None

      maxNum = max(nums[i:j + 1])
      maxIndex = nums.index(maxNum)

      root = TreeNode(maxNum)
      root.left = build(i, maxIndex - 1)
      root.right = build(maxIndex + 1, j)
      return root

    return build(0, len(nums) - 1)
  
