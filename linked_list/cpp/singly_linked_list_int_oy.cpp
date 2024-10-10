// 1. Node 클래스 및 SinglyLinkedList 클래스 초기화
//    - 노드와 단일 연결 리스트 초기화
// 2. insert_at_index
//    - 특정 인덱스에 노드를 삽입하는 함수
// 3. delete_at_index
//    - 특정 인덱스의 노드를 삭제하는 함수
// 4. find
//    - 리스트에서 특정 값이 처음 나타나는 위치(인덱스)를 반환하는 함수
// 5. delete_value
//    - 특정 값을 가진 노드를 삭제하는 함수 (값을 기준으로 삭제)
// 6. swap_nodes
//    - 두 인덱스의 노드를 스왑하는 함수
// 7. length
//    - 단일 연결 리스트의 길이를 반환하는 함수
// 8. contains
//    - 단일 연결 리스트에서 특정 값이 있는지 확인하는 함수
// 9. nth_from_end
//    - 단일 연결 리스트에서 끝에서 n번째 노드를 반환하는 함수
// 10. get_middle
//     - 단일 연결 리스트의 중간 지점을 찾는 함수
// 11. reverse
//     - 단일 연결 리스트를 역순으로 만드는 함수
// 12. reverse_in_groups
//     - 주어진 크기(k)로 리스트를 그룹화하여 각 그룹을 역순으로 만드는 함수
// 13. remove_duplicates
//     - 단일 연결 리스트에서 중복된 노드를 제거하는 함수
// 14. pop_last
//     - 단일 연결 리스트에서 마지막 노드를 반환하고 삭제하는 함수
// 15. slice_range
//     - 단일 연결 리스트에서 특정 범위를 슬라이싱해서 반환하는 함수
// 16. bubble_sort
//     - 버블 정렬로 단일 연결 리스트를 정렬하는 함수
// 17. insertion_sort
//     - 삽입 정렬로 단일 연결 리스트를 정렬하는 함수
// 18. selection_sort
//     - 선택 정렬로 단일 연결 리스트를 정렬하는 함수
// 19. merge_sort
//     - 병합 정렬로 단일 연결 리스트를 정렬하는 함수
// 20. detect_cycle
//     - 단일 연결 리스트에 사이클이 있는지 확인하는 함수
// 21. remove_cycle
//     - 단일 연결 리스트에서 사이클이 존재할 경우, 이를 제거하는 함수
// 22. append_list
//     - 다른 단일 연결 리스트를 현재 리스트의 끝에 추가하는 함수
// 23. sorted_insert_in_sorted_list
//     - 정렬된 단일 연결 리스트에 새로운 노드를 올바른 위치에 삽입하는 함수
// 24. count_values() 노드 값을 기준으로 등장 횟수를 세고, 이를 unordered_map에 저장하는 함수


#include <iostream>
#include <unordered_map>
using namespace std;

