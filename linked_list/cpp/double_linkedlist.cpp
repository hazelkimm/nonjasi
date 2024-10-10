#include <iostream>
#include <cstdlib>

typedef int element;

struct Node {
    element data;
    Node* next;
    Node* prev;
};

struct LList {
    int size;
    Node *head;
    Node *tail;
};

LList *create_list() {
    LList *list = new LList;
    list->size = 0;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

int get_size(LList* list) {
    return list->size;
}

bool is_empty(LList* list) {
    return list->size == 0;
}

void clear(LList* list) {
    Node* current = list->head;
    Node* next_node;

    while (current != nullptr) {
        next_node = current->next;
        delete current;
        current = next_node;
    }

    list->head = list->tail = nullptr;
    list->size = 0;
}

int get_first(LList *list) {
    if (list->head != nullptr) {
        return list->head->data;
    }
    return -1;
}

int get_last(LList * list) {
    if (list->tail != nullptr) {
        return list->tail->data;
    }
    return -1;
}

void print_list(LList *list) {
    Node *cur = list->head;
    while (cur != nullptr) {
        std::cout << cur->data << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}

void add_first(LList * list, element item) {
    Node *temp = new Node;
    temp->data = item;
    temp->next = list->head;
    temp->prev = nullptr;
    if (list->head != nullptr) {
        list->head->prev = temp;
    }
    else {
        list->tail = temp;
    }
    list->head = temp;
    list->size++;
}

void add_before(LList *list, Node* next_node, element item) {
    if (next_node == nullptr) return;
    Node *temp = new Node;
    temp->data = item;
    temp->prev = next_node->prev;
    temp->next = next_node;
    if (next_node->prev != nullptr) {
        next_node->prev->next = temp;
    }
    else {
        list->head = temp;
    }
    next_node->prev = temp;
    list->size++;
}

void add_after(LList* list, Node* prev_node, int item) {
    if (prev_node == nullptr) return;

    Node* temp = new Node;
    temp->data = item;
    temp->next = prev_node->next;
    temp->prev = prev_node;

    if (prev_node->next != nullptr) {
        prev_node->next->prev = temp;
    } else {
        list->tail = temp;
    }

    prev_node->next = temp;
    list->size++;
}

Node* get_node_by_index(LList *list, int index) {
    if (index < 0) return nullptr;
    Node *p = list->head;
    for (int i = 0; i < index && p != nullptr; i++) {
        p = p->next;
    }
    return p;
}

void add_by_index(LList* list, int index, element item) {
    if (index < 0 || index > list->size) {
        return; // Handle out-of-bounds index
    }

    if (index == 0) {
        add_first(list, item);
        return;
    }

    Node *prev = get_node_by_index(list, index - 1);
    if (prev != nullptr) {
        add_after(list, prev, item);
    }
}

void add_to_ordered_list(LList *list, element item) {
    Node *p = list->head;
    Node *q = nullptr;

    while (p != nullptr && p->data < item) {
        q = p;
        p = p->next;
    }

    if (q == nullptr) {
        add_first(list, item);
    } else {
        add_after(list, q, item);
    }
}

Node* find_node(LList *list, element item) {
    Node *cur = list->head;
    while (cur != nullptr) {
        if (cur->data == item){
            return cur;
        }
        cur = cur -> next;
    }
    return nullptr;
}

void remove_first(LList *list) {
    if (list->head == nullptr) return;
    Node *temp = list->head;
    list->head = list->head->next;
    if (list->head != nullptr) {
        list->head->prev = nullptr;
    }
    delete temp;
    list->size--;
}

void remove_last(LList *list) {
    if (list->tail == nullptr) return;
    Node *temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != nullptr) {
        list->tail->next = nullptr;
    }
    else{
        list->head = nullptr;
    }
    delete temp;
    list->size--;
}

void remove_after(LList* list, Node* prev_node) {
    if (prev_node == nullptr || prev_node->next == nullptr) return;

    Node* temp = prev_node->next;
    prev_node->next = temp->next;

    if (temp->next != nullptr) {
        temp->next->prev = prev_node;
    } else {
        list->tail = prev_node;
    }

    delete temp;
    list->size--;
}

void remove_by_index(LList* list, int index) {
    if (index < 0) {
        return;
    }

    if (index == 0) {
        remove_first(list);
    }

    Node *prev = get_node_by_index(list, index-1);
    if (prev != nullptr && prev->next != nullptr) {
        remove_after(list, prev);
    }
}

void remove_by_value(LList* list, element item) {
    Node* node_to_remove = find_node(list, item);

    if (node_to_remove == nullptr) return;

    if (node_to_remove == list->head) {
        remove_first(list);
    } else if (node_to_remove == list->tail) {
        remove_last(list);
    } else {
        Node* prev = node_to_remove->prev;
        remove_after(list, prev);
    }
}

Node* merge(Node *list1, Node *list2) {
    Node dummy;
    Node *tail = &dummy;
    dummy.next = nullptr;

    while (list1 != nullptr && list2 != nullptr) {
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
    tail->next = (list1 != nullptr) ? list1 : list2;
    if (tail->next != nullptr) {
        tail->next->prev = tail;
    }
    return dummy.next;
}

void concat(LList* list1, LList* list2) {
    if (list1->head == nullptr) {
        list1->head = list2->head;
        list1->tail = list2->tail;
    } else if (list2->head != nullptr) {
        list1->tail->next = list2->head;
        list2->head->prev = list1->tail;
        list1->tail = list2->tail;
    }
    list1->size += list2->size;
    list2->head = list2->tail = nullptr;
    list2->size = 0;
}

Node* get_mid(LList* list) {
    if (list == nullptr || list->head == nullptr) return nullptr;
    Node* slow = list->head;
    Node* fast = list->head;

    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

void sort(LList *list) {
    if (list == nullptr || list->head == nullptr || list->head->next == nullptr) {
        return; // Base case for recursion
    }

    Node *mid = get_mid(list);
    if (mid == nullptr || mid->next == nullptr) return; // Safety check

    Node *half = mid->next;
    mid->next = nullptr; // Split the list into two halves
    if (half) {
        half->prev = nullptr; // Ensure the start of the second list has no previous node
    }

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

    Node* cur = list->head;
    while (cur && cur->next) {
        cur = cur->next;
    }
    list->tail = cur;
    list->size = left_sorted->size + right_sorted->size;

    delete left_sorted;
    delete right_sorted;
}

// Insertion sort for the linked list
void insertion_sort(LList* list) {
    if (!list->head || !list->head->next) return;

    Node* sorted_head = list->head;
    Node* cur = list->head->next;
    sorted_head->next = nullptr;

    while (cur) {
        Node* next_cur = cur->next;
        if (cur->data < sorted_head->data) {
            cur->next = sorted_head;
            sorted_head->prev = cur;
            sorted_head = cur;
        } else {
            Node* search = sorted_head;
            while (search->next && search->next->data < cur->data) {
                search = search->next;
            }
            cur->next = search->next;
            if (search->next) {
                search->next->prev = cur;
            }
            search->next = cur;
            cur->prev = search;
        }
        cur = next_cur;
    }

    list->head = sorted_head;
    list->tail = sorted_head;
    while (list->tail && list->tail->next) {
        list->tail = list->tail->next;
    }
}

// Selection sort for the linked list
void selection_sort(LList* list) {
    if (!list->head) return;

    Node* cur = list->head;
    while (cur) {
        Node* min_node = cur;
        Node* search = cur->next;
        while (search) {
            if (search->data < min_node->data) {
                min_node = search;
            }
            search = search->next;
        }
        if (min_node != cur) {
            std::swap(cur->data, min_node->data);
        }
        cur = cur->next;
    }
}


void reverse(LList* list) {
    Node* prev = nullptr;
    Node* cur = list->head;
    Node* next = nullptr;

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

void rotate(LList* list, int d) {
    if (list->head == nullptr || d == 0 || list->size == 0) return;

    d = d % list->size;
    if (d == 0) return;

    if (d < 0) d = list->size + d;

    Node* new_tail = list->head;
    for (int i = 0; i < list->size - d - 1; i++) {
        new_tail = new_tail->next;
    }

    Node* new_head = new_tail->next;
    new_tail->next = nullptr;
    new_head->prev = nullptr;

    list->tail->next = list->head;
    list->head->prev = list->tail;

    list->head = new_head;
    list->tail = new_tail;
}


///// array_to_linkedlist에 사용예정
void add_last(LList* list, element item) {
    Node* temp = new Node;
    temp->data = item;
    temp->next = nullptr;
    temp->prev = list->tail;

    if (list->tail != nullptr) {
        list->tail->next = temp;
    } else {
        list->head = temp;  // 리스트가 비어있을 경우 head도 갱신합니다.
    }

    list->tail = temp;
    list->size++;
}

void array_to_linkedlist(LList* list, element arr[], int size) {
    clear(list);  // 기존 리스트를 초기화합니다.

    for (int i = 0; i < size; ++i) {
        add_last(list, arr[i]);  // 배열의 각 요소를 리스트의 끝에 추가합니다.
    }
}

int* linkedlist_to_array(LList* list) {
    if (list->size == 0) return nullptr;  // 빈 리스트는 nullptr을 반환합니다.

    int* arr = new int[list->size];  // 리스트 크기만큼 배열을 동적 할당합니다.
    Node* current = list->head;
    int index = 0;

    while (current != nullptr) {
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

    std::cout << "Initial List:" << std::endl;
    print_list(llist);

    // Reverse the list
    reverse(llist);
    std::cout << "Reversed List:" << std::endl;
    print_list(llist);
    
    // Insertion sort the list
    insertion_sort(llist);
    std::cout << "Insertion sort List:" << std::endl;
    print_list(llist);

    // Add to ordered list
    add_to_ordered_list(llist, 4); // Wednesday
    std::cout << "Ordered Insertion:" << std::endl;
    print_list(llist);

    rotate(llist, 2);
    std::cout << "List after rotating by 2 positions:" << std::endl;
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
    std::cout << "Concatenated List:" << std::endl;
    print_list(list1);
   
    // Reverse the list
    reverse(list1);
    std::cout << "Reversed List:" << std::endl;
    print_list(list1);

    // Sort the list
    selection_sort(list1);
    std::cout << "Selection sort List:" << std::endl;
    print_list(list1);

     // LinkedList to Array
    int* array_from_list = linkedlist_to_array(list1);
    std::cout << "Array after converting from linked list:" << std::endl;
    for (int i = 0; i < get_size(list1); ++i) {
        std::cout << array_from_list[i] << " ";
    }
    std::cout << std::endl;

    // Array to Linkedlist
    LList* new_list = create_list();
    array_to_linkedlist(new_list, array_from_list, list1->size);
    std::cout << "New Linked List converted from array:" << std::endl;
    print_list(new_list);

    return 0;
}
