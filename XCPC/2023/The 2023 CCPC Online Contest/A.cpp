#include <ihxnan>
#include <StrHash>

void solve()
{
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    s = '1' + s + '2', t = '3' + t + '4';
    StrHash hs(s), ht(t);

    auto lower = [&](int i1, int i2) -> int {
        if (i1 > n || i2 > m)
            return 0;
        int l = -1, r = min(n - i1, m - i2) + 1, mid;
        while (l + 1 < r)
        {
            mid = l + r >> 1;
            if (hs.get(i1, i1 + mid) == ht.get(i2, i2 + mid))
                l = mid;
            else
                r = mid;
        }
        return r;
    };

    vi nxt(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        int i1 = i, i2 = 1;
        int step = lower(i1, i2);
        i1 += step, i2 += step;
        if (i1 > n || i2 > m)
            nxt[i] = i1;
        else
        {
            ++i1, ++i2;
            i1 += lower(i1, i2);
            nxt[i] = i1;
        }
    }

    vl sum(n + 3);
    sum[n + 1] = 1;
    for (int i = n; i > 0; --i)
        sum[i] = 2 * sum[i + 1] - sum[nxt[i] + 1];

    vl arr(n + 3);


    vvl memo(n + 2, vl(n + 2, -1));
    auto dfs = [&](auto &&self, int pos, ll zu) -> ll {
        if (memo[pos][zu] != -1)
            return memo[pos][zu];

        if (pos > n)
            return memo[pos][zu] = zu * zu % mod;

        ll res = 0;
        for (int i = pos; i < nxt[pos]; ++i)
            res = (res + self(self, i + 1, zu + 1)) % mod;
        return memo[pos][zu] = res;
    };

    cout << dfs(dfs, 1, 0) << endl;
}
