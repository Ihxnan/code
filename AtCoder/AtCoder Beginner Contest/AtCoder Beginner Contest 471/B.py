from ihxnan import *

n = II()

d = defaultdict(int)

for i in range(n):
    s = I().lower()
    d[s] += 1

print(max(d.values()))
