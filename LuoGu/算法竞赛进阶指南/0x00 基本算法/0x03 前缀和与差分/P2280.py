import math
import sys
from collections import Counter, defaultdict, deque
from heapq import heapify, heappop, heappush

input = sys.stdin.readline
sys.setrecursionlimit(1000000)


def I():
    return input().strip()


def II():
    return int(input())


def MII():
    return map(int, input().split())


def LII():
    return list(map(int, input().split()))


def GMI():
    return map(lambda x: int(x) - 1, input().split())


def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))


n, m = MII()

sum = [[0] * 5005 for _ in range(5005)]

for i in range(n):
    x, y, v = MII()
    x += 1
    y += 1
    sum[x][y] += v

for i in range(1, 5005):
    for j in range(1, 5005):
        sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1]

ans = 0
for i in range(m, 5005):
    for j in range(m, 5005):
        ans = max(ans, sum[i][j] - sum[i - m][j] - sum[i][j - m] + sum[i - m][j - m])

print(ans)
