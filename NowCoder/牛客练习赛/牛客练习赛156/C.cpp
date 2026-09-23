#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, d, k;
    cin >> n >> d >> k;

    vvi tree(n + 1);
    int cur = 1;
    for (int i = 1; i <= k && i < n; ++i)
        tree[1].push_back(++cur), tree[cur].push_back(1);
    for (int i = 2; i <= n; ++i)
    {
        int x = k - 1;
        while (x-- && cur < n)
            tree[i].push_back(++cur), tree[cur].push_back(i);
    }

    gdb(tree);

    vi dist(n + 1);

    auto dfs = [&](auto &&self, int f, int r) -> void {
        gdb(f, r);
        for (auto &s : tree[r])
            if (s != f)
                dist[s] = dist[r] + 1, self(self, r, s);
    };

    dfs(dfs, 0, n);

    if (cur != n || *max_element(dist.begin(), dist.end()) > d)
        return cout << -1 << endl, void();

    auto dfs2 = [&](auto &&self, int f, int r) -> void {
        for (auto &s : tree[r])
            if (s != f)
                self(self, r, s), cout << r << ' ' << s << endl;
    };

    dfs2(dfs2, 0, 1);
}
