#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

/**********************************************
 * CATALOG OF FUNCTIONS AND CLASSES
 **********************************************

 * GENERIC QUEUE (Queue<T>)
 1. `Queue<T>()`
    - Constructor that initializes an empty queue.
 
 2. `void enqueue(const T& value)`
    - Adds an element `value` to the queue.

 3. `T dequeue()`
    - Removes and returns the front element.
    - Throws a `runtime_error` if the queue is empty.

 4. `T front() const`
    - Returns the front element without removing it.
    - Throws a `runtime_error` if the queue is empty.

 5. `bool isEmpty() const`
    - Checks if the queue is empty.
    - Returns `true` if empty, otherwise `false`.

 6. `size_t size() const`
    - Returns the size of the queue.

 7. `void print() const`
    - Prints the contents of the queue.

 * MERGING QUEUES
 1. `void mergeInnerQueuesInQueue(Queue<Queue<T>>& outerQueue, size_t i, size_t j, size_t k)`
    - Merges two inner queues at indices `i` and `j` in the outer queue.
    - Deletes the original queues at indices `i` and `j`.
    - Inserts the merged queue at position `k`.
 **********************************************/

// Template class for Queue
template <typename T>
class Queue {
private:
    vector<T> data;    // Vector to store the queue elements
    size_t frontIdx;   // Index of the front element
    size_t sizeVal;    // Current size of the queue

public:
    // Constructor
    Queue() : frontIdx(0), sizeVal(0) {}

    // Add an element to the queue
    void enqueue(const T& value) {
        data.push_back(value);
        sizeVal++;
    }

    // Remove and return the front element
    T dequeue() {
        if (isEmpty())
            throw runtime_error("Queue underflow");
        T value = data[frontIdx++];
        sizeVal--;
        return value;
    }

    // Return the front element without removing it
    T front() const {
        if (isEmpty())
            throw runtime_error("Queue is empty");
        return data[frontIdx];
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return sizeVal == 0;
    }

    // Return the size of the queue
    size_t size() const {
        return sizeVal;
    }

    // Print the queue contents
    void print() const {
        for (size_t i = frontIdx; i < data.size(); i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // Access the underlying data
    vector<T>& getData() {
        return data;
    }
};

// Function to merge two inner queues in a queue and insert at position `k`
template <typename T>
void mergeInnerQueuesInQueue(Queue<Queue<T>>& outerQueue, size_t i, size_t j, size_t k) {
    if (i >= outerQueue.size() || j >= outerQueue.size() || k > outerQueue.size() || i == j) {
        throw runtime_error("Invalid indices for merging");
    }

    // Convert the queue to a vector for easier manipulation
    vector<Queue<T>> outerData = outerQueue.getData();

    // Create a new queue for the merged data
    Queue<T> mergedQueue;

    // Merge the i-th queue
    for (const auto& val : outerData[i].getData()) {
        mergedQueue.enqueue(val);
    }

    // Merge the j-th queue
    for (const auto& val : outerData[j].getData()) {
        mergedQueue.enqueue(val);
    }

    // Erase i-th and j-th queues
    if (i < j) {
        outerData.erase(outerData.begin() + j);
        outerData.erase(outerData.begin() + i);
    } else {
        outerData.erase(outerData.begin() + i);
        outerData.erase(outerData.begin() + j);
    }

    // Insert the merged queue at position `k`
    outerData.insert(outerData.begin() + k, mergedQueue);

    // Replace the outer queue with the updated vector
    Queue<Queue<T>> newOuterQueue;
    for (const auto& q : outerData) {
        newOuterQueue.enqueue(q);
    }
    outerQueue = newOuterQueue;
}

// Main function for testing
int main() {
    cout << "=== Testing Queue in Queue ===" << endl;

    // Create the outer queue
    Queue<Queue<int>> outerQueue;

    // Create and enqueue inner queues
    Queue<int> queue1;
    queue1.enqueue(1);
    queue1.enqueue(2);

    Queue<int> queue2;
    queue2.enqueue(3);
    queue2.enqueue(4);

    Queue<int> queue3;
    queue3.enqueue(5);
    queue3.enqueue(6);

    outerQueue.enqueue(queue1);
    outerQueue.enqueue(queue2);
    outerQueue.enqueue(queue3);

    // Print the outer queue before merging
    cout << "Outer queue before merging:" << endl;
    for (size_t i = 0; i < outerQueue.size(); i++) {
        outerQueue.getData()[i].print();
    }

    // Merge queue1 and queue2 and insert at position 1
    mergeInnerQueuesInQueue(outerQueue, 0, 1, 1);

    // Print the outer queue after merging
    cout << "Outer queue after merging:" << endl;
    for (size_t i = 0; i < outerQueue.size(); i++) {
        outerQueue.getData()[i].print();
    }

    return 0;
}