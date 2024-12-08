// append: 리스트 끝에 노드 추가.
// prepend: 리스트 처음에 노드 추가.
// insertAfter: 특정 값 뒤에 노드 삽입.
// deleteNode: 특정 값을 가진 노드 삭제.
// search: 리스트에서 특정 값 검색.
// size: 리스트의 노드 개수 반환.
// reverse: 리스트를 뒤집음.
// printList: 리스트를 보기 좋게 출력.
// freeList: 메모리 해제.
// Sorting: Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node 구조체 정의
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 단일 연결 리스트 구조체 정의
typedef struct LinkedList {
    Node* head;
} LinkedList;

// 연결 리스트 초기화
LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

// 노드 생성
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 리스트 끝에 노드 추가
void append(LinkedList* list, int data) {
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
}

// 리스트 처음에 노드 추가
void prepend(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
}

// 특정 값 뒤에 노드 삽입
void insertAfter(LinkedList* list, int prevData, int data) {
    Node* temp = list->head;
    while (temp != NULL && temp->data != prevData) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Error: Node with data %d not found.\n", prevData);
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = temp->next;
    temp->next = newNode;
}

// 특정 값을 가진 노드 삭제
void deleteNode(LinkedList* list, int data) {
    if (list->head == NULL) {
        printf("Error: List is empty.\n");
        return;
    }
    if (list->head->data == data) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return;
    }
    Node* temp = list->head;
    while (temp->next != NULL && temp->next->data != data) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Error: Node with data %d not found.\n", data);
        return;
    }
    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    free(nodeToDelete);
}

