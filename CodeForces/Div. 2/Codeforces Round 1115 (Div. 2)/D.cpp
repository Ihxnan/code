#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vl arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    for (int i = n; i > 1; --i)
        arr[i] -= arr[i - 1];
    auto parity = [](ll x) -> bool { return (x % 2 + 2) % 2; };
    for (int r = 2, l = 2; r <= n; ++r)
        if (r == n || parity(arr[r]) != parity(arr[r + 1]))
            sort(arr.begin() + l, arr.begin() + r + 1), l = r + 1;
    for (int i = 1; i <= n; ++i)
        cout << (arr[i] += arr[i - 1]) << ' ';
    cout << endl;
}
