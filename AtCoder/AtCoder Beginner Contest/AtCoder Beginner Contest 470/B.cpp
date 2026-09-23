#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    map<int, int> cnt;
    for (int i = 0, t; i < n; ++i)
        cin >> t, ++cnt[t];
    int ma = 0;
    for (auto &[k, v] : cnt)
        ma = max(ma, v);
    cout << n - ma << endl;
}
