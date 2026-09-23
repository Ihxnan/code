#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define double long double
using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;
const ll mod = 998244353;

ll ksm(ll base, ll up) {
    ll res = 1;
    while (up) {
        if (up & 1) {
            res = res * base % mod;
        }
        base = base * base % mod;
        up >>= 1;
    }
    return res;
}

ll inv(ll x) {
    return ksm(x, mod - 2);
}


void solve() {
    double sx, sy, ax, ay, bx, by;
    cin >> sx >> sy >> ax >> ay >> bx >> by;

    if (sx == 0)
    {
        double la = ax, lb = bx;
        if (la * lb < 0)
            cout << fixed << setprecision(15) << (double)0 << ' ' << fixed << setprecision(15) << max({ abs(la), abs(lb) }) << endl;
        else
            cout << fixed << setprecision(15) << min({ abs(la), abs(lb) }) << ' ' << fixed << setprecision(15) << max({ abs(la), abs(lb) }) << endl;
        return;
    }

    double len = sqrtl(ax * ax + ay * ay);

    double sun = atan2l(sy, sx);
    double a = atan2l(ay, ax);
    double b = atan2l(by, bx);

    double la = ax - ay / tanl(sun);
    double lb = bx - by / tanl(sun);

    double mx = max(abs(la), abs(lb));
    double mn = min(abs(la), abs(lb));
    double ca = ax * sx + ay * sy, cb = bx * sx + by * sy;
    if (ca * cb <= 0)
        mx = max(mx, len / sin(sun));
    
    if (la * lb < 0)
        mn = min(mn, (double)0);
    cout << fixed << setprecision(15) << mn << ' ' << fixed << setprecision(15) << mx << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
