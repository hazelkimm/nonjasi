#include <iostream>
using namespace std;

// Node structure
struct Node {
    int val;
    Node* next;

    Node(int v) : val(v), next(nullptr) {}
};

// Max-Heap class implemented as a linked list
class MaxHeap {
private:
    Node* head;

    // Helper function to create a new node
    Node* createNode(int value) {
        return new Node(value);
    }

public:
    MaxHeap() : head(nullptr) {}

    // Insert into the max-heap
    void insert(int value) {
        Node* newNode = createNode(value);
        if (!head || newNode->val > head->val) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->val >= newNode->val) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Remove and return the maximum value
    int pop() {
        if (!head) {
            throw runtime_error("Max-Heap is empty!");
        }
        int maxValue = head->val;
        Node* temp = head;
        head = head->next;
        delete temp;
        return maxValue;
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
    ~MaxHeap() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Main function to test the Max-Heap
int main() {
    cout << "\nMax-Heap with Linked List Implementation:\n";

    MaxHeap heap;

    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);

    cout << "Max-Heap after insertions: ";
    heap.print();

    cout << "Popping maximum: " << heap.pop() << endl;
    cout << "Max-Heap after popping: ";
    heap.print();

    return 0;
}