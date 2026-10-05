#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m, k, b;
    cin >> n >> m >> k >> b;
    int cnt = 0;
    int ans = 0;
    vvi arr;
    vi tmp(m);
    for (int i = 0; i < n; ++i)
    {
        int sum = 0, pos = 0, neg = 0;
        for (auto &p : tmp)
            cin >> p, sum += p, pos += p >= 1, neg += p <= 0;
        if (sum >= k)
            ++ans;
        else if (sum + neg - pos >= k)
            ++cnt;
    }
    cout << ans + min(cnt, b) << endl;
}
