def my_combination1(arr, r):
    # 결과를 저장할 빈 리스트를 초기화합니다.
    result = []
    
    # 기저 사례: 조합의 길이가 0인 경우 빈 리스트의 리스트를 반환합니다.
    if r == 0:
        return [[]]
    
    # 배열의 각 요소에 대해 반복합니다.
    for i in range(len(arr)):
        # 현재 인덱스 i의 요소를 선택합니다.
        elem = arr[i]
        
        # 현재 요소를 제외한 나머지 배열 arr[i + 1:]에서
        # n - 1개의 요소로 이루어진 조합을 재귀적으로 생성합니다.
        for rest in my_combination1(arr[i + 1:], r - 1):
            # 현재 요소 elem과 나머지 조합 rest를 합쳐 새로운 조합을 만듭니다.
            result.append([elem] + rest)
    
    # 생성된 모든 조합을 반환합니다.
    return result

############################################################################################################################

def my_combination2(arr, r):
    # 1. 배열을 정렬합니다.
    #    정렬은 중복된 요소를 처리하기 쉽도록 하기 위해 필요합니다.
    arr = sorted(arr)
    
    # 2. 각 요소의 사용 여부를 추적하기 위한 리스트를 생성합니다.
    #    초기값은 모두 0으로, 아직 사용되지 않은 상태를 나타냅니다.
    used = [0 for _ in range(len(arr))]

    # 3. 조합을 생성하는 재귀 함수 정의
    def generate(chosen):
        # 3-1. 현재까지 선택된 조합(chosen)의 길이가 r에 도달하면
        #      해당 조합을 출력하고 종료합니다.
        if len(chosen) == r:
            print(chosen)  # 생성된 조합 출력
            return  # 종료하여 더 이상 하위 재귀를 수행하지 않습니다.

        # 3-2. 선택 가능한 다음 요소의 시작 인덱스를 설정합니다.
        #      - `chosen`이 비어 있으면 배열의 처음부터 시작
        #      - `chosen`이 비어 있지 않으면, 마지막으로 선택된 요소의 인덱스 다음부터 시작
        start = arr.index(chosen[-1]) + 1 if chosen else 0

        # 3-3. 배열의 모든 요소를 탐색하며 조합을 생성합니다.
        for nxt in range(start, len(arr)):
            # 3-4. 요소를 선택할 수 있는 조건을 확인합니다.
            #      - `used[nxt] == 0`: 해당 요소가 아직 선택되지 않았을 때
            #      - `(nxt == 0 or arr[nxt-1] != arr[nxt] or used[nxt-1])`:
            #        중복된 요소는 직전 요소가 선택된 경우에만 선택 가능
            if used[nxt] == 0 and (nxt == 0 or arr[nxt-1] != arr[nxt] or used[nxt-1]):
                # 3-5. 조건을 만족하면 현재 요소를 조합(chosen)에 추가하고,
                #      사용 상태를 갱신합니다.
                chosen.append(arr[nxt])
                used[nxt] = 1

                # 3-6. 재귀 호출을 통해 다음 요소의 조합을 생성합니다.
                generate(chosen)

                # 3-7. 재귀 호출이 종료된 후, 현재 요소를 선택 취소하여
                #      이전 상태로 되돌립니다.
                chosen.pop()  # 마지막으로 추가된 요소 제거
                used[nxt] = 0  # 해당 요소의 사용 상태를 초기화

    # 4. 조합 생성을 빈 리스트로 시작합니다.
    generate([])

############################################################################################################################

def my_combination3(arr, r):
    # 1. 입력 배열을 정렬하여 중복 조합 처리를 용이하게 만듭니다.
    arr = sorted(arr)
    # 2. 배열의 각 요소가 사용되었는지 추적하기 위한 리스트를 초기화합니다.
    #    각 요소의 사용 상태를 0(미사용)으로 초기화합니다.
    used = [0 for _ in range(len(arr))]
    # 3. 결과 조합을 저장할 리스트를 생성합니다.
    result = []

    # 4. 조합을 생성하는 재귀 함수 정의
    def generate(chosen):
        # 4-1. 현재까지 선택된 조합의 길이가 r에 도달하면
        #      해당 조합을 결과 리스트에 추가하고 종료합니다.
        if len(chosen) == r:
            result.append(chosen[:])  # 현재 조합을 복사하여 저장
            return

        # 4-2. 선택 가능한 다음 요소의 시작 인덱스를 결정합니다.
        #      선택된 요소가 없으면 처음부터 탐색, 그렇지 않으면 마지막 선택된 요소 이후부터 탐색.
        start = arr.index(chosen[-1]) + 1 if chosen else 0

        # 4-3. 배열의 모든 요소를 탐색합니다.
        for nxt in range(start, len(arr)):
            # 4-4. 다음 조건을 만족하는 경우에만 현재 요소를 선택합니다:
            #      - 현재 요소가 사용되지 않았음 (`used[nxt] == 0`)
            #      - 중복 요소의 경우, 직전 요소가 선택된 경우에만 선택 가능
            #        (중복 처리를 위해 `arr[nxt-1] == arr[nxt]` 확인)
            if used[nxt] == 0 and (nxt == 0 or arr[nxt-1] != arr[nxt] or used[nxt-1]):
                # 4-5. 조건을 만족하면 요소를 선택(chosen에 추가)하고 사용 상태를 갱신합니다.
                chosen.append(arr[nxt])
                used[nxt] = 1

                # 4-6. 재귀 호출을 통해 다음 요소의 조합을 생성합니다.
                generate(chosen)

                # 4-7. 재귀 호출이 끝나면, 선택을 철회하고 사용 상태를 복구합니다.
                chosen.pop()
                used[nxt] = 0

    # 5. 초기 빈 조합으로 시작하여 조합 생성을 시작합니다.
    generate([])

    # 6. 결과 리스트를 반환합니다.
    return result

############################################################################################################################

# 중복조합
def my_combinations_with_replacement(elements, r):
    # 조합의 길이가 0이면 빈 조합을 반환 (종료 조건)
    if r == 0:
        return [[]]
    
    # 요소가 더 이상 없는데 조합의 길이가 0이 아니면 빈 리스트 반환 (종료 조건)
    if not elements:
        return []
    
    # 첫 번째 요소를 포함하는 경우
    # 조합의 길이를 1 줄이고, 현재 요소를 포함하는 하위 조합들을 계산
    with_first = my_combinations_with_replacement(elements, r - 1)
    
    # 첫 번째 요소를 현재 조합에 추가
    with_first = [[elements[0]] + comb for comb in with_first]
    
    # 첫 번째 요소를 포함하지 않는 경우
    # 첫 번째 요소를 제외한 나머지 요소들로 조합 계산
    without_first = my_combinations_with_replacement(elements[1:], r)
    
    # 첫 번째 요소를 포함하는 경우와 포함하지 않는 경우를 합쳐 최종 결과 반환
    return with_first + without_first



if __name__ == "__main__":
    import itertools

    arr = ['A', 'B', 'C']

    print(my_combination1(arr, 2))

    my_combination2(arr,2)

    print(my_combination3(arr,2))

    nCr = itertools.combinations(arr, 2)
    print(list(nCr))

    print('--------------------------------------------------')

    print(my_combinations_with_replacement(arr,2))

    result = itertools.combinations_with_replacement(arr, 2) # 중복조합
    print(list(result))