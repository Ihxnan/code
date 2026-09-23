#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    int sum = 0;
    for (auto &p : arr)
        cin >> p, sum += p;
    int ans = iINF;
    int s2 = 0;
    for (int i = 0; i < n - 1; ++i)
        s2 += arr[i], sum -= arr[i], ans = min(ans, abs(sum - s2));
    cout << ans << endl;
}
