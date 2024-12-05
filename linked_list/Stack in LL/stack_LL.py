"""
1. Stack create() - 스택을 생성하고 초기화.
2. void push(value) - 스택에 요소를 추가하며 용량 초과 시 새 스택 생성.
3. int pop() - 스택에서 요소를 제거하고 반환.
4. int peek() - 스택의 최상위 요소를 반환 (제거하지 않음).
5. int total_size() - 모든 연결된 스택의 요소 개수를 합산하여 반환.
6. void print_stack() - 스택의 모든 요소를 출력.
7. int get_element_at(index) - 특정 인덱스의 요소를 반환.
8. void merge_stacks(stack) - 두 스택을 병합.
9. int sum_stack() - 스택 내 모든 요소의 합계를 반환.
10. int find_max() - 스택 내 최댓값을 반환.
11. int find_min() - 스택 내 최솟값을 반환.
12. int find_element(value) - 특정 값을 가진 요소의 인덱스를 반환.
13. void print_reverse() - 스택의 모든 요소를 역순으로 출력.
14. int depth() - 연결된 스택의 총 스택 개수를 반환.
15. void delete_element(value) - 스택에서 특정 값을 삭제.
16. double calculate_average() - 스택 내 모든 요소의 평균값을 반환.
17. void remove_duplicates() - 스택에서 중복된 요소를 제거.
18. void delete_in_range(min_value, max_value) - 특정 값 범위의 요소를 삭제.
"""


class Node:
    """스택의 노드를 나타내는 클래스"""
    def __init__(self, data):
        self.data = data  # 노드의 데이터
        self.next = None  # 다음 노드를 가리키는 포인터


class Stack:
    """싱글 링크드 리스트 기반 스택 클래스"""
    STACK_CAPACITY = 3  # 각 스택의 최대 용량

    def __init__(self):
        self.top = None  # 스택의 최상위 노드
        self.size = 0    # 현재 스택의 크기
        self.next_stack = None  # 다음 연결된 스택

    def is_empty(self):
        """스택이 비었는지 확인"""
        return self.top is None

    def push(self, value):
        """스택에 요소를 추가하며, 용량 초과 시 새 스택 생성"""
        if self.size >= self.STACK_CAPACITY:
            if not self.next_stack:
                self.next_stack = Stack()  # 새 스택 생성
            self.next_stack.push(value)
            return

        new_node = Node(value)  # 새로운 노드 생성
        new_node.next = self.top  # 새 노드를 기존 top 위에 놓음
        self.top = new_node
        self.size += 1

    def pop(self):
        """스택에서 요소를 제거하고 반환"""
        if self.is_empty():
            if self.next_stack:
                # 다음 연결된 스택에서 요소를 가져옴
                self.__replace_with_next_stack()
                return self.pop()
            raise IndexError("Stack is empty")

        value = self.top.data  # 최상위 데이터 저장
        self.top = self.top.next  # 최상위 노드를 제거
        self.size -= 1
        return value

    def peek(self):
        """스택의 최상위 요소를 반환 (제거하지 않음)"""
        if self.is_empty():
            raise IndexError("Stack is empty")
        return self.top.data

    def total_size(self):
        """모든 연결된 스택의 요소 개수를 합산하여 반환"""
        size = self.size
        if self.next_stack:
            size += self.next_stack.total_size()
        return size

    def print_stack(self):
        """스택의 모든 요소를 출력"""
        stack_num = 1
        current_stack = self
        while current_stack:
            print(f"Stack {stack_num}: ", end="")
            current_node = current_stack.top
            while current_node:
                print(current_node.data, end=" ")
                current_node = current_node.next
            print()
            current_stack = current_stack.next_stack
            stack_num += 1

    def get_element_at(self, index):
        """특정 인덱스의 요소를 반환"""
        if index < self.size:
            current = self.top
            for _ in range(index):
                current = current.next
            return current.data
        elif self.next_stack:
            return self.next_stack.get_element_at(index - self.size)
        raise IndexError("Index out of bounds")

    def merge_stacks(self, other):
        """두 스택을 병합하여 반환"""
        if not self.next_stack:
            self.next_stack = other
        else:
            self.next_stack.merge_stacks(other)

    def sum_stack(self):
        """스택 내 모든 요소의 합계를 반환"""
        total = 0
        current_stack = self
        while current_stack:
            current_node = current_stack.top
            while current_node:
                total += current_node.data
                current_node = current_node.next
            current_stack = current_stack.next_stack
        return total

    def find_max(self):
        """스택 내 최댓값을 반환"""
        if self.is_empty():
            raise IndexError("Stack is empty")
        max_value = self.top.data
        current_stack = self
        while current_stack:
            current_node = current_stack.top
            while current_node:
                if current_node.data > max_value:
                    max_value = current_node.data
                current_node = current_node.next
            current_stack = current_stack.next_stack
        return max_value

    def find_min(self):
        """스택 내 최솟값을 반환"""
        if self.is_empty():
            raise IndexError("Stack is empty")
        min_value = self.top.data
        current_stack = self
        while current_stack:
            current_node = current_stack.top
            while current_node:
                if current_node.data < min_value:
                    min_value = current_node.data
                current_node = current_node.next
            current_stack = current_stack.next_stack
        return min_value

    def find_element(self, value):
        """특정 값을 가진 요소의 인덱스를 반환"""
        index = 0
        current_stack = self
        while current_stack:
            current_node = current_stack.top
            while current_node:
                if current_node.data == value:
                    return index
                current_node = current_node.next
                index += 1
            current_stack = current_stack.next_stack
        return -1

    def print_reverse(self):
        """스택의 모든 요소를 역순으로 출력"""
        if self.next_stack:
            self.next_stack.print_reverse()
        current_node = self.top
        while current_node:
            print(current_node.data, end=" ")
            current_node = current_node.next

    def depth(self):
        """연결된 스택의 총 개수를 반환"""
        if self.next_stack:
            return 1 + self.next_stack.depth()
        return 1

    def delete_element(self, value):
        """스택에서 특정 값을 가진 요소를 삭제"""
        prev = None
        current = self.top
        while current:
            if current.data == value:
                if prev:
                    prev.next = current.next
                else:
                    self.top = current.next
                self.size -= 1
                return
            prev = current
            current = current.next
        if self.next_stack:
            self.next_stack.delete_element(value)

    def calculate_average(self):
        """스택 내 모든 요소의 평균값을 반환"""
        total = self.sum_stack()
        count = self.total_size()
        if count == 0:
            raise IndexError("Stack is empty")
        return total / count

    def remove_duplicates(self):
        """스택에서 중복된 요소를 제거"""
        values = set()
        prev = None
        current = self.top
        while current:
            if current.data in values:
                prev.next = current.next
                self.size -= 1
            else:
                values.add(current.data)
                prev = current
            current = current.next
        if self.next_stack:
            self.next_stack.remove_duplicates()

    def delete_in_range(self, min_value, max_value):
        """스택에서 특정 값 범위의 요소를 삭제"""
        prev = None
        current = self.top
        while current:
            if min_value <= current.data <= max_value:
                if prev:
                    prev.next = current.next
                else:
                    self.top = current.next
                self.size -= 1
            else:
                prev = current
            current = current.next
        if self.next_stack:
            self.next_stack.delete_in_range(min_value, max_value)

    def __replace_with_next_stack(self):
        """현재 스택을 다음 스택으로 교체"""
        if not self.next_stack:
            raise IndexError("No next stack to replace")
        self.top = self.next_stack.top
        self.size = self.next_stack.size
        self.next_stack = self.next_stack.next_stack


