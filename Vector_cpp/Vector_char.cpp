/*
1. 리스트 합치기: vector<char> merge_lists(vector<vector<char>>& lists)
2. 중복 요소 제거: vector<char> remove_duplicates(vector<char>& lst)
3. 리스트 회전: vector<char> rotate_list(vector<char>& lst, int k)
4. 요소 빈도수 계산: int count_element(vector<char>& lst, char element)
5. 리스트 뒤집기: vector<char> reverse_list(vector<char>& lst)
6. 요소 인덱스 찾기: int find_element_index(vector<char>& lst, char element)
7. 조건에 맞는 요소 필터링: vector<char> filter_list(vector<char>& lst, Func condition_func)
8. 서브리스트 추출: vector<vector<char>> find_sublists(vector<char>& lst, int length)
9. 리스트 정렬: vector<char> sort_list(vector<char> lst, bool descending = false)
10. 특정 값 제거: vector<char> remove_value(vector<char>& lst, char value)
11. 교집합 구하기: vector<char> intersection_of_lists(vector<char>& lst1, vector<char>& lst2)
12. 합집합 구하기: vector<char> union_of_lists(vector<char>& lst1, vector<char>& lst2)
13. 차집합 구하기: vector<char> difference_of_lists(vector<char>& lst1, vector<char>& lst2)
14. 최빈값 찾기: char mode_of_list(vector<char>& lst)
15. 연속된 중복 요소 제거: vector<char> remove_consecutive_duplicates(vector<char>& lst)
16. 리스트 섞기: vector<char> shuffle_list(vector<char> lst)
17. 슬라이싱: vector<char> slice(vector<char>& vec, int start, int end)
*/


#include <iostream>
#include <vector>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////
// 여러 리스트를 합치는 함수
vector<char> merge_lists(vector<vector<char>>& lists) {
    vector<char> merged;
    for (vector<char>& list : lists) {  // 각 리스트를 순차적으로 합칩니다.
        merged.insert(merged.end(), list.begin(), list.end());
    }
    return merged;  // 합쳐진 리스트 반환
}

// int main() {
//     // 예시 리스트들
//     vector<vector<char>> lists = {
//         {'a', 'b', 'c'},
//         {'d', 'e'},
//         {'f', 'g', 'h', 'i'}
//     };

//     // merge_lists 함수 호출하여 리스트 합치기
//     vector<char> merged = merge_lists(lists);

//     // 합쳐진 리스트 출력
//     cout << "Merged List: ";
//     for (char ch : merged) {  // 합쳐진 리스트의 각 요소 출력
//         cout << ch << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트에서 중복된 요소를 제거하는 함수
vector<char> remove_duplicates(vector<char>& lst) {
    vector<char> unique_lst;
    for (char ch : lst) {
        bool found = false;
        // 이미 unique_lst에 ch가 있는지 확인
        for (char unique_ch : unique_lst) {
            if (ch == unique_ch) {
                found = true;
                break;  // 중복이 있으면 더 이상 확인할 필요 없음
            }
        }
        if (!found) {
            unique_lst.push_back(ch);  // 중복이 없으면 unique_lst에 추가
        }
    }
    return unique_lst;  // 중복이 제거된 리스트 반환
}

// int main() {
//     // 예시 리스트
//     vector<char> lst = {'a', 'b', 'b', 'c', 'd', 'd', 'e'};

//     // remove_duplicates 함수 호출하여 중복 제거
//     vector<char> unique_lst = remove_duplicates(lst);

//     // 중복이 제거된 리스트 출력
//     cout << "Unique List: ";
//     for (char ch : unique_lst) {  // 중복이 제거된 리스트의 각 요소 출력
//         cout << ch << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트를 k만큼 회전시키는 함수
vector<char> rotate_list(vector<char>& lst, int k) {
    int n = lst.size();  // 리스트의 크기
    if (n == 0) return lst;  // 리스트가 비어있으면 그대로 반환
    k %= n;  // k가 리스트 길이보다 클 수 있으므로, k를 리스트 크기로 나눈 나머지로 조정
    vector<char> rotated(lst.begin() + k, lst.end());  // k번째부터 끝까지 잘라서 새로운 벡터에 저장
    rotated.insert(rotated.end(), lst.begin(), lst.begin() + k);  // 앞부분을 뒤에 추가하여 회전 효과
    return rotated;  // 회전된 리스트 반환
}

