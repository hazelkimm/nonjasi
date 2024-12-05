"""
1. Stack create() - 스택을 생성하고 초기화.
2. void make_empty(Stack s) - 스택을 비우고 모든 노드를 메모리에서 해제.
3. void destroy(Stack s) - 스택 전체를 삭제하고 모든 메모리를 해제.
4. boolean is_empty(Stack s) - 스택이 비었는지 확인.
5. void push(Stack *s, element i) - 스택에 요소를 추가하며 용량 초과 시 새 스택 생성.
6. element pop(Stack *s) - 스택에서 요소를 제거하고 반환하며, 비었으면 이전 스택으로 이동.
7. element peek(Stack s) - 스택의 최상위 요소를 반환 (제거하지 않음).
8. int total_size(Stack s) - 모든 연결된 스택의 요소 개수를 합산하여 반환.
9. void print_stack(Stack s) - 스택의 모든 요소를 출력.
10. element get_element_at(Stack s, int index) - 특정 인덱스의 요소를 반환.
11. Stack merge_stacks(Stack s1, Stack s2) - 두 스택을 하나로 병합하여 반환.
12. element sum_stack(Stack s) - 스택 내 모든 요소의 합계를 계산하여 반환.
13. element find_max(Stack s) - 스택 내 최댓값을 반환.
14. element find_min(Stack s) - 스택 내 최솟값을 반환.
15. int find_element(Stack s, element value) - 특정 값을 가진 요소의 인덱스를 반환.
16. void print_reverse(Stack s) - 스택의 모든 요소를 역순으로 출력.
17. int stack_depth(Stack s) - 연결된 스택의 총 스택 개수를 반환.
18. void delete_element(Stack *s, element value) - 특정 값을 가진 요소를 삭제.
19. Stack copy_stack(Stack s) - 기존 스택을 복사하여 동일한 구조의 새 스택 생성.
20. double calculate_average(Stack s) - 스택 내 모든 요소의 평균값을 계산하여 반환.
21. void remove_duplicates(Stack *s) - 스택에서 중복된 요소를 제거.
22. void delete_in_range(Stack *s, element min_value, element max_value) - 특정 값 범위의 요소를 삭제.
"""

class Node:
    def __init__(self, capacity):
        self.stack = []  # 스택 데이터를 저장하는 리스트
        self.capacity = capacity  # 스택의 최대 용량
        self.next = None  # 다음 노드 참조
        self.prev = None  # 이전 노드 참조


