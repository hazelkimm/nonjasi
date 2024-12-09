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
    int data;  // 노드가 저장할 데이터
    struct Node* next;  // 다음 노드를 가리키는 포인터
    struct Node* prev;  // 이전 노드를 가리키는 포인터
} Node;

// 원형 이중 연결 리스트 구조체 정의
typedef struct {
    Node* head;  // 리스트의 첫 번째 노드를 가리킴 (head)
    Node* tail;  // 리스트의 마지막 노드를 가리킴 (tail)
} CircularDoublyLinkedList;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 새 노드를 리스트에 추가하는 함수
void append(CircularDoublyLinkedList* list, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));  // 새 노드 메모리 할당
    new_node->data = data;  // 노드의 데이터 설정

    if (list->head == NULL) {
        // 리스트가 비어있으면 새 노드를 head와 tail로 설정
        new_node->next = new_node;  // 자기 자신을 가리키는 순환 링크
        new_node->prev = new_node;  // 자기 자신을 가리키는 순환 링크
        list->head = new_node;  // 새 노드를 리스트의 head로 설정
        list->tail = new_node;  // 새 노드를 리스트의 tail로 설정
    } else {
        // 기존의 tail 뒤에 새 노드를 추가
        new_node->prev = list->tail;  // 새 노드의 이전 노드를 기존 tail로 설정
        new_node->next = list->head;  // 새 노드의 다음 노드를 head로 설정
        list->tail->next = new_node;  // 기존 tail의 다음 노드를 새 노드로 설정
        list->head->prev = new_node;  // head의 이전 노드를 새 노드로 설정
        list->tail = new_node;  // 새 노드를 새로운 tail로 설정
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트의 모든 노드를 출력하는 함수
void display(CircularDoublyLinkedList* list) {
    if (list->head == NULL) {
        // 리스트가 비어있는 경우 출력
        printf("List is empty\n");
        return;
    }
    Node* temp = list->head;  // 리스트의 head 노드부터 시작
    do {
        // 현재 노드의 데이터를 출력
        printf("%d <-> ", temp->data);
        temp = temp->next;  // 다음 노드로 이동
    } while (temp != list->head);  // head 노드로 다시 돌아오면 반복 종료
    printf("(back to head)\n");  // 리스트의 끝을 나타내는 메시지
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 버블 정렬 함수
void bubble_sort(CircularDoublyLinkedList* list) {
    if (list->head == NULL || list->head->next == list->head) {
        // 리스트가 비어있거나 노드가 하나만 있는 경우 정렬할 필요 없음
        return;
    }

    int swapped;  // 데이터가 교환되었는지를 나타내는 플래그
    Node* current;  // 현재 탐색 중인 노드
    Node* next_node;  // 다음 노드
    do {
        swapped = 0;  // 플래그 초기화
        current = list->head;  // 탐색을 head에서 시작
        while (current->next != list->head) {
            next_node = current->next;  // 현재 노드의 다음 노드 설정
            if (current->data > next_node->data) {
                // 현재 노드의 데이터가 다음 노드의 데이터보다 큰 경우 교환
                int temp = current->data;
                current->data = next_node->data;
                next_node->data = temp;
                swapped = 1;  // 교환이 발생했음을 표시
            }
            current = current->next;  // 다음 노드로 이동
        }
    } while (swapped);  // 교환이 발생했다면 계속 정렬 수행
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 선택 정렬 함수
void selection_sort(CircularDoublyLinkedList* list) {
    if (list->head == NULL || list->head->next == list->head) {
        // 리스트가 비어있거나 노드가 하나만 있는 경우 정렬할 필요 없음
        return;
    }

    Node* current = list->head;  // 현재 탐색 중인 노드
    while (current->next != list->head) {
        Node* smallest = current;  // 현재 노드를 가장 작은 값으로 설정
        Node* checker = current->next;  // 비교할 다음 노드
        while (checker != list->head) {
            if (checker->data < smallest->data) {
                // 작은 값을 찾으면 smallest를 업데이트
                smallest = checker;
            }
            checker = checker->next;  // 다음 노드로 이동
        }

        if (smallest != current) {
            // 가장 작은 값이 현재 노드가 아니면 교환
            int temp = current->data;
            current->data = smallest->data;
            smallest->data = temp;
        }

        current = current->next;  // 다음 노드로 이동
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 삽입 정렬 함수
void insertion_sort(CircularDoublyLinkedList* list) {
    if (list->head == NULL || list->head->next == list->head) {
        // 리스트가 비어있거나 노드가 하나뿐인 경우 정렬이 필요 없음
        return;
    }

    Node* current = list->head->next;  // 두 번째 노드부터 시작 (정렬되지 않은 부분)
    while (current != list->head) {
        Node* next_node = current->next;  // 현재 노드의 다음 노드
        if (current->data < list->head->data) {
            // 현재 노드가 리스트의 head보다 작으면, head 앞에 삽입
            current->prev->next = next_node;  // 현재 노드를 정렬되지 않은 리스트에서 제거
            if (next_node != list->head) {
                next_node->prev = current->prev;
            }
            current->next = list->head;  // 현재 노드를 head 앞에 삽입
            list->head->prev = current;
            current->prev = list->tail;  // tail을 현재 노드의 이전 노드로 설정
            list->tail->next = current;  // tail의 다음 노드로 현재 노드를 설정
            list->head = current;  // 새로운 head 설정
        } else {
            // 정렬된 리스트 내 적절한 위치를 찾아 현재 노드를 삽입
            Node* search = list->head;
            while (search->next != list->head && search->next->data < current->data) {
                search = search->next;  // 현재 노드보다 작은 노드가 있는지 탐색
            }

            current->prev->next = next_node;  // 현재 노드를 정렬되지 않은 리스트에서 제거
            if (next_node != list->head) {
                next_node->prev = current->prev;
            }
            current->next = search->next;  // 현재 노드를 적절한 위치에 삽입
            search->next->prev = current;
            search->next = current;
        }

        current = next_node;  // current를 갱신
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 메모리 해제를 위한 함수 (추가적 사용 시)
void free_list(CircularDoublyLinkedList* list) {
    if (list->head == NULL) {
        return;  // 리스트가 비어있으면 아무 것도 하지 않음
    }
    Node* current = list->head;  // 리스트의 첫 번째 노드부터 시작
    do {
        Node* next_node = current->next;  // 현재 노드의 다음 노드 저장
        free(current);  // 현재 노드 메모리 해제
        current = next_node;  // 다음 노드로 이동
    } while (current != list->head);  // 리스트의 끝까지 순회
    list->head = NULL;  // 리스트 초기화
    list->tail = NULL;
}




int main() {
    CircularDoublyLinkedList list = {NULL, NULL};  // 빈 리스트 생성

    // 리스트에 데이터 추가
    append(&list, 4);
    append(&list, 2);
    append(&list, 7);
    append(&list, 1);
    append(&list, 5);

    printf("Before sorting:\n");
    display(&list);  // 정렬 전 리스트 출력

    // 정렬 실행 (주석 해제 후 사용)
    // bubble_sort(&list);  // 버블 정렬
    // selection_sort(&list);  // 선택 정렬
    insertion_sort(&list);  // 삽입 정렬

    printf("After sorting:\n");
    display(&list);  // 정렬 후 리스트 출력

    // 메모리 해제
    free_list(&list);

    return 0;
}
