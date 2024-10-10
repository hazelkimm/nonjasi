// Node 구조체
// Node: 연결 리스트의 노드를 정의하는 구조체입니다. 각 노드는 데이터(data)와 다음 노드를 가리키는 포인터(next)를 가집니다.
// create_linked_list_from_list
// 기능: 배열을 받아 연결 리스트로 변환합니다.
// Input: values[] (int 배열), size (int)
// Output: Node* (연결 리스트의 head)

// print_linked_list
// 기능: 연결 리스트의 모든 노드를 출력합니다.
// Input: head (Node*)
// Output: 없음

// copy_linked_list
// 기능: 주어진 연결 리스트를 복사하여 반환합니다.
// Input: head (Node*)
// Output: Node* (복사된 연결 리스트의 head)

// insert_at_index
// 기능: 연결 리스트의 특정 인덱스에 새 노드를 삽입합니다.
// Input: head (Node*), index (int), data (int)
// Output: Node* (새로운 연결 리스트의 head)

// delete_at_index
// 기능: 연결 리스트의 특정 인덱스의 노드를 삭제합니다.
// Input: head (Node*), index (int)
// Output: Node* (새로운 연결 리스트의 head)

// delete_value
// 기능: 연결 리스트에서 특정 값을 가진 첫 번째 노드를 삭제합니다.
// Input: head (Node*), data (int), success (int*)
// Output: Node* (새로운 연결 리스트의 head), success (삭제 성공 여부)

// find
// 기능: 연결 리스트에서 특정 값이 위치한 인덱스를 반환합니다.
// Input: head (Node*), data (int)
// Output: int (값의 인덱스, 없을 경우 -1)

// swap_nodes
// 기능: 연결 리스트에서 주어진 인덱스의 두 노드를 교환합니다.
// Input: head (Node*), index1 (int), index2 (int)
// Output: Node* (새로운 연결 리스트의 head)

// length
// 기능: 연결 리스트의 길이를 반환합니다.
// Input: head (Node*)
// Output: int (리스트의 길이)

// contains
// 기능: 연결 리스트에 특정 값이 있는지 확인합니다.
// Input: head (Node*), data (int)
// Output: int (1: 값 존재, 0: 값 없음)

// is_substring
// 기능: 주어진 target 리스트가 search 리스트의 서브스트링인지 확인합니다.
// Input: search (Node*), target (Node*)
// Output: int (1: 서브스트링, 0: 서브스트링 아님)

// nth_from_end
// 기능: 리스트의 끝에서 n번째 노드를 반환합니다.
// Input: head (Node*), n (int)
// Output: Node* (n번째 노드)

// get_middle
// 기능: 연결 리스트의 중간 노드를 반환합니다.
// Input: head (Node*)
// Output: Node* (중간 노드)

// reverse
// 기능: 연결 리스트를 역순으로 변환합니다.
// Input: head (Node*)
// Output: Node* (역순으로 된 연결 리스트의 head)

//void reverseSublist(Node** head, int start_idx, int end_idx)

// reverse_k_nodes
// 기능: 연결 리스트의 처음부터 k개의 노드를 역순으로 변환하고, 다음 그룹의 시작점을 반환합니다.
// Input: start (Node*), k (int), next_group_start (Node**)
// Output: Node* (역순으로 된 그룹의 새로운 시작 노드)

// reverse_in_groups
// 기능: 연결 리스트를 k개의 그룹으로 나누어 역순으로 변환합니다.
// Input: head (Node*), k (int)
// Output: Node* (변환된 연결 리스트의 head)

// remove_duplicates
// 기능: 정렬된 연결 리스트에서 중복된 노드를 제거합니다.
// Input: head (Node*)
// Output: Node* (중복이 제거된 연결 리스트의 head)

// pop_last
// 기능: 리스트의 마지막 노드를 제거하고, 해당 노드의 데이터를 반환합니다.
// Input: head (Node*), data (int*)
// Output: Node* (새로운 연결 리스트의 head)

// slice_range
// 기능: 주어진 인덱스 범위의 노드를 복사하여 새로운 연결 리스트로 반환합니다.
// Input: head (Node*), start (int), end (int)
// Output: Node* (새로운 연결 리스트의 head)

// bubble_sort
// 기능: 버블 정렬을 사용하여 연결 리스트를 정렬합니다.
// Input: head (Node*)
// Output: Node* (정렬된 연결 리스트의 head)

