/*
1. LinkedListQueue create(capacity): 큐를 생성하고 초기화합니다. 첫 번째 노드를 생성하고 최대 용량(capacity)을 설정합니다.
2. void enqueue(value): 큐에 요소를 추가합니다. 현재 노드의 용량을 초과하면 새 노드를 생성하여 연결합니다.
3. int pop(): 큐에서 첫 번째 요소를 제거하고 반환합니다. 현재 노드가 비어 있으면 다음 노드로 이동하여 처리합니다.
4. int pop_and_shift(): 큐에서 첫 번째 요소를 제거한 후, 뒤쪽 노드의 요소를 앞으로 이동하여 
     첫 번째 노드부터 capacity를 유지하도록 재배치합니다. 마지막 노드가 비면 삭제합니다.
5. int peek(): 큐의 첫 번째 요소를 반환합니다. 요소를 제거하지 않습니다.
6. int total_size(): 큐 전체의 요소 개수를 반환합니다. 모든 노드를 순회하며 요소 수를 계산합니다.
7. void print_queue():큐의 모든 요소를 출력합니다. 각 노드의 데이터를 화살표(->)로 연결하여 표시합니다.
8. int get_element_at(index): 큐에서 특정 인덱스의 요소를 반환합니다. 연결된 노드를 순회하며 인덱스를 계산합니다.
9. void merge_queues(queue): 다른 큐와 병합합니다. 병합된 요소는 현재 큐의 끝에 추가됩니다.
10. int sum_queue(): 큐 내 모든 요소의 합계를 반환합니다.
11. int find_max(): 큐 내에서 가장 큰 값을 반환합니다. 비어 있으면 예외를 발생시킵니다.
12. int find_min(): 큐 내에서 가장 작은 값을 반환합니다. 비어 있으면 예외를 발생시킵니다.
13. int find_element(value): 큐에서 특정 값을 가진 요소의 인덱스를 반환합니다. 값이 없으면 -1을 반환합니다.
14. void print_reverse(): 큐의 모든 요소를 역순으로 출력합니다. 각 노드의 데이터를 역순으로 처리하여 표시합니다.
15. int depth(): 연결된 노드의 총 개수를 반환합니다.
16. void delete_element(value): 큐에서 특정 값을 삭제합니다. 연결된 노드들에서 값을 찾고 제거합니다.
17. double calculate_average(): 큐 내 모든 요소의 평균값을 계산하여 반환합니다.
18. void remove_duplicates(): 큐에서 중복된 요소를 제거합니다. 요소 순서를 유지하며 중복을 제거합니다.
19. void delete_in_range(min_value, max_value): 큐에서 특정 값 범위(min_value ~ max_value)에 해당하는 요소를 삭제합니다.
*/

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

// Node 클래스 정의
class Node {
public:
    vector<int> queue; // 큐 데이터를 저장하는 벡터
    int capacity;      // 큐의 최대 용량
    Node* next;        // 다음 노드 포인터
    Node* prev;        // 이전 노드 포인터

    // 생성자
    Node(int cap) : capacity(cap), next(nullptr), prev(nullptr) {}
};

// LinkedListQueue 클래스 정의
class LinkedListQueue {
private:
    Node* head;  // 첫 번째 노드
    Node* tail;  // 마지막 노드
    int capacity; // 각 노드의 최대 용량

public:
    // 생성자
    LinkedListQueue(int cap) : capacity(cap) {
        head = new Node(cap);
        tail = head;
    }

    // 요소 추가
    void enqueue(int value) {
        if (tail->queue.size() < tail->capacity) {
            tail->queue.push_back(value);
        } else {
            Node* newNode = new Node(capacity);
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            tail->queue.push_back(value);
        }
    }

    // 첫 번째 요소 제거
    int pop() {
        if (head->queue.empty()) {
            if (head->next) {
                head = head->next;
                head->prev = nullptr;
                return pop();
            } else {
                throw out_of_range("큐가 비어 있습니다.");
            }
        }
        int value = head->queue.front();
        head->queue.erase(head->queue.begin());
        return value;
    }

