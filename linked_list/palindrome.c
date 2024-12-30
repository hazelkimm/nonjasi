#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Linked list node
struct ListNode {
    int val;
    struct ListNode* next;
};

struct DoubleListNode {
    int val;
    struct DoubleListNode* prev;
    struct DoubleListNode* next;
};

// 1. Array Palindrome Check and Conversion
bool isPalindromeArray(int arr[], int size) {
    int left = 0, right = size - 1;
    while (left < right) {
        if (arr[left] != arr[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

void makePalindromeArray(int arr[], int size) {
    int left = 0, right = size - 1;
    while (left < right) {
        if (arr[left] != arr[right]) {
            arr[right] = arr[left];
        }
        left++;
        right--;
    }
}

// 회문 여부를 확인하는 함수
bool is_palindrome_array(const char *s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

// 문자열이 다른 문자열의 부분 문자열인지 확인하는 함수
bool is_substring(const char *s, const char *t) {
    return strstr(s, t) != NULL;
}

// 주어진 문자열에서 모든 고유한 회문 부분 문자열을 찾는 함수
void max_palindromes_array(const char *s, char result[][100], int *result_count) {
    int len = strlen(s);
    int temp_count = 0;
    char temp_result[100][100];  // 임시 저장 공간

    // 모든 부분 문자열을 탐색
    for (int i = 0; i < len; i++) {
        for (int l = 1; l <= len - i; l++) {
            if (is_palindrome_array(s, i, i + l - 1)) {
                bool exists = false;

                // 중복 확인
                for (int k = 0; k < temp_count; k++) {
                    if (strncmp(temp_result[k], &s[i], l) == 0 && strlen(temp_result[k]) == l) {
                        exists = true;
                        break;
                    }
                }

                if (!exists) {
                    strncpy(temp_result[temp_count], &s[i], l);
                    temp_result[temp_count][l] = '\0';
                    temp_count++;
                }
            }
        }
    }

    int sub_count = 0;
    char sub[100][100];  // 중복된 부분 문자열 저장 공간

    for (int i = 0; i < temp_count; i++) {
        for (int j = 0; j < temp_count; j++) {
            if (i != j && is_substring(temp_result[j], temp_result[i])) {
                strncpy(sub[sub_count], temp_result[i], strlen(temp_result[i]));
                sub[sub_count][strlen(temp_result[i])] = '\0';
                sub_count++;
                break;
            }
        }
    }

    // 중복을 제거한 결과를 result에 저장
    int final_count = 0;
    for (int i = 0; i < temp_count; i++) {
        bool is_sub = false;
        for (int j = 0; j < sub_count; j++) {
            if (strcmp(temp_result[i], sub[j]) == 0) {
                is_sub = true;
                break;
            }
        }
        if (!is_sub) {
            strncpy(result[final_count], temp_result[i], strlen(temp_result[i]));
            result[final_count][strlen(temp_result[i])] = '\0';
            final_count++;
        }
    }

    *result_count = final_count;
}






// 2. LinkedList Palindrome Check and Conversion
bool isPalindromeLinkedList(struct ListNode* head) {
    struct ListNode* node = head;
    int stack[1000], top = 0;

    while (node) {
        stack[top++] = node->val;
        node = node->next;
    }

    node = head;
    while (node) {
        if (node->val != stack[--top]) {
            return false;
        }
        node = node->next;
    }
    return true;
}

struct ListNode* makePalindromeLinkedList(struct ListNode* head) {
    if (!head) return NULL;

    struct ListNode* node = head;
    int stack[1000], top = 0;

    // 스택에 리스트 후반부 저장
    while (node) {
        stack[top++] = node->val;
        node = node->next;
    }

    node = head;
    // 스택에서 값을 꺼내 리스트 앞부분을 대칭적으로 수정
    while (top > 0 && node) {
        node->val = stack[--top];
        node = node->next;
    }

    return head;
}

void max_palindromes_linked_list(struct ListNode* head, char result[][100], int *result_count) {
    char chars[1000];
    int len = 0;

    struct ListNode* curr = head;
    while (curr) {
        chars[len++] = curr->val + '0';
        curr = curr->next;
    }
    chars[len] = '\0';

    max_palindromes_array(chars, result, result_count);
}




// 3. Double LinkedList Palindrome Check and Conversion
bool isPalindromeDoubleLinkedList(struct DoubleListNode* head) {
    if (!head) return true;

    struct DoubleListNode* tail = head;
    while (tail->next) {
        tail = tail->next;
    }

    while (head != tail && head->prev != tail) {
        if (head->val != tail->val) {
            return false;
        }
        head = head->next;
        tail = tail->prev;
    }

    return true;
}

struct DoubleListNode* makePalindromeDoubleLinkedList(struct DoubleListNode* head) {
    if (!head) return NULL;

    struct DoubleListNode* tail = head;
    while (tail->next) {
        tail = tail->next;
    }

    struct DoubleListNode* start = head;
    while (start != tail && start->prev != tail) {
        if (start->val != tail->val) {
            tail->val = start->val;
        }
        start = start->next;
        tail = tail->prev;
    }
    return head;
}


void max_palindromes_double_list(struct DoubleListNode* head, char result[][100], int *result_count) {
    char chars[1000];
    int len = 0;

    struct DoubleListNode* curr = head;
    while (curr) {
        chars[len++] = curr->val + '0';
        curr = curr->next;
    }
    chars[len] = '\0';

    max_palindromes_array(chars, result, result_count);
}







// 6. Deque Palindrome Check and Conversion
bool isPalindromeDeque(struct ListNode* head) {
    int deque[1000];
    int front = 0, back = 0;

    struct ListNode* node = head;
    while (node) {
        deque[back++] = node->val;
        node = node->next;
    }

    back--;
    while (front < back) {
        if (deque[front++] != deque[back--]) {
            return false;
        }
    }
    return true;
}

struct ListNode* makePalindromeDeque(struct ListNode* head) {
    if (!head) return NULL;

    int deque[1000];
    int front = 0, back = 0;

    struct ListNode* node = head;

    // 리스트의 모든 값을 deque에 추가
    while (node) {
        deque[back++] = node->val;
        node = node->next;
    }

    node = head;
    back--;
    // deque의 앞과 뒤를 비교하여 리스트를 수정
    while (front < back) {
        node->val = deque[back--];
        node = node->next;
    }

    return head;
}

// 7. Dynamic Programming Palindrome Check and Conversion
bool isPalindromeDP(char* s) {
    int n = strlen(s);
    bool dp[n][n];

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

char* makePalindromeDP(char* s) {
    int n = strlen(s);
    bool dp[n][n];
    int changes[n][n];

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

    int result_len = n + changes[0][n - 1];
    char* result = (char*)malloc(result_len + 1);
    memset(result, 0, result_len + 1);
    int left = 0, right = result_len - 1;
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

// Main function to demonstrate all methods
int main() {
    // 1. Array example
    printf("=== Array Example ===\n");
    int arr[] = {1, 2, 3, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Array is Palindrome: %s\n", isPalindromeArray(arr, size) ? "True" : "False");

    int non_palindrome_arr[] = {1, 2, 3, 4, 5};
    int non_palindrome_size = sizeof(non_palindrome_arr) / sizeof(non_palindrome_arr[0]);
    printf("Non-Palindrome Array is Palindrome: %s\n", isPalindromeArray(non_palindrome_arr, non_palindrome_size) ? "True" : "False");
    makePalindromeArray(non_palindrome_arr, non_palindrome_size);
    printf("Converted Palindrome Array: ");
    for (int i = 0; i < non_palindrome_size; i++) {
        printf("%d ", non_palindrome_arr[i]);
    }
    printf("\n");

    char arr_str[] = "12345";
    char arr_result[100][100];
    int arr_result_count = 0;
    max_palindromes_array(arr_str, arr_result, &arr_result_count);
    printf("Max Palindromic Substrings in Array:\n");
    for (int i = 0; i < arr_result_count; i++) {
        printf("%s\n", arr_result[i]);
    }
    printf("\n");

    // 2. LinkedList example
    printf("=== LinkedList Example ===\n");
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->val = 1;
    head->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->val = 2;
    head->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->next->val = 3;
    head->next->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->next->next->val = 2;
    head->next->next->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->next->next->next->val = 1;
    head->next->next->next->next->next = NULL;

    printf("LinkedList is Palindrome: %s\n", isPalindromeLinkedList(head) ? "True" : "False");

    struct ListNode* non_palindrome_head = (struct ListNode*)malloc(sizeof(struct ListNode));
    non_palindrome_head->val = 1;
    non_palindrome_head->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    non_palindrome_head->next->val = 2;
    non_palindrome_head->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    non_palindrome_head->next->next->val = 3;
    non_palindrome_head->next->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    non_palindrome_head->next->next->next->val = 4;
    non_palindrome_head->next->next->next->next = NULL;

    printf("Non-Palindrome LinkedList is Palindrome: %s\n", isPalindromeLinkedList(non_palindrome_head) ? "True" : "False");
    makePalindromeLinkedList(non_palindrome_head);
    printf("Converted Palindrome LinkedList: ");
    struct ListNode* node = non_palindrome_head;
    while (node) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");

    char linked_list_result[100][100];
    int linked_list_result_count = 0;
    max_palindromes_linked_list(non_palindrome_head, linked_list_result, &linked_list_result_count);
    printf("Max Palindromic Substrings in LinkedList:\n");
    for (int i = 0; i < linked_list_result_count; i++) {
        printf("%s\n", linked_list_result[i]);
    }
    printf("\n");

    // 3. Double LinkedList example
    printf("=== Double LinkedList Example ===\n");
    struct DoubleListNode* double_head = (struct DoubleListNode*)malloc(sizeof(struct DoubleListNode));
    double_head->val = 1;
    double_head->next = (struct DoubleListNode*)malloc(sizeof(struct DoubleListNode));
    double_head->next->val = 2;
    double_head->next->prev = double_head;
    double_head->next->next = (struct DoubleListNode*)malloc(sizeof(struct DoubleListNode));
    double_head->next->next->val = 3;
    double_head->next->next->prev = double_head->next;
    double_head->next->next->next = (struct DoubleListNode*)malloc(sizeof(struct DoubleListNode));
    double_head->next->next->next->val = 2;
    double_head->next->next->next->prev = double_head->next->next;
    double_head->next->next->next->next = (struct DoubleListNode*)malloc(sizeof(struct DoubleListNode));
    double_head->next->next->next->next->val = 1;
    double_head->next->next->next->next->prev = double_head->next->next->next;
    double_head->next->next->next->next->next = NULL;
    printf("Double LinkedList is Palindrome: %s\n", isPalindromeDoubleLinkedList(double_head) ? "True" : "False");

    struct DoubleListNode* non_palindrome_double_head = (struct DoubleListNode*)malloc(sizeof(struct DoubleListNode));
    non_palindrome_double_head->val = 1;
    non_palindrome_double_head->next = (struct DoubleListNode*)malloc(sizeof(struct DoubleListNode));
    non_palindrome_double_head->next->val = 2;
    non_palindrome_double_head->next->prev = non_palindrome_double_head;
    non_palindrome_double_head->next->next = (struct DoubleListNode*)malloc(sizeof(struct DoubleListNode));
    non_palindrome_double_head->next->next->val = 3;
    non_palindrome_double_head->next->next->prev = non_palindrome_double_head->next;
    non_palindrome_double_head->next->next->next = (struct DoubleListNode*)malloc(sizeof(struct DoubleListNode));
    non_palindrome_double_head->next->next->next->val = 4;
    non_palindrome_double_head->next->next->next->prev = non_palindrome_double_head->next->next;
    non_palindrome_double_head->next->next->next->next = NULL;

    printf("Non-Palindrome Double LinkedList is Palindrome: %s\n", isPalindromeDoubleLinkedList(non_palindrome_double_head) ? "True" : "False");
    makePalindromeDoubleLinkedList(non_palindrome_double_head);
    printf("Converted Palindrome Double LinkedList: ");
    struct DoubleListNode* double_node = non_palindrome_double_head;
    while (double_node) {
        printf("%d ", double_node->val);
        double_node = double_node->next;
    }
    printf("\n");

    char double_list_result[100][100];
    int double_list_result_count = 0;
    max_palindromes_double_list(non_palindrome_double_head, double_list_result, &double_list_result_count);
    printf("Max Palindromic Substrings in Double LinkedList:\n");
    for (int i = 0; i < double_list_result_count; i++) {
        printf("%s\n", double_list_result[i]);
    }
    printf("\n");

    // 4. Deque example
    printf("=== Deque Example ===\n");
    struct ListNode* deque_head = (struct ListNode*)malloc(sizeof(struct ListNode));
    deque_head->val = 1;
    deque_head->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    deque_head->next->val = 2;
    deque_head->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    deque_head->next->next->val = 3;
    deque_head->next->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    deque_head->next->next->next->val = 4;
    deque_head->next->next->next->next = NULL;

    printf("Deque is Palindrome: %s\n", isPalindromeDeque(deque_head) ? "True" : "False");
    makePalindromeDeque(deque_head);
    printf("Converted Palindrome Deque: ");
    node = deque_head;
    while (node) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");

    char deque_str[] = "12321";
    char deque_result[100][100];
    int deque_result_count = 0;
    max_palindromes_array(deque_str, deque_result, &deque_result_count);
    printf("Max Palindromic Substrings in Deque:\n");
    for (int i = 0; i < deque_result_count; i++) {
        printf("%s\n", deque_result[i]);
    }
    printf("\n");

    // 5. Dynamic Programming example
    printf("=== Dynamic Programming Example ===\n");
    char s[] = "abcba";
    printf("String is Palindrome: %s\n", isPalindromeDP(s) ? "True" : "False");

    char non_palindrome_str[] = "abcde";
    printf("String is Palindrome: %s\n", isPalindromeDP(non_palindrome_str) ? "True" : "False");
    char* palindrome_str = makePalindromeDP(non_palindrome_str);
    printf("Converted Palindrome String: %s\n", palindrome_str);

    char dp_result[100][100];
    int dp_result_count = 0;
    // max_palindromes_dp(s, dp_result, &dp_result_count);
    // printf("Max Palindromic Substrings in String:\n");
    // for (int i = 0; i < dp_result_count; i++) {
    //     printf("%s\n", dp_result[i]);
    // }
    // printf("\n");

    free(palindrome_str);
    return 0;
}
