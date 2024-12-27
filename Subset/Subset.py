'''
모든 부분 집합 구하기
-all_subsets1: 공집합 포함
-all_subsets2: 공집합 불포함
'''


def all_subsets1(lst):
    # 리스트가 비어 있으면, 빈 부분 집합을 반환
    # 빈 리스트의 경우, 부분 집합은 [[]] (빈 리스트) 하나뿐임
    if len(lst) == 0:
        return [[]]
    
    # 리스트의 첫 번째 요소를 'first'로 분리하고, 나머지 리스트는 'rest'로 분리
    first = lst[0]
    rest = lst[1:]
    
    # 'rest' 리스트에 대해 모든 부분 집합을 구함
    # 재귀 호출을 통해 나머지 리스트의 부분 집합을 계산
    subsets_without_first = all_subsets1(rest)
    
    # 'first' 요소를 포함한 부분 집합을 만듦
    # 'subsets_without_first'의 각 부분 집합에 'first'를 추가한 새로운 부분 집합을 생성
    subsets_with_first = [[first] + subset for subset in subsets_without_first]
    
    # 두 부분 집합을 합쳐서 반환
    # 첫 번째 부분 집합은 'first'를 포함하지 않은 부분 집합들
    # 두 번째 부분 집합은 'first'를 포함한 부분 집합들
    return subsets_without_first + subsets_with_first

# 리스트 예시
lst = [1, 2, 3]

# 'all_subsets1' 함수를 호출하여 모든 부분 집합을 출력
for subset in all_subsets1(lst):
    print(subset)


###################################################################################################################
def all_subsets2(lst):
    # 리스트가 비어 있으면, 빈 리스트를 반환 (빈 부분 집합은 제외)
    if len(lst) == 0:
        return []
    
    # 리스트의 첫 번째 요소를 'first'로 분리하고, 나머지 리스트는 'rest'로 분리
    first = lst[0]
    rest = lst[1:]
    
    # 'rest' 리스트에 대해 모든 부분 집합을 구함
    # 재귀 호출을 통해 나머지 리스트의 부분 집합을 계산
    subsets_without_first = all_subsets2(rest)
    
    # 'first' 요소를 포함한 부분 집합을 만듦
    # 'subsets_without_first'의 각 부분 집합에 'first'를 추가한 새로운 부분 집합을 생성
    subsets_with_first = [[first] + subset for subset in subsets_without_first]
    
    # 'subsets_with_first'에 'first'만 있는 부분 집합을 추가
    subsets_with_first.append([first])
    
    # 빈 리스트 제외하고 반환
    # 빈 리스트는 반환하지 않도록 주의
    return subsets_without_first + subsets_with_first

# 리스트 예시
lst = [1, 2, 3]

# 'all_subsets2' 함수를 호출하여 빈 리스트 제외한 모든 부분 집합을 출력
for subset in all_subsets2(lst):
    print(subset)