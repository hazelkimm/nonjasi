/*
모든 부분 집합 구하기
-all_subsets1: 공집합 포함
-all_subsets2: 공집합 불포함
*/

#include <stdio.h>
#include <stdlib.h>

void print_subset(int *subset, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", subset[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 모든 부분 집합을 출력하는 함수
void all_subsets1(int *lst, int lst_size, int *subset, int subset_size, int index) {
    // 종료 조건: 현재 인덱스가 리스트 크기와 같으면 부분 집합을 출력
    // index가 lst_size에 도달하면, 모든 원소를 처리한 것이므로 부분 집합을 출력
    if (index == lst_size) {
        // subset 배열을 출력하는 함수 호출
        // subset과 subset_size를 이용하여 현재까지 구한 부분 집합을 출력
        print_subset(subset, subset_size);
        return;  // 재귀 종료
    }
    
    // 현재 원소를 포함하지 않는 부분 집합을 찾기 위한 재귀 호출
    // 'index' 위치의 원소를 제외하고 나머지 부분 집합을 찾음
    all_subsets1(lst, lst_size, subset, subset_size, index + 1);
    
    // 현재 원소를 포함하는 부분 집합을 찾기 위한 재귀 호출
    // 'index' 위치의 원소를 포함시켜 부분 집합을 구성하고 다시 재귀 호출
    subset[subset_size] = lst[index];  // 현재 원소를 subset에 추가
    all_subsets1(lst, lst_size, subset, subset_size + 1, index + 1);  // 새로운 subset_size와 함께 재귀 호출
}

// int main() {
//     int lst[] = {1, 2, 3};
//     int lst_size = sizeof(lst) / sizeof(lst[0]);
//     int *subset = (int *)malloc(lst_size * sizeof(int));
    
//     all_subsets1(lst, lst_size, subset, 0, 0);
    
//     free(subset);
//     return 0;
// }


//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 모든 부분 집합을 출력하는 재귀 함수
void all_subsets2(int *lst, int lst_size, int *subset, int subset_size, int index) {
    // 종료 조건: 현재 인덱스가 lst_size와 같으면 더 이상 원소가 없으므로 부분 집합을 출력
    if (index == lst_size) {
        // 부분 집합의 크기가 0보다 클 경우에만 출력 (빈 집합은 제외)
        if (subset_size > 0) {
            print_subset(subset, subset_size);  // 현재 부분 집합을 출력
        }
        return;  // 재귀 종료
    }
    
    // 현재 원소를 포함하지 않는 경우: 재귀 호출하여, 'index' 위치의 원소를 제외한 부분 집합을 구함
    all_subsets2(lst, lst_size, subset, subset_size, index + 1);
    
    // 현재 원소를 포함하는 경우: 현재 원소를 subset에 추가하고, 재귀 호출하여 포함한 부분 집합을 구함
    subset[subset_size] = lst[index];  // 현재 원소를 subset에 추가
    all_subsets2(lst, lst_size, subset, subset_size + 1, index + 1);  // subset_size를 증가시켜 원소를 추가한 후 재귀 호출
}

// int main() {
//     int lst[] = {1, 2, 3};  // 부분 집합을 구할 원본 리스트
//     int lst_size = sizeof(lst) / sizeof(lst[0]);  // 리스트의 크기 계산 (원소 개수)
    
//     // 부분 집합을 저장할 메모리 할당
//     int *subset = (int *)malloc(lst_size * sizeof(int));  // 최대 크기는 리스트의 크기만큼
    
//     // 모든 부분 집합을 구하여 출력
//     all_subsets2(lst, lst_size, subset, 0, 0);  // 부분 집합을 구하는 함수 호출
    
//     // 할당된 메모리 해제
//     free(subset);  // 동적으로 할당한 메모리 해제
    
//     return 0;  // 프로그램 종료
// }