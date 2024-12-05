#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Pair typedef
typedef pair<int, int> Pair;

// Priority Queue class for pairs (min-heap)
class PriorityQueue {
private:
    vector<Pair> elements;

    // Bubble up to maintain min-heap property
    void bubbleUp(int index) {
        while (index > 0 && elements[index] < elements[(index - 1) / 2]) {
            swap(elements[index], elements[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // Bubble down to maintain min-heap property
    void bubbleDown(int index) {
        int size = elements.size();
        while (index * 2 + 1 < size) {
            int child = index * 2 + 1;
            if (child + 1 < size && elements[child + 1] < elements[child]) {
                child++;
            }
            if (elements[index] <= elements[child]) {
                break;
            }
            swap(elements[index], elements[child]);
            index = child;
        }
    }

public:
    // Insert into the priority queue
    void insert(Pair value) {
        elements.push_back(value);
        bubbleUp(elements.size() - 1);
    }

    // Pop the minimum pair
    Pair pop() {
        if (elements.empty()) {
            throw runtime_error("Priority queue is empty!");
        }
        Pair minValue = elements[0];
        elements[0] = elements.back();
        elements.pop_back();
        bubbleDown(0);
        return minValue;
    }

    // Print the priority queue
    void print() const {
        for (Pair value : elements) {
            cout << "(" << value.first << ", " << value.second << ") ";
        }
        cout << endl;
    }

    // Check if the priority queue is empty
    bool isEmpty() const {
        return elements.empty();
    }
};

// Node class for the linked list
class Node {
public:
    PriorityQueue heap;
    Node* next;

    Node() : next(nullptr) {}
};

// Linked list class
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Add a new node with an empty heap
    void addNode() {
        Node* newNode = new Node();
        newNode->next = head;
        head = newNode;
    }

    // Get the head node
    Node* getHead() const {
        return head;
    }

    // Print all heaps in the linked list
    void printHeaps() const {
        Node* current = head;
        int index = 0;
        while (current != nullptr) {
            cout << "Heap in Node " << index++ << ": ";
            current->heap.print();
            current = current->next;
        }
    }

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// Test the implementation
int main() {
    cout << "\nMin-Heap with Pairs in Linked List:\n";

    LinkedList list;
    list.addNode();
    list.addNode();

    Node* head = list.getHead();

    // Add elements to the first node's heap
    head->heap.insert({10, 20});
    head->heap.insert({5, 15});
    head->heap.insert({20, 10});

    // Add elements to the second node's heap
    head->next->heap.insert({15, 30});
    head->next->heap.insert({25, 25});
    head->next->heap.insert({30, 5});

    cout << "Heaps in the linked list after insertion:\n";
    list.printHeaps();

    // Pop elements from the heaps
    cout << "\nPopping elements from the first heap:\n";
    Pair p = head->heap.pop();
    cout << "Popped: (" << p.first << ", " << p.second << ")\n";
    cout << "Heap after popping: ";
    head->heap.print();

    return 0;
}