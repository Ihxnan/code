#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vl a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    vl f(n + 1);
    for (int i = 2; i <= n; ++i)
        cin >> f[i];

    ll sum = accumulate(a.begin() + 2, a.end(), 0ll);

    if (sum > 0)
        return cout << 1 << endl, void();
    if (sum < 0)
        return cout << -1 << endl, void();

    vl b(n + 1);

    for (int i = 2; i <= n; ++i)
        b[f[i]] += b[i] + a[i], b[i] = 0;

    cout << (b[1] == 0 ? 0 : b[1] > 0 ? 1 : -1) << endl;
}
