#include <ihxnan>
#include <DSU>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<pii> edge(m);
    vvi adj(n + 1);
    for (auto &[a, b] : edge)
        cin >> a >> b, adj[a].push_back(b);

    vi arr(q);
    for (auto &p : arr)
        cin >> p;

    vb sta(n + 1);
    auto dfs = [&](auto &&self, int r) -> void {
        for (auto &p : adj[r])
            if (!sta[p])
                sta[p] = true, self(self, p);
    };
    sta[1] = true;
    dfs(dfs, 1);

    if (!sta[n])
        return cout << "NO" << endl, void();

    auto check = [&](int mid) -> bool {
        fill(sta.begin(), sta.end(), false);
        for (int i = 0; i <= mid; ++i)
            sta[arr[i]] = true;
        sta[1] = true;
        dfs(dfs, 1);
        return sta[n];
    };

    int l = -1, r = q, mid;
    while (l + 1 < r)
        check(mid = l + r >> 1) ? l = mid : r = mid;

    if (l == -1)
        cout << 0 << endl;
    else if (l == q - 1)
        cout << "YES" << endl;
    else
        cout << l + 1 << endl;
}
