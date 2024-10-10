#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct Node {
    element data;
    struct Node* next;
    struct Node* prev;
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
        return list->head->data;}
    return -1;
}

int get_last(LList * list) {
    if (list->tail != NULL) {
        return list->tail->data;
    }
    return -1;
}


//리스트 찍어보기
void print_list(LList *list) {
    Node *cur = list->head;
    while (cur != NULL) {
        printf("%d ", cur->data);
        //만약 char라면 %s
        cur = cur->next;
    }
    printf("\n");
}


//노드 삽입
//p가 가리키는 노드 다음에 새로운 노드를 삽입하는 경우
// Node* add_after(Node *pre, element item) {
//     Node *new_node = (Node*)malloc(sizeof(Node));
//     new_node->data = item;
//     new_node->prev = NULL;
//     new_node->next = NULL;

//     if (pre == NULL && head == NULL) {  //노드가 0개인 empty list라면
//         head = new_node;    //첫번째 노드이면서 마지막 노드
//         tail = new_node;
//     }

//     else if (pre == NULL) {    //연결리스트의 맨 앞에 삽입
//         new_node->next = head;
//         head->prev = new_node;
//         head = new_node;
//     }

//     else if (pre == tail) {   //맨 마지막에 삽입
//         new_node -> prev = tail;
//         tail->next = new_node;
//         tail = new_node;
//     }

//     else {
//         new_node->prev = pre;
//         new_node->next = pre->next;
//         pre->next->prev = new_node;
//         pre->next = new_node;
//     }
//     size++;
// }
//add_after(tail, "new_tail");

//연결리스트의 맨 앞에 삽입
void add_first(LList * list, element item) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = item;
    temp->next = list->head;
    temp->prev = NULL;
    if (list->head != NULL) {
        list->head->prev = temp;
    }
    else {
        list->tail = temp;
    }
    list->head = temp;
    list->size++;
}

void add_before(LList *list, Node* next_node, element item) {
    if (next_node == NULL) return;
    Node * temp = (Node*)malloc(sizeof(Node));
    temp->data = item;
    temp->prev = next_node->prev;
    temp->next = next_node;
    if (next_node->prev != NULL) {
        next_node->prev->next = temp;
    }
    else {
        list->head = temp;
    }
    next_node->prev = temp;
    list->size++;
} 

//특정 노드 앞에 삽입
// void add_after(Node *prev, element item) {
//     if (prev == NULL) return;
//     Node *temp = (Node*)malloc(sizeof(Node));
//     temp->data = item;
//     temp->next = prev->next;
//     temp->prev = prev;
//     if (prev->next != NULL) {
//         prev->next->prev = temp;
//     }
//     prev->next = temp;
// }

void add_after(LList* list, Node* prev_node, int item) {
    if (prev_node == NULL) return;

    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = item;
    temp->next = prev_node->next;
    temp->prev = prev_node;

    if (prev_node->next != NULL) {
        prev_node->next->prev = temp;
    } else {
        list->tail = temp;
    }

    prev_node->next = temp;
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
;
    }
}


//노드 찾기
Node* find_node(LList *list, element item) {
    Node *cur = list->head;
    while (cur != NULL) {
        if (cur->data == item){
            return cur;
        }
        cur = cur -> next;
    }
    return NULL;
}

//노드 삭제
// //p가 가리키는 노드 삭제하기
// void delete_node(char *item) {
//     Node *cur = find_node(item);
//     //만약 item말고 그냥 Node가 주어졌으면 윗줄 필요없이 그냥 cur로 넣기

//     if (cur == NULL) return;

//     if (cur == head) {
//         head = cur->next;
//         if (head != NULL) {
//             head->prev = NULL;
//         }
//         if (cur == tail) {  //리스트가 노드 하나로 이루어진 경우
//             tail = NULL;
//         }
//     }
    
//     else if (cur == tail) {
//         tail = cur -> prev;
//         if (tail != NULL) {
//             tail ->next = NULL;
//         }
//     }
//     else {
//         cur->prev->next = cur->next;
//         cur->next->prev = cur->prev;
//     }
//     free(cur);
//     size--;
// }
//delete_node("apple");


// 첫번째 노드 지우기
void remove_first(LList *list) {
    if (list->head == NULL) return;
    Node *temp = list->head;
    list->head = list->head->next;
    if (list->head != NULL) {
        list->head->prev = NULL;
    }
    free(temp);
    list->size--;
}

