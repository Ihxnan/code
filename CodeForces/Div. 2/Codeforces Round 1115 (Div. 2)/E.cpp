#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    ll n;
    cin >> n;
    auto work = [](ll n) {
        ll ans = 0;
        for (ll i = 1; i < n - 1; ++i)
            for (ll j = i + 1; 2 * j - i <= n; ++j)
                ans += (i ^ j) == 2 * j - i;
        return ans;
    };
    for (int i = 1; i <= n; ++i)
        gdb(i, work(i));
}