// insertion_sort
// 기능: 삽입 정렬을 사용하여 연결 리스트를 정렬합니다.
// Input: head (Node*)
// Output: Node* (정렬된 연결 리스트의 head)

// sorted_insert
// 기능: 정렬된 연결 리스트에 새로운 노드를 삽입합니다.
// Input: sorted_head (Node*), new_node (Node*)
// Output: Node* (새로운 연결 리스트의 head)

// selection_sort
// 기능: 선택 정렬을 사용하여 연결 리스트를 정렬합니다.
// Input: head (Node*)
// Output: Node* (정렬된 연결 리스트의 head)

// merge_sort
// 기능: 병합 정렬을 사용하여 연결 리스트를 정렬합니다.
// Input: head (Node*)
// Output: Node* (정렬된 연결 리스트의 head)

// sorted_merge
// 기능: 두 개의 정렬된 연결 리스트를 병합합니다.
// Input: left (Node*), right (Node*)
// Output: Node* (병합된 연결 리스트의 head)

// detect_cycle
// 기능: 연결 리스트에 사이클이 있는지 확인합니다.
// Input: head (Node*)
// Output: int (1: 사이클 있음, 0: 사이클 없음)

// remove_cycle
// 기능: 연결 리스트에서 사이클을 제거합니다.
// Input: head (Node*)
// Output: Node* (사이클이 제거된 연결 리스트의 head)

// append_list
// 기능: 두 개의 연결 리스트를 연결합니다.
// Input: head1 (Node*), head2 (Node*)
// Output: Node* (결합된 연결 리스555의 head)

// sorted_insert_in_sorted_list
// 기능: 정렬된 연결 리스트에 새로운 노드를 정렬된 상태로 삽입합니다.
// Input: head (Node*), data (int)
// Output: Node* (새로운 연결 리스트의 head)

// get_all_substrings
// 기능: 연결 리스트의 모든 서브스트링을 생성하여 반환합니다.
// Input: head (Node*), count (int*)
// Output: Node** (서브스트링을 담은 연결 리스트들의 배열), count (서브스트링의 개수)

// get_all_subsequences
// 기능: 연결 리스트의 모든 부분수열을 생성하여 반환합니다.
// Input: head (Node*), count (int*)
// Output: Node** (부분수열을 담은 연결 리스트들의 배열), count (부분수열의 개수)

// get_combinations
// 기능: 연결 리스트의 모든 조합을 생성하여 반환합니다.
// Input: head (Node*), count (int*)
// Output: Node** (조합을 담은 연결 리스트들의 배열), count (조합의 개수)

// permute_linked_list
// 기능: 연결 리스트의 모든 순열을 생성하여 반환합니다.
// Input: head (Node*), count (int*)
// Output: Node** (순열을 담은 연결 리스트들의 배열), count (순열의 개수)

// find_peaks
// 기능: 연결 리스트에서 피크 요소를 찾아 리스트로 반환합니다
// Input: head (Node*), count (int*)
// Output: Node* (피크 요소들의 리스트), count (피크 요소의 개수)


#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;


Node* create_linked_list_from_list(int values[], int size) {
    if (size == 0) {
        return NULL;
    }
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = values[0];
    head->next = NULL;
    Node* current = head;
    for (int i = 1; i < size; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = values[i];
        new_node->next = NULL;
        current->next = new_node;
        current = new_node;
    }
    return head;
}

void print_linked_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}


Node* copy_linked_list(Node* head) {
    if (head == NULL) {
        return NULL;
    }
    Node* new_head = (Node*)malloc(sizeof(Node));
    new_head->data = head->data;
    new_head->next = NULL;
    Node* current = head->next;
    Node* new_current = new_head;
    while (current != NULL) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = current->data;
        new_node->next = NULL;
        new_current->next = new_node;
        new_current = new_node;
        current = current->next;
    }
    return new_head;
}