// int main() {
//     // 예시 리스트
//     vector<char> lst = {'a', 'b', 'c', 'd', 'e'};

//     // rotate_list 함수 호출하여 리스트를 회전시킴
//     vector<char> rotated_lst = rotate_list(lst, 2);

//     // 회전된 리스트 출력
//     cout << "Rotated List: ";
//     for (char ch : rotated_lst) {  // 회전된 리스트의 각 요소 출력
//         cout << ch << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트에서 주어진 요소의 빈도수를 반환하는 함수
int count_element(vector<char>& lst, char element) {
    int count = 0;  // 요소의 빈도수를 세기 위한 변수
    for (char ch : lst) {  // 리스트의 각 요소를 확인
        if (ch == element) {  // 요소가 일치하면 빈도수 증가
            ++count;
        }
    }
    return count;  // 요소의 빈도수 반환
}

// int main() {
//     // 예시 리스트
//     vector<char> lst = {'a', 'b', 'c', 'b', 'b', 'd', 'e'};

//     // count_element 함수 호출하여 'b'의 빈도수를 찾기
//     int count = count_element(lst, 'b');

//     // 결과 출력
//     cout << "Element 'b' appears " << count << " times." << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트의 순서를 뒤집는 함수
vector<char> reverse_list(vector<char>& lst) {
    vector<char> reversed(lst.rbegin(), lst.rend());  // 리스트를 뒤집어서 새로운 벡터에 저장
    return reversed;  // 뒤집힌 리스트 반환
}

// // 리스트의 순서를 뒤집는 함수 (직접 구현)
// vector<char> reverse_list(vector<char>& lst) {
//     vector<char> reversed;  // 빈 벡터를 생성

//     // 리스트를 뒤에서부터 하나씩 새 벡터에 추가
//     for (int i = lst.size() - 1; i >= 0; i--) {
//         reversed.push_back(lst[i]);
//     }

//     return reversed;  // 뒤집힌 리스트 반환
// }

// int main() {
//     // 예시 리스트
//     vector<char> lst = {'a', 'b', 'c', 'd', 'e'};

//     // reverse_list 함수 호출하여 리스트 순서 뒤집기
//     vector<char> reversed_lst = reverse_list(lst);

//     // 뒤집힌 리스트 출력
//     cout << "Reversed List: ";
//     for (char ch : reversed_lst) {  // 뒤집힌 리스트의 각 요소 출력
//         cout << ch << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트에서 주어진 요소의 인덱스를 반환하는 함수
int find_element_index(vector<char>& lst, char element) {
    for (size_t i = 0; i < lst.size(); ++i) {  // 리스트의 각 요소를 순차적으로 확인
        if (lst[i] == element) {  // 요소가 일치하면 인덱스 반환
            return i;
        }
    }
    return -1;  // 요소가 없으면 -1을 반환
}

// int main() {
//     // 예시 리스트
//     vector<char> lst = {'a', 'b', 'c', 'd', 'e'};

//     // find_element_index 함수 호출하여 'c'의 인덱스 찾기
//     int index = find_element_index(lst, 'c');

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
vector<char> filter_list(vector<char>& lst, Func condition_func) {
    vector<char> result;  // 조건에 맞는 요소를 저장할 벡터
    for (char ch : lst) {  // 리스트의 각 요소를 순차적으로 확인
        if (condition_func(ch)) {  // 조건 함수가 참이면
            result.push_back(ch);  // 해당 요소를 결과 벡터에 추가
        }
    }
    return result;  // 조건에 맞는 요소들만 반환
}

// int main() {
//     // 예시 리스트
//     vector<char> lst = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

//     // filter_list 함수 호출하여 모음만 필터링
//     vector<char> vowels = filter_list(lst, [](char ch) { 
//         return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'; 
//     });

