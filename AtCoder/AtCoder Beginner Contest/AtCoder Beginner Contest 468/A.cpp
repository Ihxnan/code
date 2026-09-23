#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    for (auto &p : arr)
        cin >> p;
    int cnt = 0;
    for (int i = 0; i < n - 2; ++i)
        cnt += arr[i] < arr[i + 1] && arr[i + 2] < arr[i + 1];
    cout << cnt << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
