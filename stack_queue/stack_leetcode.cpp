#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// 20. Valid Parentheses
// Easy

// Topics
// Companies

// Hint
// Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

// An input string is valid if:

// Open brackets must be closed by the same type of brackets.
// Open brackets must be closed in the correct order.
// Every close bracket has a corresponding open bracket of the same type.

class Solution {
 public:
  bool isValid(string s) {
    stack<char> stack;

    for (const char c : s)
      if (c == '(')
        stack.push(')');
      else if (c == '{')
        stack.push('}');
      else if (c == '[')
        stack.push(']');
      else if (stack.empty() || pop(stack) != c)
        return false;

    return stack.empty();
  }

 private:
  int pop(stack<char>& stack) {
    const int c = stack.top();
    stack.pop();
    return c;
  }
};

// 32. Longest Valid Parentheses
// Hard

// Topics
// Companies
// Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses 
// substring.

class Solution {
 public:
  int longestValidParentheses(string s) {
    const string s2 = ")" + s;
    // dp[i] := the length of the longest valid parentheses in the substring
    // s2[1..i]
    vector<int> dp(s2.length());

    for (int i = 1; i < s2.length(); ++i)
      if (s2[i] == ')' && s2[i - dp[i - 1] - 1] == '(')
        dp[i] = dp[i - 1] + dp[i - dp[i - 1] - 2] + 2;

    return *max_element(dp.begin(), dp.end());
  }
};

// 42. Trapping Rain Water
// Solved
// Hard

// Topics
// Companies
// Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

class Solution {
 public:
  int trap(vector<int>& height) {
    if (height.empty())
      return 0;

    int ans = 0;
    int l = 0;
    int r = height.size() - 1;
    int maxL = height[l];
    int maxR = height[r];

    while (l < r)
      if (maxL < maxR) {
        ans += maxL - height[l];
        maxL = max(maxL, height[++l]);
      } else {
        ans += maxR - height[r];
        maxR = max(maxR, height[--r]);
      }

    return ans;
  }
};

// 71. Simplify Path
// Medium

// Topics
// Companies
// You are given an absolute path for a Unix-style file system, which always begins with a slash '/'. Your task is to transform this absolute path into its simplified canonical path.

// The rules of a Unix-style file system are as follows:

// A single period '.' represents the current directory.
// A double period '..' represents the previous/parent directory.
// Multiple consecutive slashes such as '//' and '///' are treated as a single slash '/'.
// Any sequence of periods that does not match the rules above should be treated as a valid directory or file name. For example, '...' and '....' are valid directory or file names.
// The simplified canonical path should follow these rules:

// The path must start with a single slash '/'.
// Directories within the path must be separated by exactly one slash '/'.
// The path must not end with a slash '/', unless it is the root directory.
// The path must not have any single or double periods ('.' and '..') used to denote current or parent directories.
// Return the simplified canonical path.

class Solution {
 public:
  string simplifyPath(string path) {
    string ans;
    istringstream iss(path);
    vector<string> stack;

    for (string dir; getline(iss, dir, '/');) {
      if (dir.empty() || dir == ".")
        continue;
      if (dir == "..") {
        if (!stack.empty())
          stack.pop_back();
      } else {
        stack.push_back(dir);
      }
    }

    for (const string& s : stack)
      ans += "/" + s;

    return ans.empty() ? "/" : ans;
  }
};

// 84. Largest Rectangle in Histogram
// Hard

// Topics
// Companies
// Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

class Solution {
 public:
  int largestRectangleArea(vector<int>& heights) {
    int ans = 0;
    stack<int> stack;

    for (int i = 0; i <= heights.size(); ++i) {
      while (!stack.empty() &&
             (i == heights.size() || heights[stack.top()] > heights[i])) {
        const int h = heights[stack.top()];
        stack.pop();
        const int w = stack.empty() ? i : i - stack.top() - 1;
        ans = max(ans, h*w);
      }
      stack.push(i);
    }

    return ans;
  }
};

// 85. Maximal Rectangle
// Solved
// Hard

// Topics
// Companies
// Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

class Solution {
 public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty())
      return 0;

    int ans = 0;
    vector<int> hist(matrix[0].size());

    for (const vector<char>& row : matrix) {
      for (int i = 0; i < row.size(); ++i)
        hist[i] = row[i] == '0' ? 0 : hist[i] + 1;
      ans = max(ans, largestRectangleArea(hist));
    }

    return ans;
  }

 private:
  int largestRectangleArea(const vector<int>& heights) {
    int ans = 0;
    stack<int> stack;

    for (int i = 0; i <= heights.size(); ++i) {
      while (!stack.empty() &&
             (i == heights.size() || heights[stack.top()] > heights[i])) {
        const int h = heights[stack.top()];
        stack.pop();
        const int w = stack.empty() ? i : i - stack.top() - 1;
        ans = max(ans, h*w);
      }
      stack.push(i);
    }

    return ans;
  }
};

// 94. Binary Tree Inorder Traversal
// Easy

// Topics
// Companies
// Given the root of a binary tree, return the inorder traversal of its nodes' values.

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    stack<TreeNode*> stack;

    while (root != nullptr || !stack.empty()) {
      while (root != nullptr) {
        stack.push(root);
        root = root->left;
      }
      root = stack.top(), stack.pop();
      ans.push_back(root->val);
      root = root->right;
    }

    return ans;
  }
};

// 114. Flatten Binary Tree to Linked List
// Solved
// Medium

// Topics
// Companies

// Hint
// Given the root of a binary tree, flatten the tree into a "linked list":

