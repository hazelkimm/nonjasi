#include <iostream>
#include <vector>


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 조합
// 조합을 생성하는 재귀 함수
void generate_combinations(const std::vector<int>& arr, int n, int k, int index, std::vector<int>& data, int i, std::vector<std::vector<int>>& result) {
    // k개의 요소가 다 채워졌다면 결과 배열에 추가
    if (index == k) {
        result.push_back(data);  // 현재 데이터 배열을 결과 배열에 추가
        return;
    }

    // 배열의 끝에 도달하면 종료
    if (i >= n) return;

    // 현재 인덱스에 값을 추가하고 다음 재귀 호출
    data[index] = arr[i];
    generate_combinations(arr, n, k, index + 1, data, i + 1, result);
    
    // 현재 인덱스를 선택하지 않고 다음 재귀 호출
    generate_combinations(arr, n, k, index, data, i + 1, result);
}

// 조합을 생성하는 함수
std::vector<std::vector<int>> combinations(const std::vector<int>& arr, int n, int k) {
    std::vector<std::vector<int>> result;
    std::vector<int> data(k);  // 하나의 조합을 저장할 배열

    // 재귀적으로 조합을 생성
    generate_combinations(arr, n, k, 0, data, 0, result);
    
    return result;  // 결과 조합 배열 반환
}

// int main() {
//     std::vector<int> arr = {1, 2, 3, 4, 5};  // 입력 배열
//     int n = 5, k = 3;  // 배열 크기와 선택할 개수
    
//     // 조합 계산 함수 호출
//     std::vector<std::vector<int>> result = combinations(arr, n, k);

//     // 결과 출력
//     std::cout << "Combinations of " << n << " elements taken " << k << " at a time:\n";
//     for (const auto& combination : result) {
//         std::cout << "{ ";
//         for (int num : combination) {
//             std::cout << num << " ";  // 각 조합의 요소 출력
//         }
//         std::cout << "}\n";
//     }

//     return 0;
// }



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 중복조합
// 중복 조합을 생성하는 재귀 함수
void generate_combinations_(const std::vector<int>& arr, int n, int k, int index, std::vector<int>& data, int i, std::vector<std::vector<int>>& result) {
    // k개의 요소가 다 채워졌다면 결과 배열에 추가
    if (index == k) {
        result.push_back(data);  // 현재 데이터 배열을 결과 배열에 추가
        return;
    }

    // 배열의 인덱스 i부터 시작하여 중복 허용하여 재귀 호출
    for (int j = i; j < n; j++) {
        data[index] = arr[j];  // 현재 인덱스에 값을 추가하고
        generate_combinations_(arr, n, k, index + 1, data, j, result);  // 재귀 호출
    }
}

// 중복 조합을 계산하는 함수
std::vector<std::vector<int>> combinations_with_repetition(const std::vector<int>& arr, int n, int k) {
    // 최대 조합 수를 계산: C(n+k-1, k)
    int maxCombinations = 1;
    for (int i = 0; i < k; i++) {
        maxCombinations *= (n + k - 1 - i);
        maxCombinations /= (i + 1);  // 중복 조합 공식
    }

    std::vector<std::vector<int>> result;  // 결과를 저장할 벡터
    std::vector<int> data(k);  // 하나의 조합을 저장할 배열

    // 재귀적으로 중복 조합을 생성
    generate_combinations_(arr, n, k, 0, data, 0, result);

    return result;  // 결과 조합 배열 반환
}

// int main() {
//     std::vector<int> arr = {1, 2, 3};  // 입력 배열
//     int n = 3, k = 2;  // 배열 크기와 선택할 개수
    
//     // 중복 조합 계산 함수 호출
//     std::vector<std::vector<int>> result = combinations_with_repetition(arr, n, k);

//     // 결과 출력
//     std::cout << "Combinations with repetition of " << n << " elements taken " << k << " at a time:\n";
//     for (const auto& combination : result) {
//         std::cout << "{ ";
//         for (int num : combination) {
//             std::cout << num << " ";  // 각 조합의 요소 출력
//         }
//         std::cout << "}\n";
//     }

//     return 0;
// }