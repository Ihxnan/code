#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    ll n, k, m;
    cin >> n >> k >> m;
    if (k == 1)
    {
        ll ans = 1;
        ans += min(m, n - 1);
        ans += (n - ans) / 2;
        cout << ans << endl;
    }
    else
    {
        ll kb = n / k;
        ll ans = 0;
        if (m <= n - kb + (kb - 1) % 2)
            ans = 1 + (kb - 1) / 2 + m;
        else
        {
            ans = 1 + (kb - 1) / 2 + n - kb + (kb - 1) % 2;
            ans += (m - (n - kb + (kb - 1) % 2)) / 2;
            ans = min(ans, n);
        }
        cout << ans << endl;
    }
}
