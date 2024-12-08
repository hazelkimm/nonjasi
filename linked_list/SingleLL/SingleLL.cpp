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
// Sorting: Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort

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

    // Selection Sort for Singly Linked List
    void selectionSort() {
        Node* current = head;

        while (current) {
            Node* minNode = current;
            Node* nextNode = current->next;

            while (nextNode) {
                if (nextNode->data < minNode->data) {
                    minNode = nextNode;
                }
                nextNode = nextNode->next;
            }

            // Swap data between current node and minNode
            if (minNode != current) {
                swap(current->data, minNode->data);
            }

            current = current->next;
        }
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

    // Helper function (for Merge Sort): Split the list into two halves
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

    // Helper function (for Merge Sort): Merge two sorted lists
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

    // Quick Sort
    Node* getTail(Node* current) {
        while (current != nullptr && current->next != nullptr) {
            current = current->next;
        }
        return current;
    }

    Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
        Node* pivot = end;
        Node* prev = nullptr;
        Node* current = head;
        Node* tail = pivot;

        while (current != pivot) {
            if (current->data < pivot->data) {
                if (*newHead == nullptr) {
                    *newHead = current;
                }
                prev = current;
                current = current->next;
            } else {
                if (prev) {
                    prev->next = current->next;
                }
                Node* temp = current->next;
                current->next = nullptr;
                tail->next = current;
                tail = current;
                current = temp;
            }
        }

        if (*newHead == nullptr) {
            *newHead = pivot;
        }
        *newEnd = tail;

        return pivot;
    }

    Node* quickSortRec(Node* head, Node* end) {
        if (!head || head == end) {
            return head;
        }

        Node* newHead = nullptr;
        Node* newEnd = nullptr;

        Node* pivot = partition(head, end, &newHead, &newEnd);

        if (newHead != pivot) {
            Node* temp = newHead;
            while (temp->next != pivot) {
                temp = temp->next;
            }
            temp->next = nullptr;

            newHead = quickSortRec(newHead, temp);

            temp = getTail(newHead);
            temp->next = pivot;
        }

        pivot->next = quickSortRec(pivot->next, newEnd);

        return newHead;
    }

    void quickSort() {
        head = quickSortRec(head, getTail(head));
    }
};

int main() {
    SinglyLinkedList list;

    // 1. append: 리스트 끝에 노드 추가
    list.append(3);
    list.append(1);
    list.append(4);
    list.append(2);
    cout << "After append operations (3, 1, 4, 2):" << endl;
    list.printList();  // Output: 3 -> 1 -> 4 -> 2 -> NULL

    // 2. prepend: 리스트 처음에 노드 추가
    list.prepend(0);
    cout << "\nAfter prepend operation (0):" << endl;
    list.printList();  // Output: 0 -> 3 -> 1 -> 4 -> 2 -> NULL

    // 3. insertAfter: 특정 값 뒤에 노드 삽입
    list.insertAfter(3, 5);
    cout << "\nAfter inserting 5 after 3:" << endl;
    list.printList();  // Output: 0 -> 3 -> 5 -> 1 -> 4 -> 2 -> NULL

    // 4. deleteNode: 특정 값을 가진 노드 삭제
    list.deleteNode(5);
    cout << "\nAfter deleting 5:" << endl;
    list.printList();  // Output: 0 -> 3 -> 1 -> 4 -> 2 -> NULL

    // 5. search: 리스트에서 특정 값 검색
    cout << "\nSearch for 4: " << (list.search(4) ? "Found" : "Not Found") << endl;  // Output: Found
    cout << "Search for 7: " << (list.search(7) ? "Found" : "Not Found") << endl;    // Output: Not Found

    // 6. size: 리스트 크기 반환
    cout << "\nSize of the list: " << list.size() << endl;  // Output: 5

    // 7. reverse: 리스트 반전
    list.reverse();
    cout << "\nAfter reversing the list:" << endl;
    list.printList();  // Output: 2 -> 4 -> 1 -> 3 -> 0 -> NULL

    // 8. removeDuplicates: 중복 노드 제거
    list.append(4);
    list.append(2);
    cout << "\nAfter adding duplicates (4, 2):" << endl;
    list.printList();  // Output: 2 -> 4 -> 1 -> 3 -> 0 -> 4 -> 2 -> NULL

    list.removeDuplicates();
    cout << "\nAfter removing duplicates:" << endl;
    list.printList();  // Output: 2 -> 4 -> 1 -> 3 -> 0 -> NULL

    // 9. Sorting: Bubble Sort
    cout << "\nSorting the list using Bubble Sort:" << endl;
    list.bubbleSort();
    list.printList();  // Output: 0 -> 1 -> 2 -> 3 -> 4 -> NULL

    // 10. Sorting: Selection Sort
    list.append(3);
    list.append(1);
    cout << "\nAfter adding 3 and 1 for Selection Sort:" << endl;
    list.printList();  // Output: 0 -> 1 -> 2 -> 3 -> 4 -> 3 -> 1 -> NULL

    list.selectionSort();
    cout << "\nAfter Selection Sort:" << endl;
    list.printList();  // Output: 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> NULL

    // 11. Sorting: Insertion Sort
    list.append(5);
    list.append(0);
    cout << "\nAfter adding 5 and 0 for Insertion Sort:" << endl;
    list.printList();  // Output: 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> 0 -> NULL

    list.insertionSort();
    cout << "\nAfter Insertion Sort:" << endl;
    list.printList();  // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> NULL

    // 12. Sorting: Merge Sort
    cout << "\nSorting the list using Merge Sort:" << endl;
    list.mergeSort();
    list.printList();  // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> NULL

    // 13. Sorting: Quick Sort
    list.append(6);
    list.append(2);
    cout << "\nAfter adding 6 and 2 for Quick Sort:" << endl;
    list.printList();  // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> 6 -> 2 -> NULL

    list.quickSort();
    cout << "\nAfter Quick Sort:" << endl;
    list.printList();  // Output: 0 -> 0 -> 1 -> 1 -> 2 -> 2 -> 3 -> 3 -> 4 -> 5 -> 6 -> NULL

    return 0;
}