// The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
// The "linked list" should be in the same order as a pre-order traversal of the binary tree.

class Solution {
 public:
  void flatten(TreeNode* root) {
    if (root == nullptr)
      return;

    while (root != nullptr) {
      if (root->left != nullptr) {
        // Find the rightmost root.
        TreeNode* rightmost = root->left;
        while (rightmost->right != nullptr)
          rightmost = rightmost->right;
        // Rewire the connections.
        rightmost->right = root->right;
        root->right = root->left;
        root->left = nullptr;
      }
      // Move on to the right side of the tree.
      root = root->right;
    }
  }
};

// 143. Reorder List
// Medium

// Topics
// Companies
// You are given the head of a singly linked-list. The list can be represented as:

// L0 → L1 → … → Ln - 1 → Ln
// Reorder the list to be on the following form:

// L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
// You may not modify the values in the list's nodes. Only nodes themselves may be changed.

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
 public:
  void reorderList(ListNode* head) {
    if (!head || !head->next)
      return;

    ListNode* mid = findMid(head);
    ListNode* reversed = reverse(mid);
    merge(head, reversed);
  }

 private:
  ListNode* findMid(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
      prev = slow;
      slow = slow->next;
      fast = fast->next->next;
    }
    prev->next = nullptr;

    return slow;
  }

  ListNode* reverse(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr != nullptr) {
      ListNode* next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }

    return prev;
  }

  void merge(ListNode* l1, ListNode* l2) {
    while (l2) {
      ListNode* next = l1->next;
      l1->next = l2;
      l1 = l2;
      l2 = next;
    }
  }
};

// 144. Binary Tree Preorder Traversal
// Easy

// Topics
// Companies
// Given the root of a binary tree, return the preorder traversal of its nodes' values.

class Solution {
 public:
  vector<int> preorderTraversal(TreeNode* root) {
    if (root == nullptr)
      return {};

    vector<int> ans;
    stack<TreeNode*> stack{{root}};

    while (!stack.empty()) {
      root = stack.top(), stack.pop();
      ans.push_back(root->val);
      if (root->right)
        stack.push(root->right);
      if (root->left)
        stack.push(root->left);
    }

    return ans;
  }
};

// 145. Binary Tree Postorder Traversal
// Easy

// Topics
// Companies
// Given the root of a binary tree, return the postorder traversal of its nodes' values.

class Solution {
 public:
  vector<int> postorderTraversal(TreeNode* root) {
    if (root == nullptr)
      return {};

    vector<int> ans;
    stack<TreeNode*> stack{{root}};

    while (!stack.empty()) {
      root = stack.top(), stack.pop();
      ans.push_back(root->val);
      if (root->left)
        stack.push(root->left);
      if (root->right)
        stack.push(root->right);
    }

    reverse(ans.begin(), ans.end());
    return ans;
  }
};

// 150. Evaluate Reverse Polish Notation
// Medium

// Topics
// Companies
// You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.

// Evaluate the expression. Return an integer that represents the value of the expression.

// Note that:

// The valid operators are '+', '-', '*', and '/'.
// Each operand may be an integer or another expression.
// The division between two integers always truncates toward zero.
// There will not be any division by zero.
// The input represents a valid arithmetic expression in a reverse polish notation.
// The answer and all the intermediate calculations can be represented in a 32-bit integer.

class Solution {
 public:
  int evalRPN(vector<string>& tokens) {
    stack<long> stack;
    const unordered_map<string, function<long(long, long)>> op{
        {"+", std::plus<long>()},
        {"-", std::minus<long>()},
        {"*", std::multiplies<long>()},
        {"/", std::divides<long>()}};

    for (const string& token : tokens) {
      if (op.find(token) != op.end()) { // Check if `token` exists in the map
        const long b = stack.top();
        stack.pop();
        const long a = stack.top();
        stack.pop();
        stack.push(op.at(token)(a, b));
      } else {
        stack.push(stoi(token)); // Convert string to integer and push onto stack
      }
    }

    return stack.top();
  }
};

// 155. Min Stack
// Solved
// Medium

// Topics
// Companies

// Hint
// Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

// Implement the MinStack class:

// MinStack() initializes the stack object.
// void push(int val) pushes the element val onto the stack.
// void pop() removes the element on the top of the stack.
// int top() gets the top element of the stack.
// int getMin() retrieves the minimum element in the stack.
// You must implement a solution with O(1) time complexity for each function.

class MinStack {
 public:
  void push(int x) {
    if (stack.empty())
      stack.emplace(x, x);
    else
      stack.emplace(x, min(x, stack.top().second));
  }

  void pop() {
    stack.pop();
  }

  int top() {
    return stack.top().first;
  }

  int getMin() {
    return stack.top().second;
  }

 private:
  stack<pair<int, int>> stack;  // {x, min}
};

// 173. Binary Search Tree Iterator
// Solved
// Medium

// Topics
// Companies
// Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):

// BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
// boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
// int next() Moves the pointer to the right, then returns the number at the pointer.
// Notice that by initializing the pointer to a non-existent smallest number, the first call to next() will return the smallest element in the BST.

// You may assume that next() calls will always be valid. That is, there will be at least a next number in the in-order traversal when next() is called.

class BSTIterator {
 public:
  BSTIterator(TreeNode* root) {
    pushLeftsUntilNull(root);
  }

  int next() {
    TreeNode* root = stack.top();
    stack.pop();
    pushLeftsUntilNull(root->right);
    return root->val;
  }

  bool hasNext() {
    return !stack.empty();
  }

 private:
  stack<TreeNode*> stack;

