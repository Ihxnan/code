#include <ihxnan>

lll cost(lll k, lll x, lll a, lll b)
{
    lll ca1 = k * (a + k * a - k + 1) / 2;
    lll la = x - ca1;
    if (la <= 0)
        return k;
    lll las = k * a - k;
    lll l = 1, r = 1e9;
    lll ans = 1e9;
    while (l <= r)
    {
        lll mid = (l + r) >> 1;
        lll pd = (mid <= las) ? mid * (2 * las - mid + 1) / 2 : las * (las + 1) / 2;
        lll ca = mid * b + pd;
        if (ca >= la)
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    return k + ans;
}

void solve()
{
    lll x, a, b;
    cin >> x >> a >> b;
    if (a == 1)
        return cout << (x + b - 1) / b, void();

    lll K = 0;
    while ((K + 1) * (K + 1) <= 2 * x)
        ++K;
    K += 6;
    lll ans = (x + b - 1) / b;
    for (lll k = 1; k <= K; ++k)
        ans = min(ans, cost(k, x, a, b));
    cout << ans << endl;
}
