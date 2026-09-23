#include <ihxnan>
#include <MinCostFlowDijkstra>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int m, n;
    cin >> m >> n;
    int s = 0, t = n + 1;
    MinCostFlowDijkstra<int> mcf(t + 1);
    for (int i = 1; i <= m; ++i)
        mcf.add(s, i, 1, 0);
    for (int i = m + 1; i <= n; ++i)
        mcf.add(i, t, 1, 0);
    int u, v;
    while (cin >> u >> v, u != -1)
        mcf.add(u, v, 1, 0);
    cout << mcf.flow(s, t).first << endl;
    for (auto &e : mcf.edges())
        if (e.flow && e.from && e.to != t)
            cout << e.from << ' ' << e.to << endl;
}