//     // 필터링된 리스트 출력
//     cout << "Filtered List (Vowels): ";
//     for (char ch : vowels) {  // 필터링된 리스트의 각 요소 출력
//         cout << ch << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트에서 연속된 서브리스트를 반환하는 함수
vector<vector<char>> find_sublists(vector<char>& lst, int length) {
    vector<vector<char>> sublists;  // 결과로 반환할 서브리스트들을 저장할 벡터
    for (size_t i = 0; i <= lst.size() - length; ++i) {  // 리스트의 연속된 부분을 확인
        sublists.push_back(vector<char>(lst.begin() + i, lst.begin() + i + length));  // 서브리스트 추가
    }
    return sublists;  // 서브리스트들 반환
}

// int main() {
//     // 예시 리스트
//     vector<char> lst = {'a', 'b', 'c', 'd', 'e'};

//     // find_sublists 함수 호출하여 서브리스트 길이 3으로 찾기
//     vector<vector<char>> sublists = find_sublists(lst, 3);

//     // 서브리스트 출력
//     cout << "Sublists: " << endl;
//     for (const vector<char>& sublist : sublists) {  // 각 서브리스트 출력
//         for (char ch : sublist) {
//             cout << ch << " ";
//         }
//         cout << endl;
//     }

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트를 오름차순 또는 내림차순으로 정렬하는 함수
vector<char> sort_list(vector<char> lst, bool descending = false) {
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
//     vector<char> lst = {'e', 'b', 'd', 'a', 'c'};

//     // sort_list 함수 호출하여 리스트를 오름차순으로 정렬
//     vector<char> sorted_lst_asc = sort_list(lst);

//     // 오름차순 정렬된 리스트 출력
//     cout << "Sorted List (Ascending): ";
//     for (char ch : sorted_lst_asc) {
//         cout << ch << " ";
//     }
//     cout << endl;

//     // sort_list 함수 호출하여 리스트를 내림차순으로 정렬
//     vector<char> sorted_lst_desc = sort_list(lst, true);

//     // 내림차순 정렬된 리스트 출력
//     cout << "Sorted List (Descending): ";
//     for (char ch : sorted_lst_desc) {
//         cout << ch << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 내에서 특정 값을 가진 요소를 제거하는 함수
vector<char> remove_value(vector<char>& lst, char value) {
    vector<char> result;  // 결과를 저장할 벡터
    for (char ch : lst) {  // 리스트의 각 요소를 확인
        if (ch != value) {  // 값이 일치하지 않으면 결과에 추가
            result.push_back(ch);
        }
    }
    return result;  // 특정 값을 제외한 리스트 반환
}

// int main() {
//     // 예시 리스트
//     vector<char> lst = {'a', 'b', 'c', 'd', 'e', 'b', 'f'};

//     // remove_value 함수 호출하여 'b'를 제거한 리스트 구하기
//     vector<char> result_lst = remove_value(lst, 'b');

//     // 결과 출력
//     cout << "List after removing 'b': ";
//     for (char ch : result_lst) {  // 결과 리스트의 각 요소 출력
//         cout << ch << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 교집합을 구하는 함수
vector<char> intersection_of_lists(vector<char>& lst1, vector<char>& lst2) {
    vector<char> result;  // 교집합을 저장할 벡터
    for (char ch : lst1) {  // 첫 번째 리스트의 각 요소를 확인
        for (char ch2 : lst2) {  // 두 번째 리스트의 각 요소를 확인
            if (ch == ch2) {  // 두 리스트에서 같은 요소를 찾으면
                result.push_back(ch);  // 교집합에 추가
                break;  // 두 번째 리스트에서 더 이상 찾을 필요가 없으므로 루프 종료
            }
        }
    }
    return result;  // 교집합 결과 반환
}

// int main() {
//     // 예시 리스트
//     vector<char> lst1 = {'a', 'b', 'c', 'd', 'e'};
//     vector<char> lst2 = {'c', 'd', 'e', 'f', 'g'};

//     // intersection_of_lists 함수 호출하여 교집합 구하기
//     vector<char> result_lst = intersection_of_lists(lst1, lst2);

//     // 교집합 결과 출력
//     cout << "Intersection of lists: ";
//     for (char ch : result_lst) {  // 교집합 리스트의 각 요소 출력
//         cout << ch << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 합집합을 구하는 함수
vector<char> union_of_lists(vector<char>& lst1, vector<char>& lst2) {
    vector<char> result = lst1;  // 첫 번째 리스트를 결과 벡터에 추가
    for (char ch : lst2) {  // 두 번째 리스트의 각 요소를 확인
        bool found = false;  // 해당 요소가 이미 결과에 있는지 확인하는 변수
        for (char existing_ch : result) {  // 결과 리스트에서 이미 해당 요소가 있는지 확인
            if (ch == existing_ch) {
                found = true;  // 이미 존재하면 `found`를 true로 설정
                break;  // 더 이상 확인할 필요 없음
            }
        }
        if (!found) {  // 만약 결과에 없다면
            result.push_back(ch);  // 해당 요소를 결과에 추가
        }
    }
    return result;  // 합집합 결과 반환
}

// int main() {
//     // 예시 리스트
//     vector<char> lst1 = {'a', 'b', 'c', 'd', 'e'};
//     vector<char> lst2 = {'c', 'd', 'e', 'f', 'g'};

//     // union_of_lists 함수 호출하여 합집합 구하기
//     vector<char> result_lst = union_of_lists(lst1, lst2);

//     // 합집합 결과 출력
//     cout << "Union of lists: ";
//     for (char ch : result_lst) {  // 합집합 리스트의 각 요소 출력
//         cout << ch << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 차집합을 구하는 함수
vector<char> difference_of_lists(vector<char>& lst1, vector<char>& lst2) {
    vector<char> result;  // 차집합을 저장할 벡터
    for (char ch : lst1) {  // 첫 번째 리스트의 각 요소를 확인
        bool found = false;  // 해당 요소가 두 번째 리스트에 있는지 확인하는 변수
        for (char ch2 : lst2) {  // 두 번째 리스트의 각 요소를 확인
            if (ch == ch2) {  // 두 리스트에서 같은 요소가 있으면
                found = true;  // 해당 요소가 발견되었음을 나타내는 변수
                break;  // 더 이상 비교할 필요가 없으므로 루프 종료
            }
        }
        if (!found) {  // 두 번째 리스트에 해당 요소가 없다면
            result.push_back(ch);  // 결과에 추가
        }
    }
    return result;  // 차집합 결과 반환
}

// int main() {
//     // 예시 리스트
//     vector<char> lst1 = {'a', 'b', 'c', 'd', 'e'};
//     vector<char> lst2 = {'c', 'd', 'e', 'f', 'g'};

//     // difference_of_lists 함수 호출하여 차집합 구하기
//     vector<char> result_lst = difference_of_lists(lst1, lst2);

//     // 차집합 결과 출력
//     cout << "Difference of lists: ";
//     for (char ch : result_lst) {  // 차집합 리스트의 각 요소 출력
//         cout << ch << " ";
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 내에서 최빈값을 찾는 함수
char mode_of_list(vector<char>& lst) {
    if (lst.empty()) return '\0';  // 리스트가 비어 있으면 널 문자('\0') 반환

    vector<char> unique_values;  // 리스트에서 고유한 값을 저장할 벡터
    vector<int> counts;  // 각 고유한 값의 빈도를 저장할 벡터

    for (char ch : lst) {
        bool found = false;
        for (size_t i = 0; i < unique_values.size(); ++i) {
            if (ch == unique_values[i]) {  // 이미 고유 값에 존재하는 경우
                ++counts[i];  // 해당 값의 빈도를 증가시킴
                found = true;
                break;
            }
        }
        if (!found) {  // 고유 값에 존재하지 않으면
            unique_values.push_back(ch);  // 고유 값 리스트에 추가
            counts.push_back(1);  // 빈도 리스트에 빈도 1로 추가
        }
    }

    char mode = unique_values[0];  // 첫 번째 고유값을 초기 최빈값으로 설정
    int max_count = counts[0];  // 첫 번째 고유값의 빈도를 초기 최빈값의 빈도로 설정

    // 최빈값을 찾기 위해 리스트를 순차적으로 비교
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
//     vector<char> lst = {'a', 'b', 'c', 'c', 'b', 'b', 'a', 'a'};

//     // mode_of_list 함수 호출하여 최빈값 구하기
//     char mode = mode_of_list(lst);

//     // 결과 출력
//     cout << "Mode of list: " << mode << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 리스트 내 연속된 중복 요소를 제거하는 함수 (char 타입)
vector<char> remove_consecutive_duplicates(vector<char>& lst) {
    if (lst.empty()) {
        return {};  // 리스트가 비어 있으면 빈 벡터를 반환
    }

    vector<char> result = { lst[0] };  // 첫 번째 요소는 결과 벡터에 추가

    for (size_t i = 1; i < lst.size(); ++i) {  // 두 번째 요소부터 확인
        if (lst[i] != lst[i - 1]) {  // 현재 요소가 이전 요소와 다르면
            result.push_back(lst[i]);  // 결과 벡터에 추가
        }
    }

    return result;  // 중복이 제거된 리스트 반환
}

// int main() {
//     // 예시 리스트 (char 타입)
//     vector<char> lst = {'a', 'a', 'b', 'b', 'c', 'c', 'c', 'd', 'e', 'e'};

//     // remove_consecutive_duplicates 함수 호출하여 연속된 중복 제거
//     vector<char> result_lst = remove_consecutive_duplicates(lst);

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
// 리스트 내 요소를 순서대로 무작위로 섞는 함수 (char 타입)
vector<char> shuffle_list(vector<char> lst) {
    random_device rd;  // 난수 생성기를 위한 시드
    mt19937 g(rd());   // 메르센 트위스터 엔진 (고급 난수 생성기)

    // 리스트의 끝에서부터 시작하여 무작위로 인덱스를 교환
    for (size_t i = lst.size() - 1; i > 0; --i) {
        uniform_int_distribution<size_t> dist(0, i);  // 0부터 i까지의 난수 생성
        swap(lst[i], lst[dist(g)]);  // 현재 인덱스와 무작위 인덱스를 교환
    }

    return lst;  // 섞인 리스트 반환
}

// int main() {
//     // 예시 리스트 (char 타입)
//     vector<char> lst = {'a', 'b', 'c', 'd', 'e'};

//     // shuffle_list 함수 호출하여 리스트 섞기
//     vector<char> shuffled_lst = shuffle_list(lst);

//     // 섞인 리스트 출력
//     cout << "Shuffled list: ";
//     for (size_t i = 0; i < shuffled_lst.size(); ++i) {
//         cout << shuffled_lst[i] << " ";  // 섞인 리스트의 각 요소 출력
//     }
//     cout << endl;

//     return 0;
// }


/////////////////////////////////////////////////////////////////////////////////////////////////
// 벡터에서 start부터 end까지의 범위를 슬라이싱하는 함수
vector<char> slice(vector<char>& vec, int start, int end) {
    // 유효한 인덱스인지 확인
    if (start > end || end > vec.size() || start < 0) {
        cerr << "Invalid start or end indices for slicing." << endl;
        return {};  // 잘못된 인덱스가 입력되면 빈 벡터 반환
    }
    // 벡터의 start부터 end까지 범위로 서브 벡터 반환
    return vector<char>(vec.begin() + start, vec.begin() + end);
}

// int main() {
//     // 예시 벡터 초기화 (문자형 벡터)
//     vector<char> original = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

//     // 슬라이싱 사용
//     int start = 2;  // 시작 인덱스
//     int end = 6;    // 종료 인덱스
//     vector<char> sliced = slice(original, start, end);

//     // 원본 벡터 출력
//     cout << "Original vector: ";
//     for (char ch : original) {
//         cout << ch << " ";  // 원본 벡터의 각 문자 출력
//     }
//     cout << "\n";

//     // 슬라이스된 벡터 출력
//     cout << "Sliced vector: ";
//     for (char ch : sliced) {
//         cout << ch << " ";  // 슬라이스된 벡터의 각 문자 출력
//     }
//     cout << "\n";

//     return 0;
// }