//마지막 노드 지우기
void remove_last(LList *list) {
    if (list->tail == NULL) return;

    Node *temp = list->tail;
    list->tail = list->tail->prev;

    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;  // 리스트가 비어 있으면 head도 NULL로 설정
    }

    free(temp);
    list->size--;
}


// 해당 노드 다음 노드 지우기
void remove_after(LList* list, Node* prev_node) {
    if (prev_node == NULL || prev_node->next == NULL) return;

    Node* temp = prev_node->next;
    prev_node->next = temp->next;

    if (temp->next != NULL) {
        temp->next->prev = prev_node;
    } else {
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
    }

    Node *prev = get_node_by_index(list, index-1);
    if (prev != NULL && prev->next != NULL) {
        remove_after(list, prev);
    }
}

// 주어진 data에 해당하는 노드 지우기
void remove_by_value(LList* list, element item) {
    Node* node_to_remove = find_node(list, item);

    if (node_to_remove == NULL) return;

    if (node_to_remove == list->head) {
        remove_first(list);
    } else if (node_to_remove == list->tail) {
        remove_last(list);
    } else {
        Node* prev = node_to_remove->prev;
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
            list1->prev = tail;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2->prev = tail;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    tail->next = (list1 != NULL) ? list1 : list2;
    if (tail->next != NULL) {
        tail->next->prev = tail;
    }
    return dummy.next;
}



// Function to concatenate two lists
// Node* concat(Node *list1, Node *list2) {
//     if (list1 == NULL) {
//         return list2;
//     }
//     if (list2 == NULL) {
//         return list1;
//     }
//     Node *p = list1;
//     while (p->next != NULL) {
//         p = p->next;
//     }
//     p->next = list2;
//     list2->prev = p;
//     return list1;
// }

//or,
void concat(LList* list1, LList* list2) {
    if (list1->head == NULL) {
        list1->head = list2->head;
        list1->tail = list2->tail;
    } else if (list2->head != NULL) {
        list1->tail->next = list2->head;
        list2->head->prev = list1->tail;
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

    // printf("Starting sort: ");
    // print_list(list);

    Node *mid = get_mid(list);
    if (mid == NULL || mid->next == NULL) return; // Safety check

    Node *half = mid->next;
    mid->next = NULL; // Split the list into two halves
    if (half) {
        half->prev = NULL; // Ensure the start of the second list has no previous node
    }

    // printf("List split into two halves. Left head: %d, Right head: %d\n", list->head->data, half ? half->data : -1);

    LList* left_sorted = create_list();
    LList* right_sorted = create_list();

    left_sorted->head = list->head;
    left_sorted->tail = mid;
    left_sorted->size = list->size / 2;

    right_sorted->head = half;
    right_sorted->tail = list->tail;
    right_sorted->size = list->size - left_sorted->size;

    // printf("Sorting left half.\n");
    sort(left_sorted);
    // printf("Left half sorted: ");
    // print_list(left_sorted);

    // printf("Sorting right half.\n");
    sort(right_sorted);
    // printf("Right half sorted: ");
    // print_list(right_sorted);

    list->head = merge(left_sorted->head, right_sorted->head);
    // printf("Lists merged: ");
    // print_list(list);

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


//or,
// Node* sort(Node* head) {
//     if (head == NULL || head->next == NULL) return head;

//     Node* mid = get_mid(head);
//     Node* half = mid->next;
//     mid->next = NULL;
//     if (half != NULL) {
//         half->prev = NULL;
//     }

//     Node* left_sorted = sort(head);
//     Node* right_sorted = sort(half);
//     return merge(left_sorted, right_sorted);
// }

// void sort_list(LList* list) {
//     if (list->head == NULL || list->head->next == NULL) return;

//     list->head = sort(list->head);

//     // Update tail
//     Node* tail = list->head;
//     while (tail->next != NULL) {
//         tail = tail->next;
//     }
//     list->tail = tail;
// }


void insertion_sort(LList* list) {
    if (list->head == NULL || list->head->next == NULL) {
        return;  // 리스트가 비어있거나 요소가 하나인 경우
    }

    Node* sorted = NULL;  // 정렬된 리스트의 시작점
    Node* cur = list->head;

    while (cur != NULL) {
        Node* next = cur->next;  // 다음 노드를 미리 저장
        cur->prev = cur->next = NULL;  // 현재 노드를 분리

        if (sorted == NULL) {
            sorted = cur;  // 첫 번째 노드를 정렬된 리스트의 시작으로 설정
        } else if (sorted->data >= cur->data) {
            // 현재 노드가 정렬된 리스트의 첫 번째 노드보다 작거나 같으면, 가장 앞으로 삽입
            cur->next = sorted;
            sorted->prev = cur;
            sorted = cur;
        } else {
            // 정렬된 리스트에서 적절한 위치를 찾음
            Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < cur->data) {
                temp = temp->next;
            }
            cur->next = temp->next;
            if (temp->next != NULL) {
                temp->next->prev = cur;
            }
            cur->prev = temp;
            temp->next = cur;
        }
        cur = next;  // 다음 노드로 이동
    }

    // 정렬된 리스트를 기존 리스트에 할당
    list->head = sorted;
    list->tail = sorted;
    while (list->tail->next != NULL) {
        list->tail = list->tail->next;
    }
}


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
// Node* reverse(LList * list) {
//     Node *prev = NULL;
//     Node *cur = list->head;
//     Node *next = NULL;
//     while (cur != NULL) {
//         next = cur->next;
//         cur->next = prev;
//         cur->prev = next;
//         prev = cur;
//         cur = next;
//     }
//     return prev;
// }

//or,
void reverse(LList* list) {
    Node* prev = NULL;
    Node* cur = list->head;
    Node* next = NULL;

    while (cur) {
        next = cur->next;
        cur->next = prev;
        cur->prev = next;
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
    new_head->prev = NULL;

    list->tail->next = list->head;
    list->head->prev = list->tail;

    list->head = new_head;
    list->tail = new_tail;
}

// Convert array to linked list
void array_to_linkedlist(LList* list, element arr[], int size) {
    clear(list);  // 기존 리스트를 초기화합니다.

    for (int i = 0; i < size; ++i) {
        if (list->head == NULL) {
            add_first(list, arr[i]);  // 리스트가 비어있을 경우 첫 번째 요소 추가
        } else {
            add_after(list, list->tail, arr[i]);  // 그 이후 요소들은 tail 뒤에 추가
        }
    }
}



// Convert linked list to array
int* linkedlist_to_array(LList* list) {
    if (list->size == 0) return NULL;  // 빈 리스트는 NULL을 반환합니다.

    int* arr = (int*)malloc(list->size * sizeof(int));  // 리스트 크기만큼 배열을 동적 할당합니다.
    Node* current = list->head;
    int index = 0;

    while (current != NULL) {
        arr[index++] = current->data;  // 현재 노드의 데이터를 배열에 복사합니다.
        current = current->next;
    }

    return arr;
}


int main() {
    LList* llist = create_list();

    // Initial list setup
    add_first(llist, 3); // Thursday
    add_first(llist, 2); // Tuesday
    add_first(llist, 1); // Monday

    printf("Initial List:\n");
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
    add_to_ordered_list(llist, 7);
    print_list(llist);

    // Reverse the list
    reverse(llist);
    printf("Reversed List:\n");
    print_list(llist);

     // Selection sort
    selection_sort(llist);
    printf("List after selection sort:\n");
    print_list(llist);

    // Add to ordered list
    add_to_ordered_list(llist, 4); // Wednesday
    printf("Ordered Insertion:\n");
    print_list(llist);

    rotate(llist, 2);
    printf("List after rotating by 2 positions:\n");
    print_list(llist);

    // Insertion sort
    insertion_sort(llist);
    printf("List after insertion sort:\n");
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

    // Merge two lists
    LList* list1 = create_list();
    LList* list2 = create_list();

    add_first(list1, 4); // D
    add_first(list1, 2); // B
    add_first(list1, 1); // A

    add_first(list2, 5); // E
    add_first(list2, 3); // C


    // Node *merged_list = merge(sort(list1), sort(list2));
    // printf("Merged and Sorted List:\n");
    // print_list(merged_list);

    // Concatenate two lists
    concat(list1, list2);
    printf("Concatenated List:\n");
    print_list(list1);
   

    // Sort the list
    sort(list1);
    printf("Sorted List:\n");
    print_list(list1);

    // LinkedList to Array
    int* array_from_list = linkedlist_to_array(list1);
    printf("Array after converting from linked list:\n");
    for (int i = 0; i < get_size(list1); ++i) {
        printf("%d ", array_from_list[i]);
    }
    printf("\n");

    // Clear the list and convert array back to LinkedList
    int size_before_clear = get_size(list1); // Clear 전의 리스트 크기 저장
    clear(list1);
    array_to_linkedlist(list1, array_from_list, size_before_clear); // 저장한 크기를 사용
    printf("Linked list after converting back from array:\n");
    print_list(list1);


    // Clean up
    free(array_from_list);
    clear(list1);
    free(list1);

    return 0;
}