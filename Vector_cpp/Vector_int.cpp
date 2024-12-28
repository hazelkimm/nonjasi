/*
1. 리스트 합치기: vector<int> merge_lists(vector<vector<int>>& lists)
2. 중복 요소 제거: vector<int> remove_duplicates(vector<int>& lst)
3. 최대값과 최소값 찾기: pair<int, int> find_max_min(vector<int>& lst)
4. 리스트 회전: vector<int> rotate_list(vector<int>& lst, int k)
5. 요소 빈도수 계산: int count_element(vector<int>& lst, int element)
6. 리스트 뒤집기: vector<int> reverse_list(vector<int>& lst)
7. 요소 인덱스 찾기: int find_element_index(vector<int>& lst, int element) 
8. 조건에 맞는 요소 필터링: vector<int> filter_list(vector<int>& lst, Func condition_func)
9. 서브리스트 추출: vector<vector<int>> find_sublists(vector<int>& lst, int length)
10. 숫자 합 계산: int sum_of_numbers(vector<int>& lst)
11. 리스트 정렬: vector<int> sort_list(vector<int> lst, bool descending = false)
12. 특정 값 제거: vector<int> remove_value(vector<int>& lst, int value)
13. 교집합 구하기: vector<int> intersection_of_lists(vector<int>& lst1, vector<int>& lst2)
14. 합집합 구하기: vector<int> union_of_lists(vector<int>& lst1, vector<int>& lst2)
15. 차집합 구하기: vector<int> difference_of_lists(vector<int>& lst1, vector<int>& lst2)
16. 평균 계산: double average_of_list(vector<int>& lst) 
17. 최빈값 찾기: int mode_of_list(vector<int>& lst)
18. 연속된 중복 요소 제거: vector<int> remove_consecutive_duplicates(vector<int>& lst)
19. 리스트 섞기: vector<int> shuffle_list(vector<int> lst)
20. 슬라이싱: vector<int> slice(vector<int>& vec, int start, int end)
*/


#include <iostream>
#include <vector>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////
// 여러 리스트를 합치는 함수
vector<int> merge_lists(vector<vector<int>>& lists) {
    vector<int> merged;
    for (vector<int>& list : lists) {  // 각 리스트를 순차적으로 합칩니다.
        merged.insert(merged.end(), list.begin(), list.end());
    }
    return merged;  // 합쳐진 리스트 반환
}

// int main() {
//     // 예시 리스트들
//     vector<vector<int>> lists = {
//         {1, 2, 3},
//         {4, 5},
//         {6, 7, 8, 9}
//     };

//     // merge_lists 함수 호출하여 리스트 합치기
//     vector<int> merged = merge_lists(lists);

//     // 합쳐진 리스트 출력
//     cout << "Merged List: ";
//     for (int num : merged) {  // 합쳐진 리스트의 각 요소 출력
//         cout << num << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// #include <set>
// // 리스트에서 중복된 요소를 제거하는 함수
// vector<int> remove_duplicates(const vector<int>& lst) {
//     set<int> s(lst.begin(), lst.end());  // set을 사용하여 중복 제거
//     return vector<int>(s.begin(), s.end());  // set의 요소를 vector로 변환하여 반환
// }

// #include <algorithm>  // std::find를 사용하기 위한 헤더
// // 리스트에서 중복된 요소를 제거하는 함수
// vector<int> remove_duplicates(const vector<int>& lst) {
//     vector<int> unique_lst;
//     for (int num : lst) {
//         // 이미 unique_lst에 num이 있는지 확인
//         if (find(unique_lst.begin(), unique_lst.end(), num) == unique_lst.end()) {
//             unique_lst.push_back(num);  // 중복이 없으면 unique_lst에 추가
//         }
//     }
//     return unique_lst;  // 중복이 제거된 리스트 반환
// }

