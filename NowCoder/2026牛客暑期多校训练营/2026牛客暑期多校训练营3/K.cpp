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
    ll x, y;
    cin >> x >> y;
    ll a, b;
    cin >> a >> b;

    ll f1 = a - x, f2 = b - y;
    x = a, y = b;

    for (ll i = 2; i < n; ++i)
    {
        cin >> a >> b;
        ll g1 = a - x, g2 = b - y;
        ll c = f1 * g2 - f2 * g1;
        if (c == 0)
            cout << "STRAIGHT" << ' ';
        else if (c > 0)
            cout << "LEFT" << ' ';
        else
            cout << "RIGHT" << ' ';
        x = a, y = b;
        f1 = g1, f2 = g2;
    }
    cout << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
