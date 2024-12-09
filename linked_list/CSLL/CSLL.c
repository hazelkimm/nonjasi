/*
void initList(CircularSinglyLinkedList* list): 리스트 초기화
void addNode(CircularSinglyLinkedList* list, int data): 새로운 노드를 추가하는 함수
void displayList(CircularSinglyLinkedList* list): 리스트 출력 함수
Node* findNode(CircularSinglyLinkedList* list, int data): 특정 값을 가진 노드를 찾는 함수
int findNode2(CircularSinglyLinkedList* list, int data): 특정 값을 가진 노드가 리스트에 있는지 확인하는 함수
int getLength(CircularSinglyLinkedList* list): 리스트의 길이를 반환하는 함수
void deleteNode(CircularSinglyLinkedList* list, int data): 특정 값을 가진 노드를 삭제하는 함수
int isCircular(CircularSinglyLinkedList* list): 순환 구조 여부를 확인하는 함수
void traverseList(CircularSinglyLinkedList* list): 리스트를 순회하며 모든 노드를 방문하는 함수
Node* findMiddleNode(CircularSinglyLinkedList* list): 순환 리스트에서 중간 노드를 찾는 함수
void insertAtPosition(CircularSinglyLinkedList* list, int data, int position): 주어진 위치에 노드를 삽입하는 함수
void removeAtPosition(CircularSinglyLinkedList* list, int position): 주어진 위치의 노드를 삭제하는 함수
void reverseList(CircularSinglyLinkedList* list): 리스트의 순서를 뒤집는 함수.
int detectCycle(CircularSinglyLinkedList* list): 리스트에 순환이 있는지 탐지하는 함수 (Floyd’s Cycle Detection Algorithm).
void splitList(CircularSinglyLinkedList* list, CircularSinglyLinkedList* list1, CircularSinglyLinkedList* list2): 순환 리스트를 두 개의 리스트로 분할하는 함수.
void mergeList(CircularSinglyLinkedList* list1, CircularSinglyLinkedList* list2): 두 개의 순환 리스트를 병합하는 함수.
CircularSinglyLinkedList* copyList(CircularSinglyLinkedList* list): 현재 리스트의 복사본을 생성하는 함수.
Node* getNodeAtPosition(CircularSinglyLinkedList* list, int position): 특정 위치에 있는 노드를 반환하는 함수.
Node* getLastNode(CircularSinglyLinkedList* list): 리스트의 마지막 노드를 반환하는 함수.
void rotateList(CircularSinglyLinkedList* list, int steps): 리스트를 주어진 단계만큼 회전시키는 함수.  (steps, 양수는 오른쪽 회전, 음수는 왼쪽 회전).
void clearList(CircularSinglyLinkedList* list): 리스트의 모든 노드를 제거하는 함수.
*/


