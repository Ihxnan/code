#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    ll sum = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        if (i % 2 == 0)
            sum += arr[i];
    }

    vl dif(n);
    for (int i = 0; i < n - 1; i += 2)
    {
        dif[i] = arr[i + 1] - arr[i];
        if (i + 2 < n)
            dif[i + 1] = arr[i + 1] - arr[i + 2];
    }

    ll ma = 0, ans = 0;
    for (int i = 0; i < n; i += 2)
        ma = max(ma + dif[i], dif[i]), ans = max(ma, ans);

    gdb(dif);
    gdb(ans);

    ma = 0;
    for (int i = 1; i < n; i += 2)
        ma = max(ma + dif[i], dif[i]), ans = max(ma, ans);

    cout << sum + ans << endl;
}
