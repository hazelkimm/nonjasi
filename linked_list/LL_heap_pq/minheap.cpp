#include <iostream>
#include <vector>
using namespace std;

// Min-Heap Class
class MinHeap {
private:
    vector<int> elements;

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
    // Insert a value into the min-heap
    void insert(int value) {
        elements.push_back(value);
        bubbleUp(elements.size() - 1);
    }

    // Remove and return the minimum element
    int pop() {
        if (elements.empty()) {
            throw runtime_error("Min-Heap is empty!");
        }
        int minValue = elements[0];
        elements[0] = elements.back();
        elements.pop_back();
        bubbleDown(0);
        return minValue;
    }

    // Print the min-heap
    void print() const {
        for (int value : elements) {
            cout << value << " ";
        }
        cout << endl;
    }
};

// Main function to test the Min-Heap
int main() {
    cout << "Min-Heap Implementation:\n";

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