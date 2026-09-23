from ihxnan import *

n, b = MII()

lst = []
for _ in range(n):
    lst.append(I())

out = []
for i in range(b):
    d = defaultdict(int)
    for it in lst:
        d[it[0:i] + it[i + 1 : b]] += 1
    res = 0
    for it in d.values():
        res += it * (it - 1) // 2
    out.append(res)

print(sum(out))
print(' '.join(map(str, out)))
