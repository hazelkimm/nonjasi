// append: 리스트 끝에 노드 추가.
// prepend: 리스트 처음에 노드 추가.
// insertAfter: 특정 노드 뒤에 삽입.
// deleteNode: 특정 값을 가진 노드 삭제.
// search: 리스트에서 특정 값 검색.
// reverse: 리스트를 뒤집기.
// printList: 리스트를 순방향으로 출력.
// printReverse: 리스트를 역방향으로 출력.
// ~DoublyLinkedList: 메모리 해제(소멸자).
// Sorting: Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort

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

    // Selection Sort for Doubly Linked List
    void selectionSort() {
        if (!head || !head->next) return;

        Node* current = head;
        while (current) {
            Node* minNode = current;
            Node* nextNode = current->next;

            // Find the node with the minimum value in the unsorted part
            while (nextNode) {
                if (nextNode->data < minNode->data) {
                    minNode = nextNode;
                }
                nextNode = nextNode->next;
            }

            // Swap data if a smaller node is found
            if (minNode != current) {
                swap(current->data, minNode->data);
            }

            current = current->next;
        }
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

    // Quick Sort for Doubly Linked List
    Node* partition(Node* low, Node* high) {
        int pivot = high->data;
        Node* i = low->prev;

        for (Node* j = low; j != high; j = j->next) {
            if (j->data <= pivot) {
                i = (i == nullptr) ? low : i->next;
                swap(i->data, j->data);
            }
        }
        i = (i == nullptr) ? low : i->next;
        swap(i->data, high->data);
        return i;
    }

    void quickSortRec(Node* low, Node* high) {
        if (low && high && low != high && low != high->next) {
            Node* pivot = partition(low, high);
            quickSortRec(low, pivot->prev);
            quickSortRec(pivot->next, high);
        }
    }

    void quickSort() {
        Node* tail = head;
        while (tail && tail->next) {
            tail = tail->next;
        }
        quickSortRec(head, tail);
    }

};

int main() {
    DoublyLinkedList dll;

    // 1. append: 리스트 끝에 노드 추가
    dll.append(3);
    dll.append(1);
    dll.append(4);
    dll.append(2);
    cout << "After append operations (3, 1, 4, 2):" << endl;
    dll.printList();  // Output: 3 -> 1 -> 4 -> 2 -> NULL

    // 2. prepend: 리스트 처음에 노드 추가
    dll.prepend(0);
    cout << "\nAfter prepend operation (0):" << endl;
    dll.printList();  // Output: 0 -> 3 -> 1 -> 4 -> 2 -> NULL

    // 3. insertAfter: 특정 노드 뒤에 삽입
    dll.insertAfter(3, 5);
    cout << "\nAfter inserting 5 after 3:" << endl;
    dll.printList();  // Output: 0 -> 3 -> 5 -> 1 -> 4 -> 2 -> NULL

    // 4. deleteNode: 특정 값을 가진 노드 삭제
    dll.deleteNode(5);
    cout << "\nAfter deleting 5:" << endl;
    dll.printList();  // Output: 0 -> 3 -> 1 -> 4 -> 2 -> NULL

    // 5. search: 리스트에서 특정 값 검색
    cout << "\nSearch for 4: " << (dll.search(4) ? "Found" : "Not Found") << endl;  // Output: Found
    cout << "Search for 7: " << (dll.search(7) ? "Found" : "Not Found") << endl;    // Output: Not Found

    // 6. reverse: 리스트를 뒤집기
    dll.reverse();
    cout << "\nAfter reversing the list:" << endl;
    dll.printList();  // Output: 2 -> 4 -> 1 -> 3 -> 0 -> NULL

    // 7. printReverse: 리스트를 역순으로 출력
    cout << "\nPrint the list in reverse order:" << endl;
    dll.printReverse();  // Output: 0 <- 3 <- 1 <- 4 <- 2 <- NULL

    // 8. Sorting: Bubble Sort
    cout << "\nSorting the list using Bubble Sort:" << endl;
    dll.bubbleSort();
    dll.printList();  // Output: 0 -> 1 -> 2 -> 3 -> 4 -> NULL

    // 9. Sorting: Selection Sort
    dll.append(3);
    dll.append(1);
    cout << "\nAfter adding 3 and 1 for Selection Sort:" << endl;
    dll.printList();  // Output: 0 -> 1 -> 2 -> 3 -> 4 -> 3 -> 1 -> NULL

    dll.selectionSort();
    cout << "\nAfter Selection Sort:" << endl;
    dll.printList();  // Output: 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> NULL

    // 10. Sorting: Insertion Sort
    dll.append(5);
    dll.append(0);
    cout << "\nAfter adding 5 and 0 for Insertion Sort:" << endl;
    dll.printList();  // Output: 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> 0 -> NULL

    dll.insertionSort();
    cout << "\nAfter Insertion Sort:" << endl;
    dll.printList();  // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> NULL

    // 11. Sorting: Merge Sort
    cout << "\nSorting the list using Merge Sort:" << endl;
    dll.mergeSort();
    dll.printList();  // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> NULL

    // 12. Sorting: Quick Sort
    dll.append(6);
    dll.append(2);
    cout << "\nAfter adding 6 and 2 for Quick Sort:" << endl;
    dll.printList();  // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> 6 -> 2 -> NULL

    dll.quickSort();
    cout << "\nAfter Quick Sort:" << endl;
    dll.printList();  // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 2 -> 3 -> 3 -> 4 -> 5 -> 6 -> NULL

    return 0;
}