class LinkedListStack:
    def __init__(self, capacity):
        """스택을 초기화합니다."""
        self.head = Node(capacity)  # 첫 노드
        self.tail = self.head  # 마지막 노드
        self.capacity = capacity  # 각 노드의 최대 용량

    def is_empty(self):
        """스택이 비었는지 확인합니다."""
        return self.head == self.tail and len(self.tail.stack) == 0

    def make_empty(self):
        """스택을 초기화하여 모든 노드를 비웁니다."""
        current = self.head.next
        while current:
            temp = current
            current = current.next
            del temp
        self.head.stack = []
        self.head.next = None
        self.tail = self.head

    def destroy(self):
        """스택을 완전히 삭제하고 메모리를 해제합니다."""
        self.make_empty()
        del self.head
        self.head = None
        self.tail = None


    def push(self, value):
        """스택에 요소를 추가합니다. 용량을 초과하면 새 노드를 생성합니다."""
        if len(self.tail.stack) < self.tail.capacity:
            self.tail.stack.append(value)
        else:
            new_node = Node(self.capacity)
            self.tail.next = new_node
            new_node.prev = self.tail
            self.tail = new_node
            self.tail.stack.append(value)

    def pop(self):
        """스택에서 요소를 제거하고 반환합니다."""
        if not self.tail.stack:
            if self.tail.prev:
                self.tail = self.tail.prev
                self.tail.next = None
                return self.pop()
            else:
                raise IndexError("스택이 비어 있습니다.")
        return self.tail.stack.pop()

    def peek(self):
        """스택의 최상위 요소를 반환합니다. (제거하지 않음)"""
        if not self.tail.stack:
            if self.tail.prev:
                self.tail = self.tail.prev
                self.tail.next = None
                return self.peek()
            else:
                raise IndexError("스택이 비어 있습니다.")
        return self.tail.stack[-1]

    def total_size(self):
        """스택 전체의 요소 개수를 반환합니다."""
        size = 0
        current = self.head
        while current:
            size += len(current.stack)
            current = current.next
        return size

    def print_stack(self):
        """스택의 모든 요소를 출력합니다."""
        current = self.head
        while current:
            print(current.stack, end=" -> ")
            current = current.next
        print("None")

    def get_element_at(self, index):
        """특정 인덱스에 위치한 요소를 반환합니다."""
        current = self.head
        while current:
            if index < len(current.stack):
                return current.stack[index]
            index -= len(current.stack)
            current = current.next
        raise IndexError("인덱스가 범위를 초과했습니다.")

    def merge_stacks(self, stack):
        """다른 스택과 병합합니다."""
        current = stack.head
        while current:
            for value in current.stack:
                self.push(value)
            current = current.next

    def sum_stack(self):
        """스택 내 모든 요소의 합을 반환합니다."""
        total = 0
        current = self.head
        while current:
            total += sum(current.stack)
            current = current.next
        return total

    def find_max(self):
        """스택 내 최댓값을 반환합니다."""
        max_value = float('-inf')
        current = self.head
        while current:
            if current.stack:
                max_value = max(max_value, max(current.stack))
            current = current.next
        if max_value == float('-inf'):
            raise ValueError("스택이 비어 있습니다.")
        return max_value

    def find_min(self):
        """스택 내 최솟값을 반환합니다."""
        min_value = float('inf')
        current = self.head
        while current:
            if current.stack:
                min_value = min(min_value, min(current.stack))
            current = current.next
        if min_value == float('inf'):
            raise ValueError("스택이 비어 있습니다.")
        return min_value

    def find_element(self, value):
        """특정 값을 가진 요소의 인덱스를 반환합니다."""
        index = 0
        current = self.head
        while current:
            if value in current.stack:
                return index + current.stack.index(value)
            index += len(current.stack)
            current = current.next
        return -1

    def print_reverse(self):
        """스택의 모든 요소를 역순으로 출력합니다."""
        current = self.tail
        while current:
            print(current.stack[::-1], end=" <- ")
            current = current.prev
        print("None")

    def depth(self):
        """연결된 스택의 총 개수를 반환합니다."""
        depth = 0
        current = self.head
        while current:
            depth += 1
            current = current.next
        return depth

    def delete_element(self, value):
        """스택에서 특정 값을 삭제합니다."""
        current = self.head
        while current:
            if value in current.stack:
                current.stack.remove(value)
            current = current.next

    def calculate_average(self):
        """스택 내 모든 요소의 평균값을 반환합니다."""
        total_sum = self.sum_stack()
        total_elements = self.total_size()
        if total_elements == 0:
            raise ValueError("스택이 비어 있습니다.")
        return total_sum / total_elements

    def remove_duplicates(self):
        """스택에서 중복된 요소를 제거합니다."""
        seen = set()
        current = self.head
        while current:
            new_stack = []
            for value in current.stack:
                if value not in seen:
                    new_stack.append(value)
                    seen.add(value)
            current.stack = new_stack
            current = current.next

    def delete_in_range(self, min_value, max_value):
        """특정 값 범위의 요소를 삭제합니다."""
        current = self.head
        while current:
            current.stack = [value for value in current.stack if value < min_value or value > max_value]
            current = current.next


# 메인 함수
def main():
    stack = LinkedListStack(3)

    # 각 기능 테스트
    print("1. Push Test")
    for i in range(1, 11):
        stack.push(i)
    stack.print_stack()

    print("\n2. Pop Test")
    print("Popped value:", stack.pop())
    stack.print_stack()

    print("\n3. Peek Test")
    print("Top value:", stack.peek())

    print("\n4. Total Size Test")
    print("Total size:", stack.total_size())

    print("\n5. Get Element At Test")
    print("Element at index 4:", stack.get_element_at(4))

    print("\n6. Sum Stack Test")
    print("Sum of stack:", stack.sum_stack())

    print("\n7. Find Max Test")
    print("Max value:", stack.find_max())

    print("\n8. Find Min Test")
    print("Min value:", stack.find_min())

    print("\n9. Find Element Test")
    print("Index of element 5:", stack.find_element(5))

    print("\n10. Print Reverse Test")
    stack.print_reverse()

    print("\n11. Depth Test")
    print("Depth:", stack.depth())

    print("\n12. Delete Element Test")
    stack.delete_element(4)
    stack.print_stack()

    print("\n13. Calculate Average Test")
    print("Average:", stack.calculate_average())

    print("\n14. Remove Duplicates Test")
    stack.push(5)
    stack.push(6)
    stack.push(6)
    stack.remove_duplicates()
    stack.print_stack()

    print("\n15. Delete in Range Test")
    stack.delete_in_range(2, 6)
    stack.print_stack()

    print("\n16. Merge Stacks Test")
    stack2 = LinkedListStack(3)
    for i in range(20, 23):
        stack2.push(i)
    stack.merge_stacks(stack2)
    stack.print_stack()


# 실행
if __name__ == "__main__":
    main()
