#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <unordered_set>

using namespace std;

// 1. Array Palindrome Check and Conversion
bool isPalindromeArray(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        if (arr[left] != arr[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

vector<int> makePalindromeArray(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        if (arr[left] != arr[right]) {
            arr[right] = arr[left];
        }
        left++;
        right--;
    }
    return arr;
}


bool isPalindrome(const string& s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

bool isSubstring(const string& s, const string& t) {
    return s.find(t) != string::npos;
}

// 1. Array Palindrome Check and Conversion
vector<string> maxPalindromesArray(const string& s) {
    vector<string> result;
    unordered_set<string> unique_palindromes;

    for (size_t i = 0; i < s.size(); ++i) {
        for (size_t length = 1; length <= s.size() - i; ++length) {
            string substring = s.substr(i, length);
            if (isPalindrome(substring) && unique_palindromes.find(substring) == unique_palindromes.end()) {
                result.push_back(substring);
                unique_palindromes.insert(substring);
            }
        }
    }

    vector<string> filtered_result;
    for (const auto& t : result) {
        bool is_sub = false;
        for (const auto& ss : result) {
            if (t != ss && isSubstring(ss, t)) {
                is_sub = true;
                break;
            }
        }
        if (!is_sub) {
            filtered_result.push_back(t);
        }
    }

    return filtered_result;
}






// 2. LinkedList Palindrome Check and Conversion
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

bool isPalindromeLinkedList(ListNode* head) {
    stack<int> stack;
    ListNode* node = head;
    while (node != nullptr) {
        stack.push(node->val);
        node = node->next;
    }

    while (head != nullptr) {
        if (head->val != stack.top()) {
            return false;
        }
        stack.pop();
        head = head->next;
    }
    return true;
}


// 링크드 리스트를 반전시키는 함수
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;
    }
    return prev;
}

bool isPalindromeList(ListNode* head) {
    vector<int> vals;
    while (head != nullptr) {
        vals.push_back(head->val);
        head = head->next;
    }
    return isPalindrome(string(vals.begin(), vals.end()));
}

vector<string> maxPalindromesList(ListNode* head) {
    string chars;
    while (head != nullptr) {
        chars += to_string(head->val);
        head = head->next;
    }
    return maxPalindromesArray(chars);
}





// 3. Double LinkedList Palindrome Check and Conversion
struct DoubleListNode {
    int val;
    DoubleListNode* prev;
    DoubleListNode* next;
    DoubleListNode(int x) : val(x), prev(nullptr), next(nullptr) {}
};

// Palindrome 체크 함수
bool isPalindromeDoubleLinkedList(DoubleListNode* left) {
    if (left == nullptr) return true;

    // 리스트의 오른쪽 끝 (tail) 찾기
    DoubleListNode* right = left;
    while (right->next != nullptr) {
        right = right->next;
    }

    // head와 tail이 만날 때까지 혹은 교차할 때까지 비교
    while (left != right) {
        if (left->val != right->val) {
            return false;
        }
        
        // head와 tail이 인접한 경우 종료
        if (left->next == right) break;

        left = left->next;
        right = right->prev;
    }

    return true;
}

DoubleListNode* makePalindromeDoubleLinkedList(DoubleListNode* head) {
    if (!head) return nullptr;

    DoubleListNode* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    DoubleListNode* start = head;
    while (start != tail && start->prev != tail) {
        if (start->val != tail->val) {
            tail->val = start->val;
        }
        start = start->next;
        tail = tail->prev;
    }
    return head;
}


vector<string> maxPalindromesDoubleList(DoubleListNode* head) {
    string chars;
    while (head != nullptr) {
        chars += to_string(head->val);
        head = head->next;
    }
    return maxPalindromesArray(chars);
}







// 4. Stack Palindrome Check and Conversion
bool isPalindromeStack(ListNode* head) {
    stack<int> stack;
    ListNode* node = head;
    while (node != nullptr) {
        stack.push(node->val);
        node = node->next;
    }

    while (head != nullptr) {
        if (head->val != stack.top()) {
            return false;
        }
        stack.pop();
        head = head->next;
    }
    return true;
}


// 회문으로 변환하는 함수
ListNode* makePalindromeStack(ListNode* head) {
    if (head == nullptr) return nullptr;

    stack<int> stack;
    ListNode* slow = head;
    ListNode* fast = head;

    // 리스트의 전반부를 스택에 저장
    while (fast != nullptr && fast->next != nullptr) {
        stack.push(slow->val);
        slow = slow->next;
        fast = fast->next->next;
    }

    // 리스트의 요소 개수가 홀수인 경우, 중간 노드를 건너뜀
    if (fast != nullptr) { // 홀수 개의 요소
        slow = slow->next;
    }

    // 후반부를 스택의 값으로 수정하여 회문을 만듦
    while (slow != nullptr) {
        if (!stack.empty()) {
            slow->val = stack.top();
            stack.pop();
        }
        slow = slow->next;
    }

    return head;
}


vector<string> maxPalindromesStack(const string& s) {
    stack<string> stack;
    vector<string> result;
    unordered_set<string> unique_palindromes;

    for (size_t i = 0; i < s.size(); ++i) {
        for (size_t j = i + 1; j <= s.size(); ++j) {
            string substring = s.substr(i, j - i);
            stack.push(substring);
        }
    }

    while (!stack.empty()) {
        string substring = stack.top();
        stack.pop();
        if (isPalindrome(substring) && unique_palindromes.find(substring) == unique_palindromes.end()) {
            result.push_back(substring);
            unique_palindromes.insert(substring);
        }
    }

    vector<string> filtered_result;
    for (const auto& t : result) {
        bool is_sub = false;
        for (const auto& ss : result) {
            if (t != ss && isSubstring(ss, t)) {
                is_sub = true;
                break;
            }
        }
        if (!is_sub) {
            filtered_result.push_back(t);
        }
    }

    return filtered_result;
}



// // 5. Queue Palindrome Check and Conversion
// bool isPalindromeQueue(ListNode* head) {
//     if (!head) return true;

//     ListNode* slow = head;
//     ListNode* fast = head;
//     queue<int> q;

//     // 리스트의 중간까지 큐에 값을 넣음
//     while (fast != nullptr && fast->next != nullptr) {
//         q.push(slow->val);
//         slow = slow->next;
//         fast = fast->next->next;
//     }

//     // 리스트의 길이가 홀수인 경우 중간 노드를 건너뜀
//     if (fast != nullptr) {
//         slow = slow->next;
//     }

//     // 큐에서 값을 꺼내어 비교
//     while (slow != nullptr) {
//         if (slow->val != q.front()) {
//             return false;
//         }
//         q.pop();
//         slow = slow->next;
//     }

//     return true;
// }


// ListNode* makePalindromeQueue(ListNode* head) {
//     queue<int> queue;
//     ListNode* node = head;
//     while (node != nullptr) {
//         queue.push(node->val);
//         node = node->next;
//     }

//     node = head;
//     while (!queue.empty()) {
//         node->val = queue.front();
//         queue.pop();
//         node = node->next;
//     }
//     return head;
// }

// 6. Deque Palindrome Check and Conversion
bool isPalindromeDeque(ListNode* head) {
    deque<int> deque;
    ListNode* node = head;
    while (node != nullptr) {
        deque.push_back(node->val);
        node = node->next;
    }

    while (deque.size() > 1) {
        if (deque.front() != deque.back()) {
            return false;
        }
        deque.pop_front();
        deque.pop_back();
    }
    return true;
}

vector<string> maxPalindromesDeque(const string& s) {
    deque<string> q;
    vector<string> result;
    unordered_set<string> unique_palindromes;

    for (size_t i = 0; i < s.size(); ++i) {
        for (size_t j = i + 1; j <= s.size(); ++j) {
            string substring = s.substr(i, j - i);
            q.push_back(substring);
        }
    }

    while (!q.empty()) {
        string substring = q.back();
        q.pop_back();
        if (isPalindrome(substring) && unique_palindromes.find(substring) == unique_palindromes.end()) {
            result.push_back(substring);
            unique_palindromes.insert(substring);
        }
    }

    vector<string> filtered_result;
    for (const auto& t : result) {
        bool is_sub = false;
        for (const auto& ss : result) {
            if (t != ss && isSubstring(ss, t)) {
                is_sub = true;
                break;
            }
        }
        if (!is_sub) {
            filtered_result.push_back(t);
        }
    }

    return filtered_result;
}




// 7. Dynamic Programming Palindrome Check and Conversion
bool isPalindromeDP(string s) {
    int n = s.length();
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            if (length == 2) {
                dp[i][j] = (s[i] == s[j]);
            } else {
                dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
            }
        }
    }
    return dp[0][n - 1];
}