#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 순환 단일 연결 리스트 구조체 정의
typedef struct {
    Node* head;
} CircularSinglyLinkedList;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void initList(CircularSinglyLinkedList* list): 리스트 초기화
void initList(CircularSinglyLinkedList* list) {
    list->head = NULL;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void addNode(CircularSinglyLinkedList* list, int data): 새로운 노드를 추가하는 함수
void addNode(CircularSinglyLinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        // 리스트가 비어 있는 경우
        list->head = newNode;
        newNode->next = newNode; // 순환 연결
    } else {
        Node* current = list->head;
        // 마지막 노드로 이동
        while (current->next != list->head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = list->head; // 순환 연결
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void displayList(CircularSinglyLinkedList* list): 리스트 출력 함수
void displayList(CircularSinglyLinkedList* list) {
    if (list->head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node* current = list->head;
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("(head)\n");
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Node* findNode(CircularSinglyLinkedList* list, int data): 특정 값을 가진 노드를 찾는 함수
Node* findNode(CircularSinglyLinkedList* list, int data) {
    if (list->head == NULL) {
        return NULL;
    }

    Node* current = list->head;
    do {
        if (current->data == data) {
            return current; // 해당 노드를 반환
        }
        current = current->next;
    } while (current != list->head);
    return NULL; // 찾지 못한 경우
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int findNode2(CircularSinglyLinkedList* list, int data): 특정 값을 가진 노드가 리스트에 있는지 확인하는 함수
int findNode2(CircularSinglyLinkedList* list, int data) {
    if (list->head == NULL) {
        return 0; // 리스트가 비어 있으면 False (0)
    }

    Node* current = list->head;
    do {
        if (current->data == data) {
            return 1; // True (1): 데이터를 찾음
        }
        current = current->next;
    } while (current != list->head);
    return 0; // False (0): 데이터를 찾지 못함
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int getLength(CircularSinglyLinkedList* list): 리스트의 길이를 반환하는 함수
int getLength(CircularSinglyLinkedList* list) {
    if (list->head == NULL) {
        return 0;
    }

    int count = 0;
    Node* current = list->head;
    do {
        count++;
        current = current->next;
    } while (current != list->head);
    return count;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void deleteNode(CircularSinglyLinkedList* list, int data): 특정 값을 가진 노드를 삭제하는 함수
void deleteNode(CircularSinglyLinkedList* list, int data) {
    if (list->head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node* current = list->head;
    Node* prev = NULL;

    // 경우 1: 삭제할 노드가 head인 경우
    if (current->data == data) {
        // 마지막 노드로 이동
        while (current->next != list->head) {
            current = current->next;
        }
        if (current == list->head) {
            // 리스트에 단 하나의 노드만 있는 경우
            free(list->head);
            list->head = NULL;
        } else {
            current->next = list->head->next; // 마지막 노드 연결 변경
            free(list->head);
            list->head = current->next; // head 갱신
        }
        return;
    }

    // 경우 2: 중간이나 끝에서 삭제할 노드를 찾는 경우
    current = list->head;
    do {
        if (current->data == data) {
            prev->next = current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    } while (current != list->head);

    printf("Node not found.\n");
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int isCircular(CircularSinglyLinkedList* list): 순환 구조 여부를 확인하는 함수
int isCircular(CircularSinglyLinkedList* list) {
    if (list->head == NULL) {
        return 0; // False: 리스트가 비어 있음
    }

    Node* current = list->head->next;
    while (current != NULL) {
        if (current == list->head) {
            return 1; // True: 순환 구조 확인
        }
        current = current->next;
    }
    return 0; // False: 순환 구조 아님
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void traverseList(CircularSinglyLinkedList* list): 리스트를 순회하며 모든 노드를 방문하는 함수
void traverseList(CircularSinglyLinkedList* list) {
    if (list->head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("Traversing the list:\n");
    Node* current = list->head;
    while (1) {
        printf("%d -> ", current->data);
        current = current->next;
        if (current == list->head) {
            break; // 순환이 끝나면 종료
        }
    }
    printf("(head)\n");
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Node* findMiddleNode(CircularSinglyLinkedList* list): 순환 리스트에서 중간 노드를 찾는 함수
Node* findMiddleNode(CircularSinglyLinkedList* list) {
    if (list->head == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    Node* slow = list->head;
    Node* fast = list->head;

    while (fast->next != list->head && fast->next->next != list->head) {
        slow = slow->next;           // 느린 포인터는 한 칸 이동
        fast = fast->next->next;     // 빠른 포인터는 두 칸 이동
    }

    printf("The middle node is: %d\n", slow->data);
    return slow;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void insertAtPosition(CircularSinglyLinkedList* list, int data, int position): 주어진 위치에 노드를 삽입하는 함수
void insertAtPosition(CircularSinglyLinkedList* list, int data, int position) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    // 리스트가 비어 있는 경우
    if (list->head == NULL) {
        if (position == 0) {
            list->head = newNode;
            newNode->next = newNode; // 자기 자신을 가리킴
        } else {
            printf("Invalid position for an empty list.\n");
        }
        return;
    }

    // 위치가 0이면 head 앞에 노드 삽입
    if (position == 0) {
        Node* current = list->head;
        while (current->next != list->head) { // 마지막 노드를 찾음
            current = current->next;
        }
        current->next = newNode;
        newNode->next = list->head;
        list->head = newNode;
        return;
    }

    // 중간 또는 끝에 삽입
    Node* current = list->head;
    int count = 0;
    while (count < position - 1 && current->next != list->head) {
        current = current->next;
        count++;
    }

    if (count == position - 1) {
        newNode->next = current->next;
        current->next = newNode;
    } else {
        printf("Position out of range.\n");
        free(newNode);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void removeAtPosition(CircularSinglyLinkedList* list, int position): 주어진 위치의 노드를 삭제하는 함수
void removeAtPosition(CircularSinglyLinkedList* list, int position) {
    if (list->head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node* current = list->head;

    // 위치가 0인 경우 head를 삭제
    if (position == 0) {
        if (current->next == list->head) { // 리스트에 노드가 하나인 경우
            free(current);
            list->head = NULL;
        } else {
            Node* temp = current;
            while (current->next != list->head) { // 마지막 노드를 찾음
                current = current->next;
            }
            current->next = list->head->next;
            list->head = list->head->next;
            free(temp);
        }
        return;
    }

    // 중간 또는 끝에서 삭제
    Node* prev = NULL;
    int count = 0;
    while (count < position && current->next != list->head) {
        prev = current;
        current = current->next;
        count++;
    }

    if (count == position) {
        prev->next = current->next;
        free(current);
    } else {
        printf("Position out of range.\n");
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void reverseList(CircularSinglyLinkedList* list): 리스트의 순서를 뒤집는 함수
void reverseList(CircularSinglyLinkedList* list) {
    if (!list->head || list->head->next == list->head) {
        return; // 노드가 0개 또는 1개인 경우
    }

    Node *prev = NULL, *current = list->head, *next_node = NULL;

    do {
        next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;
    } while (current != list->head);

    list->head->next = prev; // 기존 head의 next를 마지막 노드로 설정
    list->head = prev;       // 새로운 head로 갱신
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int detectCycle(CircularSinglyLinkedList* list): 리스트에 순환이 있는지 탐지하는 함수 (Floyd’s Cycle Detection Algori
int detectCycle(CircularSinglyLinkedList* list) {
    if (!list->head) {
        // 리스트가 비어있는 경우, 순환이 있을 수 없음
        return 0;
    }

    Node *slow = list->head; // 한 번에 한 칸씩 이동하는 느린 포인터
    Node *fast = list->head; // 한 번에 두 칸씩 이동하는 빠른 포인터

    while (fast && fast->next) {
        slow = slow->next;        // 느린 포인터는 한 칸 이동
        fast = fast->next->next;  // 빠른 포인터는 두 칸 이동

        if (slow == fast) {
            // 두 포인터가 만나면 순환이 존재
            return 1;
        }
    }

    // 빠른 포인터가 리스트 끝에 도달하면 순환이 없음
    return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void splitList(CircularSinglyLinkedList* list, CircularSinglyLinkedList* list1, CircularSinglyLinkedList* list2): 순환 리스트
void splitList(CircularSinglyLinkedList* list, CircularSinglyLinkedList* list1, CircularSinglyLinkedList* list2) {
    if (!list->head || list->head->next == list->head) {
        // 리스트가 비어있거나 노드가 하나뿐인 경우 분할 불가
        printf("Cannot split a list with fewer than 2 nodes.\n");
        list1->head = NULL;
        list2->head = NULL;
        return;
    }

    Node *slow = list->head; // 느린 포인터: 한 칸씩 이동
    Node *fast = list->head; // 빠른 포인터: 두 칸씩 이동

    // 빠른 포인터가 리스트를 끝까지 순회할 때까지 반복
    while (fast->next != list->head && fast->next->next != list->head) {
        slow = slow->next;       // 느린 포인터 이동
        fast = fast->next->next; // 빠른 포인터 이동
    }

    // 두 리스트의 헤드 설정
    list1->head = list->head;     // 첫 번째 리스트는 기존 리스트의 시작 노드에서 시작
    list2->head = slow->next;     // 두 번째 리스트는 느린 포인터의 다음 노드에서 시작
    slow->next = list1->head;     // 첫 번째 리스트를 원형으로 만듦

    // 두 번째 리스트를 원형으로 만듦
    Node* current = list2->head;
    while (current->next != list->head) {
        current = current->next;
    }
    current->next = list2->head;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void mergeList(CircularSinglyLinkedList* list1, CircularSinglyLinkedList* list2): 두 개의 순환 리스트를 병합하는 함수
void mergeList(CircularSinglyLinkedList* list1, CircularSinglyLinkedList* list2) {
    if (!list1->head) {
        // 첫 번째 리스트가 비어있으면 두 번째 리스트가 병합된 결과가 됨
        list1->head = list2->head;
        return;
    }
    if (!list2->head) {
        // 두 번째 리스트가 비어있으면 아무 작업도 필요 없음
        return;
    }

    // 첫 번째 리스트의 마지막 노드를 찾음
    Node* current1 = list1->head;
    while (current1->next != list1->head) {
        current1 = current1->next;
    }

    // 두 번째 리스트의 마지막 노드를 찾음
    Node* current2 = list2->head;
    while (current2->next != list2->head) {
        current2 = current2->next;
    }

    // 리스트를 병합
    current1->next = list2->head; // 첫 번째 리스트의 끝에 두 번째 리스트의 시작 연결
    current2->next = list1->head; // 두 번째 리스트의 끝을 첫 번째 리스트의 시작으로 연결
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CircularSinglyLinkedList* copyList(CircularSinglyLinkedList* list): 현재 리스트의 복사본을 생성하는 함수
CircularSinglyLinkedList* copyList(CircularSinglyLinkedList* list) {
    CircularSinglyLinkedList* newList = (CircularSinglyLinkedList*)malloc(sizeof(CircularSinglyLinkedList));
    newList->head = NULL;

    if (!list->head) {
        return newList;
    }

    Node* current = list->head;
    Node* newNode = NULL;
    Node* tail = NULL;

    do {
        newNode = (Node*)malloc(sizeof(Node));
        newNode->data = current->data;
        newNode->next = NULL;

        if (!newList->head) {
            newList->head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        current = current->next;
    } while (current != list->head);

    tail->next = newList->head; // 원형 연결 설정
    return newList;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Node* getNodeAtPosition(CircularSinglyLinkedList* list, int position): 특정 위치에 있는 노드를 반환하는 함수
Node* getNodeAtPosition(CircularSinglyLinkedList* list, int position) {
    if (!list->head) {
        printf("The list is empty.\n");
        return NULL;
    }

    int length = 0;
    Node* current = list->head;

    do {
        length++;
        current = current->next;
    } while (current != list->head);

    position %= length; // 유효한 위치로 변환

    current = list->head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    return current;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Node* getLastNode(CircularSinglyLinkedList* list): 리스트의 마지막 노드를 반환하는 함수
Node* getLastNode(CircularSinglyLinkedList* list) {
    if (!list->head) {
        printf("The list is empty.\n");
        return NULL;
    }

    Node* current = list->head;
    while (current->next != list->head) {
        current = current->next;
    }
    return current;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void rotateList(CircularSinglyLinkedList* list, int steps): 리스트를 주어진 단계만큼 회전시키는 함수.  (steps, 양수는 오른쪽 회전, 음수는 왼쪽 회전).
void rotateList(CircularSinglyLinkedList* list, int steps) {
    if (!list->head || list->head->next == list->head) {
        return;
    }

    int length = 0;
    Node* current = list->head;
    do {
        length++;
        current = current->next;
    } while (current != list->head);

    steps %= length; // 유효한 단계로 변환
    if (steps == 0) {
        return;
    }

    int newTailPosition = length - steps;
    Node* newTail = getNodeAtPosition(list, newTailPosition - 1);

    Node* newHead = newTail->next;
    Node* lastNode = getLastNode(list);

    lastNode->next = newHead;
    newTail->next = list->head;
    list->head = newHead;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void clearList(CircularSinglyLinkedList* list): 리스트의 모든 노드를 제거하는 함수
void clearList(CircularSinglyLinkedList* list) {
    if (!list->head) {
        printf("The list is already empty.\n");
        return;
    }

    Node* current = list->head;
    Node* nextNode;

    while (current->next != list->head) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    free(current);
    list->head = NULL;
}