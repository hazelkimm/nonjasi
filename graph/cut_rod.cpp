#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int cutRod(const vector<int>& prices, int n) {
    if (n==0) {
        return 0;
    }

    vector<int>dp(n+1, INT_MIN);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i] = max(dp[i], prices[j]+dp[i-j]);
        }
    }

    return dp[n];
}

/*
prices가 {0, 2, 5, 7, 8}이고 n = 4라면:
prices[1] = 2, prices[2] = 5, prices[3] = 7, prices[4] = 8
dp[1] = max(dp[1], prices[1] + dp[0]) = max(INT_MIN, 2 + 0) = 2
dp[2] = max(dp[2], prices[1] + dp[1]) = max(INT_MIN, 2 + 2) = 4
dp[2] = max(dp[2], prices[2] + dp[0]) = max(4, 5 + 0) = 5
dp[3] = max(dp[3], prices[1] + dp[2]) = max(INT_MIN, 2 + 5) = 7
dp[3] = max(dp[3], prices[2] + dp[1]) = max(7, 5 + 2) = 7
dp[3] = max(dp[3], prices[3] + dp[0]) = max(7, 7 + 0) = 7
dp[4] = max(dp[4], prices[1] + dp[3]) = max(INT_MIN, 2 + 7) = 9
dp[4] = max(dp[4], prices[2] + dp[2]) = max(9, 5 + 5) = 10
dp[4] = max(dp[4], prices[3] + dp[1]) = max(10, 7 + 2) = 10
dp[4] = max(dp[4], prices[4] + dp[0]) = max(10, 8 + 0) = 10

*/

////////////// Top-down Approach ////////////

int memorizedCutRodAux(const vector<int>& prices, int n, vector<int>& memo) {
    //이미 메모이제이션 배열 memo에 n 길이의 막대에 대한 결과가 계산되어있다면 그 값 바로 반환
    if (memo[n] >= 0) {
        return memo[n];
    }

    int q;
    if (n == 0) { //길이가 0이면 수익이 0
        q = 0;
    } else {
        q = INT_MIN;
        for (int i=1; i<=n; i++) { //막대의 길이를 i로 잘라내고, 나머지 n-i를 자르는 최적 해 재귀적 계산
            q = max(q, prices[i]+memorizedCutRodAux(prices, n-i, memo));
        }
    }
    //계산된 최대 이익 q를 메모이제이션 배열에 저장하여, 이후에 동일한 길이에 대한 계산 피하기
    memo[n] = q;
    return q;
}


int memorizedCutRod(const vector<int>& prices, int n) {
    vector<int> memo(n + 1, INT_MIN);
    return memorizedCutRodAux(prices, n, memo);
}



////////////// Bottom-up Approach /////////////
int bottomUpCutRod(const vector<int>& prices, int n) {
    vector<int> dp(n+1, INT_MIN);
    dp[0] = 0;

    for (int j=1; j<=n; j++) {
        int q = INT_MIN;
        for (int i=1; i<=j; i++) {
            q = max(q, prices[i]+dp[j-i]);
        }
        dp[j] = q;
    }

    return dp[n];
}


///////////////Extended bottom up/////////////////
////////// maximum value 뿐만 아니라 list of piece sizes(optimal size of the first piece to cut off) 반환하기 ////////////
pair<vector<int>, vector<int>> extendedBottomUpCutRod(const vector<int>& prices, int n) {
    vector<int> dp(n+1, INT_MIN);
    vector<int> s(n+1);         //막대 자를 최적의 위치 저장하는 벡터

    dp[0] = 0;

    for (int j=1; j<=n; j++) {
        int q = INT_MIN;
        for (int i=1; i<=j; i++) {
            if (q < prices[i] + dp[j-i]) {     //만약 베스트 값을 자르면
                q = prices[i] + dp[j-i];        // 그걸로 value 업데이트 하고
                s[j] = i;                      // 거기서 자르기
            }
        }
        dp[j] = q;
    }
    return make_pair(dp, s);
}



// void printCutRodSolution(const vector<int>& prices, int n) {
//     pair<vector<int>, vector<int>> result = extendedBottomUpCutRod(prices, n);
//     const vector<int>& dp = result.first;
//     const vector<int>& s = result.second;

//     while (n > 0) {
//         cout << "Cut at length " << s[n] << " for a revenue of " << prices[s[n]] << endl;
//         n = n - s[n];
//     }
// }

void printCutRodSolution(const vector<int>& prices, int n) {
    pair<vector<int>, vector<int>> result = extendedBottomUpCutRod(prices, n);
    const vector<int>& dp = result.first;
    const vector<int>& s = result.second;

    cout << "Rod cutting solution for length " << n << ":\n";

    while (n > 0) {
        cout << "Cut a piece of length " << s[n] 
             << " (remaining length: " << n-s[n] << ") "
             << "to add a revenue of " << prices[s[n]] << endl;
        n = n - s[n];
    }

    cout << "Total revenue: " << dp[result.first.size() - 1] << endl;
}

/////////////////////////////////////////////////////
int main() {
    vector<int> prices = {0,1,5,8,9,10,17,17,20,24,30};
    int rodLength = 9;

    int maxRevenue = cutRod(prices, rodLength);
    cout << "[Naive] Maximum revenue for a rod of length " << rodLength << ": " << maxRevenue << endl;

    maxRevenue = memorizedCutRod(prices, rodLength);
    cout << "[Top-down] Maximum revenue for a rod of length " << rodLength << ": " << maxRevenue << endl;
    
    maxRevenue = bottomUpCutRod(prices, rodLength);
    cout << "[Bottom-up] Maximum revenue for a rod of length " << rodLength << ": " << maxRevenue << endl;
    
    cout << endl;
    printCutRodSolution(prices, rodLength);

    return 0;
}