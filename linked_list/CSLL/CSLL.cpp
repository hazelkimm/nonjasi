/*
void initList(): 리스트 초기화 함수
void addNode(int data): 새로운 노드를 추가하는 함수
void displayList(): 리스트 출력 함수
Node* findNode(int data): 특정 값을 가진 노드를 찾는 함수
bool findNode2(int data): 특정 값을 가진 노드가 리스트에 있는지 확인하는 함수
int getLength(): 리스트의 길이를 반환하는 함수
void deleteNode(int data): 특정 값을 가진 노드를 삭제하는 함수
bool isCircular(): 순환 구조 여부를 확인하는 함수
void traverseList(): 리스트를 순회하며 모든 노드를 방문하는 함수
Node* findMiddleNode(): 순환 리스트에서 중간 노드를 찾는 함수
void insertAtPosition(int data, int position): 주어진 위치에 노드를 삽입하는 함수
void removeAtPosition(int position): 주어진 위치의 노드를 삭제하는 함수
void reverseList(): 리스트의 순서를 뒤집는 함수
bool detectCycle(): 순환 여부를 탐지하는 함수 (Floyd’s Cycle Detection Algorithm)
void splitList(CircularSinglyLinkedList* list1, CircularSinglyLinkedList* list2): 순환 리스트를 두 개의 리스트로 분할하는 함수
void mergeList(CircularSinglyLinkedList* list2): 두 개의 순환 리스트를 병합하는 함수
CircularSinglyLinkedList* copyList(): 리스트의 복사본을 생성하는 함수
Node* getNodeAtPosition(int position): 특정 위치에 있는 노드를 반환하는 함수
Node* getLastNode(): 리스트의 마지막 노드를 반환하는 함수
void rotateList(int steps): 리스트를 주어진 단계만큼 회전시키는 함수
void clearList(): 리스트의 모든 노드를 제거하는 함수
*/


#include <iostream>

using namespace std;

// 노드 구조체 정의
struct Node {
    int data;
    Node* next;
    
    Node(int value) : data(value), next(nullptr) {}
};

// 순환 단일 연결 리스트 클래스 정의
class CircularSinglyLinkedList {
private:
    Node* head;

public:
    // 생성자
    CircularSinglyLinkedList() : head(nullptr) {}