// Node 클래스 정의
class Node {
public:
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// SinglyLinkedList 클래스 정의
class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    // 2. 특정 인덱스에 값을 가진 노드 삽입하는 함수
    void insert_at_index(int index, int data) {
        if (index < 0) {
            cout << "Index out of bounds" << endl;
            return;
        }

        Node* new_node = new Node(data);

        if (index == 0) {
            new_node->next = head;
            head = new_node;
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1 && current != nullptr; i++) {
                current = current->next;
            }

            if (current == nullptr) {
                cout << "Index out of bounds" << endl;
                delete new_node;
                return;
            }

            new_node->next = current->next;
            current->next = new_node;
        }
    }

    // 3. 특정 인덱스의 노드를 삭제하는 함수
    void delete_at_index(int index) {
        if (index < 0 || head == nullptr) {
            cout << "Index out of bounds" << endl;
            return;
        }

        Node* current = head;
        if (index == 0) {
            head = current->next;
            delete current;
        } else {
            for (int i = 0; i < index - 1 && current != nullptr; i++) {
                current = current->next;
            }

            if (current == nullptr || current->next == nullptr) {
                cout << "Index out of bounds" << endl;
                return;
            }

            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }

    // 4. 리스트에서 특정 값이 처음 나타나는 위치(인덱스)를 반환하는 함수
    int find(int data) {
        Node* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->data == data) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;  // 값이 리스트에 없을 경우
    }

    // 5. 특정 값을 가진 노드를 삭제하는 함수 (값을 기준으로 삭제)
    void delete_value(int data) {
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->data == data) {
                if (prev != nullptr) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    // 6. 두 인덱스의 노드를 스왑하는 함수
    void swap_nodes(int index1, int index2) {
        if (index1 == index2) return;

        if (index1 > index2) {
            swap(index1, index2);
        }

        Node* prev1 = nullptr;
        Node* prev2 = nullptr;
        Node* node1 = head;
        Node* node2 = head;

        for (int i = 0; i < index1 && node1 != nullptr; i++) {
            prev1 = node1;
            node1 = node1->next;
        }
        for (int i = 0; i < index2 && node2 != nullptr; i++) {
            prev2 = node2;
            node2 = node2->next;
        }

        if (node1 == nullptr || node2 == nullptr) return;

        if (prev1 != nullptr) {
            prev1->next = node2;
        } else {
            head = node2;
        }

        if (prev2 != nullptr) {
            prev2->next = node1;
        } else {
            head = node1;
        }

        Node* temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
    }

    // 7. 리스트 길이 리턴하는 함수
    int length() {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    // 8. 리스트에서 특정 값의 노드 존재 여부 확인 함수
    bool contains(int data) {
        return find(data) != -1;
    }

    // 9. 리스트에서 n번째 마지막 노드 반환 함수
    int nth_from_end(int n) {
        int len = length();
        if (n > len || n <= 0) return -1;

        Node* current = head;
        for (int i = 0; i < len - n; i++) {
            current = current->next;
        }
        return current->data;
    }

    // 10. 중간 지점 찾기 함수
    Node* get_middle() {
        if (head == nullptr) return nullptr;

        Node* slow = head;
        Node* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    // 11. 리스트를 역순으로 만드는 함수
    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head = prev;
    }

    // 12. 주어진 크기(k)로 리스트를 그룹화하여 각 그룹을 역순으로 만드는 함수
    Node* reverse_k_nodes(Node* head, int k) {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;
        int count = 0;

        while (current != nullptr && count < k) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
            count++;
        }

        if (next != nullptr) {
            head->next = reverse_k_nodes(next, k);
        }

        return prev;
    }

    void reverse_in_groups(int k) {
        head = reverse_k_nodes(head, k);
    }

    // 13. 리스트에서 중복 노드 제거 함수
    void remove_duplicates() {
        Node* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->data == current->next->data) {
                Node* temp = current->next;
                current->next = temp->next;
                delete temp;
            } else {
                current = current->next;
            }
        }
    }

    // 14. 리스트에서 마지막 노드를 반환하고 삭제하는 함수
    int pop_last() {
        if (head == nullptr) return -1;

        Node* current = head;
        Node* prev = nullptr;

        while (current->next != nullptr) {
            prev = current;
            current = current->next;
        }

        int data = current->data;
        if (prev != nullptr) {
            prev->next = nullptr;
        } else {
            head = nullptr;
        }
        delete current;

        return data;
    }

    // 15. 범위 슬라이싱 함수
    SinglyLinkedList slice_range(int start, int end) {
        SinglyLinkedList sliced_list;
        if (start < 0 || end > length() || start > end) {
            cout << "Index out of bounds" << endl;
            return sliced_list;
        }

        Node* current = head;
        for (int i = 0; i < start && current != nullptr; i++) {
            current = current->next;
        }

        for (int i = start; i < end && current != nullptr; i++) {
            sliced_list.insert_at_index(i - start, current->data);
            current = current->next;
        }

        return sliced_list;
    }

    // 16. 버블 정렬 함수
    void bubble_sort() {
        Node* end = nullptr;
        while (end != head) {
            Node* current = head;
            while (current->next != end) {
                if (current->data > current->next->data) {
                    swap(current->data, current->next->data);
                }
                current = current->next;
            }
            end = current;
        }
    }

    // 17. 삽입 정렬 함수
    void insertion_sort() {
        Node* sorted_list = nullptr;
        Node* current = head;

        while (current != nullptr) {
            Node* next = current->next;
            sorted_list = sorted_insert(sorted_list, current);
            current = next;
        }

        head = sorted_list;
    }

    Node* sorted_insert(Node* sorted_list, Node* new_node) {
        if (sorted_list == nullptr || new_node->data < sorted_list->data) {
            new_node->next = sorted_list;
            return new_node;
        }

        Node* current = sorted_list;
        while (current->next != nullptr && current->next->data < new_node->data) {
            current = current->next;
        }

        new_node->next = current->next;
        current->next = new_node;

        return sorted_list;
    }

    // 18. 선택 정렬 함수
    void selection_sort() {
        Node* current = head;

        while (current != nullptr) {
            Node* min_node = current;
            Node* next = current->next;

            while (next != nullptr) {
                if (next->data < min_node->data) {
                    min_node = next;
                }
                next = next->next;
            }

            swap(current->data, min_node->data);
            current = current->next;
        }
    }

    // 19. 병합 정렬 함수
    void merge_sort() {
        if (!head || !head->next) return;

        Node* middle = get_middle();
        Node* next_to_middle = middle->next;

        middle->next = nullptr;

        SinglyLinkedList left_list;
        left_list.head = head;
        left_list.merge_sort();

        SinglyLinkedList right_list;
        right_list.head = next_to_middle;
        right_list.merge_sort();

        head = sorted_merge(left_list.head, right_list.head);
    }

    Node* sorted_merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->data <= right->data) {
            left->next = sorted_merge(left->next, right);
            return left;
        } else {
            right->next = sorted_merge(left, right->next);
            return right;
        }
    }

    // 20. 링크드 리스트에 사이클이 있는지 확인하는 함수
    bool detect_cycle() {
        Node* slow = head;
        Node* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }

    // 21. 링크드 리스트에서 사이클이 존재할 경우, 이를 제거하는 함수
    void remove_cycle() {
        if (head == nullptr) return;

        Node* slow = head;
        Node* fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;
        }

        if (slow == fast) {
            slow = head;
            while (slow->next != fast->next) {
                slow = slow->next;
                fast = fast->next;
            }
            fast->next = nullptr;
        }
    }

    // 22. 다른 링크드 리스트를 현재 리스트의 끝에 추가하는 함수
    void append_list(SinglyLinkedList& other_list) {
        if (head == nullptr) {
            head = other_list.head;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = other_list.head;
        }
    }

    // 23. 정렬된 링크드 리스트에 새로운 노드를 올바른 위치에 삽입하는 함수
    void sorted_insert_in_sorted_list(int data) {
        Node* new_node = new Node(data);

        if (head == nullptr || head->data >= new_node->data) {
            new_node->next = head;
            head = new_node;
        } else {
            Node* current = head;
            while (current->next != nullptr && current->next->data < new_node->data) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }
    }

    // 노드 값을 기준으로 등장 횟수를 세고, 이를 unordered_map에 저장하는 함수
    unordered_map<int, int> count_values() {
        unordered_map<int, int> value_count;
        Node* current = head;

        while (current != nullptr) {
            // 현재 노드의 값을 키로 하고, 등장 횟수를 증가시킴
            value_count[current->data]++;
            current = current->next;
        }

        return value_count;
    }

    // 리스트 출력 함수 (테스트용)
    void print_list() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "None" << endl;
    }
};