  void pushLeftsUntilNull(TreeNode* root) {
    while (root != nullptr) {
      stack.push(root);
      root = root->left;
    }
  }
};

// 224. Basic Calculator
// Hard

// Topics
// Companies
// Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.

// Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

// Example 1:

// Input: s = "1 + 1"
// Output: 2
// Example 2:

// Input: s = " 2-1 + 2 "
// Output: 3
// Example 3:

// Input: s = "(1+(4+5+2)-3)+(6+8)"
// Output: 23

class Solution {
 public:
  int calculate(string s) {
    int ans = 0;
    int num = 0;
    int sign = 1;
    stack<int> stack{{sign}};  // stack.top() := the current environment's sign

    for (const char c : s)
      if (isdigit(c))
        num = num * 10 + (c - '0');
      else if (c == '(')
        stack.push(sign);
      else if (c == ')')
        stack.pop();
      else if (c == '+' || c == '-') {
        ans += sign * num;
        sign = (c == '+' ? 1 : -1) * stack.top();
        num = 0;
      }

    return ans + sign * num;
  }
};

// 225. Implement Stack using Queues
// Easy

// Topics
// Companies
// Implement a last-in-first-out (LIFO) stack using only two queues. The implemented stack should support all the functions of a normal stack (push, top, pop, and empty).

// Implement the MyStack class:

// void push(int x) Pushes element x to the top of the stack.
// int pop() Removes the element on the top of the stack and returns it.
// int top() Returns the element on the top of the stack.
// boolean empty() Returns true if the stack is empty, false otherwise.
// Notes:

// You must use only standard operations of a queue, which means that only push to back, peek/pop from front, size and is empty operations are valid.
// Depending on your language, the queue may not be supported natively. You may simulate a queue using a list or deque (double-ended queue) as long as you use only a queue's standard operations.

class MyStack {
 public:
  void push(int x) {
    q.push(x);
    for (int i = 0; i < q.size() - 1; ++i) {
      q.push(q.front());
      q.pop();
    }
  }

  int pop() {
    const int val = q.front();
    q.pop();
    return val;
  }

  int top() {
    return q.front();
  }

  bool empty() {
    return q.empty();
  }

 private:
  queue<int> q;
};

// 227. Basic Calculator II
// Medium

// Topics
// Companies
// Given a string s which represents an expression, evaluate this expression and return its value. 

// The integer division should truncate toward zero.

// You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

// Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

class Solution {
 public:
  int calculate(string s) {
    int ans = 0;
    int prevNum = 0;
    int currNum = 0;
    char op = '+';

    for (int i = 0; i < s.length(); ++i) {
      const char c = s[i];
      if (isdigit(c))
        currNum = currNum * 10 + (c - '0');
      if (!isdigit(c) && !isspace(c) || i == s.length() - 1) {
        if (op == '+' || op == '-') {
          ans += prevNum;
          prevNum = op == '+' ? currNum : -currNum;
        } else if (op == '*') {
          prevNum *= currNum;
        } else if (op == '/') {
          prevNum /= currNum;
        }
        op = c;
        currNum = 0;
      }
    }

    return ans + prevNum;
  }
};

// 232. Implement Queue using Stacks
// Easy

// Topics
// Companies
// Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

// Implement the MyQueue class:

// void push(int x) Pushes element x to the back of the queue.
// int pop() Removes the element from the front of the queue and returns it.
// int peek() Returns the element at the front of the queue.
// boolean empty() Returns true if the queue is empty, false otherwise.
// Notes:

// You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
// Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.

class MyQueue {
 public:
  void push(int x) {
    input.push(x);
  }

  int pop() {
    peek();
    const int val = output.top();
    output.pop();
    return val;
  }

  int peek() {
    if (output.empty())
      while (!input.empty())
        output.push(input.top()), input.pop();
    return output.top();
  }

  bool empty() {
    return input.empty() && output.empty();
  }

 private:
  stack<int> input;
  stack<int> output;
};

// 234. Palindrome Linked List
// Easy

// Topics
// Companies
// Given the head of a singly linked list, return true if it is a 
// palindrome
//  or false otherwise.

class Solution {
 public:
  bool isPalindrome(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
    }

    if (fast != nullptr)
      slow = slow->next;
    slow = reverseList(slow);

    while (slow != nullptr) {
      if (slow->val != head->val)
        return false;
      slow = slow->next;
      head = head->next;
    }

    return true;
  }

 private:
  ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head != nullptr) {
      ListNode* next = head->next;
      head->next = prev;
      prev = head;
      head = next;
    }
    return prev;
  }
};

// 255. Verify Preorder sequence in Binary Search (Locked)
class Solution {
 public:
  bool verifyPreorder(vector<int>& preorder) {
    int low = INT_MIN;
    stack<int> stack;

    for (const int p : preorder) {
      if (p < low)
        return false;
      while (!stack.empty() && stack.top() < p)
        low = stack.top(), stack.pop();
      stack.push(p);
    }

    return true;
  }
};

// 272. Closest Binary Search Tree II (Locked)
class Solution {
 public:
  vector<int> closestKValues(TreeNode* root, double target, int k) {
    deque<int> dq;

    inorder(root, dq);

    while (dq.size() > k)
      if (abs(dq.front() - target) > abs(dq.back() - target))
        dq.pop_front();
      else
        dq.pop_back();

    return {dq.begin(), dq.end()};
  }

 private:
  void inorder(TreeNode* root, deque<int>& dq) {
    if (root == nullptr)
      return;

    inorder(root->left, dq);
    dq.push_back(root->val);
    inorder(root->right, dq);
  }
};

// 316. Remove Duplicate Letters
// Medium

