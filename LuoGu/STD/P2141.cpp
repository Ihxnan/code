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
    vi arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    set<int> ans;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (j != i)
                for (int k = j + 1; k <= n; ++k)
                    if (k != i)
                        if (arr[j] + arr[k] == arr[i])
                            ans.insert(arr[i]);
    cout << ans.size() << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
