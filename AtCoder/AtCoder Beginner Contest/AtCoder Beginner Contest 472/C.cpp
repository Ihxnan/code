#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    ll n, m, k;
    cin >> n >> m >> k;
    vl arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    int l = 0;
    ll sum = 0;
    vb ans(n + 1);
    for (int r = 1; r <= n; ++r)
    {
        if (r - l + 1 > m)
        {
            if (ans[l])
                sum -= arr[l];
            ++l;
        }
        if (sum + arr[r] <= k)
            ans[r] = true, sum += arr[r];
        else
            ans[r] = false;
    }

    for (int i = 1; i <= n; ++i)
        if (ans[i])
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
}
