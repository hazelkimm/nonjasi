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
#include <algorithm>
#include <climits>
#include <unordered_set>
using namespace std;

// Node 클래스 정의
class Node {
public:
    vector<int> queue;   // 큐 데이터를 저장하는 벡터
    int capacity;        // 큐의 최대 용량
    Node* next;          // 다음 노드 포인터
    Node* prev;          // 이전 노드 포인터

    Node(int capacity) : capacity(capacity), next(nullptr), prev(nullptr) {}
};

// LinkedListQueue 클래스 정의
class LinkedListQueue {
private:
    Node* head;          // 첫 번째 노드
    Node* tail;          // 마지막 노드
    int capacity;        // 각 노드의 최대 용량

public:
    // 1. 생성자: 큐 초기화
    LinkedListQueue(int capacity) : capacity(capacity) {
        head = new Node(capacity);
        tail = head;
    }

    // 2. 요소 추가
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

    // 3. 첫 번째 요소 제거
    int pop() {
        if (head->queue.empty()) {
            if (head->next) {
                Node* temp = head;
                head = head->next;
                head->prev = nullptr;
                delete temp;
                return pop();
            } else {
                throw runtime_error("큐가 비어 있습니다.");
            }
        }
        int value = head->queue.front();
        head->queue.erase(head->queue.begin());
        return value;
    }

    // 4. 첫 번째 요소 제거 후 재배치
    int pop_and_shift() {
        int poppedValue = pop();

        // 뒤쪽 노드에서 요소를 가져와 앞쪽 노드를 채우기
        Node* current = head;
        while (current->next) {
            while (current->queue.size() < capacity && !current->next->queue.empty()) {
                current->queue.push_back(current->next->queue.front());
                current->next->queue.erase(current->next->queue.begin());
            }
            current = current->next;
        }

        // 마지막 노드가 비었으면 제거
        if (tail->queue.empty() && tail != head) {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }

        return poppedValue;
    }

    // 5. 큐의 첫 번째 요소 반환
    int peek() {
        if (head->queue.empty()) throw runtime_error("큐가 비어 있습니다.");
        return head->queue.front();
    }

    // 6. 큐 전체 요소 개수 반환
    int total_size() {
        int size = 0;
        Node* current = head;
        while (current) {
            size += current->queue.size();
            current = current->next;
        }
        return size;
    }

    // 7. 큐 출력
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

    // 8. 특정 인덱스의 요소 반환
    int get_element_at(int index) {
        Node* current = head;
        while (current) {
            if (index < current->queue.size()) return current->queue[index];
            index -= current->queue.size();
            current = current->next;
        }
        throw out_of_range("인덱스가 범위를 초과했습니다.");
    }

    // 9. 다른 큐와 병합
    void merge_queues(LinkedListQueue& other) {
        Node* current = other.head;
        while (current) {
            for (int value : current->queue) {
                enqueue(value);
            }
            current = current->next;
        }
    }

    // 10. 큐 내 모든 요소의 합계 반환
    int sum_queue() {
        int sum = 0;
        Node* current = head;
        while (current) {
            for (int value : current->queue) {
                sum += value;
            }
            current = current->next;
        }
        return sum;
    }

    // 11. 큐 내 최댓값 반환
    int find_max() {
        if (head->queue.empty()) throw runtime_error("큐가 비어 있습니다.");
        int maxValue = INT_MIN;
        Node* current = head;
        while (current) {
            for (int value : current->queue) {
                maxValue = max(maxValue, value);
            }
            current = current->next;
        }
        return maxValue;
    }

    // 12. 큐 내 최솟값 반환
    int find_min() {
        if (head->queue.empty()) throw runtime_error("큐가 비어 있습니다.");
        int minValue = INT_MAX;
        Node* current = head;
        while (current) {
            for (int value : current->queue) {
                minValue = min(minValue, value);
            }
            current = current->next;
        }
        return minValue;
    }

    // 13. 특정 값을 가진 요소의 인덱스 반환
    int find_element(int value) {
        int index = 0;
        Node* current = head;
        while (current) {
            auto it = find(current->queue.begin(), current->queue.end(), value);
            if (it != current->queue.end()) return index + distance(current->queue.begin(), it);
            index += current->queue.size();
            current = current->next;
        }
        return -1;
    }

    // 14. 큐 역순 출력
    void print_reverse() {
        Node* current = tail;
        while (current) {
            for (auto it = current->queue.rbegin(); it != current->queue.rend(); ++it) {
                cout << *it << " ";
            }
            cout << "<- ";
            current = current->prev;
        }
        cout << "None" << endl;
    }

    // 15. 연결된 노드의 총 개수 반환
    int depth() {
        int depth = 0;
        Node* current = head;
        while (current) {
            depth++;
            current = current->next;
        }
        return depth;
    }

    // 16. 특정 값을 삭제
    void delete_element(int value) {
        Node* current = head;
        while (current) {
            current->queue.erase(remove(current->queue.begin(), current->queue.end(), value), current->queue.end());
            current = current->next;
        }
    }

    // 17. 큐 내 모든 요소의 평균값 반환
    double calculate_average() {
        int totalSum = sum_queue();
        int totalCount = total_size();
        if (totalCount == 0) throw runtime_error("큐가 비어 있습니다.");
        return static_cast<double>(totalSum) / totalCount;
    }

    // 18. 큐에서 중복 요소 제거
    void remove_duplicates() {
        unordered_set<int> seen;
        Node* current = head;
        while (current) {
            vector<int> newQueue;
            for (int value : current->queue) {
                if (seen.find(value) == seen.end()) {
                    newQueue.push_back(value);
                    seen.insert(value);
                }
            }
            current->queue = newQueue;
            current = current->next;
        }
    }

    // 19. 특정 값 범위 삭제
    void delete_in_range(int minValue, int maxValue) {
        Node* current = head;
        while (current) {
            vector<int> newQueue;
            for (int value : current->queue) {
                if (value < minValue || value > maxValue) {
                    newQueue.push_back(value);
                }
            }
            current->queue = newQueue;
            current = current->next;
        }
    }

    // 소멸자: 모든 노드 메모리 해제
    ~LinkedListQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// 메인 함수
int main() {
    LinkedListQueue queue(3);

    // 각 함수 테스트
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6);
    queue.enqueue(7);
    queue.print_queue();

    cout << "Popped: " << queue.pop() << endl;
    queue.print_queue();

    cout << "Popped and Shifted: " << queue.pop_and_shift() << endl;
    queue.print_queue();

    cout << "Total size: " << queue.total_size() << endl;
    cout << "Sum of queue: " << queue.sum_queue() << endl;

    queue.delete_element(3);
    queue.print_queue();

    cout << "Depth: " << queue.depth() << endl;

    queue.delete_in_range(2, 4);
    queue.print_queue();

    return 0;
}
