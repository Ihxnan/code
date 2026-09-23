#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> n >> m;
    vi v(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> v[i];
    vvi mp(n + 1, vi(m + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> mp[i][j];
    int ans = m;
    multiset<int, greater<int>> hash;
    for (int i = n, t = ans; i > 0; --i, t = ans)
    {
        for (int j = 1; j <= m; ++j)
            hash.insert(mp[i][j]);
        gdb(hash);
        ll sum = 0;
        auto it = hash.begin();
        gdb(t);
        while (t--)
            if ((sum += *it++) >= v[i])
                break;
        gdb(t);
        if (t > 0)
            ans -= t;
    }
    cout << ans << endl;
}
