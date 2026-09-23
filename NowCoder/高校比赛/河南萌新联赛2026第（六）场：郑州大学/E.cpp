#include <ihxnan>

void solve()
{
    int n, x, y;
    cin >> n >> x >> y;
    vector<vector<pll>> adj(n + 1);
    vector<ti> edges(n);
    for (auto &[u, v, w] : edges)
    {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    auto dijk = [&](int start) -> vl {
        vb sta(n + 1);
        vl dist(n + 1, lINF);
        priority_queue<pll, vector<pll>, greater<pll>> que;

        dist[start] = 0;
        que.emplace(0, start);
        while (que.size())
        {
            int x = que.top().second;
            que.pop();
            if (sta[x])
                continue;
            sta[x] = true;
            for (auto &[y, w] : adj[x])
                if (dist[y] > w + dist[x])
                {
                    dist[y] = w + dist[x];
                    que.emplace(dist[y], y);
                }
        }

        return dist;
    };

    vl dx = dijk(x), dy = dijk(y);
    gdb(dx);
    gdb(dy);

    vi ans(n + 1);

    for (int i = 1; i <= n; ++i)
        if (dx[i] + dx[y] == dy[i])
            ans[i] = x;
        else if (dy[i] + dy[x] == dx[i])
            ans[i] = y;
        else if (dx[i] + dy[i] == dx[y])
            ans[i] = i;

    gdb(ans);

    int tar = 0;
    ll dist = lINF;
    for (int i = 1; i <= n; ++i)
        if (!ans[i])
            if (dx[i] < dist)
                dist = dx[i], tar = i;

    gdb(tar);

    for (int i = 1; i <= n; ++i)
        if (!ans[i])
            ans[i] = tar;

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << ' ';
}
