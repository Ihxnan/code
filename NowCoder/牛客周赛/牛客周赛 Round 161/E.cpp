#include <ihxnan>

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<tl>> adj(n + 1);

    for (int i = 0, u, v, d, r; i < m; ++i)
    {
        cin >> u >> v >> d >> r;
        adj[u].emplace_back(v, d, r);
    }

    vi sta(n + 1);
    vector<pll> dist(n + 1, {lINF, lINF});
    priority_queue<ti, vector<ti>, greater<ti>> que;

    dist[1] = {0, 0};
    que.emplace(0, 0, 1);
    while (que.size())
    {
        int x = get<2>(que.top());
        que.pop();
        if (sta[x])
            continue;
        sta[x] = 1;
        for (auto &[y, dxy, rxy] : adj[x])
            if (dist[y].first > dist[x].first + dxy)
            {
                dist[y].first = dist[x].first + dxy;
                dist[y].second = dist[x].second + rxy;
                que.emplace(dist[y].first, dist[y].second, y);
            }
            else if (dist[y].first == dist[x].first + dxy && dist[y].second > dist[x].second + rxy)
            {
                dist[y].second = dist[x].second + rxy;
                que.emplace(dist[y].first, dist[y].second, y);
            }
    }

    if (dist[n].first == lINF)
        cout << -1 << ' ' << -1 << endl;
    else
        cout << dist[n].first << ' ' << dist[n].second << endl;
}
