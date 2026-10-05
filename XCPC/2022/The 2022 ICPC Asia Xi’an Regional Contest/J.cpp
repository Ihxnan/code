#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    read(arr);
    sort(arr.rbegin(), arr.rend());
    ll ans = 0;
    if (arr[0] > 0)
        ans += arr[0];
    if (n > 1 && arr[1] > 0)
        ans += arr[1];
    cout << ans << endl;
}
