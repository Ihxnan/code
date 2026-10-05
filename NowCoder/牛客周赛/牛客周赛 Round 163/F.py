from ihxnan import *

n, q = MII()

trie = [[0] * 26 for _ in range(500005)]
end = [[0, 0] for _ in range(500005)]

tot = 0


def ins(s, c, idx, trie=trie, end=end):
    global tot
    cur = 0
    for it in s:
        x = ord(it) - 97
        if trie[cur][x] == 0:
            tot += 1
            trie[cur][x] = tot
        cur = trie[cur][x]
    end[cur] = [c, idx]


for i in range(1, n + 1):
    s, c = I().split()
    c = int(c)
    if c > 0:
        ins(s, c, i)


for _ in range(q):
    s = I()
    tar = 0
    cur = 0
    for it in s:
        x = ord(it) - 97
        if trie[cur][x] == 0:
            break
        cur = trie[cur][x]
        if end[cur][0] > 0:
            tar = cur
    if end[cur][0] > 0:
        tar = cur
    if end[tar][0] > 0:
        print(end[tar][1])
        end[tar][0] -= 1
    else:
        print(0)


