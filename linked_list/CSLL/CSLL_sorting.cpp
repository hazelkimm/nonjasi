/*
create_node 함수: 새로운 노드를 생성하고 반환합니다.
append 함수: 리스트의 끝에 새로운 노드를 추가합니다.
display 함수: 리스트의 내용을 출력합니다.
bubble_sort 함수: 리스트를 버블 정렬 알고리즘으로 정렬합니다.
selection_sort 함수: 리스트를 선택 정렬 알고리즘으로 정렬합니다.
insertion_sort 함수: 리스트를 삽입 정렬 알고리즘으로 정렬합니다.
*/


#include <iostream>

class Node {
public:
    int data;            // 노드의 데이터 값
    Node* next;          // 다음 노드를 가리키는 포인터

    Node(int data) : data(data), next(nullptr) {}  // 생성자
};

class CircularSinglyLinkedList {
private:
    Node* head;          // 리스트의 첫 번째 노드를 가리키는 포인터

public:
    CircularSinglyLinkedList() : head(nullptr) {}  // 생성자

    // 새 노드를 생성하는 함수
    Node* create_node(int data) {
        Node* new_node = new Node(data);
        new_node->next = new_node;  // 원형 리스트를 위해 자기 자신을 가리키도록 설정
        return new_node;
    }

    // 순환 단일 연결 리스트에 노드를 추가하는 함수
    void append(int data) {
        Node* new_node = create_node(data);
        if (head == nullptr) {
            // 리스트가 비어있다면, 새 노드를 head로 설정하고 원형 구조를 유지하기 위해 자기 자신을 가리키게 함
            head = new_node;
        } else {
            // 리스트의 끝까지 이동하여 새 노드를 추가
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = new_node;
            new_node->next = head;  // 새 노드의 next가 head를 가리키도록 설정하여 원형 구조 유지
        }
    }

    // 순환 단일 연결 리스트를 출력하는 함수
    void display() {
        if (head == nullptr) {
            // 리스트가 비어있는 경우
            std::cout << "List is empty" << std::endl;
            return;
        }
        Node* temp = head;
        do {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        std::cout << "(back to head)" << std::endl;
    }

    // 버블 정렬을 수행하는 함수
    void bubble_sort() {
        if (head == nullptr || head->next == head) {
            // 리스트가 비어있거나 노드가 하나뿐이면 정렬할 필요 없음
            return;
        }

        bool swapped;  // 데이터 교환 여부를 나타내는 플래그
        do {
            swapped = false;  // 초기 상태에서는 교환이 없다고 설정
            Node* current = head;
            do {
                Node* next_node = current->next;
                if (current->data > next_node->data) {
                    // 현재 노드의 데이터가 다음 노드의 데이터보다 크면 교환
                    std::swap(current->data, next_node->data);
                    swapped = true;  // 교환이 발생했음을 표시
                }
                current = current->next;  // 다음 노드로 이동
            } while (current->next != head);  // 마지막 노드까지 순회
        } while (swapped);  // 교환이 발생했으면 다시 반복
    }

    // 선택 정렬 함수 (순환 단일 연결 리스트를 정렬)
    void selection_sort() {
        if (head == nullptr || head->next == head) {
            // 리스트가 비어있거나 노드가 하나뿐이면 정렬할 필요 없음
            return;
        }

        Node* current = head;
        do {
            // 현재 노드에서 가장 작은 노드를 찾음
            Node* smallest = current;
            Node* checker = current->next;
            while (checker != head) {
                if (checker->data < smallest->data) {
                    smallest = checker;
                }
                checker = checker->next;
            }

            // 가장 작은 노드와 현재 노드의 데이터 교환
            if (smallest != current) {
                std::swap(current->data, smallest->data);
            }

            // 다음 노드로 이동
            current = current->next;
        } while (current != head);  // 리스트의 끝에 도달하면 종료
    }

    // 삽입 정렬 함수 (순환 단일 연결 리스트를 정렬)
    void insertion_sort() {
        if (head == nullptr || head->next == head) {
            // 리스트가 비어있거나 노드가 하나뿐이면 정렬할 필요 없음
            return;
        }

        Node* sorted_tail = head;
        Node* current = head->next;

        while (current != head) {
            Node* next_node = current->next;

            if (current->data < head->data) {
                // 정렬된 리스트의 시작 부분에 삽입
                sorted_tail->next = next_node;  // 현재 노드를 정렬된 리스트에서 제거
                current->next = head;  // 현재 노드를 새로운 head 앞에 삽입
                Node* temp = head;
                while (temp->next != head) {  // 마지막 노드 탐색
                    temp = temp->next;
                }
                temp->next = current;  // 마지막 노드가 새로운 head를 가리키도록 설정
                head = current;  // 새로운 head 설정
            } else {
                // 정렬된 리스트 내 적절한 위치를 찾음
                Node* search = head;
                while (search->next != head && search->next->data < current->data) {
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
};

int main() {
    CircularSinglyLinkedList list;

    list.append(3);
    list.append(1);
    list.append(4);
    list.append(2);

    std::cout << "Original list:" << std::endl;
    list.display();

    list.bubble_sort();
    std::cout << "List after bubble sort:" << std::endl;
    list.display();

    // 원래 리스트 상태를 다시 설정
    CircularSinglyLinkedList list2;
    list2.append(3);
    list2.append(1);
    list2.append(4);
    list2.append(2);

    list2.selection_sort();
    std::cout << "List after selection sort:" << std::endl;
    list2.display();

    // 원래 리스트 상태를 다시 설정
    CircularSinglyLinkedList list3;
    list3.append(3);
    list3.append(1);
    list3.append(4);
    list3.append(2);

    list3.insertion_sort();
    std::cout << "List after insertion sort:" << std::endl;
    list3.display();

    return 0;
}
