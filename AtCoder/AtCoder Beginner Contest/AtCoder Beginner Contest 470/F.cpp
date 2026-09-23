#include <ihxnan>
#include <Comb>
#include <DSU>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    string str;
    cin >> n >> m >> str;
    str = '^' + str;

    DSU dsu(n);
    for (int i = 0, a, b; i < m; ++i)
    {
        cin >> a >> b;
        dsu.merge(a, b);
    }

    map<int, int> hash;
    map<int, map<char, int>> memo;
    bool have = true;
    for (int i = 1; i <= n; ++i)
    {
        ++hash[dsu.get(i)];
        if (++memo[dsu.get(i)][str[i]] == 2)
            have = false;
    }

    ll ans = 1;
    Comb comb(mod);
    for (auto &[k, v] : hash)
        ans = ans * comb.fac(v) % mod;
    if (have)
        ans = ans * comb.inv(2) % mod;
    for (auto &[k1, v1] : memo)
        for (auto &[k2, v2] : v1)
            ans = ans * comb.inv(comb.fac(v2)) % mod;
    cout << ans << endl;
}
