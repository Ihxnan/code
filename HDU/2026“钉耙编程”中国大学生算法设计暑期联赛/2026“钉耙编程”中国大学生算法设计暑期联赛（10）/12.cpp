#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    int cnt = 0;
    int last = 0, t;
    for (int i = 0; i < n; ++i)
    {
        cin >> t, cnt += t <= n;
    }
    if (cnt == n)
        return cout << "NO" << endl, void();
    if (cnt == n - 1)
        return cout << "YES" << endl, void();
}
