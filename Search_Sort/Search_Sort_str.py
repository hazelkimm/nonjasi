"""
Search
- Linear Search  : while loop / sentinel
- Binary Search  : while loop

Sort
- Bubble Sort    : standard / optimized
- Selection Sort
- Insertion Sort
- Merge Sort     (<- merge_sort_help <- merge)
- Quick Sort     (<- partition)
"""

#######################################
############ Linear Search ############
#######################################

def linear_search(s: str, target: str) -> int:
    for i in range(len(s)):
        if s[i] == target:
            return i
    return -1

def linear_search_sentinel(s: str, target: str) -> int:
    s += target  # Add sentinel
    i = 0
    while s[i] != target:
        i += 1
    return i if i < len(s) - 1 else -1

#######################################
############ Binary Search ############
#######################################

def binary_search(s: str, target: str) -> int:
    start, end = 0, len(s) - 1
    while start <= end:
        mid = start + (end - start) // 2
        if s[mid] < target:
            start = mid + 1
        elif s[mid] > target:
            end = mid - 1
        else:
            return mid
    return -1

#######################################
############# Bubble Sort #############
#######################################

def bubble_sort(s: str) -> str:
    s = list(s)
    for i in range(len(s) - 1):
        for j in range(len(s) - 1 - i):
            if s[j] > s[j + 1]:
                s[j], s[j + 1] = s[j + 1], s[j]
    return ''.join(s)

def bubble_sort_optimized(s: str) -> str:
    s = list(s)
    for i in range(len(s) - 1):
        swapped = False
        for j in range(len(s) - 1 - i):
            if s[j] > s[j + 1]:
                s[j], s[j + 1] = s[j + 1], s[j]
                swapped = True
        if not swapped:
            break
    return ''.join(s)

#######################################
########### Selection Sort ############
#######################################

def selection_sort(s: str) -> str:
    s = list(s)
    for i in range(len(s) - 1):
        smallest = i
        for j in range(i + 1, len(s)):
            if s[j] < s[smallest]:
                smallest = j
        s[i], s[smallest] = s[smallest], s[i]
    return ''.join(s)

#######################################
########### Insertion Sort ############
#######################################

def insertion_sort(s: str) -> str:
    s = list(s)
    for i in range(1, len(s)):
        key = s[i]
        j = i - 1
        while j >= 0 and s[j] > key:
            s[j + 1] = s[j]
            j -= 1
        s[j + 1] = key
    return ''.join(s)

#######################################
############## Merge Sort #############
#######################################

def merge(s: list, left: int, mid: int, right: int) -> None:
    sub1 = s[left:mid + 1]
    sub2 = s[mid + 1:right + 1]

    i = j = 0
    k = left

    while i < len(sub1) and j < len(sub2):
        if sub1[i] <= sub2[j]:
            s[k] = sub1[i]
            i += 1
        else:
            s[k] = sub2[j]
            j += 1
        k += 1

    while i < len(sub1):
        s[k] = sub1[i]
        i += 1
        k += 1

    while j < len(sub2):
        s[k] = sub2[j]
        j += 1
        k += 1

def merge_sort(s: str) -> str:
    s = list(s)
    def merge_sort_help(s: list, left: int, right: int) -> None:
        if left < right:
            mid = left + (right - left) // 2
            merge_sort_help(s, left, mid)
            merge_sort_help(s, mid + 1, right)
            merge(s, left, mid, right)

    merge_sort_help(s, 0, len(s) - 1)
    return ''.join(s)

#######################################
############## Quick Sort #############
#######################################

def partition(s: list, low: int, high: int) -> int:
    pivot = s[high]
    i = low - 1
    for j in range(low, high):
        if s[j] <= pivot:
            i += 1
            s[i], s[j] = s[j], s[i]
    s[i + 1], s[high] = s[high], s[i + 1]
    return i + 1

def quick_sort(s: str) -> str:
    s = list(s)
    def quick_sort_help(s: list, low: int, high: int) -> None:
        if low < high:
            pivot_index = partition(s, low, high)
            quick_sort_help(s, low, pivot_index - 1)
            quick_sort_help(s, pivot_index + 1, high)

    quick_sort_help(s, 0, len(s) - 1)
    return ''.join(s)

#######################################
############## Test Cases #############
#######################################

if __name__ == "__main__":
    test_str = "zxywvutsrqponmlkjihgfedcba"
    print("Original String:", test_str)

    # Bubble Sort
    print("Bubble Sorted:", bubble_sort(test_str))

    # Optimized Bubble Sort
    print("Optimized Bubble Sorted:", bubble_sort_optimized(test_str))

    # Selection Sort
    print("Selection Sorted:", selection_sort(test_str))

    # Insertion Sort
    print("Insertion Sorted:", insertion_sort(test_str))

    # Merge Sort
    print("Merge Sorted:", merge_sort(test_str))

    # Quick Sort
    print("Quick Sorted:", quick_sort(test_str))

    # Linear Search
    print("Index of 'm' (Linear Search):", linear_search(test_str, 'm'))
    print("Index of 'z' (Linear Search):", linear_search(test_str, 'z'))
    print("Index of '1' (Linear Search):", linear_search(test_str, '1'))

    # Binary Search (on sorted string)
    sorted_str = bubble_sort(test_str)
    print("Binary Search for 'm':", binary_search(sorted_str, 'm'))
    print("Binary Search for 'z':", binary_search(sorted_str, 'z'))
    print("Binary Search for '1':", binary_search(sorted_str, '1'))
