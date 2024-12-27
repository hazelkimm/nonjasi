/*
모든 부분 집합 구하기
-all_subsets1: 공집합 포함
-all_subsets2: 공집합 불포함
*/

#include <iostream>
#include <vector>

using namespace std;

void print_subset(const vector<int>& subset) {
    cout << "[";
    for (size_t i = 0; i < subset.size(); i++) {
        cout << subset[i];
        if (i < subset.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]\n";
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
void all_subsets1(const vector<int>& lst, vector<int>& subset, int index) {
    if (index == lst.size()) {
        print_subset(subset);
        return;
    }
    
    // 현재 원소를 포함하지 않는 부분 집합
    all_subsets1(lst, subset, index + 1);
    
    // 현재 원소를 포함하는 부분 집합
    subset.push_back(lst[index]);
    all_subsets1(lst, subset, index + 1);
    
    // 원소를 추가했던 상태를 되돌림
    subset.pop_back();
}

// int main() {
//     vector<int> lst = {1, 2, 3};
//     vector<int> subset;
    
//     all_subsets1(lst, subset, 0);
    
//     return 0;
// }


//////////////////////////////////////////////////////////////////////////////////////////////////////////
void all_subsets2(const vector<int>& lst, vector<int>& subset, int index) {
    if (index == lst.size()) {
        if (!subset.empty()) { // 빈 집합이 아닌 경우만 출력
            print_subset(subset);
        }
        return;
    }
    
    // 현재 원소를 포함하지 않는 부분 집합
    all_subsets2(lst, subset, index + 1);
    
    // 현재 원소를 포함하는 부분 집합
    subset.push_back(lst[index]);
    all_subsets2(lst, subset, index + 1);
    
    // 원소를 추가했던 상태를 되돌림
    subset.pop_back();
}

// int main() {
//     vector<int> lst = {1, 2, 3};
//     vector<int> subset;
    
//     all_subsets2(lst, subset, 0);
    
//     return 0;
// }