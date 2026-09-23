from ihxnan import *

n, q = MII()

a = LII()

s = I()

lst = [0] * n

for i in range(n):
    if i == 0:
        lst[i] = a[i] if s[i] == "+" else -a[i]
    else:
        if s[i] == "+":
            lst[i] = lst[i - 1] + a[i]
        else:
            lst[i] = lst[i - 1] - a[i]

mi = [math.inf] * (n + 1)
for i in range(n - 1, -1, -1):
    mi[i] = min(mi[i + 1], lst[i])

flag = True

if mi[0] < 0:
    flag = False

sta = [0] * n
sta[0] = 1
for i in range(1, n):
    if sta[i - 1] and lst[i - 1] >= 0:
        sta[i] = 1

for _ in range(q):
    p, c = LI()
    p = int(p)
    if s[p - 1] == c:
        if flag:
            print("YES")
        else:
            print("NO")
    else:
        dif = 0
        if s[p - 1] == "+":
            dif = -2 * a[p - 1]
        else:
            dif = 2 * a[p - 1]

        if sta[p - 1]:
            if mi[p - 1] + dif >= 0:
                print("YES")
            else:
                print("NO")
        else:
            print("NO")
