#include <iostream>
using namespace std;

// Node structure
struct Node {
    int val;
    Node* next;

    Node(int v) : val(v), next(nullptr) {}
};

// Min-Heap class implemented as a linked list
class MinHeap {
private:
    Node* head;

    // Helper function to create a new node
    Node* createNode(int value) {
        return new Node(value);
    }

public:
    MinHeap() : head(nullptr) {}

    // Insert into the min-heap
    void insert(int value) {
        Node* newNode = createNode(value);
        if (!head || newNode->val < head->val) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->val <= newNode->val) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Remove and return the minimum value
    int pop() {
        if (!head) {
            throw runtime_error("Min-Heap is empty!");
        }
        int minValue = head->val;
        Node* temp = head;
        head = head->next;
        delete temp;
        return minValue;
    }

    // Print the heap
    void print() const {
        Node* current = head;
        while (current) {
            cout << current->val << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Destructor to clean up memory
    ~MinHeap() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Main function to test the Min-Heap
int main() {
    cout << "Min-Heap with Linked List Implementation:\n";

    MinHeap heap;

    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);

    cout << "Min-Heap after insertions: ";
    heap.print();

    cout << "Popping minimum: " << heap.pop() << endl;
    cout << "Min-Heap after popping: ";
    heap.print();

    return 0;
}