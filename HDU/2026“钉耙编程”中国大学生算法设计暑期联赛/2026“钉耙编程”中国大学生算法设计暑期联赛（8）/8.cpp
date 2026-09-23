#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vvi tree(n + 1);
    for (int i = 0, u, v; i < n - 1; ++i)
        cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);
    int i;
    vi sz(n + 1);
    vi cnt(n + 1, 1);

    auto dfs = [&](auto &&self, int f, int r) -> void {
        for (auto &s : tree[r])
            if (s != f)
            {
                self(self, r, s);
                sz[r] += sz[s];
            }
        cnt[r] += sz[r];
    };

    for (i = 1; i <= n; ++i)
        fill(sz.begin(), sz.end(), 1), dfs(dfs, 0, i);
    set<int> hash;

    auto mex = [&](int ans) {
        for (auto &p : hash)
            if (p == ans + 1)
                ++ans;
            else
                return ans + 1;
        return ans + 1;
    };

    vi p(n + 1);

    int ans;
    auto dfs2 = [&](auto &&self, int f, int r, int cur) -> void {
        cur = mex(cur) - 1;
        while (hash.size() && *hash.begin() <= cur)
            hash.erase(hash.begin());
        ans += mex(cur);
        for (auto &s : tree[r])
            if (s != f)
            {
                hash.insert(p[s]);
                self(self, r, s, cur);
                hash.erase(p[s]);
            }
    };

    ans = 0;
    vi tmp(n);
    iota(tmp.begin(), tmp.end(), 1);
    sort(tmp.begin(), tmp.end(), [&](int x, int y) { return cnt[x] < cnt[y]; });
    for (int i = 0; i < n; ++i)
        p[tmp[i]] = i;
    for (int i = 1; i <= n; ++i)
        hash.insert(p[i]), dfs2(dfs2, 0, i, mex(-1) - 1), hash.erase(p[i]);
    cout << ans / 2 + 1 << ' ';

    ans = 0;
    sort(tmp.begin(), tmp.end(), [&](int x, int y) { return cnt[x] > cnt[y]; });
    for (int i = 0; i < n; ++i)
        p[tmp[i]] = i;
    for (int i = 1; i <= n; ++i)
        hash.insert(p[i]), dfs2(dfs2, 0, i, mex(-1) - 1), hash.erase(p[i]);
    cout << ans / 2 + 1 << endl;
}