// Topics
// Companies

// Hint
// Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is 
// the smallest in lexicographical order
// among all possible results.

class Solution {
 public:
  string removeDuplicateLetters(string s) {
    string ans;
    vector<int> count(128);
    vector<bool> used(128);

    for (const char c : s)
      ++count[c];

    for (const char c : s) {
      --count[c];
      if (used[c])
        continue;
      while (!ans.empty() && ans.back() > c && count[ans.back()] > 0) {
        used[ans.back()] = false;
        ans.pop_back();
      }
      used[c] = true;
      ans.push_back(c);
    }

    return ans;
  }
};

// 321. Create Maximum Number
// Hard

// Topics
// Companies
// You are given two integer arrays nums1 and nums2 of lengths m and n respectively. nums1 and nums2 represent the digits of two numbers. You are also given an integer k.

// Create the maximum number of length k <= m + n from digits of the two numbers. The relative order of the digits from the same array must be preserved.

// Return an array of the k digits representing the answer.

class Solution {
 public:
  vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    vector<int> ans;

    for (int k1 = 0; k1 <= k; ++k1) {
      const int k2 = k - k1;
      if (k1 > nums1.size() || k2 > nums2.size())
        continue;
      ans = max(ans, merge(maxArray(nums1, k1), maxArray(nums2, k2)));
    }

    return ans;
  }

 private:
  vector<int> maxArray(const vector<int>& nums, int k) {
    vector<int> res;
    int toPop = nums.size() - k;
    for (const int num : nums) {
      while (!res.empty() && res.back() < num && toPop-- > 0)
        res.pop_back();
      res.push_back(num);
    }
    return {res.begin(), res.begin() + k};
  }

  // Merges nums1 and nums2.
  vector<int> merge(const vector<int>& nums1, const vector<int>& nums2) {
    vector<int> res;
    auto s1 = nums1.cbegin();
    auto s2 = nums2.cbegin();
    while (s1 != nums1.cend() || s2 != nums2.cend())
      if (lexicographical_compare(s1, nums1.cend(), s2, nums2.cend()))
        res.push_back(*s2++);
      else
        res.push_back(*s1++);
    return res;
  }
};

// 331. Verify Preorder Serialization of a Binary Tree
// Medium

// Topics
// Companies
// One way to serialize a binary tree is to use preorder traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as '#'.


// For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where '#' represents a null node.

// Given a string of comma-separated values preorder, return true if it is a correct preorder traversal serialization of a binary tree.

// It is guaranteed that each comma-separated value in the string must be either an integer or a character '#' representing null pointer.

// You may assume that the input format is always valid.

// For example, it could never contain two consecutive commas, such as "1,,3".
// Note: You are not allowed to reconstruct the tree.

class Solution {
 public:
  bool isValidSerialization(string preorder) {
    int degree = 1;  // out-degree (children) - in-degree (parent)
    istringstream iss(preorder);

    for (string node; getline(iss, node, ',');) {
      if (--degree < 0)
        return false;
      if (node != "#")
        degree += 2;
    }

    return degree == 0;
  }
};

// 341. Flatten Nested List Iterator
// Medium

// Topics
// Companies
// You are given a nested list of integers nestedList. Each element is either an integer or a list whose elements may also be integers or other lists. Implement an iterator to flatten it.

// Implement the NestedIterator class:

// NestedIterator(List<NestedInteger> nestedList) Initializes the iterator with the nested list nestedList.
// int next() Returns the next integer in the nested list.
// boolean hasNext() Returns true if there are still some integers in the nested list and false otherwise.
// Your code will be tested with the following pseudocode:

// initialize iterator with nestedList
// res = []
// while iterator.hasNext()
//     append iterator.next() to the end of res
// return res
// If res matches the expected flattened list, then your code will be judged as correct.

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

// class NestedIterator {
//  public:
//   NestedIterator(vector<NestedInteger>& nestedList) {
//     addInteger(nestedList);
//   }

//   int next() {
//     const int num = stack.top().getInteger();
//     stack.pop();
//     return num;
//   }

//   bool hasNext() {
//     while (!stack.empty() && !stack.top().isInteger()) {
//       vector<NestedInteger> nestedList = stack.top().getList();
//       stack.pop();
//       addInteger(nestedList);
//     }
//     return !stack.empty();
//   }

//  private:
//   stack<NestedInteger> stack;

//   // addInteger([1, [4, [6]]]) -> stack = [[4, [6]], 1]
//   // addInteger([4, [6]]) -> stack = [[6], 4]
//   // addInteger([6]) -> stack = [6]
//   void addInteger(const vector<NestedInteger>& nestedList) {
//     for (int i = nestedList.size() - 1; i >= 0; --i)
//       stack.push(nestedList[i]);
//   }
// };

// 364. Nested List Weight Sum II (Locked)

// class Solution {
//  public:
//   int depthSumInverse(vector<NestedInteger>& nestedList) {
//     int ans = 0;
//     int prevSum = 0;
//     queue<NestedInteger> q{{nestedList.begin(), nestedList.end()}};

//     while (!q.empty()) {
//       for (int sz = q.size(); sz > 0; --sz) {
//         const NestedInteger ni = q.front();
//         q.pop();
//         if (ni.isInteger())
//           prevSum += ni.getInteger();
//         else {
//           for (const NestedInteger nextNi : ni.getList())
//             q.push(nextNi);
//         }
//       }
//       ans += prevSum;
//     }

//     return ans;
//   }
// };

// 385. Mini Parser
// Medium

// Topics
// Companies
// Given a string s represents the serialization of a nested list, implement a parser to deserialize it and return the deserialized NestedInteger.

