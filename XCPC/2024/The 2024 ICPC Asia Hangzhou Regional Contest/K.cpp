#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    int ans = 0;
    vi cnt(n + 1);
    for (int i = 1, t; i <= n * m; ++i)
    {
        cin >> t;
        if (m - ++cnt[gx(t)] <= k && !ans)
        {
            if (i <= m)
                ans = m;
            else
                ans = i;
        }
    }
    cout << ans << endl;
}