# 테스트 코드
if __name__ == "__main__":
    # 스택 생성
    s1 = Stack()
    s2 = Stack()

    # 스택에 데이터 추가
    print("Pushing elements to Stack 1:")
    s1.push(10)
    s1.push(20)
    s1.push(30)
    s1.push(40)
    s1.push(50)
    print("Stack 1 after pushing:")
    s1.print_stack()

    # 스택 깊이와 총 크기 확인
    print(f"Depth of Stack 1: {s1.depth()}")
    print(f"Total size of Stack 1: {s1.total_size()}")

    # 최댓값과 최솟값 확인
    print(f"Maximum value in Stack 1: {s1.find_max()}")
    print(f"Minimum value in Stack 1: {s1.find_min()}")

    # 특정 값 삭제
    print("Deleting value 30 from Stack 1.")
    s1.delete_element(30)
    print("Stack 1 after deleting value 30:")
    s1.print_stack()

    # 평균 계산
    print(f"Average of Stack 1: {s1.calculate_average()}")

    # 스택 병합
    print("Pushing elements to Stack 2:")
    s2.push(60)
    s2.push(70)
    s2.push(80)
    print("Stack 2:")
    s2.print_stack()

    print("Merging Stack 1 and Stack 2.")
    s1.merge_stacks(s2)
    print("Merged Stack:")
    s1.print_stack()

    # 역순 출력
    print("Stack 1 in reverse order:")
    s1.print_reverse()
    print()

    # 스택 복사
    print("Copying Stack 1 to Stack 3.")
    s3 = Stack()
    s3 = s1
    print("Stack 3 (copy of Stack 1):")
    s3.print_stack()

    # 중복 제거
    print("Removing duplicates in Stack 1.")
    s1.remove_duplicates()
    print("Stack 1 after removing duplicates:")
    s1.print_stack()

    # 범위 삭제
    print("Deleting elements in range [10, 50] from Stack 1.")
    s1.delete_in_range(10, 50)
    print("Stack 1 after deleting in range:")
    s1.print_stack()

    # 스택 내 요소 합계
    print(f"Sum of elements in Stack 1: {s1.sum_stack()}")

    # 모든 요소 제거 및 확인
    print("Popping all elements from Stack 1:")
    while not s1.is_empty():
        print(f"Popped: {s1.pop()}")
    print("Stack 1 is now empty.")
