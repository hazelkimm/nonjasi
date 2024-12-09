'''
add_node(data): 새로운 노드를 추가하는 함수 (리스트의 끝에 추가)
display_list(): 리스트의 모든 노드를 출력하는 함수 (순환하는 특성을 반영).
find_node(data): 특정 값을 가진 노드를 찾는 함수.
get_length(): 리스트의 길이를 반환하는 함수.
delete_node(data): 특정 값을 가진 노드를 삭제하는 함수.
is_circular(): 리스트가 순환 구조인지 확인하는 함수.
traverse_list(): 리스트를 한 번 순회하며 노드를 방문하는 함수.
find_middle_node(): 순환 리스트에서 중간 노드를 찾는 함수.
insert_at_position(data, position): 주어진 위치에 노드를 삽입하는 함수.
remove_at_position(position): 주어진 위치의 노드를 삭제하는 함수.
reverse_list(): 리스트의 순서를 뒤집는 함수.
detect_cycle(): 리스트에 순환이 있는지 탐지하는 함수 (예: Floyd’s Cycle Detection Algorithm).
split_list(): 순환 리스트를 두 개의 리스트로 분할하는 함수.
merge_list(other_list): 두 개의 순환 리스트를 병합하는 함수.
copy_list(): 현재 리스트의 복사본을 생성하는 함수.
get_node_at_position(position): 특정 위치에 있는 노드를 반환하는 함수.
get_last_node(): 리스트의 마지막 노드를 반환하는 함수.
rotate_list(steps): 리스트를 주어진 단계만큼 회전시키는 함수.  (steps, 양수는 오른쪽 회전, 음수는 왼쪽 회전).
clear_list(): 리스트의 모든 노드를 제거하는 함수.
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
    # add_node(data): 리스트 끝에 새로운 노드를 추가하는 함수
    def add_node(self, data):
        new_node = Node(data)  # 새 노드를 생성

        if not self.head:  # 리스트가 비어 있는 경우
            self.head = new_node
            self.head.next = self.head  # 스스로를 가리켜 순환 연결을 만듦
            self.head.prev = self.head  # 스스로를 가리켜 순환 연결을 만듦
            self.tail = new_node  # 새 노드가 head이자 tail이 됨
        else:
            # 리스트의 끝에 노드를 추가
            self.tail.next = new_node  # 현재 tail의 다음은 새 노드
            new_node.prev = self.tail  # 새 노드의 이전은 현재 tail
            new_node.next = self.head  # 새 노드의 다음은 head를 가리킴
            self.head.prev = new_node  # head의 이전은 새 노드를 가리킴
            self.tail = new_node  # tail을 새 노드로 업데이트


    ####################################################################################################################
    # display_list(): 리스트의 모든 노드를 출력하는 함수
    def display_list(self):
        if not self.head:  # 리스트가 비어 있는 경우
            print("The list is empty.")
            return

        current = self.head
        while True:
            print(current.data, end=" <-> ")
            current = current.next
            if current == self.head:  # head로 돌아오면 종료
                break
        print("(head)")


    ####################################################################################################################
    # find_node(data): 특정 값을 가진 노드를 찾는 함수
    def find_node(self, data):
        if not self.head:  # 리스트가 비어 있는 경우
            return None

        current = self.head
        while True:
            if current.data == data:
                return current  # 데이터를 가진 노드를 반환
            current = current.next
            if current == self.head:  # head로 돌아오면 종료
                break
        return None  # 해당 데이터를 가진 노드가 없으면 None 반환


    ####################################################################################################################
    # get_length(): 리스트의 길이를 반환하는 함수
    def get_length(self):
        if not self.head:  # 리스트가 비어 있는 경우
            return 0

        count = 0
        current = self.head
        while True:
            count += 1
            current = current.next
            if current == self.head:  # head로 돌아오면 종료
                break
        return count


    ####################################################################################################################
    # delete_node(data): 특정 데이터를 가진 노드를 삭제하는 함수
    def delete_node(self, data):
        if not self.head:  # 리스트가 비어 있는 경우
            print("The list is empty.")
            return

        current = self.head
        # 경우 1: 삭제할 노드가 head인 경우
        if current.data == data:
            if current.next == self.head:  # 리스트에 단 하나의 노드만 있는 경우
                self.head = None
                self.tail = None
            else:
                self.tail.next = current.next  # tail의 다음이 current의 다음을 가리킴
                current.next.prev = self.tail  # current의 다음의 prev가 tail을 가리킴
                self.head = current.next  # head를 current의 다음으로 이동
            return

        # 경우 2: 리스트 중간이나 끝에서 삭제할 노드 찾기
        while current.next != self.head:
            if current.data == data:
                current.prev.next = current.next  # 이전 노드의 next가 current의 다음을 가리킴
                current.next.prev = current.prev  # 다음 노드의 prev가 current의 이전을 가리킴
                return
            current = current.next

        # 삭제할 노드가 없으면 메시지를 출력
        print("Node not found.")


    ####################################################################################################################
    # is_circular(): 순환 구조 여부를 확인하는 함수
    def is_circular(self):
        if not self.head:  # 리스트가 비어 있으면 순환 구조가 아님
            return False

        current = self.head
        while current.next and current.next != self.head:
            current = current.next
        # current.next가 head로 돌아오면 순환 구조임
        return current.next == self.head


    ####################################################################################################################
    # traverse_list(): 리스트를 순회하며 모든 노드를 방문하는 함수
    def traverse_list(self):
        if not self.head:  # 리스트가 비어 있는 경우
            print("The list is empty.")
            return

        current = self.head
        print("Traversing the list:")
        while True:
            print(current.data, end=" <-> ")
            current = current.next
            if current == self.head:  # 순회가 끝나면 종료
                break
        print("(head)")


    ####################################################################################################################
    # find_middle_node(): 순환 리스트에서 중간 노드를 찾는 함수
    def find_middle_node(self):
        if not self.head:  # 리스트가 비어 있는 경우
            print("The list is empty.")
            return None

        slow = self.head  # 느린 포인터
        fast = self.head  # 빠른 포인터

        # 빠른 포인터가 두 칸씩 이동하며 순환
        while fast.next != self.head and fast.next.next != self.head:
            slow = slow.next  # 느린 포인터는 한 칸 이동
            fast = fast.next.next  # 빠른 포인터는 두 칸 이동

        # 리스트의 중간 노드 반환
        print("The middle node is:", slow.data)
        return slow


    ####################################################################################################################
    # insert_at_position(data, position): 주어진 위치에 노드를 삽입하는 함수
    def insert_at_position(self, data, position):
        new_node = Node(data)

        if not self.head:  # 리스트가 비어 있는 경우
            if position == 0:
                self.head = new_node
                self.head.next = self.head  # 자기 자신을 가리키도록 설정
                self.head.prev = self.head  # 자기 자신을 가리키도록 설정
                self.tail = new_node  # 새 노드가 head이자 tail이 됨
            else:
                print("Invalid position for an empty list.")
            return

        # 위치가 0이면 head 앞에 노드 삽입
        if position == 0:
            current = self.head
            while current.next != self.head:  # 마지막 노드를 찾음
                current = current.next
            current.next = new_node  # 마지막 노드가 새 노드를 가리키게 함
            new_node.prev = current  # 새 노드의 이전은 현재 tail
            new_node.next = self.head  # 새 노드가 기존 head를 가리킴
            self.head.prev = new_node  # 기존 head의 prev가 새 노드를 가리킴
            self.head = new_node  # head를 새 노드로 변경
            return

        # 중간 또는 끝에 삽입
        current = self.head
        count = 0
        while count < position - 1 and current.next != self.head:
            current = current.next
            count += 1

        if count == position - 1:  # 위치가 유효한 경우
            new_node.next = current.next
            new_node.prev = current
            if current.next != self.head:
                current.next.prev = new_node  # 다음 노드의 prev가 새 노드를 가리킴
            current.next = new_node
            if new_node.next == self.head:  # 새 노드가 tail을 가리키는 경우
                self.tail = new_node
        else:
            print("Position out of range.")


    ####################################################################################################################
    # remove_at_position(position): 주어진 위치의 노드를 삭제하는 함수
    def remove_at_position(self, position):
        if not self.head:  # 리스트가 비어 있는 경우
            print("The list is empty.")
            return

        current = self.head

        # 위치가 0인 경우 head를 삭제
        if position == 0:
            if current.next == self.head:  # 리스트에 노드가 하나인 경우
                self.head = None
                self.tail = None
            else:
                while current.next != self.head:  # 마지막 노드를 찾음
                    current = current.next
                current.next = self.head.next  # 마지막 노드가 새로운 head를 가리킴
                self.head.next.prev = current  # 새로운 head의 이전이 마지막 노드를 가리킴
                self.head = self.head.next  # head를 다음 노드로 변경
            return

        # 중간 또는 끝에서 삭제
        prev = None
        count = 0
        while count < position and current.next != self.head:
            prev = current
            current = current.next
            count += 1

        if count == position:  # 위치가 유효한 경우
            if current.next == self.head:  # 삭제할 노드가 tail인 경우
                self.tail = prev  # tail을 이전 노드로 업데이트
            prev.next = current.next
            if current.next != self.head:
                current.next.prev = prev  # 다음 노드의 prev가 이전 노드를 가리킴
        else:
            print("Position out of range.")


    ####################################################################################################################
    # reverse_list(): 리스트를 뒤집는 함수
    def reverse_list(self):
        if not self.head or self.head.next == self.head:  # 노드가 0개 또는 1개인 경우
            return

        current = self.head
        prev = None
        next_node = None

        # 리스트를 순회하며 링크를 뒤집음
        while True:
            next_node = current.next
            current.next = prev
            current.prev = next_node  # 이전과 다음 포인터를 뒤집음
            prev = current
            current = next_node
            if current == self.head:  # 원래의 head에 도달하면 중단
                break

        # 변경된 리스트의 head와 tail을 업데이트
        self.head.next = prev  # 원래의 head가 새로운 tail을 가리킴
        self.head.prev = prev  # 새로운 head의 이전은 tail
        self.head = prev  # head를 새로운 시작점으로 설정

    
    ####################################################################################################################
    # detect_cycle(): Floyd’s Cycle Detection Algorithm을 사용하여 순환 탐지
    def detect_cycle(self):
        if not self.head:
            return False

        slow = self.head
        fast = self.head

        while fast and fast.next and fast.next != self.head:
            slow = slow.next  # 한 번에 한 칸 이동
            fast = fast.next.next  # 한 번에 두 칸 이동

            if slow == fast:  # 두 포인터가 만나면 순환 존재
                return True
        return False


    ####################################################################################################################
    # split_list(): 리스트를 두 개의 순환 리스트로 분할
    def split_list(self):
        if not self.head or self.head.next == self.head:
            print("Cannot split a list with fewer than 2 nodes.")
            return None, None

        slow = self.head
        fast = self.head

        # 중간 지점을 찾기 위해 fast와 slow 포인터 사용
        while fast.next != self.head and fast.next.next != self.head:
            slow = slow.next
            fast = fast.next.next

        head1 = self.head
        head2 = slow.next
        slow.next = head1  # 첫 번째 리스트의 끝을 원형으로 만듦

        current = head2
        while current.next != self.head:
            current = current.next
        current.next = head2  # 두 번째 리스트의 끝을 원형으로 만듦

        list1 = CircularDoublyLinkedList()
        list2 = CircularDoublyLinkedList()
        list1.head = head1
        list2.head = head2

        return list1, list2


    ####################################################################################################################
    # merge_list(other_list): 두 개의 순환 리스트를 병합하는 함수.
    def merge_list(self, other_list):
        if not self.head:
            self.head = other_list.head
            return
        if not other_list.head:
            return

        # 첫 번째 리스트의 마지막 노드 찾기
        current1 = self.head
        while current1.next != self.head:
            current1 = current1.next

        # 두 번째 리스트의 마지막 노드 찾기
        current2 = other_list.head
        while current2.next != other_list.head:
            current2 = current2.next

        # 병합
        current1.next = other_list.head  # 첫 번째 리스트의 끝이 두 번째 리스트의 시작을 가리킴
        other_list.head.prev = current1  # 두 번째 리스트의 head의 이전은 첫 번째 리스트의 마지막 노드

        current2.next = self.head  # 두 번째 리스트의 끝이 첫 번째 리스트의 시작을 가리킴
        self.head.prev = current2  # 첫 번째 리스트의 head의 이전은 두 번째 리스트의 마지막 노드


    ####################################################################################################################
    # copy_list(): 현재 리스트의 복사본을 생성하는 함수.
    def copy_list(self):
        if not self.head:
            return CircularDoublyLinkedList()

        new_list = CircularDoublyLinkedList()
        current = self.head
        while True:
            new_list.add_node(current.data)  # 데이터를 복사하여 새로운 리스트에 추가
            current = current.next
            if current == self.head:
                break

        return new_list


    ####################################################################################################################
    # get_node_at_position(position): 특정 위치의 노드 반환
    def get_node_at_position(self, position):
        if not self.head:  # 리스트가 비어 있는 경우
            print("리스트가 비어 있습니다.")
            return None

        length = self.get_length()  # 리스트의 전체 길이를 가져옴
        position = position % length  # 입력된 위치가 리스트 길이를 초과할 경우 모듈러 연산을 통해 유효한 위치로 변환

        current = self.head  # 순회를 시작할 첫 번째 노드 설정
        for _ in range(position):  # 지정된 위치에 도달할 때까지 이동
            current = current.next
        return current  # 지정된 위치의 노드를 반환


    ####################################################################################################################
    # get_last_node(): 리스트의 마지막 노드를 반환하는 함수
    def get_last_node(self):
        if not self.head:  # 리스트가 비어 있는 경우
            print("리스트가 비어 있습니다.")
            return None

        current = self.head  # 순회를 시작할 첫 번째 노드 설정
        while current.next != self.head:  # 현재 노드의 다음 노드가 head가 아닐 때까지 반복
            current = current.next
        return current  # 마지막 노드를 반환


    ####################################################################################################################
    # rotate_list(steps): 리스트를 주어진 단계만큼 회전하는 함수  (steps, 양수는 오른쪽 회전, 음수는 왼쪽 회전)
    def rotate_list(self, steps):
        if not self.head or self.head.next == self.head:  
            # 리스트가 비어 있거나 노드가 하나뿐이라면 회전할 필요가 없음
            return

        length = self.get_length()  # 리스트의 전체 길이를 가져옴
        steps = steps % length  # 회전 단계 수가 리스트 길이를 초과할 경우 모듈러 연산으로 처리
        if steps == 0:  # 유효한 회전 단계 수가 0인 경우 (회전 없음)
            return

        # 오른쪽 회전일 경우
        if steps > 0:
            for _ in range(steps):
                self.head = self.head.next
                self.tail = self.tail.next
        # 왼쪽 회전일 경우
        else:
            steps = abs(steps)
            for _ in range(steps):
                self.head = self.head.prev
                self.tail = self.tail.prev


    ####################################################################################################################
    # clear_list(): 리스트의 모든 노드를 제거하는 함수.
    def clear_list(self):
        if not self.head:  # 리스트가 비어 있는 경우
            print("리스트는 이미 비어 있습니다.")
            return

        current = self.head  # 순회를 시작할 첫 번째 노드 설정
        while current.next != self.head:  # 모든 노드를 순회
            next_node = current.next  # 다음 노드를 저장
            current.next = None  # 현재 노드의 다음 참조를 제거하여 연결 해제
            current.prev = None  # 현재 노드의 이전 참조를 제거하여 연결 해제
            current = next_node  # 다음 노드로 이동

        # 마지막 노드의 연결 해제
        current.next = None
        current.prev = None
        self.head = None
        self.tail = None  # head와 tail 모두 None으로 설정하여 리스트 초기화