#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi a(n), b(n);
    int sa = 0, sb = 0;
    for (auto &p : a)
        cin >> p, sa ^= p;
    for (auto &p : b)
        cin >> p, sb ^= p;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a == b)
        return cout << "YES" << endl, void();
    int tar = sa ^ sb;
    int idx;
    bool flag = true;
    for (int i = 0; i < n; ++i)
        if (a[i] == tar)
            flag = false, idx = i;
    if (flag)
        return cout << "NO" << endl, void();
    for (int i = 0; i < n; ++i)
        if (i != idx)
            a[i] ^= tar;
    sort(a.begin(), a.end());
    cout << (a == b ? "YES" : "NO") << endl;
}
