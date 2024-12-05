// append: 리스트 끝에 노드 추가.
// prepend: 리스트 처음에 노드 추가.
// insertAfter: 특정 값 뒤에 노드 삽입.
// deleteNode: 특정 값을 가진 노드 삭제.
// search: 리스트에서 특정 값 검색.
// size: 리스트 크기 반환.
// reverse: 리스트 반전.
// removeDuplicates: 중복 노드 제거.
// printList: 리스트를 보기 좋게 출력.
// 소멸자: 메모리 해제.
// Sorting: Bubble Sort, Insertion Sort, Merge Sort

#include <iostream>
#include <stdexcept>
#include <unordered_set>
using namespace std;

// Node 클래스 정의
class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// SinglyLinkedList 클래스 정의
class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    // 리스트 끝에 노드 추가
    void append(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // 리스트 처음에 노드 추가
    void prepend(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    // 특정 값 뒤에 노드 삽입
    void insertAfter(int prevData, int data) {
        Node* temp = head;
        while (temp && temp->data != prevData) {
            temp = temp->next;
        }
        if (!temp) {
            throw invalid_argument("Node with the given value not found.");
        }
        Node* newNode = new Node(data);
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // 특정 값을 가진 노드 삭제
    void deleteNode(int data) {
        if (!head) return;

        if (head->data == data) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* temp = head;
        while (temp->next && temp->next->data != data) {
            temp = temp->next;
        }

        if (!temp->next) {
            throw invalid_argument("Node with the given value not found.");
        }

        Node* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
    }

    // 리스트에서 특정 값 검색
    bool search(int data) {
        Node* temp = head;
        while (temp) {
            if (temp->data == data) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // 리스트 크기 반환
    int size() {
        int count = 0;
        Node* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // 리스트 반전
    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    // 중복 노드 제거
    void removeDuplicates() {
        unordered_set<int> seen;
        Node* temp = head;
        Node* prev = nullptr;

        while (temp) {
            if (seen.find(temp->data) != seen.end()) {
                prev->next = temp->next;
                delete temp;
            } else {
                seen.insert(temp->data);
                prev = temp;
            }
            temp = prev->next;
        }
    }

    // 리스트 출력
    void printList() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // 리스트 메모리 해제
    ~SinglyLinkedList() {
        Node* temp = head;
        while (temp) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
    
    // Bubble Sort for Singly Linked List
    void bubbleSort() {
        if (!head || !head->next) return;

        bool swapped;
        Node* end = nullptr;

        do {
            swapped = false;
            Node* current = head;

            while (current->next != end) {
                if (current->data > current->next->data) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
            end = current;
        } while (swapped);
    }

    // Helper function: Split the list into two halves
    void splitList(Node* source, Node** front, Node** back) {
        Node* slow = source;
        Node* fast = source->next;

        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *front = source;
        *back = slow->next;
        slow->next = nullptr;
    }

    // Helper function: Merge two sorted lists
    Node* mergeSorted(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;

        Node* result;
        if (a->data <= b->data) {
            result = a;
            result->next = mergeSorted(a->next, b);
        } else {
            result = b;
            result->next = mergeSorted(a, b->next);
        }
        return result;
    }

    // Merge Sort
    void mergeSort(Node** headRef) {
        Node* head = *headRef;
        if (!head || !head->next) return;

        Node *a, *b;

        splitList(head, &a, &b);

        mergeSort(&a);
        mergeSort(&b);

        *headRef = mergeSorted(a, b);
    }

    void mergeSort() {
        mergeSort(&head);
    }

    // Insertion Sort for Singly Linked List
    void insertionSort() {
        if (!head || !head->next) return;

        Node* sorted = nullptr;
        Node* current = head;

        while (current) {
            Node* next = current->next;

            if (!sorted || sorted->data >= current->data) {
                current->next = sorted;
                sorted = current;
            } else {
                Node* temp = sorted;
                while (temp->next && temp->next->data < current->data) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }

            current = next;
        }

        head = sorted;
    }
};

// 테스트 코드
int main() {
    SinglyLinkedList list;

    list.append(1);
    list.append(2);
    list.append(3);
    list.prepend(0);
    list.printList(); // Output: 0 -> 1 -> 2 -> 3 -> NULL

    list.insertAfter(2, 4);
    list.printList(); // Output: 0 -> 1 -> 2 -> 4 -> 3 -> NULL

    list.deleteNode(2);
    list.printList(); // Output: 0 -> 1 -> 4 -> 3 -> NULL

    cout << "Size: " << list.size() << endl; // Output: Size: 4

    cout << "Search 4: " << (list.search(4) ? "Found" : "Not Found") << endl; // Output: Found
    cout << "Search 5: " << (list.search(5) ? "Found" : "Not Found") << endl; // Output: Not Found

    list.reverse();
    list.printList(); // Output: 3 -> 4 -> 1 -> 0 -> NULL

    list.append(1);
    list.append(3);
    list.removeDuplicates();
    list.printList(); // Output: 3 -> 4 -> 1 -> 0 -> NULL

    return 0;
}
