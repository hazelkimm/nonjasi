#include <stdio.h>
#include <stdlib.h>

// 순열을 생성하고 출력하는 재귀 함수
void generate_permutations(int *arr, int *current_permutation, int *used, int arr_length, int perm_length, int depth) {
    // 현재 깊이가 순열의 길이와 같으면 현재 순열을 출력
    if (depth == perm_length) {
        for (int i = 0; i < perm_length; i++) {
            printf("%d ", current_permutation[i]);
        }
        printf("\n");
        return;
    }
    // 배열의 모든 원소에 대해 순열을 생성
    for (int i = 0; i < arr_length; i++) {
        // 원소가 사용되지 않았으면
        if (!used[i]) {
            used[i] = 1; // 원소를 사용한다고 표시
            current_permutation[depth] = arr[i]; // 현재 깊이의 순열에 원소 추가
            // 다음 깊이로 재귀 호출
            generate_permutations(arr, current_permutation, used, arr_length, perm_length, depth + 1);
            used[i] = 0; // 원소 사용 취소
        }
    }
}

// 주어진 배열의 길이 perm_length인 순열을 생성하고 출력하는 함수
void permutations(int *arr, int arr_length, int perm_length) {
    // 현재 순열을 저장할 배열과 원소 사용 여부를 표시할 배열
    int *current_permutation = (int *)malloc(perm_length * sizeof(int));
    int *used = (int *)calloc(arr_length, sizeof(int)); // 0으로 초기화된 메모리
    
    if (current_permutation == NULL || used == NULL) {
        printf("메모리 할당 실패.\n");
        return;
    }
    
    // 순열 생성 함수 호출
    generate_permutations(arr, current_permutation, used, arr_length, perm_length, 0);
    
    // 동적 메모리 해제
    free(current_permutation);
    free(used);
}

// int main() {
//     int arr[] = {1, 2, 3}; // 입력 배열
//     int arr_length = sizeof(arr) / sizeof(arr[0]); // 배열의 길이
//     int perm_length = 3; // 생성할 순열의 길이
    
//     // 순열 생성 함수 호출
//     permutations(arr, arr_length, perm_length);
    
//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 순열을 생성하고 반환하는 재귀 함수
void generate_permutations_(int *arr, int *current_permutation, int *used, int arr_length, int perm_length, int depth, int **result, int *result_index) {
    // 현재 깊이가 순열의 길이와 같으면 현재 순열을 결과 배열에 추가
    if (depth == perm_length) {
        for (int i = 0; i < perm_length; i++) {
            result[*result_index][i] = current_permutation[i]; // 현재 순열을 결과 배열에 복사
        }
        (*result_index)++; // 결과 배열에 새로운 순열을 추가
        return;
    }

    // 배열의 모든 원소에 대해 순열을 생성
    for (int i = 0; i < arr_length; i++) {
        // 원소가 사용되지 않았으면
        if (!used[i]) {
            used[i] = 1; // 원소를 사용한다고 표시
            current_permutation[depth] = arr[i]; // 현재 깊이의 순열에 원소 추가
            // 다음 깊이로 재귀 호출
            generate_permutations_(arr, current_permutation, used, arr_length, perm_length, depth + 1, result, result_index);
            used[i] = 0; // 원소 사용 취소
        }
    }
}

// 주어진 배열의 길이 perm_length인 순열을 생성하고 반환하는 함수
int** permutations_(int *arr, int arr_length, int perm_length, int *result_count) {
    // 순열을 저장할 배열과 원소 사용 여부를 표시할 배열
    int *current_permutation = (int *)malloc(perm_length * sizeof(int));
    int *used = (int *)calloc(arr_length, sizeof(int)); // 0으로 초기화된 메모리
    int **result = (int **)malloc(100 * sizeof(int *)); // 결과 배열 (최대 100개의 순열을 저장한다고 가정)
    int result_index = 0; // 결과 배열의 인덱스

    if (current_permutation == NULL || used == NULL || result == NULL) {
        printf("메모리 할당 실패.\n");
        return NULL;
    }

    // 순열 생성 함수 호출
    generate_permutations_(arr, current_permutation, used, arr_length, perm_length, 0, result, &result_index);

    *result_count = result_index; // 생성된 순열의 개수
    return result; // 결과 배열 반환
}

// 순열 배열을 출력하는 함수
void print_permutations(int **result, int result_count, int perm_length) {
    for (int i = 0; i < result_count; i++) {
        for (int j = 0; j < perm_length; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

// int main() {
//     int arr[] = {1, 2, 3}; // 입력 배열
//     int arr_length = sizeof(arr) / sizeof(arr[0]); // 배열의 길이
//     int perm_length = 3; // 생성할 순열의 길이
//     int result_count = 0;

//     // 순열 생성 함수 호출
//     int **result = permutations_(arr, arr_length, perm_length, &result_count);

//     if (result != NULL) {
//         // 순열 출력
//         print_permutations(result, result_count, perm_length);

//         // 동적 메모리 해제
//         for (int i = 0; i < result_count; i++) {
//             free(result[i]); // 각 순열에 대한 메모리 해제
//         }
//         free(result); // 결과 배열의 메모리 해제
//     }

//     return 0;
// }