    // 첫 번째 요소 제거 후 재배치
    int pop_and_shift() {
        if (head->queue.empty()) {
            if (head->next) {
                head = head->next;
                head->prev = nullptr;
                return pop_and_shift();
            } else {
                throw out_of_range("큐가 비어 있습니다.");
            }
        }

        int poppedValue = head->queue.front();
        head->queue.erase(head->queue.begin());

        // 뒤쪽 노드의 요소를 앞으로 이동
        Node* current = head;
        while (current->next) {
            while (current->queue.size() < capacity && !current->next->queue.empty()) {
                current->queue.push_back(current->next->queue.front());
                current->next->queue.erase(current->next->queue.begin());
            }
            current = current->next;
        }

        // 마지막 노드가 비어 있으면 제거
        if (current->queue.empty() && current != head) {
            if (current->prev) {
                current->prev->next = nullptr;
            }
            tail = current->prev;
            delete current;
        }

        return poppedValue;
    }

    // 첫 번째 요소 반환 (제거하지 않음)
    int peek() {
        if (head->queue.empty()) {
            if (head->next) {
                head = head->next;
                head->prev = nullptr;
                return peek();
            } else {
                throw out_of_range("큐가 비어 있습니다.");
            }
        }
        return head->queue.front();
    }

    // 전체 크기 반환
    int total_size() {
        int size = 0;
        Node* current = head;
        while (current) {
            size += current->queue.size();
            current = current->next;
        }
        return size;
    }

    // 큐 출력
    void print_queue() {
        Node* current = head;
        while (current) {
            cout << "[";
            for (size_t i = 0; i < current->queue.size(); ++i) {
                cout << current->queue[i];
                if (i < current->queue.size() - 1) cout << ", ";
            }
            cout << "] -> ";
            current = current->next;
        }
        cout << "None" << endl;
    }

    // 특정 인덱스의 요소 반환
    int get_element_at(int index) {
        Node* current = head;
        while (current) {
            if (index < current->queue.size()) {
                return current->queue[index];
            }
            index -= current->queue.size();
            current = current->next;
        }
        throw out_of_range("인덱스가 범위를 초과했습니다.");
    }

    // 다른 큐와 병합
    void merge_queues(LinkedListQueue& queue) {
        Node* current = queue.head;
        while (current) {
            for (int value : current->queue) {
                enqueue(value);
            }
            current = current->next;
        }
    }

    // 큐의 모든 요소 합계 반환
    int sum_queue() {
        int total = 0;
        Node* current = head;
        while (current) {
            total += accumulate(current->queue.begin(), current->queue.end(), 0);
            current = current->next;
        }
        return total;
    }

    // 큐 내 최댓값 반환
    int find_max() {
        int max_value = INT_MIN;
        Node* current = head;
        while (current) {
            if (!current->queue.empty()) {
                max_value = max(max_value, *max_element(current->queue.begin(), current->queue.end()));
            }
            current = current->next;
        }
        if (max_value == INT_MIN) {
            throw runtime_error("큐가 비어 있습니다.");
        }
        return max_value;
    }

    // 큐 내 최솟값 반환
    int find_min() {
        int min_value = INT_MAX;
        Node* current = head;
        while (current) {
            if (!current->queue.empty()) {
                min_value = min(min_value, *min_element(current->queue.begin(), current->queue.end()));
            }
            current = current->next;
        }
        if (min_value == INT_MAX) {
            throw runtime_error("큐가 비어 있습니다.");
        }
        return min_value;
    }

    // 특정 값을 가진 요소의 인덱스 반환
    int find_element(int value) {
        int index = 0;
        Node* current = head;
        while (current) {
            auto it = find(current->queue.begin(), current->queue.end(), value);
            if (it != current->queue.end()) {
                return index + distance(current->queue.begin(), it);
            }
            index += current->queue.size();
            current = current->next;
        }
        return -1;
    }

    // 역순 출력
    void print_reverse() {
        Node* current = tail;
        while (current) {
            for (auto it = current->queue.rbegin(); it != current->queue.rend(); ++it) {
                cout << *it << " ";
            }
            if (current->prev) cout << "<- ";
            current = current->prev;
        }
        cout << "None" << endl;
    }

    // 연결된 노드 개수 반환
    int depth() {
        int depth = 0;
        Node* current = head;
        while (current) {
            depth++;
            current = current->next;
        }
        return depth;
    }

