class Node:
    MAX_CAPACITY = 3

    def __init__(self):
        self.stack = []
        self.next = None

    def is_full(self):
        return len(self.stack) == self.MAX_CAPACITY

    def is_empty(self):
        return len(self.stack) == 0

    def push(self, data):
        if not self.is_full():
            self.stack.append(data)
        else:
            raise Exception("Stack is full")

    def pop(self):
        if not self.is_empty():
            return self.stack.pop()
        else:
            raise Exception("Stack is empty")


class LinkedListOfStacks:
    def __init__(self):
        self.head = Node()

    def get_last_node(self):
        current = self.head
        while current.next is not None:
            current = current.next
        return current

    def push(self, data):
        last_node = self.get_last_node()
        if last_node.is_full():
            new_node = Node()
            new_node.push(data)
            last_node.next = new_node
        else:
            last_node.push(data)

    def pop(self):
        current = self.head
        prev = None

        # 마지막 노드까지 이동
        while current.next is not None:
            prev = current
            current = current.next

        if current.is_empty() and prev is not None:
            prev.next = None
            return prev.pop()
        elif not current.is_empty():
            return current.pop()
        else:
            raise Exception("All stacks are empty!")

    def print_stacks(self):
        current = self.head
        index = 1
        while current:
            print(f"Stack {index}: {current.stack}")
            current = current.next
            index += 1


# 사용 예시
stack_list = LinkedListOfStacks()

# Push 예시
for i in range(1, 11):
    stack_list.push(i)
stack_list.print_stacks()

# Pop 예시
for _ in range(5):
    print(f"Popped: {stack_list.pop()}")
stack_list.print_stacks()
