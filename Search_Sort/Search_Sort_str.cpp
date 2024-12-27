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

#include <iostream>
#include <string>

using namespace std;

///////////////////////////////////////
//////////// Linear Search ////////////
///////////////////////////////////////

int linear_search(const string& s, char target) {
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == target) return i;
    }
    return -1;
}

///////////////////////////////////////
//////////// Binary Search ////////////
///////////////////////////////////////

int binary_search(const string& s, char target) {
    int start = 0, end = s.size() - 1;
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

string bubble_sort(string s) {
    for (size_t i = 0; i < s.size() - 1; ++i) {
        for (size_t j = 0; j < s.size() - 1 - i; ++j) {
            if (s[j] > s[j + 1]) {
                swap(s[j], s[j + 1]);
            }
        }
    }
    return s;
}

string bubble_sort_optimized(string s) {
    for (size_t i = 0; i < s.size() - 1; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < s.size() - 1 - i; ++j) {
            if (s[j] > s[j + 1]) {
                swap(s[j], s[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return s;
}

///////////////////////////////////////
/////////// Selection Sort ////////////
///////////////////////////////////////

string selection_sort(string s) {
    for (size_t i = 0; i < s.size() - 1; ++i) {
        size_t smallest = i;
        for (size_t j = i + 1; j < s.size(); ++j) {
            if (s[j] < s[smallest]) {
                smallest = j;
            }
        }
        swap(s[i], s[smallest]);
    }
    return s;
}

///////////////////////////////////////
/////////// Insertion Sort ////////////
///////////////////////////////////////

string insertion_sort(string s) {
    for (size_t i = 1; i < s.size(); ++i) {
        char key = s[i];
        size_t j = i;
        while (j > 0 && s[j - 1] > key) {
            s[j] = s[j - 1];
            --j;
        }
        s[j] = key;
    }
    return s;
}

///////////////////////////////////////
//////////// Merge Sort ///////////////
///////////////////////////////////////

void merge(string& s, int left, int mid, int right) {
    string sub1 = s.substr(left, mid - left + 1);
    string sub2 = s.substr(mid + 1, right - mid);

    size_t i = 0, j = 0;
    int k = left;

    while (i < sub1.size() && j < sub2.size()) {
        if (sub1[i] <= sub2[j]) {
            s[k++] = sub1[i++];
        } else {
            s[k++] = sub2[j++];
        }
    }
    while (i < sub1.size()) s[k++] = sub1[i++];
    while (j < sub2.size()) s[k++] = sub2[j++];
}

void merge_sort(string& s, int left, int right) {
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

int partition(string& s, int low, int high) {
    char pivot = s[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (s[j] <= pivot) {
            ++i;
            swap(s[i], s[j]);
        }
    }
    swap(s[i + 1], s[high]);
    return i + 1;
}

void quick_sort(string& s, int low, int high) {
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
    string test_str = "zxywvutsrqponmlkjihgfedcba";

    cout << "Original String: " << test_str << endl;

    // Bubble Sort
    cout << "Bubble Sorted: " << bubble_sort(test_str) << endl;

    // Optimized Bubble Sort
    cout << "Optimized Bubble Sorted: " << bubble_sort_optimized(test_str) << endl;

    // Selection Sort
    cout << "Selection Sorted: " << selection_sort(test_str) << endl;

    // Insertion Sort
    cout << "Insertion Sorted: " << insertion_sort(test_str) << endl;

    // Merge Sort
    string merge_sorted = test_str;
    merge_sort(merge_sorted, 0, merge_sorted.size() - 1);
    cout << "Merge Sorted: " << merge_sorted << endl;

    // Quick Sort
    string quick_sorted = test_str;
    quick_sort(quick_sorted, 0, quick_sorted.size() - 1);
    cout << "Quick Sorted: " << quick_sorted << endl;

    // Linear Search
    cout << "Index of 'm' (Linear Search): " << linear_search(test_str, 'm') << endl;
    cout << "Index of 'z' (Linear Search): " << linear_search(test_str, 'z') << endl;
    cout << "Index of '1' (Linear Search): " << linear_search(test_str, '1') << endl;

    // Binary Search (on sorted string)
    string sorted_str = bubble_sort(test_str);
    cout << "Binary Search for 'm': " << binary_search(sorted_str, 'm') << endl;
    cout << "Binary Search for 'z': " << binary_search(sorted_str, 'z') << endl;
    cout << "Binary Search for '1': " << binary_search(sorted_str, '1') << endl;

    return 0;
}
