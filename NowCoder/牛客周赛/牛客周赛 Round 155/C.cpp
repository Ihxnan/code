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
    string s, t;
    cin >> s >> t;
    int ans = n;

    auto add = [](char &ch, int x) -> void { ch = (ch - 'A' + x) % 5 + 'A'; };

    auto work = [&](int c, int p, int q, string s) -> void {
        for (int i = 0; i < c; ++i)
            add(s[i], p);
        for (int i = c; i < n; ++i)
            add(s[i], q);
        int cnt = 0;
        for (int i = 0; i < n; ++i)
            cnt += s[i] != t[i];
        ans = min(ans, cnt);
    };

    for (int c = 0; c <= n; ++c)
        for (int p = 0; p <= 4; ++p)
            for (int q = 0; q <= 4; ++q)
                work(c, p, q, s);

    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
