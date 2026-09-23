from ihxnan import *

t = II()
outs = []

for _ in range(t):
    n = II()

    b = LII()
    ans = [-1] * n

    for i in range(n):
        if b[i] == 0:
            ans[i] = 1
        elif b[i] > 0:
            ans[i] = 0

    print(ans)

print("\n".join(outs))
