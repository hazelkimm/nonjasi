/*
1. 배열 초기화 및 출력: void initializeArray, void printArray
2. 배열의 최대값, 최소값 찾기: int findMax, int findMin
3. 배열의 합과 평균 계산: int calculateSum, double calculateAverage
4. 배열의 정렬: void bubbleSort
5. 배열에서 특정 값 찾기: int findValueIndex
6. 2차원 배열 초기화 및 출력: void initialize2DArray, void print2DArray
7. 배열의 회전: void rotateRight
8. 중복 제거: int removeDuplicates
*/

#include <stdio.h>

void initializeArray(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/////////////////////////////////////////////////////////////////////////////////////
int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/////////////////////////////////////////////////////////////////////////////////////
int findMin(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

/////////////////////////////////////////////////////////////////////////////////////
int calculateSum(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

/////////////////////////////////////////////////////////////////////////////////////
double calculateAverage(int arr[], int size) {
    int sum = calculateSum(arr, size);
    return (double)sum / size;
}

/////////////////////////////////////////////////////////////////////////////////////
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
int findValueIndex(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return i; // 값의 인덱스 반환
        }
    }
    return -1; // 값이 없을 경우 -1 반환
}

/////////////////////////////////////////////////////////////////////////////////////
void initialize2DArray(int rows, int cols, int arr[rows][cols], int value) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = value;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void print2DArray(int rows, int cols, int arr[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void rotateRight(int arr[], int size, int k) {
    k = k % size; // 회전 수가 배열 크기보다 클 경우 처리
    int temp[k];
    
    for (int i = 0; i < k; i++) {
        temp[i] = arr[size - k + i];
    }
    
    for (int i = size - 1; i >= k; i--) {
        arr[i] = arr[i - k];
    }
    
    for (int i = 0; i < k; i++) {
        arr[i] = temp[i];
    }
}

/////////////////////////////////////////////////////////////////////////////////////
int removeDuplicates(int arr[], int size) {
    int temp[size];
    int newSize = 0;

    for (int i = 0; i < size; i++) {
        int isDuplicate = 0;
        for (int j = 0; j < newSize; j++) {
            if (arr[i] == temp[j]) {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            temp[newSize++] = arr[i];
        }
    }

    for (int i = 0; i < newSize; i++) {
        arr[i] = temp[i];
    }
    return newSize;
}