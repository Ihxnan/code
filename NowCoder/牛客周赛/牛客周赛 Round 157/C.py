from ihxnan import *

n = II()

f = {}
b = {}

lst = LII()

for i in range(n):
    if lst[i] not in f:
        f[lst[i]] = i
    if lst[n - 1 - i] not in b:
        b[lst[n - 1 - i]] = n - 1 - i

cnt = 0
for x, l in f.items():
    if b[x] != l and (b[x] - l) % 2 == 0:
        cnt += 1
print(cnt)
