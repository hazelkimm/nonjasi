'''
목적: 주어진 배열에서 길이 n의 모든 순열을 생성합니다.
1. 초기화:
    result: 결과를 저장할 빈 리스트를 초기화합니다.
2. 길이 검사:
    요청한 길이 n이 배열의 길이보다 크면 가능한 순열이 없으므로 빈 리스트를 반환합니다.
3. 길이 n이 1일 경우:
    배열의 각 원소를 단일 원소의 리스트로 만들어 result에 추가합니다.
    for 문을 사용하여 배열의 각 원소를 순회합니다.
4. 길이 n이 1보다 클 경우:
    for 문을 사용하여 배열의 각 원소를 순회합니다.
    현재 원소를 제외한 배열(ans)을 생성합니다. (ans = arr[:i] + arr[i+1:])
    재귀적으로 길이 n-1의 순열을 생성하고, 각 순열에 현재 원소를 추가하여 결과를 생성합니다.
    현재 원소와 나머지 순열을 결합하여 result에 추가합니다.
5. 결과 반환:
    최종적으로 모든 순열이 저장된 result를 반환합니다.
'''
def my_permutation(arr, n):
    result = []  # 결과를 저장할 리스트 초기화
    
    # 요청한 길이 n이 배열의 길이보다 크면 빈 리스트 반환
    if n > len(arr):
        return result
    
    # n이 1이면 배열의 각 원소를 단일 원소의 리스트로 결과에 추가
    if n == 1:
        i = 0
        for i in range(len(arr)):
            result.append([arr[i]])
    # n이 1보다 크면 재귀적으로 순열 생성
    elif n > 1:
        for i in range(len(arr)):
            ans = arr[:i] + arr[i+1:]  # 현재 원소를 제외한 배열 생성
            # 재귀적으로 길이 n-1인 순열 생성
            for p in my_permutation(ans, n-1):
                result.append([arr[i]] + p)  # 현재 원소와 나머지 순열 결합

    return result


if __name__ == "__main__":
    import itertools

    arr1 = ['A', 'B', 'C']
    print(my_permutation(arr1, 2))
    nPr = itertools.permutations(arr1, 2)
    print(list(nPr))

    arr2 = ['A', 'B', 'C', 'C']
    print(my_permutation(arr2, 2))
    nPr = itertools.permutations(arr2, 2)
    print(list(nPr))

