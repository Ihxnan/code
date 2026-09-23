from ihxnan import *

t = II()
for _ in range(t):
    n, k = MII()
    lst = LII()

    ans = 0
    for i in range(1, len(lst)):
        ans = max(ans, (lst[i] - lst[i - 1]) // 2)

    ans = max(ans, lst[0] - 1, n - lst[-1])
    print(ans)

