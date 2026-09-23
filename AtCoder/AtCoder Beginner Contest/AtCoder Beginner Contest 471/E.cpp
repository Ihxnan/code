#include <ihxnan>
#include <Comb>

Comb comb(mod);
void solve()
{
    int n, k;
    cin >> n >> k;
    vl arr(n);
    ll sum = 0, sumSquare = 0;
    for (auto &p : arr)
        cin >> p, sum = (sum + p) % mod, sumSquare = (sumSquare + p * p % mod) % mod;
    ll ans = sumSquare * comb.C(n - 1, k - 1) % mod;
    for (auto &p : arr)
        ans = (ans + p * comb.C(n - 2, k - 2) % mod * (sum - p + mod) % mod) % mod;
    cout << ans << endl;
}
