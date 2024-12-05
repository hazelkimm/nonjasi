#include <iostream>
#include <vector>
#include <utility> // For std::pair
using namespace std;

// Min-Heap Class
class MinHeap {
private:
    vector<pair<int, int>> elements;

    // Compare two pairs for min-heap logic
    bool compare(pair<int, int> a, pair<int, int> b) {
        if (a.first != b.first) {
            return a.first < b.first; // Prioritize smaller x
        }
        return a.second < b.second; // If x is equal, prioritize smaller y
    }

    // Bubble up to maintain min-heap property
    void bubbleUp(int index) {
        while (index > 0 && compare(elements[index], elements[(index - 1) / 2])) {
            swap(elements[index], elements[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // Bubble down to maintain min-heap property
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
    // Insert a pair into the min-heap
    void insert(pair<int, int> value) {
        elements.push_back(value);
        bubbleUp(elements.size() - 1);
    }

    // Remove and return the minimum pair
    pair<int, int> pop() {
        if (elements.empty()) {
            throw runtime_error("Min-Heap is empty!");
        }
        pair<int, int> minValue = elements[0];
        elements[0] = elements.back();
        elements.pop_back();
        bubbleDown(0);
        return minValue;
    }

    // Print the min-heap
    void print() const {
        for (auto value : elements) {
            cout << "(" << value.first << ", " << value.second << ") ";
        }
        cout << endl;
    }
};

// Main function to test the Min-Heap
int main() {
    cout << "Min-Heap with Pairs Implementation:\n";

    MinHeap heap;

    heap.insert({10, 20});
    heap.insert({15, 25});
    heap.insert({5, 10});
    heap.insert({10, 15});

    cout << "Min-Heap after insertions: ";
    heap.print();

    cout << "Popping minimum: ";
    pair<int, int> p = heap.pop();
    cout << "(" << p.first << ", " << p.second << ")\n";

    cout << "Min-Heap after popping: ";
    heap.print();

    return 0;
}