Node* insert_at_index(Node* head, int index, int data) {
    if (index < 0) {
        return head;  // Handle index out of bounds
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    if (index == 0) {
        new_node->next = head;
        return new_node;
    }
    Node* current = head;
    for (int i = 0; i < index - 1; i++) {
        if (current == NULL) {
            free(new_node);
            return head;  // Index out of bounds
        }
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    return head;
}

void insert_at_index(Node** head_ref, int index, int data) {
    if (index < 0) {
        return;  // Handle index out of bounds
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;

    if (index == 0) {
        new_node->next = *head_ref;
        *head_ref = new_node;
        return;
    }

    Node* current = *head_ref;
    for (int i = 0; i < index - 1; i++) {
        if (current == NULL) {
            free(new_node);  // Index out of bounds
            return;
        }
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

Node* delete_at_index(Node* head, int index) {
    if (index < 0 || head == NULL) {
        return head;  // Handle index out of bounds or empty list
    }
    if (index == 0) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    Node* current = head;
    for (int i = 0; i < index - 1; i++) {
        if (current->next == NULL) {
            return head;  // Index out of bounds
        }
        current = current->next;
    }
    Node* temp = current->next;
    if (temp != NULL) {
        current->next = temp->next;
        free(temp);
    }
    return head;
}

//  // 값 3을 가진 노드 삭제
//     delete_value(&head, 3);
void delete_at_index(Node** head_ref, int index) {
    if (index < 0 || *head_ref == NULL) {
        return;  // Handle index out of bounds or empty list
    }

    Node* current = *head_ref;

    if (index == 0) {
        *head_ref = current->next;  // Update head to the next node
        free(current);
        return;
    }

    for (int i = 0; current != NULL && i < index - 1; i++) {
        current = current->next;
    }

    if (current == NULL || current->next == NULL) {
        return;  // Index out of bounds
    }

    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
}


Node* delete_value(Node* head, int data, int* success) {
    *success = 0;
    Node* current = head;
    Node* prev = NULL;
    while (current != NULL) {
        if (current->data == data) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            free(current);
            *success = 1;
            return head;
        }
        prev = current;
        current = current->next;
    }
    return head;
}


//  // 값 3을 가진 노드 삭제
//     delete_value(&head, 3);
void delete_value(Node** head_ref, int data) {
    Node* current = *head_ref;  // 현재 노드를 가리키는 포인터
    Node* prev = NULL;  // 이전 노드를 가리키는 포인터

    while (current != NULL) {
        if (current->data == data) {
            // 삭제할 노드가 헤드인 경우
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                *head_ref = current->next;
            }
            free(current);  // 노드 삭제
            return;
        }
        prev = current;
        current = current->next;
    }
}


int find(Node* head, int data) {
    Node* current = head;
    int index = 0;
    while (current != NULL) {
        if (current->data == data) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

Node* swap_nodes(Node* head, int index1, int index2) {
    if (index1 == index2) {
        return head;
    }
    if (index1 > index2) {
        int temp = index1;
        index1 = index2;
        index2 = temp;
    }
    Node* prev1 = NULL;
    Node* curr1 = head;
    Node* prev2 = NULL;
    Node* curr2 = head;
    for (int i = 0; i < index1; i++) {
        prev1 = curr1;
        curr1 = curr1->next;
    }
    for (int i = 0; i < index2; i++) {
        prev2 = curr2;
        curr2 = curr2->next;
    }
    if (prev1 != NULL) {
        prev1->next = curr2;
    } else {
        head = curr2;
    }
    if (prev2 != NULL) {
        prev2->next = curr1;
    } else {
        head = curr1;
    }
    Node* temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;
    return head;
}

void swap_nodes(Node** head_ref, int index1, int index2) {
    if (index1 == index2) {
        return;
    }

    // Ensure index1 is less than index2 for simplicity
    if (index1 > index2) {
        int temp = index1;
        index1 = index2;
        index2 = temp;
    }

    Node* prev1 = NULL;
    Node* curr1 = *head_ref;
    Node* prev2 = NULL;
    Node* curr2 = *head_ref;

    // Traverse the list to find the nodes at index1 and index2
    for (int i = 0; i < index1; i++) {
        prev1 = curr1;
        curr1 = curr1->next;
    }
    for (int i = 0; i < index2; i++) {
        prev2 = curr2;
        curr2 = curr2->next;
    }

    // If either node doesn't exist, return (index out of bounds)
    if (curr1 == NULL || curr2 == NULL) {
        return;
    }

    // If curr1 is not the head of the list
    if (prev1 != NULL) {
        prev1->next = curr2;
    } else {
        *head_ref = curr2;
    }

    // If curr2 is not the head of the list
    if (prev2 != NULL) {
        prev2->next = curr1;
    } else {
        *head_ref = curr1;
    }

    // Swap the next pointers of curr1 and curr2
    Node* temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;
}



// Function to swap two nodes in the linked list
void swap_nodes(Node** head_ref, Node* node1, Node* node2) {
    if (node1 == node2) {
        return;  // No need to swap if both nodes are the same
    }

    Node* prev1 = NULL, * prev2 = NULL, * current = *head_ref;

    // Find the previous nodes of node1 and node2
    while (current != NULL && (prev1 == NULL || prev2 == NULL)) {
        if (current->next == node1) {
            prev1 = current;
        } else if (current->next == node2) {
            prev2 = current;
        }
        current = current->next;
    }

    // Swap node1 and node2 by adjusting pointers
    if (prev1 != NULL) {
        prev1->next = node2;
    } else {
        *head_ref = node2;
    }

    if (prev2 != NULL) {
        prev2->next = node1;
    } else {
        *head_ref = node1;
    }

    // Swap next pointers of node1 and node2
    Node* temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;
}





int length(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int contains(Node* head, int data) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == data) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}


/////////////////////////////////////////////////////////////////////
// 여기가 문제///////////////////
////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

int is_substring(Node* search, Node* target) {
    while (search != NULL) {
        Node* search_dummy = search;
        Node* cur = target;
        while (cur != NULL && search_dummy != NULL) {
            if (search_dummy->data != cur->data) {
                break;
            }
            search_dummy = search_dummy->next;
            cur = cur->next;
        }
        if (cur == NULL) {
            return 1;
        }
        search = search->next;
    }
    return 0;
}


Node* nth_from_end(Node* head, int n) {
    int total_length = length(head);
    if (n > total_length || n <= 0) {
        return NULL;
    }
    Node* current = head;
    for (int i = 0; i < total_length - n; i++) {
        current = current->next;
    }
    return current;
}


Node* get_middle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}


Node* reverse(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    while (current != NULL) {
        Node* next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;
    }
    return prev;
}
void reverse(Node** head_ref) {
    Node* prev = NULL;
    Node* current = *head_ref;
    while (current != NULL) {
        Node* next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;
    }
    *head_ref = prev;  // 역순 후 새로운 head 설정
}


void reverseSublist(Node** head, int start_idx, int end_idx) {
    if (start_idx >= end_idx || *head == NULL) {
        return;  // No need to reverse if the indices are invalid or the list is empty
    }

    Node* current = *head;
    Node* prev = NULL;
    int idx = 0;

    // Traverse the list to find the start of the sublist
    while (current != NULL && idx < start_idx) {
        prev = current;
        current = current->next;
        idx++;
    }

    // Mark the start of the sublist and the node before it
    Node* sublist_start_prev = prev;
    Node* sublist_start = current;

    // Reverse the sublist between start_idx and end_idx
    Node* next_node = NULL;
    while (current != NULL && idx <= end_idx) {
        next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;
        idx++;
    }

    // Connect the reversed sublist back to the main list
    if (sublist_start_prev != NULL) {
        sublist_start_prev->next = prev;
    } else {
        *head = prev;  // If reversing from the head, update the head pointer
    }

    sublist_start->next = current;  // Connect the end of the reversed sublist to the remaining list
}

Node* reverse_k_nodes(Node* start, int k, Node** next_group_start) {
    Node* prev = NULL;
    Node* current = start;
    int count = 0;
    while (current != NULL && count < k) {
        Node* next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;
        count++;
    }
    *next_group_start = current;  // 다음 그룹의 시작점을 반환하기 위해 포인터 사용
    return prev;  // prev는 역순으로 된 그룹의 새로운 시작 노드
}

Node* reverse_in_groups(Node* head, int k) {
    if (head == NULL || k <= 1) {
        return head;  // 잘못된 입력 처리
    }

    Node* new_head = NULL;
    Node* prev_end = NULL;
    Node* current = head;

    while (current != NULL) {
        Node* group_start = current;
        Node* next_group_start = NULL;

        // 현재 그룹을 역순으로 변경
        Node* new_start = reverse_k_nodes(group_start, k, &next_group_start);

        // 새로운 head 설정 (첫 번째 그룹일 때)
        if (new_head == NULL) {
            new_head = new_start;
        }

        // 이전 그룹의 끝을 현재 그룹의 시작과 연결
        if (prev_end != NULL) {
            prev_end->next = new_start;
        }

        // 현재 그룹의 끝을 다음 그룹의 시작과 연결
        prev_end = group_start;
        current = next_group_start;
    }

    return new_head;
}




Node* remove_duplicates(Node* head) {
    Node* current = head;
    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
    return head;
}


Node* pop_last(Node* head, int* data) {
    if (head == NULL) {
        return NULL;
    }
    if (head->next == NULL) {
        *data = head->data;
        free(head);
        return NULL;
    }
    Node* current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    *data = current->next->data;
    free(current->next);
    current->next = NULL;
    return head;
}


Node* slice_range(Node* head, int start, int end) {
    if (start < 0 || end < start) {
        return NULL;
    }

    Node* current = head;
    for (int i = 0; i < start; i++) {
        if (current == NULL) {
            return NULL;  // Start index out of range
        }
        current = current->next;
    }

    Node* new_head = NULL;
    Node* new_tail = NULL;
    for (int i = start; i <= end; i++) {  // Changed to `<= end` to include the `end` index
        if (current == NULL) {
            break;
        }
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = current->data;
        new_node->next = NULL;
        if (new_head == NULL) {
            new_head = new_tail = new_node;
        } else {
            new_tail->next = new_node;
            new_tail = new_tail->next;
        }
        current = current->next;
    }

    return new_head;
}

Node* bubble_sort(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    int swapped;
    do {
        swapped = 0;
        Node* current = head;
        while (current->next != NULL) {
            if (current->data > current->next->data) {
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);

    return head;
}

// Function to perform in-place bubble sort on a linked list
void bubble_sort(Node* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }

    int swapped;
    Node* current;
    Node* last_unsorted = NULL;

    do {
        swapped = 0;
        current = head;

        while (current->next != last_unsorted) {
            if (current->data > current->next->data) {
                // Swap the data of current node and next node
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }

        last_unsorted = current; // Mark the last sorted element

    } while (swapped);
}
////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
Node* sorted_insert(Node* sorted_head, Node* new_node) {
    if (sorted_head == NULL || new_node->data < sorted_head->data) {
        new_node->next = sorted_head;
        return new_node;
    }

    Node* current = sorted_head;
    while (current->next != NULL && current->next->data < new_node->data) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
    return sorted_head;
}

Node* insertion_sort(Node* head) {
    Node* sorted_head = NULL;
    Node* current = head;
    while (current != NULL) {
        Node* next_node = current->next;
        sorted_head = sorted_insert(sorted_head, current);
        current = next_node;
    }
    return sorted_head;
}


////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
// Helper function to insert a node into the sorted part of the list
void sorted_insert(Node** sorted_ref, Node* new_node) {
    if (*sorted_ref == NULL || new_node->data < (*sorted_ref)->data) {
        new_node->next = *sorted_ref;
        *sorted_ref = new_node;
    } else {
        Node* current = *sorted_ref;
        while (current->next != NULL && current->next->data < new_node->data) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}
// Function to perform in-place insertion sort on a linked list
void insertion_sort(Node** head_ref) {
    if (*head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }

    Node* sorted = NULL;
    Node* current = *head_ref;

    while (current != NULL) {
        Node* next_node = current->next;
        sorted_insert(&sorted, current);
        current = next_node;
    }

    *head_ref = sorted;  // Update head_ref to point to the sorted list
}




////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

Node* selection_sort(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* min_node = current;
        Node* next_node = current->next;
        while (next_node != NULL) {
            if (next_node->data < min_node->data) {
                min_node = next_node;
            }
            next_node = next_node->next;
        }

        int temp = current->data;
        current->data = min_node->data;
        min_node->data = temp;

        current = current->next;
    }
    return head;
}


// 여기서 swapNodes는 idx가 아닌 node를 인풋으로 받음
void selection_sort(Node** head_ref) {
    Node* current = *head_ref;
    while (current != NULL) {
        Node* min_node = current;
        Node* next_node = current->next;

        // Find the node with the smallest data value in the unsorted portion
        while (next_node != NULL) {
            if (next_node->data < min_node->data) {
                min_node = next_node;
            }
            next_node = next_node->next;
        }

        // Swap the current node with the minimum node found
        if (min_node != current) {
            swap_nodes(head_ref, current, min_node);
        }

        // Move to the next node in the unsorted portion
        current = current->next;
    }
}


///////////////////////////////////////////////////////////////////////////



Node* merge_sort(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node* middle = get_middle(head);
    Node* next_to_middle = middle->next;
    middle->next = NULL;

    Node* left = merge_sort(head);
    Node* right = merge_sort(next_to_middle);

    return sorted_merge(left, right);
}

Node* sorted_merge(Node* left, Node* right) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    if (left->data <= right->data) {
        left->next = sorted_merge(left->next, right);
        return left;
    } else {
        right->next = sorted_merge(left, right->next);
        return right;
    }
}
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

// Function to merge two sorted linked lists
Node* sorted_merge(Node* left, Node* right) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    if (left->data <= right->data) {
        left->next = sorted_merge(left->next, right);
        return left;
    } else {
        right->next = sorted_merge(left, right->next);
        return right;
    }
}

// Function to perform in-place merge sort on a linked list
Node* merge_sort(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Find the middle of the list
    Node* middle = get_middle(head);
    Node* next_to_middle = middle->next;

    // Split the list into two halves
    middle->next = NULL;

    // Recursively sort the two halves
    Node* left = merge_sort(head);
    Node* right = merge_sort(next_to_middle);

    // Merge the sorted halves
    return sorted_merge(left, right);
}
///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


int detect_cycle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return 1;
        }
    }
    return 0;
}

