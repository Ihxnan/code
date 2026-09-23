#include <ihxnan>

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    double ans = 0;
    for (int i = 1; i <= k; ++i)
        ans += 1.0 * (n + k - i) / (n + k) * m;
    printf("%.20f", ans);
}
