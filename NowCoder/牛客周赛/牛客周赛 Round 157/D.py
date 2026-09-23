from ihxnan import *

n, k = MII()

lst = LII()

ans = 0
score = 0

choose = deque()

for it in lst:
    if len(choose) == 0:
        choose.append(it)
        ans = max(ans, len(choose))
    else:
        score += abs(choose[-1] - it)
        choose.append(it)
        if score <= k:
            ans = max(ans, len(choose))
        else:
            while score > k:
                x = choose.popleft()
                score -= abs(x - choose[0])
            ans = max(ans, len(choose))

print(ans)