void remove_cycle(Node* head) {
    Node* slow = head;
    Node* fast = head;

    // 사이클 감지 단계
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;  // 사이클 감지
        }
    }

    // 사이클이 없을 경우
    if (fast == NULL || fast->next == NULL) {
        return;  // 리스트에 사이클이 없음
    }

    // 사이클의 시작점 찾기
    slow = head;
    while (slow->next != fast->next) {
        slow = slow->next;
        fast = fast->next;
    }

    // 사이클 제거
    fast->next = NULL;
}


void append_list(Node* head1, Node* head2) {
    if (head1 == NULL) {
        head1 = head2;  // If head1 is NULL, make head1 point to head2
        return;
    }
    if (head2 == NULL) {
        return;  // If head2 is NULL, no need to do anything
    }

    Node* current = head1;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = head2;
}


// Function to insert a new node into a sorted linked list in place
void sorted_insert_in_sorted_list(Node** head_ref, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    // If the list is empty or the new node should be the new head
    if (*head_ref == NULL || data < (*head_ref)->data) {
        new_node->next = *head_ref;
        *head_ref = new_node;
        return;
    }

    Node* current = *head_ref;
    while (current->next != NULL && current->next->data < data) {
        current = current->next;
    }

    // Insert the new node in its proper place
    new_node->next = current->next;
    current->next = new_node;
}


