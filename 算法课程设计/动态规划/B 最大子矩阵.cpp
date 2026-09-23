#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    vvl sum(n + 1, vl(m + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            cin >> sum[i][j];
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    ll ans = 0;
    for (int i = x; i <= n; ++i)
        for (int j = y; j <= m; ++j)
            ans = max(ans, sum[i][j] - sum[i - x][j] - sum[i][j - y] + sum[i - x][j - y]);
    cout << ans << endl;
}