// Each element is either an integer or a list whose elements may also be integers or other lists.

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

// class Solution {
//  public:
//   NestedInteger deserialize(string s) {
//     if (s[0] != '[')
//       return NestedInteger(stoi(s));

//     stack<NestedInteger> stack;
//     int start;  // the start index of a number

//     for (int i = 0; i < s.length(); ++i) {
//       switch (s[i]) {
//         case '[':
//           stack.push(NestedInteger());
//           start = i + 1;
//           break;
//         case ',':
//           if (i > start) {
//             const int num = stoi(s.substr(start, i));
//             stack.top().add(NestedInteger(num));
//           }
//           start = i + 1;
//           break;
//         case ']':
//           NestedInteger popped = stack.top();
//           stack.pop();
//           if (i > start) {
//             const int num = stoi(s.substr(start, i));
//             popped.add(NestedInteger(num));
//           }
//           if (stack.empty())
//             return popped;
//           else
//             stack.top().add(popped);
//           start = i + 1;
//           break;
//       }
//     }

//     throw;
//   }
// };

// 388. Longest Absolute File Path
// Medium

// Topics
// Companies
// Suppose we have a file system that stores both files and directories. An example of one system is represented in the following picture:



// Here, we have dir as the only directory in the root. dir contains two subdirectories, subdir1 and subdir2. subdir1 contains a file file1.ext and subdirectory subsubdir1. subdir2 contains a subdirectory subsubdir2, which contains a file file2.ext.

// In text form, it looks like this (with ⟶ representing the tab character):

// dir
// ⟶ subdir1
// ⟶ ⟶ file1.ext
// ⟶ ⟶ subsubdir1
// ⟶ subdir2
// ⟶ ⟶ subsubdir2
// ⟶ ⟶ ⟶ file2.ext
// If we were to write this representation in code, it will look like this: "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext". Note that the '\n' and '\t' are the new-line and tab characters.

// Every file and directory has a unique absolute path in the file system, which is the order of directories that must be opened to reach the file/directory itself, all concatenated by '/'s. Using the above example, the absolute path to file2.ext is "dir/subdir2/subsubdir2/file2.ext". Each directory name consists of letters, digits, and/or spaces. Each file name is of the form name.extension, where name and extension consist of letters, digits, and/or spaces.

// Given a string input representing the file system in the explained format, return the length of the longest absolute path to a file in the abstracted file system. If there is no file in the system, return 0.

// Note that the testcases are generated such that the file system is valid and no file or directory name has length 0.

 

// Example 1:


// Input: input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
// Output: 20
// Explanation: We have only one file, and the absolute path is "dir/subdir2/file.ext" of length 20.
// Example 2:


// Input: input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
// Output: 32
// Explanation: We have two files:
// "dir/subdir1/file1.ext" of length 21
// "dir/subdir2/subsubdir2/file2.ext" of length 32.
// We return 32 since it is the longest absolute path to a file.
// Example 3:

// Input: input = "a"
// Output: 0
// Explanation: We do not have any files, just a single directory named "a".


struct T {
  int depth;
  size_t length;
};

class Solution {
 public:
  int lengthLongestPath(string input) {
    size_t ans = 0;
    std::stack<T> stack{{{-1, 0}}};  // placeholder
    std::istringstream iss(input);

    for (std::string token; getline(iss, token, '\n');) {
      // Count the number of '\t' characters for depth
      const int depth = count(token.begin(), token.end(), '\t');
      // Remove all '\t' characters from the token
      token.erase(remove(token.begin(), token.end(), '\t'), token.end());

      // Navigate the stack to match the current depth
      while (depth <= stack.top().depth)
        stack.pop();

      if (isFile(token))
        ans = max(ans, stack.top().length + token.length());
      else  // Directory + '/'
        stack.push({depth, stack.top().length + token.length() + 1});
    }

    return ans;
  }

 private:
  bool isFile(const string& token) {
    return token.find('.') != string::npos;
  }
};

// 394. Decode String
// Medium

// Topics
// Companies
// Given an encoded string, return its decoded string.

// The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

// You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].

// The test cases are generated so that the length of the output will never exceed 105.

class Solution {
 public:
  string decodeString(string s) {
    stack<pair<string, int>> stack;  // (prevStr, repeatCount)
    string currStr;
    int currNum = 0;

    for (const char c : s)
      if (isdigit(c)) {
        currNum = currNum * 10 + (c - '0');
      } else {
        if (c == '[') {
          stack.emplace(currStr, currNum);
          currStr = "";
          currNum = 0;
        } else if (c == ']') {
          const auto [prevStr, n] = stack.top();
          stack.pop();
          currStr = prevStr + getRepeatedStr(currStr, n);
        } else {
          currStr += c;
        }
      }

    return currStr;
  }

 private:
  // Returns s * n.
  string getRepeatedStr(const string& s, int n) {
    string repeat;
    while (n-- > 0)
      repeat += s;
    return repeat;
  }
};

// 402. Remove K Digits
// Medium

// Topics
// Companies
// Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num.

 

// Example 1:

// Input: num = "1432219", k = 3
// Output: "1219"
// Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
// Example 2:

// Input: num = "10200", k = 1
// Output: "200"
// Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
// Example 3:

// Input: num = "10", k = 2
// Output: "0"
// Explanation: Remove all the digits from the number and it is left with nothing which is 0.

