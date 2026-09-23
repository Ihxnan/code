#include <ihxnan>
#include <SuffixArray>

void solve()
{
    string str;
    cin >> str;
    ll ans = 0;
    for (ll i = 1; i <= str.size(); ++i)
        ans += i * (i + 1) / 2;
    SuffixArray SA(str);
    for (auto &p : SA.lc)
        ans -= 1ll * p * (p + 1) / 2;
    cout << ans << endl;
}
