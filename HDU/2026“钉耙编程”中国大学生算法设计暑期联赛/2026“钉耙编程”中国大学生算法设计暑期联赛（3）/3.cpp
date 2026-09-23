#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    ll n;
    cin >> n;
    vector<ll> dp(64, lINF);
    for (ll i = 0, x; i < n; ++i)
    {
        cin >> x;
        for (int j = 63; j; --j)
            if (x >= dp[j - 1])
                dp[j] = min(dp[j], dp[j - 1] + x);
        dp[0] = min(dp[0], x);
    }
    for (int i = 0; i < 63; ++i)
        if (dp[i] == lINF)
        {
            cout << i << endl;
            return;
        }
}
/* ╚══════════ /SOLVE ══════════╝ */