string makePalindromeDP(string s) {
    int n = s.length();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    vector<vector<int>> changes(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            if (s[i] == s[j]) {
                dp[i][j] = true;
                changes[i][j] = changes[i + 1][j - 1];
            } else {
                if (changes[i + 1][j] < changes[i][j - 1]) {
                    changes[i][j] = changes[i + 1][j] + 1;
                } else {
                    changes[i][j] = changes[i][j - 1] + 1;
                }
            }
        }
    }

    string result(s.length() + changes[0][n - 1], ' ');
    int left = 0, right = result.length() - 1;
    int i = 0, j = n - 1;
    while (i <= j) {
        if (s[i] == s[j]) {
            result[left++] = s[i++];
            result[right--] = s[j--];
        } else if (changes[i + 1][j] < changes[i][j - 1]) {
            result[left++] = s[i];
            result[right--] = s[i++];
        } else {
            result[left++] = s[j];
            result[right--] = s[j--];
        }
    }

    return result;
}


vector<string> maxPalindromesDP(const string& s) {
    int n = s.length();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    vector<string> result;

    // 길이가 1인 모든 부분 문자열은 회문이다.
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
        result.push_back(s.substr(i, 1));
    }

    // 길이가 2인 부분 문자열에 대해 회문 여부 확인
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            result.push_back(s.substr(i, 2));
        }
    }

    // 길이가 3 이상인 부분 문자열에 대해 회문 여부 확인
    for (int length = 3; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                result.push_back(s.substr(i, length));
            }
        }
    }

    // 결과 리스트에서 중복된 부분 문자열 제거
    vector<string> filtered_result;
    for (const auto& t : result) {
        bool is_sub = false;
        for (const auto& ss : result) {
            if (t != ss && isSubstring(ss, t)) {
                is_sub = true;
                break;
            }
        }
        if (!is_sub) {
            filtered_result.push_back(t);
        }
    }

    return filtered_result;
}





