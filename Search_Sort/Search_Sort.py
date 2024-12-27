"""
Search
- Linear Search  : while loop / sentinel / for loop
- Binary Search  : while loop / recursion

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

# while loop
def linear_search(L: list, target: int) -> int:
    i = 0
    while i < len(L) and L[i] != target:
        i += 1
    
    if i == len(L):
        return -1
    else:
        return i

# with sentinel
def linear_search_sentinel(L: list, target: int) -> int:
    L.append(target)       # Add the sentinel
    i = 0
    while L[i] != target:  # This condition is enough!
        i += 1
    L.pop()                # Remove the sentinel
    
    if i == len(L):
        return -1
    else:
        return i

# for loop
def linear_search_for(L: list, target: int) -> int:
    for i in range(len(L)):
        if L[i] == target:
            return i
    return -1


#######################################
############ Binary Search ############
#######################################

# while loop
def binary_search(L: list, target: int) -> int:
    start, end = 0, len(L) - 1
    while start != end + 1:
        mid = (start + end) // 2
        if L[mid] < target:
            start = mid + 1
        else:
            end = mid - 1
    
    if start < len(L) and L[start] == target:
        return start
    else:
        return -1

# recursion
def binary_search_recur(arr, target, low, high):
    if low > high:
        return -1

    mid = (low + high) // 2

    if arr[mid] == target:
        return mid
    elif arr[mid] > target:
        return binary_search_recur(arr, target, low, mid - 1)
    else:
        return binary_search_recur(arr, target, mid + 1, high)


#######################################
############# Bubble Sort #############
#######################################

# standard
def bubble_sort(L: list) -> None:
    n = len(L)
    for i in range(n - 1):
        for j in range(n - 1 - i):
            if L[j] > L[j + 1]:
                L[j], L[j + 1] = L[j + 1], L[j]

# optimized
def bubble_sort_optimized(L: list) -> None:
    n = len(L)
    for i in range(n - 1):
        swapped = False
        for j in range(n - 1 - i):
            if L[j] > L[j + 1]:
                L[j], L[j + 1] = L[j + 1], L[j]
                swapped = True
        if not swapped:  # Optimization: stop if no swaps occurred
            break


#######################################
########### Selection Sort ############
#######################################

def selection_sort(L: list) -> None:
    for i in range(len(L) - 1):
        smallest = i                           # Find the minimum value of the unsorted list
        for j in range(i + 1, len(L)):
            if L[j] < L[smallest]:
                smallest = j
        
        L[i], L[smallest] = L[smallest], L[i]  # Swap it with the leftmost entry


#######################################
########### Insertion Sort ############
#######################################

def insertion_sort(L: list) -> None:
    for i in range(1, len(L)):     # Insert the leftmost item (=L[i]) of the unsorted list
        for j in range(i, 0, -1):  # to the proper location of the sorted list (=L[:i])
            if L[j - 1] > L[j]:
                L[j - 1], L[j] = L[j], L[j - 1]
            else:
                break


#######################################
############## Merge Sort #############
#######################################

def merge(L: list, first: int, mid: int, last: int) -> None:
    k = first
    sub1 = L[first:mid + 1]
    sub2 = L[mid + 1:last + 1]
    i = j = 0
    while i < len(sub1) and j < len(sub2):
        if sub1[i] <= sub2[j]:
            L[k] = sub1[i]
            i += 1
        else:
            L[k] = sub2[j]
            j += 1
        k +=1
    if i < len(sub1):                      # Check if any element is left
        L[k:last + 1] = sub1[i:]
    elif j < len(sub2):
        L[k:last + 1] = sub2[j:]

def merge_sort_help(L: list, first: int, last: int) -> None:
    if first == last:                      # Conditional statements
        return                             # Base case
    else:
        mid = first + (last - first) // 2
        merge_sort_help(L, first, mid)     # Recursive call for sublist1
        merge_sort_help(L, mid + 1, last)  # Recursive call for sublist2
        merge(L, first, mid, last)         # Merge the two (sorted) sublists

def merge_sort(L: list) -> None:
    merge_sort_help(L, 0, len(L) - 1)


#######################################
############## Quick Sort #############
#######################################

def partition(L: list, low: int, high: int) -> int:
    pivot = L[high]
    i = low - 1
    for j in range(low, high):
        if L[j] <= pivot:
            i += 1
            L[i], L[j] = L[j], L[i]
    L[i + 1], L[high] = L[high], L[i + 1]
    return i + 1

def quick_sort(L: list, low: int, high: int) -> None:
    if low < high:
        pivot_index = partition(L, low, high)
        quick_sort(L, low, pivot_index - 1)
        quick_sort(L, pivot_index + 1, high)

#######################################
############## Test Cases #############
#######################################

if __name__ == "__main__":
    test_list = [64, 34, 25, 12, 22, 11, 90]
    print("Original List:", test_list)

    # Bubble Sort
    bubble_sorted = test_list[:]
    bubble_sort(bubble_sorted)
    print("Bubble Sorted:", bubble_sorted)

    # Optimized Bubble Sort
    bubble_sorted_opt = test_list[:]
    bubble_sort_optimized(bubble_sorted_opt)
    print("Optimized Bubble Sorted:", bubble_sorted_opt)

    # Selection Sort
    selection_sorted = test_list[:]
    selection_sort(selection_sorted)
    print("Selection Sorted:", selection_sorted)

    # Insertion Sort
    insertion_sorted = test_list[:]
    insertion_sort(insertion_sorted)
    print("Insertion Sorted:", insertion_sorted)

    # Merge Sort
    merge_sorted = test_list[:]
    merge_sort(merge_sorted)
    print("Merge Sorted:", merge_sorted)

    # Quick Sort
    quick_sorted = test_list[:]
    quick_sort(quick_sorted, 0, len(quick_sorted) - 1)
    print("Quick Sorted:", quick_sorted)

    # Linear Search
    print("Index of 25 (Linear Search):", linear_search(test_list, 25))
    print("Index of 100 (Linear Search):", linear_search(test_list, 100))

    # Binary Search (on sorted list)
    sorted_list = sorted(test_list)
    print("Sorted List for Binary Search:", sorted_list)
    print("Index of 25 (Binary Search):", binary_search(sorted_list, 25))
    print("Index of 100 (Binary Search):", binary_search(sorted_list, 100))
