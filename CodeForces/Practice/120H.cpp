#include <ihxnan>

void solve()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    vector<vector<string>> adj(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        string str;
        cin >> str;
        for (int mask = 1; mask < 1 << str.size(); ++mask)
            if (__builtin_popcount(mask) <= 4)
            {
                string tmp;
                for (int j = 0; j < str.size(); ++j)
                    if (mask >> j & 1)
                        tmp += str[j];
                adj[i].push_back(tmp);
            }
    }

    map<string, int> visit;
    map<string, int> match;
    vector<string> ans(n + 1);

    auto dfs = [&](auto &&self, int x) -> bool {
        for (auto &p : adj[x])
            if (!visit[p])
            {
                visit[p] = true;
                if (!match[p] || self(self, match[p]))
                {
                    match[p] = x;
                    ans[x] = p;
                    return true;
                }
            }
        return false;
    };

    for (int i = 1; i <= n; ++i)
    {
        visit.clear();
        if (!dfs(dfs, i))
            return cout << -1 << endl, void();
    }

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << endl;
}
