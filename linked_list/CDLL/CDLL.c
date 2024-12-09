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
    int data;            // 노드가 저장할 데이터
    struct Node* next;   // 다음 노드를 가리키는 포인터
    struct Node* prev;   // 이전 노드를 가리키는 포인터
} Node;

// 원형 이중 연결 리스트 구조체 정의
typedef struct {
    Node* head;  // 리스트의 첫 번째 노드를 가리킴 (head)
    Node* tail;  // 리스트의 마지막 노드를 가리킴 (tail)
} CircularDoublyLinkedList;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void initList(CircularDoublyLinkedList* list): 리스트 초기화
void initList(CircularDoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void addNode(CircularDoublyLinkedList* list, int data): 새로운 노드를 추가하는 함수
void addNode(CircularDoublyLinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode;  // 초기에는 자기 자신을 가리킴
    newNode->prev = newNode;  // 초기에는 자기 자신을 가리킴

    if (list->head == NULL) {
        // 리스트가 비어 있는 경우
        list->head = newNode;
        list->tail = newNode;
    } else {
        // 리스트에 노드가 이미 있는 경우
        newNode->next = list->head;
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->head->prev = newNode;
        list->tail = newNode;  // 새 노드를 tail로 설정
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void displayList(CircularDoublyLinkedList* list): 리스트 출력 함수
void displayList(CircularDoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node* current = list->head;
    do {
        printf("%d <-> ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("(head)\n");
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Node* findNode(CircularDoublyLinkedList* list, int data): 특정 값을 가진 노드를 찾는 함수
Node* findNode(CircularDoublyLinkedList* list, int data) {
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int findNode2(CircularDoublyLinkedList* list, int data): 특정 값을 가진 노드가 리스트에 있는지 확인하는 함수
int findNode2(CircularDoublyLinkedList* list, int data) {
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int getLength(CircularDoublyLinkedList* list): 리스트의 길이를 반환하는 함수
int getLength(CircularDoublyLinkedList* list) {
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void deleteNode(CircularDoublyLinkedList* list, int data): 특정 값을 가진 노드를 삭제하는 함수
void deleteNode(CircularDoublyLinkedList* list, int data) {
    if (list->head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node* current = list->head;

    // 경우 1: 삭제할 노드가 head인 경우
    if (current->data == data) {
        if (current->next == current) {
            // 리스트에 단 하나의 노드만 있는 경우
            free(list->head);
            list->head = NULL;
            list->tail = NULL;
        } else {
            list->head = current->next;
            list->head->prev = list->tail;
            list->tail->next = list->head;
            free(current);
        }
        return;
    }

    // 경우 2: 중간이나 끝에서 삭제할 노드를 찾는 경우
    do {
        if (current->data == data) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            if (current == list->tail) {
                list->tail = current->prev;
            }
            free(current);
            return;
        }
        current = current->next;
    } while (current != list->head);

    printf("Node not found.\n");
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int isCircular(CircularDoublyLinkedList* list): 순환 구조 여부를 확인하는 함수
int isCircular(CircularDoublyLinkedList* list) {
    if (list->head == NULL) {
        return 0; // False: 리스트가 비어 있음
    }

    // 리스트의 첫 번째 노드에서 순환 여부 확인
    if (list->head->prev != list->tail || list->tail->next != list->head) {
        return 0; // 순환 구조 아님
    }
    return 1; // True: 순환 구조
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void traverseList(CircularDoublyLinkedList* list): 리스트를 순회하며 모든 노드를 방문하는 함수
void traverseList(CircularDoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("Traversing the list:\n");
    Node* current = list->head;
    do {
        printf("%d <-> ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("(head)\n");
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Node* findMiddleNode(CircularDoublyLinkedList* list): 순환 리스트에서 중간 노드를 찾는 함수
Node* findMiddleNode(CircularDoublyLinkedList* list) {
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void insertAtPosition(CircularDoublyLinkedList* list, int data, int position): 주어진 위치에 노드를 삽입하는 함수
void insertAtPosition(CircularDoublyLinkedList* list, int data, int position) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    // 리스트가 비어 있는 경우
    if (list->head == NULL) {
        if (position == 0) {
            list->head = newNode;
            list->tail = newNode;
            newNode->next = newNode;  // 자기 자신을 가리킴
            newNode->prev = newNode;  // 자기 자신을 가리킴
        } else {
            printf("Invalid position for an empty list.\n");
        }
        return;
    }

    if (position == 0) {
        // 위치가 0이면 head 앞에 노드 삽입
        newNode->next = list->head;
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->head->prev = newNode;
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
        newNode->prev = current;
        if (current->next != list->head) {
            current->next->prev = newNode;
        } else {
            list->tail = newNode;  // 마지막 노드 삽입 시 tail 갱신
        }
        current->next = newNode;
    } else {
        printf("Position out of range.\n");
        free(newNode);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void removeAtPosition(CircularDoublyLinkedList* list, int position): 주어진 위치의 노드를 삭제하는 함수
void removeAtPosition(CircularDoublyLinkedList* list, int position) {
    if (list->head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node* current = list->head;

    if (position == 0) {
        // 위치가 0인 경우 head를 삭제
        if (current->next == list->head) { // 리스트에 노드가 하나인 경우
            free(current);
            list->head = NULL;
            list->tail = NULL;
        } else {
            Node* temp = current;
            list->head = current->next;
            list->head->prev = list->tail;
            list->tail->next = list->head;
            free(temp);
        }
        return;
    }

    Node* prev = NULL;
    int count = 0;
    while (count < position && current->next != list->head) {
        prev = current;
        current = current->next;
        count++;
    }

    if (count == position) {
        prev->next = current->next;
        if (current->next != list->head) {
            current->next->prev = prev;
        } else {
            list->tail = prev;  // 삭제한 노드가 tail일 경우 tail 갱신
        }
        free(current);
    } else {
        printf("Position out of range.\n");
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void reverseList(CircularDoublyLinkedList* list): 리스트의 순서를 뒤집는 함수
void reverseList(CircularDoublyLinkedList* list) {
    if (!list->head || list->head == list->tail) {
        // 리스트가 비어있거나 노드가 하나뿐인 경우
        return;
    }

    Node* current = list->head;
    Node* temp = NULL;

    do {
        // 노드의 next와 prev 포인터를 반전
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    } while (current != list->head);

    // 리스트의 head와 tail 포인터 교환
    temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int detectCycle(CircularDoublyLinkedList* list): 리스트에 순환이 있는지 탐지하는 함수 (Floyd’s Cycle Detection Algorithm)
int detectCycle(CircularDoublyLinkedList* list) {
    if (!list->head) {
        return 0; // 리스트가 비어있으면 순환이 있을 수 없음
    }

    Node* slow = list->head; // 한 번에 한 칸씩 이동하는 느린 포인터
    Node* fast = list->head; // 한 번에 두 칸씩 이동하는 빠른 포인터

    do {
        if (!fast || !fast->next) {
            return 0; // 빠른 포인터가 NULL이면 순환이 없음
        }
        slow = slow->next;
        fast = fast->next->next;
    } while (slow != fast);

    // 두 포인터가 만나면 순환이 존재
    return 1;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void splitList(CircularDoublyLinkedList* list, CircularDoublyLinkedList* list1, CircularDoublyLinkedList* list2): 순환 리스트를 반으로 나누는 함수
void splitList(CircularDoublyLinkedList* list, CircularDoublyLinkedList* list1, CircularDoublyLinkedList* list2) {
    if (!list->head || list->head == list->tail) {
        printf("Cannot split a list with fewer than 2 nodes.\n");
        list1->head = NULL;
        list1->tail = NULL;
        list2->head = NULL;
        list2->tail = NULL;
        return;
    }

    Node* slow = list->head; // 느린 포인터
    Node* fast = list->head; // 빠른 포인터

    // 빠른 포인터가 리스트를 끝까지 순회할 때까지 반복
    while (fast->next != list->head && fast->next->next != list->head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 첫 번째 리스트와 두 번째 리스트의 헤드 설정
    list1->head = list->head;
    list1->tail = slow;
    list2->head = slow->next;
    list2->tail = list->tail;

    // 리스트 연결 해제 및 새 리스트 설정
    list1->tail->next = list1->head;
    list1->head->prev = list1->tail;

    list2->tail->next = list2->head;
    list2->head->prev = list2->tail;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void mergeList(CircularDoublyLinkedList* list1, CircularDoublyLinkedList* list2): 두 개의 순환 리스트를 병합하는 함수
void mergeList(CircularDoublyLinkedList* list1, CircularDoublyLinkedList* list2) {
    if (!list1->head) {
        // 첫 번째 리스트가 비어있으면 두 번째 리스트가 병합된 결과가 됨
        list1->head = list2->head;
        list1->tail = list2->tail;
        return;
    }
    if (!list2->head) {
        // 두 번째 리스트가 비어있으면 아무 작업도 필요 없음
        return;
    }

    // 첫 번째 리스트의 마지막 노드 찾기
    list1->tail->next = list2->head;
    list2->head->prev = list1->tail;

    // 두 번째 리스트의 마지막 노드 찾기
    list2->tail->next = list1->head;
    list1->head->prev = list2->tail;

    // 새로운 tail 설정
    list1->tail = list2->tail;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CircularDoublyLinkedList* copyList(CircularDoublyLinkedList* list): 현재 리스트의 복사본을 생성하는 함수
CircularDoublyLinkedList* copyList(CircularDoublyLinkedList* list) {
    CircularDoublyLinkedList* newList = (CircularDoublyLinkedList*)malloc(sizeof(CircularDoublyLinkedList));
    newList->head = NULL;
    newList->tail = NULL;

    if (!list->head) {
        return newList; // 원본 리스트가 비어있으면 빈 리스트 반환
    }

    Node* current = list->head;
    Node* newNode = NULL;

    do {
        newNode = (Node*)malloc(sizeof(Node));
        newNode->data = current->data;
        newNode->next = NULL;
        newNode->prev = NULL;

        if (!newList->head) {
            newList->head = newNode;
            newList->tail = newNode;
        } else {
            newList->tail->next = newNode;
            newNode->prev = newList->tail;
            newList->tail = newNode;
        }

        current = current->next;
    } while (current != list->head);

    newList->head->prev = newList->tail;
    newList->tail->next = newList->head; // 원형 연결 설정
    return newList;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Node* getNodeAtPosition(CircularDoublyLinkedList* list, int position): 특정 위치에 있는 노드를 반환하는 함수
Node* getNodeAtPosition(CircularDoublyLinkedList* list, int position) {
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Node* getLastNode(CircularDoublyLinkedList* list): 리스트의 마지막 노드를 반환하는 함수
Node* getLastNode(CircularDoublyLinkedList* list) {
    if (!list->head) {
        printf("The list is empty.\n");
        return NULL;
    }

    return list->tail; // tail 포인터가 마지막 노드를 가리킴
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void rotateList(CircularDoublyLinkedList* list, int steps): 리스트를 주어진 단계만큼 회전시키는 함수
void rotateList(CircularDoublyLinkedList* list, int steps) {
    if (!list->head || list->head == list->tail) {
        return; // 리스트가 비어있거나 노드가 하나뿐인 경우
    }

    int length = 0;
    Node* current = list->head;
    do {
        length++;
        current = current->next;
    } while (current != list->head);

    steps %= length; // 유효한 단계로 변환
    if (steps == 0) {
        return; // 회전할 단계가 없으면 그대로 반환
    }

    int newTailPosition = length - steps;
    Node* newTail = getNodeAtPosition(list, newTailPosition - 1);

    Node* newHead = newTail->next;

    // 회전을 위한 포인터 연결 수정
    newTail->next = list->head;
    list->head->prev = newTail;
    list->tail->next = newHead;
    newHead->prev = list->tail;

    list->head = newHead; // 새로운 head 설정
    list->tail = newTail; // 새로운 tail 설정
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void clearList(CircularDoublyLinkedList* list): 리스트의 모든 노드를 제거하는 함수
void clearList(CircularDoublyLinkedList* list) {
    if (!list->head) {
        printf("The list is already empty.\n");
        return;
    }

    Node* current = list->head;
    Node* nextNode;

    do {
        nextNode = current->next;
        free(current);
        current = nextNode;
    } while (current != list->head);

    list->head = NULL;
    list->tail = NULL;
}