#include <iostream>
#include <vector>

// 순열을 생성하고 출력하는 재귀 함수
void generate_permutations(const std::vector<int>& arr, std::vector<int>& current_permutation, std::vector<bool>& used, int perm_length, int depth) {
    // 현재 깊이가 순열의 길이와 같으면 현재 순열을 출력
    if (depth == perm_length) {
        for (int i = 0; i < perm_length; i++) {
            std::cout << current_permutation[i] << " ";
        }
        std::cout << std::endl;
        return;
    }
    
    // 배열의 모든 원소에 대해 순열을 생성
    for (int i = 0; i < arr.size(); i++) {
        // 원소가 사용되지 않았으면
        if (!used[i]) {
            used[i] = true; // 원소를 사용한다고 표시
            current_permutation[depth] = arr[i]; // 현재 깊이의 순열에 원소 추가
            // 다음 깊이로 재귀 호출
            generate_permutations(arr, current_permutation, used, perm_length, depth + 1);
            used[i] = false; // 원소 사용 취소
        }
    }
}

// 주어진 배열의 길이 perm_length인 순열을 생성하고 출력하는 함수
void permutations(const std::vector<int>& arr, int perm_length) {
    // 현재 순열을 저장할 배열과 원소 사용 여부를 표시할 배열
    std::vector<int> current_permutation(perm_length);
    std::vector<bool> used(arr.size(), false); // false로 초기화된 벡터
    
    // 순열 생성 함수 호출
    generate_permutations(arr, current_permutation, used, perm_length, 0);
}

// int main() {
//     std::vector<int> arr = {1, 2, 3}; // 입력 배열
//     int perm_length = 3; // 생성할 순열의 길이
    
//     // 순열 생성 함수 호출
//     permutations(arr, perm_length);
    
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 순열을 생성하고 반환하는 재귀 함수
void generate_permutations_(const std::vector<int>& arr, std::vector<int>& current_permutation, std::vector<bool>& used, int perm_length, int depth, std::vector<std::vector<int>>& result) {
    // 현재 깊이가 순열의 길이와 같으면 현재 순열을 결과 배열에 추가
    if (depth == perm_length) {
        result.push_back(current_permutation); // 현재 순열을 결과 배열에 추가
        return;
    }

    // 배열의 모든 원소에 대해 순열을 생성
    for (int i = 0; i < arr.size(); i++) {
        // 원소가 사용되지 않았으면
        if (!used[i]) {
            used[i] = true; // 원소를 사용한다고 표시
            current_permutation[depth] = arr[i]; // 현재 깊이의 순열에 원소 추가
            // 다음 깊이로 재귀 호출
            generate_permutations_(arr, current_permutation, used, perm_length, depth + 1, result);
            used[i] = false; // 원소 사용 취소
        }
    }
}

// 주어진 배열의 길이 perm_length인 순열을 생성하고 반환하는 함수
std::vector<std::vector<int>> permutations_(const std::vector<int>& arr, int perm_length) {
    // 순열을 저장할 배열과 원소 사용 여부를 표시할 배열
    std::vector<int> current_permutation(perm_length);
    std::vector<bool> used(arr.size(), false); // false로 초기화된 벡터
    std::vector<std::vector<int>> result; // 결과 배열 (동적으로 크기가 변할 수 있는 벡터)

    // 순열 생성 함수 호출
    generate_permutations_(arr, current_permutation, used, perm_length, 0, result);

    return result; // 결과 배열 반환
}

// 순열 배열을 출력하는 함수
void print_permutations(const std::vector<std::vector<int>>& result) {
    for (const auto& perm : result) {
        for (int num : perm) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

// int main() {
//     std::vector<int> arr = {1, 2, 3}; // 입력 배열
//     int perm_length = 3; // 생성할 순열의 길이

//     // 순열 생성 함수 호출
//     std::vector<std::vector<int>> result = permutations_(arr, perm_length);

//     // 순열 출력
//     print_permutations(result);

//     return 0;
// }