#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    ll n;
    cin >> n;
    vl arr(n);
    ll sum = 0;
    for (auto &p : arr)
        cin >> p, p *= 1000000, sum += p;
    vl mi(n), ma(n);
    for (int i = 0; i < n; ++i)
        mi[i] = max(arr[i] - 500000, 0ll), ma[i] = arr[i] + 499999;

    gdb(mi, arr, ma);

    int id = 0;
    const ll tar = 100000000;
    while (id < n && sum > tar)
    {
        if (sum - tar >= arr[id] - mi[id])
            sum -= arr[id] - mi[id], arr[id] = mi[id];
        else
            arr[id] -= sum - tar, sum = tar;
        ++id;
    }

    while (id < n && sum < tar)
    {
        if (tar - sum >= ma[id] - arr[id])
            sum += ma[id] - arr[id], arr[id] = ma[id];
        else
            arr[id] += tar - sum, sum = tar;
        ++id;
    }

    if (sum != tar)
        cout << "No" << endl;
    else
    {
        cout << "Yes" << endl;
        for (auto &p : arr)
            cout << p << ' ';
        cout << endl;
    }
}
