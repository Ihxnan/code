from ihxnan import *

q, v = MII()
l = []
for _ in range(q):
    query = LII()
    if query[0] == 1:
        t = query[1]
        w = query[2]
        heappush(l, t - w)
    else:
        t = query[1]
        if len(l) == 0:
            print(-1)
        else:
            w0 = -heappop(l)
            print(min(w0 + t, v))
