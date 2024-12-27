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

#include <iostream>
#include <vector>

using namespace std;

///////////////////////////////////////
//////////// Linear Search ////////////
///////////////////////////////////////

int linear_search(const vector<int>& L, int target) {
    for (int i = 0; i < L.size(); ++i) {
        if (L[i] == target) return i;
    }
    return -1;
}

int linear_search_sentinel(vector<int> L, int target) {
    L.push_back(target);
    int i = 0;
    while (L[i] != target) {
        ++i;
    }
    if (i == L.size() - 1) return -1;
    return i;
}

///////////////////////////////////////
//////////// Binary Search ////////////
///////////////////////////////////////

int binary_search(const vector<int>& L, int target) {
    int start = 0, end = L.size() - 1;
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

void bubble_sort(vector<int>& L) {
    for (size_t i = 0; i < L.size() - 1; ++i) {
        for (size_t j = 0; j < L.size() - 1 - i; ++j) {
            if (L[j] > L[j + 1]) swap(L[j], L[j + 1]);
        }
    }
}

void bubble_sort_optimized(vector<int>& L) {
    for (size_t i = 0; i < L.size() - 1; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < L.size() - 1 - i; ++j) {
            if (L[j] > L[j + 1]) {
                swap(L[j], L[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

///////////////////////////////////////
/////////// Selection Sort ////////////
///////////////////////////////////////

void selection_sort(vector<int>& L) {
    for (size_t i = 0; i < L.size() - 1; ++i) {
        size_t smallest = i;
        for (size_t j = i + 1; j < L.size(); ++j) {
            if (L[j] < L[smallest]) smallest = j;
        }
        swap(L[i], L[smallest]);
    }
}

///////////////////////////////////////
/////////// Insertion Sort ////////////
///////////////////////////////////////

void insertion_sort(vector<int>& L) {
    for (size_t i = 1; i < L.size(); ++i) {
        int key = L[i];
        size_t j = i;
        while (j > 0 && L[j - 1] > key) {
            L[j] = L[j - 1];
            --j;
        }
        L[j] = key;
    }
}

///////////////////////////////////////
//////////// Merge Sort ///////////////
///////////////////////////////////////

void merge(vector<int>& L, int first, int mid, int last) {
    vector<int> sub1(L.begin() + first, L.begin() + mid + 1);
    vector<int> sub2(L.begin() + mid + 1, L.begin() + last + 1);

    int i = 0, j = 0, k = first;
    while (i < sub1.size() && j < sub2.size()) {
        if (sub1[i] <= sub2[j]) L[k++] = sub1[i++];
        else L[k++] = sub2[j++];
    }
    while (i < sub1.size()) L[k++] = sub1[i++];
    while (j < sub2.size()) L[k++] = sub2[j++];
}

void merge_sort_help(vector<int>& L, int first, int last) {
    if (first >= last) return;
    int mid = first + (last - first) / 2;
    merge_sort_help(L, first, mid);
    merge_sort_help(L, mid + 1, last);
    merge(L, first, mid, last);
}

void merge_sort(vector<int>& L) {
    merge_sort_help(L, 0, L.size() - 1);
}

///////////////////////////////////////
//////////// Quick Sort ///////////////
///////////////////////////////////////

int partition(vector<int>& L, int low, int high) {
    int pivot = L[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (L[j] <= pivot) {
            ++i;
            swap(L[i], L[j]);
        }
    }
    swap(L[i + 1], L[high]);
    return i + 1;
}

void quick_sort(vector<int>& L, int low, int high) {
    if (low < high) {
        int pivot_index = partition(L, low, high);
        quick_sort(L, low, pivot_index - 1);
        quick_sort(L, pivot_index + 1, high);
    }
}

///////////////////////////////////////
//////////// Test Cases ///////////////
///////////////////////////////////////

int main() {
    vector<int> test_list = {64, 34, 25, 12, 22, 11, 90};

    cout << "Original List: ";
    for (int num : test_list) cout << num << " ";
    cout << endl;

    // Bubble Sort
    vector<int> bubble_sorted = test_list;
    bubble_sort(bubble_sorted);
    cout << "Bubble Sorted: ";
    for (int num : bubble_sorted) cout << num << " ";
    cout << endl;

    // Optimized Bubble Sort
    vector<int> bubble_sorted_opt = test_list;
    bubble_sort_optimized(bubble_sorted_opt);
    cout << "Optimized Bubble Sorted: ";
    for (int num : bubble_sorted_opt) cout << num << " ";
    cout << endl;

    // Selection Sort
    vector<int> selection_sorted = test_list;
    selection_sort(selection_sorted);
    cout << "Selection Sorted: ";
    for (int num : selection_sorted) cout << num << " ";
    cout << endl;

    // Insertion Sort
    vector<int> insertion_sorted = test_list;
    insertion_sort(insertion_sorted);
    cout << "Insertion Sorted: ";
    for (int num : insertion_sorted) cout << num << " ";
    cout << endl;

    // Merge Sort
    vector<int> merge_sorted = test_list;
    merge_sort(merge_sorted);
    cout << "Merge Sorted: ";
    for (int num : merge_sorted) cout << num << " ";
    cout << endl;

    // Quick Sort
    vector<int> quick_sorted = test_list;
    quick_sort(quick_sorted, 0, quick_sorted.size() - 1);
    cout << "Quick Sorted: ";
    for (int num : quick_sorted) cout << num << " ";
    cout << endl;

    // Linear Search
    cout << "Index of 25 (Linear Search): " << linear_search(test_list, 25) << endl;
    cout << "Index of 100 (Linear Search): " << linear_search(test_list, 100) << endl;

    // Binary Search (on sorted list)
    vector<int> sorted_list = merge_sorted; // Already sorted by Merge Sort
    cout << "Index of 25 (Binary Search): " << binary_search(sorted_list, 25) << endl;
    cout << "Index of 100 (Binary Search): " << binary_search(sorted_list, 100) << endl;

    return 0;
}
