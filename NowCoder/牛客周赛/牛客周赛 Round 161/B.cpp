#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vl arr(n);
    rd0(arr);
    ll ma = -lINF;
    vi idx;
    for (int i = 0; i < n; ++i)
        if (arr[i] > ma)
            idx.push_back(i), ma = max(ma, arr[i]);
    int ans = 0;
    for (int i = 1; i < idx.size(); ++i)
        ans = max(ans, idx[i] - idx[i - 1]);
    cout << idx.size() << ' ' << ans << endl;
}