class Solution {
 public:
  string removeKdigits(string num, int k) {
    if (num.length() == k)
      return "0";

    string ans;
    vector<char> stack;

    for (int i = 0; i < num.length(); ++i) {
      while (k > 0 && !stack.empty() && stack.back() > num[i]) {
        stack.pop_back();
        --k;
      }
      stack.push_back(num[i]);
    }

    while (k-- > 0)
      stack.pop_back();

    for (const char c : stack) {
      if (c == '0' && ans.empty())
        continue;
      ans += c;
    }

    return ans.empty() ? "0" : ans;
  }
};

// 445. Add Two Numbers II
// Medium

// Topics
// Companies
// You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

// You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 

// Example 1:


// Input: l1 = [7,2,4,3], l2 = [5,6,4]
// Output: [7,8,0,7]
// Example 2:

// Input: l1 = [2,4,3], l2 = [5,6,4]
// Output: [8,0,7]
// Example 3:

// Input: l1 = [0], l2 = [0]
// Output: [0]

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    stack<ListNode*> stack1;
    stack<ListNode*> stack2;

    while (l1) {
      stack1.push(l1);
      l1 = l1->next;
    }

    while (l2) {
      stack2.push(l2);
      l2 = l2->next;
    }

    ListNode* head = nullptr;
    int carry = 0;

    while (carry || !stack1.empty() || !stack2.empty()) {
      if (!stack1.empty())
        carry += stack1.top()->val, stack1.pop();
      if (!stack2.empty())
        carry += stack2.top()->val, stack2.pop();
      ListNode* node = new ListNode(carry % 10);
      node->next = head;
      head = node;
      carry /= 10;
    }

    return head;
  }
};

// 456. 132 Pattern
// Medium

// Topics
// Companies
// Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].

// Return true if there is a 132 pattern in nums, otherwise, return false.

 

// Example 1:

// Input: nums = [1,2,3,4]
// Output: false
// Explanation: There is no 132 pattern in the sequence.
// Example 2:

// Input: nums = [3,1,4,2]
// Output: true
// Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
// Example 3:

// Input: nums = [-1,3,2,0]
// Output: true
// Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].

class Solution {
 public:
  bool find132pattern(vector<int>& nums) {
    stack<int> stack;  // a decreasing stack
    int ak = INT_MIN;  // Find a seq, where ai < ak < aj.

    for (int i = nums.size() - 1; i >= 0; --i) {
      // If ai < ak, done because ai must < aj.
      if (nums[i] < ak)
        return true;
      while (!stack.empty() && stack.top() < nums[i])
        ak = stack.top(), stack.pop();
      stack.push(nums[i]);  // `nums[i]` is a candidate of aj.
    }

    return false;
  }
};

// 484. Find Permutation (Locked)

class Solution {
 public:
  vector<int> findPermutation(string s) {
    vector<int> ans;
    stack<int> stack;

    for (int i = 0; i < s.length(); ++i) {
      stack.push(i + 1);
      if (s[i] == 'I')
        while (!stack.empty())
          ans.push_back(stack.top()), stack.pop();
    }
    stack.push(s.length() + 1);

    while (!stack.empty())
      ans.push_back(stack.top()), stack.pop();

    return ans;
  }
};

// 488. Zuma Game
// Hard

// Topics
// Companies
// You are playing a variation of the game Zuma.

// In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or white 'W'. You also have several colored balls in your hand.

// Your goal is to clear all of the balls from the board. On each turn:

// Pick any ball from your hand and insert it in between two balls in the row or on either end of the row.
// If there is a group of three or more consecutive balls of the same color, remove the group of balls from the board.
// If this removal causes more groups of three or more of the same color to form, then continue removing each group until there are none left.
// If there are no more balls on the board, then you win the game.
// Repeat this process until you either win or do not have any more balls in your hand.
// Given a string board, representing the row of balls on the board, and a string hand, representing the balls in your hand, return the minimum number of balls you have to insert to clear all the balls from the board. If you cannot clear all the balls from the board using the balls in your hand, return -1.

 

// Example 1:

// Input: board = "WRRBBW", hand = "RB"
// Output: -1
// Explanation: It is impossible to clear all the balls. The best you can do is:
// - Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
// - Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
// There are still balls remaining on the board, and you are out of balls to insert.
// Example 2:

// Input: board = "WWRRBBWW", hand = "WRBRW"
// Output: 2
// Explanation: To make the board empty:
// - Insert 'R' so the board becomes WWRRRBBWW. WWRRRBBWW -> WWBBWW.
// - Insert 'B' so the board becomes WWBBBWW. WWBBBWW -> WWWW -> empty.
// 2 balls from your hand were needed to clear the board.
// Example 3:

// Input: board = "G", hand = "GGGGG"
// Output: 2
// Explanation: To make the board empty:
// - Insert 'G' so the board becomes GG.
// - Insert 'G' so the board becomes GGG. GGG -> empty.
// 2 balls from your hand were needed to clear the board.

class Solution {
 public:
  int findMinStep(string board, string hand) {
    const int ans = dfs(board + "#", hand, {});
    return ans == INT_MAX ? -1 : ans;
  }

 private:
  int dfs(string&& board, const string& hand,
          unordered_map<string, int>&& mem) {
    const string hashKey = board + '#' + hand;
    if (const auto it = mem.find(hashKey); it != mem.cend())
      return it->second;
    board = deDup(board);
    if (board == "#")
      return 0;

    unordered_set<char> boardSet = unordered_set(board.begin(), board.end());

    string hs;  // hand that is in board
    for (const char h : hand)
      if (boardSet.find(h) != boardSet.end())
        hs += h;
    if (hs.empty())  // infeasible
      return INT_MAX;

    int ans = INT_MAX;

    for (int i = 0; i < board.size(); ++i)
      for (int j = 0; j < hs.size(); ++j) {
        // Place hs[j] in board[i].
        const string& newHand = hs.substr(0, j) + hs.substr(j + 1);
        string newBoard = board.substr(0, i) + hs[j] + board.substr(i);
        const int res = dfs(std::move(newBoard), newHand, std::move(mem));
        if (res < INT_MAX)
          ans = min(ans, 1 + res);
      }

    return mem[hashKey] = ans;
  }

