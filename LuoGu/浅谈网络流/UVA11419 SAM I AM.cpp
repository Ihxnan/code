#include <ihxnan>
#include <MinCostFlowDijkstra>

void solve()
{
    int r, c, n;
    while (cin >> r >> c >> n, n)
    {
        int s = 0, sr = s, sc = sr + r, sn1 = sc + c, sn2 = sn1 + n, t = sn2 + n + 1;
        MinCostFlow<int> mcf(t + 1);
        for (int i = 1; i <= r; ++i)
            mcf.add(s, sr + i, iINF, 1);
        for (int i = 1; i <= c; ++i)
            mcf.add(s, sc + i, iINF, 1);
        for (int i = 1; i <= n; ++i)
            mcf.add(sn1 + i, sn2 + i, 1, 0);
        for (int i = 1; i <= n; ++i)
            mcf.add(sn2 + i, t, 1, 0);
        vi cntR(r + 1), cntC(c + 1);
        for (int i = 1, u, v; i <= n; ++i)
        {
            cin >> u >> v;
            ++cntR[u], ++cntC[v];
            mcf.add(sr + u, sn1 + i, 1, 0);
            mcf.add(sc + v, sn1 + i, 1, 0);
        }
        cout << mcf.flow(s, t).first << endl;
        for (auto &p : mcf.edges())
            if (p.from && p.to != t && p.flow)
                cout << p.from << ' ' << p.to << endl;
    }
}