Node** get_all_substrings(Node* head, int* count) {
    int len = length(head);
    int substr_count = 0;
    Node** substrings = NULL;

    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            Node* sub = slice_range(head, i, j);
            substrings = (Node**)realloc(substrings, sizeof(Node*) * (substr_count + 1));
            substrings[substr_count] = sub;
            substr_count++;
        }
    }

    *count = substr_count;  // Update count
    return substrings;
}

// Recursive function to generate all subsequences of the linked list
void generate_subsequences(Node* current, int* path, int path_len, Node*** subsequences, int* count) {
    if (current == NULL) {
        // Create a new subsequence from the path array
        Node* subsequence_head = NULL;
        Node* subsequence_tail = NULL;

        for (int i = 0; i < path_len; i++) {
            Node* new_node = createNode(path[i]);

            if (subsequence_head == NULL) {
                subsequence_head = subsequence_tail = new_node;
            } else {
                subsequence_tail->next = new_node;
                subsequence_tail = new_node;
            }
        }

        // Add the new subsequence to the subsequences array
        *subsequences = (Node**)realloc(*subsequences, sizeof(Node*) * (*count + 1));
        (*subsequences)[(*count)++] = subsequence_head;
        return;
    }

    // Recur without including the current node
    generate_subsequences(current->next, path, path_len, subsequences, count);

    // Include the current node in the path and recur
    path[path_len] = current->data;
    generate_subsequences(current->next, path, path_len + 1, subsequences, count);
}

