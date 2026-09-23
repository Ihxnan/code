from ihxnan import *

t = II()

for _ in range(t):

    n = II()

    if n < 6:
        print("No")
        continue

    l2 = [i for i in range(1, n + 1) if i % 2 == 0 and i % 3 != 0]
    l3 = [i for i in range(n, 0, -1) if i % 3 == 0]

    l3[-1], l3[-2] = l3[-2], l3[-1]

    p1 = l3 + l2

    p2 = p1[::-1]

    while len(p2) + len(p1) > n + 1:
        p2.pop()

    if len(p2) + len(p1) != n + 1:
        print("No")
        continue

    for i in range(1, n + 1):
        if i % 2 != 0 and i % 3 != 0:
            p1.append(i)

    st = set(p2)

    p2 = p2[::-1]
    for i in range(1, n + 1):
        if i not in st:
            p2.append(i)

    print("Yes")
    print(" ".join(map(str, p1)))
    print(" ".join(map(str, p2[::-1])))