    ///////////////////////////////////////////////////////////////////////////////////
    // void initList(): 리스트 초기화 함수
    void initList() {
        head = nullptr;
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // void addNode(int data): 새로운 노드를 추가하는 함수
    void addNode(int data) {
        Node* newNode = new Node(data);
        
        if (head == nullptr) {
            // 리스트가 비어 있는 경우
            head = newNode;
            newNode->next = newNode; // 순환 연결
        } else {
            Node* current = head;
            // 마지막 노드로 이동
            while (current->next != head) {
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head; // 순환 연결
        }
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // void displayList(): 리스트 출력 함수
    void displayList() const {
        if (head == nullptr) {
            cout << "The list is empty." << endl;
            return;
        }

        Node* current = head;
        do {
            cout << current->data << " -> ";
            current = current->next;
        } while (current != head);
        cout << "(head)" << endl;
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // Node* findNode(int data): 특정 값을 가진 노드를 찾는 함수
    Node* findNode(int data) const {
        if (head == nullptr) {
            return nullptr;
        }

        Node* current = head;
        do {
            if (current->data == data) {
                return current; // 해당 노드를 반환
            }
            current = current->next;
        } while (current != head);
        return nullptr; // 찾지 못한 경우
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // bool findNode2(int data): 특정 값을 가진 노드가 리스트에 있는지 확인하는 함수
    bool findNode2(int data) const {
        if (head == nullptr) {
            return false; // 리스트가 비어 있으면 False
        }

        Node* current = head;
        do {
            if (current->data == data) {
                return true; // True: 데이터를 찾음
            }
            current = current->next;
        } while (current != head);
        return false; // False: 데이터를 찾지 못함
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // int getLength(): 리스트의 길이를 반환하는 함수
    int getLength() const {
        if (head == nullptr) {
            return 0;
        }

        int count = 0;
        Node* current = head;
        do {
            count++;
            current = current->next;
        } while (current != head);
        return count;
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // void deleteNode(int data): 특정 값을 가진 노드를 삭제하는 함수
    void deleteNode(int data) {
        if (head == nullptr) {
            cout << "The list is empty." << endl;
            return;
        }

        Node* current = head;
        Node* prev = nullptr;

        // 경우 1: 삭제할 노드가 head인 경우
        if (current->data == data) {
            // 마지막 노드로 이동
            while (current->next != head) {
                current = current->next;
            }
            if (current == head) {
                // 리스트에 단 하나의 노드만 있는 경우
                delete head;
                head = nullptr;
            } else {
                current->next = head->next; // 마지막 노드 연결 변경
                delete head;
                head = current->next; // head 갱신
            }
            return;
        }

        // 경우 2: 중간이나 끝에서 삭제할 노드를 찾는 경우
        current = head;
        do {
            if (current->data == data) {
                prev->next = current->next;
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        } while (current != head);

        cout << "Node not found." << endl;
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // bool isCircular(): 순환 구조 여부를 확인하는 함수
    bool isCircular() const {
        if (head == nullptr) {
            return false; // 리스트가 비어 있으면 순환 구조 아님
        }

        Node* current = head->next;
        while (current != nullptr) {
            if (current == head) {
                return true; // 순환 구조 확인
            }
            current = current->next;
        }
        return false; // 순환 구조 아님
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // void traverseList(): 리스트를 순회하며 모든 노드를 방문하는 함수
    void traverseList() const {
        if (head == nullptr) {
            cout << "The list is empty." << endl;
            return;
        }

        cout << "Traversing the list:" << endl;
        Node* current = head;
        do {
            cout << current->data << " -> ";
            current = current->next;
        } while (current != head);
        cout << "(head)" << endl;
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // Node* findMiddleNode(): 순환 리스트에서 중간 노드를 찾는 함수
    Node* findMiddleNode() const {
        if (head == nullptr) {
            cout << "The list is empty." << endl;
            return nullptr;
        }

        Node* slow = head;
        Node* fast = head;

        // fast 포인터가 끝에 도달할 때까지 slow 포인터는 한 칸, fast 포인터는 두 칸 이동
        while (fast->next != head && fast->next->next != head) {
            slow = slow->next;
            fast = fast->next->next;
        }

        cout << "The middle node is: " << slow->data << endl;
        return slow;
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // void insertAtPosition(int data, int position): 주어진 위치에 노드를 삽입하는 함수
    void insertAtPosition(int data, int position) {
        Node* newNode = new Node(data);

        // 리스트가 비어 있는 경우
        if (head == nullptr) {
            if (position == 0) {
                head = newNode;
                newNode->next = newNode; // 자기 자신을 가리킴
            } else {
                cout << "Invalid position for an empty list." << endl;
            }
            return;
        }

        // 위치가 0이면 head 앞에 노드 삽입
        if (position == 0) {
            Node* current = head;
            while (current->next != head) { // 마지막 노드 찾기
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head;
            head = newNode;
            return;
        }

        // 중간 또는 끝에 삽입
        Node* current = head;
        int count = 0;
        while (count < position - 1 && current->next != head) {
            current = current->next;
            count++;
        }

        if (count == position - 1) {
            newNode->next = current->next;
            current->next = newNode;
        } else {
            cout << "Position out of range." << endl;
            delete newNode; // 메모리 해제
        }
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // void removeAtPosition(int position): 주어진 위치의 노드를 삭제하는 함수
    void removeAtPosition(int position) {
        if (head == nullptr) {
            cout << "The list is empty." << endl;
            return;
        }

        Node* current = head;

        // 위치가 0인 경우 head 삭제
        if (position == 0) {
            if (current->next == head) { // 노드가 하나만 있는 경우
                delete current;
                head = nullptr;
            } else {
                Node* temp = current;
                while (current->next != head) { // 마지막 노드 찾기
                    current = current->next;
                }
                current->next = head->next;
                head = head->next;
                delete temp;
            }
            return;
        }

        // 중간 또는 끝에서 삭제
        Node* prev = nullptr;
        int count = 0;
        while (count < position && current->next != head) {
            prev = current;
            current = current->next;
            count++;
        }

        if (count == position) {
            prev->next = current->next;
            delete current;
        } else {
            cout << "Position out of range." << endl;
        }
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // void reverseList(): 리스트의 순서를 뒤집는 함수
    void reverseList() {
        if (!head || head->next == head) {
            return; // 노드가 0개 또는 1개인 경우 변경할 필요 없음
        }

        Node* prev = nullptr;
        Node* current = head;
        Node* next_node = nullptr;

        // 리스트를 한 번 순회하며 노드의 방향을 뒤집음
        do {
            next_node = current->next; // 현재 노드의 다음 노드 저장
            current->next = prev;      // 현재 노드의 next 포인터를 이전 노드로 변경
            prev = current;            // 이전 노드를 현재 노드로 업데이트
            current = next_node;       // 현재 노드를 다음 노드로 이동
        } while (current != head);

        head->next = prev; // 기존 head의 next를 마지막 노드로 설정
        head = prev;       // 새로운 head로 갱신
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // bool detectCycle(): 순환 여부를 탐지하는 함수 (Floyd’s Cycle Detection Algorithm)
    bool detectCycle() const {
        if (!head) {
            // 리스트가 비어있는 경우, 순환이 있을 수 없음
            return false;
        }

        Node* slow = head; // 한 번에 한 칸씩 이동하는 느린 포인터
        Node* fast = head; // 한 번에 두 칸씩 이동하는 빠른 포인터

        while (fast && fast->next) {
            slow = slow->next;        // 느린 포인터는 한 칸 이동
            fast = fast->next->next;  // 빠른 포인터는 두 칸 이동

            if (slow == fast) {
                // 두 포인터가 만나면 순환이 존재
                cout << "Cycle detected in the list." << endl;
                return true;
            }
        }

        // 빠른 포인터가 리스트 끝에 도달하면 순환이 없음
        cout << "No cycle detected in the list." << endl;
        return false;
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // void splitList(CircularSinglyLinkedList* list1, CircularSinglyLinkedList* list2): 순환 리스트를 두 개의 리스트로 분할하는 함수
    void splitList(CircularSinglyLinkedList* list1, CircularSinglyLinkedList* list2) {
        if (!head || head->next == head) {
            // 리스트가 비어있거나 노드가 하나뿐인 경우 분할 불가
            cout << "Cannot split a list with fewer than 2 nodes." << endl;
            list1->head = nullptr;
            list2->head = nullptr;
            return;
        }

        Node* slow = head; // 느린 포인터: 한 칸씩 이동
        Node* fast = head; // 빠른 포인터: 두 칸씩 이동

        // 빠른 포인터가 리스트를 끝까지 순회할 때까지 반복
        while (fast->next != head && fast->next->next != head) {
            slow = slow->next;       // 느린 포인터 이동
            fast = fast->next->next; // 빠른 포인터 이동
        }

        // 두 리스트의 헤드 설정
        list1->head = head;          // 첫 번째 리스트는 기존 리스트의 시작 노드에서 시작
        list2->head = slow->next;    // 두 번째 리스트는 느린 포인터의 다음 노드에서 시작
        slow->next = list1->head;    // 첫 번째 리스트를 원형으로 만듦

        // 두 번째 리스트를 원형으로 만듦
        Node* current = list2->head;
        while (current->next != head) {
            current = current->next;
        }
        current->next = list2->head; // 두 번째 리스트의 끝을 시작으로 연결
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // void mergeList(CircularSinglyLinkedList* list2): 두 개의 순환 리스트를 병합하는 함수
    void mergeList(CircularSinglyLinkedList* list2) {
        if (!head) {
            // 첫 번째 리스트가 비어있으면 두 번째 리스트가 병합된 결과가 됨
            head = list2->head;
            return;
        }
        if (!list2->head) {
            // 두 번째 리스트가 비어있으면 아무 작업도 필요 없음
            return;
        }

        // 첫 번째 리스트의 마지막 노드를 찾음
        Node* current1 = head;
        while (current1->next != head) {
            current1 = current1->next;
        }

        // 두 번째 리스트의 마지막 노드를 찾음
        Node* current2 = list2->head;
        while (current2->next != list2->head) {
            current2 = current2->next;
        }

        // 두 리스트를 병합
        current1->next = list2->head; // 첫 번째 리스트의 끝에 두 번째 리스트의 시작 연결
        current2->next = head;        // 두 번째 리스트의 끝을 첫 번째 리스트의 시작으로 연결

        // 병합된 리스트의 head를 첫 번째 리스트의 시작 노드로 설정
        head = head;
    }
    

    ///////////////////////////////////////////////////////////////////////////////////
    // CircularSinglyLinkedList* copyList(): 리스트의 복사본을 생성하는 함수
    CircularSinglyLinkedList* copyList() {
        CircularSinglyLinkedList* newList = new CircularSinglyLinkedList();
        if (!head) {
            // 리스트가 비어있으면 새로운 리스트도 비어있음
            return newList;
        }

        Node* current = head;
        Node* newNode = nullptr;
        Node* tail = nullptr;

        do {
            newNode = new Node(current->data); // 새로운 노드 생성
            if (!newList->head) {
                newList->head = newNode; // 첫 번째 노드 설정
                tail = newNode;
            } else {
                tail->next = newNode; // 기존 마지막 노드에 새 노드 추가
                tail = newNode;
            }
            current = current->next;
        } while (current != head);

        tail->next = newList->head; // 원형 연결 설정
        return newList;
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // Node* getNodeAtPosition(int position): 특정 위치에 있는 노드를 반환하는 함수
    Node* getNodeAtPosition(int position) {
        if (!head) {
            cout << "The list is empty." << endl;
            return nullptr;
        }

        int length = 0;
        Node* current = head;

        // 리스트의 길이 계산
        do {
            length++;
            current = current->next;
        } while (current != head);

        position %= length; // 유효한 위치로 변환

        current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        return current;
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // Node* getLastNode(): 리스트의 마지막 노드를 반환하는 함수
    Node* getLastNode() {
        if (!head) {
            cout << "The list is empty." << endl;
            return nullptr;
        }

        Node* current = head;
        while (current->next != head) {
            current = current->next;
        }
        return current;
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // void rotateList(int steps): 리스트를 주어진 단계만큼 회전시키는 함수
    void rotateList(int steps) {
        if (!head || head->next == head) {
            // 노드가 없거나 단일 노드인 경우 회전 불필요
            return;
        }

        int length = 0;
        Node* current = head;
        do {
            length++;
            current = current->next;
        } while (current != head);

        steps %= length; // 유효한 단계로 변환
        if (steps == 0) {
            return; // 회전할 단계가 없는 경우
        }

        int newTailPosition = length - steps;
        Node* newTail = getNodeAtPosition(newTailPosition - 1); // 새 꼬리 노드
        Node* newHead = newTail->next; // 새 헤드 노드
        Node* lastNode = getLastNode(); // 현재 리스트의 마지막 노드

        lastNode->next = newHead; // 마지막 노드가 새 헤드를 가리킴
        newTail->next = head;     // 새 꼬리가 기존 헤드를 가리킴
        head = newHead;           // 헤드 업데이트
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // void clearList(): 리스트의 모든 노드를 제거하는 함수
    void clearList() {
        if (!head) {
            cout << "The list is already empty." << endl;
            return;
        }

        Node* current = head;
        Node* nextNode;

        // 리스트 순회하며 메모리 해제
        while (current->next != head) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }

        delete current; // 마지막 노드 해제
        head = nullptr; // 헤드 초기화
    }


    ///////////////////////////////////////////////////////////////////////////////////
    // 소멸자
    ~CircularSinglyLinkedList() {
        if (head == nullptr) return;

        Node* current = head;
        do {
            Node* next = current->next;
            delete current;
            current = next;
        } while (current != head);

        head = nullptr;
    }
};
