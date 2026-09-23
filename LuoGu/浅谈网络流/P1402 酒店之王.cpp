#include <ihxnan>
#include <MinCostFlowDijkstra>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, p, q;
    cin >> n >> p >> q;
    int s = 0, sp = s, sn1 = sp + p, sn2 = sn1 + n, sq = sn2 + n, t = sq + q + 1;
    MinCostFlowDijkstra<int> mcf(t + 1);
    for (int i = 1; i <= p; ++i)
        mcf.add(s, sp + i, 1, 0);
    for (int i = 1; i <= q; ++i)
        mcf.add(sq + i, t, 1, 0);
    for (int i = 1; i <= n; ++i)
        mcf.add(sn1 + i, sn2 + i, 1, 0);
    for (int i = 1; i <= n; ++i)
        for (int j = 1, t; j <= p; ++j)
            if (cin >> t, t == 1)
                mcf.add(sp + j, sn1 + i, 1, 0);
    for (int i = 1; i <= n; ++i)
        for (int j = 1, t; j <= q; ++j)
            if (cin >> t, t == 1)
                mcf.add(sn2 + i, sq + j, 1, 0);
    cout << mcf.flow(s, t).first << endl;
}
