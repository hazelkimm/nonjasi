#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept> // For exceptions

/**********************************************
 * CATALOG OF QUEUE FUNCTIONS
 **********************************************
 * 
 * 1. `Queue()`:
 *    Initializes an empty queue.
 * 
 * 2. `bool isEmpty() const`:
 *    Checks if the queue is empty. Returns true or false.
 * 
 * 3. `int size() const`:
 *    Returns the number of elements in the queue.
 * 
 * 4. `void enqueue(int value)`:
 *    Adds an element to the rear of the queue.
 * 
 * 5. `int dequeue()`:
 *    Removes and returns the front element of the queue.
 *    Throws an error if the queue is empty.
 * 
 * 6. `int peek() const`:
 *    Returns the front element without removing it.
 *    Throws an error if the queue is empty.
 * 
 * 7. `Queue merge(const Queue& other) const`:
 *    Merges two queues into a new queue.
 * 
 * 8. `void reverse()`:
 *    Reverses the elements of the queue in place.
 * 
 * 9. `Queue copy() const`:
 *    Creates and returns a copy of the queue.
 * 
 * 10. `void sort()`:
 *     Sorts the elements of the queue in ascending order.
 * 
 * 11. `Queue slice(int start, int end) const`:
 *     Creates and returns a new queue containing elements
 *     from index `start` to `end - 1`.
 **********************************************/

class Queue {
private:
    std::vector<int> data; // Vector for dynamic storage
    int frontIdx;          // Index of the front element
    int size;              // Current number of elements

public:
    // Constructor
    Queue() : frontIdx(0), size(0) {}

    // Check if the queue is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Get the size of the queue
    int getSize() const {
        return size;
    }

    // Add an element to the rear of the queue
    void enqueue(int value) {
        if (frontIdx + size >= (int)data.size()) {
            data.push_back(value);
        } else {
            data[frontIdx + size] = value;
        }
        size++;
    }

    // Remove and return the front element of the queue
    int dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue underflow error!");
        }
        int value = data[frontIdx];
        frontIdx++;
        size--;
        if (size == 0) {
            frontIdx = 0; // Reset indices for empty queue
        }
        return value;
    }

    // Get the front element without removing it
    int peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty!");
        }
        return data[frontIdx];
    }

    // Merge with another queue
    Queue merge(const Queue& other) const {
        Queue mergedQueue;
        for (int i = 0; i < size; i++) {
            mergedQueue.enqueue(data[frontIdx + i]);
        }
        for (int i = 0; i < other.size; i++) {
            mergedQueue.enqueue(other.data[other.frontIdx + i]);
        }
        return mergedQueue;
    }

    // Reverse the queue
    void reverse() {
        std::reverse(data.begin() + frontIdx, data.begin() + frontIdx + size);
    }

    // Copy the queue
    Queue copy() const {
        Queue copiedQueue;
        for (int i = 0; i < size; i++) {
            copiedQueue.enqueue(data[frontIdx + i]);
        }
        return copiedQueue;
    }

    // Sort the queue
    void sort() {
        std::sort(data.begin() + frontIdx, data.begin() + frontIdx + size);
    }

    // Slice the queue
    Queue slice(int start, int end) const {
        if (start < 0 || end > size || start >= end) {
            throw std::runtime_error("Invalid slice indices!");
        }
        Queue slicedQueue;
        for (int i = start; i < end; i++) {
            slicedQueue.enqueue(data[frontIdx + i]);
        }
        return slicedQueue;
    }

    // Display the elements of the queue (for testing)
    void display() const {
        for (int i = 0; i < size; i++) {
            std::cout << data[frontIdx + i] << " ";
        }
        std::cout << std::endl;
    }
};

// Main function for testing
int main() {
    Queue q1, q2;

    // Enqueue elements into q1
    q1.enqueue(10);
    q1.enqueue(20);
    q1.enqueue(30);

    // Enqueue elements into q2
    q2.enqueue(40);
    q2.enqueue(50);
    q2.enqueue(60);

    // Merge queues
    Queue mergedQueue = q1.merge(q2);
    std::cout << "Merged queue: ";
    mergedQueue.display();

    // Reverse q1
    q1.reverse();
    std::cout << "Reversed q1: ";
    q1.display();

    // Copy q2
    Queue copiedQueue = q2.copy();
    std::cout << "Copied q2: ";
    copiedQueue.display();

    // Sort q2
    q2.enqueue(25);
    q2.sort();
    std::cout << "Sorted q2: ";
    q2.display();

    // Slice q2
    Queue slicedQueue = q2.slice(1, 4);
    std::cout << "Sliced q2 (1 to 4): ";
    slicedQueue.display();

    return 0;
}