#include <iostream>
#include <vector>
#include <utility> // For std::pair
using namespace std;

// Max-Heap Class
class MaxHeap {
private:
    vector<pair<int, int>> elements;

    // Compare two pairs for max-heap logic
    bool compare(pair<int, int> a, pair<int, int> b) {
        if (a.first != b.first) {
            return a.first > b.first; // Prioritize larger x
        }
        return a.second > b.second; // If x is equal, prioritize larger y
    }

    // Bubble up to maintain max-heap property
    void bubbleUp(int index) {
        while (index > 0 && compare(elements[index], elements[(index - 1) / 2])) {
            swap(elements[index], elements[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // Bubble down to maintain max-heap property
    void bubbleDown(int index) {
        int size = elements.size();
        while (index * 2 + 1 < size) {
            int child = index * 2 + 1;
            if (child + 1 < size && compare(elements[child + 1], elements[child])) {
                child++;
            }
            if (compare(elements[index], elements[child])) {
                break;
            }
            swap(elements[index], elements[child]);
            index = child;
        }
    }

public:
    // Insert a pair into the max-heap
    void insert(pair<int, int> value) {
        elements.push_back(value);
        bubbleUp(elements.size() - 1);
    }

    // Remove and return the maximum pair
    pair<int, int> pop() {
        if (elements.empty()) {
            throw runtime_error("Max-Heap is empty!");
        }
        pair<int, int> maxValue = elements[0];
        elements[0] = elements.back();
        elements.pop_back();
        bubbleDown(0);
        return maxValue;
    }

    // Print the max-heap
    void print() const {
        for (auto value : elements) {
            cout << "(" << value.first << ", " << value.second << ") ";
        }
        cout << endl;
    }
};

// Main function to test the Max-Heap
int main() {
    cout << "\nMax-Heap with Pairs Implementation:\n";

    MaxHeap heap;

    heap.insert({10, 20});
    heap.insert({15, 25});
    heap.insert({5, 10});
    heap.insert({10, 15});

    cout << "Max-Heap after insertions: ";
    heap.print();

    cout << "Popping maximum: ";
    pair<int, int> p = heap.pop();
    cout << "(" << p.first << ", " << p.second << ")\n";

    cout << "Max-Heap after popping: ";
    heap.print();

    return 0;
}