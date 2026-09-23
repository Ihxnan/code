#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vvi mp(n, vi(n));
    for (auto &p : mp)
        for (auto &q : p)
            cin >> q;

    vi arr(n);
    iota(arr.begin(), arr.end(), 0);
    int ans = iINF;

    auto dfs = [&](auto &&self, int pos, int dist) -> void {
        if (pos == n)
        {
            ans = min(ans, dist + mp[arr[n - 1]][0]);
            return;
        }

        for (int i = pos; i < n; ++i)
            if (dist + mp[arr[pos - 1]][arr[i]] < ans)
            {
                swap(arr[i], arr[pos]);
                self(self, pos + 1, dist + mp[arr[pos - 1]][arr[pos]]);
                swap(arr[i], arr[pos]);
            }
    };

    dfs(dfs, 1, 0);

    cout << ans << endl;
}
