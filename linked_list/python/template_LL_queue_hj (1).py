from collections import deque

class Node:
    MAX_CAPACITY = 3

    def __init__(self):
        self.queue = deque()
        self.next = None

    def is_full(self):
        return len(self.queue) == self.MAX_CAPACITY

    def is_empty(self):
        return len(self.queue) == 0

    def enqueue(self, data):
        if not self.is_full():
            self.queue.append(data)
        else:
            raise Exception("Queue is full")

    def dequeue(self):
        if not self.is_empty():
            return self.queue.popleft()
        else:
            raise Exception("Queue is empty")


class LinkedListOfQueues:
    def __init__(self):
        self.head = Node()

    def get_last_node(self):
        current = self.head
        while current.next is not None:
            current = current.next
        return current

    def enqueue(self, data):
        last_node = self.get_last_node()
        if last_node.is_full():
            new_node = Node()
            new_node.enqueue(data)
            last_node.next = new_node
        else:
            last_node.enqueue(data)

    def dequeue(self):
        current = self.head
        prev = None

        if current.is_empty() and current.next is not None:
            self.head = current.next
            return self.head.dequeue()
        elif not current.is_empty():
            return current.dequeue()
        else:
            raise Exception("All queues are empty!")

    def print_queues(self):
        current = self.head
        index = 1
        while current:
            print(f"Queue {index}: {list(current.queue)}")
            current = current.next
            index += 1


# 사용 예시
queue_list = LinkedListOfQueues()

# Enqueue 예시
for i in range(1, 11):
    queue_list.enqueue(i)
queue_list.print_queues()

# Dequeue 예시
for _ in range(5):
    print(f"Dequeued: {queue_list.dequeue()}")
queue_list.print_queues()
