#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<pii> arr(q);
    for (auto &[a, b] : arr)
        cin >> a >> b;
    sort(arr.begin(), arr.end(), [&](auto &a, auto &b) { return a.second < b.second; });
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    int cnt = 0;
    int last = -1;
    for (auto &[a, b] : arr)
        if (a > last)
        {
            last = b;
            ++cnt;
        }
    int ans = 0;
    while (cnt)
    {
        ++ans;
        cnt /= 2;
    }
    cout << ans << endl;
}
