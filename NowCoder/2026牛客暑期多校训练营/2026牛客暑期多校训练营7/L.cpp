#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    ll n;
    cin >> n;
    ll t = 2, ans = 0;
    for (int i = 1; i <= sqrt(n) * 2; ++i)
    {
        t = i * (i + 1);
        ans += n / t * i;
        if (n % t - (t - i - 1) >= 0)
            ans += n % t - (t - i - 1);
    }
    cout << ans << endl;
}
