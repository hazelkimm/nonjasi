#include <iostream>
#include <vector>
using namespace std;

// Max-Heap Class
class MaxHeap {
private:
    vector<int> elements;

    // Bubble up to maintain max-heap property
    void bubbleUp(int index) {
        while (index > 0 && elements[index] > elements[(index - 1) / 2]) {
            swap(elements[index], elements[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // Bubble down to maintain max-heap property
    void bubbleDown(int index) {
        int size = elements.size();
        while (index * 2 + 1 < size) {
            int child = index * 2 + 1;
            if (child + 1 < size && elements[child + 1] > elements[child]) {
                child++;
            }
            if (elements[index] >= elements[child]) {
                break;
            }
            swap(elements[index], elements[child]);
            index = child;
        }
    }

public:
    // Insert a value into the max-heap
    void insert(int value) {
        elements.push_back(value);
        bubbleUp(elements.size() - 1);
    }

    // Remove and return the maximum element
    int pop() {
        if (elements.empty()) {
            throw runtime_error("Max-Heap is empty!");
        }
        int maxValue = elements[0];
        elements[0] = elements.back();
        elements.pop_back();
        bubbleDown(0);
        return maxValue;
    }

    // Print the max-heap
    void print() const {
        for (int value : elements) {
            cout << value << " ";
        }
        cout << endl;
    }
};

// Main function to test the Max-Heap
int main() {
    cout << "\nMax-Heap Implementation:\n";

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