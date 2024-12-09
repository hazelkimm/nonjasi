'''
1. append 메서드: 원형 연결 리스트에 데이터를 추가하는 함수. 리스트가 비어있는 경우와 아닌 경우를 나누어 처리.
2. display 메서드: 원형 연결 리스트의 모든 요소를 순서대로 출력하며, 마지막에 (back to head)를 출력.

3. bubble_sort
    -버블 정렬 알고리즘을 사용하여 데이터를 정렬.
    -리스트가 비어있거나 노드가 하나뿐인 경우에는 아무 작업도 하지 않음.
    -노드 간 데이터를 교환하여 정렬하며, 더 이상 교환이 필요 없을 때까지 반복.

4. selection_sort
    -현재 노드에서 시작하여 나머지 노드들 중 가장 작은 값을 가진 노드를 찾음.
    -데이터를 교환하여 현재 위치를 정렬.
    -한 바퀴 순회 후 head로 돌아오면 정렬 종료.

5. insertion_sort
    -현재 노드가 정렬된 리스트의 시작보다 작으면 새로운 정렬된 리스트의 시작 부분으로 삽입.
    -그렇지 않으면 정렬된 리스트 내에서 적절한 위치를 찾아 현재 노드를 삽입.
    -정렬된 리스트의 끝과 정렬되지 않은 리스트의 시작을 유지.
    '''

class Node:
    # 노드 초기화: 노드는 데이터와 다음(next), 이전(prev) 노드를 가리키는 포인터를 가짐
    def __init__(self, data) -> None:
        self.data = data   # 노드가 저장할 데이터
        self.next = None   # 다음 노드를 가리킬 포인터
        self.prev = None   # 이전 노드를 가리킬 포인터
    
class CircularDoublyLinkedList:
    # 원형 이중 연결 리스트 초기화
    def __init__(self) -> None:
        self.head = None   # 리스트의 첫 번째 노드를 가리킴 (head)
        self.tail = None   # 리스트의 마지막 노드를 가리킴 (tail)
    

    ####################################################################################################################
    # 원형 이중 연결 리스트에 새 노드를 추가
    def append(self, data):
        new_node = Node(data)
        if not self.head:
            # 리스트가 비어있으면 head와 tail 모두 새 노드를 가리킴
            self.head = new_node
            self.tail = new_node
            self.head.next = self.head  # 자기 자신을 가리키는 순환
            self.head.prev = self.head  # 자기 자신을 가리키는 순환
        else:
            # 기존의 tail 뒤에 새 노드를 추가
            new_node.prev = self.tail
            new_node.next = self.head
            self.tail.next = new_node
            self.head.prev = new_node
            self.tail = new_node  # 새 노드가 tail이 됨


    ####################################################################################################################
    # 리스트의 모든 노드를 출력
    def display(self):
        if not self.head:
            print("List is empty")
            return
        temp = self.head
        while True:
            print(temp.data, end=" <-> ")
            temp = temp.next
            if temp == self.head:
                break
        print("(back to head)")


    ####################################################################################################################
    # 버블 정렬 함수
    def bubble_sort(self):
        if not self.head or self.head.next == self.head:
            return  # 리스트가 비어있거나 노드가 하나만 있는 경우 정렬 불필요

        swapped = True
        while swapped:
            swapped = False
            current = self.head
            while current.next != self.head:  # 마지막 노드(head 이전)까지 순회
                next_node = current.next
                if current.data > next_node.data:
                    # 데이터 교환
                    current.data, next_node.data = next_node.data, current.data
                    swapped = True
                current = current.next


    ####################################################################################################################
    # 선택 정렬 함수
    def selection_sort(self):
        if not self.head or self.head.next == self.head:
            return  # 리스트가 비어있거나 노드가 하나만 있는 경우 정렬 불필요

        current = self.head
        while True:
            # 현재 노드에서 시작하여 가장 작은 노드를 찾음
            smallest = current
            checker = current.next
            while checker != self.head:  # 원형 구조를 유지하며 탐색
                if checker.data < smallest.data:
                    smallest = checker
                checker = checker.next

            # 가장 작은 노드와 현재 노드의 데이터 교환
            if smallest != current:
                current.data, smallest.data = smallest.data, current.data

            # 다음 노드로 이동
            current = current.next

            # 다시 head로 돌아오면 정렬 종료
            if current == self.head:
                break


    ####################################################################################################################
    # 삽입 정렬 함수
    def insertion_sort(self):
        if not self.head or self.head.next == self.head:
            return  # 리스트가 비어있거나 원소가 하나뿐이면 정렬할 필요 없음

        current = self.head.next
        while current != self.head:
            next_node = current.next
            if current.data < self.head.data:
                # 정렬된 리스트의 시작 부분에 삽입
                current.prev.next = next_node  # 현재 노드를 정렬된 리스트에서 제거
                next_node.prev = current.prev
                current.next = self.head
                self.head.prev = current
                current.prev = self.tail
                self.tail.next = current
                self.head = current  # 새로운 head 설정
            else:
                # 정렬된 리스트 내 적절한 위치를 찾음
                search = self.head
                while search.next != self.head and search.next.data < current.data:
                    search = search.next

                # 노드를 삽입
                current.prev.next = next_node  # 현재 노드를 정렬되지 않은 리스트에서 제거
                if next_node:
                    next_node.prev = current.prev
                current.next = search.next
                search.next.prev = current
                search.next = current

            # current를 갱신
            current = next_node



# 원형 이중 연결 리스트 생성
cdll = CircularDoublyLinkedList()
cdll.append(4)
cdll.append(2)
cdll.append(7)
cdll.append(1)
cdll.append(5)

print("Before sorting:")
cdll.display()

# 정렬
cdll.bubble_sort()
# cdll.selection_sort()
# cdll.insertion_sort()

print("After sorting:")
cdll.display()
