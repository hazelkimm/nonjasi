// append: 끝에 노드 추가.
// prepend: 처음에 노드 추가.
// insertAfter: 특정 노드 뒤에 삽입.
// deleteNode: 특정 값을 가진 노드 삭제.
// search: 특정 값을 가진 노드 검색.
// reverse: 리스트를 뒤집기.
// printList: 리스트를 순방향으로 출력.
// printReverse: 리스트를 역방향으로 출력.
// freeList: 메모리를 해제하여 누수 방지.
// Sorting: Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort

#include <stdio.h>
#include <stdlib.h>

// Node 구조체 정의
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Doubly Linked List 구조체 정의
typedef struct DoublyLinkedList {
    Node* head;
} DoublyLinkedList;

// 이중 연결 리스트 초기화
DoublyLinkedList* createDoublyLinkedList() {
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    list->head = NULL;
    return list;
}

// 노드 생성
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// 리스트 끝에 노드 추가
void append(DoublyLinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    Node* temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// 리스트 처음에 노드 추가
void prepend(DoublyLinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;
}

// 특정 값 뒤에 노드 삽입
void insertAfter(DoublyLinkedList* list, int targetData, int data) {
    Node* temp = list->head;
    while (temp != NULL && temp->data != targetData) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Error: Node with data %d not found.\n", targetData);
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

// 특정 값을 가진 노드 삭제
void deleteNode(DoublyLinkedList* list, int data) {
    if (list->head == NULL) {
        printf("Error: List is empty.\n");
        return;
    }
    Node* temp = list->head;
    while (temp != NULL && temp->data != data) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Error: Node with data %d not found.\n", data);
        return;
    }
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        list->head = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
}

// 리스트에서 특정 값 검색
int search(DoublyLinkedList* list, int data) {
    Node* temp = list->head;
    while (temp != NULL) {
        if (temp->data == data) {
            return 1; // Found
        }
        temp = temp->next;
    }
    return 0; // Not Found
}

// 리스트 반전
void reverse(DoublyLinkedList* list) {
    Node* current = list->head;
    Node* temp = NULL;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != NULL) {
        list->head = temp->prev;
    }
}

