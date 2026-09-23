#include <ihxnan>
#include <Comb>

int init = [] { return cin >> t, 0; }();

Comb comb(mod);
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    map<pii, int> hash;
    for (int i = 0, u, v; i < m; ++i)
        cin >> u >> v, ++hash[{min(u, v), max(u, v)}];
    if (k != 2)
        return cout << 0 << endl, void();
    ll ans = 0;
    for (auto &[k, v] : hash)
        ans = (ans + comb.C(v, 2)) % mod;
    cout << ans << endl;
}
