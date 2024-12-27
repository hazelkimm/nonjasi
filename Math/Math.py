'''
gcd(a, b): 최대공약수
lcm(a, b): 최대공배수
is_prime(n): 소수 판별
fibonacci(n): 피보나치 수열 계산
factorial(n): 팩토리얼 계산
prime_factors(n): 소인수분해
sieve_of_eratosthenes(n): 에라토스테네스의 체
binary_search(arr, target): 이진 탐색
merge_sort(arr, left, right): 병합 정렬
'''


################################################################################################################
# 최대공약수
def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)

# result = gcd(48, 18)  # 48과 18의 최대공약수 계산
# print(result)         # 출력: 6


################################################################################################################
def gcd_(a, b):
    # 최대공약수를 계산하는 유클리드 호제법
    while b != 0:
        temp = a % b
        a = b
        b = temp
    return a

# 최소공배수
def lcm(a, b):
    """
    최소공배수를 계산하는 함수
    공식: LCM(a, b) = (a * b) // GCD(a, b)
    """
    return (a * b) // gcd_(a, b)

# 예제 사용
# a, b = 12, 15
# print(f"LCM of {a} and {b} is {lcm(a, b)}")  # 출력: LCM of 12 and 15 is 60


################################################################################################################
# import math

# def is_prime(n):
#     """
#     주어진 수가 소수인지 판별하는 함수.
#     소수 조건:
#     - 1보다 커야 함.
#     - 1과 자기 자신 외에 나누어 떨어지는 약수가 없어야 함.
#     """
#     if n <= 1:
#         return False  # 1 이하의 수는 소수가 아님
    
#     # 2부터 sqrt(n)까지의 숫자로 나누어 떨어지는지 검사
#     for i in range(2, int(math.sqrt(n)) + 1):
#         if n % i == 0:
#             return False  # 나누어 떨어지면 소수가 아님
    
#     return True  # 나누어 떨어지는 수가 없으면 소수

# # 예제 사용
# print(is_prime(29))  # 출력: True (29는 소수)
# print(is_prime(15))  # 출력: False (15는 소수가 아님)

# 소수 판별
def is_prime(n):
    """
    주어진 수가 소수인지 판별하는 함수.
    """
    if n <= 1:
        return False  # 1 이하의 수는 소수가 아님
    
    # 2부터 n의 제곱근까지 나누어 떨어지는지 확인
    i = 2
    while i * i <= n:  # 제곱근을 계산하지 않고 i * i 방식으로 확인
        if n % i == 0:
            return False  # 나누어 떨어지면 소수가 아님
        i += 1
    
    return True  # 나누어 떨어지는 수가 없으면 소수

# 예제 사용
# print(is_prime(29))  # 출력: True (29는 소수)
# print(is_prime(15))  # 출력: False (15는 소수가 아님)


################################################################################################################
# 피보나치 수열 계산
def fibonacci(n):
    """
    피보나치 수열의 n번째 수를 계산하는 함수.
    n이 0 또는 1이면 n 자체를 반환합니다.
    그렇지 않으면 반복문을 사용하여 계산합니다.
    """
    if n <= 1:
        return n  # n이 0 또는 1일 때 결과 반환
    
    a, b = 0, 1  # 초기값 설정 (F(0) = 0, F(1) = 1)
    for i in range(2, n + 1):  # 2부터 n까지 반복
        a, b = b, a + b  # a는 이전 b, b는 a와 b의 합으로 업데이트
    
    return b  # n번째 피보나치 수 반환

# 예제 사용
# print(fibonacci(0))  # 출력: 0
# print(fibonacci(1))  # 출력: 1
# print(fibonacci(10)) # 출력: 55 (F(10) = 55)


################################################################################################################
# 팩토리얼 계산
def factorial(n):
    """
    주어진 숫자 n에 대한 팩토리얼을 계산하는 함수.
    n! = n * (n-1) * (n-2) * ... * 1
    """
    if n == 0:
        return 1  # 0!은 1
    result = 1
    for i in range(1, n + 1):
        result *= i  # result에 i를 곱함
    return result

# 예제 사용
# print(factorial(5))  # 출력: 120
# print(factorial(0))  # 출력: 1


