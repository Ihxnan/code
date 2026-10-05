from ihxnan import *

n, m = MII()

mp = [[0] * m for _ in range(n)]

row = 0
idx = 0
for it in MII():
    while it > 0:
        it -= 1
        mp[row][idx] = 1
        idx = (idx + 1) % m
    row += 1

for i in range(n):
    print(''.join(map(str, mp[i])))

