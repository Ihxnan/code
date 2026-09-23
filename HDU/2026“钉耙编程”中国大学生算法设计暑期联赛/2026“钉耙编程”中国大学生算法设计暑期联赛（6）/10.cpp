#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    ll x, y;
    cin >> x >> y;

    if (!y)
        return cout << 0, void();

    if (x <= 2)
        return cout << (x + x + y - 1) * y / 2 << endl, void();

    ll d = (x - 2) / (y + 1);
    ll r = (x - 2) % (y + 1);

    gdb(d, r);

    ll ans = (d + 1) * ((y - r) * (d + 2) + (y - r - 1) * (y - r) / 2 * (d + 1)) +
             (d + 2) * (r * (y - r) * (d + 1) + (1 + r) * r / 2 * (d + 2));

    cout << ans << endl;
}
