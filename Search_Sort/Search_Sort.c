/*
Search
- Linear Search  : while loop / sentinel / for loop
- Binary Search  : while loop / recursion

Sort
- Bubble Sort    : standard / optimized
- Selection Sort
- Insertion Sort
- Merge Sort     (<- merge_sort_help <- merge)
- Quick Sort     (<- partition)
*/

#include <stdio.h>
#include <stdbool.h>

///////////////////////////////////////
//////////// Linear Search ////////////
///////////////////////////////////////

int linear_search(int L[], int size, int target) {
    for (int i = 0; i < size; ++i) {
        if (L[i] == target) return i;
    }
    return -1;
}

int linear_search_sentinel(int L[], int size, int target) {
    L[size] = target;
    int i = 0;
    while (L[i] != target) {
        ++i;
    }
    return (i == size) ? -1 : i;
}

///////////////////////////////////////
//////////// Binary Search ////////////
///////////////////////////////////////

int binary_search(int L[], int size, int target) {
    int start = 0, end = size - 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (L[mid] == target) return mid;
        else if (L[mid] < target) start = mid + 1;
        else end = mid - 1;
    }
    return -1;
}

///////////////////////////////////////
//////////// Bubble Sort //////////////
///////////////////////////////////////

void bubble_sort(int L[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            if (L[j] > L[j + 1]) {
                int temp = L[j];
                L[j] = L[j + 1];
                L[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_optimized(int L[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < size - 1 - i; ++j) {
            if (L[j] > L[j + 1]) {
                int temp = L[j];
                L[j] = L[j + 1];
                L[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

///////////////////////////////////////
/////////// Selection Sort ////////////
///////////////////////////////////////

void selection_sort(int L[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        int smallest = i;
        for (int j = i + 1; j < size; ++j) {
            if (L[j] < L[smallest]) {
                smallest = j;
            }
        }
        int temp = L[i];
        L[i] = L[smallest];
        L[smallest] = temp;
    }
}

///////////////////////////////////////
/////////// Insertion Sort ////////////
///////////////////////////////////////

void insertion_sort(int L[], int size) {
    for (int i = 1; i < size; ++i) {
        int key = L[i];
        int j = i - 1;
        while (j >= 0 && L[j] > key) {
            L[j + 1] = L[j];
            --j;
        }
        L[j + 1] = key;
    }
}

///////////////////////////////////////
//////////// Merge Sort ///////////////
///////////////////////////////////////

void merge(int L[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int sub1[n1], sub2[n2];
    for (int i = 0; i < n1; ++i) sub1[i] = L[left + i];
    for (int j = 0; j < n2; ++j) sub2[j] = L[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (sub1[i] <= sub2[j]) {
            L[k++] = sub1[i++];
        } else {
            L[k++] = sub2[j++];
        }
    }
    while (i < n1) L[k++] = sub1[i++];
    while (j < n2) L[k++] = sub2[j++];
}

void merge_sort(int L[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(L, left, mid);
        merge_sort(L, mid + 1, right);
        merge(L, left, mid, right);
    }
}

///////////////////////////////////////
//////////// Quick Sort ///////////////
///////////////////////////////////////

int partition(int L[], int low, int high) {
    int pivot = L[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (L[j] <= pivot) {
            ++i;
            int temp = L[i];
            L[i] = L[j];
            L[j] = temp;
        }
    }
    int temp = L[i + 1];
    L[i + 1] = L[high];
    L[high] = temp;
    return i + 1;
}

void quick_sort(int L[], int low, int high) {
    if (low < high) {
        int pivot_index = partition(L, low, high);
        quick_sort(L, low, pivot_index - 1);
        quick_sort(L, pivot_index + 1, high);
    }
}

///////////////////////////////////////
//////////// Test Cases ///////////////
///////////////////////////////////////

void print_array(int L[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", L[i]);
    }
    printf("\n");
}

int main() {
    int test_list[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(test_list) / sizeof(test_list[0]);

    printf("Original List: ");
    print_array(test_list, size);

    // Bubble Sort
    int bubble_sorted[size];
    for (int i = 0; i < size; ++i) bubble_sorted[i] = test_list[i];
    bubble_sort(bubble_sorted, size);
    printf("Bubble Sorted: ");
    print_array(bubble_sorted, size);

    // Optimized Bubble Sort
    int bubble_sorted_opt[size];
    for (int i = 0; i < size; ++i) bubble_sorted_opt[i] = test_list[i];
    bubble_sort_optimized(bubble_sorted_opt, size);
    printf("Optimized Bubble Sorted: ");
    print_array(bubble_sorted_opt, size);

    // Selection Sort
    int selection_sorted[size];
    for (int i = 0; i < size; ++i) selection_sorted[i] = test_list[i];
    selection_sort(selection_sorted, size);
    printf("Selection Sorted: ");
    print_array(selection_sorted, size);

    // Insertion Sort
    int insertion_sorted[size];
    for (int i = 0; i < size; ++i) insertion_sorted[i] = test_list[i];
    insertion_sort(insertion_sorted, size);
    printf("Insertion Sorted: ");
    print_array(insertion_sorted, size);

    // Merge Sort
    int merge_sorted[size];
    for (int i = 0; i < size; ++i) merge_sorted[i] = test_list[i];
    merge_sort(merge_sorted, 0, size - 1);
    printf("Merge Sorted: ");
    print_array(merge_sorted, size);

    // Quick Sort
    int quick_sorted[size];
    for (int i = 0; i < size; ++i) quick_sorted[i] = test_list[i];
    quick_sort(quick_sorted, 0, size - 1);
    printf("Quick Sorted: ");
    print_array(quick_sorted, size);

    // Linear Search
    printf("Index of 25 (Linear Search): %d\n", linear_search(test_list, size, 25));
    printf("Index of 100 (Linear Search): %d\n", linear_search(test_list, size, 100));

    // Binary Search (on sorted list)
    printf("Index of 25 (Binary Search): %d\n", binary_search(merge_sorted, size, 25));
    printf("Index of 100 (Binary Search): %d\n", binary_search(merge_sorted, size, 100));

    return 0;
}