// Function to get all subsequences of the linked list
Node** get_all_subsequences(Node* head, int* count) {
    Node** subsequences = NULL;
    int subseq_count = 0;
    int len = length(head);
    int* path = (int*)malloc(sizeof(int) * len);

    // Generate all subsequences
    generate_subsequences(head, path, 0, &subsequences, &subseq_count);

    free(path);
    *count = subseq_count;
    return subsequences;
}



// Recursive function to generate all combinations of the linked list
void combine(Node* node, int* chosen, int chosen_len, Node*** results, int* count) {
    if (node == NULL) {
        Node* combination_head = NULL;
        Node* combination_tail = NULL;

        for (int i = 0; i < chosen_len; i++) {
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->data = chosen[i];
            new_node->next = NULL;

            if (combination_head == NULL) {
                combination_head = combination_tail = new_node;
            } else {
                combination_tail->next = new_node;
                combination_tail = new_node;
            }
        }

        *results = (Node**)realloc(*results, sizeof(Node*) * (*count + 1));
        (*results)[(*count)++] = combination_head;
        return;
    }

    combine(node->next, chosen, chosen_len, results, count);

    chosen[chosen_len] = node->data;
    combine(node->next, chosen, chosen_len + 1, results, count);
}

// Function to get all combinations of the linked list
Node** get_combinations(Node* head, int* count) {
    Node** results = NULL;
    int result_count = 0;
    int* chosen = (int*)malloc(sizeof(int) * length(head));

    combine(head, chosen, 0, &results, &result_count);

    free(chosen);
    *count = result_count;
    return results;
}



