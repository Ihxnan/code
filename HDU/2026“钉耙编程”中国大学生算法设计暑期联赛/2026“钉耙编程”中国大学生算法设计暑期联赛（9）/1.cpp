#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    for (auto &p : arr)
        cin >> p;
    sort(arr.begin(), arr.end());
    ll ans = 0, tmp = 0;
    for (int i = 0; i < n; ++i)
        if (arr[i] * 2 <= tmp)
            tmp -= arr[i];
        else
        {
            ans += 2 * arr[i] - tmp;
            tmp = arr[i];
        }
    cout << ans << endl;
}