################################################################################################################
# 소인수분해
def prime_factors(n):
    """
    주어진 정수 n의 소인수 분해 결과를 출력하는 함수.
    """
    # 2로 나눌 수 있는 모든 경우 처리
    while n % 2 == 0:
        print(2, end=" ")  # 2는 소수이므로 출력
        n //= 2  # n을 2로 나눈 몫으로 업데이트

    # 홀수로 나눌 수 있는 모든 경우 처리
    i = 3
    while i * i <= n:  # i의 제곱이 n 이하일 때만 반복
        while n % i == 0:
            print(i, end=" ")  # i는 소수이므로 출력
            n //= i  # n을 i로 나눈 몫으로 업데이트
        i += 2  # 다음 홀수로 이동

    # n이 소수로 남아 있을 경우 출력
    if n > 2:
        print(n, end=" ")

# 예제 사용
# prime_factors(315)  # 출력: 3 3 5 7
# prime_factors(84)   # 출력: 2 2 3 7


################################################################################################################
# 에라토스테네스의 체
def sieve_of_eratosthenes(n):
    """
    2부터 n까지의 소수를 찾는 에라토스테네스의 체 알고리즘.
    """
    # 모든 숫자를 소수(True)로 초기화
    sieve = [True] * (n + 1)
    sieve[0] = False  # 0은 소수가 아님
    sieve[1] = False  # 1도 소수가 아님

    # 2부터 √n까지 반복
    for i in range(2, int(n ** 0.5) + 1):
        if sieve[i]:  # 현재 숫자가 소수이면
            # i의 배수를 모두 소수가 아니라고 표시
            for j in range(i * i, n + 1, i):
                sieve[j] = False

    # 소수인 숫자를 리스트로 수집
    primes = [i for i in range(n + 1) if sieve[i]]
    return primes

# 예제 사용
# print(sieve_of_eratosthenes(30))  # 출력: [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]


################################################################################################################
# 이진 탐색
def binary_search(arr, target):
    """
    정렬된 배열에서 대상 값을 찾는 이진 탐색 함수.
    값을 찾으면 인덱스를 반환하고, 없으면 -1을 반환합니다.
    """
    left, right = 0, len(arr) - 1  # 탐색 범위 초기화

    while left <= right:
        # 중간 인덱스 계산 (오버플로우 방지)
        mid = left + (right - left) // 2

        if arr[mid] == target:
            return mid  # 대상 값을 찾은 경우
        elif arr[mid] < target:
            left = mid + 1  # 오른쪽 부분 배열로 이동
        else:
            right = mid - 1  # 왼쪽 부분 배열로 이동

    return -1  # 대상 값을 찾지 못한 경우

# 예제 사용
# arr = [1, 3, 5, 7, 9, 11]
# print(binary_search(arr, 5))  # 출력: 2 (5는 인덱스 2에 있음)
# print(binary_search(arr, 6))  # 출력: -1 (6은 배열에 없음)


################################################################################################################
# 병합 정렬
def merge(arr, left, mid, right):
    """
    두 하위 배열을 병합하여 정렬된 배열로 만듭니다.
    - arr[left:mid+1]: 첫 번째 하위 배열
    - arr[mid+1:right+1]: 두 번째 하위 배열
    """
    # 두 하위 배열의 길이 계산
    n1 = mid - left + 1
    n2 = right - mid

    # 하위 배열 생성
    L = arr[left:mid + 1]
    R = arr[mid + 1:right + 1]

    # 병합 과정
    i, j, k = 0, 0, left
    while i < n1 and j < n2:
        if L[i] <= R[j]:
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
        k += 1

    # 남은 요소 처리
    while i < n1:
        arr[k] = L[i]
        i += 1
        k += 1

    while j < n2:
        arr[k] = R[j]
        j += 1
        k += 1


def merge_sort(arr, left, right):
    """
    주어진 배열을 병합 정렬로 정렬하는 함수.
    """
    if left < right:
        # 중간 지점 계산
        mid = left + (right - left) // 2

        # 왼쪽과 오른쪽 하위 배열 정렬
        merge_sort(arr, left, mid)
        merge_sort(arr, mid + 1, right)

        # 정렬된 하위 배열 병합
        merge(arr, left, mid, right)


# 예제 사용
arr = [12, 11, 13, 5, 6, 7]
merge_sort(arr, 0, len(arr) - 1)
print(arr)  # 출력: [5, 6, 7, 11, 12, 13]