  string deDup(string board) {
    int start = 0;  // the start index of a color sequenece
    for (int i = 0; i < board.size(); ++i)
      if (board[i] != board[start]) {
        if (i - start >= 3)
          return deDup(board.substr(0, start) + board.substr(i));
        start = i;  // Meet a new sequence.
      }
    return board;
  }
};

// 496. Next Greater Element I
// Solved
// Easy

// Topics
// Companies
// The next greater element of some element x in an array is the first greater element that is to the right of x in the same array.

// You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of nums2.

// For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and determine the next greater element of nums2[j] in nums2. If there is no next greater element, then the answer for this query is -1.

// Return an array ans of length nums1.length such that ans[i] is the next greater element as described above.

 

// Example 1:

// Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
// Output: [-1,3,-1]
// Explanation: The next greater element for each value of nums1 is as follows:
// - 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
// - 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
// - 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
// Example 2:

// Input: nums1 = [2,4], nums2 = [1,2,3,4]
// Output: [3,-1]
// Explanation: The next greater element for each value of nums1 is as follows:
// - 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
// - 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so the answer is -1.

class Solution {
 public:
  vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    vector<int> ans;
    unordered_map<int, int> numToNextGreater;
    stack<int> stack;  // a decreasing stack

    for (const int num : nums2) {
      while (!stack.empty() && stack.top() < num)
        numToNextGreater[stack.top()] = num, stack.pop();
      stack.push(num);
    }

    for (const int num : nums1)
      if (const auto it = numToNextGreater.find(num);
          it != numToNextGreater.cend())
        ans.push_back(it->second);
      else
        ans.push_back(-1);

    return ans;
  }
};

// 503. Next Greater Element II
// Medium

// Topics
// Companies
// Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]), return the next greater number for every element in nums.

// The next greater number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return -1 for this number.

 

// Example 1:

// Input: nums = [1,2,1]
// Output: [2,-1,2]
// Explanation: The first 1's next greater number is 2; 
// The number 2 can't find next greater number. 
// The second 1's next greater number needs to search circularly, which is also 2.
// Example 2:

// Input: nums = [1,2,3,4,3]
// Output: [2,3,4,-1,4]

class Solution {
 public:
  vector<int> nextGreaterElements(vector<int>& nums) {
    const int n = nums.size();
    vector<int> ans(n, -1);
    stack<int> stack;  // a decreasing stack storing indices

    for (int i = 0; i < n * 2; ++i) {
      const int num = nums[i % n];
      while (!stack.empty() && nums[stack.top()] < num)
        ans[stack.top()] = num, stack.pop();
      if (i < n)
        stack.push(i);
    }

    return ans;
  }
};

// 581. Shortest Unsorted Continuous Subarray
// Medium

// Topics
// Companies
// Given an integer array nums, you need to find one continuous subarray such that if you only sort this subarray in non-decreasing order, then the whole array will be sorted in non-decreasing order.

// Return the shortest such subarray and output its length.

 

// Example 1:

// Input: nums = [2,6,4,8,10,9,15]
// Output: 5
// Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
// Example 2:

// Input: nums = [1,2,3,4]
// Output: 0
// Example 3:

// Input: nums = [1]
// Output: 0

class Solution {
 public:
  int findUnsortedSubarray(vector<int>& nums) {
    const int n = nums.size();
    int mn = INT_MAX;
    int mx = INT_MIN;
    bool meetDecrease = false;
    bool meetIncrease = false;

    for (int i = 1; i < n; ++i) {
      if (nums[i] < nums[i - 1])
        meetDecrease = true;
      if (meetDecrease)
        mn = min(mn, nums[i]);
    }

    for (int i = n - 2; i >= 0; --i) {
      if (nums[i] > nums[i + 1])
        meetIncrease = true;
      if (meetIncrease)
        mx = max(mx, nums[i]);
    }

    int l;
    for (l = 0; l < n; ++l)
      if (nums[l] > mn)
        break;

    int r;
    for (r = n - 1; r >= 0; --r)
      if (nums[r] < mx)
        break;

    return l < r ? r - l + 1 : 0;
  }
};

// 589. N-ary Tree Preorder Traversal
// Easy

// Topics
// Companies
// Given the root of an n-ary tree, return the preorder traversal of its nodes' values.

// Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)

 

// Example 1:



// Input: root = [1,null,3,2,4,null,5,6]
// Output: [1,3,5,6,2,4]
// Example 2:



// Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
// Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]

/*
// Definition for a Node.
*/
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
 public:
  vector<int> preorder(Node* root) {
    if (root == nullptr)
      return {};

    vector<int> ans;
    stack<Node*> stack{{root}};

    while (!stack.empty()) {
      root = stack.top(), stack.pop();
      ans.push_back(root->val);
      for (auto it = root->children.rbegin(); it != root->children.rend(); ++it)
        stack.push(*it);
    }

    return ans;
  }
};

// 636. Exclusive Time of Functions
// Medium

// Topics
// Companies
// On a single-threaded CPU, we execute a program containing n functions. Each function has a unique ID between 0 and n-1.

