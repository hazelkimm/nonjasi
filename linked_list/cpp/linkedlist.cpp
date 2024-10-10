#include <iostream>

typedef int element;

class Node {
public:
    element data;
    Node* next;

    Node(element data) : data(data), next(nullptr) {}
};

class LList {
private:
    int size;
    Node* head;
    Node* tail;

public:
    LList() : size(0), head(nullptr), tail(nullptr) {}

    int get_size() const {
        return size;
    }

    bool is_empty() const {
        return size == 0;
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
        head = tail = nullptr;
        size = 0;
    }

    int get_first() const {
        return head ? head->data : -1;
    }

    int get_last() const {
        return tail ? tail->data : -1;
    }

    void print_list() const {
        Node* cur = head;
        while (cur != nullptr) {
            std::cout << cur->data << " ";
            cur = cur->next;
        }
        std::cout << std::endl;
    }

    void add_first(element item) {
        Node* temp = new Node(item);
        temp->next = head;
        head = temp;
        if (tail == nullptr) {
            tail = temp;
        }
        size++;
    }

    void add_after(Node* prev_node, element item) {
        if (prev_node == nullptr) return;

        Node* temp = new Node(item);
        temp->next = prev_node->next;
        prev_node->next = temp;
        if (temp->next == nullptr) {
            tail = temp;
        }
        size++;
    }

    Node* get_node_by_index(int index) const {
        if (index < 0) return nullptr;
        Node* p = head;
        for (int i = 0; i < index && p != nullptr; ++i) {
            p = p->next;
        }
        return p;
    }

    void add_by_index(int index, element item) {
        if (index < 0 || index > size) return;

        if (index == 0) {
            add_first(item);
            return;
        }

        Node* prev = get_node_by_index(index - 1);
        if (prev != nullptr) {
            add_after(prev, item);
        }
    }

    void add_to_ordered_list(element item) {
        Node* p = head;
        Node* q = nullptr;

        while (p != nullptr && p->data < item) {
            q = p;
            p = p->next;
        }

        if (q == nullptr) {
            add_first(item);
        } else {
            add_after(q, item);
        }
    }

