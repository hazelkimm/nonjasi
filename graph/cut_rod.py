import sys
#-sys.maxsize-1 는 cpp에서 INT_MIN과 동일함
def cutRod(prices, n: int):
    if n == 0:
        return 0

    dp = [-sys.maxsize-1 for i in range(n+1)]
    dp[0] = 0

    for i in range(1, n+1):
        for j in range(1, i+1):
            dp[i] = max(dp[i], prices[j]+dp[i-j])
    
    return dp[n]



####################### Top-down approach ########################
def memorizedCutRodAux(prices, n: int, memo):
    #이미 메모이제이션 배열 memo에 n 길이의 막대에 대한 결과가 계산되어있따면 그 값 바로 반환
    if memo[n] >= 0:
        return memo[n]
    
    if n == 0: # 길이가 0이면 수익이 0
        q = 0
    else:
        q = -sys.maxsize-1
        for i in range(1, n+1):  # 막대의 길이를 i로 잘라내고, 나머지 n-i를 자르는 최적 해 재귀적 계산
            q = max(q, prices[i]+memorizedCutRodAux(prices, n-i, memo))

    # 계산된 최대 이익 q를 메모이제이션 배열에 저장하여, 이후에 동일한 길이에 대한 계산 피하기
    memo[n] = q
    return q



def memorizedCutRod(prices, n: int):
    memo = [-sys.maxsize-1 for i in range(n+1)]
    return memorizedCutRodAux(prices, n, memo)




##################### Bottom-up Approach ###########################
def bottomUpCutRod(prices, n: int):
    dp = [-sys.maxsize-1 for i in range(n+1)]
    dp[0] = 0

    for j in range(1, n+1):
        q = -sys.maxsize-1
        for i in range(1, j+1):
            q = max(q, prices[i]+dp[j-i])
        dp[j] = q
    
    return dp[n]



######################### Extended bottom up ########################
################ maximum value 뿐만 아니라 list of piece sizes(optimal size of the first piece to cut off) 반환하기 ////////////

def extendedBottomUpCutRod(prices, n: int):
    dp = [-sys.maxsize-1 for i in range(n+1)]
    s = [None for i in range(n+1)]              # 막대 자를 최적의 위치 저장하는 벡터

    dp[0] = 0

    for j in range(1, n+1):
        q = -sys.maxsize-1
        for i in range(1, j+1):
            if q < prices[i] + dp[j-i]:          # 만약 베스트 값을 자르면
                q = prices[i] + dp[j-i]          # 그걸로 value 업데이트를 하고
                s[j] = i                         # 거기서 자르기
        dp[j] = q
    
    return dp, s

# def printCutRodSolution(prices, n: int):
#     dp, s = extendedBottomUpCutRod(prices, n)
#     while n > 0:
#         print("Cut at length", s[n], "for a revenue of", prices[s[n]])
#         n = n - s[n]

def printCutRodSolution(prices, n:int):
    dp, s = extendedBottomUpCutRod(prices, n)
    while n>0:
        print("Cut at length", s[n], "(remaining length", n-s[n], ")","to add a revenue of", prices[s[n]])
        n = n-s[n]





def main():
    prices = [0,1,5,8,9,10,17,17,20,24,30]
    rodLength = 9

    maxRevenue = cutRod(prices, rodLength)
    print("[Naive] Maximum revenue for a rod of length", rodLength, ":", maxRevenue)

    maxRevenue = memorizedCutRod(prices, rodLength)
    print("[Top-down] Maximum revenue for a rod of length", rodLength, ":", maxRevenue)

    maxRevenue = bottomUpCutRod(prices, rodLength)
    print("[Bottom-up] Maximum revenue for a rod of length", rodLength, ":", maxRevenue)

    printCutRodSolution(prices, rodLength)

if __name__ == '__main__':
    main()