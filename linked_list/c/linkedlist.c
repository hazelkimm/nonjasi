#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct Node {
    element data;
    struct Node* next;
} Node;

typedef struct LList {
    int size;
    Node *head;
    Node *tail;
} LList;

LList *create_list() {
    LList *list = (LList*)malloc(sizeof(LList));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int get_size(LList* list) {
    return list->size;
}

int is_empty(LList* list) {
    return list->size == 0;
}

void clear(LList* list) {
    Node* current = list->head;
    Node* next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    list->head = list->tail = NULL;
    list->size = 0;
}

int get_first(LList *list) {
    if (list->head != NULL) {
        return list->head->data;
    }
    return -1;
}

int get_last(LList * list) {
    if (list->tail != NULL) {
        return list->tail->data;
    }
    return -1;
}

// 리스트 출력
void print_list(LList *list) {
    Node *cur = list->head;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

// 연결리스트의 맨 앞에 삽입
void add_first(LList * list, element item) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = item;
    temp->next = list->head;
    list->head = temp;
    if (list->tail == NULL) {
        list->tail = temp;
    }
    list->size++;
}

// 특정 노드 뒤에 삽입
void add_after(LList* list, Node* prev_node, int item) {
    if (prev_node == NULL) return;

    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = item;
    temp->next = prev_node->next;

    prev_node->next = temp;
    if (temp->next == NULL) {
        list->tail = temp;
    }
    list->size++;
}

// index에 해당하는 노드 찾기
Node* get_node_by_index(LList *list, int index) {
    if (index < 0) return NULL;
    Node *p = list->head;
    for (int i = 0; i < index && p != NULL; i++) {
        p = p->next;
    }
    return p;
}

// index에 해당하는 노드 삽입하기
void add_by_index(LList* list, int index, element item) {
    if (index < 0 || index > list->size) {
        return; // Handle out-of-bounds index
    }

    if (index == 0) {
        add_first(list, item);
        return;
    }

    Node *prev = get_node_by_index(list, index - 1);
    if (prev != NULL) {
        add_after(list, prev, item);
    }
}

// ordered list에 add하기
void add_to_ordered_list(LList *list, element item) {
    Node *p = list->head;
    Node *q = NULL;

    while (p != NULL && p->data < item) {
        q = p;
        p = p->next;
    }

    if (q == NULL) {
        add_first(list, item);
    } else {
        add_after(list, q, item);
    }
}

// 노드 찾기
Node* find_node(LList *list, element item) {
    Node *cur = list->head;
    while (cur != NULL) {
        if (cur->data == item) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// 첫번째 노드 지우기
void remove_first(LList *list) {
    if (list->head == NULL) return;
    Node *temp = list->head;
    list->head = list->head->next;
    free(temp);
    if (list->head == NULL) {
        list->tail = NULL;
    }
    list->size--;
}

// 마지막 노드 지우기
void remove_last(LList *list) {
    if (list->head == NULL) return;

    if (list->head == list->tail) {
        free(list->head);
        list->head = list->tail = NULL;
    } else {
        Node *temp = list->head;
        while (temp->next != list->tail) {
            temp = temp->next;
        }
        free(list->tail);
        list->tail = temp;
        list->tail->next = NULL;
    }
    list->size--;
}

// 해당 노드 다음 노드 지우기
void remove_after(LList* list, Node* prev_node) {
    if (prev_node == NULL || prev_node->next == NULL) return;

    Node* temp = prev_node->next;
    prev_node->next = temp->next;

    if (temp == list->tail) {
        list->tail = prev_node;
    }

    free(temp);
    list->size--;
}

// index로 노드 지우기
void remove_by_index(LList* list, int index) {
    if (index < 0) {
        return;
    }

    if (index == 0) {
        remove_first(list);
        return;
    }

    Node *prev = get_node_by_index(list, index - 1);
    if (prev != NULL && prev->next != NULL) {
        remove_after(list, prev);
    }
}

// 주어진 data에 해당하는 노드 지우기
void remove_by_value(LList* list, element item) {
    if (list->head == NULL) return;

    if (list->head->data == item) {
        remove_first(list);
        return;
    }

    Node* prev = list->head;
    Node* cur = list->head->next;

    while (cur != NULL && cur->data != item) {
        prev = cur;
        cur = cur->next;
    }

    if (cur != NULL) {
        remove_after(list, prev);
    }
}

// Function to merge two sorted lists
Node* merge(Node *list1, Node *list2) {
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    tail->next = (list1 != NULL) ? list1 : list2;
    return dummy.next;
}

// Function to concatenate two lists
void concat(LList* list1, LList* list2) {
    if (list1->head == NULL) {
        list1->head = list2->head;
        list1->tail = list2->tail;
    } else if (list2->head != NULL) {
        list1->tail->next = list2->head;
        list1->tail = list2->tail;
    }
    list1->size += list2->size;
    list2->head = list2->tail = NULL;
    list2->size = 0;
}

// Function to get the middle node
Node* get_mid(LList* list) {
    if (list == NULL || list->head == NULL) return NULL;
    Node* slow = list->head;
    Node* fast = list->head;

    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Function to sort the list (오름차순 정렬)
void sort(LList *list) {
    if (list == NULL || list->head == NULL || list->head->next == NULL) {
        return; // Base case for recursion
    }

    Node *mid = get_mid(list);
    if (mid == NULL) return; // Safety check

    Node *half = mid->next;
    mid->next = NULL; // Split the list into two halves

    LList* left_sorted = create_list();
    LList* right_sorted = create_list();

    left_sorted->head = list->head;
    left_sorted->tail = mid;
    left_sorted->size = list->size / 2;

    right_sorted->head = half;
    right_sorted->tail = list->tail;
    right_sorted->size = list->size - left_sorted->size;

    sort(left_sorted);
    sort(right_sorted);

    list->head = merge(left_sorted->head, right_sorted->head);

    // Update tail pointer after merging
    Node* cur = list->head;
    while (cur && cur->next) {
        cur = cur->next;
    }
    list->tail = cur;
    list->size = left_sorted->size + right_sorted->size;

    free(left_sorted);
    free(right_sorted);
}

// Insertion Sort
void insertion_sort(LList* list) {
    if (list->head == NULL || list->head->next == NULL) {
        return;  // 리스트가 비어있거나 요소가 하나인 경우
    }

    Node* sorted = NULL;  // 정렬된 리스트의 시작점
    Node* cur = list->head;

    while (cur != NULL) {
        Node* next = cur->next;  // 다음 노드를 미리 저장
        cur->next = NULL;  // 현재 노드를 분리

        if (sorted == NULL || sorted->data >= cur->data) {
            cur->next = sorted;
            sorted = cur;
        } else {
            Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < cur->data) {
                temp = temp->next;
            }
            cur->next = temp->next;
            temp->next = cur;
        }
        cur = next;  // 다음 노드로 이동
    }

    list->head = sorted;

    Node* end = sorted;
    while (end->next != NULL) {
        end = end->next;
    }
    list->tail = end;
}

// Selection Sort
void selection_sort(LList* list) {
    if (list->head == NULL || list->head->next == NULL) {
        return;  // 리스트가 비어있거나 요소가 하나인 경우
    }

    Node* cur = list->head;

    while (cur != NULL) {
        Node* min = cur;
        Node* r = cur->next;

        // 현재 위치에서 최소값을 찾음
        while (r != NULL) {
            if (r->data < min->data) {
                min = r;
            }
            r = r->next;
        }

        // 최소값을 현재 위치의 값과 교환
        if (min != cur) {
            element temp = cur->data;
            cur->data = min->data;
            min->data = temp;
        }

        cur = cur->next;  // 다음 노드로 이동
    }
}


// Function to reverse the list
void reverse(LList* list) {
    Node* prev = NULL;
    Node* cur = list->head;
    Node* next = NULL;

    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    list->tail = list->head;
    list->head = prev;
}

// Rotate the list
void rotate(LList* list, int d) {
    if (list->head == NULL || d == 0 || list->size == 0) return;

    d = d % list->size;
    if (d == 0) return;

    if (d < 0) d = list->size + d;

    Node* new_tail = list->head;
    for (int i = 0; i < list->size - d - 1; i++) {
        new_tail = new_tail->next;
    }

    Node* new_head = new_tail->next;
    new_tail->next = NULL;

    Node* temp = list->head;
    list->head = new_head;

    Node* end = list->head;
    while (end->next != NULL) {
        end = end->next;
    }
    end->next = temp;
    list->tail = new_tail;
}

#include <stdbool.h>

bool hasCycle(struct Node *head) {
    struct Node *slow_ptr = head;
    struct Node *fast_ptr = head;
    while (fast_ptr != NULL && fast_ptr->next != NULL){
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;
        if(slow_ptr == fast_ptr){
            return true;
        }
    }
    return false;
}

struct Node *detectCycle(struct Node *head) {
    
    // Initial Condition for for no node or no cycle
    if(head == NULL || head->next == NULL)return NULL;
    
    struct Node* slowptr = head;//Slow Pointer
    struct Node* fastptr = head;//Fast Pointer
    struct Node* entryptr = head; // entry location
    
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

int* linkedlist_to_array(LList* list) {
    int* arr = (int*)malloc(list->size * sizeof(int));
    Node* current = list->head;
    int index = 0;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }
    return arr;
}

void array_to_linkedlist(LList* list, int* arr, int array_size) {
    clear(list);  // 기존 리스트를 초기화합니다.
    for (int i = 0; i < array_size; i++) {
        if (list->head == NULL) {
            add_first(list, arr[i]);  // 리스트가 비어 있을 경우 첫 번째 요소 추가
        } else {
            add_after(list, list->tail, arr[i]);  // 그 이후 요소들은 tail 뒤에 추가
        }
    }
}


int main() {
    LList* llist = create_list();

    // Initial list setup
    printf("Adding 3, 2, 1 to the list using add_first:\n");
    add_first(llist, 3); // Thursday
    add_first(llist, 2); // Tuesday
    add_first(llist, 1); // Monday
    print_list(llist);

    // Get size of the list
    printf("Size of the list: %d\n", get_size(llist));

    // Get first and last elements
    printf("First element: %d\n", get_first(llist));
    printf("Last element: %d\n", get_last(llist));

    // Find a node
    printf("Finding node with value 2:\n");
    Node* found = find_node(llist, 2);
    printf("Found: %d\n", found != NULL ? found->data : -1);

    // Insert at index
    printf("Inserting 5 at index 1:\n");
    add_by_index(llist, 1, 5);
    print_list(llist);

    // Ordered insertion
    printf("Adding 4 to ordered list:\n");
    add_to_ordered_list(llist, 4);
    print_list(llist);

    // Reverse the list
    printf("Reversing the list:\n");
    reverse(llist);
    print_list(llist);

    // Sort the list
    printf("Insertion sort:\n");
    insertion_sort(llist);
    print_list(llist);

    // Rotate the list
    printf("Rotating the list by 2 positions:\n");
    rotate(llist, 2);
    print_list(llist);

    printf("Selection sorting:\n");
    selection_sort(llist);
    print_list(llist);

    // Remove first and last
    printf("Removing first element:\n");
    remove_first(llist);
    print_list(llist);

    printf("Removing last element:\n");
    remove_last(llist);
    print_list(llist);

    // Remove by value
    printf("Removing node with value 4:\n");
    remove_by_value(llist, 4);
    print_list(llist);

    // Clear the list
    printf("Clearing the list:\n");
    clear(llist);
    print_list(llist);

    // Creating two lists for merging and concatenating
    LList* list1 = create_list();
    LList* list2 = create_list();
    add_first(list1, 4);
    add_first(list1, 2);
    add_first(list1, 1);
    add_first(list2, 5);
    add_first(list2, 3);
    printf("List 1:\n");
    print_list(list1);
    printf("List 2:\n");
    print_list(list2);

    // Concatenate two lists
    printf("Concatenating list 1 and list 2:\n");
    concat(list1, list2);
    print_list(list1);

    // Convert list1 to array and back to linked list
    int* array_from_list = linkedlist_to_array(list1);
    printf("Array after converting from linked list:\n");
    for (int i = 0; i < get_size(list1); i++) {
        printf("%d ", array_from_list[i]);
    }
    printf("\n");

    array_to_linkedlist(list1, array_from_list, get_size(list1));
    printf("Linked list after converting back from array:\n");
    print_list(list1);

    free(array_from_list);  // 동적 할당한 배열 해제

    return 0;
}
