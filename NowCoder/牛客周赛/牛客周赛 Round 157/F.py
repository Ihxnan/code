from ihxnan import *

n, q = MII()

s = I()
lst = [-1]
for it in s:
    if it == "A":
        lst.append(0)
    elif it == "B":
        lst.append(1)
    else:
        lst.append(2)

ls = lambda x: x << 1
rs = lambda x: x << 1 | 1

tree = [[0, 0, 0] for _ in range(4 * n)]
lc = [0] * (4 * n)
rc = [0] * (4 * n)
lazy = [0] * (4 * n)


def push_up(p):
    for i in range(3):
        tree[p][i] = tree[ls(p)][i] + tree[rs(p)][i]

    if rc[ls(p)] == 0 and lc[rs(p)] == 0:
        tree[p][0] -= 1
    if rc[ls(p)] == 1 and lc[rs(p)] == 1:
        tree[p][1] -= 1
    if rc[ls(p)] == 2 and lc[rs(p)] == 2:
        tree[p][2] -= 1

    lc[p] = lc[ls(p)]
    rc[p] = rc[rs(p)]


def build(p, l, r):
    if l == r:
        if lst[l] == 0:
            tree[p][0] = 1
        elif lst[l] == 1:
            tree[p][1] = 1
        else:
            tree[p][2] = 1
        lc[p] = rc[p] = lst[l]
        return

    mid = l + r >> 1

    build(ls(p), l, mid)
    build(rs(p), mid + 1, r)

    push_up(p)


build(1, 1, n)


def change(p, l, r, k):

    lc[p] = (lc[p] + k) % 3
    rc[p] = (rc[p] + k) % 3

    tree[p][k % 3], tree[p][(k + 1) % 3], tree[p][(k + 2) % 3] = tree[p][0], tree[p][1], tree[p][2]

    lazy[p] += k


def push_down(p, l, r):
    if lazy[p]:
        mid = l + r >> 1
        change(ls(p), l, mid, lazy[p])
        change(rs(p), mid + 1, r, lazy[p])
        lazy[p] = 0


def update(ul, ur, p, l, r):
    if ul <= l and r <= ur:
        change(p, l, r, 1)
        return

    push_down(p, l, r)

    mid = l + r >> 1

    if ul <= mid:
        update(ul, ur, ls(p), l, mid)

    if ur > mid:
        update(ul, ur, rs(p), mid + 1, r)

    push_up(p)


def query(ql, qr, p, l, r):
    if ql <= l and r <= qr:
        return lc[p], tree[p][0], rc[p]

    push_down(p, l, r)

    mid = l + r >> 1

    tl = tr = 0

    llc = lrc = rlc = rrc = -1

    if ql <= mid:
        llc, tl, lrc = query(ql, qr, ls(p), l, mid)

    if qr > mid:
        rlc, tr, rrc = query(ql, qr, rs(p), mid + 1, r)

    ans = tl + tr

    if lrc == 0 and rlc == 0:
        ans -= 1

    return lc[p], ans, rc[p]


for _ in range(q):
    qr = LI()
    op = int(qr[0])
    if op == 1:
        update(int(qr[1]), int(qr[2]), 1, 1, n)
    else:
        print(tree[1][0])