// 리스트 출력
void printList(DoublyLinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// 리스트 역순 출력
void printReverse(DoublyLinkedList* list) {
    Node* temp = list->head;
    if (temp == NULL) {
        printf("List is empty.\n");
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    while (temp != NULL) {
        printf("%d <- ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

// 리스트 메모리 해제
void freeList(DoublyLinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    free(list);
}

// Bubble Sort for Doubly Linked List
void bubbleSort(Node** headRef) {
    if (*headRef == NULL || (*headRef)->next == NULL)
        return;

    int swapped;
    Node* current;
    Node* end = NULL;

    do {
        swapped = 0;
        current = *headRef;

        while (current->next != end) {
            if (current->data > current->next->data) {
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
        end = current;
    } while (swapped);
}

// Selection Sort for Doubly Linked List
void selectionSort(Node** headRef) {
    if (*headRef == NULL || (*headRef)->next == NULL)
        return;

    Node* current = *headRef;
    while (current) {
        Node* minNode = current;
        Node* nextNode = current->next;

        // Find the node with the minimum value in the unsorted part
        while (nextNode) {
            if (nextNode->data < minNode->data) {
                minNode = nextNode;
            }
            nextNode = nextNode->next;
        }

        // Swap data if a smaller node is found
        if (minNode != current) {
            int temp = current->data;
            current->data = minNode->data;
            minNode->data = temp;
        }

        current = current->next;
    }
}

// Insertion Sort for Doubly Linked List
void insertionSort(Node** headRef) {
    if (*headRef == NULL || (*headRef)->next == NULL)
        return;

    Node* current = (*headRef)->next;
    while (current != NULL) {
        int key = current->data;
        Node* prev = current->prev;

        // Move elements of the sorted segment that are greater than key
        while (prev != NULL && prev->data > key) {
            prev->next->data = prev->data;
            prev = prev->prev;
        }

        // Insert the key at the correct position
        if (prev == NULL)
            (*headRef)->data = key;
        else
            prev->next->data = key;

        current = current->next;
    }
}

// Helper function to split the list into two halves
void splitList(Node* source, Node** frontRef, Node** backRef) {
    Node* slow = source;
    Node* fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
    if (*backRef != NULL)
        (*backRef)->prev = NULL;
}

// Helper function to merge two sorted halves
Node* mergeSorted(Node* a, Node* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    Node* result = NULL;

    if (a->data <= b->data) {
        result = a;
        result->next = mergeSorted(a->next, b);
        result->next->prev = result;
        result->prev = NULL;
    } else {
        result = b;
        result->next = mergeSorted(a, b->next);
        result->next->prev = result;
        result->prev = NULL;
    }
    return result;
}

// Merge Sort for Doubly Linked List
void mergeSort(Node** headRef) {
    if (*headRef == NULL || (*headRef)->next == NULL)
        return;

    Node* head = *headRef;
    Node* a;
    Node* b;

    splitList(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = mergeSorted(a, b);
}

// Quick Sort for Doubly Linked List
Node* partition(Node* low, Node* high) {
    int pivot = high->data;
    Node* i = low->prev;

    for (Node* j = low; j != high; j = j->next) {
        if (j->data <= pivot) {
            i = (i == NULL) ? low : i->next;
            int temp = i->data;
            i->data = j->data;
            j->data = temp;
        }
    }
    i = (i == NULL) ? low : i->next;
    int temp = i->data;
    i->data = high->data;
    high->data = temp;

    return i;
}

void quickSortRec(Node* low, Node* high) {
    if (low && high && low != high && low != high->next) {
        Node* pivot = partition(low, high);
        quickSortRec(low, pivot->prev);
        quickSortRec(pivot->next, high);
    }
}

void quickSort(Node** headRef) {
    Node* tail = *headRef;
    while (tail && tail->next) {
        tail = tail->next;
    }
    quickSortRec(*headRef, tail);
}

int main() {
    // 이중 연결 리스트 생성
    DoublyLinkedList* list = createDoublyLinkedList();

    // 1. append: 리스트 끝에 노드 추가
    append(list, 3);
    append(list, 1);
    append(list, 4);
    append(list, 2);
    printf("After append operations (3, 1, 4, 2):\n");
    printList(list);            // Output: 3 -> 1 -> 4 -> 2 -> NULL
    printReverse(list);         // Output: 2 <- 4 <- 1 <- 3 <- NULL

    // 2. prepend: 리스트 처음에 노드 추가
    prepend(list, 0);
    printf("\nAfter prepend operation (0):\n");
    printList(list);            // Output: 0 -> 3 -> 1 -> 4 -> 2 -> NULL
    printReverse(list);         // Output: 2 <- 4 <- 1 <- 3 <- 0 <- NULL

    // 3. insertAfter: 특정 값 뒤에 노드 삽입
    insertAfter(list, 3, 5);
    printf("\nAfter inserting 5 after 3:\n");
    printList(list);            // Output: 0 -> 3 -> 5 -> 1 -> 4 -> 2 -> NULL
    printReverse(list);         // Output: 2 <- 4 <- 1 <- 5 <- 3 <- 0 <- NULL

    // 4. deleteNode: 특정 값을 가진 노드 삭제
    deleteNode(list, 5);
    printf("\nAfter deleting 5:\n");
    printList(list);            // Output: 0 -> 3 -> 1 -> 4 -> 2 -> NULL
    printReverse(list);         // Output: 2 <- 4 <- 1 <- 3 <- 0 <- NULL

    // 5. search: 리스트에서 특정 값 검색
    printf("\nSearch for 4: %s\n", search(list, 4) ? "Found" : "Not Found");  // Output: Found
    printf("Search for 7: %s\n", search(list, 7) ? "Found" : "Not Found");    // Output: Not Found

    // 6. reverse: 리스트를 뒤집음
    reverse(list);
    printf("\nAfter reversing the list:\n");
    printList(list);            // Output: 2 -> 4 -> 1 -> 3 -> 0 -> NULL
    printReverse(list);         // Output: 0 <- 3 <- 1 <- 4 <- 2 <- NULL

    // 7. Sorting: Bubble Sort
    bubbleSort(&list->head);
    printf("\nAfter Bubble Sort:\n");
    printList(list);            // Output: 0 -> 1 -> 2 -> 3 -> 4 -> NULL
    printReverse(list);         // Output: 4 <- 3 <- 2 <- 1 <- 0 <- NULL

    // 8. Sorting: Selection Sort
    append(list, 3);
    append(list, 1);
    printf("\nAfter adding 3 and 1 for Selection Sort:\n");
    printList(list);            // Output: 0 -> 1 -> 2 -> 3 -> 4 -> 3 -> 1 -> NULL

    selectionSort(&list->head);
    printf("\nAfter Selection Sort:\n");
    printList(list);            // Output: 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> NULL
    printReverse(list);         // Output: 4 <- 3 <- 3 <- 2 <- 1 <- 1 <- 0 <- NULL

    // 9. Sorting: Insertion Sort
    append(list, 5);
    append(list, 0);
    printf("\nAfter adding 5 and 0 for Insertion Sort:\n");
    printList(list);            // Output: 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> 0 -> NULL

    insertionSort(&list->head);
    printf("\nAfter Insertion Sort:\n");
    printList(list);            // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> NULL
    printReverse(list);         // Output: 5 <- 4 <- 3 <- 3 <- 2 <- 1 <- 1 <- 0 <- 0 <- NULL

    // 10. Sorting: Merge Sort
    printf("\nAfter Merge Sort:\n");
    mergeSort(&list->head);
    printList(list);            // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> NULL

    // 11. Sorting: Quick Sort
    append(list, 6);
    append(list, 2);
    printf("\nAfter adding 6 and 2 for Quick Sort:\n");
    printList(list);            // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> 6 -> 2 -> NULL

    quickSort(&list->head);
    printf("\nAfter Quick Sort:\n");
    printList(list);            // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 2 -> 3 -> 3 -> 4 -> 5 -> 6 -> NULL

    // 메모리 해제
    freeList(list);

    return 0;
}
