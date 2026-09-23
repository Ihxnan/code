#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    set<pii> hash;
    int id = 0;
    for (auto &p : arr)
        cin >> p, hash.emplace(++id, p);
    bool flag = true;
    for (int i = 1; i < n; ++i)
        if (arr[i] < arr[i - 1])
        {
            flag = false;
            break;
        }
    if (flag)
        return cout << n - 1 << endl, void();
    flag = true;
    for (int i = 1; i < n; ++i)
        if (arr[i] > arr[i - 1])
        {
            flag = false;
            break;
        }
    if (flag)
        return cout << n - 1 << endl, void();
    for (int i = 1; i < n; ++i)
        if (abs(arr[i - 1] - arr[i]) == 1)
        {
            hash.emplace(i - 1 + 1, arr[i]);
            hash.emplace(i + 1, arr[i - 1]);
        }
    flag = true;
    for (int i = 1; i <= n; ++i)
        if (!hash.count({i, i}))
        {
            flag = false;
            break;
        }
    if (flag)
        return cout << n << endl, void();
    flag = true;
    for (int i = 1; i <= n; ++i)
        if (!hash.count({i, n + 1 - i}))
        {
            flag = false;
            break;
        }
    if (flag)
        return cout << n << endl, void();
    cout << -1 << endl;
}
