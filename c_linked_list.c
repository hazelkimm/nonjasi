#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Definition for singly-linked list
struct ListNode {
    int val;
    struct ListNode* next;
};

// Function to create a linked list from an array
struct ListNode* createLinkedList(int arr[], int n) {
    if (n == 0) {
        return NULL;
    }

    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->val = arr[0];
    head->next = NULL;

    struct ListNode* current = head;

    for (int i = 1; i < n; ++i) {
        current->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        current = current->next;
        current->val = arr[i];
        current->next = NULL;
    }

    return head;
}

// Function to print the linked list
void printLinkedList(struct ListNode* head) {
    while (head != NULL) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

// Example usage:
int main() {
    int myArray[] = {1, 2, 3, 4, 5};
    int arraySize = sizeof(myArray) / sizeof(myArray[0]);

    struct ListNode* myLinkedList = createLinkedList(myArray, arraySize);
    printLinkedList(myLinkedList);

    // Don't forget to free the allocated memory when you are done
    struct ListNode* current = myLinkedList;
    while (current != NULL) {
        struct ListNode* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
// bool hasCycle(struct ListNode *head)
// struct ListNode *detectCycle(struct ListNode *head): cycle이 시작되는 가장 빠른 지점
// struct ListNode* reverseLinkedList(struct ListNode* head)
// struct ListNode* copyReverseLinkedList(struct ListNode* head) {
// void printList(struct ListNode* head) {
// void freeList(struct ListNode* head) 
// bool isPalindrome(struct ListNode* head)
// struct ListNode* getMiddleNode(struct ListNode* head) : 홀수면 중간, 짝수면 2번째 중간 노드 반환
// // struct ListNode* removeElements(struct ListNode* head, int val) : Function to remove elements from the linked list
// ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
// int get_length(struct ListNode* head) {
// 모든 substring
// 모든 subsequence
// struct ListNode* stringToLinkedList(const char* str) : 문자열을 받아서 링크드 리스트로 변환하는 함수
// char* linkedListToString(struct ListNode* head): 링크드 리스트를 받아서 문자열로 변환하는 함수

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Leetcode
// 817. Linked List Components
// 328. Odd Even Linked List
// 707. Design Linked List
// 92. Reverse Linked List II (left right 범위만 reverse)
// 86. Partition List (int x보다 작은 것을 앞으로 빼기)
// 203. Remove Linked List Elements (int x랑 같은 값을 가지는 노드는 삭제)

/////////////////////////////////////////////////////////////////////////////////////////////////////////

bool hasCycle(struct ListNode *head) {
    struct ListNode *slow_ptr = head;
    struct ListNode *fast_ptr = head;
    while (fast_ptr != NULL && fast_ptr->next != NULL){
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;
        if(slow_ptr == fast_ptr){
            return true;
        }
    }
    return false;
}

struct ListNode *detectCycle(struct ListNode *head) {
    
    // Initial Condition for for no node or no cycle
    if(head == NULL || head->next == NULL)return NULL;
    
    struct ListNode* slowptr = head;//Slow Pointer
    struct ListNode* fastptr = head;//Fast Pointer
    struct ListNode* entryptr = head; // entry location
    
    //Search of the loop cycle using fast pointer
    while(fastptr->next && fastptr->next->next){
        slowptr = slowptr->next;
        fastptr = fastptr->next->next;
        
        //Condition if cycle exist, if cycle exist then check the entry point of the cycle further
        if(slowptr == fastptr){
            
            //loop to check the entrypoint of the cycle, 
            //once found return the pointer to the entry point 
            while(slowptr != entryptr){
                slowptr = slowptr->next;
                entryptr = entryptr->next;
            }
            return entryptr;
        }
    }
    return NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Function to reverse a linked list
struct ListNode* reverseLinkedList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;
    
    while (curr) {
        struct ListNode* next_node = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_node;
    }
    
    return prev;
}

// Function to copy a linked list
struct ListNode* copyLinkedList(struct ListNode* head) {
    if (!head) {
        return NULL;
    }
    
    struct ListNode* new_head = (struct ListNode*)malloc(sizeof(struct ListNode));
    new_head->val = head->val;
    new_head->next = NULL;
    
    struct ListNode* current_old = head->next;
    struct ListNode* current_new = new_head;
    
    while (current_old) {
        current_new->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        current_new->next->val = current_old->val;
        current_new->next->next = NULL;
        
        current_old = current_old->next;
        current_new = current_new->next;
    }
    
    return new_head;
}

// Function to copy and reverse a linked list without modifying the original
struct ListNode* copyReverseLinkedList(struct ListNode* head) {
    struct ListNode* copied = copyLinkedList(head);
    struct ListNode* reversed = reverseLinkedList(copied);
    return reversed;
}

// Function to print a linked list
void printList(struct ListNode* head) {
    while (head) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

// Function to free the memory allocated for a linked list
void freeList(struct ListNode* head) {
    while (head) {
        struct ListNode* temp = head;
        head = head->next;
        free(temp);
    }
}

// Example usage
int main() {
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->val = 1;
    head->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->val = 2;
    head->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->next->val = 3;
    head->next->next->next = NULL;

    printf("Original Linked List: ");
    printList(head);

    struct ListNode* reversedCopy = copyReverseLinkedList(head);

    printf("Reversed Copied Linked List: ");
    printList(reversedCopy);

    // Free the memory allocated for the linked lists
    freeList(head);
    freeList(reversedCopy);

    return 0;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isPalindrome(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return true;  // An empty list or single-node list is considered a palindrome
    }

    // Find the middle of the linked list using the slow and fast pointer approach
    struct ListNode* slow = head;
    struct ListNode* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse the second half of the linked list
    struct ListNode* secondHalfReversed = reverseList(slow);

    // Compare the first half with the reversed second half
    while (secondHalfReversed != NULL) {
        if (head->val != secondHalfReversed->val) {
            // Clean up the reversed second half before returning
            reverseList(slow);
            return false;
        }

        head = head->next;
        secondHalfReversed = secondHalfReversed->next;
    }

    // Clean up the reversed second half before returning
    reverseList(slow);

    return true;
}
int main() {
    // Test case: 1 -> 2 -> 3 -> 2 -> 1
    int myArray[] = {1, 2, 3, 2, 1};
    int arraySize = sizeof(myArray) / sizeof(myArray[0]);

    struct ListNode* myLinkedList = createLinkedList(myArray, arraySize);

    printf("Original Linked List: ");
    printLinkedList(myLinkedList);

    if (isPalindrome(myLinkedList)) {
        printf("The linked list is a palindrome.\n");
    } else {
        printf("The linked list is not a palindrome.\n");
    }

    // Don't forget to free the allocated memory when you are done
    struct ListNode* current = myLinkedList;
    while (current != NULL) {
        struct ListNode* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

struct ListNode* getMiddleNode(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return head;
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while(fast!=NULL && fast->next!=NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Function to remove elements from the linked list
struct ListNode* removeElements(struct ListNode* head, int val) {
    // Create a sentinel node
    struct ListNode* sentinel = (struct ListNode*)malloc(sizeof(struct ListNode));
    sentinel->val = 0;
    sentinel->next = head;

    struct ListNode* p = sentinel;

    while (p) {
        if (p->next && p->next->val == val) {
            struct ListNode* temp = p->next;
            if (p->next->next) {
                p->next = p->next->next;
            } else {
                p->next = NULL;
            }
            free(temp);
        } else {
            p = p->next;
        }
    }

    // Get the new head (skip the sentinel node)
    struct ListNode* newHead = sentinel->next;
    
    // Free the sentinel node
    free(sentinel);

    return newHead;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
    struct ListNode* p1 = headA;
    struct ListNode* p2 = headB;

    while (p1 != p2) {
        p1 = (p1 ? p1->next : headB);
        p2 = (p2 ? p2->next : headA);
    }

    return p1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int get_length(struct ListNode* head) {
    struct ListNode* cursor = head;
    int output = 0;
    while (cursor) {
        output += 1;
        cursor = cursor->next;
    }
    return output;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 모든 substring
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

// Linked List에 새로운 노드를 추가하는 함수
void push(struct ListNode** head_ref, int new_val) {
    struct ListNode* new_node = (struct ListNode*)malloc(sizeof(struct ListNode));
    new_node->val = new_val;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// Linked List를 출력하는 함수
void printList(struct ListNode* node) {
    while (node != NULL) {
        printf("%c", node->val);
        node = node->next;
    }
    printf("\n");
}

// 주어진 Linked List로 문자열의 모든 부분 문자열을 생성하는 함수
char** getAllSubstrings(struct ListNode* head, int* count) {
    int length = 0;
    struct ListNode* current = head;

    // Linked List의 길이 계산
    while (current != NULL) {
        length++;
        current = current->next;
    }

    // 부분 문자열을 저장할 이중 포인터 동적 할당
    char** substrings = (char**)malloc((length * (length + 1) / 2) * sizeof(char*));
    *count = 0;

    struct ListNode* start = head;

    while (start != NULL) {
        struct ListNode* end = start;

        while (end != NULL) {
            // 현재 부분 문자열 저장
            int substringLength = end - start + 1;
            substrings[*count] = (char*)malloc((substringLength + 1) * sizeof(char));

            int index = 0;
            struct ListNode* current = start;
            while (current != end->next) {
                substrings[*count][index++] = current->val;
                current = current->next;
            }
            substrings[*count][index] = '\0';

            (*count)++;
            end = end->next;
        }

        start = start->next;
    }

    return substrings;
}

// 메모리 해제 함수
void freeSubstrings(char** substrings, int count) {
    for (int i = 0; i < count; i++) {
        free(substrings[i]);
    }
    free(substrings);
}

int main() {
    // Linked List 생성
    struct ListNode* head = NULL;
    push(&head, 'a');
    push(&head, 'b');
    push(&head, 'c');

    // 생성된 Linked List 출력
    printf("Linked List: ");
    printList(head);

    // Linked List로 문자열의 모든 부분 문자열을 얻어오기
    int count;
    char** substrings = getAllSubstrings(head, &count);

    // 부분 문자열 출력
    printf("\nAll Substrings:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", substrings[i]);
    }

    // 메모리 해제
    freeSubstrings(substrings, count);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 모든 subsequence
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

// Linked List에 새로운 노드를 추가하는 함수
void push(struct ListNode** head_ref, int new_val) {
    struct ListNode* new_node = (struct ListNode*)malloc(sizeof(struct ListNode));
    new_node->val = new_val;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// Linked List를 출력하는 함수
void printList(struct ListNode* node) {
    while (node != NULL) {
        printf("%c", node->val);
        node = node->next;
    }
    printf("\n");
}

// 문자열의 부분 수열을 생성하는 재귀 함수
void generateSubsequences(struct ListNode* current, char* subsequence, int index) {
    // 현재 노드가 NULL이면 재귀 종료
    if (current == NULL) {
        subsequence[index] = '\0';  // 부분 수열 끝에 null 문자 추가
        printf("%s\n", subsequence);  // 부분 수열 출력
        return;
    }

    // 현재 노드를 부분 수열에 추가하고 다음 노드로 재귀 호출
    subsequence[index] = current->val;
    generateSubsequences(current->next, subsequence, index + 1);

    // 현재 노드를 부분 수열에서 제외하고 다음 노드로 재귀 호출
    generateSubsequences(current->next, subsequence, index);
}

// 주어진 Linked List로 문자열의 모든 부분 수열을 생성하는 함수
void getAllSubsequences(struct ListNode* head) {
    int length = 0;
    struct ListNode* current = head;

    // Linked List의 길이 계산
    while (current != NULL) {
        length++;
        current = current->next;
    }

    // 부분 수열을 저장할 배열 생성
    char* subsequence = (char*)malloc((length + 1) * sizeof(char));

    // 재귀 함수 호출
    generateSubsequences(head, subsequence, 0);

    // 메모리 해제
    free(subsequence);
}

int main() {
    // Linked List 생성
    struct ListNode* head = NULL;
    push(&head, 'a');
    push(&head, 'b');
    push(&head, 'c');

    // 생성된 Linked List 출력
    printf("Linked List: ");
    printList(head);

    // Linked List로 문자열의 모든 부분 수열을 출력
    printf("\nAll Subsequences:\n");
    getAllSubsequences(head);

    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 문자열을 받아서 링크드 리스트로 변환하는 함수
struct ListNode {
    char val;
    struct LinkedNode* next;
};

struct ListNode* stringToLinkedList(const char* str) {
    if (str == NULL || *str == '\0') {
        return NULL; // 빈 문자열이거나 NULL인 경우, 빈 링크드 리스트 반환
    }

    struct ListNode* head = NULL;
    struct ListNode* current = NULL;

    while (*str != '\0') {
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = *str;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            current = head;
        } else {
            current->next = newNode;
            current = current->next;
        }

        str++;
    }

    return head;
}

// 링크드 리스트를 출력하는 함수
void printList(struct ListNode* node) {
    while (node != NULL) {
        printf("%c", node->val);
        node = node->next;
    }
    printf("\n");
}

// 링크드 리스트를 해제하는 함수
void freeLinkedList(struct ListNode* head) {
    struct ListNode* current = head;
    struct ListNode* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    const char* inputString = "abcd";

    // 문자열을 링크드 리스트로 변환
    struct ListNode* linkedList = stringToLinkedList(inputString);

    // 링크드 리스트 출력
    printf("Linked List: ");
    printList(linkedList);

    // 메모리 해제
    freeLinkedList(linkedList);

    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ListNode {
    char val;
    struct LinkedNode* next;
};

// 링크드 리스트를 받아서 문자열로 변환하는 함수
char* linkedListToString(struct ListNode* head) {
    if (head == NULL) {
        return NULL; // 빈 링크드 리스트인 경우, NULL 반환
    }

    // 문자열을 저장할 동적 할당된 배열 생성
    int length = 0;
    struct ListNode* current = head;

    while (current != NULL) {
        length++;
        current = current->next;
    }

    char* resultString = (char*)malloc((length + 1) * sizeof(char));
    current = head;
    int index = 0;

    // 링크드 리스트의 각 노드의 값을 배열에 복사
    while (current != NULL) {
        resultString[index++] = current->val;
        current = current->next;
    }

    resultString[index] = '\0'; // 문자열 끝에 null 문자 추가

    return resultString;
}

// 링크드 리스트를 출력하는 함수
void printList(struct ListNode* node) {
    while (node != NULL) {
        printf("%c", node->val);
        node = node->next;
    }
    printf("\n");
}

// 링크드 리스트를 해제하는 함수
void freeLinkedList(struct ListNode* head) {
    struct ListNode* current = head;
    struct ListNode* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    // 링크드 리스트 생성
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->val = 'a';
    head->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->val = 'b';
    head->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->next->next->val = 'c';
    head->next->next->next = NULL;

    // 링크드 리스트 출력
    printf("Linked List: ");
    printList(head);

    // 링크드 리스트를 문자열로 변환
    char* resultString = linkedListToString(head);

    // 변환된 문자열 출력
    printf("Result String: %s\n", resultString);

    // 메모리 해제
    free(resultString);
    freeLinkedList(head);

    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 817. Linked List Components
// You are given the head of a linked list containing unique integer values and an integer array nums that is a subset of the linked list values.
// Return the number of connected components in nums where two values are connected if they appear consecutively in the linked list.
// Example 1:
// Input: head = [0,1,2,3], nums = [0,1,3]
// Output: 2
// Explanation: 0 and 1 are connected, so [0, 1] and [3] are the two connected components.

// Example 2:
// Input: head = [0,1,2,3,4], nums = [0,3,1,4]
// Output: 2
// Explanation: 0 and 1 are connected, 3 and 4 are connected, so [0, 1] and [3, 4] are the two connected components.
 
int numComponents(struct ListNode* head, int* nums, int numsSize) {
    int c[1000000]={0};
    for (int i=0;i<numsSize;i++) c[nums[i]]+=1;

    struct ListNode* cur = head;
    int cnt=0;
    while (cur!=NULL){
        if (c[cur->val]==1){
            while(cur!=NULL&&c[cur->val]==1){cur=cur->next;}
            cnt++;
        }
        else cur = cur->next;
    }
    return cnt;
}

//////////////////////////////////////////////////////////////////////////////////////

// 328. Odd Even Linked List

// Given the head of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return the reordered list.

// The first node is considered odd, and the second node is even, and so on.

// Note that the relative order inside both the even and odd groups should remain as it was in the input.

// You must solve the problem in O(1) extra space complexity and O(n) time complexity.

// Example 1:
// Input: head = [1,2,3,4,5]
// Output: [1,3,5,2,4]

// Example 2:
// Input: head = [2,1,3,5,6,4,7]
// Output: [2,3,6,7,1,5,4]
struct ListNode* oddEvenList(struct ListNode* head) {
    if (head == NULL || head->next == NULL)
        return head;

    struct ListNode* odd_ptr = head;
    struct ListNode* even_ptr = head->next;
    struct ListNode* even_head = even_ptr;

    while (even_ptr != NULL && even_ptr->next != NULL) {
        odd_ptr->next = even_ptr->next;
        odd_ptr = odd_ptr->next;

        even_ptr->next = odd_ptr->next;
        even_ptr = even_ptr->next;
    }

    odd_ptr->next = even_head;

    return head;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 92. Reverse Linked List II
// Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.

// Example 1:
// Input: head = [1,2,3,4,5], left = 2, right = 4
// Output: [1,4,3,2,5]

// Example 2:
// Input: head = [5], left = 1, right = 1
// Output: [5]

struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
    struct ListNode* cur = head;
    struct ListNode* prev = NULL;
    struct ListNode* next = NULL;

    // 이 부분에서 left-2로 설정하면서 left-1 번째 노드까지 이동하려고 했으나,
    // left가 1일 때는 cur가 head를 가리켜야 하므로 left-1이 아닌 left-2로 설정하면 안 됩니다.
    for (int i = 0; i < left - 1; i++) {
        prev = cur;
        cur = cur->next;
    }

    struct ListNode* left_ptr = cur;  // left 번째 노드를 가리킴
    struct ListNode* tail = prev;     // left-1 번째 노드를 가리킴

    // 이 부분에서 right-left+1로 설정하여 뒤집어야 하는 노드들의 개수를 구합니다.
    for (int j = 0; j < right - left + 1; j++) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    // 뒤집힌 부분의 첫 번째 노드와 마지막 노드를 연결합니다.
    if (tail != NULL) {
        tail->next = prev;
    } else {
        head = prev;
    }

    left_ptr->next = cur;

    return head;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 86. Partition List
// Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
// You should preserve the original relative order of the nodes in each of the two partitions.


// Example 1:
// Input: head = [1,4,3,2,5,2], x = 3
// Output: [1,2,2,4,3,5]

// Example 2:
// Input: head = [2,1], x = 2
// Output: [1,2]

struct ListNode* partition(struct ListNode* head, int x) {
    // 두 그룹의 시작을 나타낼 더미 노드를 생성합니다.
    struct ListNode less_dummy;
    struct ListNode greater_dummy;
    
    struct ListNode* less = &less_dummy;
    struct ListNode* greater = &greater_dummy;

    struct ListNode* cur = head;

    while (cur != NULL) {
        if (cur->val < x) {
            // 현재 노드가 x보다 작으면 'less' 그룹에 추가
            less->next = cur;
            less = less->next;
        } else {
            // 현재 노드가 x 이상이면 'greater' 그룹에 추가
            greater->next = cur;
            greater = greater->next;
        }

        // 다음 노드로 이동
        cur = cur->next;
    }

    // 그룹의 끝을 NULL로 설정하여 연결 리스트의 끝을 표시
    greater->next = NULL;

    // 'less' 그룹의 끝을 'greater' 그룹의 시작에 연결하여 두 그룹을 합침
    less->next = greater_dummy.next;

    // 'less' 그룹의 시작인 더미 노드의 다음을 반환
    return less_dummy.next;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 707. Design Linked List

// Design your implementation of the linked list. You can choose to use a singly or doubly linked list.
// A node in a singly linked list should have two attributes: val and next. val is the value of the current node, and next is a pointer/reference to the next node.
// If you want to use the doubly linked list, you will need one more attribute prev to indicate the previous node in the linked list. Assume all nodes in the linked list are 0-indexed.

// Implement the MyLinkedList class:

// MyLinkedList() Initializes the MyLinkedList object.
// int get(int index) Get the value of the indexth node in the linked list. If the index is invalid, return -1.
// void addAtHead(int val) Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
// void addAtTail(int val) Append a node of value val as the last element of the linked list.
// void addAtIndex(int index, int val) Add a node of value val before the indexth node in the linked list. If index equals the length of the linked list, the node will be appended to the end of the linked list. If index is greater than the length, the node will not be inserted.
// void deleteAtIndex(int index) Delete the indexth node in the linked list, if the index is valid.



struct Node {
    int val;
    struct Node *next;
};

typedef struct MyLinkedList{
    struct Node *head;

} MyLinkedList;

//helper function to create nodes
struct Node *createNode(int val)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->val = val;
    return newNode;
}

//create list "object"
MyLinkedList* myLinkedListCreate() {
    MyLinkedList *obj = malloc(sizeof(MyLinkedList));
    obj->head = NULL;
    return obj;
}

int myLinkedListGet(MyLinkedList* obj, int index) {
    struct Node *current = obj->head;
    if(index == 0 && current)
        return current->val;
    else if(index == 0 && !current)
        return -1;
    else
    {
        for(int i = 0; i<index; i++)
        {
            if(current->next)
                current = current->next;
            else
                return -1;
        }
        return current->val;
    }
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    if(obj->head == NULL)
        obj->head = createNode(val);
    else
    {
        struct Node *temp = obj->head;
        obj->head = createNode(val);
        obj->head->next = temp;
    }
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    struct Node *current;

    //in case MyLinkedList is empty, add to head instead
    if(!obj->head)
        myLinkedListAddAtHead(obj,val);
    else
    {
        current = obj->head;
        //get to the last node
        while(current->next != NULL)
        {
            current = current->next;
        }
        //create node
        current->next = createNode(val);
    }
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    struct Node *current = obj->head;
    struct Node *temp;
    //in case user adds to head
    if(index == 0)
        myLinkedListAddAtHead(obj,val);

    //get to given index
    else if(index > 0 && current)
    {
        for(int i = 1;i<index;i++)
        {
            if(current->next)
                current = current->next;
            else
                return;
        }
        //hold next node's address in temp
        temp = current->next;
        //set current node's next to new node
        current->next = createNode(val);
        //step into new node
        current = current->next;
        //set new node's next pointer to the displaced node's address
        current->next = temp;
    }
    else
        return;
}

void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    struct Node *current = obj->head;
    struct Node *deleteNode;

    //handling the case that index points to head
   if(index == 0 && current->next)
    {
        obj->head = current->next;
        free(current);
    }
    else if(index == 0 && !current->next)
    {
        obj->head = NULL;
    }

    else if(current->next)
    {
        //get to given index
        for(int i = 1;i < index; i++)
        {
            //set current's address to the node right before
            // the node to be deleted
            //unless index doesn't exist
            if(current->next->next)
                current = current->next;
            else
                return;
        }
        //hold the address of the node to be deleted in deleteNode
        deleteNode = current->next;
        //remove the to-be-deleted node from the linked list chain
        current->next = deleteNode->next;
        //free the deleted node from the heap's memory
        free(deleteNode);
    }
}

void myLinkedListFree(MyLinkedList* obj) {
    struct Node *temp = obj->head;
    struct Node *next;
    //if there's more than just a head node
    if(temp && temp->next)
    {
        next = temp->next;
        //freeing head
        free(temp);
        while(next->next)
        {
            //set temp's pointer to next node in line
            temp = next;
            //iterate next
            next = next->next;
            //delete node
            free(temp);
        }
        //finally free tail from heap
        free(next);
    }
    else if(temp)
    {
        free(temp);
    }
    else
        return;
}


void display(MyLinkedList* obj)
{
    struct Node * current = obj->head;
    printf("Data in all linked list: ");
    if(obj->head == NULL)
    {
        printf("NULL\n");

    }
    while(current != NULL)
    {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);
 
 * myLinkedListAddAtHead(obj, val);
 
 * myLinkedListAddAtTail(obj, val);
 
 * myLinkedListAddAtIndex(obj, index, val);
 
 * myLinkedListDeleteAtIndex(obj, index);
 
 * myLinkedListFree(obj);
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////
// 203. Remove Linked List Elements
// Given the head of a linked list and an integer val, remove all the nodes of the linked list that has Node.val == val, and return the new head.

// Example 1:
// Input: head = [1,2,6,3,4,5,6], val = 6
// Output: [1,2,3,4,5]

// Example 2:
// Input: head = [], val = 1
// Output: []

// Example 3:
// Input: head = [7,7,7,7], val = 7
// Output: []


struct ListNode* removeElements(struct ListNode* head, int val) {
    // 헤드 노드가 NULL인 경우 예외 처리
    if (head == NULL) {
        return head;
    }

    // 헤드 노드부터 시작
    struct ListNode* cur = head;

    // 다음 노드가 NULL이 아닐 때까지 반복
    while (cur->next) {
        // 다음 노드의 값이 val과 같으면 해당 노드를 건너뛰고 다음 노드와 연결
        if (cur->next->val == val) {
            struct ListNode* temp = cur->next;
            cur->next = cur->next->next;
            free(temp);  // 해당 노드를 동적으로 할당된 메모리에서 해제
        } else {
            cur = cur->next;
        }
    }

    // 마지막 노드의 값이 val과 같으면 마지막 노드를 제거
    if (head->val == val) {
        struct ListNode* temp = head;
        head = head->next;
        
        free(temp);  // 헤드 노드를 동적으로 할당된 메모리에서 해제
    }

    return head;
}


