from ihxnan import *

n, d = MII()
s = I()
t = d
cnt = 0

for it in s:
    if it == "+":
        t = (t + 1) % 10
        if t == d:
            cnt += 1
    else:
        t = (t + 9) % 10
        if t == d:
            cnt += 1

print(t, cnt)
