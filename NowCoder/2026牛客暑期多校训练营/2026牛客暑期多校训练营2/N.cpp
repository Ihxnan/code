#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
#undef cout
    int n, k;
    cin >> n >> k;
    vl arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    sort(arr.begin(), arr.end());
    vl sum(n + 1);
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + arr[i];
    if (k < 3)
    {
        cout << sum[n] << endl;
        return;
    }
    ll ans = 0;
    if (k & 1)
        for (int i = k; i <= n; ++i)
            ans = max(ans, sum[n] - sum[k >> 1] - sum[i] + sum[i - k / 2 - 1] + k * arr[i - k / 2]);
    else
        for (int i = k; i <= n; ++i)
            ans = max(ans, sum[n] - sum[k / 2 - 1] - sum[i] + sum[i - k / 2 - 1] +
                               k / 2 * (arr[i - k / 2] + arr[i - k / 2 + 1]));
    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