    Node* find_node(element item) const {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == item) {
                return cur;
            }
            cur = cur->next;
        }
        return nullptr;
    }

    void remove_first() {
        if (head == nullptr) return;
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
        size--;
    }

    void remove_last() {
        if (head == nullptr) return;

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = head;
            while (temp->next != tail) {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        size--;
    }

    void remove_after(Node* prev_node) {
        if (prev_node == nullptr || prev_node->next == nullptr) return;

        Node* temp = prev_node->next;
        prev_node->next = temp->next;

        if (temp == tail) {
            tail = prev_node;
        }

        delete temp;
        size--;
    }

    void remove_by_index(int index) {
        if (index < 0) return;

        if (index == 0) {
            remove_first();
            return;
        }

        Node* prev = get_node_by_index(index - 1);
        if (prev != nullptr && prev->next != nullptr) {
            remove_after(prev);
        }
    }

    void remove_by_value(element item) {
        if (head == nullptr) return;

        if (head->data == item) {
            remove_first();
            return;
        }

        Node* prev = head;
        Node* cur = head->next;

        while (cur != nullptr && cur->data != item) {
            prev = cur;
            cur = cur->next;
        }

        if (cur != nullptr) {
            remove_after(prev);
        }
    }

    Node* merge(Node* list1, Node* list2) {
        Node dummy(0);
        Node* tail = &dummy;
        dummy.next = nullptr;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->data <= list2->data) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        tail->next = (list1 != nullptr) ? list1 : list2;
        return dummy.next;
    }

    void concat(LList& list2) {
        if (head == nullptr) {
            head = list2.head;
            tail = list2.tail;
        } else if (list2.head != nullptr) {
            tail->next = list2.head;
            tail = list2.tail;
        }
        size += list2.size;
        list2.head = list2.tail = nullptr;
        list2.size = 0;
    }

    Node* get_mid() const {
        if (head == nullptr) return nullptr;
        Node* slow = head;
        Node* fast = head;

        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    void sort() {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        Node* mid = get_mid();
        if (mid == nullptr) return;

        Node* half = mid->next;
        mid->next = nullptr;

        LList left_sorted;
        LList right_sorted;

        left_sorted.head = head;
        left_sorted.tail = mid;
        left_sorted.size = size / 2;

        right_sorted.head = half;
        right_sorted.tail = tail;
        right_sorted.size = size - left_sorted.size;

        left_sorted.sort();
        right_sorted.sort();

        head = merge(left_sorted.head, right_sorted.head);

        Node* cur = head;
        while (cur && cur->next) {
            cur = cur->next;
        }
        tail = cur;
        size = left_sorted.size + right_sorted.size;
    }

    // Insertion Sort
    void insertion_sort() {
        if (head == nullptr || head->next == nullptr) {
            return;  // 리스트가 비어있거나 요소가 하나인 경우
        }

        Node* sorted = nullptr;  // 정렬된 리스트의 시작점
        Node* cur = head;

        while (cur != nullptr) {
            Node* next = cur->next;  // 다음 노드를 미리 저장
            cur->next = nullptr;  // 현재 노드를 분리

            if (sorted == nullptr || sorted->data >= cur->data) {
                cur->next = sorted;
                sorted = cur;
            } else {
                Node* temp = sorted;
                while (temp->next != nullptr && temp->next->data < cur->data) {
                    temp = temp->next;
                }
                cur->next = temp->next;
                temp->next = cur;
            }
            cur = next;  // 다음 노드로 이동
        }

        head = sorted;

        Node* end = sorted;
        while (end->next != nullptr) {
            end = end->next;
        }
        tail = end;
    }

    // Selection Sort
    void selection_sort() {
        if (head == nullptr || head->next == nullptr) {
            return;  // 리스트가 비어있거나 요소가 하나인 경우
        }

        Node* cur = head;

        while (cur != nullptr) {
            Node* min = cur;
            Node* r = cur->next;

            // 현재 위치에서 최소값을 찾음
            while (r != nullptr) {
                if (r->data < min->data) {
                    min = r;
                }
                r = r->next;
            }

            // 최소값을 현재 위치의 값과 교환
            if (min != cur) {
                element temp = cur->data;
                cur->data = min->data;
                min->data = temp;
            }

            cur = cur->next;  // 다음 노드로 이동
        }
    }

    void reverse() {
        Node* prev = nullptr;
        Node* cur = head;
        Node* next = nullptr;

        while (cur) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        tail = head;
        head = prev;
    }

    void rotate(int d) {
        if (head == nullptr || d == 0 || size == 0) return;

        d = d % size;
        if (d == 0) return;

        if (d < 0) d = size + d;

        Node* new_tail = head;
        for (int i = 0; i < size - d - 1; ++i) {
            new_tail = new_tail->next;
        }

        Node* new_head = new_tail->next;
        new_tail->next = nullptr;

        Node* temp = head;
        head = new_head;

        Node* end = head;
        while (end->next != nullptr) {
            end = end->next;
        }
        end->next = temp;
        tail = new_tail;
    }



    bool hasCycle() const {
        Node* slow_ptr = head;
        Node* fast_ptr = head;
        
        while (fast_ptr != nullptr && fast_ptr->next != nullptr) {
            slow_ptr = slow_ptr->next;
            fast_ptr = fast_ptr->next->next;
            
            if (slow_ptr == fast_ptr) {
                return true;
            }
        }
        
        return false;
    }

    Node* detectCycle() const {
        if (head == nullptr || head->next == nullptr) {
            return nullptr;
        }
        
        Node* slow_ptr = head;
        Node* fast_ptr = head;
        Node* entry_ptr = head;
        
        while (fast_ptr->next != nullptr && fast_ptr->next->next != nullptr) {
            slow_ptr = slow_ptr->next;
            fast_ptr = fast_ptr->next->next;
            
            if (slow_ptr == fast_ptr) {
                while (slow_ptr != entry_ptr) {
                    slow_ptr = slow_ptr->next;
                    entry_ptr = entry_ptr->next;
                }
                return entry_ptr;
            }
        }
        
        return nullptr;
    }

    int* linkedlist_to_array() const {
        int* arr = new int[size];
        Node* current = head;
        int index = 0;
        while (current != nullptr) {
            arr[index++] = current->data;
            current = current->next;
        }
        return arr;
    }

    void array_to_linkedlist(int* arr, int array_size) {
        clear();  // 기존 리스트를 초기화합니다.
        for (int i = 0; i < array_size; i++) {
            if (tail == nullptr) {
                add_first(arr[i]);  // 리스트가 비어 있으면 add_first를 사용합니다.
            } else {
                add_after(tail, arr[i]);  // 그 외에는 add_after를 사용합니다.
            }
        }
    }


};

