from ihxnan import *

n = II()
alice = LII()
bob = LII()
per = []
tmp = []


def dfs(pos):
    if pos > n:
        per.append(tmp[:])
        return
    for i in range(n):
        if i not in tmp:
            tmp.append(i)
            dfs(pos + 1)
            tmp.pop()


dfs(1)


flag = False


def check(p1, p2):
    for i in range(n):
        if math.gcd(alice[p1[i]], bob[p2[i]]) > 1:
            return False
    return True


for p1 in per:
    for p2 in per:
        if check(p1, p2):
            break
    else:
        flag = True

print("Alice" if flag else "Bob")
