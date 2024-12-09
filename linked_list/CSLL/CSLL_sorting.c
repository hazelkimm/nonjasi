/*
create_node 함수: 새로운 노드를 생성하고 반환합니다.
append 함수: 리스트의 끝에 새로운 노드를 추가합니다.
display 함수: 리스트의 내용을 출력합니다.
bubble_sort 함수: 리스트를 버블 정렬 알고리즘으로 정렬합니다.
selection_sort 함수: 리스트를 선택 정렬 알고리즘으로 정렬합니다.
insertion_sort 함수: 리스트를 삽입 정렬 알고리즘으로 정렬합니다.
*/

#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;               // 노드의 데이터 값
    struct Node* next;      // 다음 노드를 가리키는 포인터
} Node;

// 순환 단일 연결 리스트 구조체 정의
typedef struct {
    Node* head;             // 리스트의 첫 번째 노드를 가리키는 포인터
} CircularSinglyLinkedList;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 새 노드를 생성하는 함수
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));  // 새 노드를 동적 메모리에 할당
    new_node->data = data;  // 노드의 데이터 설정
    new_node->next = new_node;  // 원형 리스트를 위해 자기 자신을 가리키도록 설정
    return new_node;  // 생성된 노드 반환
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 순환 단일 연결 리스트에 노드를 추가하는 함수
void append(CircularSinglyLinkedList* list, int data) {
    Node* new_node = create_node(data);  // 새로운 노드 생성
    if (list->head == NULL) {
        // 리스트가 비어있다면, 새 노드를 head로 설정하고 원형 구조를 유지하기 위해 자기 자신을 가리키게 함
        list->head = new_node;
    } else {
        // 리스트의 끝까지 이동하여 새 노드를 추가
        Node* temp = list->head;
        while (temp->next != list->head) {
            temp = temp->next;  // 리스트의 끝까지 순회
        }
        temp->next = new_node;  // 마지막 노드의 next를 새 노드로 설정
        new_node->next = list->head;  // 새 노드의 next가 head를 가리키도록 설정하여 원형 구조 유지
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 순환 단일 연결 리스트를 출력하는 함수
void display(CircularSinglyLinkedList* list) {
    if (list->head == NULL) {
        // 리스트가 비어있는 경우
        printf("List is empty\n");
        return;
    }
    Node* temp = list->head;
    do {
        // 노드의 데이터를 출력하고 "->" 기호를 표시
        printf("%d -> ", temp->data);
        temp = temp->next;  // 다음 노드로 이동
    } while (temp != list->head);  // head로 돌아올 때까지 반복
    printf("(back to head)\n");  // 원형 구조의 끝을 나타냄
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 버블 정렬을 수행하는 함수
void bubble_sort(CircularSinglyLinkedList* list) {
    if (list->head == NULL || list->head->next == list->head) {
        // 리스트가 비어있거나 노드가 하나뿐이면 정렬할 필요 없음
        return;
    }

    int swapped;  // 데이터 교환 여부를 나타내는 플래그
    do {
        swapped = 0;  // 초기 상태에서는 교환이 없다고 설정
        Node* current = list->head;  // 리스트의 첫 노드부터 시작
        do {
            Node* next_node = current->next;  // 현재 노드의 다음 노드를 가져옴
            if (current->data > next_node->data) {
                // 현재 노드의 데이터가 다음 노드의 데이터보다 크면 교환
                int temp = current->data;
                current->data = next_node->data;
                next_node->data = temp;
                swapped = 1;  // 교환이 발생했음을 표시
            }
            current = current->next;  // 다음 노드로 이동
        } while (current->next != list->head);  // 마지막 노드까지 순회
    } while (swapped);  // 교환이 발생했으면 다시 반복
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 선택 정렬 함수 (순환 단일 연결 리스트를 정렬)
void selection_sort(CircularSinglyLinkedList* list) {
    if (list->head == NULL || list->head->next == list->head) {
        // 리스트가 비어있거나 노드가 하나뿐이면 정렬할 필요 없음
        return;
    }

    Node* current = list->head;
    do {
        // 현재 노드에서 가장 작은 노드를 찾음
        Node* smallest = current;
        Node* checker = current->next;
        while (checker != list->head) {  // 원형 구조를 유지하며 탐색
            if (checker->data < smallest->data) {
                smallest = checker;
            }
            checker = checker->next;
        }

        // 가장 작은 노드와 현재 노드의 데이터 교환
        if (smallest != current) {
            int temp = current->data;
            current->data = smallest->data;
            smallest->data = temp;
        }

        // 다음 노드로 이동
        current = current->next;
    } while (current != list->head);  // 리스트의 끝에 도달하면 종료
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 삽입 정렬 함수 (순환 단일 연결 리스트를 정렬)
void insertion_sort(CircularSinglyLinkedList* list) {
    if (list->head == NULL || list->head->next == list->head) {
        // 리스트가 비어있거나 노드가 하나뿐이면 정렬할 필요 없음
        return;
    }

    Node* sorted_tail = list->head;
    Node* current = list->head->next;

    while (current != list->head) {
        Node* next_node = current->next;

        if (current->data < list->head->data) {
            // 정렬된 리스트의 시작 부분에 삽입
            sorted_tail->next = next_node;  // 현재 노드를 정렬된 리스트에서 제거
            current->next = list->head;  // 현재 노드를 새로운 head 앞에 삽입
            Node* temp = list->head;
            while (temp->next != list->head) {  // 마지막 노드 탐색
                temp = temp->next;
            }
            temp->next = current;  // 마지막 노드가 새로운 head를 가리키도록 설정
            list->head = current;  // 새로운 head 설정
        } else {
            // 정렬된 리스트 내 적절한 위치를 찾음
            Node* search = list->head;
            while (search->next != list->head && search->next->data < current->data) {
                search = search->next;
            }

            // 노드를 적절한 위치에 삽입
            sorted_tail->next = next_node;  // 현재 노드를 정렬되지 않은 리스트에서 제거
            current->next = search->next;
            search->next = current;

            // 삽입 후, sorted_tail을 갱신
            if (search == sorted_tail) {
                sorted_tail = current;
            }
        }

        // 다음 노드로 이동
        current = next_node;
    }
}


int main() {
    CircularSinglyLinkedList list = {NULL};

    append(&list, 3);
    append(&list, 1);
    append(&list, 4);
    append(&list, 2);

    printf("Original list:\n");
    display(&list);

    bubble_sort(&list);
    printf("List after selection sort:\n");
    display(&list);

    // 원래 리스트 상태를 다시 설정
    list.head = NULL;
    append(&list, 3);
    append(&list, 1);
    append(&list, 4);
    append(&list, 2);

    selection_sort(&list);
    printf("List after insertion sort:\n");
    display(&list);

     // 원래 리스트 상태를 다시 설정
    list.head = NULL;
    append(&list, 3);
    append(&list, 1);
    append(&list, 4);
    append(&list, 2);

    insertion_sort(&list);
    printf("List after insertion sort:\n");
    display(&list);

    return 0;
}