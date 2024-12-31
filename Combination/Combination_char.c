#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 조합
// 재귀적으로 문자 배열에 대한 조합을 생성하는 함수
void generate_combinations(char *arr, int n, int k, int index, char *data, int i, char **result, int *count) {
    // k개의 요소가 다 채워졌다면 결과 배열에 추가
    if (index == k) {
        // 결과 배열에 조합을 추가
        result[*count] = (char *)malloc((k + 1) * sizeof(char));  // 새로운 배열 할당 (k+1은 NULL 종료 문자 공간)
        for (int j = 0; j < k; j++) {
            result[*count][j] = data[j];  // 현재 조합을 결과 배열에 복사
        }
        result[*count][k] = '\0';  // 문자열 종료를 위해 NULL을 추가
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

// 문자 배열에 대한 조합을 생성하는 함수
char **combinations(char *arr, int n, int k, int *totalCombinations) {
    // 최대 조합 수를 계산: C(n, k)
    int maxCombinations = 1;
    for (int i = 0; i < k; i++) maxCombinations *= (n - i) / (i + 1); // 조합 개수

    // 동적 메모리 할당: 최대 조합 수 만큼 2차원 배열을 준비
    char **result = (char **)malloc(maxCombinations * sizeof(char *));
    char *data = (char *)malloc(k * sizeof(char));  // 하나의 조합을 저장할 배열
    *totalCombinations = 0;  // 총 조합 개수를 0으로 초기화

    // 재귀적으로 조합을 생성
    generate_combinations(arr, n, k, 0, data, 0, result, totalCombinations);
    free(data);  // 임시 배열 메모리 해제

    return result;  // 결과 조합 배열 반환
}

// int main() {
//     char arr[] = {'a', 'b', 'c', 'd', 'e'};  // 문자 배열
//     int n = 5, k = 3;  // 배열 크기와 선택할 개수
//     int totalCombinations;

//     // 조합 계산 함수 호출
//     char **result = combinations(arr, n, k, &totalCombinations);

//     // 결과 출력
//     printf("Combinations of %d characters taken %d at a time:\n", n, k);
//     for (int i = 0; i < totalCombinations; i++) {
//         printf("{ ");
//         for (int j = 0; j < k; j++) {
//             printf("%c ", result[i][j]);  // 각 조합의 문자 출력
//         }
//         printf("}\n");
//         free(result[i]);  // 각 조합에 할당된 메모리 해제
//     }
//     free(result);  // 2차원 배열의 메모리 해제

//     return 0;
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 재귀적으로 문자열 배열에 대한 조합을 생성하는 함수
void _generate_combinations(char **arr, int n, int k, int index, char **data, int i, char ***result, int *count) {
    // k개의 요소가 다 채워졌다면 결과 배열에 추가
    if (index == k) {
        result[*count] = (char **)malloc(k * sizeof(char *));  // 새로운 배열 할당
        for (int j = 0; j < k; j++) {
            result[*count][j] = (char *)malloc((strlen(data[j]) + 1) * sizeof(char));  // 각 문자열의 길이에 맞춰 메모리 할당
            strcpy(result[*count][j], data[j]);  // 문자열을 복사
        }
        (*count)++;  // 결과 개수 증가
        return;
    }

    // 배열의 끝에 도달하면 종료
    if (i >= n) return;

    // 현재 인덱스에 값을 추가하고 다음 재귀 호출
    data[index] = arr[i];
    _generate_combinations(arr, n, k, index + 1, data, i + 1, result, count);

    // 현재 인덱스를 선택하지 않고 다음 재귀 호출
    _generate_combinations(arr, n, k, index, data, i + 1, result, count);
}

// 문자열 배열에 대한 조합을 생성하는 함수
char ***combinations_(char **arr, int n, int k, int *totalCombinations) {
    // 최대 조합 수를 계산: C(n, k)
    int maxCombinations = 1;
    for (int i = 0; i < k; i++) {
        maxCombinations *= (n - i) / (i + 1);  // 조합 개수 계산
    }

    // 동적 메모리 할당: 최대 조합 수 만큼 3차원 배열을 준비
    char ***result = (char ***)malloc(maxCombinations * sizeof(char **));
    char **data = (char **)malloc(k * sizeof(char *));  // 하나의 조합을 저장할 배열
    *totalCombinations = 0;  // 총 조합 개수를 0으로 초기화

    // 재귀적으로 조합을 생성
    _generate_combinations(arr, n, k, 0, data, 0, result, totalCombinations);
    free(data);  // 임시 배열 메모리 해제

    return result;  // 결과 조합 배열 반환
}

// int main() {
//     char *arr[] = {"apple", "banana", "cherry", "date", "elderberry"};  // 문자열 배열
//     int n = 5, k = 3;  // 배열 크기와 선택할 개수
//     int totalCombinations;

//     // 조합 계산 함수 호출
//     char ***result = combinations_(arr, n, k, &totalCombinations);

//     // 결과 출력
//     printf("Combinations of %d strings taken %d at a time:\n", n, k);
//     for (int i = 0; i < totalCombinations; i++) {
//         printf("{ ");
//         for (int j = 0; j < k; j++) {
//             printf("\"%s\" ", result[i][j]);  // 각 조합의 문자열 출력
//         }
//         printf("}\n");
//         // 각 조합에 할당된 메모리 해제
//         for (int j = 0; j < k; j++) {
//             free(result[i][j]);
//         }
//         free(result[i]);
//     }
//     free(result);  // 3차원 배열의 메모리 해제

//     return 0;
// }



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 중복조합
// 중복 조합을 재귀적으로 생성하는 함수
void generate_combinations_(char *arr, int n, int k, int index, char *data, int i, char **result, int *count) {
    // k개의 요소가 다 채워졌다면 결과 배열에 추가
    if (index == k) {
        result[*count] = (char *)malloc((k + 1) * sizeof(char));  // 새로운 배열 할당 (k+1은 NULL 종료 문자 공간)
        for (int j = 0; j < k; j++) {
            result[*count][j] = data[j];  // 현재 데이터 배열을 결과 배열에 복사
        }
        result[*count][k] = '\0';  // 문자열 종료를 위해 NULL을 추가
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
char **combinations_with_repetition(char *arr, int n, int k, int *totalCombinations) {
    // 최대 조합 수를 계산: C(n+k-1, k)
    int maxCombinations = 1;
    for (int i = 0; i < k; i++) {
        maxCombinations *= (n + k - 1 - i);
        maxCombinations /= (i + 1);  // 중복 조합 공식
    }

    // 동적 메모리 할당: 최대 조합 수 만큼 2차원 배열을 준비
    char **result = (char **)malloc(maxCombinations * sizeof(char *));
    char *data = (char *)malloc(k * sizeof(char));  // 하나의 조합을 저장할 배열
    *totalCombinations = 0;  // 총 조합 개수를 0으로 초기화

    // 재귀적으로 중복 조합을 생성
    generate_combinations_(arr, n, k, 0, data, 0, result, totalCombinations);
    free(data);  // 임시 배열 메모리 해제

    return result;  // 결과 조합 배열 반환
}

// int main() {
//     char arr[] = {'a', 'b', 'c'};  // 입력 문자 배열
//     int n = 3, k = 2;  // 배열 크기와 선택할 개수
//     int totalCombinations;

//     // 중복 조합 계산 함수 호출
//     char **result = combinations_with_repetition(arr, n, k, &totalCombinations);

//     // 결과 출력
//     printf("Combinations with repetition of %d characters taken %d at a time:\n", n, k);
//     for (int i = 0; i < totalCombinations; i++) {
//         printf("{ ");
//         for (int j = 0; j < k; j++) {
//             printf("%c ", result[i][j]);  // 각 조합의 문자 출력
//         }
//         printf("}\n");
//         free(result[i]);  // 각 조합에 할당된 메모리 해제
//     }
//     free(result);  // 2차원 배열의 메모리 해제

//     return 0;
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 중복 조합을 재귀적으로 생성하는 함수
void generate_combinations__(char **arr, int n, int k, int index, char **data, int i, char ***result, int *count) {
    // k개의 요소가 다 채워졌다면 결과 배열에 추가
    if (index == k) {
        result[*count] = (char **)malloc(k * sizeof(char *));  // 각 조합을 저장할 배열
        for (int j = 0; j < k; j++) {
            result[*count][j] = (char *)malloc((strlen(data[j]) + 1) * sizeof(char));  // 문자열의 길이에 맞춰 메모리 할당
            strcpy(result[*count][j], data[j]);  // 문자열 복사
        }
        (*count)++;  // 결과 개수 증가
        return;
    }

    // 배열의 인덱스 i부터 시작하여 중복 허용하여 재귀 호출
    for (int j = i; j < n; j++) {
        data[index] = arr[j];  // 현재 인덱스에 값을 추가하고
        generate_combinations__(arr, n, k, index + 1, data, j, result, count);  // 재귀 호출
    }
}

// 중복 조합을 계산하는 함수
char ***combinations_with_repetition_(char **arr, int n, int k, int *totalCombinations) {
    // 최대 조합 수를 계산: C(n+k-1, k)
    int maxCombinations = 1;
    for (int i = 0; i < k; i++) {
        maxCombinations *= (n + k - 1 - i);
        maxCombinations /= (i + 1);  // 중복 조합 공식
    }

    // 동적 메모리 할당: 최대 조합 수 만큼 2차원 배열을 준비
    char ***result = (char ***)malloc(maxCombinations * sizeof(char **));
    char **data = (char **)malloc(k * sizeof(char *));  // 하나의 조합을 저장할 배열
    *totalCombinations = 0;  // 총 조합 개수를 0으로 초기화

    // 재귀적으로 중복 조합을 생성
    generate_combinations__(arr, n, k, 0, data, 0, result, totalCombinations);
    free(data);  // 임시 배열 메모리 해제

    return result;  // 결과 조합 배열 반환
}

// int main() {
//     char *arr[] = {"apple", "banana", "cherry"};  // 입력 문자열 배열
//     int n = 3, k = 2;  // 배열 크기와 선택할 개수
//     int totalCombinations;

//     // 중복 조합 계산 함수 호출
//     char ***result = combinations_with_repetition_(arr, n, k, &totalCombinations);

//     // 결과 출력
//     printf("Combinations with repetition of %d strings taken %d at a time:\n", n, k);
//     for (int i = 0; i < totalCombinations; i++) {
//         printf("{ ");
//         for (int j = 0; j < k; j++) {
//             printf("\"%s\" ", result[i][j]);  // 각 조합의 문자열 출력
//         }
//         printf("}\n");
//         // 각 조합에 할당된 메모리 해제
//         for (int j = 0; j < k; j++) {
//             free(result[i][j]);
//         }
//         free(result[i]);
//     }
//     free(result);  // 3차원 배열의 메모리 해제

//     return 0;
// }