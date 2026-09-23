#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    ll n, q, x;
    cin >> n >> q >> x;
    vl arr(n);
    for (ll i = 0, t; i < n; ++i)
        cin >> t, arr[i] = abs(t - x);
    sort(arr.rbegin(), arr.rend());
    gdb(arr);
    for (int i = 1; i < n; ++i)
        arr[i] += arr[i - 1];
    gdb(arr);
    gdb(arr.back());
    for (ll i = 0, t; i < q; ++i)
    {
        cin >> t;
        if (arr.back() <= t)
            cout << 0 << endl;
        else
            cout << lower_bound(arr.begin(), arr.end(), arr.back() - t) - arr.begin() + 1 << endl;
    }
}