// Main function to demonstrate all methods
int main() {
    // Array example
    string arrStr = "12321";
    vector<int> arr = {1, 2, 3, 2, 1};
    cout << "Array is Palindrome: " << isPalindromeArray(arr) << endl;

    vector<int> nonPalindromeArr = {1, 2, 3, 4, 5};
    cout << "Array is Palindrome: " << isPalindromeArray(nonPalindromeArr) << endl;
    vector<int> palindromeArr = makePalindromeArray(nonPalindromeArr);
    cout << "Converted Palindrome Array: ";
    for (int num : palindromeArr) {
        cout << num << " ";
    }
    cout << endl;

    vector<string> arrayPalindromes = maxPalindromesArray(arrStr);
    cout << "Max Palindromes in Array: ";
    for (const string& palindrome : arrayPalindromes) {
        cout << palindrome << " ";
    }
    cout << endl;
    cout << endl;

    // LinkedList example
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(2);
    head->next->next->next->next = new ListNode(1);
    cout << "LinkedList is Palindrome: " << isPalindromeLinkedList(head) << endl;

    ListNode* nonPalindromeHead = new ListNode(1);
    nonPalindromeHead->next = new ListNode(2);
    nonPalindromeHead->next->next = new ListNode(3);
    nonPalindromeHead->next->next->next = new ListNode(4);

    cout << "LinkedList is Palindrome: " << isPalindromeLinkedList(nonPalindromeHead) << endl;
    vector<string> listPalindromes = maxPalindromesList(head);
    cout << "Max Palindromes in LinkedList: ";
    for (const string& palindrome : listPalindromes) {
        cout << palindrome << " ";
    }
    cout << endl;
    cout << endl;

    // Double LinkedList example
    DoubleListNode* doubleHead = new DoubleListNode(1);
    doubleHead->next = new DoubleListNode(2);
    doubleHead->next->prev = doubleHead;
    doubleHead->next->next = new DoubleListNode(3);
    doubleHead->next->next->prev = doubleHead->next;
    doubleHead->next->next->next = new DoubleListNode(2);
    doubleHead->next->next->next->prev = doubleHead->next->next;
    doubleHead->next->next->next->next = new DoubleListNode(1);
    doubleHead->next->next->next->next->prev = doubleHead->next->next->next;
    cout << "Double LinkedList is Palindrome: " << isPalindromeDoubleLinkedList(doubleHead) << endl;

    DoubleListNode* nonPalindromeDoubleHead = new DoubleListNode(1);
    nonPalindromeDoubleHead->next = new DoubleListNode(2);
    nonPalindromeDoubleHead->next->prev = nonPalindromeDoubleHead;
    nonPalindromeDoubleHead->next->next = new DoubleListNode(3);
    nonPalindromeDoubleHead->next->next->prev = nonPalindromeDoubleHead->next;
    nonPalindromeDoubleHead->next->next->next = new DoubleListNode(4);
    nonPalindromeDoubleHead->next->next->next->prev = nonPalindromeDoubleHead->next->next;

    cout << "Double LinkedList is Palindrome: " << isPalindromeDoubleLinkedList(nonPalindromeDoubleHead) << endl;
    vector<string> doubleListPalindromes = maxPalindromesDoubleList(doubleHead);
    cout << "Max Palindromes in Double LinkedList: ";
    for (const string& palindrome : doubleListPalindromes) {
        cout << palindrome << " ";
    }
    cout << endl;
    cout << endl;

    // Stack example
    string stackStr = "12321";
    ListNode* stackHead = new ListNode(1);
    stackHead->next = new ListNode(2);
    stackHead->next->next = new ListNode(3);
    stackHead->next->next->next = new ListNode(2);
    stackHead->next->next->next->next = new ListNode(1);
    cout << "Stack is Palindrome: " << isPalindromeStack(stackHead) << endl;

    ListNode* nonPalindromeStackHead = new ListNode(1);
    nonPalindromeStackHead->next = new ListNode(2);
    nonPalindromeStackHead->next->next = new ListNode(3);
    nonPalindromeStackHead->next->next->next = new ListNode(4);

    cout << "Stack is Palindrome: " << isPalindromeStack(nonPalindromeStackHead) << endl;
    vector<string> stackPalindromes = maxPalindromesStack(stackStr);
    cout << "Max Palindromes in Stack: ";
    for (const string& palindrome : stackPalindromes) {
        cout << palindrome << " ";
    }
    cout << endl;
    cout << endl;

    // Deque example
    string dequeStr = "12321";
    ListNode* dequeHead = new ListNode(1);
    dequeHead->next = new ListNode(2);
    dequeHead->next->next = new ListNode(3);
    dequeHead->next->next->next = new ListNode(2);
    dequeHead->next->next->next->next = new ListNode(1);
    cout << "Deque is Palindrome: " << isPalindromeDeque(dequeHead) << endl;

    ListNode* nonPalindromeDequeHead = new ListNode(1);
    nonPalindromeDequeHead->next = new ListNode(2);
    nonPalindromeDequeHead->next->next = new ListNode(3);
    nonPalindromeDequeHead->next->next->next = new ListNode(4);

    vector<string> dequePalindromes = maxPalindromesDeque(dequeStr);
    cout << "Max Palindromes in Deque: ";
    for (const string& palindrome : dequePalindromes) {
        cout << palindrome << " ";
    }
    cout << endl;
    cout << endl;

    // Dynamic Programming example
    string dpStr = "abcba";
    cout << "String is Palindrome: " << isPalindromeDP(dpStr) << endl;

    string nonPalindromeStr = "abcde";
    cout << "String is Palindrome: " << isPalindromeDP(nonPalindromeStr) << endl;
    string palindromeStr = makePalindromeDP(nonPalindromeStr);
    cout << "Converted Palindrome String: " << palindromeStr << endl;

    vector<string> dpPalindromes = maxPalindromesDP(dpStr);
    cout << "Max Palindromes in String (DP): ";
    for (const string& palindrome : dpPalindromes) {
        cout << palindrome << " ";
    }
    cout << endl;

    return 0;
}
