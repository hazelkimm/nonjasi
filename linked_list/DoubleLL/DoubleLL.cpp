// append: 리스트 끝에 노드 추가.
// prepend: 리스트 처음에 노드 추가.
// insertAfter: 특정 노드 뒤에 삽입.
// deleteNode: 특정 값을 가진 노드 삭제.
// search: 리스트에서 특정 값 검색.
// reverse: 리스트를 뒤집기.
// printList: 리스트를 순방향으로 출력.
// printReverse: 리스트를 역방향으로 출력.
// ~DoublyLinkedList: 메모리 해제(소멸자).
// Sorting: Bubble Sort, Insertion Sort, Merge Sort

#include <iostream>
using namespace std;

// Node 클래스 정의
class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

// DoublyLinkedList 클래스 정의
class DoublyLinkedList {
private:
    Node* head;

public:
    DoublyLinkedList() {
        head = nullptr;
    }

    // 1. 리스트 끝에 노드 추가
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
        newNode->prev = temp;
    }

    // 2. 리스트 처음에 노드 추가
    void prepend(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    // 3. 특정 노드 뒤에 삽입
    void insertAfter(int targetData, int data) {
        Node* temp = head;
        while (temp && temp->data != targetData) {
            temp = temp->next;
        }
        if (!temp) {
            cout << "Error: Node with data " << targetData << " not found." << endl;
            return;
        }
        Node* newNode = new Node(data);
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next) {
            temp->next->prev = newNode;
        }
        temp->next = newNode;
    }

    // 4. 특정 값을 가진 노드 삭제
    void deleteNode(int data) {
        if (!head) {
            cout << "Error: List is empty." << endl;
            return;
        }
        Node* temp = head;
        while (temp && temp->data != data) {
            temp = temp->next;
        }
        if (!temp) {
            cout << "Error: Node with data " << data << " not found." << endl;
            return;
        }
        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next;
        }
        if (temp->next) {
            temp->next->prev = temp->prev;
        }
        delete temp;
    }

    // 5. 리스트에서 특정 값 검색
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

    // 6. 리스트 반전
    void reverse() {
        Node* current = head;
        Node* prevNode = nullptr;
        while (current) {
            Node* nextNode = current->next;
            current->next = prevNode;
            current->prev = nextNode;
            prevNode = current;
            current = nextNode;
        }
        head = prevNode;
    }

    // 7. 리스트 출력
    void printList() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // 8. 리스트 역순 출력
    void printReverse() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        while (temp) {
            cout << temp->data << " <- ";
            temp = temp->prev;
        }
        cout << "NULL" << endl;
    }

    // 9. 메모리 해제
    ~DoublyLinkedList() {
        Node* temp = head;
        while (temp) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }

    // Bubble Sort for Doubly Linked List
    void bubbleSort() {
        if (!head || !head->next) return;

        bool swapped;
        Node* current;
        Node* end = nullptr;

        do {
            swapped = false;
            current = head;

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

    // Insertion Sort for Doubly Linked List
    void insertionSort() {
        if (!head || !head->next) return;

        Node* current = head->next;
        while (current) {
            int key = current->data;
            Node* prev = current->prev;

            // Shift nodes in sorted segment to the right
            while (prev && prev->data > key) {
                prev->next->data = prev->data;
                prev = prev->prev;
            }

            // Insert the key at the correct position
            if (prev)
                prev->next->data = key;
            else
                head->data = key;

            current = current->next;
        }
    }

    // Helper: Split the list into two halves
    void splitList(Node* source, Node** front, Node** back) {
        Node* slow = source;
        Node* fast = source->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        *front = source;
        *back = slow->next;
        slow->next = nullptr;

        if (*back)
            (*back)->prev = nullptr;
    }

    // Helper: Merge two sorted halves
    Node* mergeSorted(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->data <= right->data) {
            left->next = mergeSorted(left->next, right);
            left->next->prev = left;
            left->prev = nullptr;
            return left;
        } else {
            right->next = mergeSorted(left, right->next);
            right->next->prev = right;
            right->prev = nullptr;
            return right;
        }
    }

    // Merge Sort for Doubly Linked List
    void mergeSort(Node** headRef) {
        if (!*headRef || !(*headRef)->next) return;

        Node* head = *headRef;
        Node* left;
        Node* right;

        splitList(head, &left, &right);

        mergeSort(&left);
        mergeSort(&right);

        *headRef = mergeSorted(left, right);
    }

    void mergeSort() {
        mergeSort(&head);
    }
};

// 테스트 코드
int main() {
    DoublyLinkedList list;

    list.append(1);
    list.append(2);
    list.append(3);
    list.prepend(0);
    list.printList(); // Output: 0 -> 1 -> 2 -> 3 -> NULL

    list.insertAfter(1, 1.5);
    list.printList(); // Output: 0 -> 1 -> 1.5 -> 2 -> 3 -> NULL

    list.deleteNode(1.5);
    list.printList(); // Output: 0 -> 1 -> 2 -> 3 -> NULL

    cout << "Search 2: " << (list.search(2) ? "Found" : "Not Found") << endl; // Output: Found
    cout << "Search 4: " << (list.search(4) ? "Found" : "Not Found") << endl; // Output: Not Found

    list.reverse();
    list.printList(); // Output: 3 -> 2 -> 1 -> 0 -> NULL

    list.printReverse(); // Output: 0 <- 1 <- 2 <- 3 <- NULL

    return 0;
}

0 -> 1 -> 2 -> 3 -> NULL
0 -> 1 -> 1.5 -> 2 -> 3 -> NULL
0 -> 1 -> 2 -> 3 -> NULL
Search 2: Found
Search 4: Not Found
3 -> 2 -> 1 -> 0 -> NULL
0 <- 1 <- 2 <- 3 <- NULL
