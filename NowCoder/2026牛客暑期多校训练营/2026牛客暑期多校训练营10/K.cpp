#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    int peo = 3 * n;
    vvi mp(peo, vi(peo));
    for (auto &p : mp)
        for (auto &q : p)
            cin >> q;

    vl dp(1 << peo, -lINF);
    dp[0] = 0;
    dp[7] = mp[0][1] + mp[0][2] + mp[1][2];

    int S = 1 << peo;

    for (int mask = 1; mask < S; ++mask)
    {
        if (__builtin_popcount((unsigned)mask) % 3)
            continue;
        int p = __builtin_ctz((unsigned)mask);
        int rest = mask ^ (1 << p);
        int base = mask ^ (1 << p);
        for (int q = rest; q; q &= q - 1)
        {
            int qb = __builtin_ctz((unsigned)q);
            int rest2 = rest & ~((1u << (qb + 1)) - 1);
            for (int r = rest2; r; r &= r - 1)
            {
                int rb = __builtin_ctz((unsigned)r);
                ll val = dp[base ^ (1 << qb) ^ (1 << rb)] + mp[p][qb] + mp[p][rb] + mp[qb][rb];
                if (val > dp[mask])
                    dp[mask] = val;
            }
        }
    }

    cout << dp.back() << endl;
}
