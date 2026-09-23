#include <ihxnan>

void solve()
{
    int n, m;
    cin >> n >> m;
    int ans = 0;
    int last = 0;
    for (int i = 0; i < n; ++i)
    {
        int sum = 0;
        for (int j = 0, t; j < m; ++j)
            cin >> t, sum += t;
        if (sum < last)
            ++ans;
        last = sum;
    }
    cout << ans << endl;
}
