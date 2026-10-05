#include <ihxnan>

void solve()
{
    int n, q;
    cin >> n >> q;

    vvi adj(n + 1);
    for (int i = 2, p; i <= n; ++i)
        cin >> p, adj[p].push_back(i);

    vi ans(n + 1);
    vi sz(n + 1, 1);
    vector<set<pii>> arr(n + 1);

    auto dfs = [&](auto &&self, int r) -> void {
        for (auto &s : adj[r])
        {
            self(self, s);
            sz[r] += sz[s];
            if (arr[r].size() < arr[s].size())
                swap(arr[r], arr[s]);
            while (arr[s].size())
                arr[r].insert(*arr[s].begin()), arr[s].erase(arr[s].begin());
        }
        arr[r].emplace(sz[r], r);
        ans[r] = arr[r].lower_bound({(sz[r] + 1) / 2, 0})->second;
    };

    dfs(dfs, 1);

    for (int i = 0, t; i < q; ++i)
        cin >> t, cout << ans[t] << endl;
}
