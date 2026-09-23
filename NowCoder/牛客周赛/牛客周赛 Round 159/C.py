from ihxnan import *

m, q, b = MII()

lst = LII()

s = [0] * (m + 1)
s[0] = lst[0]
for i in range(1, m):
    s[i] = s[i - 1] + lst[i]

out = []
for _ in range(q):
    t = II()
    l = -1
    r = m
    while l + 1 < r:
        mid = l + r >> 1
        if s[mid] >= t:
            r = mid
        else:
            l = mid
    print(b ^ r & 1, r + 1, t - s[r - 1])