// 테스트 코드
int main() {
    SinglyLinkedList sll;
    sll.insert_at_index(0, 3);
    sll.insert_at_index(1, 1);
    sll.insert_at_index(2, 2);
    sll.insert_at_index(3, 5);
    sll.insert_at_index(4, 4);

    cout << "Original List:" << endl;
    sll.print_list();

    cout << "Reversed List:" << endl;
    sll.reverse();
    sll.print_list();

    cout << "Bubble Sort:" << endl;
    sll.bubble_sort();
    sll.print_list();

    cout << "Insertion Sort:" << endl;
    sll.insertion_sort();
    sll.print_list();

    cout << "Selection Sort:" << endl;
    sll.selection_sort();
    sll.print_list();

    cout << "Swapping index 1 and 3:" << endl;
    sll.swap_nodes(1, 3);
    sll.print_list();

    cout << "Length of the list: " << sll.length() << endl;

    cout << "Middle of the list: " << sll.get_middle()->data << endl;

    cout << "Merge Sort:" << endl;
    sll.merge_sort();
    sll.print_list();

    cout << "Slice from index 1 to 4:" << endl;
    SinglyLinkedList sliced_sll = sll.slice_range(1, 4);
    sliced_sll.print_list();

    cout << "Deleting node at index 2:" << endl;
    sll.delete_at_index(2);
    sll.print_list();

    cout << "Checking if list contains value 5: " << (sll.contains(5) ? "Yes" : "No") << endl;

    cout << "Removing duplicates:" << endl;
    sll.remove_duplicates();
    sll.print_list();

    cout << "Popping last node:" << endl;
    cout << "Popped value: " << sll.pop_last() << endl;
    sll.print_list();

    cout << "2nd node from the end: " << sll.nth_from_end(2) << endl;

    // 값의 등장 횟수를 세는 함수 호출
    unordered_map<int, int> value_count = sll.count_values();

    // 등장 횟수를 출력
    cout << "Value counts:" << endl;
    for (const auto& pair : value_count) {
        cout << pair.first << ": " << pair.second << " times" << endl;
    }

    return 0;
}
