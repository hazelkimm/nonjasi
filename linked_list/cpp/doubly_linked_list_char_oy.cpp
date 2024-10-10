// 1. Node 클래스 및 DoublyLinkedList 클래스 초기화
//    - 노드와 이중 연결 리스트 초기화
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
//    - 이중 연결 리스트의 길이를 반환하는 함수
// 8. contains
//    - 이중 연결 리스트에서 특정 값이 있는지 확인하는 함수
// 9. nth_from_end
//    - 이중 연결 리스트에서 끝에서 n번째 노드를 반환하는 함수
// 10. get_middle
//     - 이중 연결 리스트의 중간 지점을 찾는 함수
// 11. reverse
//     - 이중 연결 리스트를 역순으로 만드는 함수
// 12. reverse_in_groups
//     - 주어진 크기(k)로 리스트를 그룹화하여 각 그룹을 역순으로 만드는 함수
// 13. remove_duplicates
//     - 이중 연결 리스트에서 중복된 노드를 제거하는 함수
// 14. pop_last
//     - 이중 연결 리스트에서 마지막 노드를 반환하고 삭제하는 함수
// 15. slice_range
//     - 이중 연결 리스트에서 특정 범위를 슬라이싱해서 반환하는 함수
// 16. bubble_sort
//     - 버블 정렬로 이중 연결 리스트를 정렬하는 함수
// 17. insertion_sort
//     - 삽입 정렬로 이중 연결 리스트를 정렬하는 함수
// 18. selection_sort
//     - 선택 정렬로 이중 연결 리스트를 정렬하는 함수
// 19. merge_sort
//     - 병합 정렬로 이중 연결 리스트를 정렬하는 함수
// 20. detect_cycle
//     - 이중 연결 리스트에 사이클이 있는지 확인하는 함수
// 21. remove_cycle
//     - 이중 연결 리스트에서 사이클이 존재할 경우, 이를 제거하는 함수
// 22. append_list
//     - 다른 이중 연결 리스트를 현재 리스트의 끝에 추가하는 함수
// 23. sorted_insert_in_sorted_list
//     - 정렬된 이중 연결 리스트에 새로운 노드를 올바른 위치에 삽입하는 함수
// 24. 노드 값의 개수를 세어 딕셔너리처럼 반환하는 함수

#include <iostream>
#include <unordered_map>
using namespace std;

// 노드 클래스 정의
class Node {
public:
    char data;  // char 타입으로 변경
    Node* next;
    Node* prev;

    Node(char val) : data(val), next(nullptr), prev(nullptr) {}
};

// 이중 연결 리스트 클래스 정의
class DoublyLinkedList {
private:
    Node* head;

public:
    // 생성자
    DoublyLinkedList() : head(nullptr) {}

    // 2. 특정 인덱스에 값을 가진 노드 삽입하는 함수
    void insert_at_index(int index, char data) {
        if (index < 0 || index > length()) {
            throw out_of_range("Index out of bounds");
        }

        Node* new_node = new Node(data);

        if (index == 0) {
            new_node->next = head;
            if (head != nullptr) {
                head->prev = new_node;
            }
            head = new_node;
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            new_node->next = current->next;
            new_node->prev = current;
            if (current->next != nullptr) {
                current->next->prev = new_node;
            }
            current->next = new_node;
        }
    }

    // 3. 특정 인덱스의 노드를 삭제하는 함수
    void delete_at_index(int index) {
        if (index < 0 || index >= length()) {
            throw out_of_range("Index out of bounds");
        }

        if (index == 0) {
            Node* temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            delete temp;
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            Node* temp = current->next;
            current->next = temp->next;
            if (temp->next != nullptr) {
                temp->next->prev = current;
            }
            delete temp;
        }
    }