// Function calls are stored in a call stack: when a function call starts, its ID is pushed onto the stack, and when a function call ends, its ID is popped off the stack. The function whose ID is at the top of the stack is the current function being executed. Each time a function starts or ends, we write a log with the ID, whether it started or ended, and the timestamp.

// You are given a list logs, where logs[i] represents the ith log message formatted as a string "{function_id}:{"start" | "end"}:{timestamp}". For example, "0:start:3" means a function call with function ID 0 started at the beginning of timestamp 3, and "1:end:2" means a function call with function ID 1 ended at the end of timestamp 2. Note that a function can be called multiple times, possibly recursively.

// A function's exclusive time is the sum of execution times for all function calls in the program. For example, if a function is called twice, one call executing for 2 time units and another call executing for 1 time unit, the exclusive time is 2 + 1 = 3.

// Return the exclusive time of each function in an array, where the value at the ith index represents the exclusive time for the function with ID i.

 

// Example 1:


// Input: n = 2, logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
// Output: [3,4]
// Explanation:
// Function 0 starts at the beginning of time 0, then it executes 2 for units of time and reaches the end of time 1.
// Function 1 starts at the beginning of time 2, executes for 4 units of time, and ends at the end of time 5.
// Function 0 resumes execution at the beginning of time 6 and executes for 1 unit of time.
// So function 0 spends 2 + 1 = 3 units of total time executing, and function 1 spends 4 units of total time executing.
// Example 2:

// Input: n = 1, logs = ["0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"]
// Output: [8]
// Explanation:
// Function 0 starts at the beginning of time 0, executes for 2 units of time, and recursively calls itself.
// Function 0 (recursive call) starts at the beginning of time 2 and executes for 4 units of time.
// Function 0 (initial call) resumes execution then immediately calls itself again.
// Function 0 (2nd recursive call) starts at the beginning of time 6 and executes for 1 unit of time.
// Function 0 (initial call) resumes execution at the beginning of time 7 and executes for 1 unit of time.
// So function 0 spends 2 + 4 + 1 + 1 = 8 units of total time executing.
// Example 3:

// Input: n = 2, logs = ["0:start:0","0:start:2","0:end:5","1:start:6","1:end:6","0:end:7"]
// Output: [7,1]
// Explanation:
// Function 0 starts at the beginning of time 0, executes for 2 units of time, and recursively calls itself.
// Function 0 (recursive call) starts at the beginning of time 2 and executes for 4 units of time.
// Function 0 (initial call) resumes execution then immediately calls function 1.
// Function 1 starts at the beginning of time 6, executes 1 unit of time, and ends at the end of time 6.
// Function 0 resumes execution at the beginning of time 6 and executes for 2 units of time.
// So function 0 spends 2 + 4 + 1 = 7 units of total time executing, and function 1 spends 1 unit of total time executing.

class Solution {
 public:
  vector<int> exclusiveTime(int n, vector<string>& logs) {
    vector<int> ans(n);
    stack<int> stack;  // [oldest_id, ..., latest_id]
    int prevTime;

    for (const string& log : logs) {
      // Get the seperators' indices.
      const int colon1 = log.find_first_of(':');
      const int colon2 = log.find_last_of(':');
      // Get the function_id, the label, and the timestamp.
      const int id = stoi(log.substr(0, colon1));  // {function_id}
      const char label = log[colon1 + 1];  // {"s" ("start") | "e" ("end") }
      const int timestamp = stoi(log.substr(colon2 + 1));  // {timestamp}
      if (label == 's') {
        if (!stack.empty())
          ans[stack.top()] += timestamp - prevTime;
        stack.push(id);
        prevTime = timestamp;
      } else {
        ans[stack.top()] += timestamp - prevTime + 1, stack.pop();
        prevTime = timestamp + 1;
      }
    }

    return ans;
  }
};

// 654. Maximum Binary Tree
// Medium

// Topics
// Companies
// You are given an integer array nums with no duplicates. A maximum binary tree can be built recursively from nums using the following algorithm:

// Create a root node whose value is the maximum value in nums.
// Recursively build the left subtree on the subarray prefix to the left of the maximum value.
// Recursively build the right subtree on the subarray suffix to the right of the maximum value.
// Return the maximum binary tree built from nums.

 

// Example 1:


// Input: nums = [3,2,1,6,0,5]
// Output: [6,3,5,null,2,0,null,null,1]
// Explanation: The recursive calls are as follow:
// - The largest value in [3,2,1,6,0,5] is 6. Left prefix is [3,2,1] and right suffix is [0,5].
//     - The largest value in [3,2,1] is 3. Left prefix is [] and right suffix is [2,1].
//         - Empty array, so no child.
//         - The largest value in [2,1] is 2. Left prefix is [] and right suffix is [1].
//             - Empty array, so no child.
//             - Only one element, so child is a node with value 1.
//     - The largest value in [0,5] is 5. Left prefix is [0] and right suffix is [].
//         - Only one element, so child is a node with value 0.
//         - Empty array, so no child.
// Example 2:


// Input: nums = [3,2,1]
// Output: [3,null,2,null,1]

class Solution {
 public:
  TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    return build(nums, 0, nums.size() - 1);
  }

 private:
  TreeNode* build(const vector<int>& nums, int i, int j) {
    if (i > j)
      return nullptr;

    const auto it = max_element(nums.begin() + i, nums.begin() + j + 1);
    const int maxNum = *it;
    const int maxIndex = it - nums.begin();

    TreeNode* root = new TreeNode(maxNum);
    root->left = build(nums, i, maxIndex - 1);
    root->right = build(nums, maxIndex + 1, j);
    return root;
  }
};