// 리스트에서 특정 값 검색
bool search(LinkedList* list, int data) {
    Node* temp = list->head;
    while (temp != NULL) {
        if (temp->data == data) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// 리스트 크기 반환
int size(LinkedList* list) {
    int count = 0;
    Node* temp = list->head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// 리스트 반전
void reverse(LinkedList* list) {
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

// 리스트 출력
void printList(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// 리스트 메모리 해제
void freeList(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    free(list);
}

// Bubble Sort
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

// Selection Sort for Singly Linked List
void selectionSort(Node** headRef) {
    Node* current = *headRef;

    while (current != NULL) {
        Node* minNode = current;
        Node* nextNode = current->next;

        while (nextNode != NULL) {
            if (nextNode->data < minNode->data) {
                minNode = nextNode;
            }
            nextNode = nextNode->next;
        }

        // Swap data between current node and minNode
        if (minNode != current) {
            int temp = current->data;
            current->data = minNode->data;
            minNode->data = temp;
        }

        current = current->next;
    }
}

// Insertion Sort
void insertionSort(Node** headRef) {
    Node* sorted = NULL;
    Node* current = *headRef;

    while (current != NULL) {
        Node* next = current->next;

        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    *headRef = sorted;
}

// Merge Sort Helper: Split the list into two halves
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
}

// Merge Sort Helper: Merge two sorted lists
Node* sortedMerge(Node* a, Node* b) {
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;

    Node* result;
    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

// Merge Sort
void mergeSort(Node** headRef) {
    Node* head = *headRef;
    if (head == NULL || head->next == NULL)
        return;

    Node* a;
    Node* b;

    splitList(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = sortedMerge(a, b);
}

// Helper function (for Quick Sort) to get the tail of the list
Node* getTail(Node* current) {
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    return current;
}

// Partition function for Quick Sort
Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node* prev = NULL;
    Node* current = head;
    Node* tail = pivot;

    while (current != pivot) {
        if (current->data < pivot->data) {
            if (*newHead == NULL) {
                *newHead = current;
            }
            prev = current;
            current = current->next;
        } else {
            if (prev != NULL) {
                prev->next = current->next;
            }
            Node* temp = current->next;
            current->next = NULL;
            tail->next = current;
            tail = current;
            current = temp;
        }
    }

    if (*newHead == NULL) {
        *newHead = pivot;
    }
    *newEnd = tail;

    return pivot;
}

// Quick Sort recursive function
Node* quickSortRec(Node* head, Node* end) {
    if (head == NULL || head == end) {
        return head;
    }

    Node* newHead = NULL;
    Node* newEnd = NULL;

    Node* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Node* temp = newHead;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = NULL;

        newHead = quickSortRec(newHead, temp);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRec(pivot->next, newEnd);

    return newHead;
}

// Quick Sort
void quickSort(Node** headRef) {
    *headRef = quickSortRec(*headRef, getTail(*headRef));
}

int main() {
    // 연결 리스트 생성
    LinkedList* list = createLinkedList();

    // 1. append: 리스트 끝에 노드 추가
    append(list, 3);
    append(list, 1);
    append(list, 4);
    append(list, 2);
    printf("After append operations (3, 1, 4, 2):\n");
    printList(list);  // Output: 3 -> 1 -> 4 -> 2 -> NULL

    // 2. prepend: 리스트 처음에 노드 추가
    prepend(list, 0);
    printf("\nAfter prepend operation (0):\n");
    printList(list);  // Output: 0 -> 3 -> 1 -> 4 -> 2 -> NULL

    // 3. insertAfter: 특정 값 뒤에 노드 삽입
    insertAfter(list, 3, 5);
    printf("\nAfter inserting 5 after 3:\n");
    printList(list);  // Output: 0 -> 3 -> 5 -> 1 -> 4 -> 2 -> NULL

    // 4. deleteNode: 특정 값을 가진 노드 삭제
    deleteNode(list, 5);
    printf("\nAfter deleting 5:\n");
    printList(list);  // Output: 0 -> 3 -> 1 -> 4 -> 2 -> NULL

    // 5. search: 리스트에서 특정 값 검색
    printf("\nSearch for 4: %s\n", search(list, 4) ? "Found" : "Not Found");  // Output: Found
    printf("Search for 7: %s\n", search(list, 7) ? "Found" : "Not Found");    // Output: Not Found

    // 6. size: 리스트의 노드 개수 반환
    printf("\nSize of the list: %d\n", size(list));  // Output: 5

    // 7. reverse: 리스트를 뒤집음
    reverse(list);
    printf("\nAfter reversing the list:\n");
    printList(list);  // Output: 2 -> 4 -> 1 -> 3 -> 0 -> NULL

    // 8. Sorting: Bubble Sort
    bubbleSort(&list->head);
    printf("\nAfter Bubble Sort:\n");
    printList(list);  // Output: 0 -> 1 -> 2 -> 3 -> 4 -> NULL

    // 9. Sorting: Selection Sort
    append(list, 3);
    append(list, 1);
    printf("\nAfter adding 3 and 1 for Selection Sort:\n");
    printList(list);  // Output: 0 -> 1 -> 2 -> 3 -> 4 -> 3 -> 1 -> NULL

    selectionSort(&list->head);
    printf("\nAfter Selection Sort:\n");
    printList(list);  // Output: 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> NULL

    // 10. Sorting: Insertion Sort
    append(list, 5);
    append(list, 0);
    printf("\nAfter adding 5 and 0 for Insertion Sort:\n");
    printList(list);  // Output: 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> 0 -> NULL

    insertionSort(&list->head);
    printf("\nAfter Insertion Sort:\n");
    printList(list);  // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> NULL

    // 11. Sorting: Merge Sort
    printf("\nAfter Merge Sort:\n");
    mergeSort(&list->head);
    printList(list);  // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> NULL

    // 12. Sorting: Quick Sort
    append(list, 6);
    append(list, 2);
    printf("\nAfter adding 6 and 2 for Quick Sort:\n");
    printList(list);  // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> 6 -> 2 -> NULL

    quickSort(&list->head);
    printf("\nAfter Quick Sort:\n");
    printList(list);  // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 2 -> 3 -> 3 -> 4 -> 5 -> 6 -> NULL

    // 메모리 해제
    freeList(list);

    return 0;
}
