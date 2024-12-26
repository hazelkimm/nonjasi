#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cutRod(const int prices[], int n) {
    if (n == 0) {
        return 0;
    }

    int *dp = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        dp[i] = INT_MIN;
    }
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i] = (dp[i] > prices[j] + dp[i - j]) ? dp[i] : (prices[j] + dp[i - j]);
        }
    }

    int result = dp[n];
    free(dp);
    return result;
}


////////////////// Top-down Approach /////////////////////////
int memorizedCutRodAux(const int prices[], int n, int memo[]) {
//이미 메모이제이션 배열 memo에 n 길이의 막대에 대한 결과가 계산되어있다면 그 값 바로 반환
    if (memo[n] >= 0) {
        return memo[n];
    }

    int q;
    if (n == 0) {        // 길이가 0이면 수익이 0
        q = 0;
    } else {
        q = INT_MIN;
        for (int i = 1; i <= n; i++) {    //막대의 길이를 i로 잘라내고, 나머지 n-i를 자르는 최적 해 재귀적 계산
            q = (q > prices[i] + memorizedCutRodAux(prices, n - i, memo)) ? q : (prices[i] + memorizedCutRodAux(prices, n - i, memo));
        }
    }

    //계산된 최대 이익 q를 메모이제이션 배열에 저장하여, 이후에 동일한 길이에 대한 계산 피하기
    memo[n] = q;
    return q;
}

int memorizedCutRod(const int prices[], int n) {
    int *memo = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        memo[i] = INT_MIN;
    }

    int result = memorizedCutRodAux(prices, n, memo);
    free(memo);
    return result;
}




////////////// Bottom-up Approach /////////////
int bottomUpCutRod(const int prices[], int n) {
    int *dp = (int*)malloc((n + 1) * sizeof(int));
    dp[0] = 0;

    for (int j = 1; j <= n; j++) {
        int q = INT_MIN;
        for (int i = 1; i <= j; i++) {
            q = (q > prices[i] + dp[j - i]) ? q : (prices[i] + dp[j - i]);
        }
        dp[j] = q;
    }

    int result = dp[n];
    free(dp);
    return result;
}




///////////////Extended bottom up/////////////////
////////// maximum value 뿐만 아니라 list of piece sizes(optimal size of the first piece to cut off) 반환하기 ////////////
void extendedBottomUpCutRod(const int prices[], int n, int **dp, int **s) {
    *dp = (int*)malloc((n + 1) * sizeof(int));
    *s = (int*)malloc((n + 1) * sizeof(int));             //막대 자를 최적의 위치 저장하는 벡터

    for (int i = 0; i <= n; i++) { 
        (*dp)[i] = INT_MIN;
    }
    (*dp)[0] = 0;

    for (int j = 1; j <= n; j++) {
        int q = INT_MIN;
        for (int i = 1; i <= j; i++) {
            if (q < prices[i] + (*dp)[j - i]) {                   //만약 베스트 값을 자르면
                q = prices[i] + (*dp)[j - i];                     // 그걸로 value 업데이트 하고
                (*s)[j] = i;                                      // 거기서 자르기
            }
        } 
        (*dp)[j] = q;
    }
}

void printCutRodSolution(const int prices[], int n) {
    int *dp, *s;
    extendedBottomUpCutRod(prices, n, &dp, &s);

    while (n > 0) {
        printf("Cut at length %d (remaining length %d) to add a revenue of %d\n", s[n], n-s[n], prices[s[n]]);
        n = n - s[n];
    }

    free(dp);
    free(s);
}







int main() {
    int prices[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int rodLength = 9;

    int maxRevenue = cutRod(prices, rodLength);
    printf("[Naive] Maximum revenue for a rod of length %d: %d\n", rodLength, maxRevenue);

    maxRevenue = memorizedCutRod(prices, rodLength);
    printf("[Top-down] Maximum revenue for a rod of length %d: %d\n", rodLength, maxRevenue);

    maxRevenue = bottomUpCutRod(prices, rodLength);
    printf("[Bottom-up] Maximum revenue for a rod of length %d: %d\n", rodLength, maxRevenue);

    printf("\n");
    printCutRodSolution(prices, rodLength);

    return 0;
}