    // 특정 값 삭제
    void delete_element(int value) {
        Node* current = head;
        while (current) {
            current->queue.erase(remove(current->queue.begin(), current->queue.end(), value), current->queue.end());
            current = current->next;
        }
    }

    // 평균값 계산
    double calculate_average() {
        int total_sum = sum_queue();
        int total_elements = total_size();
        if (total_elements == 0) {
            throw runtime_error("큐가 비어 있습니다.");
        }
        return static_cast<double>(total_sum) / total_elements;
    }

    // 중복 제거
    void remove_duplicates() {
        set<int> seen;
        Node* current = head;
        while (current) {
            vector<int> new_queue;
            for (int value : current->queue) {
                if (seen.find(value) == seen.end()) {
                    new_queue.push_back(value);
                    seen.insert(value);
                }
            }
            current->queue = new_queue;
            current = current->next;
        }
    }

    // 값 범위 삭제
    void delete_in_range(int min_value, int max_value) {
        Node* current = head;
        while (current) {
            current->queue.erase(remove_if(current->queue.begin(), current->queue.end(),
                                           [&](int value) { return value >= min_value && value <= max_value; }),
                                 current->queue.end());
            current = current->next;
        }
    }
};

int main() {
    // 큐 생성
    LinkedListQueue queue(3);

    // 1. Enqueue 테스트
    cout << "1. Enqueue Test" << endl;
    for (int i = 1; i <= 10; ++i) {
        queue.enqueue(i);
    }
    queue.print_queue();

    // 2. Pop 테스트
    cout << "\n2. Pop Test" << endl;
    cout << "Popped value: " << queue.pop() << endl;
    queue.print_queue();

    // 3. Pop and Shift 테스트
    cout << "\n3. Pop and Shift Test" << endl;
    cout << "Popped value: " << queue.pop_and_shift() << endl;
    queue.print_queue();

    // 4. Peek 테스트
    cout << "\n4. Peek Test" << endl;
    cout << "First value: " << queue.peek() << endl;

    // 5. Total Size 테스트
    cout << "\n5. Total Size Test" << endl;
    cout << "Total size: " << queue.total_size() << endl;

    // 6. Get Element At 테스트
    cout << "\n6. Get Element At Test" << endl;
    cout << "Element at index 4: " << queue.get_element_at(4) << endl;

    // 7. Merge Queues 테스트
    cout << "\n7. Merge Queues Test" << endl;
    LinkedListQueue queue2(3);
    for (int i = 20; i <= 22; ++i) {
        queue2.enqueue(i);
    }
    queue.merge_queues(queue2);
    queue.print_queue();

    // 8. Sum Queue 테스트
    cout << "\n8. Sum Queue Test" << endl;
    cout << "Sum of queue: " << queue.sum_queue() << endl;

    // 9. Find Max 테스트
    cout << "\n9. Find Max Test" << endl;
    cout << "Max value: " << queue.find_max() << endl;

    // 10. Find Min 테스트
    cout << "\n10. Find Min Test" << endl;
    cout << "Min value: " << queue.find_min() << endl;

    // 11. Find Element 테스트
    cout << "\n11. Find Element Test" << endl;
    cout << "Index of element 5: " << queue.find_element(5) << endl;

    // 12. Print Reverse 테스트
    cout << "\n12. Print Reverse Test" << endl;
    queue.print_reverse();

    // 13. Depth 테스트
    cout << "\n13. Depth Test" << endl;
    cout << "Depth: " << queue.depth() << endl;

    // 14. Delete Element 테스트
    cout << "\n14. Delete Element Test" << endl;
    queue.delete_element(4);
    queue.print_queue();

    // 15. Calculate Average 테스트
    cout << "\n15. Calculate Average Test" << endl;
    cout << "Average: " << queue.calculate_average() << endl;

    // 16. Remove Duplicates 테스트
    cout << "\n16. Remove Duplicates Test" << endl;
    queue.enqueue(5);
    queue.enqueue(6);
    queue.enqueue(6);
    queue.remove_duplicates();
    queue.print_queue();

    // 17. Delete in Range 테스트
    cout << "\n17. Delete in Range Test" << endl;
    queue.delete_in_range(2, 6);
    queue.print_queue();

    return 0;
}
