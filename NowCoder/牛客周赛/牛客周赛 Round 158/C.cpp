#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    map<int, vi> hash;
    for (int i = 1, t; i <= n; ++i)
        cin >> t, hash[t].push_back(i);
    ll ans = 0;
    for (auto &[k, v] : hash)
        if (v.size() & 1)
            ans += v[v.size() >> 1];
    cout << ans << endl;
}
