#include <stdio.h>
#include <stdlib.h>


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 조합
// 재귀적으로 조합을 생성하는 함수
void generate_combinations(int *arr, int n, int k, int index, int *data, int i, int ***result, int *count) {
    // k개의 요소가 다 채워졌다면 결과 배열에 추가
    if (index == k) {
        (*result)[*count] = (int *)malloc(k * sizeof(int));  // 새로운 배열 할당
        for (int j = 0; j < k; j++) {
            (*result)[*count][j] = data[j];  // 현재 데이터 배열을 결과 배열에 복사
        }
        (*count)++;  // 결과 개수 증가
        return;
    }
    
    // 배열의 끝에 도달하면 종료
    if (i >= n) return;

    // 현재 인덱스에 값을 추가하고 다음 재귀 호출
    data[index] = arr[i];
    generate_combinations(arr, n, k, index + 1, data, i + 1, result, count);
    
    // 현재 인덱스를 선택하지 않고 다음 재귀 호출
    generate_combinations(arr, n, k, index, data, i + 1, result, count);
}

// 조합을 생성하는 함수
int **combinations(int *arr, int n, int k, int *totalCombinations) {
    // 최대 조합 수를 계산: C(n, k)
    int maxCombinations = 1;
    for (int i = 0; i < k; i++) maxCombinations *= (n - i) / (i + 1); // 조합 개수

    // 동적 메모리 할당: 최대 조합 수 만큼 2차원 배열을 준비
    int **result = (int **)malloc(maxCombinations * sizeof(int *));
    int *data = (int *)malloc(k * sizeof(int));  // 하나의 조합을 저장할 배열
    *totalCombinations = 0;  // 총 조합 개수를 0으로 초기화

    // 재귀적으로 조합을 생성
    generate_combinations(arr, n, k, 0, data, 0, &result, totalCombinations);
    free(data);  // 임시 배열 메모리 해제

    return result;  // 결과 조합 배열 반환
}

// int main() {
//     int arr[] = {1, 2, 3, 4, 5};  // 입력 배열
//     int n = 5, k = 3;  // 배열 크기와 선택할 개수
//     int totalCombinations;
    
//     // 조합 계산 함수 호출
//     int **result = combinations(arr, n, k, &totalCombinations);

//     // 결과 출력
//     printf("Combinations of %d elements taken %d at a time:\n", n, k);
//     for (int i = 0; i < totalCombinations; i++) {
//         printf("{ ");
//         for (int j = 0; j < k; j++) {
//             printf("%d ", result[i][j]);  // 각 조합의 요소 출력
//         }
//         printf("}\n");
//         free(result[i]);  // 각 조합에 할당된 메모리 해제
//     }
//     free(result);  // 2차원 배열의 메모리 해제

//     return 0;
// }



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 중복조합
#include <stdio.h>
#include <stdlib.h>

// 중복 조합을 재귀적으로 생성하는 함수
void generate_combinations_(int *arr, int n, int k, int index, int *data, int i, int ***result, int *count) {
    // k개의 요소가 다 채워졌다면 결과 배열에 추가
    if (index == k) {
        (*result)[*count] = (int *)malloc(k * sizeof(int));  // 새로운 배열 할당
        for (int j = 0; j < k; j++) {
            (*result)[*count][j] = data[j];  // 현재 데이터 배열을 결과 배열에 복사
        }
        (*count)++;  // 결과 개수 증가
        return;
    }

    // 배열의 인덱스 i부터 시작하여 중복 허용하여 재귀 호출
    for (int j = i; j < n; j++) {
        data[index] = arr[j];  // 현재 인덱스에 값을 추가하고
        generate_combinations_(arr, n, k, index + 1, data, j, result, count);  // 재귀 호출
    }
}

// 중복 조합을 계산하는 함수
int **combinations_with_repetition(int *arr, int n, int k, int *totalCombinations) {
    // 최대 조합 수를 계산: C(n+k-1, k)
    int maxCombinations = 1;
    for (int i = 0; i < k; i++) {
        maxCombinations *= (n + k - 1 - i);
        maxCombinations /= (i + 1);  // 중복 조합 공식
    }

    // 동적 메모리 할당: 최대 조합 수 만큼 2차원 배열을 준비
    int **result = (int **)malloc(maxCombinations * sizeof(int *));
    int *data = (int *)malloc(k * sizeof(int));  // 하나의 조합을 저장할 배열
    *totalCombinations = 0;  // 총 조합 개수를 0으로 초기화

    // 재귀적으로 중복 조합을 생성
    generate_combinations_(arr, n, k, 0, data, 0, &result, totalCombinations);
    free(data);  // 임시 배열 메모리 해제

    return result;  // 결과 조합 배열 반환
}

// int main() {
//     int arr[] = {1, 2, 3};  // 입력 배열
//     int n = 3, k = 2;  // 배열 크기와 선택할 개수
//     int totalCombinations;

//     // 중복 조합 계산 함수 호출
//     int **result = combinations_with_repetition(arr, n, k, &totalCombinations);

//     // 결과 출력
//     printf("Combinations with repetition of %d elements taken %d at a time:\n", n, k);
//     for (int i = 0; i < totalCombinations; i++) {
//         printf("{ ");
//         for (int j = 0; j < k; j++) {
//             printf("%d ", result[i][j]);  // 각 조합의 요소 출력
//         }
//         printf("}\n");
//         free(result[i]);  // 각 조합에 할당된 메모리 해제
//     }
//     free(result);  // 2차원 배열의 메모리 해제

//     return 0;
// }
