#include <iostream>
#include <vector>
#include <string>


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 조합
// 재귀적으로 문자 배열에 대한 조합을 생성하는 함수
void generate_combinations(const std::vector<char>& arr, int n, int k, int index, std::vector<char>& data, int i, std::vector<std::string>& result) {
    // k개의 요소가 다 채워졌다면 결과 배열에 추가
    if (index == k) {
        result.push_back(std::string(data.begin(), data.begin() + k));  // 현재 조합을 문자열로 변환하여 추가
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

// 문자 배열에 대한 조합을 생성하는 함수
std::vector<std::string> combinations(const std::vector<char>& arr, int n, int k) {
    std::vector<std::string> result;  // 결과를 저장할 벡터
    std::vector<char> data(k);  // 하나의 조합을 저장할 배열

    // 재귀적으로 조합을 생성
    generate_combinations(arr, n, k, 0, data, 0, result);

    return result;  // 결과 조합 배열 반환
}

// int main() {
//     std::vector<char> arr = {'a', 'b', 'c', 'd', 'e'};  // 문자 배열
//     int n = 5, k = 3;  // 배열 크기와 선택할 개수

//     // 조합 계산 함수 호출
//     std::vector<std::string> result = combinations(arr, n, k);

//     // 결과 출력
//     std::cout << "Combinations of " << n << " characters taken " << k << " at a time:\n";
//     for (const auto& combination : result) {
//         std::cout << "{ ";
//         for (char ch : combination) {
//             std::cout << ch << " ";  // 각 조합의 문자 출력
//         }
//         std::cout << "}\n";
//     }

//     return 0;
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 재귀적으로 문자열 배열에 대한 조합을 생성하는 함수
void _generate_combinations(const std::vector<std::string>& arr, int n, int k, int index, std::vector<std::string>& data, int i, std::vector<std::vector<std::string>>& result) {
    // k개의 요소가 다 채워졌다면 결과 배열에 추가
    if (index == k) {
        result.push_back(data);  // 현재 조합을 결과에 추가
        return;
    }

    // 배열의 끝에 도달하면 종료
    if (i >= n) return;

    // 현재 인덱스에 값을 추가하고 다음 재귀 호출
    data[index] = arr[i];
    _generate_combinations(arr, n, k, index + 1, data, i + 1, result);

    // 현재 인덱스를 선택하지 않고 다음 재귀 호출
    _generate_combinations(arr, n, k, index, data, i + 1, result);
}

// 문자열 배열에 대한 조합을 생성하는 함수
std::vector<std::vector<std::string>> _combinations(const std::vector<std::string>& arr, int n, int k) {
    std::vector<std::vector<std::string>> result;  // 결과를 저장할 벡터
    std::vector<std::string> data(k);  // 하나의 조합을 저장할 배열

    // 재귀적으로 조합을 생성
    _generate_combinations(arr, n, k, 0, data, 0, result);

    return result;  // 결과 조합 배열 반환
}

// int main() {
//     std::vector<std::string> arr = {"apple", "banana", "cherry", "date", "elderberry"};  // 문자열 배열
//     int n = 5, k = 3;  // 배열 크기와 선택할 개수

//     // 조합 계산 함수 호출
//     std::vector<std::vector<std::string>> result = _combinations(arr, n, k);

//     // 결과 출력
//     std::cout << "Combinations of " << n << " strings taken " << k << " at a time:\n";
//     for (const auto& combination : result) {
//         std::cout << "{ ";
//         for (const auto& str : combination) {
//             std::cout << "\"" << str << "\" ";  // 각 조합의 문자열 출력
//         }
//         std::cout << "}\n";
//     }

//     return 0;
// }



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 중복조합
// 재귀적으로 중복 조합을 생성하는 함수
void generate_combinations_(const std::vector<char>& arr, int n, int k, int index, std::vector<char>& data, int i, std::vector<std::string>& result) {
    // k개의 요소가 다 채워졌다면 결과 배열에 추가
    if (index == k) {
        result.push_back(std::string(data.begin(), data.end()));  // 현재 데이터 배열을 문자열로 변환하여 추가
        return;
    }

    // 배열의 인덱스 i부터 시작하여 중복 허용하여 재귀 호출
    for (int j = i; j < n; j++) {
        data[index] = arr[j];  // 현재 인덱스에 값을 추가하고
        generate_combinations_(arr, n, k, index + 1, data, j, result);  // 재귀 호출
    }
}

// 중복 조합을 계산하는 함수
std::vector<std::string> combinations_with_repetition(const std::vector<char>& arr, int n, int k) {
    std::vector<std::string> result;  // 결과를 저장할 벡터
    std::vector<char> data(k);  // 하나의 조합을 저장할 배열

    // 재귀적으로 중복 조합을 생성
    generate_combinations_(arr, n, k, 0, data, 0, result);

    return result;  // 결과 조합 배열 반환
}

// int main() {
//     std::vector<char> arr = {'a', 'b', 'c'};  // 입력 문자 배열
//     int n = 3, k = 2;  // 배열 크기와 선택할 개수

//     // 중복 조합 계산 함수 호출
//     std::vector<std::string> result = combinations_with_repetition(arr, n, k);

//     // 결과 출력
//     std::cout << "Combinations with repetition of " << n << " characters taken " << k << " at a time:\n";
//     for (const auto& combination : result) {
//         std::cout << "{ ";
//         for (char c : combination) {
//             std::cout << c << " ";  // 각 조합의 문자 출력
//         }
//         std::cout << "}\n";
//     }

//     return 0;
// }

// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 중복 조합을 재귀적으로 생성하는 함수
void generate_combinations__(const std::vector<std::string>& arr, int n, int k, int index, std::vector<std::string>& data, int i, std::vector<std::vector<std::string>>& result) {
    // k개의 요소가 다 채워졌다면 결과 배열에 추가
    if (index == k) {
        result.push_back(data);  // 현재 데이터를 결과 배열에 추가
        return;
    }

    // 배열의 인덱스 i부터 시작하여 중복 허용하여 재귀 호출
    for (int j = i; j < n; j++) {
        data[index] = arr[j];  // 현재 인덱스에 값을 추가하고
        generate_combinations__(arr, n, k, index + 1, data, j, result);  // 재귀 호출
    }
}

// 중복 조합을 계산하는 함수
std::vector<std::vector<std::string>> combinations_with_repetition_(const std::vector<std::string>& arr, int n, int k) {
    std::vector<std::vector<std::string>> result;  // 결과를 저장할 벡터
    std::vector<std::string> data(k);  // 하나의 조합을 저장할 배열

    // 재귀적으로 중복 조합을 생성
    generate_combinations__(arr, n, k, 0, data, 0, result);

    return result;  // 결과 조합 배열 반환
}

int main() {
    std::vector<std::string> arr = {"apple", "banana", "cherry"};  // 입력 문자열 배열
    int n = 3, k = 2;  // 배열 크기와 선택할 개수

    // 중복 조합 계산 함수 호출
    std::vector<std::vector<std::string>> result = combinations_with_repetition_(arr, n, k);

    // 결과 출력
    std::cout << "Combinations with repetition of " << n << " strings taken " << k << " at a time:\n";
    for (const auto& combination : result) {
        std::cout << "{ ";
        for (const auto& str : combination) {
            std::cout << "\"" << str << "\" ";  // 각 조합의 문자열 출력
        }
        std::cout << "}\n";
    }

    return 0;
}