int main() {
    LList llist;

    // Initial list setup
    std::cout << "Adding 3, 2, 1 to the list using add_first:\n";
    llist.add_first(3); // Thursday
    llist.add_first(2); // Tuesday
    llist.add_first(1); // Monday
    llist.print_list();

    // Get size of the list
    std::cout << "Size of the list: " << llist.get_size() << "\n";

    // Get first and last elements
    std::cout << "First element: " << llist.get_first() << "\n";
    std::cout << "Last element: " << llist.get_last() << "\n";

    // Find a node
    std::cout << "Finding node with value 2:\n";
    Node* found = llist.find_node(2);
    std::cout << "Found: " << (found != nullptr ? found->data : -1) << "\n";

    // Insert at index
    std::cout << "Inserting 5 at index 1:\n";
    llist.add_by_index(1, 5);
    llist.print_list();

    // Ordered insertion
    std::cout << "Adding 4 to ordered list:\n";
    llist.add_to_ordered_list(4);
    llist.print_list();

    // Reverse the list
    std::cout << "Reversing the list:\n";
    llist.reverse();
    llist.print_list();

    // Sort the list
    std::cout << "Selection sorting the concatenated list:\n";
    llist.selection_sort();
    llist.print_list();

    // Rotate the list
    std::cout << "Rotating the list by 2 positions:\n";
    llist.rotate(2);
    llist.print_list();
    
    std::cout << "Insertion sort:\n";
    llist.insertion_sort();
    llist.print_list();

    // Remove first and last
    std::cout << "Removing first element:\n";
    llist.remove_first();
    llist.print_list();

    std::cout << "Removing last element:\n";
    llist.remove_last();
    llist.print_list();

    // Remove by value
    std::cout << "Removing node with value 4:\n";
    llist.remove_by_value(4);
    llist.print_list();

    // Clear the list
    std::cout << "Clearing the list:\n";
    llist.clear();
    llist.print_list();

    // Creating two lists for merging and concatenating
    LList list1;
    LList list2;
    list1.add_first(4);
    list1.add_first(2);
    list1.add_first(1);
    list2.add_first(5);
    list2.add_first(3);
    std::cout << "List 1:\n";
    list1.print_list();
    std::cout << "List 2:\n";
    list2.print_list();

    // Concatenate two lists
    std::cout << "Concatenating list 1 and list 2:\n";
    list1.concat(list2);
    list1.print_list();

    // Convert list1 to array and back to linked list
    int* array_from_list = list1.linkedlist_to_array();
    std::cout << "Array after converting from linked list:\n";
    for (int i = 0; i < list1.get_size(); i++) {
        std::cout << array_from_list[i] << " ";
    }
    std::cout << std::endl;

    list1.array_to_linkedlist(array_from_list, list1.get_size());
    std::cout << "Linked list after converting back from array:\n";
    list1.print_list();

    delete[] array_from_list;  // 동적 할당한 배열 해제

    return 0;
}
