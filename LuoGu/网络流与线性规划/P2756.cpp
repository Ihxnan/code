/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, m;
    cin >> m >> n;
    int u, v;
    vvi adj(n + 1);
    while (cin >> u >> v, u != -1)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vi visit(n + 1);
    vi match(n + 1);
    auto dfs = [&](auto &&self, int x) -> bool {
        for (auto &p : adj[x])
            if (!visit[p])
            {
                visit[p] = 1;
                if (!match[p] || self(self, match[p]))
                {
                    match[p] = x;
                    return true;
                }
            }
        return false;
    };

    int cnt = 0;
    for (int i = 1; i <= m; ++i)
    {
        fill(visit.begin(), visit.end(), 0);
        cnt += dfs(dfs, i);
    }

    cout << cnt << endl;
    for (int i = 1; i <= n; ++i)
        if (match[i])
            cout << match[i] << ' ' << i << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
