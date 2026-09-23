from ihxnan import *

n, m = MII()
s = I()
lst = []
for it in s:
    lst.append(int(it))

cnt = 0
for i in range(10):
    lst = [(int(it) + i) % 10 for it in s]
    if int("".join(map(str, lst))) % m == 0:
        cnt += 1

print(cnt)
