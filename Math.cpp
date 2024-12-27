/*
int gcd(int a, int b): 최대공약수
int lcm(int a, int b): 최소공배수
bool is_prime(int n): 소수 판별
int fibonacci(int n): 피보나치 수열 
int factorial(int n): 팩토리얼 계산 
void prime_factors(int n): 소인수분해 
vector<int> sieve_of_eratosthenes(int n): 에라토스테네스의 체
int binary_search(const vector<int>& arr, int target): 이진 탐색
void merge_sort(vector<int>& arr, int left, int right): 병합 정렬
*/


#include <iostream>

using namespace std;

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
//     std::cout << "GCD: " << gcd(a, b) << std::endl;
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 최소공배수를 계산하는 함수
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

// int main() {
//     int a = 12, b = 15;
//     std::cout << "LCM: " << lcm(a, b) << std::endl;
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 소수 판별 함수

// #include <cmath>

// bool is_prime(int n) {
//     if (n <= 1) {
//         return false;
//     }
//     for (int i = 2; i <= std::sqrt(n); i++) {
//         if (n % i == 0) {
//             return false;
//         }
//     }
//     return true;
// }

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
//         std::cout << number << " is prime." << std::endl;
//     } else {
//         std::cout << number << " is not prime." << std::endl;
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
//     std::cout << fibonacci(10) << std::endl;  // 결과: 55
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 팩토리얼 계산 함수
int factorial(int n) {
    if (n == 0) {
        return 1;
    }
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// int main() {
//     std::cout << factorial(5) << std::endl;  // 결과: 120
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 소인수분해 함수

// #include <cmath>

// void prime_factors(int n) {
//     while (n % 2 == 0) {
//         std::cout << 2 << " ";
//         n /= 2;
//     }
//     for (int i = 3; i <= std::sqrt(n); i += 2) {
//         while (n % i == 0) {
//             std::cout << i << " ";
//             n /= i;
//         }
//     }
//     if (n > 2) {
//         std::cout << n << " ";
//     }
// }

void prime_factors(int n) {
    // Handle factor of 2
    while (n % 2 == 0) {
        std::cout << 2 << " ";
        n /= 2;
    }
    
    // Check for odd factors starting from 3
    for (int i = 3; i <= square_root(n); i += 2) {
        while (n % i == 0) {
            std::cout << i << " ";
            n /= i;
        }
    }
    
    // If n is a prime number greater than 2, print it
    if (n > 2) {
        std::cout << n << " ";
    }
}

// int main() {
//     prime_factors(56);  // 결과: 2 2 2 7 
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 에라토스테네스의 체 함수
#include <vector>
#include <cmath>

vector<int> sieve_of_eratosthenes(int n) {
    vector<bool> sieve(n+1, true);
    sieve[0] = false;
    sieve[1] = false;

    for (int i = 2; i <= std::sqrt(n); i++) {
        if (sieve[i]) {
            for (int j = i*i; j <= n; j += i) {
                sieve[j] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 0; i <= n; i++) {
        if (sieve[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

// int main() {
//     vector<int> primes = sieve_of_eratosthenes(30);
//     for (int prime : primes) {
//         cout << prime << " ";
//     }  // 결과: 2 3 5 7 11 13 17 19 23 29
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 이진 탐색 함수
int binary_search(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;  // 찾지 못한 경우
}

// int main() {
//     vector<int> arr = {1, 3, 5, 7, 9, 11};
//     int target = 5;
//     int index = binary_search(arr, target);
//     cout << "The position of value " << target << " is: " << index << endl;  // 결과: 2
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 병합 정렬 함수
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
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

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// int main() {
//     // Define an array of integers
//     vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    
//     // Sort the array using merge sort
//     merge_sort(arr, 0, arr.size() - 1);
    
//     // Output the sorted array
//     cout << "Sorted array: ";
//     for (int num : arr) {
//         cout << num << " ";
//     }
//     cout << endl;
    
//     return 0;
// }