/*
1. 배열 초기화 및 출력: void initializeArray, void printArray
2. 배열의 최대값, 최소값 찾기: int findMax, int findMin
3. 배열의 합과 평균 계산: int calculateSum, double calculateAverage
4. 배열의 정렬: void sortArray
5. 배열에서 특정 값 찾기: int findValueIndex
6. 2차원 배열 초기화 및 출력: void initialize2DArray, void print2DArray
7. 배열의 회전: void rotateRight
8. 중복 제거: int removeDuplicates
9. 배열에서 k번째 최댓값 찾기: int findKthLargest
*/

#include <iostream>
#include <vector>
#include <algorithm> // std::max_element, std::min_element, std::sort, std::find, std::unique, std::erase
#include <numeric> // std::accumulate

void initializeArray(std::vector<int>& arr, int value) {
    for (auto& elem : arr) {
        elem = value;
    }
}
// void initializeArray(std::vector<int>& arr, int value) {
//     for (int i = 0; i < arr.size(); i++) {
//         arr[i] = value;
//     }
// }

/////////////////////////////////////////////////////////////////////////////////////
void printArray(const std::vector<int>& arr) {
    for (const auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
// void printArray(const std::vector<int>& arr) {
//     for (int i = 0; i < arr.size(); i++) {
//         std::cout << arr[i] << " ";
//     }
//     std::cout << std::endl;
// }

/////////////////////////////////////////////////////////////////////////////////////
int findMax(const std::vector<int>& arr) {
    return *std::max_element(arr.begin(), arr.end());
}
// int findMax(const std::vector<int>& arr) {
//     int max = arr[0];
//     for (int i = 1; i < arr.size(); i++) {
//         if (arr[i] > max) {
//             max = arr[i];
//         }
//     }
//     return max;
// }

/////////////////////////////////////////////////////////////////////////////////////
int findMin(const std::vector<int>& arr) {
    return *std::min_element(arr.begin(), arr.end());
}
// int findMin(const std::vector<int>& arr) {
//     int min = arr[0];
//     for (int i = 1; i < arr.size(); i++) {
//         if (arr[i] < min) {
//             min = arr[i];
//         }
//     }
//     return min;
// }

/////////////////////////////////////////////////////////////////////////////////////
int calculateSum(const std::vector<int>& arr) {
    return std::accumulate(arr.begin(), arr.end(), 0);
}
// int calculateSum(const std::vector<int>& arr) {
//     int sum = 0;
//     for (int i = 0; i < arr.size(); i++) {
//         sum += arr[i];
//     }
//     return sum;
// }

/////////////////////////////////////////////////////////////////////////////////////
double calculateAverage(const std::vector<int>& arr) {
    int sum = calculateSum(arr);
    return static_cast<double>(sum) / arr.size();
}

/////////////////////////////////////////////////////////////////////////////////////
void sortArray(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
}
// void bubbleSort(std::vector<int>& arr) {
//     for (int i = 0; i < arr.size() - 1; i++) {
//         for (int j = 0; j < arr.size() - i - 1; j++) {
//             if (arr[j] > arr[j + 1]) {
//                 int temp = arr[j];
//                 arr[j] = arr[j + 1];
//                 arr[j + 1] = temp;
//             }
//         }
//     }
// }

/////////////////////////////////////////////////////////////////////////////////////
int findValueIndex(const std::vector<int>& arr, int value) {
    auto it = std::find(arr.begin(), arr.end(), value);
    if (it != arr.end()) {
        return std::distance(arr.begin(), it); // 값의 인덱스 반환
    }
    return -1; // 값이 없을 경우 -1 반환
}
// int findValueIndex(const std::vector<int>& arr, int value) {
//     for (int i = 0; i < arr.size(); i++) {
//         if (arr[i] == value) {
//             return i; // 값의 인덱스 반환
//         }
//     }
//     return -1; // 값이 없을 경우 -1 반환
// }

/////////////////////////////////////////////////////////////////////////////////////
void initialize2DArray(std::vector<std::vector<int>>& arr, int value) {
    for (auto& row : arr) {
        for (auto& elem : row) {
            elem = value;
        }
    }
}
// void initialize2DArray(std::vector<std::vector<int>>& arr, int value) {
//     for (int i = 0; i < arr.size(); i++) {
//         for (int j = 0; j < arr[i].size(); j++) {
//             arr[i][j] = value;
//         }
//     }
// }

/////////////////////////////////////////////////////////////////////////////////////
void print2DArray(const std::vector<std::vector<int>>& arr) {
    for (const auto& row : arr) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}
// void print2DArray(const std::vector<std::vector<int>>& arr) {
//     for (int i = 0; i < arr.size(); i++) {
//         for (int j = 0; j < arr[i].size(); j++) {
//             std::cout << arr[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
// }

/////////////////////////////////////////////////////////////////////////////////////
void rotateRight(std::vector<int>& arr, int k) {
    int n = arr.size();
    k = k % n; // 회전 수가 배열 크기보다 클 경우 처리

    std::rotate(arr.begin(), arr.end() - k, arr.end());
}
// void rotateRight(std::vector<int>& arr, int k) {
//     int n = arr.size();
//     k = k % n; // 회전 수가 배열 크기보다 클 경우 처리

//     std::vector<int> temp(k);
//     for (int i = 0; i < k; i++) {
//         temp[i] = arr[n - k + i];
//     }

//     for (int i = n - 1; i >= k; i--) {
//         arr[i] = arr[i - k];
//     }

//     for (int i = 0; i < k; i++) {
//         arr[i] = temp[i];
//     }
// }

/////////////////////////////////////////////////////////////////////////////////////
void removeDuplicates(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end()); // 중복 제거를 위해 정렬
    auto last = std::unique(arr.begin(), arr.end()); // 중복을 제거
    arr.erase(last, arr.end()); // 실제 배열에서 제거
}
// void removeDuplicates(std::vector<int>& arr) {
//     for (int i = 0; i < arr.size(); i++) {
//         for (int j = i + 1; j < arr.size(); ) {
//             if (arr[i] == arr[j]) {
//                 arr.erase(arr.begin() + j); // 중복값 제거
//             } else {
//                 j++;
//             }
//         }
//     }
// }

/////////////////////////////////////////////////////////////////////////////////////
int findKthLargest(std::vector<int>& arr, int k) {
    std::sort(arr.begin(), arr.end(), std::greater<int>()); // 내림차순 정렬
    return arr[k - 1]; // k번째 값 반환
}
// int findKthLargest(std::vector<int>& arr, int k) {
//     for (int i = 0; i < k; i++) {
//         int maxIndex = i;
//         for (int j = i + 1; j < arr.size(); j++) {
//             if (arr[j] > arr[maxIndex]) {
//                 maxIndex = j;
//             }
//         }
//         std::swap(arr[i], arr[maxIndex]); // 최대값을 앞으로 이동
//     }
//     return arr[k - 1]; // k번째 값 반환
// }