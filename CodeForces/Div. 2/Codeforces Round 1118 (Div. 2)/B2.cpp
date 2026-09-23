#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    ll n, m;
    cin >> n >> m;
    vl cnt(2 * m + 1);
    for (int i = 0, t; i < n; ++i)
        cin >> t, ++cnt[t];

    vl suf(m + 2);
    for (int i = m; i >= 1; --i)
        suf[i] = cnt[i] + suf[i + 1];

    vl ans(m + 1);

    for (ll k = 1, b = 2; k <= min(30ll, m); ++k, b <<= 1)
        for (ll i = 1, t; i <= m; ++i)
        {
            t = 0;
            for (int q = 1; q <= min(b - 1, m / i); ++q)
                t += suf[q * i];
            if (b * i <= m)
                t += cnt[(b * i)];
            if (t > ans[k])
                ans[k] = t;
        }

    for (int i = 31; i <= m; ++i)
        ans[i] = ans[i - 1];

    for (int i = 1; i <= m; ++i)
        cout << ans[i] << ' ';
    cout << endl;
}
