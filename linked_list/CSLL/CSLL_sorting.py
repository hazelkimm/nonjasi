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

6. merge_sort*
7. quick_sort*
'''

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class CircularSinglyLinkedList:
    def __init__(self):
        self.head = None


    ####################################################################################################################
    def append(self, data):
        # 새 노드를 리스트에 추가
        new_node = Node(data)
        if not self.head:
            # 리스트가 비어있으면 head를 새 노드로 설정하고,
            # 다음 노드가 자기 자신을 가리키도록 설정
            self.head = new_node
            self.head.next = self.head
        else:
            # 리스트의 끝까지 이동한 후 새 노드를 연결
            temp = self.head
            while temp.next != self.head:
                temp = temp.next
            temp.next = new_node
            new_node.next = self.head


    ####################################################################################################################
    def display(self):
        # 리스트의 모든 노드를 출력
        if not self.head:
            print("List is empty")
            return
        temp = self.head
        while True:
            print(temp.data, end=" -> ")
            temp = temp.next
            if temp == self.head:  # 다시 head로 돌아오면 종료
                break
        print("(back to head)")


    ####################################################################################################################
    def bubble_sort(self):
        # 버블 정렬 함수
        if not self.head or self.head.next == self.head:
            # 리스트가 비어있거나 노드가 하나만 있는 경우 정렬 불필요
            return

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
    def selection_sort(self):
        if not self.head or self.head.next == self.head:
            # 리스트가 비어있거나 노드가 하나뿐이면 정렬 필요 없음
            return

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
    def insertion_sort(self):
        if not self.head or self.head.next == self.head:
            return  # 리스트가 비어있거나 원소가 하나뿐이면 정렬할 필요 없음

        sorted_tail = self.head
        current = self.head.next

        while current != self.head:
            next_node = current.next

            if current.data < self.head.data:
                # 정렬된 리스트의 시작 부분에 삽입
                sorted_tail.next = next_node  # 현재 노드를 정렬된 리스트에서 제거
                current.next = self.head  # 현재 노드를 새로운 head 앞에 삽입
                temp = self.head
                while temp.next != self.head:  # 마지막 노드 탐색
                    temp = temp.next
                temp.next = current  # 마지막 노드가 새로운 head를 가리키도록 설정
                self.head = current  # 새로운 head 설정
            else:
                # 정렬된 리스트 내 적절한 위치를 찾음
                search = self.head
                while search.next != self.head and search.next.data < current.data:
                    search = search.next

                # 노드를 삽입
                sorted_tail.next = next_node  # 현재 노드를 정렬되지 않은 리스트에서 제거
                current.next = search.next
                search.next = current

            # sorted_tail을 갱신
            if sorted_tail.next == self.head:
                break
            current = next_node



############################################################
# # 원형 단일 연결 리스트 생성
# cll = CircularSinglyLinkedList()
# cll.append(4)
# cll.append(2)
# cll.append(7)
# cll.append(1)
# cll.append(5)

# print("Before sorting:")
# cll.display()

# # 삽입 정렬 실행
# cll.insertion_sort()

# print("After sorting:")
# cll.display()