// 리스트에서 중복된 요소를 제거하는 함수
vector<int> remove_duplicates(vector<int>& lst) {
    vector<int> unique_lst;
    for (int num : lst) {
        bool found = false;
        // 이미 unique_lst에 num이 있는지 확인
        for (int unique_num : unique_lst) {
            if (num == unique_num) {
                found = true;
                break;  // 중복이 있으면 더 이상 확인할 필요 없음
            }
        }
        if (!found) {
            unique_lst.push_back(num);  // 중복이 없으면 unique_lst에 추가
        }
    }
    return unique_lst;  // 중복이 제거된 리스트 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {1, 2, 2, 3, 4, 4, 5};

//     // remove_duplicates 함수 호출하여 중복 제거
//     vector<int> unique_lst = remove_duplicates(lst);

//     // 중복이 제거된 리스트 출력
//     cout << "Unique List: ";
//     for (int num : unique_lst) {  // 중복이 제거된 리스트의 각 요소 출력
//         cout << num << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트에서 최대값과 최소값을 찾는 함수
pair<int, int> find_max_min(vector<int>& lst) {
    if (lst.empty()) return {0, 0};  // 리스트가 비어 있으면 (0, 0) 반환
    int max_value = lst[0], min_value = lst[0];  // 첫 번째 값을 최대값과 최소값으로 초기화
    for (int num : lst) {  // 리스트의 각 요소를 확인
    //for (int i = 0; i < lst.size(); ++i)
        if (num > max_value) max_value = num;  // 최대값 갱신
        if (num < min_value) min_value = num;  // 최소값 갱신
    }
    return {max_value, min_value};  // 최대값과 최소값을 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {10, 2, 33, 4, 5, 7, -1};

//     // find_max_min 함수 호출하여 최대값과 최소값 찾기
//     pair<int, int> result = find_max_min(lst);

//     // 최대값과 최소값 출력
//     cout << "Max Value: " << result.first << ", Min Value: " << result.second << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트를 k만큼 회전시키는 함수
vector<int> rotate_list(vector<int>& lst, int k) {
    int n = lst.size();  // 리스트의 크기
    if (n == 0) return lst;  // 리스트가 비어있으면 그대로 반환
    k %= n;  // k가 리스트 길이보다 클 수 있으므로, k를 리스트 크기로 나눈 나머지로 조정
    vector<int> rotated(lst.begin() + k, lst.end());  // k번째부터 끝까지 잘라서 새로운 벡터에 저장
    rotated.insert(rotated.end(), lst.begin(), lst.begin() + k);  // 앞부분을 뒤에 추가하여 회전 효과
    return rotated;  // 회전된 리스트 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {1, 2, 3, 4, 5};

//     // rotate_list 함수 호출하여 리스트를 회전시킴
//     vector<int> rotated_lst = rotate_list(lst, 2);

//     // 회전된 리스트 출력
//     cout << "Rotated List: ";
//     for (int num : rotated_lst) {  // 회전된 리스트의 각 요소 출력
//         cout << num << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트에서 주어진 요소의 빈도수를 반환하는 함수
int count_element(vector<int>& lst, int element) {
    int count = 0;  // 요소의 빈도수를 세기 위한 변수
    for (int num : lst) {  // 리스트의 각 요소를 확인
        if (num == element) {  // 요소가 일치하면 빈도수 증가
            ++count;
        }
    }
    return count;  // 요소의 빈도수 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {1, 2, 3, 4, 2, 2, 5};

//     // count_element 함수 호출하여 2의 빈도수를 찾기
//     int count = count_element(lst, 2);

//     // 결과 출력
//     cout << "Element 2 appears " << count << " times." << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트의 순서를 뒤집는 함수
vector<int> reverse_list(vector<int>& lst) {
    vector<int> reversed(lst.rbegin(), lst.rend());  // 리스트를 뒤집어서 새로운 벡터에 저장
    return reversed;  // 뒤집힌 리스트 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {1, 2, 3, 4, 5};

//     // reverse_list 함수 호출하여 리스트 순서 뒤집기
//     vector<int> reversed_lst = reverse_list(lst);

//     // 뒤집힌 리스트 출력
//     cout << "Reversed List: ";
//     for (int num : reversed_lst) {  // 뒤집힌 리스트의 각 요소 출력
//         cout << num << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트에서 주어진 요소의 인덱스를 반환하는 함수
int find_element_index(vector<int>& lst, int element) {
    for (size_t i = 0; i < lst.size(); ++i) {  // 리스트의 각 요소를 순차적으로 확인
        if (lst[i] == element) {  // 요소가 일치하면 인덱스 반환
            return i;
        }
    }
    return -1;  // 요소가 없으면 -1을 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {10, 20, 30, 40, 50};

//     // find_element_index 함수 호출하여 30의 인덱스 찾기
//     int index = find_element_index(lst, 30);

//     // 결과 출력
//     if (index != -1) {
//         cout << "Element found at index: " << index << endl;
//     } else {
//         cout << "Element not found." << endl;
//     }

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 내 주어진 조건에 맞는 요소만을 반환하는 함수
template<typename Func>
vector<int> filter_list(vector<int>& lst, Func condition_func) {
    vector<int> result;  // 조건에 맞는 요소를 저장할 벡터
    for (int num : lst) {  // 리스트의 각 요소를 순차적으로 확인
        if (condition_func(num)) {  // 조건 함수가 참이면
            result.push_back(num);  // 해당 요소를 결과 벡터에 추가
        }
    }
    return result;  // 조건에 맞는 요소들만 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {1, 2, 3, 4, 5, 6, 7, 8, 9};

//     // filter_list 함수 호출하여 짝수만 필터링
//     vector<int> even_numbers = filter_list(lst, [](int num) { return num % 2 == 0; });

//     // 필터링된 리스트 출력
//     cout << "Filtered List (Even Numbers): ";
//     for (int num : even_numbers) {  // 필터링된 리스트의 각 요소 출력
//         cout << num << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트에서 연속된 서브리스트를 반환하는 함수
vector<vector<int>> find_sublists(vector<int>& lst, int length) {
    vector<vector<int>> sublists;  // 결과로 반환할 서브리스트들을 저장할 벡터
    for (size_t i = 0; i <= lst.size() - length; ++i) {  // 리스트의 연속된 부분을 확인
        sublists.push_back(vector<int>(lst.begin() + i, lst.begin() + i + length));  // 서브리스트 추가
    }
    return sublists;  // 서브리스트들 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {1, 2, 3, 4, 5};

//     // find_sublists 함수 호출하여 서브리스트 길이 3으로 찾기
//     vector<vector<int>> sublists = find_sublists(lst, 3);

//     // 서브리스트 출력
//     cout << "Sublists: " << endl;
//     for (const vector<int>& sublist : sublists) {  // 각 서브리스트 출력
//         for (int num : sublist) {
//             cout << num << " ";
//         }
//         cout << endl;
//     }

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 내의 숫자들의 합을 반환하는 함수
int sum_of_numbers(vector<int>& lst) {
    int sum = 0;  // 합을 저장할 변수
    for (int num : lst) {  // 리스트의 각 요소를 순차적으로 확인
        sum += num;  // 요소를 합산
    }
    return sum;  // 합 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {1, 2, 3, 4, 5};

//     // sum_of_numbers 함수 호출하여 리스트의 합 구하기
//     int total = sum_of_numbers(lst);

//     // 결과 출력
//     cout << "Sum of numbers: " << total << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트를 오름차순 또는 내림차순으로 정렬하는 함수
vector<int> sort_list(vector<int> lst, bool descending = false) {
    for (size_t i = 0; i < lst.size(); ++i) {  // 리스트의 각 요소를 확인
        for (size_t j = i + 1; j < lst.size(); ++j) {  // i보다 뒤에 있는 요소들을 비교
            // 내림차순 정렬 조건 또는 오름차순 정렬 조건에 맞는 경우 두 요소를 교환
            if ((descending && lst[i] < lst[j]) || (!descending && lst[i] > lst[j])) {
                swap(lst[i], lst[j]);  // 요소 교환
            }
        }
    }
    return lst;  // 정렬된 리스트 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {5, 3, 8, 1, 2};

//     // sort_list 함수 호출하여 리스트를 오름차순으로 정렬
//     vector<int> sorted_lst_asc = sort_list(lst);

//     // 오름차순 정렬된 리스트 출력
//     cout << "Sorted List (Ascending): ";
//     for (int num : sorted_lst_asc) {
//         cout << num << " ";
//     }
//     cout << endl;

//     // sort_list 함수 호출하여 리스트를 내림차순으로 정렬
//     vector<int> sorted_lst_desc = sort_list(lst, true);

//     // 내림차순 정렬된 리스트 출력
//     cout << "Sorted List (Descending): ";
//     for (int num : sorted_lst_desc) {
//         cout << num << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 내에서 특정 값을 가진 요소를 제거하는 함수
vector<int> remove_value(vector<int>& lst, int value) {
    vector<int> result;  // 결과를 저장할 벡터
    for (int num : lst) {  // 리스트의 각 요소를 확인
        if (num != value) {  // 값이 일치하지 않으면 결과에 추가
            result.push_back(num);
        }
    }
    return result;  // 특정 값을 제외한 리스트 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {1, 2, 3, 4, 5, 2, 6};

//     // remove_value 함수 호출하여 2를 제거한 리스트 구하기
//     vector<int> result_lst = remove_value(lst, 2);

//     // 결과 출력
//     cout << "List after removing 2: ";
//     for (int num : result_lst) {  // 결과 리스트의 각 요소 출력
//         cout << num << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 교집합을 구하는 함수
vector<int> intersection_of_lists(vector<int>& lst1, vector<int>& lst2) {
    vector<int> result;  // 교집합을 저장할 벡터
    for (int num : lst1) {  // 첫 번째 리스트의 각 요소를 확인
        for (int num2 : lst2) {  // 두 번째 리스트의 각 요소를 확인
            if (num == num2) {  // 두 리스트에서 같은 요소를 찾으면
                result.push_back(num);  // 교집합에 추가
                break;  // 두 번째 리스트에서 더 이상 찾을 필요가 없으므로 루프 종료
            }
        }
    }
    return result;  // 교집합 결과 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst1 = {1, 2, 3, 4, 5};
//     vector<int> lst2 = {3, 4, 5, 6, 7};

//     // intersection_of_lists 함수 호출하여 교집합 구하기
//     vector<int> result_lst = intersection_of_lists(lst1, lst2);

//     // 교집합 결과 출력
//     cout << "Intersection of lists: ";
//     for (int num : result_lst) {  // 교집합 리스트의 각 요소 출력
//         cout << num << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 합집합을 구하는 함수
vector<int> union_of_lists(vector<int>& lst1, vector<int>& lst2) {
    vector<int> result = lst1;  // 첫 번째 리스트를 결과 벡터에 추가
    for (int num : lst2) {  // 두 번째 리스트의 각 요소를 확인
        bool found = false;  // 해당 요소가 이미 결과에 있는지 확인하는 변수
        for (int existing_num : result) {  // 결과 리스트에서 이미 해당 요소가 있는지 확인
            if (num == existing_num) {
                found = true;  // 이미 존재하면 `found`를 true로 설정
                break;  // 더 이상 확인할 필요 없음
            }
        }
        if (!found) {  // 만약 결과에 없다면
            result.push_back(num);  // 해당 요소를 결과에 추가
        }
    }
    return result;  // 합집합 결과 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst1 = {1, 2, 3, 4, 5};
//     vector<int> lst2 = {3, 4, 5, 6, 7};

//     // union_of_lists 함수 호출하여 합집합 구하기
//     vector<int> result_lst = union_of_lists(lst1, lst2);

//     // 합집합 결과 출력
//     cout << "Union of lists: ";
//     for (int num : result_lst) {  // 합집합 리스트의 각 요소 출력
//         cout << num << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 차집합을 구하는 함수
vector<int> difference_of_lists(vector<int>& lst1, vector<int>& lst2) {
    vector<int> result;  // 차집합을 저장할 벡터
    for (int num : lst1) {  // 첫 번째 리스트의 각 요소를 확인
        bool found = false;  // 해당 요소가 두 번째 리스트에 있는지 확인하는 변수
        for (int num2 : lst2) {  // 두 번째 리스트의 각 요소를 확인
            if (num == num2) {  // 두 리스트에서 같은 요소가 있으면
                found = true;  // 해당 요소가 발견되었음을 나타내는 변수
                break;  // 더 이상 비교할 필요가 없으므로 루프 종료
            }
        }
        if (!found) {  // 두 번째 리스트에 해당 요소가 없다면
            result.push_back(num);  // 결과에 추가
        }
    }
    return result;  // 차집합 결과 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst1 = {1, 2, 3, 4, 5};
//     vector<int> lst2 = {3, 4, 5, 6, 7};

//     // difference_of_lists 함수 호출하여 차집합 구하기
//     vector<int> result_lst = difference_of_lists(lst1, lst2);

//     // 차집합 결과 출력
//     cout << "Difference of lists: ";
//     for (int num : result_lst) {  // 차집합 리스트의 각 요소 출력
//         cout << num << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 내의 숫자들의 합을 구하는 함수 (이전에 작성된 함수)
int sum_of_numbers_(vector<int>& lst) {
    int sum = 0;  // 합을 저장할 변수
    for (int num : lst) {  // 리스트의 각 요소를 순차적으로 확인
        sum += num;  // 요소를 합산
    }
    return sum;  // 합 반환
}

// 리스트의 평균을 구하는 함수
double average_of_list(vector<int>& lst) {
    if (lst.empty()) return 0.0;  // 리스트가 비어 있으면 0.0 반환
    return static_cast <double>(sum_of_numbers_(lst)) / lst.size();  // 합을 리스트의 크기로 나누어 평균 계산
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {1, 2, 3, 4, 5};

//     // average_of_list 함수 호출하여 리스트의 평균 구하기
//     double avg = average_of_list(lst);

//     // 결과 출력
//     cout << "Average of list: " << avg << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 내에서 최빈값을 찾는 함수
int mode_of_list(vector<int>& lst) {
    if (lst.empty()) return 0;  // 리스트가 비어 있으면 0 반환
    
    vector<int> unique_values;  // 리스트에서 고유한 값을 저장할 벡터
    vector<int> counts;  // 각 고유한 값의 빈도를 저장할 벡터

    for (int num : lst) {
        bool found = false;
        for (size_t i = 0; i < unique_values.size(); ++i) {
            if (num == unique_values[i]) {  // 이미 고유 값에 존재하는 경우
                ++counts[i];  // 해당 값의 빈도를 증가시킴
                found = true;
                break;
            }
        }
        if (!found) {  // 고유 값에 존재하지 않으면
            unique_values.push_back(num);  // 고유 값 리스트에 추가
            counts.push_back(1);  // 빈도 리스트에 빈도 1로 추가
        }
    }

    int mode = unique_values[0], max_count = counts[0];
    for (size_t i = 1; i < unique_values.size(); ++i) {
        if (counts[i] > max_count) {  // 빈도가 더 높은 값 찾기
            mode = unique_values[i];
            max_count = counts[i];
        }
    }

    return mode;  // 최빈값 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {1, 2, 2, 3, 3, 3, 4, 5};

//     // mode_of_list 함수 호출하여 최빈값 구하기
//     int mode = mode_of_list(lst);

//     // 결과 출력
//     cout << "Mode of list: " << mode << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 내 연속된 중복 요소를 제거하는 함수
vector<int> remove_consecutive_duplicates(vector<int>& lst) {
    if (lst.empty()) {
        return {};  // 리스트가 비어 있으면 빈 벡터를 반환
    }

    vector<int> result = { lst[0] };  // 첫 번째 요소는 결과 벡터에 추가

    for (size_t i = 1; i < lst.size(); ++i) {  // 두 번째 요소부터 확인
        if (lst[i] != lst[i - 1]) {  // 현재 요소가 이전 요소와 다르면
            result.push_back(lst[i]);  // 결과 벡터에 추가
        }
    }

    return result;  // 중복이 제거된 리스트 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {1, 1, 2, 2, 3, 3, 3, 4, 5, 5};

//     // remove_consecutive_duplicates 함수 호출하여 연속된 중복 제거
//     vector<int> result_lst = remove_consecutive_duplicates(lst);

//     // 결과 출력
//     cout << "List without consecutive duplicates: ";
//     for (size_t i = 0; i < result_lst.size(); ++i) {
//         cout << result_lst[i] << " ";  // 중복이 제거된 리스트의 요소 출력
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
#include <random> 
// 리스트 내 요소를 순서대로 무작위로 섞는 함수
vector<int> shuffle_list(vector<int> lst) {
    random_device rd;  // 난수 생성기를 위한 시드
    mt19937 g(rd());   // 메르센 트위스터 엔진 (고급 난수 생성기)

    for (size_t i = lst.size() - 1; i > 0; --i) {  // 리스트의 끝에서부터 시작
        uniform_int_distribution<size_t> dist(0, i);  // 0부터 i까지의 난수 생성
        swap(lst[i], lst[dist(g)]);  // 현재 인덱스와 무작위 인덱스를 교환
    }

    return lst;  // 섞인 리스트 반환
}

// int main() {
//     // 예시 리스트
//     vector<int> lst = {1, 2, 3, 4, 5};

//     // shuffle_list 함수 호출하여 리스트 섞기
//     vector<int> shuffled_lst = shuffle_list(lst);

//     // 섞인 리스트 출력
//     cout << "Shuffled list: ";
//     for (size_t i = 0; i < shuffled_lst.size(); ++i) {
//         cout << shuffled_lst[i] << " ";  // 섞인 리스트의 각 요소 출력
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
vector<int> slice(vector<int>& vec, int start, int end) {
    if (start > end || end > vec.size() || start < 0) {
        cerr << "Invalid start or end indices for slicing." << endl;
        return {};
    }
    return vector<int>(vec.begin() + start, vec.begin() + end);
}

// int main() {
//     // 벡터 초기화
//     vector<int> original = {1, 2, 3, 4, 5, 6, 7, 8, 9};

//     // 슬라이싱 사용
//     int start = 2;
//     int end = 6;
//     vector<int> sliced = slice(original, start, end);

//     // 결과 출력
//     cout << "Original vector: ";
//     for (int num : original) {
//         cout << num << " ";
//     }
//     cout << "\n";

//     cout << "Sliced vector: ";
//     for (int num : sliced) {
//         cout << num << " ";
//     }
//     cout << "\n";

//     return 0;
// }