#include <ihxnan>
#include <MinCostFlowDijkstra>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, a, b, k;
    cin >> n >> a >> b >> k;

    int s = 0, t = a + b + 1;
    MinCostFlowDijkstra<ll> mcf(t + 1);
    for (int i = 1, p, c; i <= a; ++i)
        cin >> p >> c, mcf.add(p, i, c, 0);
    for (int i = 1, p, c; i <= b; ++i)
        cin >> p >> c, mcf.add(i + a, p ? p + a : t, c, 0);

    int ma = 0;
    for (int i = 0, x, y, w; i < n; ++i)
    {
        cin >> x >> y >> w;
        ma = max(ma, w);
        mcf.add(x, a + y, 1, -w);
    }

    auto [f, c] = mcf.flow(s, t, k);
    if (f < k)
        cout << -1 << endl;
    else
        cout << -c << endl;
}
