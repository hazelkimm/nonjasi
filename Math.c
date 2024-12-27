/*
int gcd(int a, int b):  최대공약수
int lcm(int a, int b): 최소공배수
bool is_prime(int n): 소수 판별
int fibonacci(int n): 피보나치 수열
int factorial(int n): 팩토리얼 계산
void prime_factors(int n): 소인수분해
void sieve_of_eratosthenes(int n): 에라토스테네스의 체
int binary_search(int arr[], int size, int target): 이진 탐색
void merge_sort(int arr[], int left, int right): 병합 정렬
*/


#include <stdio.h>
#include <stdbool.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 최대공약수를 계산하는 함수
int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// int main() {
//     int a = 12, b = 15;
//     printf("GCD: %d\n", gcd(a, b));
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 최대공약수를 계산하는 함수
int gcd_(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// 최소공배수를 계산하는 함수
int lcm(int a, int b) {
    return (a * b) / gcd_(a, b);
}

// int main() {
//     int a = 12, b = 15;
//     printf("LCM: %d\n", lcm(a, b));
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 제곱근을 계산하는 함수 (sqrt()를 사용하지 않음)
int square_root(int n) {
    int left = 1, right = n, mid, ans = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (mid * mid == n) {
            return mid;  // 정확한 제곱근을 찾은 경우
        }
        if (mid * mid < n) {
            left = mid + 1;
            ans = mid;  // mid * mid < n이면 ans를 갱신
        } else {
            right = mid - 1;
        }
    }
    return ans;  // 가장 근접한 정수 값 반환
}

// 소수 판별 함수
bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    int limit = square_root(n);  // 제곱근을 구함
    for (int i = 2; i <= limit; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// int main() {
//     int number = 17;
//     if (is_prime(number)) {
//         printf("%d is prime.\n", number);
//     } else {
//         printf("%d is not prime.\n", number);
//     }
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 피보나치 수열 함수
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        int temp = b;
        b = a + b;
        a = temp;
    }
    return b;
}

// int main() {
//     printf("%d\n", fibonacci(10));  // 결과: 55
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 팩토리얼 계산 함수
int factorial(int n) {
    if (n == 0) {
        return 1;  // 0!은 1
    }
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;  // i와 result를 곱함
    }
    return result;
}

// int main() {
//     printf("%d\n", factorial(5));  // 결과: 120
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 소인수 분해 함수
void prime_factors(int n) {
    // 2의 배수 처리
    while (n % 2 == 0) {
        printf("%d ", 2);
        n /= 2;
    }

    // 3부터 시작하여 홀수 인수들에 대해 처리
    for (int i = 3; i <= square_root(n); i += 2) {
        while (n % i == 0) {
            printf("%d ", i);
            n /= i;
        }
    }

    // n이 2보다 큰 소수일 경우 출력
    if (n > 2) {
        printf("%d ", n);
    }
}

// int main() {
//     prime_factors(56);  // 결과: 2 2 2 7 
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 에라토스테네스의 체 함수
void sieve_of_eratosthenes(int n) {
    bool sieve[n + 1];
    for (int i = 0; i <= n; i++) {
        sieve[i] = true;
    }
    sieve[0] = false;  // 0은 소수가 아님
    sieve[1] = false;  // 1은 소수가 아님

    // 2부터 sqrt(n)까지 반복하여 소수 판별
    for (int i = 2; i <= square_root(n); i++) {
        if (sieve[i]) {
            for (int j = i * i; j <= n; j += i) {
                sieve[j] = false;
            }
        }
    }

    // 소수 출력
    for (int i = 2; i <= n; i++) {
        if (sieve[i]) {
            printf("%d ", i);
        }
    }
}

// int main() {
//     sieve_of_eratosthenes(30);  // 결과: 2 3 5 7 11 13 17 19 23 29
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 이진 탐색 함수
int binary_search(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;  // 목표값을 찾은 경우
        } else if (arr[mid] < target) {
            left = mid + 1;  // 오른쪽 부분 탐색
        } else {
            right = mid - 1;  // 왼쪽 부분 탐색
        }
    }
    return -1;  // 찾지 못한 경우
}

// int main() {
//     int arr[] = {1, 3, 5, 7, 9, 11};
//     int size = sizeof(arr) / sizeof(arr[0]);  // 배열의 크기 계산
//     int target = 5;
//     int index = binary_search(arr, size, target);
//     printf("The position of value %d is: %d\n", target, index);  // 결과: 2
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 병합 함수
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];  // 왼쪽과 오른쪽 배열

    // 왼쪽 배열 L에 복사
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }

    // 오른쪽 배열 R에 복사
    for (int i = 0; i < n2; i++) {
        R[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    
    // 병합 단계
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // L 배열에 남은 요소 복사
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // R 배열에 남은 요소 복사
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 병합 정렬 함수
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);       // 왼쪽 부분 정렬
        merge_sort(arr, mid + 1, right);  // 오른쪽 부분 정렬
        merge(arr, left, mid, right);     // 병합
    }
}

// int main() {
//     // 정수 배열 정의
//     int arr[] = {38, 27, 43, 3, 9, 82, 10};
//     int size = sizeof(arr) / sizeof(arr[0]);  // 배열의 크기 계산
    
//     // 병합 정렬 수행
//     merge_sort(arr, 0, size - 1);
    
//     // 정렬된 배열 출력
//     printf("Sorted array: ");
//     for (int i = 0; i < size; i++) {
//         printf("%d ", arr[i]);
//     }
//     printf("\n");

//     return 0;
// }