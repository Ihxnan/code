#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vvi ans(n);

    auto dfs = [&](auto &&self, int l, int r, int pos) -> void {
        if (l == r)
            return;
        int mid = l + r >> 1;
        for (int i = l; i <= mid; ++i)
            ans[pos].push_back(i);
        self(self, l, mid, pos + 1);
        self(self, mid + 1, r, pos + 1);
    };

    dfs(dfs, 1, n, 0);

    int cnt = 0;
    while (ans[cnt].size())
        ++cnt;

    cout << cnt << endl;
    for (int i = 0; i < cnt; ++i)
    {
        cout << ans[i].size() << ' ';
        for (auto &p : ans[i])
            cout << p << ' ';
        cout << endl;
    }
}
