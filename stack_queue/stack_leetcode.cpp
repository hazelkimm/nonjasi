#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

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

