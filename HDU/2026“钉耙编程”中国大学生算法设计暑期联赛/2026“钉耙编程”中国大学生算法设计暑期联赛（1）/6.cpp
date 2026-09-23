#include <algorithm>
#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
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
    int n;
    cin >> n;
    vvl dp(n + 3, vl(2));
    dp[1][0] = 1;
    dp[2][0] = 2;
    dp[2][1] = 2;
    for (int i = 3; i <= n; ++i)
    {
        dp[i][1] = (dp[i - 1][0] * i) % mod;
        dp[i][0] = (dp[i][1] + dp[i][1] * qmi(i + 3, mod - 2) % mod) % mod;
    }
    gdb(dp);
    ll ans = 0;
    for (ll i = 0, t; i < n; ++i)
    {
        cin >> t;
        ans = (ans + dp[n][i && i < n - 1] * t % mod) % mod;
    }

    ll fact = 1;
    for (int i = 2; i <= n; ++i)
        fact = fact * i % mod;
    cout << ans * qmi(fact, mod - 2) % mod << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
