from ihxnan import *

t = II()
for _ in range(t):
    n, k = MII()
    s = I()
    lst = []
    for i in range(k):
        lst.append(LII())

    x, y = 0, 0
    cnt = 0
    for it in s:
        if it == "U":
            x -= 1
        elif it == "D":
            x += 1
        elif it == "L":
            y -= 1
        elif it == "R":
            y += 1
        else:
            cnt += 1

        flag = False
        for it in lst:
            if abs(x - it[0]) + abs(y - it[1]) <= cnt:
                flag = True
                print("Yes")
                break

        if flag:
            break

    else:
        print("No")

