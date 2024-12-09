/*
create_node 함수: 새로운 노드를 생성하고 반환합니다.
append 함수: 리스트의 끝에 새로운 노드를 추가합니다.
display 함수: 리스트의 내용을 출력합니다.
bubble_sort 함수: 리스트를 버블 정렬 알고리즘으로 정렬합니다.
selection_sort 함수: 리스트를 선택 정렬 알고리즘으로 정렬합니다.
insertion_sort 함수: 리스트를 삽입 정렬 알고리즘으로 정렬합니다.
*/

#include <iostream>
using namespace std;

// 노드 클래스 정의
class Node {
public:
    int data;  // 노드가 저장할 데이터
    Node* next;  // 다음 노드를 가리키는 포인터
    Node* prev;  // 이전 노드를 가리키는 포인터

    // 생성자
    Node(int data) : data(data), next(nullptr), prev(nullptr) {}
};

// 원형 이중 연결 리스트 클래스 정의
class CircularDoublyLinkedList {
public:
    Node* head;  // 리스트의 첫 번째 노드를 가리킴
    Node* tail;  // 리스트의 마지막 노드를 가리킴


    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // 생성자
    CircularDoublyLinkedList() : head(nullptr), tail(nullptr) {}


    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // 원형 이중 연결 리스트에 새 노드를 추가하는 메서드
    void append(int data) {
        Node* new_node = new Node(data);  // 새 노드 메모리 할당
        if (head == nullptr) {
            // 리스트가 비어있으면 새 노드를 head와 tail로 설정
            head = new_node;
            tail = new_node;
            head->next = head;  // 자기 자신을 가리키는 순환 링크
            head->prev = head;  // 자기 자신을 가리키는 순환 링크
        } else {
            // 기존의 tail 뒤에 새 노드를 추가
            new_node->prev = tail;  // 새 노드의 이전 노드를 기존 tail로 설정
            new_node->next = head;  // 새 노드의 다음 노드를 head로 설정
            tail->next = new_node;  // 기존 tail의 다음 노드를 새 노드로 설정
            head->prev = new_node;  // head의 이전 노드를 새 노드로 설정
            tail = new_node;  // 새 노드를 새로운 tail로 설정
        }
    }


    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // 리스트의 모든 노드를 출력하는 메서드
    void display() {
        if (head == nullptr) {
            // 리스트가 비어있는 경우 출력
            cout << "List is empty" << endl;
            return;
        }
        Node* temp = head;  // 리스트의 head 노드부터 시작
        do {
            // 현재 노드의 데이터를 출력
            cout << temp->data << " <-> ";
            temp = temp->next;  // 다음 노드로 이동
        } while (temp != head);  // head 노드로 돌아오면 반복 종료
        cout << "(back to head)" << endl;  // 리스트의 끝을 나타내는 메시지
    }


    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // 버블 정렬 함수
    void bubble_sort() {
        if (head == nullptr || head->next == head) {
            // 리스트가 비어있거나 노드가 하나만 있는 경우 정렬할 필요 없음
            return;
        }

        bool swapped;
        Node* current;
        Node* next_node;
        do {
            swapped = false;  // 플래그 초기화
            current = head;  // 탐색을 head에서 시작
            while (current->next != head) {
                next_node = current->next;  // 현재 노드의 다음 노드 설정
                if (current->data > next_node->data) {
                    // 현재 노드의 데이터가 다음 노드의 데이터보다 큰 경우 교환
                    std::swap(current->data, next_node->data);
                    swapped = true;  // 교환이 발생했음을 표시
                }
                current = current->next;  // 다음 노드로 이동
            }
        } while (swapped);  // 교환이 발생했다면 계속 정렬 수행
    }


    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // 선택 정렬 함수
    void selection_sort() {
        if (head == nullptr || head->next == head) {
            // 리스트가 비어있거나 노드가 하나만 있는 경우 정렬할 필요 없음
            return;
        }

        Node* current = head;  // 현재 탐색 중인 노드
        while (current->next != head) {
            Node* smallest = current;  // 현재 노드를 가장 작은 값으로 설정
            Node* checker = current->next;  // 비교할 다음 노드
            while (checker != head) {
                if (checker->data < smallest->data) {
                    // 작은 값을 찾으면 smallest를 업데이트
                    smallest = checker;
                }
                checker = checker->next;  // 다음 노드로 이동
            }

            if (smallest != current) {
                // 가장 작은 값이 현재 노드가 아니면 교환
                std::swap(current->data, smallest->data);
            }

            current = current->next;  // 다음 노드로 이동
        }
    }


    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // 삽입 정렬 메서드
    void insertion_sort() {
        if (head == nullptr || head->next == head) {
            // 리스트가 비어있거나 노드가 하나뿐인 경우 정렬이 필요 없음
            return;
        }

        Node* current = head->next;  // 두 번째 노드부터 시작 (정렬되지 않은 부분)
        while (current != head) {
            Node* next_node = current->next;  // 현재 노드의 다음 노드
            if (current->data < head->data) {
                // 현재 노드가 리스트의 head보다 작으면, head 앞에 삽입
                current->prev->next = next_node;  // 현재 노드를 정렬되지 않은 리스트에서 제거
                if (next_node != head) {
                    next_node->prev = current->prev;
                }
                current->next = head;  // 현재 노드를 head 앞에 삽입
                head->prev = current;
                current->prev = tail;  // tail을 현재 노드의 이전 노드로 설정
                tail->next = current;  // tail의 다음 노드로 현재 노드를 설정
                head = current;  // 새로운 head 설정
            } else {
                // 정렬된 리스트 내 적절한 위치를 찾아 현재 노드를 삽입
                Node* search = head;
                while (search->next != head && search->next->data < current->data) {
                    search = search->next;  // 현재 노드보다 작은 노드가 있는지 탐색
                }

                current->prev->next = next_node;  // 현재 노드를 정렬되지 않은 리스트에서 제거
                if (next_node != head) {
                    next_node->prev = current->prev;
                }
                current->next = search->next;  // 현재 노드를 적절한 위치에 삽입
                search->next->prev = current;
                search->next = current;
            }

            current = next_node;  // current를 갱신
        }
    }
};



// 테스트 코드
int main() {
    CircularDoublyLinkedList list;  // 빈 리스트 생성

    // 리스트에 데이터 추가
    list.append(4);
    list.append(2);
    list.append(7);
    list.append(1);
    list.append(5);

    cout << "Before sorting:" << endl;
    list.display();  // 정렬 전 리스트 출력

    // 정렬 실행 (주석 해제 후 사용)
    // list.bubble_sort();  // 버블 정렬
    // list.selection_sort();  // 선택 정렬
    list.insertion_sort();  // 삽입 정렬

    cout << "After sorting:" << endl;
    list.display();  // 정렬 후 리스트 출력

    return 0;
}
