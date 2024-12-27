/*
Search
- Linear Search
- Binary Search

Sort
- Bubble Sort    : standard / optimized
- Selection Sort
- Insertion Sort
- Merge Sort     (<- merge)
- Quick Sort     (<- partition)
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

///////////////////////////////////////
//////////// Linear Search ////////////
///////////////////////////////////////

int linear_search(const char *s, char target) {
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == target) return i;
    }
    return -1;
}

///////////////////////////////////////
//////////// Binary Search ////////////
///////////////////////////////////////

int binary_search(const char *s, char target) {
    int start = 0, end = strlen(s) - 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (s[mid] < target) {
            start = mid + 1;
        } else if (s[mid] > target) {
            end = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

///////////////////////////////////////
//////////// Bubble Sort //////////////
///////////////////////////////////////

void bubble_sort(char *s) {
    int n = strlen(s);
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (s[j] > s[j + 1]) {
                char temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_optimized(char *s) {
    int n = strlen(s);
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (s[j] > s[j + 1]) {
                char temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

///////////////////////////////////////
/////////// Selection Sort ////////////
///////////////////////////////////////

void selection_sort(char *s) {
    int n = strlen(s);
    for (int i = 0; i < n - 1; ++i) {
        int smallest = i;
        for (int j = i + 1; j < n; ++j) {
            if (s[j] < s[smallest]) {
                smallest = j;
            }
        }
        char temp = s[i];
        s[i] = s[smallest];
        s[smallest] = temp;
    }
}

///////////////////////////////////////
/////////// Insertion Sort ////////////
///////////////////////////////////////

void insertion_sort(char *s) {
    int n = strlen(s);
    for (int i = 1; i < n; ++i) {
        char key = s[i];
        int j = i - 1;
        while (j >= 0 && s[j] > key) {
            s[j + 1] = s[j];
            --j;
        }
        s[j + 1] = key;
    }
}

///////////////////////////////////////
//////////// Merge Sort ///////////////
///////////////////////////////////////

void merge(char *s, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    char sub1[n1 + 1], sub2[n2 + 1];

    for (int i = 0; i < n1; ++i) sub1[i] = s[left + i];
    for (int i = 0; i < n2; ++i) sub2[i] = s[mid + 1 + i];

    sub1[n1] = '\0';
    sub2[n2] = '\0';

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (sub1[i] <= sub2[j]) {
            s[k++] = sub1[i++];
        } else {
            s[k++] = sub2[j++];
        }
    }
    while (i < n1) s[k++] = sub1[i++];
    while (j < n2) s[k++] = sub2[j++];
}

void merge_sort(char *s, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(s, left, mid);
        merge_sort(s, mid + 1, right);
        merge(s, left, mid, right);
    }
}

///////////////////////////////////////
//////////// Quick Sort ///////////////
///////////////////////////////////////

int partition(char *s, int low, int high) {
    char pivot = s[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (s[j] <= pivot) {
            ++i;
            char temp = s[i];
            s[i] = s[j];
            s[j] = temp;
        }
    }
    char temp = s[i + 1];
    s[i + 1] = s[high];
    s[high] = temp;
    return i + 1;
}

void quick_sort(char *s, int low, int high) {
    if (low < high) {
        int pivot_index = partition(s, low, high);
        quick_sort(s, low, pivot_index - 1);
        quick_sort(s, pivot_index + 1, high);
    }
}

///////////////////////////////////////
//////////// Test Cases ///////////////
///////////////////////////////////////

int main() {
    char test_str[] = "zxywvutsrqponmlkjihgfedcba";

    printf("Original String: %s\n", test_str);

    // Bubble Sort
    char bubble_sorted[sizeof(test_str)];
    strcpy(bubble_sorted, test_str);
    bubble_sort(bubble_sorted);
    printf("Bubble Sorted: %s\n", bubble_sorted);

    // Optimized Bubble Sort
    char bubble_sorted_opt[sizeof(test_str)];
    strcpy(bubble_sorted_opt, test_str);
    bubble_sort_optimized(bubble_sorted_opt);
    printf("Optimized Bubble Sorted: %s\n", bubble_sorted_opt);

    // Selection Sort
    char selection_sorted[sizeof(test_str)];
    strcpy(selection_sorted, test_str);
    selection_sort(selection_sorted);
    printf("Selection Sorted: %s\n", selection_sorted);

    // Insertion Sort
    char insertion_sorted[sizeof(test_str)];
    strcpy(insertion_sorted, test_str);
    insertion_sort(insertion_sorted);
    printf("Insertion Sorted: %s\n", insertion_sorted);

    // Merge Sort
    char merge_sorted[sizeof(test_str)];
    strcpy(merge_sorted, test_str);
    merge_sort(merge_sorted, 0, strlen(merge_sorted) - 1);
    printf("Merge Sorted: %s\n", merge_sorted);

    // Quick Sort
    char quick_sorted[sizeof(test_str)];
    strcpy(quick_sorted, test_str);
    quick_sort(quick_sorted, 0, strlen(quick_sorted) - 1);
    printf("Quick Sorted: %s\n", quick_sorted);

    // Linear Search
    printf("Index of 'm' (Linear Search): %d\n", linear_search(test_str, 'm'));
    printf("Index of 'z' (Linear Search): %d\n", linear_search(test_str, 'z'));
    printf("Index of '1' (Linear Search): %d\n", linear_search(test_str, '1'));

    // Binary Search (on sorted string)
    printf("Binary Search for 'm': %d\n", binary_search(bubble_sorted, 'm'));
    printf("Binary Search for 'z': %d\n", binary_search(bubble_sorted, 'z'));
    printf("Binary Search for '1': %d\n", binary_search(bubble_sorted, '1'));

    return 0;
}
