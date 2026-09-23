#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vl arr(n + 1), sa(n + 1), sb(n + 2);
    bool flag = true;
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i], sa[i] = arr[i] + sa[i - 1];
        if (arr[i] > 0)
            flag = false;
    }

    if (flag)
        return cout << *max_element(arr.begin() + 1, arr.end()) << endl, void();

    for (int i = n; i >= 1; --i)
        sb[i] = max(sb[i + 1] + arr[i], arr[i]);

    for (int i = n; i >= 1; --i)
        sb[i] = max(sb[i], sb[i + 1]);

    gdb(sb);
    ll ans = 0;
    for (int i = 0; i <= n; ++i)
        ans = max(ans, sa[i] + sb[i + 1]);

    cout << ans << endl;
}
