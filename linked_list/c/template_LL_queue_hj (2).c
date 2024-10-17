#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 3

// Node 구조체 정의 (Stack을 포함)
typedef struct Node {
    int stack[MAX_CAPACITY];  // 스택을 배열로 구현 (최대 3개까지)
    int top;                  // 스택의 최상단 인덱스
    struct Node* next;        // 다음 노드를 가리키는 포인터
} Node;

// Linked List of Stack 구조체 정의
typedef struct {
    Node* head;  // 리스트의 첫 번째 노드를 가리키는 포인터
} LinkedListOfStacks;

// 새로운 노드 생성
Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->top = -1;  // 스택이 비어있음을 나타냄
    newNode->next = NULL;
    return newNode;
}

// Linked List of Stack 초기화
LinkedListOfStacks* createLinkedListOfStacks() {
    LinkedListOfStacks* list = (LinkedListOfStacks*)malloc(sizeof(LinkedListOfStacks));
    list->head = createNode();  // 빈 노드로 시작
    return list;
}

// 스택이 가득 찼는지 확인
int isFull(Node* node) {
    return node->top == MAX_CAPACITY - 1;
}

// 스택이 비었는지 확인
int isEmpty(Node* node) {
    return node->top == -1;
}

// 스택에 원소 추가
void push(LinkedListOfStacks* list, int data) {
    Node* lastNode = list->head;
    // 마지막 노드 찾기
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }

    if (isFull(lastNode)) {
        // 스택이 가득 찬 경우 새 노드를 추가
        Node* newNode = createNode();
        newNode->stack[++(newNode->top)] = data;  // 새 노드의 스택에 데이터 추가
        lastNode->next = newNode;  // 리스트에 새 노드 연결
    } else {
        // 스택에 데이터 추가
        lastNode->stack[++(lastNode->top)] = data;
    }
}

// 스택에서 원소 제거 및 반환
int pop(LinkedListOfStacks* list) {
    Node* current = list->head;
    Node* prev = NULL;

    // 마지막 노드 찾기
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (isEmpty(current)) {
        // 스택이 비어 있으면 이전 노드로 이동하여 삭제
        if (prev != NULL) {
            free(current);
            prev->next = NULL;
            current = prev;
        } else {
            printf("All stacks are empty!\n");
            return -1;
        }
    }

    // 현재 스택에서 원소 제거 및 반환
    return current->stack[(current->top)--];
}

// 스택 출력 (디버깅용)
void printStacks(LinkedListOfStacks* list) {
    Node* current = list->head;
    int nodeIndex = 1;
    while (current != NULL) {
        printf("Stack %d: ", nodeIndex++);
        for (int i = 0; i <= current->top; i++) {
            printf("%d ", current->stack[i]);
        }
        printf("\n");
        current = current->next;
    }
}

int main() {
    LinkedListOfStacks* stackList = createLinkedListOfStacks();

    // Push 예시
    for (int i = 1; i <= 10; i++) {
        push(stackList, i);
    }
    printStacks(stackList);

    // Pop 예시
    for (int i = 0; i < 5; i++) {
        printf("Popped: %d\n", pop(stackList));
    }
    printStacks(stackList);

    return 0;
}