void permute(Node* node, int* chosen, int chosen_len, Node*** results, int* count) {
    if (node == NULL) {
        Node* perm_head = NULL;
        Node* perm_tail = NULL;

        for (int i = 0; i < chosen_len; i++) {
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->data = chosen[i];
            new_node->next = NULL;

            if (perm_head == NULL) {
                perm_head = perm_tail = new_node;
            } else {
                perm_tail->next = new_node;
                perm_tail = new_node;
            }
        }

        *results = (Node**)realloc(*results, sizeof(Node*) * (*count + 1));
        (*results)[(*count)++] = perm_head;
        return;
    }

    Node* current = node;
    Node* prev = NULL;

    while (current != NULL) {
        Node* next_node = current->next;

        if (prev != NULL) {
            prev->next = next_node;
        } else {
            node = next_node;
        }

        chosen[chosen_len] = current->data;
        permute(node, chosen, chosen_len + 1, results, count);

        if (prev != NULL) {
            prev->next = current;
        } else {
            node = current;
        }

        prev = current;
        current = next_node;
    }
}

Node** permute_linked_list(Node* head, int* count) {
    Node** results = NULL;
    int result_count = 0;
    int* chosen = (int*)malloc(sizeof(int) * length(head));

    permute(head, chosen, 0, &results, &result_count);

    free(chosen);
    *count = result_count;
    return results;
}


Node* find_peaks(Node* head, int* count) {
    Node* peaks_head = NULL;
    Node* peaks_tail = NULL;
    *count = 0;

    Node* prev = NULL;
    Node* current = head;
    Node* next_node = head != NULL ? head->next : NULL;

    if (next_node != NULL && current->data > next_node->data) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = current->data;
        new_node->next = NULL;
        peaks_head = peaks_tail = new_node;
        (*count)++;
    }

    while (next_node != NULL && next_node->next != NULL) {
        prev = current;
        current = next_node;
        next_node = next_node->next;

        if (current->data > prev->data && current->data > next_node->data) {
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->data = current->data;
            new_node->next = NULL;

            if (peaks_head == NULL) {
                peaks_head = peaks_tail = new_node;
            } else {
                peaks_tail->next = new_node;
                peaks_tail = new_node;
            }

            (*count)++;
        }
    }

    if (current != NULL && next_node != NULL && next_node->data > current->data) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = next_node->data;
        new_node->next = NULL;

        if (peaks_head == NULL) {
            peaks_head = peaks_tail = new_node;
        } else {
            peaks_tail->next = new_node;
            peaks_tail = new_node;
        }

        (*count)++;
    }

    return peaks_head;
}



int main() {
    int values[] = {1, 2, 3, 4};
    Node* head = create_linked_list_from_list(values, 4);

    print_linked_list(head);

    Node* sorted = bubble_sort(head);
    print_linked_list(sorted);

    int count;
    Node** substrings = get_all_substrings(head, &count);
    for (int i = 0; i < count; i++) {
        print_linked_list(substrings[i]);
    }

    return 0;
}
