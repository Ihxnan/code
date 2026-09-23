#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vvi tree(n + 1);
    for (int i = 2, t; i <= n; ++i)
        cin >> t, tree[t].push_back(i);

    auto dfs1 = [&](auto &&self, int root) -> int {
        if (tree[root].empty())
            return 0;
        priority_queue<pii, vector<pii>, greater<pii>> que;
        for (auto &son : tree[root])
            que.emplace(self(self, son), son);
        if (que.size() == 1)
            return que.top().first + 1;
        while (que.size() > 1)
        {
            auto [h1, s1] = que.top();
            que.pop();
            auto [h2, s2] = que.top();
            que.pop();

            int h = max(h1, h2) + 1;
            que.emplace(h, s1);
        }
        return que.top().first;
    };

    ll sum = 0;

    auto dfs2 = [&](auto &&self, int root) -> int {
        if (tree[root].empty())
            return 1;
        priority_queue<int, vector<int>, greater<int>> que;
        for (auto &son : tree[root])
            que.push(self(self, son));
        while (que.size() > 2)
        {
            int sz1 = que.top();
            que.pop();
            int sz2 = que.top();
            que.pop();
            sum += sz1 + sz2;
            que.push(sz1 + sz2);
        }

        int sz = 0;
        while (que.size())
            sz += que.top(), que.pop();

        sum += sz;
        return sz + 1;
    };

    dfs2(dfs2, 1);

    cout << dfs1(dfs1, 1) << ' ' << sum << endl;
}
