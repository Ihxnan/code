/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
ll qmi(ll a, ll b)
{
    ll ans = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1)
            ans = ans * a % mod;
    return ans;
}

void solve()
{
    mod = 9901;
    int a, b;
    cin >> a >> b;
    map<int, int> hash;
    for (int i = 2; i <= sqrt(a); ++i)
        while (a % i == 0)
            ++hash[i], a /= i;
    if (a > 1)
        ++hash[a];
    ll ans = 1;
    for (auto &[p, n] : hash)
        if ((p - 1) % mod)
            ans = ans * (qmi(p, n * b + 1) - 1 + mod) % mod * qmi(p - 1, mod - 2) % mod;
        else
            ans = ans * (n * b + 1) % mod;
    cout << ans;
}
/* ╚══════════ /SOLVE ══════════╝ */
