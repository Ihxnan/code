#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> n >> m;
    vi cnt(2 * m + 1);
    for (int i = 0, t; i < n; ++i)
        cin >> t, ++cnt[t];

    vi suf(m + 2);
    for (int i = m; i >= 1; --i)
        suf[i] = cnt[i] + suf[i + 1];

    int ans = 0;
    for (int i = 1; i <= m; ++i)
        ans = max(ans, cnt[i] + cnt[2 * i] + suf[i + 1]);

    cout << ans << endl;
}
