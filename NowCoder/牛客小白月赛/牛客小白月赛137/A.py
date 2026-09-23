from ihxnan import *

n = II()

if n <= 2:
    print("No")
else:
    lst = [1, 5, 2]
    for i in range(n - 3):
        lst.append(0)
    print("".join(map(str, lst)))

