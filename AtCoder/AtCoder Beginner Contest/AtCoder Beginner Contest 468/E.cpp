#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
#include <Comb>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    cin >> n;
    vl sum(n + 2);
    for (int i = 1; i <= n; ++i)
        cin >> sum[i], sum[i] = (sum[i] + sum[i - 1]) % mod;
    ll ans = n * sum[n] % mod;
    ll tmp = 0;
    Comb comb(mod);
    for (int i = 1; i <= n; ++i)
    {
        ans = (ans - tmp * comb.inv(i) % mod + mod) % mod;
        tmp = (tmp + sum[i] + sum[n] - sum[n - i] + mod) % mod;
    }
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
