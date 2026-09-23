from ihxnan import *

n = II()
l = LII()

l1 = []
l2 = []
for it in l:
    if it < 0:
        l1.append(it)
    else:
        l2.append(it)

l1.sort(key=lambda x: -x)
l2.sort()
ans = i1 = i2 = cur = 0

while i1 < len(l1) and i2 < len(l2):
    if cur - l1[i1] <= l2[i2] - cur:
        ans += cur - l1[i1]
        cur = l1[i1]
        i1 += 1
    else:
        ans += l2[i2] - cur
        cur = l2[i2]
        i2 += 1

while i1 < len(l1):
    ans += cur - l1[i1]
    cur = l1[i1]
    i1 += 1

while i2 < len(l2):
    ans += l2[i2] - cur
    cur = l2[i2]
    i2 += 1

print(ans)