    // 4. 리스트에서 특정 값이 처음 나타나는 위치(인덱스)를 반환하는 함수
    int find(char data) {
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
    bool delete_value(char data) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == data) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                }
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                }
                if (current == head) {
                    head = current->next;
                }
                delete current;
                return true;  // 삭제 성공
            }
            current = current->next;
        }
        return false;  // 값이 리스트에 없을 경우
    }

    // 6. 두 인덱스의 노드 스왑하는 함수
    void swap_nodes(int index1, int index2) {
        if (index1 == index2) return;
        if (index1 > index2) swap(index1, index2);

        Node* node1 = head;
        Node* node2 = head;

        for (int i = 0; i < index1; i++) {
            node1 = node1->next;
        }
        for (int i = 0; i < index2; i++) {
            node2 = node2->next;
        }

        if (node1->prev) {
            node1->prev->next = node2;
        }
        if (node2->next) {
            node2->next->prev = node1;
        }

        node1->next, node2->next = node2->next, node1->next;
        node1->prev, node2->prev = node2->prev, node1->prev;

        if (node1->next) {
            node1->next->prev = node1;
        }
        if (node2->prev) {
            node2->prev->next = node2;
        }

        if (index1 == 0) {
            head = node2;
        } else if (index2 == 0) {
            head = node1;
        }
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
    bool contains(char data) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // 9. 리스트에서 n번째 마지막 노드 반환 함수
    char nth_from_end(int n) {
        int len = length();
        if (n > len || n <= 0) return '\0';

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
        Node* current = head;
        Node* temp = nullptr;

        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp != nullptr) {
            head = temp->prev;
        }
    }

    // 12. 주어진 크기(k)로 리스트를 그룹화하여 각 그룹을 역순으로 만드는 함수
    void reverse_in_groups(int k) {
        Node* current = head;
        Node* prev_group_end = nullptr;

        while (current != nullptr) {
            Node* group_start = current;
            Node* prev = nullptr;
            int count = 0;

            while (current != nullptr && count < k) {
                Node* next = current->next;
                current->next = prev;
                current->prev = next;
                prev = current;
                current = next;
                count++;
            }

            if (prev_group_end == nullptr) {
                head = prev;
            } else {
                prev_group_end->next = prev;
                prev->prev = prev_group_end;
            }

            prev_group_end = group_start;
        }
    }

    // 13. 리스트에서 중복 노드 제거 함수
    void remove_duplicates() {
        Node* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->data == current->next->data) {
                Node* temp = current->next;
                current->next = temp->next;
                if (temp->next != nullptr) {
                    temp->next->prev = current;
                }
                delete temp;
            } else {
                current = current->next;
            }
        }
    }

    // 14. 리스트에서 마지막 노드를 반환하고 삭제하는 함수
    char pop_last() {
        if (head == nullptr) return '\0';

        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }

        char data = current->data;
        if (current->prev != nullptr) {
            current->prev->next = nullptr;
        } else {
            head = nullptr;
        }
        delete current;

        return data;
    }

    // 15. 범위 슬라이싱 함수
    DoublyLinkedList slice_range(int start, int end) {
        if (start < 0 || end > length() || start > end) {
            throw out_of_range("Index out of bounds");
        }

        DoublyLinkedList sliced_list;
        Node* current = head;
        for (int i = 0; i < start; i++) {
            current = current->next;
        }

        for (int i = start; i < end; i++) {
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
            if (sorted_list != nullptr) {
                sorted_list->prev = new_node;
            }
            return new_node;
        }

        Node* current = sorted_list;
        while (current->next != nullptr && current->next->data < new_node->data) {
            current = current->next;
        }

        new_node->next = current->next;
        if (current->next != nullptr) {
            current->next->prev = new_node;
        }
        current->next = new_node;
        new_node->prev = current;

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
        if (next_to_middle) next_to_middle->prev = nullptr;

        DoublyLinkedList left_list;
        left_list.head = head;
        left_list.merge_sort();

        DoublyLinkedList right_list;
        right_list.head = next_to_middle;
        right_list.merge_sort();

        head = sorted_merge(left_list.head, right_list.head);
    }

    Node* sorted_merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->data <= right->data) {
            left->next = sorted_merge(left->next, right);
            if (left->next) left->next->prev = left;
            left->prev = nullptr;
            return left;
        } else {
            right->next = sorted_merge(left, right->next);
            if (right->next) right->next->prev = right;
            right->prev = nullptr;
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
        if (!head) return;

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

    // 22. 다른 이중 연결 리스트를 현재 리스트의 끝에 추가하는 함수
    void append_list(DoublyLinkedList& other_list) {
        if (!head) {
            head = other_list.head;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = other_list.head;
            if (other_list.head) {
                other_list.head->prev = current;
            }
        }
    }

    // 23. 정렬된 이중 연결 리스트에 새로운 노드를 올바른 위치에 삽입하는 함수
    void sorted_insert_in_sorted_list(char data) {
        Node* new_node = new Node(data);

        if (head == nullptr || head->data >= new_node->data) {
            new_node->next = head;
            if (head != nullptr) {
                head->prev = new_node;
            }
            head = new_node;
        } else {
            Node* current = head;
            while (current->next != nullptr && current->next->data < new_node->data) {
                current = current->next;
            }
            new_node->next = current->next;
            if (current->next != nullptr) {
                current->next->prev = new_node;
            }
            current->next = new_node;
            new_node->prev = current;
        }
    }

    // 24. 노드 값의 개수를 세어 딕셔너리처럼 반환하는 함수
    unordered_map<char, int> count_values() {
        unordered_map<char, int> value_counts;
        Node* current = head;
        while (current != nullptr) {
            value_counts[current->data]++;
            current = current->next;
        }
        return value_counts;
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
    DoublyLinkedList dll;
    dll.insert_at_index(0, 'c');
    dll.insert_at_index(1, 'a');
    dll.insert_at_index(2, 'b');
    dll.insert_at_index(3, 'e');
    dll.insert_at_index(4, 'd');
    dll.insert_at_index(5, 'a');  // 추가된 값

    cout << "Original List:" << endl;
    dll.print_list();

    cout << "Value Counts:" << endl;
    unordered_map<char, int> counts = dll.count_values();
    for (const auto& pair : counts) {
        cout << pair.first << ": " << pair.second << " times" << endl;
    }

    return 0;
}
