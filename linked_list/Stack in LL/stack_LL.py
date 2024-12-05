class Node:
    """스택의 각 노드를 나타내는 클래스"""
    def __init__(self, data):
        self.data = data  # 노드의 데이터
        self.next = None  # 다음 노드를 가리키는 포인터


class Stack:
    """용량 제한이 있는 스택 클래스"""
    STACK_CAPACITY = 3  # 각 스택의 최대 용량

    def __init__(self):
        self.top = None  # 스택의 최상위 노드
        self.size = 0    # 현재 스택의 크기
        self.next_stack = None  # 다음 연결된 스택

    def is_empty(self):
        """스택이 비었는지 확인"""
        return self.top is None

    def push(self, value):
        if self.size >= self.STACK_CAPACITY:
            if not self.next_stack:
                print(f"Creating new stack for value {value}.")
                self.next_stack = Stack()
            self.next_stack.push(value)
            return

        # 현재 스택에 값 추가
        new_node = Node(value)
        new_node.next = self.top
        self.top = new_node
        self.size += 1
        print(f"Pushed value {value} to current stack. Size is now {self.size}.")

    def pop(self):
        """스택의 최상위 값을 제거하고 반환"""
        if self.is_empty():
            if self.next_stack:
                # 현재 스택이 비었으면 다음 스택으로 이동
                self.__replace_with_next_stack()
                return self.pop()
            else:
                raise IndexError("Stack is empty")

        # 최상위 값을 제거
        value = self.top.data
        self.top = self.top.next
        self.size -= 1
        return value

    def peek(self):
        """스택의 최상위 값을 반환 (제거하지 않음)"""
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
        current_stack = self
        stack_num = 1
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
            current_node = self.top
            for _ in range(index):
                current_node = current_node.next
            return current_node.data
        elif self.next_stack:
            return self.next_stack.get_element_at(index - self.size)
        else:
            raise IndexError("Index out of bounds")

    def depth(self):
        """연결된 스택의 총 개수를 반환"""
        if self.next_stack:
            return 1 + self.next_stack.depth()
        return 1

    def remove_value(self, value):
        """특정 값을 스택에서 제거"""
        prev = None
        current = self.top

        # 현재 스택에서 값 찾기
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

        # 다음 스택에서 값 제거
        if self.next_stack:
            self.next_stack.remove_value(value)

    def remove_in_range(self, min_value, max_value):
        """특정 범위의 값 삭제"""
        temp_stack = Stack()

        # 범위에 포함되지 않는 값을 임시 스택으로 이동
        while not self.is_empty():
            value = self.pop()
            if value < min_value or value > max_value:
                temp_stack.push(value)

        # 임시 스택의 값을 다시 현재 스택으로 복사
        while not temp_stack.is_empty():
            self.push(temp_stack.pop())

        # 다음 스택에서도 범위 내 값 삭제
        if self.next_stack:
            self.next_stack.remove_in_range(min_value, max_value)

    def __replace_with_next_stack(self):
        """현재 스택을 다음 스택으로 교체"""
        if not self.next_stack:
            raise IndexError("No next stack to replace")
        self.top = self.next_stack.top
        self.size = self.next_stack.size
        self.next_stack = self.next_stack.next_stack


# 테스트 코드
if __name__ == "__main__":
    s1 = Stack()

    # 요소 추가
    print("Pushing elements to s1...")
    s1.push(10)
    s1.push(20)
    s1.push(30)  # 첫 번째 스택이 가득 참
    s1.push(40)  # 두 번째 스택 생성
    s1.push(50)

    # 스택 출력
    print("Initial stack (s1):")
    s1.print_stack()

    # 총 크기 확인
    print("Total size of stack s1:", s1.total_size())

    # 스택 깊이 확인
    print("Depth of stack s1:", s1.depth())

    # 특정 인덱스의 요소 조회
    search_index = 4
    print(f"Element at index {search_index}:", s1.get_element_at(search_index))

    # 최상단 값 확인 및 삭제
    print("Peeking top element:", s1.peek())
    print("Popping top element:", s1.pop())

    # 특정 값 삭제
    delete_value = 30
    print(f"Removing value {delete_value} from stack.")
    s1.remove_value(delete_value)
    s1.print_stack()

    # 특정 범위의 요소 삭제
    print("Removing values in range 10 to 30 from stack.")
    s1.remove_in_range(10, 30)
    s1.print_stack()
