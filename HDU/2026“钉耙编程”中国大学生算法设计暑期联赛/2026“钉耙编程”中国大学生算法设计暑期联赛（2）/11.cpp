#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    cin >> n;
    vi arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    gdb(arr);
    vvl dp(n + 1, vl(2));
    for (int i = 2; i <= n; ++i)
    {
        dp[i][0] = min(dp[i - 1][0] + arr[i], dp[i - 1][1] + max(arr[i] - arr[i - 2], 0));
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + arr[i - 1];
    }
    gdb(dp);
    cout << min(dp[n][0], dp[n][1]) << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
