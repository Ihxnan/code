#include <ihxnan>

void solve()
{
    ll n, s, l;
    cin >> n >> s >> l;
    vl dist(n + 1);
    for (int i = 1; i < n; ++i)
        cin >> dist[i];

    auto func = [&](int idx, ll len, bool flag) -> ll {
        if (flag == false)
        {
            while (idx < n && len >= dist[idx])
                len -= dist[idx++];
            return idx;
        }
        else
        {
            while (idx > 1 && len >= dist[idx - 1])
                len -= dist[--idx];
            return idx;
        }
    };

    ll len = l;
    ll ans = 0;
    for (int i = s; i >= 1; --i)
    {
        if (len < 0)
            break;
        ans = max(ans, max(s, func(i, len, 0)) - i + 1);
        len -= dist[i - 1];
    }

    len = l;
    for (int i = s; i <= n; ++i)
    {
        if (len < 0)
            break;
        ans = max(ans, i - min(s, func(i, len, 1)) + 1);
        len -= dist[i];
    }

    cout << ans << endl;
}
